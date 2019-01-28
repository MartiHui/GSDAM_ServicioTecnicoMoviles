#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>
#include <QTimer>

#include "server.h"
#include "client.h"
#include "action.h"

Server::Server(quint16 port) {
    m_port = port;
    QTimer::singleShot(0, this, SLOT(startServer()));
}

Server::~Server() {
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::startServer() {
    m_webSocketServer = new QWebSocketServer(QStringLiteral("Servidor Servicio Tecnico de Moviles"),
                                           QWebSocketServer::NonSecureMode, this);
    if (m_webSocketServer->listen(QHostAddress::Any, m_port)) {
        qDebug() << "Servidor iniciado. Puerto: " << m_port;

        connect(m_webSocketServer, &QWebSocketServer::newConnection, this, &Server::socketConnected);
        connect(m_webSocketServer, &QWebSocketServer::closed, this, &Server::close);
    }
}

void Server::socketConnected() {
    Client *client = new Client(m_webSocketServer->nextPendingConnection());

    qDebug() << "Conexion recibida: " << client->getWebSocket();

    connect(client->getWebSocket(), SIGNAL(textMessageReceived(const QString &)), this, SLOT(processTextMessage(client, const QString &)));


//    connect(client->getWebSocket(), &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(client->getWebSocket(), &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << client;
}

void Server::socketDisconnected() {
    Client *client = qobject_cast<Client *>(sender());
    // La siguiente lnea crashea el programa
    //qDebug() << "Conexión finalizada: " << client->getWebSocket();
    qDebug() << "Un cliente se ha desconectado";

    if (client) {
        qDebug() << "hola1";
        m_clients.removeAll(client);
        qDebug() << "hola2";
        client->deleteLater();
        qDebug() << "hola3";
    }
}

void Server::processTextMessage(Client *client, const QString & message) {qDebug() << "mensaje2";
    //Client *client = qobject_cast<Client *>(sender());
    qDebug() << "Mensaje recibido. Remitente: " << client->getWebSocket();

    Action *action = new Action(&message);
    QString reply;

    if (action->getActionType() == ActionType::ESTABLISH_CONNECTION || client->isValidated()) {
        action->getReply(&reply, client);
    } else {
        action->error(&reply, "No te has autentificado correctamente");
    }

    client->getWebSocket()->sendTextMessage(message);

    delete action;
}
