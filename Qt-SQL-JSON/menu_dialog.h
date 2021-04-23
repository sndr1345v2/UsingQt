#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H
#include <iostream>
#include <QDialog>
#include "cuenta.h"
#include <QStandardItem>
#include "libro.h"
#include <QJsonArray>
#include <vector>


using namespace std;


namespace Ui {
class menu_dialog;
}

class menu_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit menu_dialog(QWidget *parent = 0);
    Ui::menu_dialog *ui;
    ~menu_dialog();
//Métodos usuario:
    void mostrar_usuario();
    void edita();

//Métodos libros:
    void cargar_libros(QString);
    void cargar_libros_usuario();


    void actualiza_mis_libros();
    void actualiza_favoritos();
    void actualiza_libros();
    void guardar_libros_usuario();


    //Método ordenamiento

    vector<Libro> merge(const vector<Libro>& left, const vector<Libro>& right);
    vector<Libro> merge_sort(vector<Libro>& vec);


    //Método recomendación

    void crear_grafo();

    void grafo_recomendacion();







private:


    QHash <QString, int> aristas;
    QHash <QString, QHash<QString, int>> grafo;



    QJsonArray booksArray;
    //This is to save all books at the end in "guardar_libros_usuario"

    QList<Libro> libros;
    QList<Libro> mis_libros;
    QList<Libro> favoritos;

    QList<Libro>libro1;


    QList <Cuenta> Usuarios;
    QList <Cuenta> Usuariosmenos;

    QList <Libro> MisLibros;
    QList <Libro> Favoritos;
    QList <Libro> MisLibrosmenos;
    QList <Libro> Favoritosmenos;

    QStandardItemModel *model_libros = new QStandardItemModel;
    QStandardItemModel *model_mis_libros = new QStandardItemModel;
    QStandardItemModel *model_favoritos = new QStandardItemModel;

    QString user;
    QString contr;

    QString correo;

    QString buscado;
signals:
    void enviaEditDatos(QString,QString,QString,QString);


private slots:
    //void recibe(QString usr, QString con);

    void recibeDatosUsuario(QString,QString,QString);
    //void hace();



    void on_buscar_LE_textChanged(const QString &arg1);
    void on_buscar_misLibros_LE_textChanged(const QString &arg1);
    void on_buscar_favoritos_LE_textChanged(const QString &arg1);



    void on_editar_usrPB_clicked();
    void on_editar_cePB_clicked();

    void on_editar_con_clicked();

    void on_usuario_LE_editingFinished();
    void on_correo_LE_editingFinished();

    void on_cont_LE_editingFinished();


    void on_tableView_clicked(const QModelIndex &index);
    void on_misLibros_clicked(const QModelIndex &index);




    void on_antologia_PB_clicked();

    void on_biografia_PB_clicked();
    void on_drama_PB_clicked();
    void on_expositivo_PB_clicked();
    void on_espistolar_PB_clicked();
    void on_narrativa_PB_clicked();
    void on_obragrafica_PB_clicked();
    void on_poesia_PB_clicked();
    void on_referencia_PB_clicked();
    void on_clasico_PB_clicked();



    void on_mostrarLibros_clicked();

    void on_comboBox_sortLibros_currentTextChanged(const QString &arg1);
    void on_comboBox_sortMislibros_currentTextChanged(const QString &arg1);
    void on_comboBox_sortFavoritos_currentTextChanged(const QString &arg1);
};



#endif // MENU_DIALOG_H
