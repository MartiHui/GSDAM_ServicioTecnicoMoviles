#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPair>

class QXmlStreamReader;

// El tipo de xml que se ha recibido
enum class ActionType {
    ERROR,
    ESTABLISH_CONNECTION,
    LISTA_ORDENES_REPLY,
    MARCAS_INFO_REPLY,
    MODELOS_INFO_REPLY,
    REPARACION_INFO_REPLY,
    ORDEN_REQUEST_REPLY,
    ORDEN_STATUS_CHANGED,
};

// Clase para manejar los xml recibidos y escribir xml para enviar solicitudes al servidor
class Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const QString &message);
    ~Action();
    ActionType getActionType() const;
    int getCallbackId() const;
    QString getErrorMessage();
    QString getNombreCliente();
    QVector<QPair<int, QString> > getListaOrdenes();
    QVector<QPair<QString, int> > getMarcasInfo();
    QVector<QPair<QString, int> > getModelosInfo();
    QVector<QPair<QString, int> > getReparacionesInfo();
    static QString establishConnection(int callbackId, QString user, QString password);
    static QString askListaOrdenes(int callbackId);
    static QString askMarcasInfo(int callbackId);
    static QString askModelosInfo(int callbackId, int marcaId);
    static QString askReparacionInfo(int callbackId, int modeloId);
    static QString askOrdenRequest(int callbackId, int modeloId, const QVector<int> &reparacionesId);

private:
    ActionType m_actionType;
    QString m_messageXml;
    QXmlStreamReader *m_xmlReader;
    int m_callbackId;

    // Lee el XML hasta encontrar el elemento llamado tagName. Devuelve true si lo encuentra, false si llega hasta el final del documento
    bool readUntilElement(QString tagName);
    // Parsea el xml con su xsd.
    bool isXmlValid(QString filename);
    // Obtiene el archivo xml con el nombre filename localizado en la ruta XML_FOLDER y con extension .xml
    static QString getXmlTemplate(QString filename);

    void setActionInfo();
};

#endif // ACTION_H
