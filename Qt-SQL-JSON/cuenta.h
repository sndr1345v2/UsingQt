#ifndef CUENTA_H
#define CUENTA_H
#include <Qstring>
using namespace std;

class Cuenta
{

private:

    QString mail;
    QString name;
    QString password;
public:

    Cuenta();
    Cuenta(QString, QString, QString);
    QString getMail() const;
    void setMail(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);

};


#endif // CUENTA_H
