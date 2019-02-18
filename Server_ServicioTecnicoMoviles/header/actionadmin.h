#ifndef ACTIONADMIN_H
#define ACTIONADMIN_H

#include <QString>

#include "action.h"
#include "client.h"

enum class ActionAdminType {
    MARCAS_INFO_ASK,
    MODELOS_INFO_ASK,
    REPARACION_INFO_ASK,
    TIENDAS_INFO_ASK,
    MODIFY_TIENDA_ASK,
    INVALID
};

class ActionAdmin : public Action {
public:
    ActionAdmin(const QString &message);
    void setActionType();
    QString getReply(const Client &client);

    static QString newOrder(int orderId, QString status);

private:
    ActionAdminType m_actionType;
    bool m_validXml;

    QString getMarcas();
    QString getModelos();
    QString getReparaciones();
    QString getTiendas();
};

#endif // ACTIONADMIN_H
