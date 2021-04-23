#include "libro.h"

Libro::Libro()
{

}

void Libro::set_titulo(QString tit)
{
    titulo=tit;
}

QString Libro::get_titulo()const
{
    return titulo;
}

void Libro::set_autor(QString aut)
{
    autor=aut;
}

QString Libro::get_autor()const
{
    return autor;
}

void Libro::set_editorial(QString edit)
{
    editorial=edit;
}

QString Libro::get_editorial()const
{
    return editorial;
}

void Libro::set_anio(int ani)
{
    anio=ani;
}

int Libro::get_anio()const
{
    return anio;
}

void Libro::set_tipo(QString tip)
{
    tipo=tip;
}

QString Libro::get_tipo()const
{
    return tipo;
}



Libro::Libro(QString titulo, QString autor, QString editorial,int anio, QString tipo)
{
    this->titulo = titulo;
    this->autor = autor;
    this->editorial = editorial;

    this->anio = anio;

    this->tipo = tipo;

}


Libro::Libro(QString c)//Constructor que toma una cadena, o sea, un archivo y una vez adentro pone los valores en la cuenta
{
   /* QString tit = "";
    QString aut = "";
    QString edi = "";
    QString ani = "";
    QString tip = "";


    int i;
    for(i=0; c[i]!='|'; i++ )
    {
        tit+=c[i];

    }
    for(i++; c[i]!= '|'; i++ )
    {
        aut+=c[i];

    }
    for(i++; c[i]!= '|'; i++ )
    {
        edi+=c[i];
    }
    for(i++; c[i]!= '|'; i++ )
    {
        ani +=c[i];

    }
    for(i++;c[i]!=' '; i++)
    {
        tip +=c[i];
        if(c[i]=='\0')
        {
            break;
        }

    }




    titulo=tit;
    autor=aut;
    editorial=edi;
    anio=ani;
    tipo=tip;
    //Cuenta(usr,cE,nom,pass);*/

}

QString Libro::toString()
{
    QString r = "";
    r = titulo +" "+ autor+ " "+ editorial +" "+ anio+" "+tipo;
    return r;
}

QString Libro::toFile()
{

    QString r = "";
    r = titulo + "|" + autor+ "|" + editorial +"|"+ anio+ "|" + tipo;
    return r;
}


