#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <qgeocoordinate.h>
#include <qgeoboundingbox.h>
#include <QTcpSocket>
#include <QPointF>
#include <vector>
#include <qgeomapobject.h>

using namespace std;

class ClientState;
class DataLogger;

QTM_USE_NAMESPACE

class ClientConnection : public QObject
{
    Q_OBJECT


public:
    explicit ClientConnection(QTcpSocket* socket, QString id, QObject *parent = 0);
    ~ClientConnection();

    void sendMessage(QString text);
    void logVw(QGeoCoordinate position, QGeoBoundingBox viewportBounds, qreal scale);
    void sendMapObjects(QList<QGeoMapObject*> mapObjects);
    void sendWedgeStatus(bool isEnabled, bool objWedgeEnabled);
    void sendGlobalButtonStatus(bool isEnabled);
    void sendWedgeIconsStatus(bool isEnabled);
    void sendWedgeIconsPresses(bool isEnabled);
    void sendStatusSlider(bool isEnabled);
    void sendStatusSliderInteractivity(bool isEnabled);

    inline void setClientState(ClientState* state) {clientState = state;}
    inline ClientState* getClientState() {return clientState;}
    inline QString getClientId() {return clientId;}

signals:
    void requestRepaint();
    void clientStateChanged(QString clientId);

private slots:
    void inDataReady();
    void disconnectClient();

private:
    void parseMessage(QString message);

private:
    quint16 blockSize;
    QTcpSocket* clientSocket;
    ClientState* clientState;
    QString clientId;
    DataLogger* logger;
    //vector<QPointF> locHist; //Location history. Stack of coordinates.
};

#endif // CLIENTCONNECTION_H
