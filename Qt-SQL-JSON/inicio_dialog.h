#ifndef INICIO_DIALOG_H
#define INICIO_DIALOG_H
#include "cuenta.h"//agregar librería
#include <QDialog>

namespace Ui {
class inicio_dialog;
}

class inicio_dialog : public QDialog
{
    Q_OBJECT

signals:

    void enviaUsuario(QString, QString);
    void registrar();
    void mostrar();
    void pasar();
public:
    explicit inicio_dialog(QWidget *parent = 0);
    ~inicio_dialog();

private slots:

    void on_usuario_LE_textChanged(const QString &arg1);

    void on_contra_LE_textChanged(const QString &arg1);

    void on_iniciar_PB_clicked();

    void on_registrar_PB_clicked();

    void on_user_PB_clicked();

private:
    Ui::inicio_dialog *ui;

};

#endif // INICIO_DIALOG_H
