#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtSql>

#include "action.h"

#include "client.h"
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
        Client *client = new Client(nullptr);
        QString respuesta;
        QFile reply("respuesta.xml");
        if (!reply.open(QIODevice::WriteOnly)) {
            qDebug() << "No puedo escribir la respuesta";
            action->getReply(&respuesta, client);
            qDebug() << respuesta;
        } else {
            QTextStream out(&reply);
            action->getReply(&respuesta, client);
            out << respuesta;
            reply.close();
            qDebug() << "Se ha escrito la respuesta en un archivo";
        }
    }/*
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setDatabaseName("ServicioTecnicoMoviles");
    db.setUserName("usuario");
    db.setPassword("usuario");
    if (db.open()) {
        qDebug() << "Bien";
    } else {
        qDebug() << "Mierda";
    }*/

    return a.exec();
}
