#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include <inicio_dialog.h>
#include <recommend_dialog.h>
#include <QObject>

class Principal : public QObject
{
    Q_OBJECT

private:

public:
    explicit Principal(QObject *parent = nullptr);
    inicio_dialog *inicio;
    recommend_dialog *recom;

    void start();

public slots:
    void start_recom();
   void start_inicio(bool);

};

#endif // PRINCIPAL_H
