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
    void sendMessage(QString xmlMessage);
    void connectToServer(QString user, QString password);
    void disconnect();

private:
    QUrl m_serverUrl;
    QString m_user;
    QString m_password;

private slots:
    void onConnected();
    void onTextMessageReceived(QString message);

signals:
    void messageReceived(QString message);
};

#endif // SERVERCONNECTION_H
