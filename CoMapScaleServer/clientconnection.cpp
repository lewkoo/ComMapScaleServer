#include <iostream>
#include <QStringList>
#include "clientconnection.h"
#include "clientstate.h"
#include "tcpserver.h"
#include "datalogger.h"

using namespace std;

ClientConnection::ClientConnection(QTcpSocket* socket, QString id, QObject *parent) :
    QObject(parent), blockSize(0), clientSocket(socket)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(inDataReady()));
    connect (socket, SIGNAL(disconnected()), this, SLOT(disconnectClient()));
    this->clientId = id;

    logger = new DataLogger(id);
}

ClientConnection::~ClientConnection()
{
    if (clientSocket != NULL)
    {
        delete clientSocket;
    }

    if (clientState != NULL)
    {
        delete clientState;
    }

    if (logger != NULL)
    {
        logger->closeFiles();
        delete logger;
    }
}

void ClientConnection::disconnectClient()
{
    ((TcpServer*)parent())->removeClient(this);
    clientSocket->deleteLater();
    clientSocket = NULL;
}

void ClientConnection::inDataReady()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_4_0);
    int bytes;

    bytes = clientSocket->bytesAvailable();

    while (bytes > 0)
    {
        bytes = clientSocket->bytesAvailable();
        if (bytes >= (int)sizeof(quint16))
        {
            if (blockSize == 0)
            {
                in >> blockSize;
            }

            bytes = clientSocket->bytesAvailable();
            if (bytes >= blockSize)
            {
                QString text;
                in >> text;
                parseMessage(text);
                blockSize = 0;
            }
            else
            {
                qDebug() << "Too many bytes available";
            }
        }
        else
        {
            qDebug() << "Insufficient bytes available";
        }

        bytes = clientSocket->bytesAvailable();
    }
}

void ClientConnection::parseMessage(QString message)
{
    QStringList elements = message.split(',');

    bool parseOK = true;
    int id = 0;
    float lat = 0;
    float lon = 0;
    float topLeftLat = 0;
    float topLeftLon = 0;
    float botRightLat = 0;
    float botRightLon = 0;
    qreal scale = 0;
    QString clickInfo = NULL;


    for (int i = 0; i < elements.size(); i++)
    {
        QString pair = elements.at(i);

//        if (pair.startsWith("id"))
//        {
//            QString idString = pair.remove(0, 3);
//            id = idString.toInt(&parseOK);

//            if (!parseOK)
//            {
//                qDebug() << "Problem parsing id";
//            }
//        }
//        else
        if (pair.startsWith("lat"))    //Current position latitude
        {
            QString latString = pair.remove(0, 4);
            lat = latString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lat";
            }
        }
        else if (pair.startsWith("lon"))    //Position longitude
        {
            QString lonString = pair.remove(0, 4);
            lon = lonString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lon";
            }

        }
        else if (pair.startsWith("tllat"))  //Top left latitude
        {
            QString latString = pair.remove(0, 6);
            topLeftLat = latString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lon";
            }

        }
        else if (pair.startsWith("tllon"))  //Top left longitude
        {
            QString lonString = pair.remove(0, 6);
            topLeftLon = lonString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lon";
            }

        }
        else if (pair.startsWith("brlat"))  //Bottom right latitude
        {
            QString latString = pair.remove(0, 6);
            botRightLat = latString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing lon";
            }

        }
        else if (pair.startsWith("brlon"))  //Bottom right longitude
        {
            QString lonString = pair.remove(0, 6);
            botRightLon = lonString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing brlon";
            }

        }
        else if (pair.startsWith("scale"))  //zoom level
        {
            QString scaleString = pair.remove(0, 6);
            scale = scaleString.toFloat(&parseOK);

            if (!parseOK)
            {
                qDebug() << "Problem parsing scale";
            }

        }else if (pair.startsWith("click"))//icon click
        {
            clickInfo = pair.remove(0,6);
        }
        else
            qDebug() << "Unrecognized message element: " << pair;

    }

    if (parseOK)
    {
        QGeoCoordinate location(lat, lon);
        QGeoCoordinate topLeft(topLeftLat, topLeftLon);
        QGeoCoordinate bottomRight(botRightLat, botRightLon);
        QGeoBoundingBox box(topLeft, bottomRight);
        //locHist.push_back(location);

        QTime time = QDateTime::currentDateTime().time();

        clientState->setLastPosition(location, box, scale, time);
        clientState->setLastBox(box);
        clientState->setZoomLevel(scale);

        //Repaint if location or scale update has been sent.
        if (lat != 0 || lon != 0 || scale != 0)
        {
            emit requestRepaint();
            emit clientStateChanged(this->clientId);

            logger->writePos(time.toString("hh:mm:ss.zzz"), QString::number(lat), QString::number(lon), QString::number(topLeftLat), QString::number(topLeftLon),
                          QString::number(botRightLat), QString::number(botRightLon), QString::number(scale));
        }


        //Write if any click info received

        if(clickInfo != NULL){
            logger->writeClick(time.toString("hh:mm:ss,zzz"), clickInfo);
        }


        //qDebug() << "Received update: " << message;
    }
    else
    {
        qDebug() << "Failed to parse incoming message: " << message;
    }
}

