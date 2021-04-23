#include "menu_dialog.h"
#include "ui_menu_dialog.h"
#include "QMessageBox"
#include <QFile>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTextStream>
#include <QtAlgorithms>
#include <QFile>
#include <list>
#include "cuenta.h"
#include "libro.h"
#include <qdebug.h>

menu_dialog::menu_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::menu_dialog)
{


    /*QPixmap image("blah.jpg");

    QLabel imageLabel = new QLabel();
    ui->widget_antologia.setPixmap(image);


    mainLayout.addWidget(imageLabel);*/

    ui->setupUi(this);
    ui->widget_antologia->setVisible(true);


    ui->user_LE->setReadOnly(true);
    ui->usuario_LE->setReadOnly(true);
    ui->cont_LE->setReadOnly(true);
    ui->correo_LE->setReadOnly(true);

    ui->buscar_LE->setPlaceholderText("Buscar título o autor");

    ui->buscar_misLibros_LE->setPlaceholderText("Buscar título o autor");
    ui->buscar_favoritos_LE->setPlaceholderText("Buscar título o autor");

    QStringList opciones,opciones1;

    opciones<<"     "<<"Título"<<"Autor"<<"Editorial"<<"Año"<<"Tipo";
    ui->comboBox_sortLibros->addItems(opciones);
    opciones1<<"     "<<"Título";
    ui->comboBox_sortFavoritos->addItems(opciones1);
    ui->comboBox_sortMislibros->addItems(opciones1);

    cargar_libros("bukin.json");
   // crear_grafo();

}

menu_dialog::~menu_dialog()
{
    delete ui;
}

void menu_dialog::edita()
{
    emit enviaEditDatos(ui->usuario_LE->text(),ui->correo_LE->text(),ui->cont_LE->text(),ui->user_LE->text());
}

void menu_dialog::on_editar_usrPB_clicked()
{
    ui->usuario_LE->setReadOnly(false);
}

void menu_dialog::on_editar_cePB_clicked()
{
    ui->correo_LE->setReadOnly(false);
}

void menu_dialog::on_editar_con_clicked()
{
    ui->cont_LE->setReadOnly(false);
}



void menu_dialog::on_usuario_LE_editingFinished()
{

    edita();
    ui->usuario_LE->setReadOnly(true);
    ui->usuario_LE->setText(ui->usuario_LE->text());
}

void menu_dialog::on_correo_LE_editingFinished()
{

    edita();
    ui->correo_LE->setReadOnly(true);
    ui->correo_LE->setText(ui->correo_LE->text());
}



void menu_dialog::on_cont_LE_editingFinished()
{

    edita();
    ui->cont_LE->setReadOnly(true);
    ui->cont_LE->setText(ui->cont_LE->text());
}



void menu_dialog::recibeDatosUsuario(QString usuario, QString correo, QString cont)
{
    ui->usuario_LE->setText(usuario);
    ui->correo_LE->setText(correo);
    ui->cont_LE->setText(cont);

    ui->user_LE->setText(usuario);

    cargar_libros_usuario();
    grafo_recomendacion();


}



void menu_dialog::cargar_libros(QString r)
{

    QFile jsonFile(r);

    if(jsonFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {


        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject jsonObject = jsonDocument.object(); //Se transforma el documento entero en un objeto

        QJsonValue booksArrayValue = jsonObject.value("books");//Busca la llave del arreglo del objeto
        booksArray = booksArrayValue.toArray(); //Arreglo como valor de la clase

        foreach (const QJsonValue & value, booksArray) //Busca en el arreglo por los valoresJSON del arreglo
        {
            Libro l;

            QJsonObject obj = value.toObject();

            l.set_titulo(obj.value("title").toString());
            l.set_autor(obj.value("author").toString());//Indexa y transforma de objeto a cadena
            l.set_editorial(obj.value("editorial").toString());
            l.set_anio(obj.value("year").toInt());
            l.set_tipo(obj.value("type").toString());

            libros.push_back(l);

        }

    }
    else
    {
        qDebug()<<"Archivo no existe o se encuentra corrupto.";
    }


    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

    for(int i = 0; i < libros.size(); i++)
    {
        //qDebug()<<"TITULOS MIS LIBROS"<<mis_libros[i].get_titulo();
        QStandardItem *titulo = new QStandardItem(libros[i].get_titulo());
        QStandardItem *autor = new QStandardItem (libros[i].get_autor());
        QStandardItem *editorial =  new QStandardItem (libros[i].get_editorial());
        QStandardItem *anio = new QStandardItem (libros[i].get_anio());
        QStandardItem *tipo = new QStandardItem(libros[i].get_tipo());
        QStandardItem *check = new QStandardItem("+");

        //QStandardItem *check = new QStandardItem("text");

        //check->setCheckable(true);
        //check->setCheckState(Qt::Unchecked);

        model_libros->setItem(i, 0,check);
        model_libros->setItem(i, 1, titulo);
        model_libros->setItem(i, 2, autor);
        model_libros->setItem(i, 3, editorial);
        model_libros->setItem(i, 4, anio);
        model_libros->setItem(i, 5, tipo);



    }





    ui->tableView->setModel(model_libros);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);



}

