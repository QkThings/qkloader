#include "clhandler.h"
#include <iostream>

void CLHandler::run()
{
    connect(&loader, SIGNAL(output(QString)), this, SLOT(log(QString)));

    std::cout << "> Connecting to port " << portName.toStdString();
    if(loader.open(portName))
       loader.upload(filePath);

    std::cout << std::endl;
    emit done();
}

void CLHandler::log(const QString &message)
{
    static bool firstProgress = true;
    if(message.contains("/"))
    {
        if(firstProgress)
        {
            std::cout << std::endl;
            firstProgress = false;
        }
        std::cout << message.toStdString() << "\r";
    }
    else
        std::cout << "\n> " << message.toStdString();
}
