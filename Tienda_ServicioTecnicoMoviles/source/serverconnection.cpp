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
    sendMessage(Action::establishConnection(m_user, m_password));
}

void ServerConnection::onTextMessageReceived(QString message) { //qDebug() << "Recibido " <<  message;
    emit messageReceived(message);
}

void ServerConnection::sendMessage(QString xmlMessage) { //qDebug() << "Enviado " << xmlMessage;
    m_webSocket->sendTextMessage(xmlMessage);
}

void ServerConnection::connectToServer(QString user, QString password) {
    m_user = user;
    m_password = password;

    disconnect();
    m_webSocket->open(QUrl(m_serverUrl));
}

void ServerConnection::disconnect() {
    m_webSocket->close();
}

