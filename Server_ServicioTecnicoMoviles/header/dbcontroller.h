#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>

class QSqlDatabase;

class DBController : QObject {
    Q_OBJECT

public:
    explicit DBController();
    ~DBController();

private:
    QSqlDatabase *database;
};

#endif // DBCONTROLLER_H
