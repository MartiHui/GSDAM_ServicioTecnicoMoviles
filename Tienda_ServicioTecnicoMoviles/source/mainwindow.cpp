#include <QDebug>
#include <QTimer>
#include <QWebSocket>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverconnection.h"
#include "action.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setEnabled(false);

    m_serverConnection = new ServerConnection("ws://localhost:1234");
    connect(m_serverConnection, SIGNAL(messageReceived(QString)), this, SLOT(replyReceived(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::replyReceived(QString message) {
    Action *action = new Action(message);

    switch (action->getActionType()) {
    case ActionType::ERROR:
        break;

    case ActionType::ESTABLISH_CONNECTION:
        establishConnectionReply(action);
        break;

    case ActionType::LISTA_ORDENES_REPLY:
        break;

    case ActionType::MARCAS_INFO_REPLY:
        break;

    case ActionType::MODELOS_INFO_REPLY:
        break;

    case ActionType::REPARACION_INFO_REPLY:
        break;

    case ActionType::ORDEN_REQUEST_REPLY:
        break;

    case ActionType::ORDEN_STATUS_CHANGED:
        break;

    }

    delete action;
}

/*void MainWindow::replyReceived(QString message) {
    switchCentralWidgetEnabled(); // Desbloqueamos el programa
    Action *action = new Action(&message);
    QMessageBox msgBox;

    switch (action->getActionType()) {
    case ActionType::ERROR:
        msgBox.setText(action->getElementText("message"));
        msgBox.exec();
        break;

    case ActionType::ESTABLISH_CONNECTION:
        switchCentralWidgetEnabled(); // Bloqueamos el programa hasta recibir las marcas
        m_serverConnection->sendMessage(Action::askMarcasInfo());

        msgBox.setText(action->getElementText("tienda"));
        msgBox.exec();
        break;

    case ActionType::LISTA_ORDENES_REPLY:
        break;

    case ActionType::MARCAS_INFO_REPLY:
        fillMarcasCmbBox(action->getMarcasInfo());
        break;

    case ActionType::MODELOS_INFO_REPLY:
        fillModelosCmbBox(action->getModelosInfo());
        break;

    case ActionType::REPARACION_INFO_REPLY:
        fillReparacionesPosiblesList(action->getReparacionesInfo());
        break;

    case ActionType::ORDEN_REQUEST_REPLY:
        msgBox.setText(QString("El código de tu pedido es: ") + action->getElementText("orden_id"));
        msgBox.exec();
        break;

    case ActionType::ORDEN_STATUS_REPLY:
        msgBox.setText(QString("Estado del pedido: " + action->getElementText("respuesta")));
        msgBox.exec();
        break;
    }

    delete action;
}*/

void MainWindow::establishConnectionReply(Action &action) {
    ui->conectarServidor->setEnabled(true);
}

/*
void MainWindow::switchCentralWidgetEnabled() {
    static bool isEnabled = true;
    if (m_serverConnection->m_webSocket->isValid()) {
        isEnabled = !isEnabled;
        ui->centralWidget->setEnabled(isEnabled);
    }
}

void MainWindow::fillMarcasCmbBox(QVector<QPair<QString, int> > marcas) {
    ui->marcasCmbBox->clear();
    for (auto marca : marcas) {
        ui->marcasCmbBox->addItem(marca.first, marca.second);
    }
}

void MainWindow::fillModelosCmbBox(QVector<QPair<QString, int> > modelos) {
    ui->modelosCmbBox->clear();
    for (auto modelo : modelos) {
        ui->modelosCmbBox->addItem(modelo.first, modelo.second);
    }
}

void MainWindow::fillReparacionesPosiblesList(QVector<QPair<QString, int> > reparaciones) {
    clearLists();
    for (auto reparacion : reparaciones) {
        QListWidgetItem *listItem = new QListWidgetItem(reparacion.first);
        listItem->setData(0x0100, reparacion.second);
        ui->reparacionesPosibles->addItem(listItem);
    }
}

void MainWindow::clearLists() {
    ui->reparacionesPosibles->clear();
    ui->reparacionesElegidas->clear();
}

void MainWindow::resetLists() {
    for (int i = ui->reparacionesElegidas->count()-1; i >= 0; i--) {
        ui->reparacionesPosibles->addItem(ui->reparacionesElegidas->takeItem(i));
    }
}

void MainWindow::on_conectarServidor_clicked()
{
    QString nombreTienda = ui->nombreTienda->text();
    m_serverConnection->sendMessage(Action::establishConnection(nombreTienda));
    switchCentralWidgetEnabled();
}

void MainWindow::on_marcasCmbBox_currentIndexChanged(int index)
{
    int marcaId = ui->marcasCmbBox->itemData(index).toInt();
    m_serverConnection->sendMessage(Action::askModelosInfo(marcaId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_modelosCmbBox_currentIndexChanged(int index)
{
    int modeloId = ui->modelosCmbBox->itemData(index).toInt();
    m_serverConnection->sendMessage(Action::askReparacionInfo(modeloId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_ordenRequest_clicked()
{
    int modeloId = ui->modelosCmbBox->itemData(ui->modelosCmbBox->currentIndex()).toInt();
    QVector<int> reparacionesId;
    int numReparaciones = ui->reparacionesElegidas->count();
    if (numReparaciones == 0) {
        QMessageBox msgBox;
        msgBox.setText("No has elegido ninguna reparación");
        msgBox.exec();
    } else {
        for (int i = 0; i < numReparaciones; i++) {
            reparacionesId.push_back(ui->reparacionesElegidas->item(i)->data(0x0100).toInt());
        }
        m_serverConnection->sendMessage(Action::askOrdenRequest(modeloId, &reparacionesId));
        resetLists();
        switchCentralWidgetEnabled();
    }
}

void MainWindow::on_ordenEstado_clicked()
{
    QString ordenId = ui->numOrden->text();
    ui->numOrden->setText("");
    m_serverConnection->sendMessage(Action::askOrdenStatus(ordenId));
    switchCentralWidgetEnabled();
}

void MainWindow::on_reparacionesPosibles_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesElegidas->addItem(ui->reparacionesPosibles->takeItem(ui->reparacionesPosibles->row(item)));
}

void MainWindow::on_reparacionesElegidas_itemDoubleClicked(QListWidgetItem *item)
{
    ui->reparacionesPosibles->addItem(ui->reparacionesElegidas->takeItem(ui->reparacionesElegidas->row(item)));
}*/

void MainWindow::on_conectarServidor_clicked()
{
    ui->conectarServidor->setEnabled(false);

    QString user = ui->usuario->text();
    ui->usuario->setText("");
    QString password = ui->password->text();
    ui->password->setText("");

    m_serverConnection->connectToServer(user, password);
}
