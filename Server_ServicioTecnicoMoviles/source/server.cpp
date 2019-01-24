#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>

#include "server.h"
#include "client.h"
#include "action.h"

Server::Server(quint16 port) {
    m_webSocketServer = new QWebSocketServer(QStringLiteral("Servidor Servicio Tecnico de Moviles"),
                                           QWebSocketServer::NonSecureMode, this);
    if (m_webSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Servidor iniciado. Puerto: " << port;

        connect(m_webSocketServer, &QWebSocketServer::newConnection, this, &Server::socketConnected);
        connect(m_webSocketServer, &QWebSocketServer::closed, this, &Server::close);
    }
}

Server::~Server() {
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::removeClientSocket(Client *client) {
    m_clients.removeAll(client);
    client->deleteLater();
}

void Server::socketConnected() {
    Client *client = new Client(m_webSocketServer->nextPendingConnection());

    qDebug() << "Conexion recibida: " << client->getWebSocket();

    connect(client->getWebSocket(), &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(client->getWebSocket(), &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << client;
}

void Server::socketDisconnected() {
    Client *client = qobject_cast<Client *>(sender());
    qDebug() << "Conexión finalizada: " << client->getWebSocket();

    if (client) {
        removeClientSocket(client);
    }
}

void Server::processTextMessage(QString message) {
    Client *client = qobject_cast<Client *>(sender());
    qDebug() << "Mensaje recibido. Remitente: " << client->getWebSocket();

    QString reply;

    if (client->isValidated()) {
        Action *action = new Action(&message);
        reply = action->getReply();
    } else {
        removeClientSocket(client);
    }
}
