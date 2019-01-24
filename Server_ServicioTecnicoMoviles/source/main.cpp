#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "action.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile file("../XML/ReparacionInfoAsk.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error";
    } else {
        QTextStream in(&file);
        QString xml = in.readAll();
        file.close();

        Action *action = new Action(&xml);
        qDebug() << action->getReply();
    }
    return a.exec();
}
