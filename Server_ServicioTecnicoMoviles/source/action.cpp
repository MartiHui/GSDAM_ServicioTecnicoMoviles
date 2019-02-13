#include <QXmlStreamReader>
#include <QDebug>
#include <QVector>
#include <QPair>
#include <QTextStream>
#include <QFile>
#include <QUrl>
#include <QXmlSchema>
#include <QXmlSchemaValidator>

#include "action.h"
#include "dbcontroller.h"
#include "client.h"

Action::Action(const QString &message) :
        m_requestXml{message} {
    m_xmlReader = new QXmlStreamReader(m_requestXml);
    setRequestInfo();
}

Action::~Action() {
    delete m_xmlReader;
}

void Action::setRequestInfo() {
    readUntilElement("action");
    m_requestType = m_xmlReader->readElementText();
}

bool Action::readUntilElement(QString tagName) {
    while (!m_xmlReader->isEndDocument()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement() && m_xmlReader->name() == tagName) {
            return true;
        }
    }

    return false; // Has llegado hasta el final del documento sin encontrar el elemento deseado
}

bool Action::isXmlValid() {
    bool valid = false;

    QFile schemaFile("./XML/" + m_requestType + ".xsd");
    if (!schemaFile.open(QIODevice::ReadOnly)) {
        qDebug() << "No se puede abrir el schema " + m_requestType;
    } else {
        QString schemaText(schemaFile.readAll());
        schemaFile.close();

        QXmlSchema schema;
        if (schema.load(schemaText.toUtf8())) {
            if (schema.isValid()) {
                QXmlSchemaValidator validator(schema);
                if (validator.validate(m_requestXml.toUtf8())) {
                    valid = true;
                }
            }
        } else {
            qDebug() << "Problemas al cargar el xsd " + m_requestType;
        }
    }

    return valid;
}

QString Action::getXmlTemplate(QString filename) {
    QString xmlTemplate{""};

    QFile file("./XML/" + filename + ".xml");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);
        xmlTemplate = in.readAll();
        file.close();
    } else {
        qDebug() << "No se ha encontrado la plantilla XML " + filename + ".xml";
    }

    return xmlTemplate;
}

QString Action::generateErrorXml(QString errorMessage) {
    return QString(Action::getXmlTemplate("Error")).arg(errorMessage);
}

QString Action::establishConnection(Client &client) {
    QString reply{""};
    QString xmlTemplate = Action::getXmlTemplate("EstablishConnectionReply");

    if (isXmlValid()) {
        readUntilElement("info");
        QString tipo = m_xmlReader->attributes().value("type").toString();

        readUntilElement("user");
        QString user = m_xmlReader->readElementText();

        readUntilElement("password");
        QString password = m_xmlReader->readElementText();

        QPair<int, QString> result;
        if (DBController::getInstance()->clientInDatabase(tipo, user, password, &result)) {
            client.identify(result.first, tipo);
            reply = QString(xmlTemplate).arg("SUCCESS").arg(result.second);
        } else {
            reply = QString(xmlTemplate).arg("FAILURE").arg("ERROR");
        }
    } else {
        reply = QString(xmlTemplate).arg("FAILURE").arg("ERROR");
    }

    return reply;
}

bool Action::isConnectionPetition() {
    return m_requestType == "EstablishConnectionAsk";
}


