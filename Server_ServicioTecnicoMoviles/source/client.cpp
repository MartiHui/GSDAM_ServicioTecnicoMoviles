#include <QWebSocket>
#include <QDebug>

#include "client.h"

Client::Client(QWebSocket * webSocket) {
    m_tiendaId = -1;
    m_validated = false;
    m_webSocket = webSocket;
}

QWebSocket* Client::getWebSocket() {
    return m_webSocket;
}
