#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ServerConnection;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ServerConnection *m_serverConnection;

private slots:
    void pruebas();
    void on_pushButton_clicked();
    void on_marcasCmbBox_currentIndexChanged(int index);
    void on_conectarServidor_clicked();
    void on_modelosCmbBox_currentIndexChanged(int index);
    void on_reparacionesPosibles_doubleClicked(const QModelIndex &index);
    void on_reparacionesElegidas_doubleClicked(const QModelIndex &index);
    void on_ordenRequest_clicked();
    void on_ordenEstado_clicked();
};

#endif // MAINWINDOW_H
