#include <QDebug>
#include <QTimer>
#include <QWebSocket>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_serverConnection = new ServerConnection("ws://localhost:1234");
    //m_serverConnection->m_conectado = true;
    //QTimer::singleShot(0, this, SLOT(pruebas()));
    //m_serverConnection->sendMessage(Action::establishConnection("EDIB"));
    //qDebug() << m_serverConnection->m_xmlReply;
    ui->marcasCmbBox->addItem("Uno", 1);
    ui->marcasCmbBox->addItem("Diez", 10);
    ui->marcasCmbBox->addItem("Cien", 100);
    ui->marcasCmbBox->addItem("Mil", 1000);
    ui->marcasCmbBox->addItem("Treinta", 30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pruebas() {
    qDebug() << "enviando mensaje";
    m_serverConnection->m_webSocket->sendTextMessage("hola");
    //m_serverConnection->sendMessage(Action::establishConnection("EDIB"));
    //qDebug() << m_serverConnection->m_xmlReply;
}

void MainWindow::on_conectarServidor_clicked()
{
    QString nombreTienda = ui->nombreTienda->text();
    m_serverConnection->sendMessage(Action::establishConnection(nombreTienda));
    // TODO conectarme al sevidor
}

void MainWindow::on_marcasCmbBox_currentIndexChanged(int index)
{
    int marcaId = ui->marcasCmbBox->itemData(index).toInt();
    // TODO rellenar combo box modelos
}

void MainWindow::on_modelosCmbBox_currentIndexChanged(int index)
{
    int modeloId = ui->modelosCmbBox->itemData(index).toInt();
    // TODO rellenar lista reparaciones posibles
}

void MainWindow::on_reparacionesPosibles_doubleClicked(const QModelIndex &index)
{
    // Quitar de esta lita y añadir a la otra
}

void MainWindow::on_reparacionesElegidas_doubleClicked(const QModelIndex &index)
{
    // Quitar de esta lita y aadir a la otra
}

void MainWindow::on_ordenRequest_clicked()
{
    // Hacer pedido y obtener id de pedido
}

void MainWindow::on_ordenEstado_clicked()
{
    QString ordenId = ui->numOrden->text();
    // Solicitar estado del pedido
}
