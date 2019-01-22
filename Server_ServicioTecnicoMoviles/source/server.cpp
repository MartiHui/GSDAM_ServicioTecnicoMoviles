#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>

#include "server.h"

Server::Server(quint16 port) {
    m_webSocketServer(new QWebSocketServer(QStringLiteral("Servidor Servicio Tecnico de Moviles"),
                                           QWebSocket::NonSecureMode, this));
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

void Server::socketConnected() {
    QWebSocket *clientSocket = m_webSocketServer->nextPendingConnection();

    qDebug() << "Conexion recibida: " << clientSocket;

    connect(clientSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(clientSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << clientSocket;
}

void Server::socketDisconnected() {
    QWebSocket clientSocket = qobject_cast<QWebSocket *>(sender());

    qDebug() << "Conexión finalizada: " << clientSocket;

    if (clientSocket) {
        m_clients.removeAll(clientSocket);
        clientSocket.deleteLater();
    }
}

void Server::processTextMessage(QString message) {
    QWebSocket *clientSocket = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Mensaje recibido. Remitente: " << clientSocket;


}
