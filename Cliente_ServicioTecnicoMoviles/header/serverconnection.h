#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>

class QWebSocket;

class ServerConnection : public QObject {
    Q_OBJECT
public:
    QWebSocket *m_webSocket;
    bool m_conectado{false};

    explicit ServerConnection(QString url);
    ~ServerConnection();
    bool sendMessage(QString xmlMessage); // Envia un mensaje al servidor. Devuelve true si lo ha podido mandar

private:
    bool m_waitingReply{false};

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void messageReceived(QString message);
};

#endif // SERVERCONNECTION_H
