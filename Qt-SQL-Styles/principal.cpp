#include "principal.h"

Principal::Principal(QObject *parent) : QObject(parent)
{
    inicio = new inicio_dialog();
    recom = new recommend_dialog();

    QObject::connect(inicio, SIGNAL(inicia_recomend(bool)), this, SLOT(start_recom()));
    QObject::connect(inicio, SIGNAL(envia_datos_usuario(QString,QPixmap)), recom, SLOT(recibe_datos_usuario(QString,QPixmap)));
    QObject::connect(recom, SIGNAL(regresa_inicio(bool)), this, SLOT(start_inicio(bool)));
}

void Principal::start()
{
    inicio->exec();
}

void Principal::start_recom()
{
    inicio->hide();
    recom->exec();

}

void Principal::start_inicio(bool requerido)
{
    if (requerido == true){
        recom->hide();
        inicio->show();
    }

}
