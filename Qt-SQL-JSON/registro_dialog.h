#ifndef REGISTRO_DIALOG_H
#define REGISTRO_DIALOG_H
#include "cuenta.h"
#include <QPushButton>
#include <QDialog>
#include <iostream>


namespace Ui {
class registro_dialog;
}

class registro_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit registro_dialog(QWidget *parent = 0);
    ~registro_dialog();

signals:
    void enviaRegistro(Cuenta u);
    void registra();

    void enviaRevisaUsuario(QString,QString);


private slots:

    void recibeBool(int);


    void on_correo_LE_textChanged(const QString &arg1);


    void on_usuario_LE_textChanged(const QString &arg1);

    void on_cont_LE_textChanged(const QString &arg1);

    void on_registro_BB_accepted();


private:
    Ui::registro_dialog *ui;
    void habilita_boton();

};

#endif // REGISTRO_DIALOG_H
