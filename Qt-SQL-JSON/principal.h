#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <iostream>
#include "cuenta.h"
#include <QList>
#include "inicio_dialog.h"
#include "registro_dialog.h"
#include "menu_dialog.h"
#include <QObject>


using namespace std;




class Principal : public QObject
{
    Q_OBJECT


private:

    inicio_dialog *ini;
    registro_dialog*reg;
    menu_dialog *men;


    QString name;
    QString password;
    QString mail;

    QList <Cuenta> listaUsuarios;


public:

    explicit Principal(QObject *parent = nullptr);

    void comenzar();
    void abrirMenu();
    void imprimirLista();

    void cargarDesdeDisco(QString);

    void guardarEnDisco();


    void posicionObjeto();


signals:
    void enviaDatosUsuario(QString,QString,QString);
    void regresaBool(int);

public slots:

    void abrirRegistro();
    void recibeUsuario(QString,QString);

    void recibeRevisaUsuario(QString,QString);

    void recibeEditDatos(QString,QString,QString,QString);
    void agregaRegistro(Cuenta);



};




#endif // PRINCIPAL_H
