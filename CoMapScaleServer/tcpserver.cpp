#include <QDebug>
#include <tcpserver.h>
#include <clientconnection.h>
#include "clientstate.h"
#include "mainwindow.h"

const int TcpServer::MAX_CLIENTS = 2;
int TcpServer::clientIdCounter = 0;

TcpServer::TcpServer(MappingWidget* mapWidget, MainWindow *parent)
  : QTcpServer(parent)
{
    this->mapWidget = mapWidget;
    this->parent = parent;
    clientList = new QList<ClientConnection*>;
    connect (this, SIGNAL(newConnection()), this, SLOT(connectClient()));
    vwEnabled = true;
    wedgeEnabled = true;
    objWedgeEnabled = false;
}

TcpServer::~TcpServer()
{
    while (!clientList->isEmpty())
    {
        ClientConnection* client = clientList->last();
        clientList->removeLast();

        if (client != NULL)
        {
            delete client;
            client = NULL;
        }
    }

    delete clientList;
    clientList = NULL;
}

void TcpServer::connectClient()
{
    //Make sure there is room for another client and the id number isn't in use;
    bool clientOk = true;
    bool idInUse = true;

    if (clientList->count() >= TcpServer::MAX_CLIENTS)
    {
        clientOk = false;
    }
    else
    {
        while (idInUse)
        {
            idInUse = false;

            for (int i = 0; i < clientList->count(); i++)
            {
                if (clientList->at(i)->getClientId().toInt() == TcpServer::clientIdCounter)
                {
                    idInUse = true;
                    break;
                }
            }

            if (idInUse)
            {
                TcpServer::clientIdCounter += 1;
                TcpServer::clientIdCounter %= TcpServer::MAX_CLIENTS;
            }
        }
    }

    if (clientOk)
    {
        QTcpSocket* socket = this->nextPendingConnection();
        QString clientId = QString::number(TcpServer::clientIdCounter);
        TcpServer::clientIdCounter += 1;
        TcpServer::clientIdCounter %= TcpServer::MAX_CLIENTS;
        ClientConnection* clientConnection = new ClientConnection(socket, clientId, this);

        ClientState* clientState = new ClientState(clientId);
        clientConnection->setClientState(clientState);
        clientList->push_back(clientConnection);

        //Add client widget to map
        MapMarker* marker = mapWidget->addNewPeer(clientId, clientState->getLastPosition());
        clientState->setMarker(marker); //Allows client to update marker position

        //Set client's id
        QString text = tr("id:%1").arg(clientId);
        clientConnection->sendMessage(text);

        QList<QGeoMapObject*> mapObjects = mapWidget->getMapObjects();
        clientConnection->sendMapObjects(mapObjects);
        clientConnection->sendWedgeStatus(this->wedgeEnabled, this->objWedgeEnabled);
        clientConnection->sendGlobalButtonStatus(parent->getGlobalButtonSwitchState());
        clientConnection->sendStatusSlider(parent->getSliderStatusSwitchState());

        qDebug()<<parent->getSliderStatusSwitchState();

        connect(clientConnection, SIGNAL(requestRepaint()), mapWidget, SLOT(update()));
        connect(clientConnection, SIGNAL(clientStateChanged(QString)), this, SLOT(updateClients(QString)));
    }
    else
    {
        qDebug() << "Client Rejected. Maximum number of connections are in use";
    }
}

QList<ClientConnection*>* TcpServer::getClientList()
{
    return this->clientList;
}

void TcpServer::removeClient(ClientConnection *client)
{
    QString senderId = client->getClientId();
    updateClientDisconnect(senderId);

    int index = clientList->indexOf(client);
    clientList->removeAt(index);

    if (client != NULL)
    {
        client->deleteLater();
    }
}

//void TcpServer::updateClientColour(QString clientId, QColor color)
//{
//    QString text = tr("col:%1").arg(color.name());

//    for (int i = 0; i < clientList->size(); i++)
//    {
//        ClientConnection* client = clientList->at(i);
//        if (client->getClientId().compare(clientId) == 0)
//        {
//            client->sendMessage(text);
//            break;
//        }
//    }
//}

