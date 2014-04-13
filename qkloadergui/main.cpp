#include "qkloadergui.h"
#include <QApplication>
#include <QStyle>
#include <QStyleFactory>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStyle *style = QStyleFactory::create("Fusion");
    a.setStyle(style);
    a.setOrganizationDomain("qkthings");
    a.setApplicationName("qkloader");

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, a.applicationDirPath());
    QSettings::setDefaultFormat(QSettings::IniFormat);

    QkLoaderGUI w;
    w.show();

    return a.exec();
}
