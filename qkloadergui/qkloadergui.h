#ifndef QKLOADERGUI_H
#define QKLOADERGUI_H

#include <QMainWindow>
#include "qkutils.h"

using namespace QkUtils;

namespace Ui {
class QkLoaderGUI;
}

class QkLoader;
class QSerialPort;

class QkLoaderGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit QkLoaderGUI(QWidget *parent = 0);
    ~QkLoaderGUI();

private slots:
    void slotReloadSerialPorts();
    void slotBrowse();
    void slotUpload();
    void slotConnect();
    void slotSendASCII();
    void slotDataReady();
    void log(const QString &text);
    void updateInterface();

private:
    Ui::QkLoaderGUI *ui;
    QkLoader *loader;

    QSerialPort *serialPort;

    QMap<QString, Target> targetsMap;

    void setTarget(const Target &target);
    void readSettings();
};

#endif // QKLOADERGUI_H
