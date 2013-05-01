/********************************************************************************
** Form generated from reading UI file 'clickwindow.ui'
**
** Created: Tue Apr 30 20:13:21 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLICKWINDOW_H
#define UI_CLICKWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ClickWindow
{
public:
    QSpinBox *globButCount;
    QSpinBox *wedgePresCount;
    QSpinBox *scaleButCount;
    QLabel *globBut;
    QLabel *wedgeBut;
    QLabel *scaleBut;

    void setupUi(QGroupBox *ClickWindow)
    {
        if (ClickWindow->objectName().isEmpty())
            ClickWindow->setObjectName(QString::fromUtf8("ClickWindow"));
        ClickWindow->resize(196, 376);
        ClickWindow->setFlat(false);
        ClickWindow->setCheckable(false);
        globButCount = new QSpinBox(ClickWindow);
        globButCount->setObjectName(QString::fromUtf8("globButCount"));
        globButCount->setEnabled(false);
        globButCount->setGeometry(QRect(110, 30, 61, 22));
        globButCount->setAutoFillBackground(false);
        globButCount->setWrapping(true);
        globButCount->setReadOnly(true);
        globButCount->setMaximum(999999);
        wedgePresCount = new QSpinBox(ClickWindow);
        wedgePresCount->setObjectName(QString::fromUtf8("wedgePresCount"));
        wedgePresCount->setEnabled(false);
        wedgePresCount->setGeometry(QRect(110, 140, 61, 22));
        wedgePresCount->setAutoFillBackground(false);
        wedgePresCount->setWrapping(true);
        wedgePresCount->setReadOnly(true);
        wedgePresCount->setMaximum(999999);
        scaleButCount = new QSpinBox(ClickWindow);
        scaleButCount->setObjectName(QString::fromUtf8("scaleButCount"));
        scaleButCount->setEnabled(false);
        scaleButCount->setGeometry(QRect(110, 250, 61, 22));
        scaleButCount->setAutoFillBackground(false);
        scaleButCount->setWrapping(true);
        scaleButCount->setReadOnly(true);
        scaleButCount->setMaximum(999999);
        globBut = new QLabel(ClickWindow);
        globBut->setObjectName(QString::fromUtf8("globBut"));
        globBut->setGeometry(QRect(10, 30, 81, 81));
        wedgeBut = new QLabel(ClickWindow);
        wedgeBut->setObjectName(QString::fromUtf8("wedgeBut"));
        wedgeBut->setGeometry(QRect(10, 140, 81, 81));
        scaleBut = new QLabel(ClickWindow);
        scaleBut->setObjectName(QString::fromUtf8("scaleBut"));
        scaleBut->setGeometry(QRect(10, 250, 81, 81));

        retranslateUi(ClickWindow);

        QMetaObject::connectSlotsByName(ClickWindow);
    } // setupUi

    void retranslateUi(QGroupBox *ClickWindow)
    {
        ClickWindow->setWindowTitle(QApplication::translate("ClickWindow", "Click output", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ClickWindow->setToolTip(QApplication::translate("ClickWindow", "Displays the information about clicks in real time", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ClickWindow->setTitle(QApplication::translate("ClickWindow", "Red user", 0, QApplication::UnicodeUTF8));
        globBut->setText(QString());
        wedgeBut->setText(QString());
        scaleBut->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ClickWindow: public Ui_ClickWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLICKWINDOW_H
