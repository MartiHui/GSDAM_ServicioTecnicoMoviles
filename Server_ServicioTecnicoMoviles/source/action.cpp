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
        if (schema.load(schemaText.toUtf8()) && schema.isValid()) {
            QXmlSchemaValidator validator(schema);
            if (validator.validate(m_requestXml.toUtf8())) {
                valid = true;
            } else {
                qDebug() << "El XML " + m_requestType + " es incorrecto.";
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
