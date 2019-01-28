#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include <QObject>

class QWebSocket;

class ServerConnection : public QObject {
    Q_OBJECT
public:
    bool m_conectado{false};
    QString m_xmlReply;
    QWebSocket *m_webSocket;

    explicit ServerConnection(QString url);
    ~ServerConnection();
    bool sendMessage(QString xmlMessage); // Envia un mensaje al servidor. Devuelve true si lo ha podido mandar

private:
    bool m_waitingReply{false};

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);
};

#endif // SERVERCONNECTION_H
