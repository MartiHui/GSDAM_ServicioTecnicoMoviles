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

void Client::identify(int clientId, QString type) {
    m_clientId = clientId;

    if (type == "TIENDA") {
        m_type = ClientType::TIENDA;
    } else if (type == "TECNICO") {
        m_type = ClientType::TECNICO;
    } else if (type == "ADMIN") {
        m_type = ClientType::ADMIN;
    }
}

int Client::getClientId() const{
    return m_clientId;
}

ClientType Client::getClientType() const{
    return m_type;
}

void Client::onSocketMessageReceived(const QString & message) {
    emit textMessageReceived(message);
}

void Client::onSocketDisconnected() {
    emit disconnected();
}
