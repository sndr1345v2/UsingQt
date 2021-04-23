/********************************************************************************
** Form generated from reading UI file 'menu_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_DIALOG_H
#define UI_MENU_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_menu_dialog
{
public:
    QTabWidget *Menu;
    QWidget *tab_inicio;
    QWidget *widget_antologia;
    QPushButton *biografia_PB;
    QPushButton *expositivo_PB;
    QPushButton *narrativa_PB;
    QPushButton *poesia_PB;
    QPushButton *antologia_PB;
    QPushButton *drama_PB;
    QPushButton *espistolar_PB;
    QPushButton *obragrafica_PB;
    QPushButton *referencia_PB;
    QPushButton *clasico_PB;
    QTableView *tableView;
    QLineEdit *buscar_LE;
    QPushButton *mostrarLibros;
    QComboBox *comboBox_sortLibros;
    QLineEdit *user_LE;
    QWidget *tab_mislibros;
    QLineEdit *buscar_misLibros_LE;
    QTableView *misLibros;
    QComboBox *comboBox_sortMislibros;
    QWidget *tab_fav;
    QTableView *favoritos;
    QLineEdit *buscar_favoritos_LE;
    QComboBox *comboBox_sortFavoritos;
    QWidget *tab_perfil;
    QLabel *usuarioL;
    QLineEdit *usuario_LE;
    QLabel *label_5;
    QLineEdit *correo_LE;
    QLabel *label_4;
    QLineEdit *cont_LE;
    QPushButton *editar_usrPB;
    QPushButton *editar_cePB;
    QPushButton *editar_con;
    QLabel *label_2;

    void setupUi(QDialog *menu_dialog)
    {
        if (menu_dialog->objectName().isEmpty())
            menu_dialog->setObjectName(QString::fromUtf8("menu_dialog"));
        menu_dialog->resize(1231, 646);
        Menu = new QTabWidget(menu_dialog);
        Menu->setObjectName(QString::fromUtf8("Menu"));
        Menu->setGeometry(QRect(0, 30, 1301, 671));
        tab_inicio = new QWidget();
        tab_inicio->setObjectName(QString::fromUtf8("tab_inicio"));
        widget_antologia = new QWidget(tab_inicio);
        widget_antologia->setObjectName(QString::fromUtf8("widget_antologia"));
        widget_antologia->setGeometry(QRect(0, 20, 1781, 731));
        biografia_PB = new QPushButton(widget_antologia);
        biografia_PB->setObjectName(QString::fromUtf8("biografia_PB"));
        biografia_PB->setGeometry(QRect(200, 20, 151, 91));
        expositivo_PB = new QPushButton(widget_antologia);
        expositivo_PB->setObjectName(QString::fromUtf8("expositivo_PB"));
        expositivo_PB->setGeometry(QRect(200, 130, 151, 91));
        narrativa_PB = new QPushButton(widget_antologia);
        narrativa_PB->setObjectName(QString::fromUtf8("narrativa_PB"));
        narrativa_PB->setGeometry(QRect(200, 240, 151, 91));
        poesia_PB = new QPushButton(widget_antologia);
        poesia_PB->setObjectName(QString::fromUtf8("poesia_PB"));
        poesia_PB->setGeometry(QRect(200, 350, 151, 91));
        antologia_PB = new QPushButton(widget_antologia);
        antologia_PB->setObjectName(QString::fromUtf8("antologia_PB"));
        antologia_PB->setGeometry(QRect(20, 20, 151, 91));
        drama_PB = new QPushButton(widget_antologia);
        drama_PB->setObjectName(QString::fromUtf8("drama_PB"));
        drama_PB->setGeometry(QRect(20, 130, 151, 91));
        espistolar_PB = new QPushButton(widget_antologia);
        espistolar_PB->setObjectName(QString::fromUtf8("espistolar_PB"));
        espistolar_PB->setGeometry(QRect(20, 240, 151, 91));
        obragrafica_PB = new QPushButton(widget_antologia);
        obragrafica_PB->setObjectName(QString::fromUtf8("obragrafica_PB"));
        obragrafica_PB->setGeometry(QRect(20, 350, 151, 91));
        referencia_PB = new QPushButton(widget_antologia);
        referencia_PB->setObjectName(QString::fromUtf8("referencia_PB"));
        referencia_PB->setGeometry(QRect(20, 460, 151, 91));
        clasico_PB = new QPushButton(widget_antologia);
        clasico_PB->setObjectName(QString::fromUtf8("clasico_PB"));
        clasico_PB->setGeometry(QRect(200, 460, 151, 91));
        tableView = new QTableView(widget_antologia);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(390, 70, 821, 481));
        buscar_LE = new QLineEdit(widget_antologia);
        buscar_LE->setObjectName(QString::fromUtf8("buscar_LE"));
        buscar_LE->setGeometry(QRect(930, 40, 281, 20));
        mostrarLibros = new QPushButton(widget_antologia);
        mostrarLibros->setObjectName(QString::fromUtf8("mostrarLibros"));
        mostrarLibros->setGeometry(QRect(390, 20, 111, 41));
        comboBox_sortLibros = new QComboBox(widget_antologia);
        comboBox_sortLibros->setObjectName(QString::fromUtf8("comboBox_sortLibros"));
        comboBox_sortLibros->setGeometry(QRect(800, 40, 121, 21));
        user_LE = new QLineEdit(tab_inicio);
        user_LE->setObjectName(QString::fromUtf8("user_LE"));
        user_LE->setGeometry(QRect(1100, 0, 113, 20));
        Menu->addTab(tab_inicio, QString());
        tab_mislibros = new QWidget();
        tab_mislibros->setObjectName(QString::fromUtf8("tab_mislibros"));
        buscar_misLibros_LE = new QLineEdit(tab_mislibros);
        buscar_misLibros_LE->setObjectName(QString::fromUtf8("buscar_misLibros_LE"));
        buscar_misLibros_LE->setGeometry(QRect(700, 50, 481, 20));
        misLibros = new QTableView(tab_mislibros);
        misLibros->setObjectName(QString::fromUtf8("misLibros"));
        misLibros->setGeometry(QRect(20, 80, 1161, 311));
        comboBox_sortMislibros = new QComboBox(tab_mislibros);
        comboBox_sortMislibros->setObjectName(QString::fromUtf8("comboBox_sortMislibros"));
        comboBox_sortMislibros->setGeometry(QRect(590, 50, 101, 20));
        Menu->addTab(tab_mislibros, QString());
        tab_fav = new QWidget();
        tab_fav->setObjectName(QString::fromUtf8("tab_fav"));
        favoritos = new QTableView(tab_fav);
        favoritos->setObjectName(QString::fromUtf8("favoritos"));
        favoritos->setGeometry(QRect(20, 80, 1171, 491));
        buscar_favoritos_LE = new QLineEdit(tab_fav);
        buscar_favoritos_LE->setObjectName(QString::fromUtf8("buscar_favoritos_LE"));
        buscar_favoritos_LE->setGeometry(QRect(700, 50, 491, 20));
        comboBox_sortFavoritos = new QComboBox(tab_fav);
        comboBox_sortFavoritos->setObjectName(QString::fromUtf8("comboBox_sortFavoritos"));
        comboBox_sortFavoritos->setGeometry(QRect(590, 50, 101, 21));
        Menu->addTab(tab_fav, QString());
        tab_perfil = new QWidget();
        tab_perfil->setObjectName(QString::fromUtf8("tab_perfil"));
        usuarioL = new QLabel(tab_perfil);
        usuarioL->setObjectName(QString::fromUtf8("usuarioL"));
        usuarioL->setGeometry(QRect(40, 40, 47, 13));
        usuario_LE = new QLineEdit(tab_perfil);
        usuario_LE->setObjectName(QString::fromUtf8("usuario_LE"));
        usuario_LE->setGeometry(QRect(150, 40, 161, 20));
        label_5 = new QLabel(tab_perfil);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 80, 91, 16));
        correo_LE = new QLineEdit(tab_perfil);
        correo_LE->setObjectName(QString::fromUtf8("correo_LE"));
        correo_LE->setGeometry(QRect(150, 80, 161, 20));
        label_4 = new QLabel(tab_perfil);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 120, 91, 16));
        cont_LE = new QLineEdit(tab_perfil);
        cont_LE->setObjectName(QString::fromUtf8("cont_LE"));
        cont_LE->setGeometry(QRect(150, 120, 161, 20));
        cont_LE->setEchoMode(QLineEdit::Password);
        editar_usrPB = new QPushButton(tab_perfil);
        editar_usrPB->setObjectName(QString::fromUtf8("editar_usrPB"));
        editar_usrPB->setGeometry(QRect(320, 40, 71, 21));
        editar_cePB = new QPushButton(tab_perfil);
        editar_cePB->setObjectName(QString::fromUtf8("editar_cePB"));
        editar_cePB->setGeometry(QRect(320, 80, 71, 20));
        editar_con = new QPushButton(tab_perfil);
        editar_con->setObjectName(QString::fromUtf8("editar_con"));
        editar_con->setGeometry(QRect(320, 120, 71, 20));
        Menu->addTab(tab_perfil, QString());
        label_2 = new QLabel(menu_dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(600, 20, 47, 13));

        retranslateUi(menu_dialog);

        Menu->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(menu_dialog);
    } // setupUi

    void retranslateUi(QDialog *menu_dialog)
    {
        menu_dialog->setWindowTitle(QCoreApplication::translate("menu_dialog", "Bookin", nullptr));
        biografia_PB->setText(QCoreApplication::translate("menu_dialog", "Biograf\303\255a", nullptr));
        expositivo_PB->setText(QCoreApplication::translate("menu_dialog", "Expositivo", nullptr));
        narrativa_PB->setText(QCoreApplication::translate("menu_dialog", "Narrativa", nullptr));
        poesia_PB->setText(QCoreApplication::translate("menu_dialog", "Poes\303\255a", nullptr));
        antologia_PB->setText(QCoreApplication::translate("menu_dialog", "Antologia", nullptr));
        drama_PB->setText(QCoreApplication::translate("menu_dialog", "Drama", nullptr));
        espistolar_PB->setText(QCoreApplication::translate("menu_dialog", "Epistolar", nullptr));
        obragrafica_PB->setText(QCoreApplication::translate("menu_dialog", "Obra gr\303\241fica", nullptr));
        referencia_PB->setText(QCoreApplication::translate("menu_dialog", "Referencia", nullptr));
        clasico_PB->setText(QCoreApplication::translate("menu_dialog", "Cl\303\241sico", nullptr));
        mostrarLibros->setText(QCoreApplication::translate("menu_dialog", "LIBROS", nullptr));
        Menu->setTabText(Menu->indexOf(tab_inicio), QCoreApplication::translate("menu_dialog", "Inicio", nullptr));
        Menu->setTabText(Menu->indexOf(tab_mislibros), QCoreApplication::translate("menu_dialog", "Mis libros", nullptr));
        Menu->setTabText(Menu->indexOf(tab_fav), QCoreApplication::translate("menu_dialog", "Favoritos", nullptr));
        usuarioL->setText(QCoreApplication::translate("menu_dialog", "Usuario:", nullptr));
        label_5->setText(QCoreApplication::translate("menu_dialog", "Correo electr\303\263nico:", nullptr));
        label_4->setText(QCoreApplication::translate("menu_dialog", "Contrase\303\261a:", nullptr));
        editar_usrPB->setText(QCoreApplication::translate("menu_dialog", "Editar", nullptr));
        editar_cePB->setText(QCoreApplication::translate("menu_dialog", "Editar", nullptr));
        editar_con->setText(QCoreApplication::translate("menu_dialog", "Editar", nullptr));
        Menu->setTabText(Menu->indexOf(tab_perfil), QCoreApplication::translate("menu_dialog", "Perfil", nullptr));
        label_2->setText(QCoreApplication::translate("menu_dialog", "BOOKIN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class menu_dialog: public Ui_menu_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_DIALOG_H
