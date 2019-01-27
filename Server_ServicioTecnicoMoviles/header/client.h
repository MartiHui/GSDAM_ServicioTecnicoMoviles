#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

class QWebSocket;

class Client : public QObject {
    Q_OBJECT
public:
    explicit Client(QWebSocket * webSocket);
    ~Client();

    QWebSocket* getWebSocket();
    bool isValidated();
    void validate(int tiendaId);

private:
    int m_tiendaId; // EL ID que tiene esta tienda en la base de datos
    bool m_validated; // Si se ha validado que la conexion proviene de una tienda aceptada
    QWebSocket *m_webSocket; // Gestiona la conexion por socket
};

#endif // CLIENT_H
