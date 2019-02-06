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
    m_pInstance = nullptr;
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

void DBController::getReparaciones(int modeloId, QVector<Action::Reparacion> *reparaciones) {
    QSqlQuery query;
    query.exec("SELECT id_modelo_reparacion, nombre_reparacion, tiempo_modelo_reparacion, "
               "coste_modelo_reparacion FROM modelo_reparacion INNER JOIN reparaciones "
               " ON reparaciones.id_reparacion = modelo_reparacion.id_reparacion "
               "WHERE \"id_modelo_telefono\" = \'" + QString::number(modeloId) + "\'");
    while (query.next()) {
        Action::Reparacion reparacion;
        reparacion.reparacionId = query.value(0).toInt();
        reparacion.nombre = query.value(1).toString();
        reparacion.tiempoMinutos = query.value(2).toInt();
        reparacion.precio = query.value(3).toFloat();
        reparaciones->push_back(reparacion);
    }
}

void DBController::insertOrden(Action::Orden *orden) {
    QSqlQuery query;
    query.exec("INSERT INTO ordenes(id_modelo_telefono, id_tienda) VALUES ("
               + QString::number(orden->modeloId) + ", " + QString::number(orden->tiendaId) + ")");
    int ordenId = 0;
    if (query.lastInsertId().isValid()) {
        ordenId = query.lastInsertId().toInt();
        orden->ordenId = ordenId;
        for (int idx = 0; idx < orden->reparacionesId.count(); idx++) {
            query.exec("INSERT INTO orden_detalles(id_orden, id_reparacion_modelo) "
                       "VALUES(" + QString::number(ordenId) + ", " +
                       QString::number(orden->reparacionesId.at(idx)) + ")");
        }
    }
}

void DBController::getOrdenStatus(int ordenId, QPair<int, QString> *ordenStatus) {
    QSqlQuery query;
    query.exec("SELECT id_tienda, nombre_estado FROM public.ordenes JOIN estado "
               "ON ordenes.id_estado = estado.id_estado WHERE id_orden = \'" +
               QString::number(ordenId) + "\'");

    if (query.next()) {
        ordenStatus->first = query.value(0).toInt();
        ordenStatus->second = query.value(1).toString();
    }
}
