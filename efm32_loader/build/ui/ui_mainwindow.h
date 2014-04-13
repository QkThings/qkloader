/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboPort;
    QPushButton *buttonReload;
    QPushButton *buttonConnect;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineFile;
    QPushButton *buttonBrowse;
    QPushButton *buttonUpload;
    QPlainTextEdit *textLog;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(493, 303);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        comboPort = new QComboBox(centralWidget);
        comboPort->setObjectName(QStringLiteral("comboPort"));

        horizontalLayout_2->addWidget(comboPort);

        buttonReload = new QPushButton(centralWidget);
        buttonReload->setObjectName(QStringLiteral("buttonReload"));

        horizontalLayout_2->addWidget(buttonReload);

        buttonConnect = new QPushButton(centralWidget);
        buttonConnect->setObjectName(QStringLiteral("buttonConnect"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonConnect->sizePolicy().hasHeightForWidth());
        buttonConnect->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(buttonConnect);


        formLayout->setLayout(0, QFormLayout::FieldRole, horizontalLayout_2);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineFile = new QLineEdit(centralWidget);
        lineFile->setObjectName(QStringLiteral("lineFile"));
        lineFile->setReadOnly(true);

        horizontalLayout->addWidget(lineFile);

        buttonBrowse = new QPushButton(centralWidget);
        buttonBrowse->setObjectName(QStringLiteral("buttonBrowse"));

        horizontalLayout->addWidget(buttonBrowse);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);


        verticalLayout->addLayout(formLayout);

        buttonUpload = new QPushButton(centralWidget);
        buttonUpload->setObjectName(QStringLiteral("buttonUpload"));

        verticalLayout->addWidget(buttonUpload);

        textLog = new QPlainTextEdit(centralWidget);
        textLog->setObjectName(QStringLiteral("textLog"));

        verticalLayout->addWidget(textLog);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Serial port", 0));
        buttonReload->setText(QApplication::translate("MainWindow", "Reload", 0));
        buttonConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        label_2->setText(QApplication::translate("MainWindow", "Binary file", 0));
        buttonBrowse->setText(QApplication::translate("MainWindow", "Browse...", 0));
        buttonUpload->setText(QApplication::translate("MainWindow", "Upload", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
