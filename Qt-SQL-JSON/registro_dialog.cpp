#include "registro_dialog.h"
#include "ui_registro_dialog.h"
#include <QMessageBox>


registro_dialog::registro_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registro_dialog)
{
    ui->setupUi(this);


    ui->correo_LE->setPlaceholderText("Correo electrónico");
    ui->cont_LE->setPlaceholderText("Contraseña");
    ui->usuario_LE->setPlaceholderText("Usuario");




    ui->registro_BB->button(QDialogButtonBox::Ok)->setEnabled(false);
}

registro_dialog::~registro_dialog()
{
    delete ui;
}

void registro_dialog::recibeBool(int boul)
{
    if(boul == 1)
    {
      ui->usuario_LE->clear();

    }
    else if(boul == 2)
    {

      ui->correo_LE->clear();
    }

}

void registro_dialog::habilita_boton()
{


    emit enviaRevisaUsuario(ui->usuario_LE->text(),ui->correo_LE->text());



    if(ui->cont_LE->text().size()>0 &&
        ui->correo_LE->text().size()>0&& ui->usuario_LE->text().size())

    {

        ui->registro_BB->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {

        ui->registro_BB->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}






void registro_dialog::on_correo_LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1); //Evitar advertencias del compilador
    habilita_boton();

}



void registro_dialog::on_usuario_LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    habilita_boton();

}

void registro_dialog::on_cont_LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1); //Evitar advertencias del compilador
    habilita_boton();
}




void registro_dialog::on_registro_BB_accepted()
{

    Cuenta cuenta(ui->usuario_LE->text(),ui->correo_LE->text(),ui->cont_LE->text());

    emit enviaRegistro(cuenta);
    accept();

}








