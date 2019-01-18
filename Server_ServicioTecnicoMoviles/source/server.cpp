#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>

#include "server.h"

Server::Server(quint16 port) {
    m_webSocketServer(new QWebSocketServer(QStringLiteral("Servidor Servicio Tecnico de Moviles"),
                                           QWebSocket::NonSecureMode, this));
    if (m_webSocketServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Servidor iniciado. Puerto: " << port;

        connect()
    }
}
