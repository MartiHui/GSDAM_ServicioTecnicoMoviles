#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>


class QWebSocketServer;
class Client;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port);
    ~Server();

    void removeClientSocket(Client *client);

private:
    QWebSocketServer *m_webSocketServer;
    QList<Client *> m_clients;

signals:
    void close();

private slots:
    void socketConnected();
    void socketDisconnected();
    void processTextMessage(QString message);
};

#endif // SERVER_H
