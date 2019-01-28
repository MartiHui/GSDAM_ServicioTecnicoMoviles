#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QString>

class Action : public QObject {
    Q_OBJECT
public:
    static QString establishConnection(QString nombreTienda);
    static QString askMarcasInfo();
    static QString askModelosInfo(int marcaId);
    static QString askReparacionInfo(int modeloId);
    static QString error(QString message);
};

#endif // ACTION_H
