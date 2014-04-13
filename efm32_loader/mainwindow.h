#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class EFM32Loader;

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
    void log(const QString &text);
    void updateInterface();

private:
    Ui::MainWindow *ui;

    EFM32Loader *loader;
    bool m_connected;

    void readSettings();
};

#endif // MAINWINDOW_H
