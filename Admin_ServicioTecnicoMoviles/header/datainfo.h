#ifndef DATAINFO_H
#define DATAINFO_H

#include <QString>
#include <QVector>

struct Reparacion {
    int id;
    QString nombre;
};

struct Modelo {
    int id;
    QString nombre;
    QVector<Reparacion> reparaciones;
};

struct Marca {
    int id;
    QString nombre;
    QVector<Modelo> modelos;
};

struct Tienda {
    int id;
    QString nombre;
    QString user;
    QString password;
    QString direccion;
}

#endif // DATAINFO_H
