#include "principal.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QList>
#include <QJsonArray>
#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>


Principal::Principal(QObject *parent) : QObject(parent)
{

    ini = new inicio_dialog();
    reg = new registro_dialog();
    men = new menu_dialog();



    cargarDesdeDisco("users.json");


    QObject::connect(ini, SIGNAL(registrar()), this, SLOT(abrirRegistro()));

    QObject::connect(reg, SIGNAL(enviaRevisaUsuario(QString,QString)),this,SLOT(recibeRevisaUsuario(QString,QString)));

    QObject::connect(this,SIGNAL(regresaBool(int)),reg,SLOT(recibeBool(int)));

    QObject::connect(reg, SIGNAL(enviaRegistro(Cuenta)), this, SLOT(agregaRegistro(Cuenta)));

    QObject::connect(ini, SIGNAL(validar(QString,QString)),men, SLOT(recibe(QString, QString)));

    QObject::connect(ini, SIGNAL(enviaUsuario(QString,QString)), this, SLOT(recibeUsuario(QString,QString)));

    QObject::connect(this,SIGNAL(enviaDatosUsuario(QString,QString,QString)),men,SLOT(recibeDatosUsuario(QString,QString,QString)));

    QObject::connect(men, SIGNAL(enviaEditDatos(QString,QString,QString,QString)),this,SLOT(recibeEditDatos(QString,QString,QString,QString)));

}



void Principal::comenzar()
{
    ini->exec();
}


void Principal::abrirRegistro()
{
    ini->setVisible(false);
    reg->exec();
}




void Principal::abrirMenu()
{

    men->exec();

}



void Principal::recibeRevisaUsuario(QString name, QString mail)
{


    for(int i=0; i<listaUsuarios.size(); i++)
    {

        if(listaUsuarios[i].getName()==name)
        {
            QMessageBox e;
            e.setText("Usuario ya existe. Por favor ingresa uno nuevo.");//si no se encontró usuario
            e.exec();
            emit regresaBool(1);
        }
        if(listaUsuarios[i].getMail()==mail)
        {
            QMessageBox e;
            e.setText("Correo ya existe. Por favor ingresa uno nuevo.");//si no se encontró usuario
            e.exec();
            emit regresaBool(2);

        }
    }

}

void Principal::recibeUsuario(QString name, QString password)
{
    for(int i=0; i<listaUsuarios.size(); i++)
    {

        if(listaUsuarios[i].getName()==name || listaUsuarios[i].getPassword()==password)
        {

            emit enviaDatosUsuario(listaUsuarios[i].getName(),listaUsuarios[i].getMail(),listaUsuarios[i].getPassword());
            ini->setVisible(false);
            abrirMenu();

        }
        else
        {
            QMessageBox e;
            e.setText("Error. Usuario o contraseña incorrectos");//si no se encontró usuario

        }
    }

}


