#ifndef ACTION_H
#define ACTION_H

#include <QObject>

class QXmlStreamReader;
class Client;

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
    struct Reparacion {
        int reparacionId;
        QString nombre;
        int tiempoMinutos;
        float precio;
    };

    explicit Action(const QString *message);
    ~Action();
    ActionType getActionType();
    void getReply(QString *reply, Client *client);
    void error(QString *reply, QString message);

private:
    ActionType m_actionType{ActionType::INVALID};
    QXmlStreamReader *m_xmlReader;
    const QString  DTD_DECLARATION{"<!DOCTYPE ServicioTecnicoMoviles SYSTEM \"%1\">"};

    void setActionType();
    bool isXmlValid(const char *archivoXML);
    void establishConnection(QString *reply, Client *client);
    void listaOrdenes(QString *reply, Client *client);
    void marcasInfo(QString *reply);
    void modelosInfo(QString *reply);
    void reparacionInfo(QString *reply);
    void ordenRequest(QString *reply);
    void ordenStatus(QString *reply);
    QString getTextElement(QString tagName);
};

#endif // ACTION_H
