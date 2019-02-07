#ifndef ACTIONTIENDA_H
#define ACTIONTIENDA_H

#include "action.h"

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
    QString getReply();

private:
    ActionTiendaType m_actionType;
};

#endif // ACTIONTIENDA_H
