#ifndef EFM32LOADER_H
#define EFM32LOADER_H

#include <QObject>

class QSerialPort;
class XMODEM;

class EFM32Loader : public QObject
{
    Q_OBJECT
public:
    explicit EFM32Loader(QObject *parent = 0);

    QSerialPort *serialPort() { return m_serialPort; }

signals:
    void output(QString);

public slots:
    bool open(const QString &portName);
    void close();
    bool upload(const QString &filePath);

private:
    QSerialPort *m_serialPort;
    XMODEM *m_xmodem;

    bool waitForChipID();
    bool waitForReady();
    bool waitForData(int timeout);

    void enterBoot();
    void exitBoot();
    void reset();
};

#endif // EFM32LOADER_H
