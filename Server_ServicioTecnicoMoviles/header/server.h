#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>

class QWebSocketServer;
class QWebSocket;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port);
    ~Server();

private:
    QWebSocketServer *m_webSocketServer;
    QList<QWebSocket *> m_clients;

signals:
    void close();

private slots:
    void socketConnected();
    void socketDisconnected();
};

#endif // SERVER_H
