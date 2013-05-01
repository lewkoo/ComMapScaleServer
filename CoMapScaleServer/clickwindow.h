#ifndef CLICKWINDOW_H
#define CLICKWINDOW_H

#include <QGroupBox>

namespace Ui {
class ClickWindow;
}

class ClickWindow : public QGroupBox
{
    Q_OBJECT
    
public:
    explicit ClickWindow(QWidget *parent = 0);

    void showGlobBut();
    void showWedgeBut();
    void showScaleBut();



    ~ClickWindow();
    
private:
    Ui::ClickWindow *ui;
    void sleepFor(int timeToWait);


};

#endif // CLICKWINDOW_H
