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
    database.setDatabaseName("ServicioTecnicoMoviles_v2");
    database.setUserName("usuario");
    database.setPassword("usuario");
    database.open();
}

bool DBController::clientInDatabase(QString type, QString user, QString password, QPair<int, QString> *result) {
    QSqlQuery query;
    query.prepare(prepareClientInDatabaseQuery(type));
    query.bindValue(0, user);
    query.bindValue(1, password);
    query.exec();

    if (query.next()) {
        result->first = query.value(0).toInt();
        result->second = query.value(1).toString();
        return true;
    } else {
        return false;
    }
}

QString DBController::prepareClientInDatabaseQuery(const QString &type) {
    QString tipo{""};
    if (type == "TIENDA") {
        tipo = "tienda";
    } else if (type == "TECNICO") {
        tipo = "tecnico";
    }

    QString tabla = tipo + "s";
    QString id = tipo + "_id";
    QString nombre = tipo + "_nombre";
    QString user = tipo + "_user";
    QString password = tipo + "_password";
    QString activo = tipo + "_activo";

    return QString("SELECT %1, %2 FROM %3 WHERE %4 = :user AND %5 = :password AND %6 = TRUE").arg(id).arg(nombre).arg(tabla).arg(user).arg(password).arg(activo);
}

void DBController::loadListaOrdenes(const Client &client, QVector<QPair<int, QString> > &ordenes) {
    QString queryStr = "SELECT orden_id, estado_nombre FROM ordenes JOIN estados ON ordenes.estado_id = estados.estado_id "
                       "WHERE %1_id = ?";
    QString tipoCliente = "";
    switch (client.getClientType()) {
    case ClientType::TIENDA:
        tipoCliente = "tienda";
        break;

    case ClientType::TECNICO:
        tipoCliente = "tecnico";
        break;
    }

    QSqlQuery query;
    query.prepare(QString(queryStr).arg(tipoCliente));
    query.bindValue(0, client.getClientId());
    query.exec();

    while (query.next()) {
        QPair<int, QString> orden;
        orden.first = query.value(0).toInt();
        orden.second = query.value(1).toString();

        ordenes.push_back(orden);
    }
}

void DBController::loadMarcas(QVector<QPair<int, QString> > &marcas) {
    QSqlQuery query;
    query.prepare("SELECT marca_id, marca_nombre FROM marcas WHERE marca_activo = TRUE "); 
    query.exec();

    while (query.next()) {
        QPair<int, QString> marca;
        marca.first = query.value(0).toInt();
        marca.second = query.value(1).toString();

        marcas.push_back(marca);
    }
}

void DBController::loadModelos(QVector<QPair<int, QString> > &modelos, int marcaId) {
    QSqlQuery query;
    query.prepare("SELECT modelo_id, modelo_nombre FROM modelos WHERE marca_id = ? AND modelo_activo = TRUE ");
    query.bindValue(0, marcaId);
    query.exec();

    while (query.next()) {
        QPair<int, QString> modelo;
        modelo.first = query.value(0).toInt();
        modelo.second = query.value(1).toString();

        modelos.push_back(modelo);
    }
}

void DBController::loadReparaciones(QVector<QPair<int, QString> > &reparaciones, int modeloId) {
    QSqlQuery query;
    query.prepare("SELECT reparaciones.reparacion_id, reparacion_nombre FROM modelo_reparaciones JOIN reparaciones"
                  " ON reparaciones.reparacion_id = modelo_reparaciones.reparacion_id WHERE modelo_id = ? AND modelo_reparaciones_activo = TRUE ");
    query.bindValue(0, modeloId);
    query.exec();

    while (query.next()) {
        QPair<int, QString> reparacion;
        reparacion.first = query.value(0).toInt();
        reparacion.second = query.value(1).toString();

        reparaciones.push_back(reparacion);
    }
}

void DBController::loadStatuses(QVector<QPair<int, QString> > &statuses) {
    QSqlQuery query;
    query.prepare("SELECT estado_id, estado_nombre FROM estados WHERE estado_activo = TRUE ");
    query.exec();

    while (query.next()) {
        QPair<int, QString> status;
        status.first = query.value(0).toInt();
        status.second = query.value(1).toString();

        statuses.push_back(status);
    }
}

QPair<int, QString> DBController::insertNewOrden(int tiendaId, int modeloId, QVector<int> &reparacionesId) {
    QSqlQuery query;
    query.prepare("INSERT INTO ordenes(modelo_id, tienda_id) VALUES (?, ?)");
    query.bindValue(0, modeloId);
    query.bindValue(1, tiendaId);
    query.exec();

    QPair<int, QString> orden;
    if (query.lastInsertId().isValid()) {
        orden.first = query.lastInsertId().toInt();
        for (auto reparacion : reparacionesId) {
            query.prepare("INSERT INTO orden_detalles(orden_id, modelo_reparaciones_id) VALUES (?, ?)");
            query.bindValue(0, orden.first);
            query.bindValue(1, reparacion);
            query.exec();
        }

        query.exec("SELECT estado_nombre FROM estados JOIN ordenes ON estados.estado_id = ordenes.estado_id "
                      "WHERE orden_id = " + QString::number(orden.first));
        query.next();
        orden.second = query.value(0).toString();
    }

    return orden;
}

/*
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
}*/
