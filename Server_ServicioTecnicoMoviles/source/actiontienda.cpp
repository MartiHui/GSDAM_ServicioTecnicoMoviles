#include <QVector>
#include <QPair>
#include <QWebSocket>

#include "actiontienda.h"
#include "dbcontroller.h"
#include "server.h"
#include "actiontecnico.h"

ActionTienda::ActionTienda(const QString &message) : Action(message) {
    setActionType();
    m_validXml = isXmlValid();
}

void ActionTienda::setActionType() {
    if (m_requestType == "ListaOrdenesAsk") {
        m_actionType = ActionTiendaType::LISTA_ORDENES_ASK;
    } else if (m_requestType == "MarcasInfoAsk") {
        m_actionType = ActionTiendaType::MARCAS_INFO_ASK;
    } else if (m_requestType == "ModelosInfoAsk") {
        m_actionType = ActionTiendaType::MODELOS_INFO_ASK;
    } else if (m_requestType == "ReparacionInfoAsk") {
        m_actionType = ActionTiendaType::REPARACION_INFO_ASK;
    } else if (m_requestType == "OrdenRequestAsk") {
        m_actionType = ActionTiendaType::ORDEN_REQUEST_ASK;
    } else {
        m_actionType = ActionTiendaType::INVALID;
    }
}

QString ActionTienda::getReply(const Client &client) {
    QString reply{""};

    switch (m_actionType) {
    case ActionTiendaType::LISTA_ORDENES_ASK:
        reply = getListaOrdenes(client);
        break;

    case ActionTiendaType::MARCAS_INFO_ASK:
        reply = getMarcas();
        break;

    case ActionTiendaType::MODELOS_INFO_ASK:
        reply = getModelos();
        break;

    case ActionTiendaType::REPARACION_INFO_ASK:
        reply = getReparaciones();
        break;

    case ActionTiendaType::ORDEN_REQUEST_ASK:
        reply = newOrderRequest(client);
        break;

    case ActionTiendaType::INVALID:
        reply = Action::generateErrorXml("XML no válido");
        break;
    }

    return reply;
}

QString ActionTienda::getListaOrdenes(const Client &client) {
    QString xml = Action::getXmlTemplate("ListaOrdenesReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QVector<QPair<int, QString> > ordenes;
    DBController::getInstance()->loadListaOrdenes(client, ordenes);

    QString ordenesXml{""};
    for (auto orden : ordenes) {
        ordenesXml += QString("<orden id=\"%1\">%2</orden>")
                .arg(QString::number(orden.first)).arg(orden.second);
    }

    return QString(xml).arg("SUCCESS").arg(ordenesXml);
}

QString ActionTienda::getMarcas() {
    QString xml = Action::getXmlTemplate("MarcasInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QVector<QPair<int, QString> > marcas;
    DBController::getInstance()->loadMarcas(marcas);

    QString marcasXml{""};
    for (auto marca : marcas) {
        marcasXml += QString("<marca id=\"%1\">%2</marca>")
                .arg(QString::number(marca.first)).arg(marca.second);
    }

    return QString(xml).arg("SUCCESS").arg(marcasXml);
}

QString ActionTienda::getModelos() {
    QString xml = Action::getXmlTemplate("ModelosInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QString searchField = "marca_id";
    readUntilElement(searchField);
    QString marcaId = m_xmlReader->readElementText();


    QVector<QPair<int, QString> > modelos;
    DBController::getInstance()->loadModelos(modelos, marcaId.toInt());

    QString modelosXml{""};
    for (auto modelo : modelos) {
        modelosXml += QString("<modelo id=\"%1\">%2</modelo>")
                .arg(QString::number(modelo.first)).arg(modelo.second);
    }

    return QString(xml).arg("SUCCESS").arg(modelosXml);
}

QString ActionTienda::getReparaciones() {
    QString xml = Action::getXmlTemplate("ReparacionInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QString searchField = "modelo_id";
    readUntilElement(searchField);
    QString searchId = m_xmlReader->readElementText();


    QVector<QPair<int, QString> > reparaciones;
    DBController::getInstance()->loadReparaciones(reparaciones, searchId.toInt());

    QString reparacionesXml{""};
    for (auto reparacion : reparaciones) {
        reparacionesXml += QString("<reparacion id=\"%1\">%2</reparacion>")
                .arg(QString::number(reparacion.first)).arg(reparacion.second);
    }

    return QString(xml).arg("SUCCESS").arg(reparacionesXml);
}

QString ActionTienda::newOrderRequest(const Client &client) {
    auto orden = insertOrderDatabase(client);
    QString xml = Action::getXmlTemplate("OrdenRequestReply");

    if (orden.first == 0 || !m_validXml) {
        return QString(xml).arg("FAILURE").arg("0").arg("ERROR");
    } else {
        notifyTecnico(orden);
        return QString(xml).arg("SUCCESS").arg(QString::number(orden.first)).arg(orden.second);
    }
}

void ActionTienda::notifyTecnico(QPair<int, QString> order) {
    int tecnicoId = DBController::getInstance()->getOrderTecnico(order.first);
    auto tecnicoConnection = Server::getInstance()->searchClient(tecnicoId, ClientType::TECNICO);
    if (tecnicoConnection) {
        tecnicoConnection->getWebSocket()->sendTextMessage(ActionTecnico::newOrder(order.first, order.second));
    }

}

QPair<int, QString> ActionTienda::insertOrderDatabase(const Client &client) {
    int tiendaId = client.getClientId();

    readUntilElement("modelo_id");
    int modeloId = m_xmlReader->readElementText().toInt();

    QVector<int> reparacionesId;
    readUntilElement("reparaciones");
    while (m_xmlReader->readNextStartElement()) {
        if (m_xmlReader->name() == "reparacion_id") {
            reparacionesId.push_back(m_xmlReader->readElementText().toInt());
        }
    }

    return DBController::getInstance()->insertNewOrden(tiendaId, modeloId, reparacionesId);
}

QString ActionTienda::orderStatusChanged(int orderId, QString status) {
    return Action::getXmlTemplate("OrderStatusChanged").arg("SUCCESS").arg(QString::number(orderId)).arg(status);
}
