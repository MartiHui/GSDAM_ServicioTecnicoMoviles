#include "actiontecnico.h"

ActionTecnico::ActionTienda(const QString &message) : Action(message) {

}

QString ActionTecnico::getReply() {
    if (!isXmlValid()) {
        return Action::generateErrorXml(m_callbackId, "XML no válido");
    }
}
