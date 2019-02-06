#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>

class QWebSocketServer;
class Client;

// La clase principal que gestionará el servidor
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port);
    ~Server();

private:
    quint16 m_port; // El puerto al que se conecta
    QWebSocketServer *m_webSocketServer;
    QList<Client *> m_clients; // La lista de clientes conectados al servidor

signals:
    void close();

private slots:
    void socketConnected();
    void socketDisconnected();
    void processTextMessage(const QString & message);
    void startServer();
};

#endif // SERVER_H
