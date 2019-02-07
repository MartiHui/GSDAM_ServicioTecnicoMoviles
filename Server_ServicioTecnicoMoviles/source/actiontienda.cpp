#include "actiontienda.h"

ActionTienda::ActionTienda(const QString &message) : Action(message) {
    setActionType();
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

QString ActionTienda::getReply() {
    if (!isXmlValid() || m_actionType == ActionTiendaType::INVALID) {
        return Action::generateErrorXml(m_callbackId, "XML no válido");
    }

    QString reply;
    switch (m_actionType) {
    case ActionTiendaType::LISTA_ORDENES_ASK:

        break;

    case ActionTiendaType::MARCAS_INFO_ASK:

        break;

    case ActionTiendaType::MODELOS_INFO_ASK:

        break;

    case ActionTiendaType::REPARACION_INFO_ASK:

        break;

    case ActionTiendaType::ORDEN_REQUEST_ASK:

        break;
    }

    return reply;
}
