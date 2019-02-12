#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QVector>

class QXmlStreamReader;
class QXmlStreamWriter;
class Client;
/*
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
};*/

enum class ReplyType {
    SAME_CLIENT,
    DIFF_CLIENT,
    NO_REPLY,
};

// Clase para parsear los xml recibidos por el servidor y escribir los xml como respuesta correspondientes;
class Action : public QObject {
    Q_OBJECT
public:
    /*struct Reparacion {
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
    };*/

    explicit Action(const QString &message);
    ~Action();
    bool isConnectionPetition();
    // Genera un XML con la plantilla de Error.xml
    static QString generateErrorXml(QString errorMessage);
    // Se conecta con la base de datos y comprueba si el usuario y contraseña existen. En caso afirmativo valida client y devuelve el xml de respuesta, de lo contrario, deuelve el xml de error.
    QString establishConnection(Client &client);

    /*ActionType getActionType();
    void getReply(QString *reply, Client *client); // Crea un xml con la repsuesta segun el ActionType del xml
    void error(QString *reply, QString message); // Crea un xml con un mensaje de error*/

protected:
    QString m_requestXml; // Todo el archivo xml recibido del cliente
    QString m_requestType{""}; // El tipo de accion, que deberia estar en la etiqueta <action> del xml recibido
    QXmlStreamReader *m_xmlReader;
    ReplyType m_replyType{ReplyType::SAME_CLIENT};

    // Obtiene el tipo de la solicitud y el id del callback
    void setRequestInfo();
    // Lee el XML hasta encontrar el elemento llamado tagName. Devuelve true si lo encuentra, false si llega hasta el final del documento
    bool readUntilElement(QString tagName);
    // Parsea el xml con su xsd. Se da por hecho que el XSD tiene el mismo nombbre que el XML, que coincide con el campo action del xml.
    bool isXmlValid();
    // Obtiene el archivo xml con el nombre filename localizado en la ruta XML_FOLDER y con extension .xml
    static QString getXmlTemplate(QString filename);

    /*ActionType m_actionType{ActionType::INVALID};
    QXmlStreamReader *m_xmlReader;

    void setActionType(const QString *message);
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
    QString getTextElement(QString tagName); // Devuelve el texto que contenga la etiqueta tagName*/
};

#endif // ACTION_H
