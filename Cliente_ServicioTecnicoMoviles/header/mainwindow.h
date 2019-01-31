#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>

class ServerConnection;
class QListWidgetItem;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void switchCentralWidgetEnabled();

private:
    Ui::MainWindow *ui;
    ServerConnection *m_serverConnection;

    void fillMarcasCmbBox(QVector<QPair<QString, int> > marcas);
    void fillModelosCmbBox(QVector<QPair<QString, int> > modelos);
    void fillReparacionesPosiblesList(QVector<QPair<QString, int> > reparaciones);
    void clearLists();

private slots:
    void replyReceived(QString message);
    void on_marcasCmbBox_currentIndexChanged(int index);
    void on_conectarServidor_clicked();
    void on_modelosCmbBox_currentIndexChanged(int index);
    void on_ordenRequest_clicked();
    void on_ordenEstado_clicked();
    void on_reparacionesPosibles_itemDoubleClicked(QListWidgetItem *item);
    void on_reparacionesElegidas_itemDoubleClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
