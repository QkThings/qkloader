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