void menu_dialog::cargar_libros_usuario()
{
    QFile jsonFile("bukin.json");

    if(jsonFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {

        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject jsonObject = jsonDocument.object();

        QJsonValue usersArrayValue = jsonObject.value("users");
        QJsonArray usersArray = usersArrayValue.toArray();

        foreach (const QJsonValue & value, usersArray)
        {
            Cuenta user;

            QString nombre = ui->usuario_LE->text();

            QJsonObject obj = value.toObject();

            if(obj.value("name").toString()==nombre)
            {
                user.setMail(obj.value("mail").toString());
                user.setName(obj.value("name").toString());
                user.setPassword(obj.value("password").toString());

                Usuarios.push_back(user);
                /*qDebug()<<obj.value("mail").toString();
                qDebug()<<obj.value("name").toString();
                qDebug()<<obj.value("password").toString();*/

                foreach (const QJsonValue & value, obj.value("myBooks").toArray())
                {
                    QJsonObject obj2 = value.toObject();
                    Libro libro(obj2.value("title").toString()," "," ",0," ");

                    qDebug()<<"OBJETO DE LIBRO:"<<libro.get_titulo();



                    MisLibros.push_back(libro);

                    qDebug()<<"Mis libros:"<<obj2.value("title").toString();


                }
                foreach (const QJsonValue & value, obj.value("favorites").toArray())
                {
                    QJsonObject obj3 = value.toObject();

                    Libro libro(obj3.value("title").toString()," "," ",0," ");
                    Favoritos.push_back(libro);


                    qDebug()<<"Favoritos:"<<obj3.value("title").toString();


                }









            }
        }



        model_mis_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));

        model_mis_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

        model_favoritos->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));

        model_favoritos->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

        //model->setHorizontalHeaderItem(5,new QStandardItem(QString(" ")));


        for(int i = 0; i < MisLibros.size(); i++)
        {
            //qDebug()<<"TITULOS MIS LIBROS"<<mis_libros[i].get_titulo();
            QStandardItem *titulo = new QStandardItem(MisLibros[i].get_titulo());
            QStandardItem *check = new QStandardItem("+");
            model_mis_libros->setItem(i, 0,check);
            model_mis_libros->setItem(i, 1, titulo);

        }


        for(int i = 0; i < Favoritos.size(); i++)
        {
            //qDebug()<<"TITULOS MIS LIBROS"<<mis_libros[i].get_titulo();
            QStandardItem *titulo = new QStandardItem(Favoritos[i].get_titulo());
            QStandardItem *check = new QStandardItem("+");

            model_favoritos->setItem(i, 0,check);
            model_favoritos->setItem(i, 1, titulo);

        }

        ui->misLibros->setModel(model_mis_libros);
        ui->misLibros->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->favoritos->setModel(model_favoritos);
        ui->favoritos->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->misLibros->resizeColumnToContents(0);
        ui->misLibros->setColumnWidth(1,770);

        ui->misLibros->verticalHeader()->setVisible(false);



        ui->favoritos->resizeColumnToContents(0);
        ui->favoritos->setColumnWidth(1,770);

        ui->favoritos->verticalHeader()->setVisible(false);

    }
}



void menu_dialog::guardar_libros_usuario()
{
    QFile jsonFile("bukin.json");

    if(jsonFile.open(QIODevice::ReadWrite))
    {

        QByteArray jsonFiledata = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFiledata);
        QJsonObject jsonObject = jsonDocument.object();


        QJsonValue usersArrayValue = jsonObject.value("users");
        QJsonArray usersArray = usersArrayValue.toArray();




        int i= 0;
        for(auto value: usersArray)
        {


            QJsonObject obj = value.toObject();

            if(obj.value("name").toString()==ui->usuario_LE->text())
            {
                int blanco = i;
                usersArray.removeAt(blanco);

                QJsonObject newObject, Object, Object1;

                newObject["name"] = ui->usuario_LE->text();
                newObject["email"] = ui->correo_LE->text();
                newObject["password"] = ui->cont_LE->text();

                QJsonArray myBooksArray, favoritesArray;

                for(auto value: MisLibros)
                {
                    //newObject.se

                    Object["title"] = value.get_titulo();

                    myBooksArray.push_back(Object);

                    //newObject["myBooks"].toArray().append(MisLibros[i].get_titulo());
                    //qDebug()<<"MISLIBROS"<<MisLibros[i].get_titulo();

                }
                
                newObject.insert("myBooks",myBooksArray);


                for(auto value: Favoritos)
                {

                    Object1["title"] = value.get_titulo();

                    favoritesArray.push_back(Object1);
                    //favoritesArray.push_back(value.get_titulo());
                    //newObject["favorites"].toArray().append(Favoritos[i].get_titulo());

                    //newObject["favorites"].toArray() = Favoritos[i].get_titulo();


                }
                newObject.insert("favorites",favoritesArray);

                usersArray.insert(blanco, newObject);
            }


            qDebug()<<"mail"<<obj.value("mail").toString();
            qDebug()<<"name"<<obj.value("name").toString();

            qDebug()<<"password"<<obj.value("password").toString();


            i++;
            qDebug()<<"i"<<i;




        }

        jsonObject.insert("books",booksArray);

        jsonObject.insert("users",usersArray);



        jsonFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);



        QJsonDocument newDoc(jsonObject);
        QByteArray finalData = newDoc.toJson(QJsonDocument::Indented);

        jsonFile.write(finalData);


    }















    /*QJsonDocument newDoc(finalObject);//se crea el documento con el nuevo objeto

        QByteArray finalData = newDoc.toJson(QJsonDocument::Indented);// comprime a JSON

        jsonFileSave.write(finalData);//Escribe QByteArray*/

}


