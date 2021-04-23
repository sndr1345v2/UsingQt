/****************************************************************************
** Meta object code from reading C++ file 'inicio_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../inicio_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inicio_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_inicio_dialog_t {
    QByteArrayData data[12];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_inicio_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_inicio_dialog_t qt_meta_stringdata_inicio_dialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "inicio_dialog"
QT_MOC_LITERAL(1, 14, 12), // "enviaUsuario"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 9), // "registrar"
QT_MOC_LITERAL(4, 38, 7), // "mostrar"
QT_MOC_LITERAL(5, 46, 5), // "pasar"
QT_MOC_LITERAL(6, 52, 25), // "on_usuario_LE_textChanged"
QT_MOC_LITERAL(7, 78, 4), // "arg1"
QT_MOC_LITERAL(8, 83, 24), // "on_contra_LE_textChanged"
QT_MOC_LITERAL(9, 108, 21), // "on_iniciar_PB_clicked"
QT_MOC_LITERAL(10, 130, 23), // "on_registrar_PB_clicked"
QT_MOC_LITERAL(11, 154, 18) // "on_user_PB_clicked"

    },
    "inicio_dialog\0enviaUsuario\0\0registrar\0"
    "mostrar\0pasar\0on_usuario_LE_textChanged\0"
    "arg1\0on_contra_LE_textChanged\0"
    "on_iniciar_PB_clicked\0on_registrar_PB_clicked\0"
    "on_user_PB_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_inicio_dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       3,    0,   64,    2, 0x06 /* Public */,
       4,    0,   65,    2, 0x06 /* Public */,
       5,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   67,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void inicio_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<inicio_dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enviaUsuario((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->registrar(); break;
        case 2: _t->mostrar(); break;
        case 3: _t->pasar(); break;
        case 4: _t->on_usuario_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_contra_LE_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_iniciar_PB_clicked(); break;
        case 7: _t->on_registrar_PB_clicked(); break;
        case 8: _t->on_user_PB_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (inicio_dialog::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inicio_dialog::enviaUsuario)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (inicio_dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inicio_dialog::registrar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (inicio_dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inicio_dialog::mostrar)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (inicio_dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&inicio_dialog::pasar)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject inicio_dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_inicio_dialog.data,
    qt_meta_data_inicio_dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *inicio_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *inicio_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_inicio_dialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int inicio_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void inicio_dialog::enviaUsuario(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void inicio_dialog::registrar()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void inicio_dialog::mostrar()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void inicio_dialog::pasar()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
