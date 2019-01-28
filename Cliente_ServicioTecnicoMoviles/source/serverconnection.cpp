#include <QWebSocket>
#include <QDebug>

#include "serverconnection.h"
#include "action.h"

ServerConnection::ServerConnection(QString url) {
    m_webSocket = new QWebSocket();
    connect(m_webSocket, &QWebSocket::connected, this, &ServerConnection::onConnected);
    m_webSocket->open(QUrl(url));
}

ServerConnection::~ServerConnection() {
    m_webSocket->close();
    delete m_webSocket;
}

void ServerConnection::onConnected() {
    m_conectado = true;
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &ServerConnection::onTextMessageReceived);
    sendMessage(Action::establishConnection("EDIB"));
}

void ServerConnection::onTextMessageReceived(QString message) {
    m_xmlReply = message;
    m_waitingReply = false;
}

bool ServerConnection::sendMessage(QString xmlMessage) {
    if (m_conectado) {
        m_webSocket->sendTextMessage(xmlMessage);
        m_waitingReply = true;
        return true;
    } else {
        return false;
    }
}

