#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>
#include <QUrl>

class QWebSocket;

// Clase para gestionar la conexion con el programa servidor
class ServerConnection : public QObject {
    Q_OBJECT
public:
    QWebSocket *m_webSocket;

    explicit ServerConnection(QString url);
    ~ServerConnection();
    bool sendMessage(QString xmlMessage);

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void messageReceived(QString message);
};

#endif // SERVERCONNECTION_H
