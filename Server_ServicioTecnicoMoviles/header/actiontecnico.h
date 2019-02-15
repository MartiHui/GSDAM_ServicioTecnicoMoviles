#ifndef ACTIONTECNICO_H
#define ACTIONTECNICO_H
#include "action.h"
#include "client.h"

enum class ActionTecnicoType {
    LISTA_ORDENES_ASK,
    LISTA_STATUS_ASK,
    CHANGE_ORDER_STATUS_ASK,
    INVALID
};

class ActionTecnico : public Action {
public:
    ActionTecnico(const QString &message);
    void setActionType();
    QString getReply();

private:
    ActionTecnicoType m_actionType;
    bool m_validXml;

    QString getListaOrdenes(const Client &client);
    QString getListaStatus();
    void changeOrderStatus();
};
#endif // ACTIONTECNICO_H
