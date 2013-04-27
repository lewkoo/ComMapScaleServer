#include <QtGui>
#include <QtNetwork>
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"
#include <stdlib.h>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mappingwidget.h"

const QString MainWindow::NOT_CONNECTED_TEXT = QString("Not Connected");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mapWidget(NULL)
{
    ui->setupUi(this);
    server = NULL;

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(startServer()));
    connect(ui->btnDisconnect, SIGNAL(clicked()), this, SLOT(stopServer()));
    connect(ui->btnQuit, SIGNAL(clicked()), this, SLOT(closeWindow()));
    connect(ui->btnLoad, SIGNAL(clicked()), this, SLOT(loadIcons()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clearMapObjects()));
    connect(ui->chkWedge, SIGNAL(stateChanged(int)), this, SLOT(wedgeStateChanged(int)));
    connect(ui->chkObjWedge, SIGNAL(stateChanged(int)), this, SLOT(objWedgeStateChanged(int)));
    connect(ui->chkVw, SIGNAL(stateChanged(int)), this, SLOT(vwStateChanged(int)));
    connect(ui->chkGlobalBtn, SIGNAL(stateChanged(int)), this, SLOT(globalButtonStateChanged(int)));
    connect(ui->chkWedgeIcon, SIGNAL(stateChanged(int)), this, SLOT(wedgeIconsStateChanged(int)));
    connect(ui->chkStatusSlider, SIGNAL(stateChanged(int)), this, SLOT(statusSliderStateChanged(int)));
    connect(ui->chkWedgePresses, SIGNAL(stateChanged(int)), this, SLOT(wedgeIconPressesStateChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addMapWidget(MappingWidget* mapWidget)
{
    this->mapWidget = mapWidget;

    QDockWidget *dockWidget = new QDockWidget(tr("Map"), this);
    dockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
    dockWidget->setWidget(mapWidget);
    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
    dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
}

void MainWindow::startServer()
{
    server = new TcpServer(mapWidget, this);

    ui->chkWedge->setEnabled(true);
    ui->chkObjWedge->setEnabled(ui->chkWedge->checkState());
    ui->chkVw->setEnabled(true);
    ui->chkGlobalBtn->setEnabled(true);
    ui->chkWedgeIcon->setEnabled(true);
    ui->chkWedgePresses->setEnabled(true);
    ui->chkStatusSlider->setEnabled(true);

    //Give map widget a handle to client data
    if (mapWidget != NULL)
    {
        mapWidget->setClientList(server->getClientList());
    }

    if (!server->listen(QHostAddress::Any, 50000))
    {
        QMessageBox::critical(this, tr("TcpServer"),
                              tr("Unable to start the server: %1.")
                              .arg(server->errorString()));
        //close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->lblStatus->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
                            "Ready for N900 connections.")
                           .arg(ipAddress).arg(server->serverPort()));
}

void MainWindow::stopServer()
{
    delete server;
    server = NULL;

    ui->chkWedge->setEnabled(false);
    ui->chkObjWedge->setEnabled(false);
    ui->chkVw->setEnabled(false);

    ui->lblStatus->setText(NOT_CONNECTED_TEXT);
}

void MainWindow::loadIcons()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/bens/Code/CoMapOvi_MapData", tr("CSV files (*.csv)"));
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList lineList;
        QTextStream stream(&file);

        while (!stream.atEnd())
        {
            QString line = stream.readLine();
            lineList.append(line);
        }

        mapWidget->addIcons(lineList);
    }
    else
    {
        qDebug() << "Can't open file " + fileName;
    }
}

void MainWindow::clearMapObjects()
{
    mapWidget->clearMapObjects();
}

void MainWindow::vwStateChanged(int state)
{
    if (state == Qt::Checked)
    {
        server->setVwEnabled(true);
    }
    else if (state == Qt::Unchecked)
    {
        server->setVwEnabled(false);
    }
}

void MainWindow::wedgeStateChanged(int state)
{
    if (state == Qt::Checked)
    {
        ui->chkObjWedge->setEnabled(true);
        ui->chkWedgePresses->setEnabled(true);
        ui->chkWedgeIcon->setEnabled(true);
    }
    else if (state == Qt::Unchecked)
    {
        ui->chkObjWedge->setChecked(false);
        ui->chkObjWedge->setEnabled(false);
        ui->chkWedgePresses->setChecked(false);
        ui->chkWedgePresses->setEnabled(false);
        ui->chkWedgeIcon->setChecked(false);
        ui->chkWedgeIcon->setEnabled(false);
    }

    server->setWedgeEnabled(ui->chkWedge->checkState(), ui->chkObjWedge->checkState());
}

void MainWindow::objWedgeStateChanged(int state)
{
    server->setWedgeEnabled(ui->chkWedge->checkState(), ui->chkObjWedge->checkState());
}

void MainWindow::globalButtonStateChanged(int state){
    if(state == Qt::Checked)
    {
        server->setGlobalButtonEnabled(true);
    }else if(state == Qt::Unchecked){
        server->setGlobalButtonEnabled(false);
    }
}

void MainWindow::wedgeIconsStateChanged(int state){
    if(state == Qt::Checked)
    {
        server->setWedgeIcons(true);
        ui->chkWedgePresses->setEnabled(true);
    }else if(state == Qt::Unchecked){
        server->setWedgeIcons(false);
        ui->chkWedgePresses->setEnabled(false);
        ui->chkWedgePresses->setChecked(false);
    }
}

void MainWindow::wedgeIconPressesStateChanged(int state){
    if(state == Qt::Checked){
        server->setWedgeIconPresses(true);
    }else if(state == Qt::Unchecked){
        server->setWedgeIconPresses(false);
    }
}

void MainWindow::statusSliderStateChanged(int state){
    if(state == Qt::Checked){
        server->setStatusSlider(true);
    }else if(state == Qt::Unchecked){
        server->setStatusSlider(false);
    }
}

void MainWindow::closeWindow(){

    stopServer();
    close();

}

bool MainWindow::getGlobalButtonSwitchState(){
    return ui->chkGlobalBtn->isChecked();
}

bool MainWindow::getSliderStatusSwitchState(){
    return ui->chkStatusSlider->isChecked();
}

