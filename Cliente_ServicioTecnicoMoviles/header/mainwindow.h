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
};

#endif // MAINWINDOW_H