void menu_dialog::on_tableView_clicked(const QModelIndex &index)
{

    //QItemSelectionModel* selmodel = ui->tableView->selectionModel();
    //QModelIndex current = selmodel->currentIndex(); // the "current" item
    //QModelIndexList selected = selmodel->selectedIndexes(); // list of "selected" items

    qDebug() << "Seleccion " << index.data().toString();
    qDebug()<< "Titulo"<<index.sibling(index.row(),1).data(Qt::DisplayRole).toString();
    qDebug()<< "Autor"<<index.sibling(index.row(),2).data(Qt::DisplayRole).toString();
    qDebug()<< "Editorial"<<index.sibling(index.row(),3).data(Qt::DisplayRole).toString();
    qDebug()<< "Anio"<<index.sibling(index.row(),4).data(Qt::DisplayRole).toString();
    qDebug()<<"Tipo"<<index.sibling(index.row(),5).data(Qt::DisplayRole).toString();

    QString titulo =index.sibling(index.row(),1).data(Qt::DisplayRole).toString();


    Libro obj(titulo," "," ",0," ");


    qDebug()<<"BANDERA"<<MisLibros.contains(obj);

    if(!MisLibros.contains(obj))
    {
        qDebug()<<obj.toString();
        MisLibros.push_front(obj);
        actualiza_mis_libros();
        guardar_libros_usuario();
    }



}



void menu_dialog::on_misLibros_clicked(const QModelIndex &index)
{
    /*qDebug() << "Seleccion " << index.data().toString();
    qDebug()<< "Titulo"<<index.sibling(index.row(),1).data(Qt::DisplayRole).toString();
    qDebug()<< "Autor"<<index.sibling(index.row(),2).data(Qt::DisplayRole).toString();
    qDebug()<< "Editorial"<<index.sibling(index.row(),3).data(Qt::DisplayRole).toString();
    qDebug()<< "Anio"<<index.sibling(index.row(),4).data(Qt::DisplayRole).toString();
    qDebug()<<"Tipo"<<index.sibling(index.row(),5).data(Qt::DisplayRole).toString();*/

    QString titulo =index.sibling(index.row(),1).data(Qt::DisplayRole).toString();
    /*QString autor  =index.sibling(index.row(),2).data(Qt::DisplayRole).toString();
    QString editorial =index.sibling(index.row(),3).data(Qt::DisplayRole).toString();
    int anio = index.sibling(index.row(),4).data(Qt::DisplayRole).toInt();
    QString tipo =index.sibling(index.row(),5).data(Qt::DisplayRole).toString();*/

    Libro obj(titulo," "," ",0," ");



    qDebug()<<"Bandera"<<Favoritos.contains(obj);
    if(!Favoritos.contains(obj))
    {
        qDebug()<<obj.toString();
        Favoritos.push_front(obj);
        actualiza_favoritos();
        guardar_libros_usuario();

    }



}







void menu_dialog::actualiza_mis_libros()
{

    model_mis_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));

    model_mis_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

    for(int i = 0; i < MisLibros.size(); i++)
    {
        QStandardItem *titulo = new QStandardItem(MisLibros[i].get_titulo());

        QStandardItem *check = new QStandardItem("+");




        model_mis_libros->setItem(i, 0, check);
        model_mis_libros->setItem(i, 1, titulo);


    }

    ui->misLibros->setModel(model_mis_libros);
    ui->misLibros->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->misLibros->resizeColumnToContents(0);
    ui->misLibros->setColumnWidth(1,260);
    ui->misLibros->setColumnWidth(2,190);
    ui->misLibros->verticalHeader()->setVisible(false);




}