void Principal::recibeEditDatos(QString name, QString mail, QString password, QString user)
{



    for(int i=0; i<listaUsuarios.size();i++)
    {
      qDebug()<<"INFO:"<<listaUsuarios[i].getMail();//obtienen datos para guardar en arreglo (array)
      qDebug()<<"INFO:"<<listaUsuarios[i].getName();
      qDebug()<<"INFO:"<<listaUsuarios[i].getPassword();

      if(listaUsuarios[i].getName()==user)
      {
          listaUsuarios[i].setName(name);
          listaUsuarios[i].setMail(mail);
          listaUsuarios[i].setPassword(password);
      }

    }

    guardarEnDisco();




    //Regresar a este método después para ver sobre guardar directamente con listas
    //Acá una página donde lo explican: http://www.davideling.it/2014/02/qt5-json-serialization/

    /*QFile jsonFile("users.json");


    if(jsonFile.open(QIODevice::ReadWrite))
    {


        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);

        QJsonObject rootObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        //QJsonValue usersObj = rootObject.value("users");//Busca la llave del arreglo del objeto

        QJsonValueRef ArrayRef = rootObject.find("users").value();

        QJsonArray Array = ArrayRef.toArray();
        //Se asigna a arreglo la llave en memoria

        int i = 0;

        int value = 0;



        QJsonArray::iterator ArrayIterator = Array.begin();
        foreach (const QJsonValue & v, Array) //Busca en el arreglo por los valoresJSON del arreglo
        {



            if(v.toObject().value("name").toString()==user)
            {
                qDebug()<<"POSICION ENCONTRADO:"<<i;

                value = i;

            }

            qDebug()<<"POSICION:"<<i;

            i++;

        }

        QJsonValueRef ElementOneValueRef = ArrayIterator[11];


        QJsonObject ElementOneObject = ElementOneValueRef.toObject();


        ElementOneObject.insert("mail", QJsonValue(mail));
        ElementOneObject.insert("name", QJsonValue(name));
        ElementOneObject.insert("password", QJsonValue(password));
        //ElementOneObject.insert("name", QJsonValue(QString("David")));


        // Make modifications to ElementOneObject

        ElementOneValueRef = ElementOneObject;

        ArrayRef = Array;

        jsonDocument.setObject(rootObject);

        //QByteArray finalData = jsonDocument.toJson();
        //jsonDocument.setObject(rootObject);

        jsonFile.open(QIODevice::ReadWrite);

        jsonFile.write(jsonDocument.toJson());

        jsonFile.close();*/

    /*

        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject rootObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        QJsonValue usersArrayValue = rootObject.value("users");//Busca la llave del arreglo del objeto
        QJsonArray usersArray = usersArrayValue.toArray(); //Se asigna a arreglo la



       QJsonObject newObject;

        newObject["mail"] = mail;
        newObject["name"] = name;
        newObject["password"] = password;

        int i =0;



        foreach (const QJsonValue & v, usersArray) //Busca en el arreglo por los valoresJSON del arreglo
        {



            if(v.toObject().value("name").toString()==user)
            {
                qDebug()<<"POSICION ENCONTRADO:"<<i;


                usersArray.removeAt(i);

                usersArray.replace(i,newObject);

            }

            qDebug()<<"POSICION:"<<i;

            i++;

        }





        rootObject.remove("users");

        rootObject.insert("users", usersArray);

        QJsonDocument newDoc(rootObject);

        QByteArray finalData = newDoc.toJson();

        jsonFile.open(QIODevice::ReadWrite);

        jsonFile.write(finalData);

        jsonFile.close();*/










}

void Principal::agregaRegistro(Cuenta cuenta)
{
    listaUsuarios.push_back(cuenta);
    guardarEnDisco();

    ini->setVisible(true);
}




void Principal::imprimirLista()
{
    for(int i=0; i<listaUsuarios.size(); i++)
    {

        qDebug()<<"Mail:"<<listaUsuarios[i].getMail();
        qDebug()<<"Name:"<<listaUsuarios[i].getName();
        qDebug()<<"Password:"<<listaUsuarios[i].getPassword();
    }



}



