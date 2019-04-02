/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QCustomPlot *plot;
    QDoubleSpinBox *bx_x;
    QDoubleSpinBox *bx_y;
    QPushButton *btn_add;
    QPushButton *btn_clear;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btn_zoomFull;
    QPushButton *btn_GrahamScan;
    QPushButton *btn_KPS;
    QPushButton *btn_JarvisMarch;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(683, 635);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setGeometry(QRect(20, 20, 581, 391));
        bx_x = new QDoubleSpinBox(centralWidget);
        bx_x->setObjectName(QStringLiteral("bx_x"));
        bx_x->setGeometry(QRect(60, 460, 76, 27));
        bx_x->setSingleStep(0.1);
        bx_y = new QDoubleSpinBox(centralWidget);
        bx_y->setObjectName(QStringLiteral("bx_y"));
        bx_y->setGeometry(QRect(200, 460, 76, 27));
        bx_y->setSingleStep(0.1);
        btn_add = new QPushButton(centralWidget);
        btn_add->setObjectName(QStringLiteral("btn_add"));
        btn_add->setGeometry(QRect(330, 460, 96, 27));
        btn_clear = new QPushButton(centralWidget);
        btn_clear->setObjectName(QStringLiteral("btn_clear"));
        btn_clear->setGeometry(QRect(450, 460, 96, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 460, 74, 18));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 460, 74, 18));
        btn_zoomFull = new QPushButton(centralWidget);
        btn_zoomFull->setObjectName(QStringLiteral("btn_zoomFull"));
        btn_zoomFull->setGeometry(QRect(560, 460, 96, 27));
        btn_GrahamScan = new QPushButton(centralWidget);
        btn_GrahamScan->setObjectName(QStringLiteral("btn_GrahamScan"));
        btn_GrahamScan->setGeometry(QRect(20, 520, 181, 41));
        btn_KPS = new QPushButton(centralWidget);
        btn_KPS->setObjectName(QStringLiteral("btn_KPS"));
        btn_KPS->setGeometry(QRect(470, 520, 181, 41));
        btn_JarvisMarch = new QPushButton(centralWidget);
        btn_JarvisMarch->setObjectName(QStringLiteral("btn_JarvisMarch"));
        btn_JarvisMarch->setGeometry(QRect(260, 520, 151, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 683, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        btn_add->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        btn_clear->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "y", Q_NULLPTR));
        btn_zoomFull->setText(QApplication::translate("MainWindow", "Zoom Full", Q_NULLPTR));
        btn_GrahamScan->setText(QApplication::translate("MainWindow", "Run Graham's Scan", Q_NULLPTR));
        btn_KPS->setText(QApplication::translate("MainWindow", "Run Kirkpatrick Siedel", Q_NULLPTR));
        btn_JarvisMarch->setText(QApplication::translate("MainWindow", "Run Jarvis March", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
