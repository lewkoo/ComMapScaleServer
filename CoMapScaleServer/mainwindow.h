#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"


class ClickWindow;
class MappingWidget;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static const QString NOT_CONNECTED_TEXT;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool getGlobalButtonSwitchState();
    bool getSliderStatusSwitchState();
    bool getSliderStatusInteractivitySwitchState();
    bool getWedgeInteractivity();
    bool getWedgeIconsState();

    void addMapWidget(MappingWidget* mapWidget);
    inline MappingWidget* getMapWidget() {return this->mapWidget;}


private slots:
    void startServer();
    void stopServer();
    void loadIcons();
    void clearMapObjects();
    void wedgeStateChanged(int state);
    void objWedgeStateChanged(int state);
    void vwStateChanged(int state);
    void globalButtonStateChanged(int state);
    void wedgeIconsStateChanged(int state);
    void wedgeIconPressesStateChanged(int state);
    void statusSliderStateChanged(int state);
    void closeWindow();
    void displayClick(QString clickData);

private:
    Ui::MainWindow *ui;
    TcpServer* server;
    MappingWidget* mapWidget;
    ClickWindow* clicks;
};

#endif // MAINWINDOW_H