void menu_dialog::actualiza_favoritos()
{
    model_favoritos->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));

    model_favoritos->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

    for(int i = 0; i < Favoritos.size(); i++)
    {
        QStandardItem *titulo = new QStandardItem(Favoritos[i].get_titulo());

        QStandardItem *check = new QStandardItem("\u2714");

        model_favoritos->setItem(i, 0, check);
        model_favoritos->setItem(i, 1, titulo);


    }


    ui->favoritos->setModel(model_favoritos);
    ui->favoritos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->favoritos->resizeColumnToContents(0);
    ui->favoritos->setColumnWidth(1,260);
    ui->favoritos->setColumnWidth(2,190);
    ui->favoritos->verticalHeader()->setVisible(false);
}

void menu_dialog::actualiza_libros()
{
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

    for(int i = 0; i < libros.size(); i++)
    {
        //qDebug()<<"TITULOS MIS LIBROS"<<mis_libros[i].get_titulo();
        QStandardItem *titulo = new QStandardItem(libros[i].get_titulo());
        QStandardItem *autor = new QStandardItem (libros[i].get_autor());
        QStandardItem *editorial =  new QStandardItem (libros[i].get_editorial());
        QStandardItem *anio = new QStandardItem (libros[i].get_anio());
        QStandardItem *tipo = new QStandardItem(libros[i].get_tipo());
        QStandardItem *check = new QStandardItem("+");

        //QStandardItem *check = new QStandardItem("text");

        //check->setCheckable(true);
        //check->setCheckState(Qt::Unchecked);

        model_libros->setItem(i, 0,check);
        model_libros->setItem(i, 1, titulo);
        model_libros->setItem(i, 2, autor);
        model_libros->setItem(i, 3, editorial);
        model_libros->setItem(i, 4, anio);
        model_libros->setItem(i, 5, tipo);



    }





    ui->tableView->setModel(model_libros);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);


}




vector<Libro> menu_dialog::merge(const vector<Libro> &left, const vector<Libro> &right)
{

    vector<Libro> result;


    unsigned left_it = 0, right_it = 0;
    //string left_it =left[0].get_titulo();
    //string right_it= right[0].get_titulo();

    while(left_it < left.size() && right_it < right.size())
    {

        if(left[left_it] < right[right_it])
        {
            result.push_back(left[left_it]);
            left_it++;
        }
        else
        {
            result.push_back(right[right_it]);
            right_it++;
        }
    }


    while(left_it < left.size())
    {
        result.push_back(left[left_it]);
        left_it++;
    }

    while(right_it < right.size())
    {
        result.push_back(right[right_it]);
        right_it++;
    }

    return result;
}

vector<Libro> menu_dialog::merge_sort(vector<Libro> &vec)
{

    if(vec.size() == 1)
    {
        return vec;
    }


    std::vector<Libro>::iterator middle = vec.begin() + (vec.size() / 2);
    vector<Libro> left(vec.begin(), middle);
    vector<Libro> right(middle, vec.end());

    left = merge_sort(left);
    right = merge_sort(right);

    return merge(left, right);
}