void Principal::cargarDesdeDisco(QString r)
{

    QFile jsonFile(r);


    if(jsonFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {


        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject jsonObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        QJsonValue usersArrayValue = jsonObject.value("users");//Busca la llave del arreglo del objeto
        QJsonArray usersArray = usersArrayValue.toArray(); //Se asigna a arreglo la llave en memoria

        foreach (const QJsonValue & v, usersArray) //Busca en el arreglo por los valoresJSON del arreglo
        {
            Cuenta c;

            c.setMail(v.toObject().value("mail").toString());//Indexa y transforma de objeto a cadena
            c.setName(v.toObject().value("name").toString());
            c.setPassword(v.toObject().value("password").toString());

            listaUsuarios.push_back(c);


            qDebug() << v.toObject().value("mail").toString();//Indexa y transforma de objeto a cadena
            qDebug() << v.toObject().value("name").toString();
            qDebug() << v.toObject().value("password").toString();



            qDebug() << "\n";




        }

    }
    else
    {
        qDebug()<<"Archivo no existe o se encuentra corrupto.";
    }

}



void Principal::guardarEnDisco()
{

    //Regresar a este método después para ver sobre guardar directamente con listas
    //Acá una página donde lo explican: http://www.davideling.it/2014/02/qt5-json-serialization/

    /*QFile jsonFile("users.json");


    if(jsonFile.open(QIODevice::ReadWrite))
    {


        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject rootObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        QJsonValue usersObj = rootObject.value("users");//Busca la llave del arreglo del objeto
        QJsonArray usersArray = usersObj.toArray(); //Se asigna a arreglo la llave en memoria



        QJsonObject newObject;

        newObject["mail"] = cuenta.getMail();
        newObject["name"] = cuenta.getName();
        newObject["password"] = cuenta.getPassword();

        usersArray.push_back(newObject);



        QJsonObject userObject;

        userObject["users"] = usersArray;

        QJsonDocument newDoc(userObject);

        QByteArray finalData = newDoc.toJson();

        jsonFile.open(QIODevice::ReadWrite);

        jsonFile.write(finalData);

        jsonFile.close();


    }*/


    QFile jsonFile("users.json");


    if(jsonFile.open(QIODevice::ReadWrite))
    {






    QJsonObject u;//objeto principal

    QJsonArray usersArray;//arreglo principal

    for(int i=0; i<listaUsuarios.size();i++)
    {
      qDebug()<<"INFO:"<<listaUsuarios[i].getMail();//obtienen datos para guardar en arreglo (array)
      qDebug()<<"INFO:"<<listaUsuarios[i].getName();
      qDebug()<<"INFO:"<<listaUsuarios[i].getPassword();



        u["mail"] = listaUsuarios[i].getMail();//obtienen datos para guardar en arreglo (array)
        u["name"] = listaUsuarios[i].getName();
        u["password"] = listaUsuarios[i].getPassword();


        usersArray.append(u);// inserta en arreglo JsonObject

    }




    QJsonObject obj;//se define un nuevo objeto para encapsular los demás objetos

    obj["users"] = usersArray;//define el nombre del objeto y se asigna el arreglo


    QJsonDocument newDoc(obj);//se crea el documento con el nuevo objeto

    QByteArray finalData = newDoc.toJson();// comprime a JSON

    jsonFile.write(finalData);//Escribe QByteArray

      }
}







void Principal::posicionObjeto()
{

    QFile jsonFile("users.json");


    if(jsonFile.open(QIODevice::ReadWrite))
    {


        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject rootObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        QJsonValue usersObj = rootObject.value("users");//Busca la llave del arreglo del objeto
        QJsonArray usersArray = usersObj.toArray(); //Se asigna a arreglo la llave en memoria


        foreach (const QJsonValue & v, usersArray) //Busca en el arreglo por los valoresJSON del arreglo
        {


            v.toObject().value("mail").toString();//Indexa y transforma de objeto a cadena
            v.toObject().value("name").toString();
            v.toObject().value("password").toString();

        }



        /*QJsonObject newObject;

        newObject["mail"] = mail;
        newObject["name"] = name;
        newObject["password"] = password;

        usersArray.removeAt(0);

        usersArray.insert(0,newObject);

        rootObject.remove("users");

        rootObject.insert("users", usersArray);

        QJsonDocument newDoc(rootObject);

        QByteArray finalData = newDoc.toJson();
        //jsonDocument.setObject(rootObject);

        jsonFile.open(QIODevice::ReadWrite);

        jsonFile.write(finalData);

        jsonFile.close();


    }*/




    /*QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject jsonObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        //QJsonValue usersArrayValue = jsonObject.value("users");//Busca la llave del arreglo del objeto
        //QJsonArray usersArray = usersArrayValue.toArray(); //Se asigna a arreglo la llave en memoria
        */


}

}


