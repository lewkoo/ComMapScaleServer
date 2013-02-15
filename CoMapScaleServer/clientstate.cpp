#include "clientstate.h"

const qreal ClientState::VW_DIST = 1000;
const qreal ClientState::VW_TIME = 5000;
const qreal ClientState::VW_MIN_DIST = VW_DIST;
const qreal ClientState::VW_MIN_ZOOM_LEVEL = 14;

ClientState::ClientState(QString clientId)
{
    lastPosition = QGeoCoordinate(48.854716, 2.346611);
    lastBox = QGeoBoundingBox(lastPosition, 4, 2);
    lastPosTime = QTime::currentTime();
    zoomLevel = 12;

    vwPosition = lastPosition;
    vwBox = lastBox;
    vwPosTime = lastPosTime;
    vwZoomLevel = zoomLevel;

    this->colour = ClientState::getColorById(clientId);
    vwReady = false;
}

ClientState::~ClientState()
{
}

//Static method
QColor ClientState::getColorById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    QColor colour;

    switch (id)
    {
    case 0:
        colour = QColor("red");
        break;
    case 1:
        colour = QColor("blue");
        break;
    default:
        colour = QColor("black");
    }

    return colour;
}

//Static method
MapMarker::MarkerType ClientState::getMarkerTypeById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    MapMarker::MarkerType markerType;

    switch (id)
    {
    case 0:
        markerType = MapMarker::PeerRedType;
        break;
    case 1:
        markerType = MapMarker::PeerBlueType;
        break;
    default:

        markerType = MapMarker::PeerType;
    }

    return markerType;
}

MapMarker::MarkerType ClientState::getVwMarkerTypeById(QString clientId)
{
    //Assume id is an integer.
    int id = clientId.toInt();
    MapMarker::MarkerType markerType;

    switch (id)
    {
    case 0:
        markerType = MapMarker::AnchorRedType;
        break;
    case 1:
        markerType = MapMarker::AnchorBlueType;
        break;
    default:

        markerType = MapMarker::AnchorType;
    }

    return markerType;
}

void ClientState::setLastPosition(QGeoCoordinate coordinate, QGeoBoundingBox box, qreal scale, QTime time)
{
    qreal distance = vwPosition.distanceTo(coordinate);   // in metres

    if (distance > VW_DIST)
    {
        //Reset last position
        vwPosition = coordinate;
        vwBox = box;
        vwZoomLevel = scale;
        vwPosTime = time;
    }
    else
    {
        int timeDiff = vwPosTime.msecsTo(time);               // in ms

        if (timeDiff > VW_TIME && zoomLevel >= ClientState::VW_MIN_ZOOM_LEVEL)
        {
            //Send visit wear to other clients.
            vwReady = true;
        }
    }

    //prevPosition = lastPosition;
    //prevPosTime = lastPosTime;
    lastPosition = coordinate;
    lastPosTime = time;
    marker->setCoordinate(coordinate);
}
