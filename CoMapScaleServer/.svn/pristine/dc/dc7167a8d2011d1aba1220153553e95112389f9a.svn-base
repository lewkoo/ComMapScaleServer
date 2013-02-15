#include <QtGui/QApplication>
#include "mainwindow.h"
#include <qgeoserviceprovider.h>
#include "mappingwidget.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    MappingWidget mapWidget;
    //mapWidget.showMaximized();

    QGeoServiceProvider serviceProvider ("nokia");

    if (serviceProvider.error() == QGeoServiceProvider::NoError)
    {
        mapWidget.initialize(serviceProvider.mappingManager());
    }
    else
    {
        qDebug() << "Service provider error: " << serviceProvider.errorString();
    }

    w.addMapWidget(&mapWidget);
    w.showMaximized();

    return a.exec();
}