void ClientConnection::sendMessage(QString text)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << text;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    //qDebug() << "Sending message: " << text;

    clientSocket->write(block);
}

void ClientConnection::logVw(QGeoCoordinate position, QGeoBoundingBox viewportBounds, qreal scale)
{
    QTime time = QDateTime::currentDateTime().time();
    logger->writeVw(time.toString("hh:mm:ss.zzz"), QString::number(position.latitude()), QString::number(position.longitude()),
                    QString::number(viewportBounds.topLeft().latitude()), QString::number(viewportBounds.topLeft().longitude()),
                    QString::number(viewportBounds.bottomRight().latitude()), QString::number(viewportBounds.bottomRight().longitude()),
                    QString::number(scale));
}

void ClientConnection::sendMapObjects(QList<QGeoMapObject *> mapObjects)
{
    foreach (QGeoMapObject* object, mapObjects)
    {
        MapMarker* mapMarker = dynamic_cast<MapMarker*>(object);

        if (mapMarker != NULL)
        {
            MapMarker::MarkerType objectType = mapMarker->markerType();

            if (objectType != MapMarker::PeerType &&
                    objectType != MapMarker::PeerOrangeType &&
                    objectType != MapMarker::PeerPurpleType &&
                    objectType != MapMarker::PeerRedType &&
                    objectType != MapMarker::PeerBlueType)
            {
                QString text;

                switch (objectType)
                {
                case MapMarker::AnchorRedType:
                    text = tr("id:0,") +
                            tr("vwLat:%1,").arg(mapMarker->coordinate().latitude()) +
                            tr("vwLon:%1").arg(mapMarker->coordinate().longitude());
                    break;
                case MapMarker::AnchorBlueType:
                    text = tr("id:1,") +
                            tr("vwLat:%1,").arg(mapMarker->coordinate().latitude()) +
                            tr("vwLon:%1").arg(mapMarker->coordinate().longitude());
                    break;
                case MapMarker::RestaurantType:
                    text = tr("res,") +
                            tr("lat:%1,").arg(mapMarker->coordinate().latitude()) +
                            tr("lon:%1,").arg(mapMarker->coordinate().longitude()) +
                            tr("txt:%1").arg(mapMarker->getText());
                    break;
                case MapMarker::HotelType:
                    text = tr("hot,") +
                            tr("lat:%1,").arg(mapMarker->coordinate().latitude()) +
                            tr("lon:%1,").arg(mapMarker->coordinate().longitude()) +
                            tr("txt:%1").arg(mapMarker->getText());
                    break;
                }

                sendMessage(text);
            }
        }
    }
}

void ClientConnection::sendWedgeStatus(bool isEnabled, bool objWedgeEnabled)
{
    QString text;

    if (isEnabled)
    {
        text = tr("wedge,");

        if (objWedgeEnabled)
        {
            text += tr("objw");
        }
        else
        {
            text += tr("noobjw");
        }
    }
    else
    {
        text = tr("nowedge");
    }

    sendMessage(text);
}
