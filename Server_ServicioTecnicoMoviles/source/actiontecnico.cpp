#include "actiontecnico.h"
#include "dbcontroller.h"

ActionTecnico::ActionTecnico(const QString &message) : Action(message) {
    setActionType();
    m_validXml = isXmlValid();
}

void ActionTecnico::setActionType() {
    if (m_requestType == "ListaOrdenesAsk") {
        m_actionType = ActionTecnicoType::LISTA_ORDENES_ASK;
    } else if (m_requestType == "ListaStatusAsk") {
        m_actionType = ActionTecnicoType::LISTA_STATUS_ASK;
    } else if (m_requestType == "ChangeOrderStatusAsk") {
        m_actionType = ActionTecnicoType::CHANGE_ORDER_STATUS_ASK;
    } else {
        m_actionType = ActionTecnicoType::INVALID;
    }
}

QString ActionTecnico::getReply() {
    QString reply{""};

    switch (m_actionType) {
    case ActionTecnicoType::LISTA_ORDENES_ASK:
        reply = getListaOrdenes(client);
        break;

    case ActionTecnicoType::LISTA_STATUS_ASK:
        reply = getListaStatus();
        break;

    case ActionTecnicoType::CHANGE_ORDER_STATUS_ASK:
        reply = "";
        changeOrderStatus();
        break;

    case ActionTecnicoType::INVALID:
        reply = Action::generateErrorXml("XML no válido");
        break;
    }

    return reply;
}

QString ActionTecnico::getListaOrdenes(const Client &client) {
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

QString ActionTecnico::getListaStatus() {
    QString xml = Action::getXmlTemplate("ListaStatusReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QVector<QPair<int, QString> > statuses;
    DBController::getInstance()->loadStatuses(statuses);

    QString statusXml{""};
    for (auto status : statuses) {
        statusXml += QString("<status id=\"%1\">%2</status>")
                .arg(QString::number(status.first)).arg(status.second);
    }

    return QString(xml).arg("SUCCESS").arg(statusXml);
}

void ActionTecnico::changeOrderStatus() {
    QPair<int, int> newOrderStatus;

    readUntilElement("order_id");
    newOrderStatus.first = m_xmlReader->readElementText().toInt();

    readUntilElement("status_id");
    newOrderStatus.second = m_xmlReader->readElementText().toInt();
}
