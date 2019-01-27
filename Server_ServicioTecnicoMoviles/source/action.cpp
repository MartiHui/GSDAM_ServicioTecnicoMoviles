#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QVector>
#include <QPair>

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

void Action::getReply(QString *reply, Client *client) {
    switch (m_actionType) {
    case ActionType::INVALID:
        //reply = QString("INVALID");
        error(reply, QString("Ha habido un error con tu solicitud."));
        break;

    case ActionType::ESTABLISH_CONNECTION:
        establishConnection(reply, client);

    case ActionType::LISTA_ORDENES_ASK:
        //reply = QString("LISTA_ORDENES_ASK");
        listaOrdenes(reply, client);
        break;

    case ActionType::MARCAS_INFO_ASK:
        //reply = QString("MARCAS_INFO_ASK");
        marcasInfo(reply);
        break;

    case ActionType::MODELOS_INFO_ASK:
        //reply = QString("MODELOS_INFO_ASK");
        modelosInfo(reply);
        break;

    case ActionType::REPARACION_INFO_ASK:
        //reply = QString("REPARACION_INFO_ASK");
        reparacionInfo(reply);
        break;

    case ActionType::ORDEN_REQUEST_ASK:
        //reply = QString("ORDEN_REQUEST_ASK");
        ordenRequest(reply);
        break;

    case ActionType::ORDEN_STATUS_ASK:
        //reply = QString("ORDEN_STATUS_ASK");
        ordenStatus(reply);
        break;
    }
}

bool Action::isXmlValid(const char *archivoXML) {
    return true;
}

void Action::error(QString *reply, QString message) {
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

void Action::establishConnection(QString *reply, Client *client) {
    QString nombreTienda = getTextElement(QString("tienda"));

    int id = DBController::getInstance()->tiendaInDb(nombreTienda);
    if (id) {
        client->validate(id);

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
        error(reply, QString("Tu tienda no está en nuestra base de datos"));
    }
}

void Action::listaOrdenes(QString *reply, Client *client) {

}

void Action::marcasInfo(QString *reply) {
    QVector<QPair<int, QString> > marcas;
    DBController::getInstance()->getMarcas(&marcas);

    QXmlStreamWriter writer(reply);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"MarcasInfoReply.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MARCAS_INFO_REPLY");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeStartElement("marcas");
    for (int i = 0; i < marcas.count(); i++) {
        writer.writeStartElement("marca");
        writer.writeAttribute("id", QString::number(marcas.at(i).first));
        writer.writeCharacters(marcas.at(i).second);
        writer.writeEndElement();
    }
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::modelosInfo(QString *reply) {
    int marcaId = getTextElement("marca_id").toInt();
    QVector<QPair<int, QString> > modelos;
    DBController::getInstance()->getModelos(marcaId, &modelos);

    QXmlStreamWriter writer(reply);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"ModelosInfoReply.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MODELOS_INFO_REPLY");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("marca_id", QString::number(marcaId));
    writer.writeStartElement("modelos");qDebug() << modelos.count();
    for (int i = 0; i < modelos.count(); i++) {
        writer.writeStartElement("modelo");
        writer.writeAttribute("id", QString::number(modelos.at(i).first));
        writer.writeCharacters(modelos.at(i).second);
        writer.writeEndElement();
    }
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::reparacionInfo(QString *reply) {

}

void Action::ordenRequest(QString *reply) {

}

void Action::ordenStatus(QString *reply) {

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
