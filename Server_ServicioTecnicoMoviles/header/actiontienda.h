#ifndef ACTIONTIENDA_H
#define ACTIONTIENDA_H

#include <QPair>

#include "action.h"
#include "client.h"

enum class ActionTiendaType {
    LISTA_ORDENES_ASK,
    MARCAS_INFO_ASK,
    MODELOS_INFO_ASK,
    REPARACION_INFO_ASK,
    ORDEN_REQUEST_ASK,
    INVALID
};

class ActionTienda : public Action {
public:
    ActionTienda(const QString &message);
    void setActionType();
    QString getReply(const Client &client);
    static QString orderStatusChanged(int orderId, QString status);

private:
    ActionTiendaType m_actionType;
    bool m_validXml;

    QString getListaOrdenes(const Client &client);
    QString getMarcas();
    QString getModelos();
    QString getReparaciones();
    QString newOrderRequest(const Client &client);
    QPair<int, QString> insertOrderDatabase(const Client &client);
    void notifyTecnico(QPair<int, QString> order);
};

#endif // ACTIONTIENDA_H
