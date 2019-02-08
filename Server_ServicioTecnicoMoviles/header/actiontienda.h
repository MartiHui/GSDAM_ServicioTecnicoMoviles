#ifndef ACTIONTIENDA_H
#define ACTIONTIENDA_H

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
    static QString orderStatusChanged();

private:
    ActionTiendaType m_actionType;

    QString getListaOrdenes(const Client &client);
    QString getMarcas();
    QString getModelos();
    QString getReparaciones();
};

#endif // ACTIONTIENDA_H
