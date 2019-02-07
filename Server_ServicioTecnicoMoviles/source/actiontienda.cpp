#include "actiontienda.h"

ActionTienda::ActionTienda(const QString &message) : Action(message) {

}

QString ActionTienda::getReply() {
    if (!isXmlValid()) {
        return Action::generateErrorXml(m_callbackId, "XML no válido");
    }
}
