#ifndef CLHANDLER_H
#define CLHANDLER_H

#include <QObject>
#include "efm32loader.h"

class CLHandler : public QObject
{
    Q_OBJECT
public:
    QString portName;
    QString filePath;

public slots:
    void run();

private slots:
    void log(const QString &message);

signals:
    void done();

private:
    EFM32Loader loader;

};

#endif // CLHANDLER_H
