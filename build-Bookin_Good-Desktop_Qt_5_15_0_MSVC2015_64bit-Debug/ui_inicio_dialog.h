/********************************************************************************
** Form generated from reading UI file 'inicio_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INICIO_DIALOG_H
#define UI_INICIO_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_inicio_dialog
{
public:
    QLabel *label;
    QLineEdit *usuario_LE;
    QLineEdit *contra_LE;
    QPushButton *iniciar_PB;
    QPushButton *registrar_PB;

    void setupUi(QDialog *inicio_dialog)
    {
        if (inicio_dialog->objectName().isEmpty())
            inicio_dialog->setObjectName(QString::fromUtf8("inicio_dialog"));
        inicio_dialog->resize(396, 324);
        label = new QLabel(inicio_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 30, 47, 13));
        usuario_LE = new QLineEdit(inicio_dialog);
        usuario_LE->setObjectName(QString::fromUtf8("usuario_LE"));
        usuario_LE->setGeometry(QRect(100, 80, 211, 20));
        contra_LE = new QLineEdit(inicio_dialog);
        contra_LE->setObjectName(QString::fromUtf8("contra_LE"));
        contra_LE->setGeometry(QRect(100, 110, 211, 20));
        contra_LE->setEchoMode(QLineEdit::Password);
        iniciar_PB = new QPushButton(inicio_dialog);
        iniciar_PB->setObjectName(QString::fromUtf8("iniciar_PB"));
        iniciar_PB->setGeometry(QRect(100, 140, 211, 23));
        registrar_PB = new QPushButton(inicio_dialog);
        registrar_PB->setObjectName(QString::fromUtf8("registrar_PB"));
        registrar_PB->setGeometry(QRect(100, 230, 211, 23));

        retranslateUi(inicio_dialog);

        QMetaObject::connectSlotsByName(inicio_dialog);
    } // setupUi

    void retranslateUi(QDialog *inicio_dialog)
    {
        inicio_dialog->setWindowTitle(QCoreApplication::translate("inicio_dialog", "inicio_dialog", nullptr));
        label->setText(QCoreApplication::translate("inicio_dialog", "Bookin", nullptr));
        iniciar_PB->setText(QCoreApplication::translate("inicio_dialog", "Iniciar sesi\303\263n", nullptr));
        registrar_PB->setText(QCoreApplication::translate("inicio_dialog", "Registrarse", nullptr));
    } // retranslateUi

};

namespace Ui {
    class inicio_dialog: public Ui_inicio_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INICIO_DIALOG_H
