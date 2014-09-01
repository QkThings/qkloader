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
#include "ui_qkloadergui.h"

#include "qkloader.h"
#include "qkutils.h"

#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>

using namespace QkUtils;

QkLoaderGUI::QkLoaderGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QkLoaderGUI)
{
    ui->setupUi(this);
    ui->textLog->setFont(QFont("Courier New", 9));

    serialPort = new QSerialPort(this);

    QkUtils::setInfoPath(qApp->applicationDirPath() + "/resources/info");
    targetsMap = supportedTargets();

    ui->comboTargetName->clear();
    foreach(QString targetName, targetsMap.keys())
        ui->comboTargetName->addItem(targetName);

//    setTarget(targetsMap["EFM32"][0]);

    readSettings();
    slotReloadSerialPorts();

    connect(ui->buttonReload, SIGNAL(clicked()), this, SLOT(slotReloadSerialPorts()));
    connect(ui->buttonBrowse, SIGNAL(clicked()), this, SLOT(slotBrowse()));
    connect(ui->buttonUpload, SIGNAL(clicked()), this, SLOT(slotUpload()));
    connect(ui->comboTargetName, SIGNAL(currentIndexChanged(int)), this, SLOT(updateInterface()));
    connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(slotConnect()));
    connect(ui->lineASCII, SIGNAL(returnPressed()), this, SLOT(slotSendASCII()));

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(slotDataReady()));

    updateInterface();
}

QkLoaderGUI::~QkLoaderGUI()
{
    delete ui;
}

void QkLoaderGUI::readSettings()
{
    int i, size;
    QSettings settings;

    ui->lineFile->setText(settings.value("lastBinaryFile").toString());
}

void QkLoaderGUI::log(const QString &text)
{
    ui->textLog->appendPlainText(text);
}

void QkLoaderGUI::slotDataReady()
{
    while(serialPort->bytesAvailable() > 0)
        log(QString(serialPort->readAll()));
}

void QkLoaderGUI::slotReloadSerialPorts()
{
    QStringList list;
    foreach(QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        QString portName = info.portName();
        if(portName.contains("ACM") || portName.contains("USB"))
            list.append(portName);
    }
    ui->comboPort->clear();
    ui->comboPort->addItems(list);
}

void QkLoaderGUI::slotBrowse()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select a binary file"), QString(), "*.bin");
    ui->lineFile->setText(filePath);

    QSettings settings;
    settings.setValue("lastBinaryFile", QVariant(filePath));
}

void QkLoaderGUI::slotConnect()
{
    QString filePath = ui->lineFile->text();
    QSerialPort *sp = serialPort;

    if(!sp->isOpen())
    {
        sp->setPortName(ui->comboPort->currentText());
        if(sp->open(QSerialPort::ReadWrite))
        {
            sp->setBaudRate(115200);
            sp->setDataBits(QSerialPort::Data8);
            sp->setParity(QSerialPort::NoParity);
            sp->setStopBits(QSerialPort::OneStop);
            sp->setFlowControl(QSerialPort::NoFlowControl);

            log(tr("Connected"));
            ui->buttonConnect->setText(tr("Disconnect"));
        }
        else
        {
            QString errMsg = tr("Failed to open port. ") + sp->errorString();
            log(errMsg);
            return;
        }
    }
    else
    {
        sp->close();
        log(tr("Disconnected"));
        ui->buttonConnect->setText(tr("Connect"));
    }
}

void QkLoaderGUI::slotSendASCII()
{
    serialPort->write(ui->lineASCII->text().toUtf8());
    ui->lineASCII->clear();
}

void QkLoaderGUI::slotUpload()
{   
    QString targetName = ui->comboTargetName->currentText();

    log(tr("Uploading..."));

    disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(slotDataReady()));

    QkLoaderEFM32 efm32_loader(serialPort, this);
    connect(&efm32_loader, SIGNAL(output(QString)), this, SLOT(log(QString)));
    efm32_loader.upload(ui->lineFile->text());

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(slotDataReady()));
}

void QkLoaderGUI::updateInterface()
{
    QString targetName = ui->comboTargetName->currentText();
    Target target = targetsMap.value(targetName);

    ui->comboTargetVariant->clear();    
    foreach(Target::Variant variant, target.variants)
        ui->comboTargetVariant->addItem(variant.name);
}

void QkLoaderGUI::setTarget(const Target &target)
{
    ui->comboTargetName->setCurrentText(target.name);
}
