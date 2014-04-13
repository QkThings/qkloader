/*
 * XMODEM-CRC implementation following this specification:
 * http://web.mit.edu/6.115/www/miscfiles/amulet/amulet-help/xmodem.htm
 */

#include "xmodem.h"

#include <QDebug>

#include <QSerialPort>
#include <QFile>
#include <QEventLoop>
#include <QTimer>

XMODEM::XMODEM(QSerialPort *sp, QObject *parent) :
    QObject(parent)
{
    m_serialPort = sp;
}

bool XMODEM::sendFile(const QString &filePath)
{
    QFile file(filePath);

    if(!file.open(QFile::ReadOnly))
    {
        qDebug() << "failed to open file" << filePath;
        return false;
    }

    file.size();

    char dataBuffer[128];
    m_packetNumber = 1;

    int totalBytesRead = 0;
    double progress = 0.0;

    m_serialPort->readAll();
//    qDebug() << "waiting for 'C'";
//    while(m_serialPort->waitForReadyRead(3500));
//    m_serialPort->readAll();

    while(!file.atEnd())
    {
        int bytesRead = file.read(dataBuffer, 128);
        totalBytesRead += bytesRead;

        for(int i = bytesRead; i < 128; i++)
            dataBuffer[i] = 0xFF; // pad buffer with 0xFF

//        for(int i=0; i < 128; i++) dataBuffer[i] = 0xFF;

//        progress = (double)totalBytesRead/(double)(file.size())*100.0;
//        qDebug() << "progress:" << (int)progress << "%";
        qDebug() << "packet:" << m_packetNumber << "bytes transfered:" << QString().sprintf("%10d / %10d", totalBytesRead, file.size());
        emit output(QString().sprintf("[%d/%d]", totalBytesRead, file.size()));

        sendPacket(dataBuffer, 128);
        waitACK(1000);
    }

    dataBuffer[0] = (char) XMODEM::EOT;
    m_serialPort->write(dataBuffer, 1);
    waitACK(1000);

    dataBuffer[0] = (char) XMODEM::ETB;
    m_serialPort->write(dataBuffer, 1);
    waitACK(1000);

    qDebug() << "file sent";
    qDebug() << m_serialPort->readAll();

    file.close();

    return true;
}

void XMODEM::sendPacket(char *data, int count)
{
    QSerialPort *sp = m_serialPort;
    QByteArray packet;
    int crc = calculateCRC(data, count);

    packet.append(XMODEM::SOH);
    packet.append(m_packetNumber);
    packet.append(0xFF - m_packetNumber);
    packet.append(data, count);
    packet.append((char) ((crc >> 8) & 0xFF));
    packet.append((char) (crc & 0xFF));

    m_packetNumber++;
    if(m_packetNumber > 255)
        m_packetNumber = 0;

    sp->write(packet);
}

int XMODEM::waitACK(int timeout)
{
//    if(!m_serialPort->waitForReadyRead(timeout))
//    {
//        qDebug() << "timeout";
//        return -1;
//    }
    int retries = 4;
    QByteArray rxData;

    QTimer timer;
    QEventLoop eventLoop;

    timer.setInterval(3500);

    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(m_serialPort, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));

    while(retries-- > 0)
    {
        //m_serialPort->waitForReadyRead(timeout);
        eventLoop.exec();
        rxData = m_serialPort->readAll();
        if(rxData.size() > 0)
            break;
    }

    if(retries == 0 && rxData.size() == 0)
    {
        qDebug() << "failed to get ack";
        emit output(tr("XMODEM: Failed to get ACK"));
        return -1;
    }

//    qDebug() << "ack size:" << rxData.size();
//    for(int i=0; i < rxData.size(); i++)
//        qDebug() << QString().sprintf("  %02X", rxData.at(i));

    int code = rxData.at(0);
    switch(code)
    {
    case XMODEM::ACK: qDebug() << "ACK"; break;
    case XMODEM::NAK: qDebug() << "NAK"; break;
    default:
        qDebug() << "unknown ACK code:" << QString().sprintf("%02X",code);
        emit output(tr("XMODEM: Unknown ACK code") + QString().sprintf("%02X",code));
    }
    return code;
}

int XMODEM::calculateCRC(char *ptr, int count)
{
    int  crc;
    char i;
    crc = 0;
    while (--count >= 0)
    {
        crc = crc ^ (int) *ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return (crc);
}
