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
    } else if (type == "ADMIN") {
        tipo = "admin";
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

    case ClientType::INVALID:
        return;
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

QPair<int, QString> DBController::updateOrderStatus(int orderId, int statusId) {
    QSqlQuery query;
    query.prepare("UPDATE ordenes SET estado_id = ? WHERE orden_id = ? ");
    query.bindValue(0, statusId);
    query.bindValue(1, orderId);
    query.exec();

    query.prepare("SELECT tienda_id, estado_nombre FROM estados JOIN ordenes ON estados.estado_id = ordenes.estado_id "
                  "WHERE orden_id = ?");
    query.bindValue(0, orderId);
    query.exec();

    QPair<int, QString> orderDetails;
    query.next();
    orderDetails.first = query.value(0).toInt();
    orderDetails.second = query.value(1).toString();

    return orderDetails;
}

int DBController::getOrderTecnico(int orderId) {
    QSqlQuery query;
    query.prepare("SELECT tecnico_id FROM ordenes WHERE orden_id = ?");
    query.bindValue(0, orderId);
    query.exec();

    query.next();
    return query.value(0).toInt();
}
