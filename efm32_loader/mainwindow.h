#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class EFM32Loader;
class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    Ui::MainWindow *ui;

    EFM32Loader *loader;
    QSerialPort *serialPort;
    bool m_connected;

    void readSettings();
};

#endif // MAINWINDOW_H
