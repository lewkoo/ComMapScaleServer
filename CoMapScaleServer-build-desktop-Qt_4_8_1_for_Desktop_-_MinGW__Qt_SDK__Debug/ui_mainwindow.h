/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Feb 14 23:03:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btnConnect;
    QLabel *lblStatus;
    QPushButton *btnDisconnect;
    QPushButton *btnQuit;
    QPushButton *btnLoad;
    QPushButton *btnClear;
    QCheckBox *chkWedge;
    QCheckBox *chkVw;
    QCheckBox *chkObjWedge;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(825, 506);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btnConnect = new QPushButton(centralWidget);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setGeometry(QRect(10, 10, 91, 24));
        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(30, 80, 311, 101));
        btnDisconnect = new QPushButton(centralWidget);
        btnDisconnect->setObjectName(QString::fromUtf8("btnDisconnect"));
        btnDisconnect->setGeometry(QRect(10, 40, 91, 24));
        btnQuit = new QPushButton(centralWidget);
        btnQuit->setObjectName(QString::fromUtf8("btnQuit"));
        btnQuit->setGeometry(QRect(10, 430, 91, 24));
        btnLoad = new QPushButton(centralWidget);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));
        btnLoad->setGeometry(QRect(10, 290, 91, 24));
        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        btnClear->setGeometry(QRect(10, 260, 91, 24));
        chkWedge = new QCheckBox(centralWidget);
        chkWedge->setObjectName(QString::fromUtf8("chkWedge"));
        chkWedge->setEnabled(false);
        chkWedge->setGeometry(QRect(10, 200, 91, 21));
        chkWedge->setChecked(true);
        chkVw = new QCheckBox(centralWidget);
        chkVw->setObjectName(QString::fromUtf8("chkVw"));
        chkVw->setEnabled(false);
        chkVw->setGeometry(QRect(10, 170, 79, 21));
        chkVw->setCheckable(true);
        chkVw->setChecked(true);
        chkObjWedge = new QCheckBox(centralWidget);
        chkObjWedge->setObjectName(QString::fromUtf8("chkObjWedge"));
        chkObjWedge->setEnabled(false);
        chkObjWedge->setGeometry(QRect(10, 230, 121, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 825, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btnConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QString());
        btnDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        btnQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        btnLoad->setText(QApplication::translate("MainWindow", "Load Icons", 0, QApplication::UnicodeUTF8));
        btnClear->setText(QApplication::translate("MainWindow", "Clear Map", 0, QApplication::UnicodeUTF8));
        chkWedge->setText(QApplication::translate("MainWindow", "Wedge", 0, QApplication::UnicodeUTF8));
        chkVw->setText(QApplication::translate("MainWindow", "Visit Wear", 0, QApplication::UnicodeUTF8));
        chkObjWedge->setText(QApplication::translate("MainWindow", "Object Wedges", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
