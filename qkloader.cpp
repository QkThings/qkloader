/*
 * QkThings LICENSE
 * The open source framework and modular platform for smart devices.
 * Copyright (C) 2014 <http://qkthings.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "xmodem.h"

#include <QDebug>
#include <QSerialPort>
#include <QSettings>
#include <QEventLoop>
#include <QTimer>

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

    QEventLoop eventLoop;
    QTimer timer;
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(m_device, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));

    m_device->readAll();

    // Autobaud sync
    byteBuf = 'U';
    m_device->write(&byteBuf, 1);
    waitForChipID();
//    waitForData(1000);
//    timer.start(1000);
//    eventLoop.exec();
//    emit output(QString(m_device->readAll()));

    // Enter upload mode (XMODEM)
    byteBuf = 'u';
    m_device->write(&byteBuf, 1);
    waitForReady();
//    waitForData(2000);
//    timer.start(2500);
//    eventLoop.exec();
//    emit output(QString(m_device->readAll()));

    // Send file through XMODEM-CRC protocol
    success = m_xmodem->sendFile(filePath);
    m_device->readAll();
    emit output(tr("Done"));
    return success;
}

bool QkLoaderEFM32::waitForChipID()
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
            QString line = QString(m_device->readLine());
            if(line.contains("ChipID"))
            {
                emit output(tr("Bootloader detected"));
                return true;
            }
        }
    }
}

bool QkLoaderEFM32::waitForReady()
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
            QString line = QString(m_device->readLine());
            if(line.contains("C"))
            {
                emit output(tr("Ready"));
                return true;
            }
        }
    }
}

bool QkLoaderEFM32::waitForData(int timeout)
{
    QEventLoop eventLoop;
    QTimer timer;

    timer.setInterval(timeout);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));
    connect(m_device, SIGNAL(readyRead()), &eventLoop, SLOT(quit()));

    if(m_device->bytesAvailable() > 0)
        return true;
    else
    {
        timer.start();
        eventLoop.exec();
        return (timer.remainingTime() > 0);
    }
}
