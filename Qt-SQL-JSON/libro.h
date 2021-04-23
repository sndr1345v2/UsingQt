#ifndef LIBRO_H
#define LIBRO_H
#include <QString>

using namespace std;
class Libro
{

public:
    Libro();
    Libro(QString titulo,QString autor,QString editorial,int anio,QString tipo);
    Libro(QString c);

    QString toString();
    QString toFile();

    void set_titulo(QString);
    QString get_titulo()const;
    void set_autor(QString);
    QString get_autor()const;
    void set_editorial(QString);
    QString get_editorial()const;
    void set_anio(int);
    int get_anio()const;
    void set_tipo(QString);
    QString get_tipo()const;

    int opcion;

    void set_opc(int o)
    {
        opcion=o;
    }

    int get_opc()
    {
        return opcion;
    }

    bool operator<(const Libro&obj)const
    {
        if(opcion==1)
        {
            return titulo < obj.titulo;
        }
        else if(opcion==2)
        {
            return autor < obj.autor;
        }
        else if(opcion==3)
        {
            return editorial<obj.editorial;
        }
        else if(opcion==4)
        {
            return anio<obj.anio;
        }
        else if(opcion==5)
        {
            return tipo<obj.tipo;
        }
    }

    bool operator>(const Libro&obj)const
    {
        if(opcion==1)
        {
            return titulo > obj.get_titulo();
        }
        else if(opcion==2)
        {
            return autor > obj.autor;
        }
        else if(opcion==3)
        {
            return editorial>obj.editorial;
        }
        else if(opcion==4)
        {
            return anio>obj.anio;
        }
        else if(opcion==5)
        {
            return tipo>obj.tipo;
        }
    }


    bool operator==(const Libro&obj)const
    {
        return titulo ==obj.get_titulo() && autor == obj.get_autor()&& editorial == obj.get_editorial()&& anio == obj.get_anio() && tipo == obj.get_tipo();
    }


    /*inline uint qHash(const Libro &key, uint seed)
    {
        return qHash(key.get_anio(), seed) ^ key.get_autor();
    }*/


private:
    QString titulo;
    QString autor;
    QString editorial;
    int anio;
    QString tipo;


};





#endif // LIBRO_H
