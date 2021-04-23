/********************************************************************************
** Form generated from reading UI file 'registro_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRO_DIALOG_H
#define UI_REGISTRO_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_registro_dialog
{
public:
    QLabel *label;
    QLineEdit *usuario_LE;
    QLineEdit *correo_LE;
    QLineEdit *cont_LE;
    QDialogButtonBox *registro_BB;

    void setupUi(QDialog *registro_dialog)
    {
        if (registro_dialog->objectName().isEmpty())
            registro_dialog->setObjectName(QString::fromUtf8("registro_dialog"));
        registro_dialog->resize(400, 300);
        label = new QLabel(registro_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 20, 47, 13));
        usuario_LE = new QLineEdit(registro_dialog);
        usuario_LE->setObjectName(QString::fromUtf8("usuario_LE"));
        usuario_LE->setGeometry(QRect(80, 60, 221, 20));
        correo_LE = new QLineEdit(registro_dialog);
        correo_LE->setObjectName(QString::fromUtf8("correo_LE"));
        correo_LE->setGeometry(QRect(80, 100, 221, 20));
        cont_LE = new QLineEdit(registro_dialog);
        cont_LE->setObjectName(QString::fromUtf8("cont_LE"));
        cont_LE->setGeometry(QRect(80, 140, 221, 20));
        cont_LE->setEchoMode(QLineEdit::Password);
        registro_BB = new QDialogButtonBox(registro_dialog);
        registro_BB->setObjectName(QString::fromUtf8("registro_BB"));
        registro_BB->setGeometry(QRect(110, 180, 156, 23));
        registro_BB->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(registro_dialog);

        QMetaObject::connectSlotsByName(registro_dialog);
    } // setupUi

    void retranslateUi(QDialog *registro_dialog)
    {
        registro_dialog->setWindowTitle(QCoreApplication::translate("registro_dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("registro_dialog", "Bookin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registro_dialog: public Ui_registro_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRO_DIALOG_H