/*
ActionType Action::getActionType() {
    return m_actionType;
}

void Action::setActionType(const QString *message) {
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

    if (type != ActionType::INVALID && !isXmlValid(message->toStdString().c_str())) {
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
        break;

    case ActionType::LISTA_ORDENES_ASK:
        //reply = QString("LISTA_ORDENES_ASK");
        //listaOrdenes(reply, client);
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
        ordenRequest(reply, client);
        break;

    case ActionType::ORDEN_STATUS_ASK:
        //reply = QString("ORDEN_STATUS_ASK");
        ordenStatus(reply, client);
        break;
    }
}

bool Action::isXmlValid(const char *archivoXML) {
    return true;
    /*bool result = false;
    qDebug() << "validador";
    qDebug() << QString(archivoXML);

    /// Crea el contexto del analizador.
    xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
    if (ctxt == NULL)
    {
        qDebug() << "Error al crear el contexto del analizador.";
        return false;
    } // end if

    /// Analiza el archivo activando la opción de validación DTD.
    xmlDocPtr doc = xmlCtxtReadFile(ctxt, archivoXML, NULL, XML_PARSE_DTDLOAD);
    if (doc == NULL)
    {
        qDebug() << "Error al analizar el archivo.";
        return false;
    } // end if

    /// Comprueba la validez del XML.
    if (ctxt->valid == 0)
    {
        qDebug() << "El archivo XML no es valido.";
    } else {
        qDebug() << "El archivo XML es valido.";
        result = true;
    } // end if

    /// Libera memoria.
    xmlFreeDoc(doc);
    xmlFreeParserCtxt(ctxt);

    return result;
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

void Action::error(QString *reply, QString message) {
    QXmlStreamWriter writer(reply);
    writeXmlStart(writer, "Error", "ERROR");

    writer.writeStartElement("body");
    writer.writeTextElement("message", message);
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::establishConnection(QString *reply, Client *client) {
    QString nombreTienda = getTextElement(QString("tienda"));

    int id = DBController::getInstance()->tiendaInDb(nombreTienda);
    if (id) {
        client->identify(id); // Se marca el cliente como validado para que pueda hacer solicitudes

        QXmlStreamWriter writer(reply);
        writeXmlStart(writer, "EstablishConnection", "ESTABLISH_CONNECTION");

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
    writeXmlStart(writer, "MarcasInfoReply", "MARCAS_INFO_REPLY");

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
    writeXmlStart(writer, "ModelosInfoReply", "MODELOS_INFO_REPLY");

    writer.writeStartElement("body");
    writer.writeTextElement("marca_id", QString::number(marcaId));
    writer.writeStartElement("modelos");
    for (int i = 0; i < modelos.count(); i++) {
        writer.writeStartElement("modelo");
        writer.writeAttribute("id", QString::number(modelos.at(i).first));
        writer.writeCharacters(modelos.at(i).second);
        writer.writeEndElement();
    }
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::reparacionInfo(QString *reply) {
    int modeloId = getTextElement("modelo_id").toInt();
    QVector<Reparacion> reparaciones;
    DBController::getInstance()->getReparaciones(modeloId, &reparaciones);

    QXmlStreamWriter writer(reply);
    writeXmlStart(writer, "ReparacionInfoReply", "REPARACION_INFO_REPLY");

    writer.writeStartElement("body");
    writer.writeTextElement("modelo_id", QString::number(modeloId));
    writer.writeStartElement("reparaciones");
    for (int i = 0; i < reparaciones.count(); i++) {
        writer.writeStartElement("reparacion");
        writer.writeAttribute("id", QString::number(reparaciones.at(i).reparacionId));
        writer.writeTextElement("nombre", reparaciones.at(i).nombre);
        writer.writeTextElement("tiempo", QString::number(reparaciones.at(i).tiempoMinutos));
        writer.writeTextElement("coste", QString::number(reparaciones.at(i).precio));
        writer.writeEndElement();
    }
    writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
}

void Action::ordenRequest(QString *reply, Client *client) {
    Orden orden;
    orden.modeloId = getTextElement("modelo_id").toInt();
    orden.tiendaId = client->getClientId();
    m_xmlReader->readNextStartElement();
    while (m_xmlReader->readNextStartElement()) {
        orden.reparacionesId.push_back(m_xmlReader->readElementText().toInt());
    }

    DBController::getInstance()->insertOrden(&orden);
    if (orden.ordenId) {
        QXmlStreamWriter writer(reply);
        writeXmlStart(writer, "OrdenRequestReply", "ORDEN_REQUEST_REPLY");

        writer.writeStartElement("body");
        writer.writeTextElement("orden_id", QString::number(orden.ordenId));
        writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
    } else {
        error(reply, "Ha habido un error con tu solicitud");
    }
}

void Action::ordenStatus(QString *reply, Client *client) {
    QPair<int, QString> ordenStatus; // El prime valor devolvera el id de la tienda de la orden
    int ordenId = getTextElement("order_id").toInt();
    DBController::getInstance()->getOrdenStatus(ordenId, &ordenStatus);

    if (client->getClientId() == ordenStatus.first) {
        QXmlStreamWriter writer(reply);
        writeXmlStart(writer, "OrdenStatusReply", "ORDEN_STATUS_REPLY");

        writer.writeStartElement("body");
        writer.writeTextElement("respuesta", ordenStatus.second);
        writer.writeEndDocument(); // Se cierran todas las etiquetas hasta el final
    } else {
        error(reply, "No puedes acceder a este pedido.");
    }
}
*/

