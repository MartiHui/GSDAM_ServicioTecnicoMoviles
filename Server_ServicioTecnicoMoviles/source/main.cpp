#include <QCoreApplication>

#include "server.h"
#include "dbcontroller.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //Server *server = new Server(1234);
    DBController::getInstance()->pruebas();

    return a.exec();
}
