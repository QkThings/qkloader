#ifndef XMODEM_H
#define XMODEM_H

#include <QObject>

class QSerialPort;

class XMODEM : public QObject
{
    Q_OBJECT
public:
    explicit XMODEM(QSerialPort *sp, QObject *parent = 0);

signals:
    void output(QString message);

public slots:
    bool sendFile(const QString &filePath);


private:
    enum
    {
        SOH = 0x01,
        EOT = 0x04,
        ACK = 0x06,
        NAK = 0x15,
        ETB = 0x17,
        CAN = 0x18,
        C = 0x43
    };

    QSerialPort *m_serialPort;

    void sendPacket(char *data, int count);
    int calculateCRC(char *ptr, int count);
    int waitACK(int timeout);

    int m_packetNumber;

};

#endif // XMODEM_H
