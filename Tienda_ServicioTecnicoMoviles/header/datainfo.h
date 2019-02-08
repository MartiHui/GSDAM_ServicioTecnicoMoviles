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

#endif // DATAINFO_H
