#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
#include <functional>
#include <QMap>

#include "datainfo.h"

class ServerConnection;
class QListWidgetItem;
class Action;

namespace Ui {
class MainWindow;
}

enum class InfoType {
    MARCA,
    MODELO,
    REPARACION,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ServerConnection *m_serverConnection;
    QVector<Marca> m_marcas;
    QVector<Tienda> m_tiendas;

    void establishConnectionReply(Action *action);
    void showErrorMsgBox(QString msg);
    void fillMarcasVector(InfoType infoType, Action *action);
    void fillTiendasVector(Action *action);

private slots:
    void replyReceived(QString message);
    void on_conectarServidor_clicked();
};

#endif // MAINWINDOW_H
