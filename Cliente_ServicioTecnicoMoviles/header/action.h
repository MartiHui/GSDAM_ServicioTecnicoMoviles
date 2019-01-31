#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QPair>

class QXmlStreamReader;
class QXmlStreamWriter;

// El tipo de xml que se ha recibido
enum class ActionType {
    ERROR,
    ESTABLISH_CONNECTION,
    LISTA_ORDENES_REPLY,
    MARCAS_INFO_REPLY,
    MODELOS_INFO_REPLY,
    REPARACION_INFO_REPLY,
    ORDEN_REQUEST_REPLY,
    ORDEN_STATUS_REPLY,
};

// Clase para manejar los xml recibidos y escribir xml para enviar solicitudes al servidor
class Action : public QObject {
    Q_OBJECT
public:
    explicit Action(const QString *message);
    ~Action();
    ActionType getActionType();
    QString getElementText(QString tagName); // Obtiene el texto del elementos tagName
    QVector<QPair<QString, int> > getMarcasInfo();
    QVector<QPair<QString, int> > getModelosInfo();
    QVector<QPair<QString, int> > getReparacionesInfo();

    static QString establishConnection(QString nombreTienda);
    static QString askMarcasInfo();
    static QString askModelosInfo(int marcaId);
    static QString askReparacionInfo(int modeloId);
    static QString askOrdenStatus(QString ordenId);
    static QString askOrdenRequest(int modeloId, QVector<int> *reparacionesId);
    static QString error(QString message);

private:
    ActionType m_actionType;
    QXmlStreamReader *m_xmlReader;

    void setActionType();
    bool isXmlValid(const char *archivoXml);
    static void writeXmlStart(QXmlStreamWriter &writer, const QString &dtdName, const QString &action);
};

#endif // ACTION_H
