#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QList>
#include <qgeocoordinate.h>
#include "mappingwidget.h"

QTM_USE_NAMESPACE

class ClientConnection;

class TcpServer: public QTcpServer
{
    Q_OBJECT

public:
    static const int MAX_CLIENTS;
    static int clientIdCounter;

public:
    TcpServer(MappingWidget* mapWidget, QObject *parent = 0);
    ~TcpServer();

    QList<ClientConnection*>* getClientList();
    void removeClient(ClientConnection* client);
    void setVwEnabled(bool isEnabled);
    void setWedgeEnabled(bool isEnabled, bool objWedgeEnabled);

signals:

private slots:
    void connectClient();
    void updateClients(QString senderId);
    void updateClientDisconnect(QString senderId);

private:
    QList<ClientConnection*>* clientList;
    MappingWidget* mapWidget;
    bool vwEnabled;
    bool wedgeEnabled;
    bool objWedgeEnabled;
};

#endif // TCPSERVER_H
