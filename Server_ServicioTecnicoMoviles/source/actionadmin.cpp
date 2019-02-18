#include "actionadmin.h"
#include "dbcontroller.h"

ActionAdmin::ActionAdmin(const QString &message) : Action(message) {
    setActionType();
    m_validXml = isXmlValid();
}

void ActionAdmin::setActionType() {
    if (m_requestType == "MarcasInfoAsk") {
        m_actionType = ActionAdminType::MARCAS_INFO_ASK;
    } else if (m_requestType == "ModelosInfoAsk") {
        m_actionType = ActionAdminType::MODELOS_INFO_ASK;
    } else if (m_requestType == "ReparacionInfoAsk") {
        m_actionType = ActionAdminType::REPARACION_INFO_ASK;
    } else if (m_requestType == "TiendasInfoAsk") {
        m_actionType = ActionAdminType::TIENDAS_INFO_ASK;
    } else if (m_requestType == "ModifyTiendaAsk") {
        m_actionType = ActionAdminType::MODIFY_TIENDA_ASK;
    } else {
        m_actionType = ActionAdminType::INVALID;
    }
}

QString ActionAdmin::getReply(const Client &client) {
    QString reply{""};

    switch (m_actionType) {
    case ActionAdminType::MARCAS_INFO_ASK:
        reply = getMarcas();
        break;

    case ActionAdminType::MODELOS_INFO_ASK:
        reply = getModelos();
        break;

    case ActionAdminType::REPARACION_INFO_ASK:
        reply = getReparaciones();
        break;

    case ActionAdminType::TIENDAS_INFO_ASK:

        break;

    case ActionAdminType::MODIFY_TIENDA_ASK:

        break;

    case ActionAdminType::INVALID:
        reply = Action::generateErrorXml("XML no válido");
        break;
    }

    return reply;
}

QString ActionAdmin::getMarcas() {
    QString xml = Action::getXmlTemplate("MarcasInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QVector<QPair<int, QString> > marcas;
    DBController::getInstance()->loadMarcas(marcas);

    QString marcasXml{""};
    for (auto marca : marcas) {
        marcasXml += QString("<marca id=\"%1\">%2</marca>")
                .arg(QString::number(marca.first)).arg(marca.second);
    }

    return QString(xml).arg("SUCCESS").arg(marcasXml);
}

QString ActionAdmin::getModelos() {
    QString xml = Action::getXmlTemplate("ModelosInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QString searchField = "marca_id";
    readUntilElement(searchField);
    QString marcaId = m_xmlReader->readElementText();


    QVector<QPair<int, QString> > modelos;
    DBController::getInstance()->loadModelos(modelos, marcaId.toInt());

    QString modelosXml{""};
    for (auto modelo : modelos) {
        modelosXml += QString("<modelo id=\"%1\">%2</modelo>")
                .arg(QString::number(modelo.first)).arg(modelo.second);
    }

    return QString(xml).arg("SUCCESS").arg(modelosXml);
}

QString ActionAdmin::getReparaciones() {
    QString xml = Action::getXmlTemplate("ReparacionInfoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QString searchField = "modelo_id";
    readUntilElement(searchField);
    QString searchId = m_xmlReader->readElementText();


    QVector<QPair<int, QString> > reparaciones;
    DBController::getInstance()->loadReparaciones(reparaciones, searchId.toInt());

    QString reparacionesXml{""};
    for (auto reparacion : reparaciones) {
        reparacionesXml += QString("<reparacion id=\"%1\">%2</reparacion>")
                .arg(QString::number(reparacion.first)).arg(reparacion.second);
    }

    return QString(xml).arg("SUCCESS").arg(reparacionesXml);
}

QString ActionAdmin::getTiendas() {
    QString xml = Action::getXmlTemplate("TiendasIndoReply");

    if (!m_validXml) {
        return QString(xml).arg("FAILURE").arg("");
    }

    QString tiendaTemplate = "<tienda><tienda_id>%1</tienda_id><tienda_nombre>%2</tienda_nombre>"
                             "<tienda_user>%3</tienda_user><tienda_password>%4</tienda_password>"
                             "<tienda_direccion>%5</tienda_direccion></tienda>";


}
