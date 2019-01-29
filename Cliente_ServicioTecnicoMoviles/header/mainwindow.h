#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QPair>

class ServerConnection;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool m_isWaitingReply;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ServerConnection *m_serverConnection;

    void fillMarcasCmbBox(QVector<QPair<QString, int> > marcas);

private slots:
    void replyReceived(QString message);
    void on_marcasCmbBox_currentIndexChanged(int index);
    void on_conectarServidor_clicked();
    void on_modelosCmbBox_currentIndexChanged(int index);
    void on_reparacionesPosibles_doubleClicked(const QModelIndex &index);
    void on_reparacionesElegidas_doubleClicked(const QModelIndex &index);
    void on_ordenRequest_clicked();
    void on_ordenEstado_clicked();
};

#endif // MAINWINDOW_H
