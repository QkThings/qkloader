#include "qkloader.h"

#include "xmodem.h"

#include <QDebug>
#include <QSerialPort>
#include <QSettings>

QkLoader::QkLoader(QIODevice *device, QObject *parent) :
    QObject(parent)
{
    m_device = device;
}

void QkLoader::setCpuName(const QString &cpuName)
{
    m_cpuName = cpuName;
}

QkLoaderEFM32::QkLoaderEFM32(QIODevice *device, QObject *parent) :
    QkLoader(device, parent)
{
    m_xmodem = new XMODEM((QSerialPort*)device, this);

    connect(m_xmodem, SIGNAL(output(QString)), this, SIGNAL(output(QString)));
}

bool QkLoaderEFM32::upload(const QString &filePath)
{
    bool success;
    char byteBuf;

    // Autobaud sync
    byteBuf = 'U';
    m_device->write(&byteBuf, 1);
    m_device->waitForReadyRead(500);
    m_device->readAll();

    // Enter upload mode (XMODEM)
    byteBuf = 'u';
    m_device->write(&byteBuf, 1);
    m_device->waitForReadyRead(500);
    m_device->readAll();

    // Send file through XMODEM-CRC protocol
    success = m_xmodem->sendFile(filePath);

    m_device->readAll();
    return success;
}
