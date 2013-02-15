#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>
#include <QColor>
#include <QTime>
#include "mapmarker.h"

QTM_USE_NAMESPACE



class ClientState
{
public:
    //A visit wear is dropped if client doesn't travel more than VW_DIST within VW_TIME
    static const qreal VW_DIST; //In metres
    static const qreal VW_TIME; //In ms
    static const qreal VW_MIN_DIST; //Minimum distance between two visit wares.
    static const qreal VW_MIN_ZOOM_LEVEL;//Minimum zoom level for a visit ware to be dropped.

public:
    ClientState(QString clientId);
    ~ClientState();

    inline void setLastBox(QGeoBoundingBox box) {lastBox = box;}
    inline QGeoBoundingBox getLastBox() {return lastBox;}
    void setLastPosition(QGeoCoordinate coordinate, QGeoBoundingBox box, qreal scale, QTime time);
    inline QGeoCoordinate getLastPosition() {return lastPosition;}
    inline QGeoCoordinate getVwPosition() {return vwPosition;}
    inline QGeoBoundingBox getVwBox() {return vwBox;}
    inline qreal getVwZoomLevel() {return vwZoomLevel;}
    inline void setZoomLevel(qreal zoomLevel) {this->zoomLevel = zoomLevel;}
    inline qreal getZoomLevel() {return zoomLevel;}
    inline QColor getColour() {return colour; }
    inline bool isVwReady() {return vwReady; }
    inline void resetVw() {vwReady = false;}    
    inline void setMarker(MapMarker* peerMarker) {marker = peerMarker;}
    inline MapMarker* getMarker() {return marker;}

    static QColor getColorById(QString clientId);
    static MapMarker::MarkerType getMarkerTypeById(QString clientId);
    static MapMarker::MarkerType getVwMarkerTypeById(QString clientId);

private:
    QGeoCoordinate lastPosition;
    QTime lastPosTime;
    QGeoCoordinate vwPosition;  //Used to track when a visit ware should be dropped
    QGeoBoundingBox vwBox;      //Viewport bounds at time when vwPosition is recorded
    qreal vwZoomLevel;          //Zoom level when vwPosition is recorded
    QTime vwPosTime;
    QGeoBoundingBox lastBox;
    qreal zoomLevel;
    bool vwReady; //When true, set visit wear for this client.

    QColor colour;
    MapMarker* marker;   //Handle to map marker (managed by map object)
};

#endif // CLIENTSTATE_H
