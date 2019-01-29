#include <QDebug>
#include <QTimer>
#include <QWebSocket>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_isWaitingReply = false;
    m_serverConnection = new ServerConnection("ws://localhost:1234");
    connect(m_serverConnection, SIGNAL(messageReceived(QString)), this, SLOT(replyReceived(QString)));
}

void MainWindow::replyReceived(QString message) {
    qDebug() << "reply";
    m_isWaitingReply = false;
    Action *action = new Action(&message);
    QMessageBox msgBox;

    switch (action->getActionType()) {
    case ActionType::ERROR:
        msgBox.setText(action->getElementText("message"));
        msgBox.exec();
        break;

    case ActionType::ESTABLISH_CONNECTION:
        //m_isWaitingReply = true;
        //m_serverConnection->sendMessage(Action::askMarcasInfo());

        m_serverConnection->m_conectado = true;
        msgBox.setText(action->getElementText("tienda"));
        msgBox.exec();
        break;

    case ActionType::LISTA_ORDENES_REPLY:
        break;

    case ActionType::MARCAS_INFO_REPLY:
        fillMarcasCmbBox(action->getMarcasInfo());
        break;

    case ActionType::MODELOS_INFO_REPLY:
        break;

    case ActionType::REPARACION_INFO_REPLY:
        break;

    case ActionType::ORDEN_REQUEST_REPLY:
        msgBox.setText(action->getElementText("El código de tu pedido es " + action->getElementText("orden_id")));
        msgBox.exec();
        break;

    case ActionType::ORDEN_STATUS_REPLY:
        msgBox.setText(action->getElementText("respuesta"));
        msgBox.exec();
        break;

    }

    delete action;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillMarcasCmbBox(QVector<QPair<QString, int> > marcas) {
    for (auto marca : marcas) {
        ui->marcasCmbBox->addItem(marca.first, marca.second);
    }
}

void MainWindow::on_conectarServidor_clicked()
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;
        QString nombreTienda = ui->nombreTienda->text();
        m_serverConnection->sendMessage(Action::establishConnection(nombreTienda));
    }
}

void MainWindow::on_marcasCmbBox_currentIndexChanged(int index)
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    int marcaId = ui->marcasCmbBox->itemData(index).toInt();
    // TODO rellenar combo box modelos
}

void MainWindow::on_modelosCmbBox_currentIndexChanged(int index)
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    int modeloId = ui->modelosCmbBox->itemData(index).toInt();
    // TODO rellenar lista reparaciones posibles
}

void MainWindow::on_reparacionesPosibles_doubleClicked(const QModelIndex &index)
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    // Quitar de esta lita y añadir a la otra
}

void MainWindow::on_reparacionesElegidas_doubleClicked(const QModelIndex &index)
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    // Quitar de esta lita y aadir a la otra
}

void MainWindow::on_ordenRequest_clicked()
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    // Hacer pedido y obtener id de pedido
}

void MainWindow::on_ordenEstado_clicked()
{
    if (!m_isWaitingReply) {
        m_isWaitingReply = true;

    }
    QString ordenId = ui->numOrden->text();
    // Solicitar estado del pedido
}
