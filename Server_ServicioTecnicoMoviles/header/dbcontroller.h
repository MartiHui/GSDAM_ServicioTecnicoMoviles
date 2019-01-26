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
    bool tiendaInDb(QString nombreTienda);

private:
    explicit DBController();
    ~DBController();

    static DBController* m_pInstance;
    QSqlDatabase database;
};

#endif // DBCONTROLLER_H
