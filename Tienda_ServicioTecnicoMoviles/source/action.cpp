#include <QXmlStreamWriter>
#include <QString>
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
    ActionType type = ActionType::ERROR;
    while (m_xmlReader->readNextStartElement()) {
        if (m_xmlReader->name() == "action") {
            QString action = m_xmlReader->readElementText();
            if (action == "ERROR") {
                type = ActionType::ERROR;
            } else if (action == "ESTABLISH_CONNECTION") {
                type = ActionType::ESTABLISH_CONNECTION;
            } else if (action == "LISTA_ORDENES_REPLY") {
                type = ActionType::LISTA_ORDENES_REPLY;
            } else if (action == "MARCAS_INFO_REPLY") {
                type = ActionType::MARCAS_INFO_REPLY;
            } else if (action == "MODELOS_INFO_REPLY") {
                type = ActionType::MODELOS_INFO_REPLY;
            } else if (action == "REPARACION_INFO_REPLY") {
                type = ActionType::REPARACION_INFO_REPLY;
            } else if (action == "ORDEN_REQUEST_REPLY") {
                type = ActionType::ORDEN_REQUEST_REPLY;
            } else if (action == "ORDEN_STATUS_REPLY") {
                type = ActionType::ORDEN_STATUS_REPLY;
            }
            break;
        }
    }

    if (type != ActionType::ERROR && !isXmlValid("")) {
        type = ActionType::ERROR;
    }

    m_actionType = type;
}

bool Action::isXmlValid(const char *archivoXml) {
    return true;
}

QString Action::establishConnection(QString nombreTienda) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "EstablishConnection", "ESTABLISH_CONNECTION");

    writer.writeStartElement("body");
    writer.writeTextElement("tienda", nombreTienda);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askMarcasInfo() {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "MarcasInfoAsk", "MARCAS_INFO_ASK");

    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askModelosInfo(int marcaId) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "ModelosInfoAsk", "MODELOS_INFO_ASK");

    writer.writeStartElement("body");
    writer.writeTextElement("marca_id", QString::number(marcaId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askReparacionInfo(int modeloId) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "ReparacionInfoAsk", "REPARACION_INFO_ASK");

    writer.writeStartElement("body");
    writer.writeTextElement("modelo_id", QString::number(modeloId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::error(QString errorMessage) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "Error", "ERROR");

    writer.writeStartElement("body");
    writer.writeTextElement("message", errorMessage);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askOrdenStatus(QString ordenId) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "OrdenStatusAsk", "ORDEN_STATUS_ASK");

    writer.writeStartElement("body");
    writer.writeTextElement("order_id", ordenId);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askOrdenRequest(int modeloId, QVector<int> *reparacionesId) {
    QString message;
    QXmlStreamWriter writer(&message);
    writeXmlStart(writer, "OrdenRequestAsk", "ORDEN_REQUEST_ASK");

    writer.writeStartElement("body");
    writer.writeTextElement("modelo_id", QString::number(modeloId));
    writer.writeStartElement("reparaciones");
    for (auto reparacionId : *reparacionesId) {
        writer.writeTextElement("reparacion_id", QString::number(reparacionId));
    }
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::getElementText(QString tagName) {
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

QVector<QPair<QString, int> > Action::getMarcasInfo() {
    QVector<QPair<QString, int> > marcas;
    m_xmlReader->skipCurrentElement(); // salimos de <head>
    m_xmlReader->readNextStartElement(); // entramos en <body>
    m_xmlReader->readNextStartElement(); // entramos en <marcas>
    while (m_xmlReader->readNextStartElement()) { // leemos todos los elementos <marca>
        QPair<QString, int> marca;
        marca.second = m_xmlReader->attributes().value("id").toInt(); // Debe leerse primero el atributo, ya que readElementText adelanta el puntero
        marca.first = m_xmlReader->readElementText();
        marcas.push_back(marca);
    }
    return marcas;
}

QVector<QPair<QString, int> > Action::getModelosInfo() {
    QVector<QPair<QString, int> > modelos;
    m_xmlReader->skipCurrentElement(); // Salimos de <head>
    m_xmlReader->readNextStartElement(); // Entramos en <body>
    m_xmlReader->readNextStartElement(); // Entramose n marca_id
    // TODO encontrar que causa que lea dos veces marca_id
    m_xmlReader->readNextStartElement(); // Por alguna razon lee dos veces marca_id
    m_xmlReader->readNextStartElement(); // Entramos en <modelos>
    while (m_xmlReader->readNextStartElement()) { // recorremos todos los <modelo>
        QPair<QString, int> modelo;
        modelo.second = m_xmlReader->attributes().value("id").toInt();
        modelo.first = m_xmlReader->readElementText();
        modelos.push_back(modelo);
    }
    return modelos;
}

QVector<QPair<QString, int> > Action::getReparacionesInfo() {
    QVector<QPair<QString, int> > reparaciones;
    m_xmlReader->skipCurrentElement(); // Salimos de <head>
    m_xmlReader->readNextStartElement(); // Entramos en <body>
    m_xmlReader->readNextStartElement(); // Entramose n modelo_id
    // TODO encontrar que causa que lea dos veces modelo_id
    m_xmlReader->readNextStartElement(); // Por alguna razon lee dos veces modelo_id
    m_xmlReader->readNextStartElement(); // Entramos en <reparaciones>
    while (m_xmlReader->readNextStartElement()) { // recorremos todos los <reparacion>
        QPair<QString, int> reparacion;
        reparacion.second = m_xmlReader->attributes().value("id").toInt();
        m_xmlReader->readNextStartElement(); // pasamos al hijo <nombre>
        reparacion.first = m_xmlReader->readElementText();
        reparaciones.push_back(reparacion);
        m_xmlReader->skipCurrentElement(); // saltamos hasta el proximo <reparacion>
    }
    return reparaciones;
}

void Action::writeXmlStart(QXmlStreamWriter &writer, const QString &dtdName, const QString &action) {
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD(QString("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"" + dtdName + ".dtd\">"));

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", action);
    writer.writeEndElement(); // Cerrar etiqueta head
}
