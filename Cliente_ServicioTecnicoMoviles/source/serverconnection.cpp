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
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &ServerConnection::onTextMessageReceived);
}

void ServerConnection::onTextMessageReceived(QString message) {
    m_waitingReply = false;
    qDebug() << message;
    emit messageReceived(message);
}

bool ServerConnection::sendMessage(QString xmlMessage) {
    qDebug() << "mensaje";
    m_webSocket->sendTextMessage(xmlMessage);
    m_waitingReply = true;
}

