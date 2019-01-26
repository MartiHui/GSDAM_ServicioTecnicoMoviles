#include <QtSql>

#include "dbcontroller.h"

DBController *DBController::m_pInstance = NULL;

DBController* DBController::getInstance() {
    if (!m_pInstance) {
        m_pInstance = new DBController;
    }

    return m_pInstance;
}

void DBController::deleteInstance() {
    delete m_pInstance;
}

DBController::DBController() {
    database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("127.0.0.1");
    database.setPort(5432);
    database.setDatabaseName("ServicioTecnicoMoviles");
    database.setUserName("usuario");
    database.setPassword("usuario");
    database.open();
}

DBController::~DBController() {

}

bool DBController::tiendaInDb(QString nombreTienda) {
    QSqlQuery query;
    query.exec("SELECT * FROM tiendas WHERE \"nombre_tienda\" = \'" + nombreTienda + "\'");
    return query.next();
}
