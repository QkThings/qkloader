/****************************************************************************
** Meta object code from reading C++ file 'efm32loader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../efm32loader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'efm32loader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EFM32Loader_t {
    QByteArrayData data[8];
    char stringdata[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_EFM32Loader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_EFM32Loader_t qt_meta_stringdata_EFM32Loader = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 6),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 4),
QT_MOC_LITERAL(4, 25, 8),
QT_MOC_LITERAL(5, 34, 5),
QT_MOC_LITERAL(6, 40, 6),
QT_MOC_LITERAL(7, 47, 8)
    },
    "EFM32Loader\0output\0\0open\0portName\0"
    "close\0upload\0filePath\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EFM32Loader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    1,   37,    2, 0x0a,
       5,    0,   40,    2, 0x0a,
       6,    1,   41,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,    7,

       0        // eod
};

void EFM32Loader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EFM32Loader *_t = static_cast<EFM32Loader *>(_o);
        switch (_id) {
        case 0: _t->output((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { bool _r = _t->open((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: _t->close(); break;
        case 3: { bool _r = _t->upload((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EFM32Loader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EFM32Loader::output)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject EFM32Loader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EFM32Loader.data,
      qt_meta_data_EFM32Loader,  qt_static_metacall, 0, 0}
};


const QMetaObject *EFM32Loader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EFM32Loader::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EFM32Loader.stringdata))
        return static_cast<void*>(const_cast< EFM32Loader*>(this));
    return QObject::qt_metacast(_clname);
}

int EFM32Loader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void EFM32Loader::output(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