void TcpServer::updateClientDisconnect(QString senderId)
{
    QString text = tr("id:%1,").arg(senderId);
    text += "dis";

    //Update all other clients
    for (int i = 0; i < clientList->size(); i++)
    {
        ClientConnection* client = clientList->at(i);
        if (client->getClientId().compare(senderId) != 0)
        {
            client->sendMessage(text);
        }
        else
        {
            //Remove map marker
            MapMarker* marker = client->getClientState()->getMarker();
            mapWidget->removeMapMarker(marker);
        }
    }  
}

void TcpServer::updateClients(QString senderId)
{
    QGeoCoordinate clientPos, vwPos;
    int clientScale;
    QString text;
    QString vwText;
    ClientState* clientState;
    ClientConnection* client;

    //Find client with senderId
    for (int i = 0; i < clientList->size(); i++)
    {
        client = clientList->at(i);
        if (client->getClientId().compare(senderId) == 0)
        {
            clientState = client->getClientState();
            clientPos = clientState->getLastPosition();
            clientScale = clientState->getVwZoomLevel();

            text = tr("id:%1,").arg(client->getClientId());
            text += tr("lat:%1,").arg(clientPos.latitude(), 0, 'f', 5) + tr("lon:%1,").arg(clientPos.longitude(), 0, 'f', 5);
            text += tr("scale:%1,").arg(clientScale);

            break;
        }
    }

    //Create visit wares
    if (vwEnabled && clientState->isVwReady())
    {
        vwPos = clientState->getVwPosition();
        qreal distToClosestVw = mapWidget->getClosestVw(vwPos);

        if (distToClosestVw > ClientState::VW_MIN_DIST)
        {
            QString clientId = client->getClientId();
            vwText = tr("id:%1,").arg(clientId);
            vwText += tr("vwLat:%1,").arg(vwPos.latitude(), 0, 'f', 5) + tr("vwLon:%1").arg(vwPos.longitude(), 0, 'f', 5);
            client->logVw(vwPos, clientState->getVwBox(), clientState->getVwZoomLevel());
            MapMarker::MarkerType markerType = ClientState::getVwMarkerTypeById(clientId);
            mapWidget->addMapMarker(markerType, vwPos);
        }
        clientState->resetVw();
    }

    //Update all other clients
    for (int i = 0; i < clientList->size(); i++)
    {
        ClientConnection* client = clientList->at(i);
        if (client->getClientId().compare(senderId) != 0)
        {
            if (wedgeEnabled)
            {
                client->sendMessage(text);
            }
        }
//        else
//        {
//            qDebug() << "Failed to locate other client. SenderId:" << senderId << ", clientId:"<< client->getClientId();
//        }

        //Send vw message to all clients
        if (!vwText.isNull())
        {
            client->sendMessage(vwText);
        }
    }
}

void TcpServer::setVwEnabled(bool isEnabled)
{
    this->vwEnabled = isEnabled;
}

void TcpServer::setWedgeEnabled(bool isEnabled, bool objWedgeEnabled)
{
    this->wedgeEnabled = isEnabled;
    this->objWedgeEnabled = objWedgeEnabled;

    if (clientList != NULL)
    {
        for (int i = 0; i < this->clientList->count(); i++)
        {
            clientList->at(i)->sendWedgeStatus(this->wedgeEnabled, this->objWedgeEnabled);
        }
    }
}

void TcpServer::setGlobalButtonEnabled(bool isEnabled){
    if (clientList != NULL)
    {
        for (int i = 0; i < this->clientList->count(); i++)
        {
            clientList->at(i)->sendGlobalButtonStatus(isEnabled);
        }
    }
}

void TcpServer::setWedgeIcons(bool isEnabled){
    if (clientList != NULL)
    {
        for (int i = 0; i < this->clientList->count(); i++)
        {
            clientList->at(i)->sendWedgeIconsStatus(isEnabled);
        }
    }
}

void TcpServer::setWedgeIconPresses(bool isEnabled){
    if (clientList != NULL)
    {
        for (int i = 0; i < this->clientList->count(); i++)
        {
            clientList->at(i)->sendWedgeIconsPresses(isEnabled);
        }
    }
}

void TcpServer::setStatusSlider(bool isEnabled){
    if (clientList != NULL)
    {
        for (int i = 0; i < this->clientList->count(); i++)
        {
            clientList->at(i)->sendStatusSlider(isEnabled);
        }
    }
}