void menu_dialog::crear_grafo()
{
    QFile jsonFile("bukin.json");

    QList<Cuenta>Usuarios;
    QList<Libro>MisLibros,Favoritos,UserMisLibros,UserFavoritos;


    if(jsonFile.open(QIODevice::ReadOnly| QIODevice::Text))
    {

        QByteArray jsonFileData = jsonFile.readAll();
        jsonFile.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonFileData);
        QJsonObject jsonObject = jsonDocument.object();

        QJsonValue usersArrayValue = jsonObject.value("users");
        QJsonArray usersArray = usersArrayValue.toArray();

        foreach (const QJsonValue & value, usersArray)
        {


            QJsonObject obj = value.toObject();

            Cuenta user;

            user.setMail(obj.value("mail").toString());
            user.setName(obj.value("name").toString());
            user.setPassword(obj.value("password").toString());

            Usuarios.push_back(user);

            foreach (const QJsonValue & value, obj.value("myBooks").toArray())
            {
                QJsonObject obj2 = value.toObject();
                
                
                Libro libro(obj2.value("title").toString()," "," ",0," ");

                qDebug()<<"OBJETO DE LIBRO:"<<libro.get_titulo();



                MisLibros.push_back(libro);

                UserMisLibros.push_back(libro);

                qDebug()<<"Mis libros:"<<obj2.value("title").toString();


            }
            foreach (const QJsonValue & value, obj.value("favorites").toArray())
            {
                QJsonObject obj3 = value.toObject();

                Libro libro(obj3.value("title").toString()," "," ",0," ");
                Favoritos.push_back(libro);

                UserFavoritos.push_back(libro);


                qDebug()<<"Favoritos:"<<obj3.value("title").toString();


            }

            //Create graph with "MyBooks" list

            bool existe=false;
            for(int i=0; i<MisLibros.size(); i++)
            {
                for(int j=0; j<MisLibros.size(); j++)
                {

                    if(MisLibros[j].get_titulo()!=MisLibros[i].get_titulo())
                    {
                        qDebug()<<"i: "<<i<<MisLibros[i].get_titulo();
                        qDebug()<<"j: "<<j<<MisLibros[j].get_titulo();

                        existe = false;

                        QHash<QString, QHash<QString, int>>::iterator origen;
                        for (origen = grafo.begin(); origen!= grafo.end(); ++origen)
                        {
                            QHash<QString, int>::iterator destino;
                            for (destino = origen.value().begin(); destino != origen.value().end(); ++destino)
                            {
                                if(MisLibros[i].get_titulo()== origen.key() && MisLibros[j].get_titulo()== destino.key())
                                {
                                    //Increase the value by 1 if the conexion exists
                                    existe=true;
                                    destino.value()=destino.value()+1;
                                }

                            }
                        }
                        if(!existe)
                        {
                            qDebug()<<"DESTINO INSERTADO"<<MisLibros[j].get_titulo();
                            aristas.insert(MisLibros[j].get_titulo(), 1);
                        }
                    }
                }

                qDebug()<<"ORIGEN INSERTADO:"<<MisLibros[i].get_titulo();

                grafo.insertMulti(MisLibros[i].get_titulo(), aristas);


                aristas.clear();
            }

            MisLibros.clear();
            //Acá agregaría al grafo, ya que la lista solo puede alamcenar un rango de valores por usuario

            for(int i=0; i<Favoritos.size(); i++)
            {
                for(int j=0; j<Favoritos.size(); j++)
                {

                    if(Favoritos[j].get_titulo() != Favoritos[i].get_titulo())
                    {
                        QHash<QString, QHash<QString, int>>::iterator origen;

                        for (origen = grafo.begin(); origen!= grafo.end(); ++origen)
                        {
                            QHash<QString, int>::iterator destino;
                            for (destino = origen.value().begin(); destino != origen.value().end(); ++destino)
                            {
                                if(Favoritos[i].get_titulo() == origen.key()
                                        && Favoritos[j].get_titulo() == destino.key())
                                {
                                    //Increase the value by 5 if the conexion exists
                                    destino.value()=destino.value()+5;
                                }
                            }
                        }
                    }
                }
            }


            Favoritos.clear();

        }



    }

    qDebug()<<"GRAFO FINAL:";

    QHash<QString, QHash<QString, int>>::iterator origenes= grafo.begin();
    while(origenes!=grafo.end())
    {

        QHash<QString, int>::iterator destinos= origenes.value().begin();
        while (destinos!=origenes.value().end())
        {

            qDebug()<<origenes.key()<<","
                   <<destinos.key()<<":"<<destinos.value();
            ++destinos;
        }
        ++origenes;
    }
}






void menu_dialog::grafo_recomendacion()
{

     /*QList<Libro> NoMisLibros;


    for(int i=0; i<MisLibros.size(); i++)
    {

        for(int j=0; j<MisLibros.size(); j++)
        {

            if(MisLibros[j].get_titulo()!=MisLibros[i].get_titulo())
            {


                QHash<QString, QHash<QString, int>>::iterator origen;
                for (origen = grafo.begin(); origen!= grafo.end(); ++origen)
                {

                    QHash<QString, int>::iterator destino;
                    for (destino = origen.value().begin(); destino != origen.value().end(); ++destino)
                    {
                        if(MisLibros[i].get_titulo()!= origen.key() && MisLibros[j].get_titulo() != destino.key())
                        {
                            NoMisLibros.push_back(origen.key());
                        }

                    }
                }
                if(!existe)
                {
                    qDebug()<<"DESTINO INSERTADO"<<MisLibros[j].get_titulo();
                    aristas.insert(MisLibros[j].get_titulo(), 1);
                }
            }
        }

        qDebug()<<"ORIGEN INSERTADO:"<<MisLibros[i].get_titulo();

        grafo.insertMulti(MisLibros[i].get_titulo(), aristas);


        aristas.clear();
    }

    */

    //Iterar sobre toda la clase
}





























    //QHash </*QString*/Titulo, int> aristas;

    //QString(1) -> vértice


    //QHash <QString, QHash<QString, int>> grafo; //define prototipo

    //QHash<char,int> = aristas
    //aristas.insert('B',3);//destino

    /*grafo.insert('A', aristas);//origenes

    aristas.clear();
    aristas.insert('C',11);
    grafo.insert('B',aristas);

    aristas.clear();
    aristas.insert('A',9);
    aristas.insert('D',7);
    grafo.insert('C',aristas);

    aristas.clear();
    aristas.insert('B',5);
    grafo.insert('D',aristas);

    QHash<char, QHash<char, int>>::iterator origenes= grafo.begin();

    while(origenes!=grafo.end())
    {
        QHash<char, int>::iterator destinos= origenes.value().begin();
        while (destinos!=origenes.value().end())
        {
            qDebug()<<origenes.key()<<","
                   <<destinos.key()<<":"<<destinos.value();
            ++destinos;
        }
        ++origenes;
    }*/




