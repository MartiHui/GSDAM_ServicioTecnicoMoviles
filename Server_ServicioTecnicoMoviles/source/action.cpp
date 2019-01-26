#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>

#include "action.h"
#include "dbcontroller.h"
#include "client.h"

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
    ActionType type = ActionType::INVALID;
    while (m_xmlReader->readNextStartElement()) {
        if (m_xmlReader->name() == "action") {
            QString action = m_xmlReader->readElementText();
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
            break;
        }
    }

    if (type != ActionType::INVALID && !isXmlValid("")) {
        type = ActionType::INVALID;
    }

    m_actionType = type;
}

QString Action::getReply() {
    QString reply;

    switch (m_actionType) {
    case ActionType::INVALID:
        //reply = QString("INVALID");
        Error(&reply, QString("Ha habido un error con tu solicitud."));
        break;

    case ActionType::LISTA_ORDENES_ASK:
        //reply = QString("LISTA_ORDENES_ASK");
        ListaOrdenes(&reply);
        break;

    case ActionType::MARCAS_INFO_ASK:
        //reply = QString("MARCAS_INFO_ASK");
        MarcasInfo(&reply);
        break;

    case ActionType::MODELOS_INFO_ASK:
        //reply = QString("MODELOS_INFO_ASK");
        ModelosInfo(&reply);
        break;

    case ActionType::REPARACION_INFO_ASK:
        //reply = QString("REPARACION_INFO_ASK");
        break;

    case ActionType::ORDEN_REQUEST_ASK:
        //reply = QString("ORDEN_REQUEST_ASK");
        OrdenRequest(&reply);
        break;

    case ActionType::ORDEN_STATUS_ASK:
        //reply = QString("ORDEN_STATUS_ASK");
        OrdenStatus(&reply);
        break;
    }

    return reply;
}

bool Action::isXmlValid(const char *archivoXML) {
    return true;
}

void Action::Error(QString *reply, QString message) {
    QXmlStreamWriter writer(reply);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD(QString(DTD_DECLARATION).arg("Error.dtd"));

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "ERROR");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("message", message);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::EstablishConnection(QString *reply, Client *client) {
    QString nombreTienda = getTextElement(QString("tienda"));

    if (DBController::getInstance()->tiendaInDb(nombreTienda)) {
        client->validate();

        QXmlStreamWriter writer(reply);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"EstablishConnection.dtd\">");

        writer.writeStartElement("ServicioTecnicoMoviles");

        writer.writeStartElement("head");
        writer.writeTextElement("action", "ESTABLISH_CONNECTION");
        writer.writeEndElement(); // Cerrar etiqueta head

        writer.writeStartElement("body");
        writer.writeTextElement("tienda", "Conectado con la base de datos.");
        writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
    } else {
        Error(reply, QString("Tu tienda no está en nuestra base de datos"));
    }
}

void Action::ListaOrdenes(QString *reply) {

}

void Action::MarcasInfo(QString *reply) {

}

void Action::ModelosInfo(QString *reply) {

}

void Action::ReparacionInfo(QString *reply) {

}

void Action::OrdenRequest(QString *reply) {

}

void Action::OrdenStatus(QString *reply) {

}

QString Action::clientNotValidated() {

}

QString Action::getTextElement(QString tagName) {
    QString value{""};
    m_xmlReader->skipCurrentElement();
    while (m_xmlReader->readNextStartElement()) {
        if (m_xmlReader->name() == tagName) {
            value = m_xmlReader->readElementText();
            break;
        }
    }

    return value;
}
