#include <QWebSocket>
#include <QDebug>
#include <QMessageBox>

#include "serverconnection.h"
#include "action.h"

ServerConnection::ServerConnection(QString url) {
    m_webSocket = new QWebSocket();
    connect(m_webSocket, SIGNAL(connected()), this, SLOT(onConnected()));
    m_webSocket->open(QUrl(url));
}

ServerConnection::~ServerConnection() {
    m_webSocket->close();
    delete m_webSocket;
}

void ServerConnection::onConnected() {
    connect(m_webSocket, &QWebSocket::textMessageReceived, this, &ServerConnection::onTextMessageReceived);
}

void ServerConnection::onTextMessageReceived(QString message) { //qDebug() << "Recibido " <<  message;
    emit messageReceived(message);
}

bool ServerConnection::sendMessage(QString xmlMessage) { //qDebug() << "Enviado " << xmlMessage;
    if (m_webSocket->isValid()) {
        m_webSocket->sendTextMessage(xmlMessage);
        return true;
    } else {
        QMessageBox msgBox;
        msgBox.setText("No hay conexión con el servidor");
        msgBox.exec();
        return false;
    }
}