void menu_dialog::on_buscar_LE_textChanged(const QString &arg1)
{

    Q_UNUSED(arg1);


    if (ui->buscar_LE->text().size()==0)
    {

        ui->tableView->setModel(model_libros);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->resizeColumnToContents(0);
        ui->tableView->setColumnWidth(1,260);
        ui->tableView->setColumnWidth(2,190);
        ui->tableView->verticalHeader()->setVisible(false);


    }

    if(ui->buscar_LE->text().size()>0)
    {


        QStandardItemModel *model = new QStandardItemModel;


        model->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
        model->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
        model->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
        model->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
        model->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
        model->setHorizontalHeaderItem(0,new QStandardItem(QString("")));

        QString buscar = ui->buscar_LE->text();

        QList<Libro>libros1;

        for(int i = 0; i < libros.size(); i++)
        {

            if(libros[i].get_titulo().contains(buscar, Qt::CaseInsensitive)||libros[i].get_autor().contains(buscar, Qt::CaseInsensitive))
            {
                libros1.push_back(libros[i]);

            }


        }

        for (int j=0; j<libros1.size(); j++)
        {

            QStandardItem *titulo = new QStandardItem(libros1[j].get_titulo());
            QStandardItem *autor = new QStandardItem (libros1[j].get_autor());
            QStandardItem *editorial = new QStandardItem (libros1[j].get_editorial());
            QStandardItem *anio = new QStandardItem (libros1[j].get_anio());
            QStandardItem *tipo = new QStandardItem(libros1[j].get_tipo());
            QStandardItem *check = new QStandardItem("+");

            model->setItem(j, 0, check);
            model->setItem(j, 1, titulo);
            model->setItem(j, 2, autor);
            model->setItem(j, 3, editorial);
            model->setItem(j, 4, anio);
            model->setItem(j, 5, tipo);
        }


        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->resizeColumnToContents(0);
        ui->tableView->setColumnWidth(1,260);
        ui->tableView->setColumnWidth(2,190);
        ui->tableView->verticalHeader()->setVisible(false);


    }

}











void menu_dialog::on_buscar_favoritos_LE_textChanged(const QString &arg1)
{
    if(ui->buscar_favoritos_LE->text().size()==0)
    {

        model_favoritos->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
        model_favoritos->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
        model_favoritos->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
        model_favoritos->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
        model_favoritos->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
        model_favoritos->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

        for(int i = 0; i < Favoritos.size(); i++)
        {
            QStandardItem *titulo = new QStandardItem(Favoritos[i].get_titulo());
            QStandardItem *autor = new QStandardItem (Favoritos[i].get_autor());
            QStandardItem *editorial =  new QStandardItem (Favoritos[i].get_editorial());
            QStandardItem *anio = new QStandardItem (Favoritos[i].get_anio());
            QStandardItem *tipo = new QStandardItem(Favoritos[i].get_tipo());
            QStandardItem *check = new QStandardItem("+");




            model_favoritos->setItem(i, 0, check);
            model_favoritos->setItem(i, 1, titulo);
            model_favoritos->setItem(i, 2, autor);
            model_favoritos->setItem(i, 3, editorial);
            model_favoritos->setItem(i, 4, anio);
            model_favoritos->setItem(i, 5, tipo);

        }
        ui->favoritos->setModel(model_favoritos);
        ui->favoritos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->favoritos->resizeColumnToContents(0);
        ui->favoritos->setColumnWidth(1,260);
        ui->favoritos->setColumnWidth(2,190);
        ui->favoritos->verticalHeader()->setVisible(false);
    }

    if(ui->buscar_favoritos_LE->text().size()>0)
    {
        QStandardItemModel *model = new QStandardItemModel;


        model->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
        model->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
        model->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
        model->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
        model->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
        model->setHorizontalHeaderItem(0,new QStandardItem(QString("")));

        QString buscar = ui->buscar_favoritos_LE->text();

        QList<Libro>libros1;

        for(int i = 0; i < Favoritos.size(); i++)
        {

            if(Favoritos[i].get_titulo().contains(buscar, Qt::CaseInsensitive)||Favoritos[i].get_autor().contains(buscar, Qt::CaseInsensitive))
            {
                libros1.push_back(favoritos[i]);

            }



        }

        for (int j=0; j<libros1.size(); j++)
        {

            QStandardItem *titulo = new QStandardItem(libros1[j].get_titulo());
            QStandardItem *autor = new QStandardItem (libros1[j].get_autor());
            QStandardItem *editorial = new QStandardItem (libros1[j].get_editorial());
            QStandardItem *anio = new QStandardItem (libros1[j].get_anio());
            QStandardItem *tipo = new QStandardItem(libros1[j].get_tipo());
            QStandardItem *check = new QStandardItem("+");

            model->setItem(j, 0, check);
            model->setItem(j, 1, titulo);
            model->setItem(j, 2, autor);
            model->setItem(j, 3, editorial);
            model->setItem(j, 4, anio);
            model->setItem(j, 5, tipo);
        }


        ui->favoritos->setModel(model_favoritos);
        ui->favoritos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->favoritos->resizeColumnToContents(0);
        ui->favoritos->setColumnWidth(1,260);
        ui->favoritos->setColumnWidth(2,190);
        ui->favoritos->verticalHeader()->setVisible(false);
    }
}



