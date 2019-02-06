#include <QWebSocket>
#include <QDebug>

#include "client.h"

Client::Client(QWebSocket * webSocket) :
        m_webSocket{webSocket} {
    connect(m_webSocket, SIGNAL(textMessageReceived(const QString &)), this, SLOT(onSocketMessageReceived(const QString &)));
    connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
}

Client::~Client() {
    delete m_webSocket;
}

QWebSocket* Client::getWebSocket() {
    return m_webSocket;
}

bool Client::hasIdentified() {
    return m_type != ClientType::INVALID;
}

void Client::identify(int tiendaId, ClientType type) {
    m_clientId = tiendaId;
    m_type = type;
}

int Client::getClientId() {
    return m_clientId;
}

void Client::onSocketMessageReceived(const QString & message) {
    emit textMessageReceived(message);
}

void Client::onSocketDisconnected() {
    emit disconnected();
}
