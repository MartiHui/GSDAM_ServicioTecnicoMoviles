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

private:
    ActionType m_actionType{ActionType::INVALID};
    QXmlStreamReader *m_xmlReader;

    void setActionType();
};

#endif // ACTION_H
