#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include "server.h"
#include "action.h"
#include "client.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Server *server = new Server(1234);

    QFile file("__Pruebas.xml");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString xmlAsk = in.readAll();
    file.close();

    Client *client = new Client(nullptr);
    client->validate(1);
    Action *action = new Action(&xmlAsk);
    QString xmlReply;
    action->getReply(&xmlReply, client);
    qDebug() << xmlReply;

    return a.exec();
}
