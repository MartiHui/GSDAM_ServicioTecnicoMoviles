#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "action.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("../XML/__Pruebas.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No encuentro el archivo";
    } else {
        QTextStream in(&file);
        QString xml = in.readAll();
        file.close();

        Action *action = new Action(&xml);
        QFile reply("respuesta.xml");
        if (!reply.open(QIODevice::WriteOnly)) {
            qDebug() << "No puedo escribir la respuesta";
            qDebug() << action->getReply();
        } else {
            QTextStream out(&reply);
            out << action->getReply();
            reply.close();
            qDebug() << "Se ha escrito la respuesta en un archivo";
        }
    }

    return a.exec();
}
