#include <QWebSocket>
#include <QDebug>

#include "client.h"

Client::Client(QWebSocket * webSocket) {
    m_tiendaId = -1;
    m_validated = false;
    m_webSocket = webSocket;
    connect(m_webSocket, SIGNAL(textMessageReceived(const QString &)), this, SLOT(onSocketMessageReceived(const QString &)));
    connect(m_webSocket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
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

void Client::validate(int tiendaId) {
    m_tiendaId = tiendaId;
    m_validated = true;
}

int Client::getTiendaId() {
    return m_tiendaId;
}

void Client::onSocketMessageReceived(const QString & message) {
    emit textMessageReceived(message);
}

void Client::onSocketDisconnected() {
    emit disconnected();
}
