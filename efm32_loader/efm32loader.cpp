#include "efm32loader.h"

#include "xmodem.h"

#include <QSerialPort>
#include <QEventLoop>
#include <QTimer>
#include <QFile>
#include <QElapsedTimer>

EFM32Loader::EFM32Loader(QObject *parent) :
    QObject(parent)
{
    m_serialPort = new QSerialPort(this);
    m_xmodem = new XMODEM(m_serialPort, this);
    connect(m_xmodem, SIGNAL(output(QString)), this, SIGNAL(output(QString)));
}

bool EFM32Loader::open(const QString &portName)
{
    QSerialPort *sp = m_serialPort;

    if(!sp->isOpen())
    {
        sp->setPortName(portName);
        if(sp->open(QSerialPort::ReadWrite))
        {
            //sp->setBaudRate(115200);
            sp->setBaudRate(450000);
            sp->setDataBits(QSerialPort::Data8);
            sp->setParity(QSerialPort::NoParity);
            sp->setStopBits(QSerialPort::OneStop);
            sp->setFlowControl(QSerialPort::NoFlowControl);

            emit output(tr("Connected"));
        }
        else
        {
            QString errMsg = tr("Failed to open port. ") + sp->errorString();
            emit output(errMsg);
            return false;
        }
    }
    else
    {
        emit output(tr("Port is already opened"));
        return false;
    }

    return true;
}

void EFM32Loader::close()
{
    emit output(tr("Disconnected"));
    m_serialPort->close();
}

bool EFM32Loader::upload(const QString &filePath)
{
    QFile file(filePath);
    if(!file.open(QFile::ReadOnly))
    {
        emit output(tr("Failed to open binary file"));
        return false;
    }

    bool success;
    char byteBuf;

    QElapsedTimer elapsedTimer;

    m_serialPort->readAll();
    enterBoot();

    elapsedTimer.start();

    // Autobaud sync
    byteBuf = 'U';
    m_serialPort->write(&byteBuf, 1);
    waitForChipID();

    // Enter upload mode (XMODEM)
    byteBuf = 'u';
    m_serialPort->write(&byteBuf, 1);
    waitForReady();

    // Send file through XMODEM-CRC protocol
    success = m_xmodem->sendFile(filePath);
    emit output(QString().sprintf("Elapsed time: %.3f seconds", (double)elapsedTimer.elapsed()/1000.0));
    m_serialPort->readAll();
    exitBoot();
    emit output(tr("Done"));
    return success;
}

void EFM32Loader::enterBoot()
{
    // RTS - RSTN
    // DTR - DBG

    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));

    m_serialPort->setDataTerminalReady(false);
    timer.start(100);
    eventLoop.exec();

    reset();
}

void EFM32Loader::exitBoot()
{
    m_serialPort->setDataTerminalReady(true);
    reset();
}

void EFM32Loader::reset()
{
    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));

    m_serialPort->setRequestToSend(true);
    timer.start(100);
    eventLoop.exec();
    m_serialPort->setRequestToSend(false);
    timer.start(100);
    eventLoop.exec();
}

bool EFM32Loader::waitForChipID()
{
    while(1)
    {
        if(!waitForData(2000))
        {
            emit output("Unable to receive ChipID");
            return false;
        }
        else
        {
            QString line = QString(m_serialPort->readLine());
            if(line.contains("ChipID"))
            {
                emit output(tr("Bootloader detected"));
                return true;
            }
        }
    }
}

bool EFM32Loader::waitForReady()
{
    while(1)
    {
        if(!waitForData(2000))
        {
            emit output("Unable to receive 'C'");
            return false;
        }
        else
        {
            QString line = QString(m_serialPort->readLine());
            if(line.contains("C"))
            {
                emit output(tr("Ready"));
                return true;
            }
        }
    }
}

bool EFM32Loader::waitForData(int timeout)
{
    QEventLoop eventLoop;
    QTimer timer;

    timer.setInterval(timeout);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(m_serialPort, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));

    if(m_serialPort->bytesAvailable() > 0)
        return true;
    else
    {
        timer.start();
        eventLoop.exec();
        return (timer.remainingTime() > 0);
    }
}