void menu_dialog::on_buscar_misLibros_LE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);


    if (ui->buscar_misLibros_LE->text().size()==0)
    {

        model_mis_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
        model_mis_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
        model_mis_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
        model_mis_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
        model_mis_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
        model_mis_libros->setHorizontalHeaderItem(0,new QStandardItem(QString("")));



        for (int j=0; j<MisLibros.size(); j++)
        {

            QStandardItem *titulo = new QStandardItem(MisLibros[j].get_titulo());
            QStandardItem *autor = new QStandardItem (MisLibros[j].get_autor());
            QStandardItem *editorial = new QStandardItem (MisLibros[j].get_editorial());
            QStandardItem *anio = new QStandardItem (MisLibros[j].get_anio());
            QStandardItem *tipo = new QStandardItem(MisLibros[j].get_tipo());
            QStandardItem *check = new QStandardItem("+");


            model_mis_libros->setItem(j, 0, check);
            model_mis_libros->setItem(j, 1, titulo);
            model_mis_libros->setItem(j, 2, autor);
            model_mis_libros->setItem(j, 3, editorial);
            model_mis_libros->setItem(j, 4, anio);
            model_mis_libros->setItem(j, 5, tipo);
        }


        ui->misLibros->setModel(model_mis_libros);
        ui->misLibros->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->misLibros->resizeColumnToContents(0);
        ui->misLibros->setColumnWidth(1,260);
        ui->misLibros->setColumnWidth(2,190);
        ui->misLibros->verticalHeader()->setVisible(false);
    }

    if(ui->buscar_misLibros_LE->text().size()>0)
    {
        QStandardItemModel *model = new QStandardItemModel;


        model->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
        model->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
        model->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
        model->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
        model->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
        model->setHorizontalHeaderItem(0,new QStandardItem(QString("")));

        QString buscar = ui->buscar_misLibros_LE->text();

        QList<Libro>libros1;

        for(int i = 0; i < MisLibros.size(); i++)
        {

            if(MisLibros[i].get_titulo().contains(buscar, Qt::CaseInsensitive)||MisLibros[i].get_autor().contains(buscar, Qt::CaseInsensitive))
            {
                libros1.push_back(MisLibros[i]);

            }




        }

        for (int j=0; j<libros1.size(); j++)
        {

            QStandardItem *titulo = new QStandardItem(libros1[j].get_titulo());
            QStandardItem *autor = new QStandardItem (libros1[j].get_autor());
            QStandardItem *editorial = new QStandardItem (libros1[j].get_editorial());
            QStandardItem *anio = new QStandardItem (libros1[j].get_anio());
            QStandardItem *tipo = new QStandardItem(libros1[j].get_tipo());
            QStandardItem *check = new QStandardItem("+");

            model->setItem(j, 0, check);
            model->setItem(j, 1, titulo);
            model->setItem(j, 2, autor);
            model->setItem(j, 3, editorial);
            model->setItem(j, 4, anio);
            model->setItem(j, 5, tipo);
        }



        ui->misLibros->setModel(model);
        ui->misLibros->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->misLibros->resizeColumnToContents(0);
        ui->misLibros->setColumnWidth(1,260);
        ui->misLibros->setColumnWidth(2,190);
        ui->misLibros->verticalHeader()->setVisible(false);



    }
}







void menu_dialog::on_antologia_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Antología"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void menu_dialog::on_biografia_PB_clicked()
{

    libro1.clear();
    model_libros->clear();

    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));


    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Biografía"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void menu_dialog::on_drama_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));


    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Drama"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void menu_dialog::on_expositivo_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));


    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Expositivo"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void menu_dialog::on_espistolar_PB_clicked()
{

    libro1.clear();
    model_libros->clear();


    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Epistolar"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void menu_dialog::on_narrativa_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Narrativa"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void menu_dialog::on_obragrafica_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Obra"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void menu_dialog::on_poesia_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Poea"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void menu_dialog::on_referencia_PB_clicked()
{


    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Referencia"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void menu_dialog::on_clasico_PB_clicked()
{

    libro1.clear();

    model_libros->clear();
    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));



    for(int i = 0; i < libros.size(); i++)
    {


        if(libros[i].get_tipo().contains("Clásico"))
        {
            libro1.push_back(libros[i]);
        }

    }

    for(int j=0; j<libro1.size();j++)
    {

        QStandardItem *titulo = new QStandardItem(libro1[j].get_titulo());
        QStandardItem *autor = new QStandardItem (libro1[j].get_autor());
        QStandardItem *editorial =  new QStandardItem (libro1[j].get_editorial());
        QStandardItem *anio = new QStandardItem (libro1[j].get_anio());
        QStandardItem *tipo = new QStandardItem(libro1[j].get_tipo());
        QStandardItem *check = new QStandardItem("+");


        model_libros->setItem(j, 0, check);
        model_libros->setItem(j, 1, titulo);
        model_libros->setItem(j, 2, autor);
        model_libros->setItem(j, 3, editorial);
        model_libros->setItem(j, 4, anio);
        model_libros->setItem(j, 5, tipo);

    }


    ui->tableView->setModel(model_libros);
    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}








