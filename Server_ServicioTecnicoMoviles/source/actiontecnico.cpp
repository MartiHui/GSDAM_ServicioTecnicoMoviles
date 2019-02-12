#include "actiontecnico.h"

ActionTecnico::ActionTecnico(const QString &message) : Action(message) {

}

QString ActionTecnico::getReply() {
    if (!isXmlValid()) {
        return Action::generateErrorXml("XML no válido");
    }
}
