#ifndef ACTIONTIENDA_H
#define ACTIONTIENDA_H

#include "action.h"

enum class ActionTiendaType {
    LISTA_ORDENES_ASK,
    MARCAS_INFO_ASK,
    MODELOS_INFO_ASK,
    REPARACION_INFO_ASK,
    ORDEN_REQUEST_ASK,
};

class ActionTienda : public Action {
public:
    ActionTienda(const QString &message);
    QString getReply();
};

#endif // ACTIONTIENDA_H
