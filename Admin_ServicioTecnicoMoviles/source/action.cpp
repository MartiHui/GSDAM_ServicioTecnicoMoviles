#include <QString>
#include <QXmlStreamReader>
#include <QDebug>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QFile>

#include "action.h"

Action::Action(const QString &message) : m_messageXml{message} {
    m_xmlReader = new QXmlStreamReader(m_messageXml);
    setActionInfo();
}

Action::~Action() {
    delete m_xmlReader;
}

bool Action::isXmlValid(QString filename) {
    bool valid = false;

    QFile schemaFile("./XML/" + filename + ".xsd");
    if (!schemaFile.open(QIODevice::ReadOnly)) {
        qDebug() << "No se puede abrir el schema " + filename;
    } else {
        QString schemaText(schemaFile.readAll());
        schemaFile.close();

        QXmlSchema schema;
        if (schema.load(schemaText.toUtf8()) && schema.isValid()) {
            QXmlSchemaValidator validator(schema);
            if (validator.validate(m_messageXml.toUtf8())) {
                valid = true;
            } else {
                qDebug() << "El XML " + filename + " es incorrecto.";
            }
        } else {
            qDebug() << "Problemas al cargar el xsd " + filename;
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

bool Action::readUntilElement(QString tagName) {
    while (!m_xmlReader->isEndDocument()) {
        m_xmlReader->readNext();
        if (m_xmlReader->isStartElement() && m_xmlReader->name() == tagName) {
            return true;
        }
    }

    return false; // Has llegado hasta el final del documento sin encontrar el elemento deseado
}

ActionType Action::getActionType() const {
    return m_actionType;
}

bool Action::getRequestSuccess() const {
    return m_isRequestSuccess;
}

void Action::setActionInfo() {
    readUntilElement("action");

    m_isRequestSuccess = m_xmlReader->attributes().value("result").toString() == "SUCCESS";

    QString action = m_xmlReader->readElementText();
    ActionType type;
    if (action == "Error") {
        type = ActionType::ERROR;
    } else if (action == "EstablishConnectionReply") {
        type = ActionType::ESTABLISH_CONNECTION;
    } else if (action == "MarcasInfoReply") {
        type = ActionType::MARCAS_INFO_REPLY;
    } else if (action == "ModelosInfoReply") {
        type = ActionType::MODELOS_INFO_REPLY;
    } else if (action == "ReparacionInfoReply") {
        type = ActionType::REPARACION_INFO_REPLY;
    } else if (action == "TiendasInfoReply") {
        type = ActionType::TIENDAS_INFO_REPLY;
    } else if (action == "ModifyTiendaReply") {
        type = ActionType::MODIFY_TIENDA_REPLY;
    }

    if (!isXmlValid(action)) {
        type = ActionType::ERROR;
    }

    m_actionType = type;
}

QString Action::getErrorMessage() {
    QString msg{"Ha habido un problema con la respuesta recibida"};

    if (readUntilElement("message")) {
        msg = m_xmlReader->readElementText();
    }

    return msg;
}

QString Action::getNombreCliente() {
    readUntilElement("reply");
    return m_xmlReader->readElementText();
}

QVector<QPair<int, QString>> Action::getMarcasInfo() {
    QVector<QPair<int, QString> > marcas;

    readUntilElement("marcas");
    while (m_xmlReader->readNextStartElement()) {
        QPair<int, QString> marca;

        marca.first = m_xmlReader->attributes().value("id").toInt();
        marca.second = m_xmlReader->readElementText();

        marcas.push_back(marca);
    }

    return marcas;
}

QVector<QPair<int, QString> > Action::getModelosInfo() {
    QVector<QPair<int, QString> > modelos;

    readUntilElement("modelos");
    while (m_xmlReader->readNextStartElement()) {
        QPair<int, QString> modelo;

        modelo.first = m_xmlReader->attributes().value("id").toInt();
        modelo.second = m_xmlReader->readElementText();

        modelos.push_back(modelo);
    }

    return modelos;
}

QVector<QPair<int, QString> > Action::getReparacionesInfo() {
    QVector<QPair<int, QString> > reparaciones;

    readUntilElement("reparaciones");
    while (m_xmlReader->readNextStartElement()) {
        QPair<int, QString> reparacion;

        reparacion.first = m_xmlReader->attributes().value("id").toInt();
        reparacion.second = m_xmlReader->readElementText();

        reparaciones.push_back(reparacion);
    }

    return reparaciones;
}

QVector<Tienda> Action::getTiendasInfo() {
    QVector<Tienda> tiendas;

    readUntilElement("tiendas");
    while (m_xmlReader->readNextStartElement()) {
        Tienda tienda;

        readUntilElement("tienda_id");
        tienda.id = m_xmlReader->readElementText().toInt();

        readUntilElement("tienda_nombre");
        tienda.nombre = m_xmlReader->readElementText();

        readUntilElement("tienda_user");
        tienda.user = m_xmlReader->readElementText();

        readUntilElement("tienda_password");
        tienda.password = m_xmlReader->readElementText();

        readUntilElement("tienda_direccion");
        tienda.direccion = m_xmlReader->readElementText();

        tiendas.push_back(tienda);
    }

    return tiendas;
}

QString Action::establishConnection(QString user, QString password) {
    return getXmlTemplate("EstablishConnectionAsk").arg("ADMIN").arg(user).arg(password);
}

QString Action::askMarcasInfo() {
    return getXmlTemplate("MarcasInfoAsk");
}

QString Action::askModelosInfo(int marcaId) {
    return getXmlTemplate("ModelosInfoAsk").arg(QString::number(marcaId));
}

QString Action::askReparacionInfo(int modeloId) {
    return getXmlTemplate("ReparacionInfoAsk").arg(QString::number(modeloId));
}

QString Action::askTiendasInfo() {
    return getXmlTemplate("TiendasInfoAsk");
}
