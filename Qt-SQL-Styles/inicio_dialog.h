#ifndef INICIO_DIALOG_H
#define INICIO_DIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>

namespace Ui {
class inicio_dialog;
}

class inicio_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit inicio_dialog(QWidget *parent = nullptr);
    ~inicio_dialog();

    QString name;
    QPixmap path;

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
    void on_pushButton_learn_clicked();

    void on_pushButton_recommend_clicked();

private:
    Ui::inicio_dialog *ui;

signals:
    void inicia_recomend(bool);
    void envia_datos_usuario(QString, QPixmap);
};

#endif // INICIO_DIALOG_H
