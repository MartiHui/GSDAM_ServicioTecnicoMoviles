#include <QXmlStreamWriter>
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
        if (schema.load(schemaText.toUtf8())) {
            if (schema.isValid()) {
                QXmlSchemaValidator validator(schema);
                if (validator.validate(m_messageXml.toUtf8())) {
                    valid = true;
                }
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
    } else if (action == "ListaOrdenesReply") {
        type = ActionType::LISTA_ORDENES_REPLY;
    } else if (action == "ListaStatusReply") {
        type = ActionType::LISTA_STATUS_REPLY;
    } else if (action == "NewOrderRequest") {
        type = ActionType::NEW_ORDER_REQUEST;
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

QVector<QPair<int, QString> > Action::getListaOrdenes() {
    QVector<QPair<int, QString> > ordenes;

    readUntilElement("ordenes");
    while (m_xmlReader->readNextStartElement()) {
        QPair<int, QString> orden;

        orden.first = m_xmlReader->attributes().value("id").toInt();
        orden.second = m_xmlReader->readElementText();

        ordenes.push_back(orden);
    }

    return ordenes;
}

QVector<QPair<int, QString> > Action::getListaStatus() {
    QVector<QPair<int, QString> > statuses;

    readUntilElement("statuses");
    while (m_xmlReader->readNextStartElement()) {
        QPair<int, QString> status;

        status.first = m_xmlReader->attributes().value("id").toInt();
        status.second = m_xmlReader->readElementText();

        statuses.push_back(status);
    }

    return statuses;
}

QPair<int, QString> Action::getNewOrderRequest() {
    QPair<int, QString> order;

    readUntilElement("order_id");
    order.first = QString::number(m_xmlReader->readElementText());

    readUntilElement("status");
    order.second = m_xmlReader->readElementText();

    return order;
}

QString Action::askListaOrdenes() {
    return getXmlTemplate("ListaOrdenesAsk");
}

QString Action::askListaStatus() {
    return getXmlTemplate("ListaStatusAsk");
}

QString Action::changeOrderStatus(int orderId, int statusId) {
    return QString(getXmlTemplate("ChangeOrderStatusAsk")).arg(QString::number(orderId)).arg(QString::number(statusId));
}
/*
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

QPair<int, QString> Action::getOrdenRequestInfo() {
    QPair<int, QString> orden;

    readUntilElement("orden");
    orden.first = m_xmlReader->attributes().value("id").toInt();
    orden.second = m_xmlReader->readElementText();

    return orden;
}
*/
QString Action::establishConnection(QString user, QString password) {
    return getXmlTemplate("EstablishConnectionAsk").arg("TECNICO").arg(user).arg(password);
}
/*
QString Action::askListaOrdenes() {
    return getXmlTemplate("ListaOrdenesAsk");
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

QString Action::askOrdenRequest(int modeloId, const QVector<int> &reparacionesId) {
    QString xml = getXmlTemplate("OrdenRequestAsk");

    QString reparacionesXml{""};
    for (auto id : reparacionesId) {
        reparacionesXml += QString("<reparacion_id>%1</reparacion_id>").arg(QString::number(id));
    }

    return QString(xml).arg(QString::number(modeloId)).arg(reparacionesXml);
}*/
