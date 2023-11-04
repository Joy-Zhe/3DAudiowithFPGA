/********************************************************************************
** Form generated from reading UI file 'pcie_memory_rw.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PCIE_MEMORY_RW_H
#define UI_PCIE_MEMORY_RW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pcie_memory_rw
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnClrRcv;
    QPushButton *btnSnd;
    QTextBrowser *txtBro;
    QPlainTextEdit *txtEdit;
    QPushButton *btnClrSnd;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pcie_memory_rw)
    {
        if (pcie_memory_rw->objectName().isEmpty())
            pcie_memory_rw->setObjectName("pcie_memory_rw");
        pcie_memory_rw->resize(804, 809);
        centralwidget = new QWidget(pcie_memory_rw);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(410, 20, 61, 20));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 20, 61, 20));
        btnClrRcv = new QPushButton(centralwidget);
        btnClrRcv->setObjectName("btnClrRcv");
        btnClrRcv->setGeometry(QRect(20, 710, 91, 31));
        btnSnd = new QPushButton(centralwidget);
        btnSnd->setObjectName("btnSnd");
        btnSnd->setGeometry(QRect(690, 710, 91, 31));
        txtBro = new QTextBrowser(centralwidget);
        txtBro->setObjectName("txtBro");
        txtBro->setGeometry(QRect(410, 50, 371, 241));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(12);
        txtBro->setFont(font);
        txtEdit = new QPlainTextEdit(centralwidget);
        txtEdit->setObjectName("txtEdit");
        txtEdit->setGeometry(QRect(20, 50, 351, 241));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Microsoft YaHei")});
        font1.setPointSize(12);
        txtEdit->setFont(font1);
        btnClrSnd = new QPushButton(centralwidget);
        btnClrSnd->setObjectName("btnClrSnd");
        btnClrSnd->setGeometry(QRect(120, 710, 91, 31));
        xSlider = new QSlider(centralwidget);
        xSlider->setObjectName("xSlider");
        xSlider->setGeometry(QRect(80, 350, 160, 16));
        xSlider->setOrientation(Qt::Horizontal);
        ySlider = new QSlider(centralwidget);
        ySlider->setObjectName("ySlider");
        ySlider->setGeometry(QRect(80, 410, 160, 16));
        ySlider->setOrientation(Qt::Horizontal);
        zSlider = new QSlider(centralwidget);
        zSlider->setObjectName("zSlider");
        zSlider->setGeometry(QRect(80, 470, 160, 16));
        zSlider->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 350, 31, 16));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 410, 21, 16));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 470, 21, 16));
        pcie_memory_rw->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pcie_memory_rw);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 804, 21));
        pcie_memory_rw->setMenuBar(menubar);
        statusbar = new QStatusBar(pcie_memory_rw);
        statusbar->setObjectName("statusbar");
        pcie_memory_rw->setStatusBar(statusbar);

        retranslateUi(pcie_memory_rw);
        QObject::connect(btnClrRcv, &QPushButton::clicked, txtBro, qOverload<>(&QTextBrowser::clear));
        QObject::connect(btnClrSnd, &QPushButton::clicked, txtEdit, qOverload<>(&QPlainTextEdit::clear));

        QMetaObject::connectSlotsByName(pcie_memory_rw);
    } // setupUi

    void retranslateUi(QMainWindow *pcie_memory_rw)
    {
        pcie_memory_rw->setWindowTitle(QCoreApplication::translate("pcie_memory_rw", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("pcie_memory_rw", "\346\216\245\346\224\266\347\252\227\345\217\243", nullptr));
        label_2->setText(QCoreApplication::translate("pcie_memory_rw", "\345\217\221\351\200\201\347\252\227\345\217\243", nullptr));
        btnClrRcv->setText(QCoreApplication::translate("pcie_memory_rw", "\346\270\205\347\251\272\346\216\245\346\224\266\342\206\221", nullptr));
        btnSnd->setText(QCoreApplication::translate("pcie_memory_rw", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        btnClrSnd->setText(QCoreApplication::translate("pcie_memory_rw", "\346\270\205\347\251\272\345\217\221\351\200\201\342\206\223", nullptr));
        label_3->setText(QCoreApplication::translate("pcie_memory_rw", "x", nullptr));
        label_4->setText(QCoreApplication::translate("pcie_memory_rw", "y", nullptr));
        label_5->setText(QCoreApplication::translate("pcie_memory_rw", "z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pcie_memory_rw: public Ui_pcie_memory_rw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PCIE_MEMORY_RW_H
