#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QtSql>

//class QSqlDatabase;

class DBController : QObject {
    Q_OBJECT

public:
    static DBController* getInstance();
    static void deleteInstance();
    int tiendaInDb(QString nombreTienda);
    void getMarcas(QVector<QPair<int, QString> > *marcas);
    void getModelos(int marcaId, QVector<QPair<int, QString> > *modelos);

private:
    explicit DBController();
    ~DBController();

    static DBController* m_pInstance;
    QSqlDatabase database;
};

#endif // DBCONTROLLER_H
