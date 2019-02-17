#ifndef ACTIONADMIN_H
#define ACTIONADMIN_H

/*enum class ActionTecnicoType {
    LISTA_ORDENES_ASK,
    LISTA_STATUS_ASK,
    CHANGE_ORDER_STATUS_ASK,
    INVALID
};*/

class ActionAdmin : public Action {
public:
    ActionAdmin(const QString &message);
    void setActionType();
    QString getReply(const Client &client);

    static QString newOrder(int orderId, QString status);

private:
    ActionTecnicoType m_actionType;
    bool m_validXml;

    QString getListaOrdenes(const Client &client);
    QString getListaStatus();
    void changeOrderStatus();
};

#endif // ACTIONADMIN_H
