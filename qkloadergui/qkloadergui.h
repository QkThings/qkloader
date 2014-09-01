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