void menu_dialog::on_mostrarLibros_clicked()
{

    model_libros->setHorizontalHeaderItem(1,new QStandardItem(QString("Título")));
    model_libros->setHorizontalHeaderItem(2,new QStandardItem(QString("Autor")));
    model_libros->setHorizontalHeaderItem(3,new QStandardItem(QString("Editorial")));
    model_libros->setHorizontalHeaderItem(4,new QStandardItem(QString("Año")));
    model_libros->setHorizontalHeaderItem(5,new QStandardItem(QString("Tipo")));
    model_libros->setHorizontalHeaderItem(0,new QStandardItem(QString(" ")));

    for(int i = 0; i < libros.size(); i++)
    {
        //qDebug()<<"TITULOS MIS LIBROS"<<mis_libros[i].get_titulo();
        QStandardItem *titulo = new QStandardItem(libros[i].get_titulo());
        QStandardItem *autor = new QStandardItem (libros[i].get_autor());
        QStandardItem *editorial =  new QStandardItem (libros[i].get_editorial());
        QStandardItem *anio = new QStandardItem (libros[i].get_anio());
        QStandardItem *tipo = new QStandardItem(libros[i].get_tipo());
        QStandardItem *check = new QStandardItem("+");

        //QStandardItem *check = new QStandardItem("text");

        //check->setCheckable(true);
        //check->setCheckState(Qt::Unchecked);

        model_libros->setItem(i, 0,check);
        model_libros->setItem(i, 1, titulo);
        model_libros->setItem(i, 2, autor);
        model_libros->setItem(i, 3, editorial);
        model_libros->setItem(i, 4, anio);
        model_libros->setItem(i, 5, tipo);



    }





    ui->tableView->setModel(model_libros);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);


    ui->tableView->resizeColumnToContents(0);
    ui->tableView->setColumnWidth(1,260);
    ui->tableView->setColumnWidth(2,190);
    ui->tableView->verticalHeader()->setVisible(false);

}




void menu_dialog::on_comboBox_sortLibros_currentTextChanged(const QString &arg1)
{qDebug()<<ui->comboBox_sortLibros->currentText();

    if(ui->comboBox_sortLibros->currentText()=="Título")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(libros.begin(), libros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(1);
        }
        nuevo2=merge_sort(nuevo);
        libros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(libros));
        actualiza_libros();
    }

    if(ui->comboBox_sortLibros->currentText()=="Autor")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        Libro obj;
        obj.set_opc(2);
        std::copy(libros.begin(), libros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(2);
        }
        nuevo2=merge_sort(nuevo);
        libros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(libros));

        actualiza_libros();
    }
    if(ui->comboBox_sortLibros->currentText()=="Editorial")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(libros.begin(), libros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(3);
        }
        nuevo2=merge_sort(nuevo);
        libros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(libros));
        actualiza_libros();
    }
    if(ui->comboBox_sortLibros->currentText()=="Año")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(libros.begin(), libros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(4);
        }
        nuevo2=merge_sort(nuevo);
        libros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(libros));
        actualiza_libros();//corregir
    }
    if(ui->comboBox_sortLibros->currentText()=="Tipo")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(libros.begin(), libros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(5);
        }
        nuevo2=merge_sort(nuevo);
        libros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(libros));
        actualiza_libros();
    }

}

void menu_dialog::on_comboBox_sortMislibros_currentTextChanged(const QString &arg1)
{
    qDebug()<<ui->comboBox_sortMislibros->currentText();

    if(ui->comboBox_sortMislibros->currentText()=="Título")
    {
        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(MisLibros.begin(), MisLibros.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(1);
        }
        nuevo2=merge_sort(nuevo);
        MisLibros.clear();
        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(MisLibros));
        actualiza_mis_libros();
    }


}

void menu_dialog::on_comboBox_sortFavoritos_currentTextChanged(const QString &arg1)
{
    if(ui->comboBox_sortFavoritos->currentText()=="Título")

    {

        vector<Libro>nuevo;
        vector<Libro>nuevo2;
        std::copy(Favoritos.begin(), Favoritos.end(), std::back_inserter(nuevo));
        for(int i=0; i<nuevo.size();i++)
        {
            nuevo[i].set_opc(1);
        }
        nuevo2=merge_sort(nuevo);
        Favoritos.clear();

        std::copy(nuevo2.begin(), nuevo2.end(), std::back_inserter(Favoritos));
        actualiza_favoritos();
    }


}
