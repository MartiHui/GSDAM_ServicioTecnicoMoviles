#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>
#include <functional>

#include "datainfo.h"

class ServerConnection;
class QListWidgetItem;
class Action;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void switchCentralWidgetEnabled(); // Alterna los elementos de la ui entre bloqueados y desbloqueados

private:
    Ui::MainWindow *ui;
    ServerConnection *m_serverConnection;
    static int s_callbackId;
    QVector<QPair<int, std::function<void(Action &)> > > m_callbacks;

    void establishConnectionReply(Action &action);

    /*void fillMarcasCmbBox(QVector<QPair<QString, int> > marcas);
    void fillModelosCmbBox(QVector<QPair<QString, int> > modelos);
    void fillReparacionesPosiblesList(QVector<QPair<QString, int> > reparaciones);
    void clearLists();
    void resetLists();*/

private slots:
    //void replyReceived(QString message);
    void connexionEstablished();
    /*void on_marcasCmbBox_currentIndexChanged(int index);
    void on_conectarServidor_clicked();
    void on_modelosCmbBox_currentIndexChanged(int index);
    void on_ordenRequest_clicked();
    void on_ordenEstado_clicked();
    void on_reparacionesPosibles_itemDoubleClicked(QListWidgetItem *item);
    void on_reparacionesElegidas_itemDoubleClicked(QListWidgetItem *item);*/
    void on_conectarServidor_clicked();
};

#endif // MAINWINDOW_H
