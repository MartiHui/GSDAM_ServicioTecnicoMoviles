#include <QXmlStreamWriter>
#include <QString>
#include <QXmlStreamReader>

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

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"EstablishConnection.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "ESTABLISH_CONNECTION");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("tienda", nombreTienda);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askMarcasInfo() {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"MarcasInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MARCAS_INFO_ASK");
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askModelosInfo(int marcaId) {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"ModelosInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "MODELOS_INFO_ASK");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("marca_id", QString::number(marcaId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::askReparacionInfo(int modeloId) {
    QString message;
    QXmlStreamWriter writer(&message);

    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"ReparacionInfoAsk.dtd\">");

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "REPARACION_INFO_ASK");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("modelo_id", QString::number(modeloId));
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final

    return message;
}

QString Action::error(QString errorMessage) {
    QString message;
    QXmlStreamWriter writer(&message);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD(QString("<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"Error.dtd\">"));

    writer.writeStartElement("ServicioTecnicoMoviles");

    writer.writeStartElement("head");
    writer.writeTextElement("action", "ERROR");
    writer.writeEndElement(); // Cerrar etiqueta head

    writer.writeStartElement("body");
    writer.writeTextElement("message", errorMessage);
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
    m_xmlReader->skipCurrentElement();
    m_xmlReader->readNextStartElement();
    while (m_xmlReader->readNextStartElement()) {
        QPair<QString, int> marca;
        marca.first = m_xmlReader->readElementText();
        marca.second = m_xmlReader->attributes().value("id").toInt();
        marcas.push_back(marca);
    }
    return marcas;
}

