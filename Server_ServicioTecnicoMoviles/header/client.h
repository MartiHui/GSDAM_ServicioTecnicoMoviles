#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QWebSocket;

enum class ClientType {
    TIENDA,
    TECNICO,
    INVALID,
};

// Clase que gestionará la información de las conexiones a nuestro servidor
class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QWebSocket * webSocket);
    ~Client();

    QWebSocket* getWebSocket();
    bool hasIdentified(); // true si el cliente se ha identificado
    void identify(int clientId, QString type); // marca el cliente como identificado y le asigna su id de la base de datos
    int getClientId();

private:
    int m_clientId{0}; // EL ID que tiene esta tienda en la base de datos
    ClientType m_type{ClientType::INVALID}; // El tipo de cliente
    QWebSocket *m_webSocket; // Gestiona la conexion por socket

signals:
    void textMessageReceived(const QString &);
    void disconnected();

private slots:
    void onSocketMessageReceived(const QString &);
    void onSocketDisconnected();
};

#endif // CLIENT_H
