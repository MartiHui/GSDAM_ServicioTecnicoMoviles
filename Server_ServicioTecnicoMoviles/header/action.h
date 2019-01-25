#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class QXmlStreamReader;

enum class ActionType {
    INVALID,
    ESTABLISH_CONNECTION,
    LISTA_ORDENES_ASK,
    MARCAS_INFO_ASK,
    MODELOS_INFO_ASK,
    REPARACION_INFO_ASK,
    ORDEN_REQUEST_ASK,
    ORDEN_STATUS_ASK,
};

class Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const QString *message);
    ~Action();
    ActionType getActionType();
    QString getReply();
    QString clientNotValidated();

private:
    ActionType m_actionType{ActionType::INVALID};
    QXmlStreamReader *m_xmlReader;
    const QString  DTD_DECLARATION{"<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"%1\">"};

    void setActionType();
    bool isXmlValid(const char *archivoXML);
    void InvalidXml(QString *reply);
    void EstablishConnection(QString *reply);
    void ListaOrdenes(QString *reply);
    void MarcasInfo(QString *reply);
    void ModelosInfo(QString *reply);
    void ReparacionInfo(QString *reply);
    void OrdenRequest(QString *reply);
    void OrdenStatus(QString *reply);
};

#endif // ACTION_H
