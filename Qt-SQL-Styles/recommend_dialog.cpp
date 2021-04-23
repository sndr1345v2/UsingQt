#include "recommend_dialog.h"
#include "ui_recommend_dialog.h"

recommend_dialog::recommend_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recommend_dialog)
{
    ui->setupUi(this);



    QSqlQuery *query =  new QSqlQuery(data);
    query->prepare("select* from eje_grupo_recomendar where nombre = 'Patrones'");
    query->exec();
    while (query->next()) {
        QString recom_name1 = (query->value(1).toString());
        QPixmap recom_path1 = (query->value(5).toString());
        ui->recom1_name->setText(recom_name1);
        int w = ui->trial_label->width();
        int h = ui->trial_label->height();
        ui->trial_label->setPixmap(recom_path1.scaled(w,h,Qt::KeepAspectRatio));
    }
    query->clear();
    query->prepare("select* from eje_grupo_recomendar where nombre = 'Adicionysustraccion'");
    query->exec();
    while (query->next()) {
        QString recom_name2 = (query->value(1).toString());
        QPixmap recom_path2 = (query->value(5).toString());
        ui->recom2_name->setText(recom_name2);
        int w = ui->recom2_icon->width();
        int h = ui->recom2_icon->height();
        ui->recom2_icon->setPixmap(recom_path2.scaled(w,h,Qt::KeepAspectRatio));
    }
    query->clear();
    query->prepare("select* from eje_grupo_recomendar where nombre= 'Proporcionalidad'");
    query->exec();
    while (query->next()) {
        QString recom_name3 = (query->value(1).toString());
        QPixmap recom_path3 = (query->value(5).toString());
        ui->recom3_name->setText(recom_name3);
        int w = ui->recom3_icon->width();
        int h = ui->recom3_icon->height();
        ui->recom3_icon->setPixmap(recom_path3.scaled(w,h,Qt::KeepAspectRatio));
    }

}

recommend_dialog::~recommend_dialog()
{
    delete ui;
}

void recommend_dialog::on_pushButton_config_clicked()
{

}

void recommend_dialog::on_pushButton_ayuda_2_clicked()
{

}

void recommend_dialog::recibe_datos_usuario(QString user, QPixmap path)
{
    ui->user_name->setText(user);
    int w = ui->user_icon->width();
    int h = ui->user_icon->height();
    ui->user_icon->setPixmap(path.scaled(w,h,Qt::KeepAspectRatio));
}

void recommend_dialog::on_pushButton_back_clicked()
{
    qDebug()<<"button was pressed";
    emit regresa_inicio(true);
    accept();
}
