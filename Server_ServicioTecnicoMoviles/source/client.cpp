#include <QWebSocket>
#include <QDebug>

#include "client.h"

Client::Client(QWebSocket * webSocket) {
    m_tiendaId = -1;
    m_validated = false;
    m_webSocket = webSocket;
}

Client::~Client() {
    delete m_webSocket;
}

QWebSocket* Client::getWebSocket() {
    return m_webSocket;
}

bool Client::isValidated() {
    return m_validated;
}

void Client::validate() {
    m_validated = true;
}
