#ifndef MAPPINGWIDGET_H
#define MAPPINGWIDGET_H

#include <QWidget>
//#include <QGeoMappingManager>
#include "qgeomappingmanager.h"
//#include "clientstate.h"
#include "mapmarker.h"


QTM_USE_NAMESPACE

class GeoMap;
class QGraphicsView;
class ZoomButtonItem;
class ClientConnection;

class MappingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MappingWidget(QWidget *parent = 0);
    ~MappingWidget ();

    //void resizeEvent(QResizeEvent *event);
    //void mapPositionChanged(QGeoCoordinate coordinate);
    void setClientList (QList<ClientConnection*>* list);

    inline QList<ClientConnection*>* getClientList() {return clientList;}

    MapMarker* addNewPeer(QString clientId, QGeoCoordinate coordinate);
    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location);
    MapMarker* addMapMarker(MapMarker::MarkerType markerType, QGeoCoordinate location, QString text);
    qreal getClosestVw(QGeoCoordinate location);
    void removeMapMarker(MapMarker* marker);
    void clearMapObjects();
    QList<QGeoMapObject*> getMapObjects();

    void addIcons(QStringList iconList);
    void addIcon(QString lineItem);

protected: //events
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void initialize (QGeoMappingManager* mapManager);


private:
    GeoMap* map;
    QGraphicsView* view;
    ZoomButtonItem* zoomButton;
    QList<ClientConnection*>* clientList;
};

#endif // MAPPINGWIDGET_H
