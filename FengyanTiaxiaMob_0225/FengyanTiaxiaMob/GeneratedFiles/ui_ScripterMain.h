/********************************************************************************
** Form generated from reading UI file 'ScripterMain.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPTERMAIN_H
#define UI_SCRIPTERMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScripterMainClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *unBindBtn;
    QLabel *label_2;
    QLineEdit *chongzhiLine;
    QPushButton *chongzhiBtn;
    QLabel *label_3;
    QComboBox *modeComboBox;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ScripterMainClass)
    {
        if (ScripterMainClass->objectName().isEmpty())
            ScripterMainClass->setObjectName(QStringLiteral("ScripterMainClass"));
        ScripterMainClass->resize(471, 305);
        centralWidget = new QWidget(ScripterMainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 120, 75, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 80, 54, 12));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(110, 80, 321, 20));
        unBindBtn = new QPushButton(centralWidget);
        unBindBtn->setObjectName(QStringLiteral("unBindBtn"));
        unBindBtn->setGeometry(QRect(260, 120, 75, 23));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 170, 54, 16));
        chongzhiLine = new QLineEdit(centralWidget);
        chongzhiLine->setObjectName(QStringLiteral("chongzhiLine"));
        chongzhiLine->setGeometry(QRect(110, 170, 321, 20));
        chongzhiBtn = new QPushButton(centralWidget);
        chongzhiBtn->setObjectName(QStringLiteral("chongzhiBtn"));
        chongzhiBtn->setGeometry(QRect(220, 200, 75, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 40, 54, 20));
        modeComboBox = new QComboBox(centralWidget);
        modeComboBox->setObjectName(QStringLiteral("modeComboBox"));
        modeComboBox->setGeometry(QRect(110, 40, 111, 22));
        ScripterMainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ScripterMainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 471, 23));
        ScripterMainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ScripterMainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ScripterMainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ScripterMainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ScripterMainClass->setStatusBar(statusBar);

        retranslateUi(ScripterMainClass);
        QObject::connect(pushButton, SIGNAL(clicked()), ScripterMainClass, SLOT(enterBtnClicked()));

        QMetaObject::connectSlotsByName(ScripterMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *ScripterMainClass)
    {
        ScripterMainClass->setWindowTitle(QApplication::translate("ScripterMainClass", "QQ", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ScripterMainClass", "Enter", Q_NULLPTR));
        label->setText(QApplication::translate("ScripterMainClass", "\346\263\250\345\206\214\347\240\201\357\274\232", Q_NULLPTR));
        unBindBtn->setText(QApplication::translate("ScripterMainClass", "\350\247\243\347\273\221\346\214\211\351\222\256", Q_NULLPTR));
        label_2->setText(QApplication::translate("ScripterMainClass", "\345\205\205\345\200\274\357\274\232", Q_NULLPTR));
        chongzhiBtn->setText(QApplication::translate("ScripterMainClass", "\345\205\205\345\200\274\346\214\211\351\222\256", Q_NULLPTR));
        label_3->setText(QApplication::translate("ScripterMainClass", "\347\211\210\346\234\254\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ScripterMainClass: public Ui_ScripterMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPTERMAIN_H
