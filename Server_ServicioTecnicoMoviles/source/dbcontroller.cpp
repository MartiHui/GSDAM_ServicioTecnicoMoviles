#include <QtSql>

#include "dbcontroller.h"

DBController DBController::getInstance() {
    if (s_singleton)
}

DBController::DBController() {
    *database = QSqlDatabase::addDatabase("QPSQL");
    database->setHostName("127.0.0.1");
    database->setPort(5432);
    database->setDatabaseName("ServicioTecnicoMoviles");
    database->setUserName("usuario");
    database->setPassword("usuario");
}
