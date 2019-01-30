#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QVector>

class QXmlStreamReader;
class QXmlStreamWriter;
class Client;

// Define el tipo de XML que se ha recibido
enum class ActionType {
    INVALID,
    ESTABLISH_CONNECTION,
    LISTA_ORDENES_ASK,
    MARCAS_INFO_ASK,
    MODELOS_INFO_ASK,
    REPARACION_INFO_ASK,
    ORDEN_REQUEST_ASK,
    ORDEN_STATUS_ASK,
};

// Clase para parsear los xml recibidos por el servidor y escribir los xml como respuesta correspondientes;
class Action : public QObject {
    Q_OBJECT
public:
    struct Reparacion {
        int reparacionId;
        QString nombre;
        int tiempoMinutos;
        float precio;
    };

    struct Orden {
        int ordenId;
        int modeloId;
        int tiendaId;
        QVector<int> reparacionesId;
    };

    explicit Action(const QString *message);
    ~Action();
    ActionType getActionType();
    void getReply(QString *reply, Client *client); // Crea un xml con la repsuesta segun el ActionType del xml
    void error(QString *reply, QString message); // Crea un xml con un mensaje de error

private:
    ActionType m_actionType{ActionType::INVALID};
    QXmlStreamReader *m_xmlReader;

    void setActionType();
    bool isXmlValid(const char *archivoXML); // Parsea el xml con el dtd indicado. Devuelve true si el xml es correcto

    // Métodos para crear los xml de respesta en el puntero a QString reply. Algunos métodos necesitarán información sobre el cliente que hace la solicitud.
    void establishConnection(QString *reply, Client *client);
    //void listaOrdenes(QString *reply, Client *client);
    void marcasInfo(QString *reply);
    void modelosInfo(QString *reply);
    void reparacionInfo(QString *reply);
    void ordenRequest(QString *reply, Client *client);
    void ordenStatus(QString *reply, Client *client);

    void writeXmlStart(QXmlStreamWriter &writer, const QString &dtdName, const QString &action); // Escribe el header, que coincide entre todos, a excepcion del nombre del dtd y la accion.
    QString getTextElement(QString tagName); // Devuelve el texto que contenga la etiqueta tagName
};

#endif // ACTION_H
