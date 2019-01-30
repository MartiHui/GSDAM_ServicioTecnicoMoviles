#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QWebSocket;

// Clase que gestionará la información de las conexiones a nuestro servidor
class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QWebSocket * webSocket);
    ~Client();

    QWebSocket* getWebSocket();
    bool isValidated(); // true si el cliente se ha identificado
    void validate(int tiendaId); // marca el cliente como identificado y le asigna su id de la base de datos
    int getTiendaId();

private:
    int m_tiendaId; // EL ID que tiene esta tienda en la base de datos
    bool m_validated; // Si se ha validado que la conexion proviene de una tienda aceptada
    QWebSocket *m_webSocket; // Gestiona la conexion por socket

signals:
    void textMessageReceived(const QString &);
    void disconnected();

private slots:
    void onSocketMessageReceived(const QString &);
    void onSocketDisconnected();
};

#endif // CLIENT_H
