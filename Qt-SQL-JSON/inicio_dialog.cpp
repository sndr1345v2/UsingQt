#include "inicio_dialog.h"
#include "ui_inicio_dialog.h"

inicio_dialog::inicio_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inicio_dialog)
{
    ui->setupUi(this);
    ui->usuario_LE->setPlaceholderText("Usuario");
    ui->contra_LE->setPlaceholderText("Contraseña");
}

inicio_dialog::~inicio_dialog()
{
    delete ui;
}

void inicio_dialog::on_usuario_LE_textChanged(const QString &arg1)
{

    if (ui->usuario_LE->text().size() > 0 &&
            ui->contra_LE->text().size() > 0)
    {
        ui->iniciar_PB->setEnabled(true);
    }

    else
    {
        ui->iniciar_PB->setEnabled(false);
    }
    Q_UNUSED(arg1);


}

void inicio_dialog::on_contra_LE_textChanged(const QString &arg1)
{
    if (ui->usuario_LE->text().size() > 0 && ui->contra_LE->text().size() > 0)
    {
        ui->iniciar_PB->setEnabled(true);
    }

    else
    {
        ui->iniciar_PB->setEnabled(false);
    }
    Q_UNUSED(arg1);

}

void inicio_dialog::on_iniciar_PB_clicked()
{

    emit enviaUsuario(ui->usuario_LE->text(), ui->contra_LE->text());
    emit pasar();

}

void inicio_dialog::on_registrar_PB_clicked()
{

    emit registrar();
}

void inicio_dialog::on_user_PB_clicked()
{
    emit mostrar();
}
