#include <QtSql>
#include <QVector>
#include <QPair>

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

int DBController::tiendaInDb(QString nombreTienda) {
    QSqlQuery query;
    query.exec("SELECT * FROM tiendas WHERE \"nombre_tienda\" = \'" + nombreTienda + "\'");
    int id = 0;
    if (query.next()) {
        id = query.value(0).toInt();
    }
    return id;
}

void DBController::getMarcas(QVector<QPair<int, QString> > *marcas) {
    QSqlQuery query;
    query.exec("SELECT id_marca_telefono, nombre_marca_telefono FROM marcas_telefono");
    while (query.next()) {
        QPair<int, QString> marca;
        marca.first = query.value(0).toInt();
        marca.second = query.value(1).toString();
        marcas->push_back(marca);
    }
}

void DBController::getModelos(int marcaId, QVector<QPair<int, QString> > *modelos) {
    QSqlQuery query;
    query.exec("SELECT id_modelo_telefono, nombre_modelo_telefono FROM modelo_telefono "
               "WHERE \"id_marca_modelo_telefono\" = \'" + QString::number(marcaId) + "\'");
    while (query.next()) {
        QPair<int, QString> modelo;
        modelo.first = query.value(0).toInt();
        modelo.second = query.value(1).toString();
        modelos->push_back(modelo);
    }
}
