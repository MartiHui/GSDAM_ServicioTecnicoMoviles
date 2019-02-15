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
    LISTA_STATUS_REPLY,
    NEW_ORDER_REQUEST,
};

// Clase para manejar los xml recibidos y escribir xml para enviar solicitudes al servidor
class Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const QString &message);
    ~Action();
    ActionType getActionType() const;
    bool getRequestSuccess() const;

    // Metodos para obtener informacion de los XML recibidos
    QString getErrorMessage();
    QString getNombreCliente();
    QVector<QPair<int, QString> > getListaOrdenes();
    QVector<QPair<int, QString> > getListaStatus();
    QPair<int, QString> getNewOrderRequest();

    // Metodos para crear XML que enviar al servidor
    static QString establishConnection(QString user, QString password);
    static QString askListaOrdenes();
    static QString askListaStatus();
    static QString changeOrderStatus(int orderId, int statusId);

    /*QVector<QPair<int, QString> > getMarcasInfo();
    QVector<QPair<int, QString> > getModelosInfo();
    QVector<QPair<int, QString> > getReparacionesInfo();
    QPair<int, QString> getOrdenRequestInfo();

    // Metodos para crear  XML que enviar al servidor
    static QString askListaOrdenes();
    static QString askMarcasInfo();
    static QString askModelosInfo(int marcaId);
    static QString askReparacionInfo(int modeloId);
    static QString askOrdenRequest(int modeloId, const QVector<int> &reparacionesId);*/

private:
    ActionType m_actionType;
    QString m_messageXml;
    QXmlStreamReader *m_xmlReader;
    bool m_isRequestSuccess; // Determina si el servidor ha considerado nuestra solicitud anterior como correcta

    // Lee el XML hasta encontrar el elemento llamado tagName. Devuelve true si lo encuentra, false si llega hasta el final del documento
    bool readUntilElement(QString tagName);
    // Parsea el xml con su xsd.
    bool isXmlValid(QString filename);
    // Obtiene el archivo xml con el nombre filename localizado en la ruta XML_FOLDER y con extension .xml
    static QString getXmlTemplate(QString filename);
    void setActionInfo();
};

#endif // ACTION_H
