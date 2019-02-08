#include <QWebSocket>
#include <QDebug>

#include "serverconnection.h"
#include "action.h"

ServerConnection::ServerConnection(QString url) : m_serverUrl{url} {
    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
}

ServerConnection::~ServerConnection() {
    m_webSocket->close();
    delete m_webSocket;
}

void ServerConnection::onConnected() {
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &ServerConnection::onTextMessageReceived);
    emit connectedToServer();
}

void ServerConnection::onTextMessageReceived(QString message) { //qDebug() << "Recibido " <<  message;
    emit messageReceived(message);
}

void ServerConnection::sendMessage(QString xmlMessage) { //qDebug() << "Enviado " << xmlMessage;
    m_webSocket->sendTextMessage(xmlMessage);
}

void ServerConnection::connect() {
    disconnect();
    m_webSocket->open(QUrl(url));
}

void ServerConnection::disconnect() {
    m_webSocket->close();
}

