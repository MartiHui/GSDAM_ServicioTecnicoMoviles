#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QtSql>
#include <QVector>
#include <QPair>

#include "action.h"
#include "client.h"

// Clase que controla la conexion y las querys a la base de datos.
class DBController : QObject {
    Q_OBJECT

public:
    static DBController* getInstance(); // devuelve la unica instancia posible de la clase, para evitar conexiones multiples
    static void deleteInstance();
    // Busca el cliente en la base de datos con la combinacion de user y password e introduce en
    // result el id y nombre obtenidos. Devuelve true si se ha encontrado el cliente
    bool clientInDatabase(QString type, QString user, QString password, QPair<int, QString> *result);
    // Rellena el QVector ordenes con pares de id y estado de las ordenes de la tienda
    void loadListaOrdenes(const Client &client, QVector<QPair<int, QString> > &ordenes);
    void loadMarcas(QVector<QPair<int, QString> > &marcas);
    void loadModelos(QVector<QPair<int, QString> > &modelos, int marcaId);
    // Rellena el QVector reparaciones con pares de id y nombre de las reparaciones del modelo identificado por modeloId
    void loadReparaciones(QVector<QPair<int, QString> > &reparaciones, int modeloId);
    void loadStatuses(QVector<QPair<int, QString> > &statuses);
    QPair<int, QString> insertNewOrden(int tienda_id, int modelo_id, QVector<int> &reparaciones_id);
    // Actualiza la orden con id orderId con el status statusId y devuelve un pair que tiene el de la tienda a la que pertenece la orden
    // y un string con el nuevo estado
    QPair<int, QString> updateOrderStatus(int orderId, int statusId);
    int getOrderTecnico(int orderId);

private:
    explicit DBController();
    QString prepareClientInDatabaseQuery(const QString &type);

    static DBController* m_pInstance;
    QSqlDatabase database;
};

#endif // DBCONTROLLER_H
