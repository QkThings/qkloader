#ifndef QKLOADER_H
#define QKLOADER_H

#include "qkloader_global.h"

#include <QObject>
#include <QIODevice>

class XMODEM;

class QKLOADERSHARED_EXPORT QkLoader : public QObject
{
    Q_OBJECT
public:
    explicit QkLoader(QIODevice *device, QObject *parent = 0);

    void setCpuName(const QString &cpuName);

    virtual bool upload(const QString &filePath) = 0;

signals:
    void output(QString message);

protected:
    QString m_cpuName;
    QIODevice *m_device;

};


class QKLOADERSHARED_EXPORT QkLoaderEFM32 : public QkLoader
{
    Q_OBJECT
public:
    explicit QkLoaderEFM32(QIODevice *device, QObject *parent = 0);

    bool upload(const QString &filePath);

signals:

public slots:

private:
    XMODEM *m_xmodem;

};

#endif // QKLOADER_H
