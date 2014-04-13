#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QSettings>
#include <QDebug>
#include <QTimer>

#include "clhandler.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStyle *style = QStyleFactory::create("Fusion");
    a.setStyle(style);
    a.setOrganizationDomain("settings");
    a.setApplicationName("EFM32 Loader");

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, a.applicationDirPath());
    QSettings::setDefaultFormat(QSettings::IniFormat);

    CLHandler handler;
    MainWindow w;

    if(argc > 1)
    {
        if(argc != 3)
        {
            std::cout << "Wrong number of arguments." << std::endl;
            std::cout << "Usage: efm32_loader <port_name> <file_path>" << std::endl;
            exit(EXIT_FAILURE);
        }
        handler.portName = QString(argv[1]);
        handler.filePath = QString(argv[2]);
        QObject::connect(&handler, SIGNAL(done()), &a, SLOT(quit()));
        QTimer::singleShot(0, &handler, SLOT(run()));
    }
    else
    {
        w.show();
    }

    return a.exec();
}
