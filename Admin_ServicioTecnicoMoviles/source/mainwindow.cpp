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
        showErrorMsgBox("No te has identificado al servidor");
        ui->conectarServidor->setEnabled(true);
        break;

    case ActionType::ESTABLISH_CONNECTION:
        establishConnectionReply(action);
        break;

    case ActionType::MARCAS_INFO_REPLY:
        fillMarcasVector(InfoType::MARCA, action);
        break;

    case ActionType::MODELOS_INFO_REPLY:
        fillMarcasVector(InfoType::MODELO, action);
        break;

    case ActionType::REPARACION_INFO_REPLY:
        fillMarcasVector(InfoType::REPARACION, action);
        break;

    case ActionType::TIENDAS_INFO_REPLY:
        fillTiendasVector(action);
        break;

    case ActionType::MODIFY_TIENDA_REPLY:

        break;

    }

    delete action;
}

void MainWindow::showErrorMsgBox(QString msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}

void MainWindow::establishConnectionReply(Action *action) {
    ui->conectarServidor->setEnabled(true);

    if (action->getRequestSuccess()) {
        ui->nombreTienda->setText(action->getNombreCliente());

        m_serverConnection->sendMessage(Action::askMarcasInfo());
    } else {
        showErrorMsgBox("Error al identificarse al servidor");
    }
}

void MainWindow::fillMarcasVector(InfoType infoType, Action *action) {
    if (!action->getRequestSuccess()) {
        showErrorMsgBox("Error al recibir la información de marcas/modelos/reparaciones");
        return;
    }

    static int marcaIndex = 0;
    static int numMarcas = 0;
    static int modeloIndex = 0;
    static int numModelos = 0;

    switch (infoType) {
    case InfoType::MARCA:
        for (auto marcaXml : action->getMarcasInfo()) {
            Marca marca{};
            marca.id = marcaXml.first;
            marca.nombre = marcaXml.second;

            m_marcas.push_back(marca);
        }

        numMarcas = m_marcas.count();
        if (numMarcas > 0) {
            m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[0].id));
        } else {
            m_serverConnection->sendMessage(Action::askTiendasInfo());
        }
        break;

    case InfoType::MODELO:
        for (auto modeloXml : action->getModelosInfo()) {
            Modelo modelo{};
            modelo.id = modeloXml.first;
            modelo.nombre = modeloXml.second;

            m_marcas[marcaIndex].modelos.push_back(modelo);
        }

        numModelos = m_marcas[marcaIndex].modelos.count();
        if (numModelos > 0) {
            m_serverConnection->sendMessage(Action::askReparacionInfo(m_marcas[marcaIndex].modelos[0].id));
        } else {
            modeloIndex = 0;
            marcaIndex++;
            if (marcaIndex < numMarcas) {
                m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[marcaIndex].id));
            } else {
                m_serverConnection->sendMessage(Action::askTiendasInfo());
            }
        }
        break;

    case InfoType::REPARACION:
        for (auto reparacionXml : action->getReparacionesInfo()) {
            Reparacion reparacion{reparacionXml.first, reparacionXml.second};
            m_marcas[marcaIndex].modelos[modeloIndex].reparaciones.push_back(reparacion);
        }

        modeloIndex++;
        if (modeloIndex < numModelos) {
            m_serverConnection->sendMessage(Action::askReparacionInfo(m_marcas[marcaIndex].modelos[modeloIndex].id));
        } else {
            modeloIndex = 0; numModelos = 0;
            marcaIndex++;
            if (marcaIndex < numMarcas) {
                m_serverConnection->sendMessage(Action::askModelosInfo(m_marcas[marcaIndex].id));
            } else {
                m_serverConnection->sendMessage(Action::askTiendasInfo());
            }
        }
        break;
    }
}

void MainWindow::fillTiendasVector(Action *action) {
    if (!action->getRequestSuccess()) {
        showErrorMsgBox("Ha habido un problema obteniendo la información de las tiendas.");
        return;
    }

    m_tiendas = action->getTiendasInfo();
}

void MainWindow::on_conectarServidor_clicked()
{
    ui->conectarServidor->setEnabled(false);

    QString user = ui->usuario->text();
    ui->usuario->setText("");
    QString password = ui->password->text();
    ui->password->setText("");

    if (!m_serverConnection->sendMessage(Action::establishConnection(user, password))) {
        ui->conectarServidor->setEnabled(true);
    }
}
