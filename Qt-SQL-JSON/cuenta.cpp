#include "cuenta.h"

Cuenta::Cuenta()
{

}

Cuenta::Cuenta(QString _name, QString _mail, QString _pass)
{
    name = _name;
    mail = _mail;
    password = _pass;


}

QString Cuenta::getMail() const
{
    return mail;
}

void Cuenta::setMail(const QString &value)
{
    mail=value;
}

QString Cuenta::getName() const
{
    return name;
}

void Cuenta::setName(const QString &value)
{
    name=value;
}

QString Cuenta::getPassword() const
{
    return password;
}

void Cuenta::setPassword(const QString &value)
{
    password=value;
}


