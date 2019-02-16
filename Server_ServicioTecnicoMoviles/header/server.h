#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QList>

#include "client.h"

class QWebSocketServer;

// La clase principal que gestionará el servidor
class Server : public QObject
{
    Q_OBJECT
public:
    static Server* getInstance(quint16 port=0);
    static void deleteInstance();
    Client* searchClient(int clientId, ClientType type);

private:
    explicit Server(quint16 port);
    ~Server();

    static Server* m_pInstance;
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
