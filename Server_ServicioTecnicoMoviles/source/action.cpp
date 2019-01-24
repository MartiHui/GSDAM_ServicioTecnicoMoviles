#include <QXmlStreamReader>
#include <QDebug>

#include "action.h"

Action::Action(const QString *message) {
    m_xmlReader = new QXmlStreamReader(*message);
    setActionType();
}

Action::~Action() {
    delete m_xmlReader;
}

ActionType Action::getActionType() {
    return m_actionType;
}

void Action::setActionType() {
    while (m_xmlReader->readNextStartElement()) {
        if (m_xmlReader->name() == "action") {
            QString action = m_xmlReader->readElementText();
            ActionType type;
            if (action == "ESTABLISH_CONNECTION") {
                type = ActionType::ESTABLISH_CONNECTION;
            } else if (action == "LISTA_ORDENES_ASK") {
                type = ActionType::LISTA_ORDENES_ASK;
            } else if (action == "MARCAS_INFO_ASK") {
                type = ActionType::MARCAS_INFO_ASK;
            } else if (action == "MODELOS_INFO_ASK") {
                type = ActionType::MODELOS_INFO_ASK;
            } else if (action == "REPARACION_INFO_ASK") {
                type = ActionType::REPARACION_INFO_ASK;
            } else if (action == "ORDEN_REQUEST_ASK") {
                type = ActionType::ORDEN_REQUEST_ASK;
            } else if (action == "ORDEN_STATUS_ASK") {
                type = ActionType::ORDEN_STATUS_ASK;
            } else {
                type = ActionType::INVALID;
            }
            m_actionType = type;
            break;
        }
    }
}

QString Action::getReply() {
    QString reply;

    switch (m_actionType) {
    case ActionType::INVALID:
        reply = QString("INVALID");
        break;

    case ActionType::ESTABLISH_CONNECTION:
        reply = QString("ESTABLISH_CONNECTION");
        break;

    case ActionType::LISTA_ORDENES_ASK:
        reply = QString("LISTA_ORDENES_ASK");
        break;

    case ActionType::MARCAS_INFO_ASK:
        reply = QString("MARCAS_INFO_ASK");
        break;

    case ActionType::MODELOS_INFO_ASK:
        reply = QString("MODELOS_INFO_ASK");
        break;

    case ActionType::REPARACION_INFO_ASK:
        reply = QString("REPARACION_INFO_ASK");
        break;

    case ActionType::ORDEN_REQUEST_ASK:
        reply = QString("ORDEN_REQUEST_ASK");
        break;

    case ActionType::ORDEN_STATUS_ASK:
        reply = QString("ORDEN_STATUS_ASK");
        break;
    }

    return reply;
}

bool Action::isXmlValid(const char *archivoXML) {

}
