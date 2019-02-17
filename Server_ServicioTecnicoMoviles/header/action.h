#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QVector>

class QXmlStreamReader;
class QXmlStreamWriter;
class Client;

// Clase para parsear los xml recibidos por el servidor y escribir los xml como respuesta correspondientes;
class Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const QString &message);
    ~Action();
    bool isConnectionPetition();
    // Genera un XML con la plantilla de Error.xml
    static QString generateErrorXml(QString errorMessage);
    // Se conecta con la base de datos y comprueba si el usuario y contraseña existen. En caso afirmativo valida client y devuelve el xml de respuesta, de lo contrario, deuelve el xml de error.
    QString establishConnection(Client &client);

protected:
    QString m_requestXml; // Todo el archivo xml recibido del cliente
    QString m_requestType{""}; // El tipo de accion, que deberia estar en la etiqueta <action> del xml recibido
    QXmlStreamReader *m_xmlReader;

    // Obtiene el tipo de la solicitud y el id del callback
    void setRequestInfo();
    // Lee el XML hasta encontrar el elemento llamado tagName. Devuelve true si lo encuentra, false si llega hasta el final del documento
    bool readUntilElement(QString tagName);
    // Parsea el xml con su xsd. Se da por hecho que el XSD tiene el mismo nombbre que el XML, que coincide con el campo action del xml.
    bool isXmlValid();
    // Obtiene el archivo xml con el nombre filename localizado en la ruta XML_FOLDER y con extension .xml
    static QString getXmlTemplate(QString filename);
};

#endif // ACTION_H
