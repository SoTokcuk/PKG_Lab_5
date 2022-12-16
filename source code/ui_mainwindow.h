/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionadd;
    QAction *actionadd_Rectangle;
    QAction *actioncut_off;
    QAction *actionadd_polygon;
    QAction *actionpolygon_cut_off;
    QAction *actionadd_cutting_polynom;
    QAction *actionclear_polygons;
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QMenu *menumenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionadd = new QAction(MainWindow);
        actionadd->setObjectName(QString::fromUtf8("actionadd"));
        actionadd_Rectangle = new QAction(MainWindow);
        actionadd_Rectangle->setObjectName(QString::fromUtf8("actionadd_Rectangle"));
        actioncut_off = new QAction(MainWindow);
        actioncut_off->setObjectName(QString::fromUtf8("actioncut_off"));
        actionadd_polygon = new QAction(MainWindow);
        actionadd_polygon->setObjectName(QString::fromUtf8("actionadd_polygon"));
        actionpolygon_cut_off = new QAction(MainWindow);
        actionpolygon_cut_off->setObjectName(QString::fromUtf8("actionpolygon_cut_off"));
        actionadd_cutting_polynom = new QAction(MainWindow);
        actionadd_cutting_polynom->setObjectName(QString::fromUtf8("actionadd_cutting_polynom"));
        actionclear_polygons = new QAction(MainWindow);
        actionclear_polygons->setObjectName(QString::fromUtf8("actionclear_polygons"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 791, 551));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menumenu = new QMenu(menubar);
        menumenu->setObjectName(QString::fromUtf8("menumenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menumenu->menuAction());
        menumenu->addAction(actionadd);
        menumenu->addAction(actionadd_Rectangle);
        menumenu->addAction(actioncut_off);
        menumenu->addAction(actionadd_polygon);
        menumenu->addAction(actionadd_cutting_polynom);
        menumenu->addAction(actionpolygon_cut_off);
        menumenu->addAction(actionclear_polygons);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionadd->setText(QCoreApplication::translate("MainWindow", "add", nullptr));
        actionadd_Rectangle->setText(QCoreApplication::translate("MainWindow", "add Rectangle", nullptr));
        actioncut_off->setText(QCoreApplication::translate("MainWindow", "cut off", nullptr));
        actionadd_polygon->setText(QCoreApplication::translate("MainWindow", "add polygon ", nullptr));
        actionpolygon_cut_off->setText(QCoreApplication::translate("MainWindow", "polygon cut off", nullptr));
        actionadd_cutting_polynom->setText(QCoreApplication::translate("MainWindow", "add cutting polynom", nullptr));
        actionclear_polygons->setText(QCoreApplication::translate("MainWindow", "clear polygons", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        menumenu->setTitle(QCoreApplication::translate("MainWindow", "menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
