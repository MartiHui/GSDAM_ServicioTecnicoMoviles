#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>
#include <QTimer>

#include "server.h"
#include "client.h"
#include "action.h"
#include "actiontienda.h"
#include "actiontecnico.h"

Server::Server(quint16 port) :
        m_port{port}{
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

    connect(client, SIGNAL(textMessageReceived(const QString &)), this, SLOT(processTextMessage(const QString &)));
    connect(client, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));

    m_clients << client;
}

void Server::socketDisconnected() {
    Client *client = qobject_cast<Client *>(sender());
    qDebug() << "Conexión finalizada: " << client->getWebSocket();

    if (client) {
        m_clients.removeAll(client);
        client->deleteLater();
    }
}

void Server::processTextMessage(const QString & message) {
    Client *client = qobject_cast<Client *>(sender());

    QString reply{""};
    if (!client->hasIdentified()) {
        Action action(&message);
        if (action.isConnectionPetition()) {
            reply = action.establishConnection(client);
        } else {
            reply = Action::generateErrorXml(action.m_callbackId, "Aún no te has identifiado");
        }
    } else if (client->getClientType() == ClientType::TIENDA) {
        ActionTienda action(&message);
        reply = action.getReply();
    } else if (client->getClientType() == ClientType::TECNICO) {
        ActionTecnico action(&message);
        reply = action.getReply();
    }

    client->getWebSocket()->sendTextMessage(reply);

    //qDebug() << "Recibido: " << message;
    //qDebug() << "Enviado: " << reply;
}
