#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>

class QWebSocket;

// Clase para gestionar la conexion con el programa servidor
class ServerConnection : public QObject {
    Q_OBJECT
public:
    QWebSocket *m_webSocket;

    explicit ServerConnection(QString url);
    ~ServerConnection();
    void sendMessage(QString xmlMessage);
    void connect();
    void disconnect();

private:
    QUrl m_serverUrl;

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void messageReceived(QString message);
    void connectedToServer();
};

#endif // SERVERCONNECTION_H
