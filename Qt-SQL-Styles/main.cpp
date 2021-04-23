#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>
#include <QDebug>
#include <QApplication>
#include <principal.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Principal principal;
    principal.start();

    return a.exec();

}
