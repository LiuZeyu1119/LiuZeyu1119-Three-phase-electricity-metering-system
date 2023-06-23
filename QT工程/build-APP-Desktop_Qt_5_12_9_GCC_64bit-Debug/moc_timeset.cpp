/****************************************************************************
** Meta object code from reading C++ file 'timeset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../APP/timeset/timeset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_timeSet_t {
    QByteArrayData data[9];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_timeSet_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_timeSet_t qt_meta_stringdata_timeSet = {
    {
QT_MOC_LITERAL(0, 0, 7), // "timeSet"
QT_MOC_LITERAL(1, 8, 9), // "connected"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 9), // "readyRead"
QT_MOC_LITERAL(4, 29, 6), // "setNtp"
QT_MOC_LITERAL(5, 36, 13), // "connectsucess"
QT_MOC_LITERAL(6, 50, 16), // "readingDataGrams"
QT_MOC_LITERAL(7, 67, 12), // "setNTPServer"
QT_MOC_LITERAL(8, 80, 9) // "NTPServer"

    },
    "timeSet\0connected\0\0readyRead\0setNtp\0"
    "connectsucess\0readingDataGrams\0"
    "setNTPServer\0NTPServer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_timeSet[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       7,    1,   49,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void timeSet::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<timeSet *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->readyRead(); break;
        case 2: _t->setNtp(); break;
        case 3: _t->connectsucess(); break;
        case 4: _t->readingDataGrams(); break;
        case 5: _t->setNTPServer((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (timeSet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&timeSet::connected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (timeSet::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&timeSet::readyRead)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject timeSet::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_timeSet.data,
    qt_meta_data_timeSet,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *timeSet::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *timeSet::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_timeSet.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int timeSet::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void timeSet::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void timeSet::readyRead()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
