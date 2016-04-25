/****************************************************************************
** Meta object code from reading C++ file 'BV_OpenGL.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/BV_OpenGL.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BV_OpenGL.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BV_OpenGL_t {
    QByteArrayData data[11];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BV_OpenGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BV_OpenGL_t qt_meta_stringdata_BV_OpenGL = {
    {
QT_MOC_LITERAL(0, 0, 9), // "BV_OpenGL"
QT_MOC_LITERAL(1, 10, 5), // "label"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "text"
QT_MOC_LITERAL(4, 22, 5), // "light"
QT_MOC_LITERAL(5, 28, 12), // "set_dropdown"
QT_MOC_LITERAL(6, 41, 3), // "sel"
QT_MOC_LITERAL(7, 45, 10), // "set_slider"
QT_MOC_LITERAL(8, 56, 1), // "z"
QT_MOC_LITERAL(9, 58, 14), // "button_pressed"
QT_MOC_LITERAL(10, 73, 5) // "reset"

    },
    "BV_OpenGL\0label\0\0text\0light\0set_dropdown\0"
    "sel\0set_slider\0z\0button_pressed\0reset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BV_OpenGL[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       9,    0,   56,    2, 0x0a /* Public */,
      10,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BV_OpenGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BV_OpenGL *_t = static_cast<BV_OpenGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->label((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->light((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->set_dropdown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->set_slider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->button_pressed(); break;
        case 5: _t->reset(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BV_OpenGL::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BV_OpenGL::label)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BV_OpenGL::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BV_OpenGL::light)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject BV_OpenGL::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_BV_OpenGL.data,
      qt_meta_data_BV_OpenGL,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *BV_OpenGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BV_OpenGL::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_BV_OpenGL.stringdata0))
        return static_cast<void*>(const_cast< BV_OpenGL*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int BV_OpenGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void BV_OpenGL::label(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BV_OpenGL::light(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
