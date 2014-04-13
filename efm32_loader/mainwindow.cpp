#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "efm32loader.h"
#include <QSerialPortInfo>
#include <QFileDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textLog->setFont(QFont("Courier New", 9));

    loader = new EFM32Loader(this);
    m_connected = false;

    readSettings();
    slotReloadSerialPorts();

    connect(loader, SIGNAL(output(QString)), this, SLOT(log(QString)));
    connect(ui->buttonReload, SIGNAL(clicked()), this, SLOT(slotReloadSerialPorts()));
    connect(ui->buttonBrowse, SIGNAL(clicked()), this, SLOT(slotBrowse()));
    connect(ui->buttonUpload, SIGNAL(clicked()), this, SLOT(slotUpload()));
    connect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(slotConnect()));

    setWindowTitle("EFM32 Loader");
    updateInterface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readSettings()
{
    int i, size;
    QSettings settings;

    ui->lineFile->setText(settings.value("lastBinaryFile").toString());
}

void MainWindow::log(const QString &text)
{
    ui->textLog->appendPlainText(text);
}

void MainWindow::slotReloadSerialPorts()
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
    updateInterface();
}

void MainWindow::slotBrowse()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select a binary file"), QString(), "*.bin");
    ui->lineFile->setText(filePath);

    QSettings settings;
    settings.setValue("lastBinaryFile", QVariant(filePath));
}

void MainWindow::slotConnect()
{
    if(!m_connected)
    {
        m_connected = loader->open(ui->comboPort->currentText());
    }
    else
    {
        loader->close();
        m_connected = false;
    }
    updateInterface();
}

void MainWindow::slotUpload()
{
    loader->upload(ui->lineFile->text());
}

void MainWindow::updateInterface()
{
    ui->buttonConnect->setDisabled(ui->comboPort->count() == 0);
    ui->buttonUpload->setEnabled(m_connected);

    if(m_connected)
        ui->buttonConnect->setText(tr("Disconnect"));
    else
        ui->buttonConnect->setText(tr("Connect"));

    ui->comboPort->setEnabled(!m_connected);
}
