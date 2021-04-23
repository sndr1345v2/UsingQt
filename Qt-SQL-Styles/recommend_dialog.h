#ifndef RECOMMEND_DIALOG_H
#define RECOMMEND_DIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QPixmap>

namespace Ui {
class recommend_dialog;
}

class recommend_dialog : public QDialog
{
    Q_OBJECT


public:
    explicit recommend_dialog(QWidget *parent = nullptr);
    ~recommend_dialog();
    QString user_recom;
    QPixmap path_recom;

     Ui::recommend_dialog *ui;



     QSqlDatabase data;
     bool conectBase(){

         data=QSqlDatabase::addDatabase("QPSQL");
         data.setHostName("localhost");
         data.setPort(5432);//Set the port to specify where it's running on
         data.setDatabaseName("postgres");
         data.setPassword("1234");
         data.setUserName("postgres");

         if(!data.open()){

             qDebug()<<"Error al abrir base de datos";
             return false;
         }
         else{

             qDebug()<<"Conectado";
             return true;
         }

     }

     void desconBase()
     {
         data.close();

     }


private slots:
    void on_pushButton_config_clicked();
    void on_pushButton_ayuda_2_clicked();
    void on_pushButton_back_clicked();

public slots:
    void recibe_datos_usuario(QString,QPixmap);


private:

signals:
    bool regresa_inicio(bool);

};

#endif // RECOMMEND_DIALOG_H
