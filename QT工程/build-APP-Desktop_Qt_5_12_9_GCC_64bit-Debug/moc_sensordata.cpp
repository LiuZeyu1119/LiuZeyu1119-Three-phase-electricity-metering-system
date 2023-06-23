/****************************************************************************
** Meta object code from reading C++ file 'sensordata.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../APP/sensordata/sensordata.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensordata.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sensordata_t {
    QByteArrayData data[5];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sensordata_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sensordata_t qt_meta_stringdata_sensordata = {
    {
QT_MOC_LITERAL(0, 0, 10), // "sensordata"
QT_MOC_LITERAL(1, 11, 13), // "connectFailed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "mqttInit"
QT_MOC_LITERAL(4, 35, 9) // "detcMeter"

    },
    "sensordata\0connectFailed\0\0mqttInit\0"
    "detcMeter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sensordata[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Void,

       0        // eod
};

void sensordata::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sensordata *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectFailed(); break;
        case 1: { int _r = _t->mqttInit();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->detcMeter(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sensordata::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sensordata::connectFailed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject sensordata::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_sensordata.data,
    qt_meta_data_sensordata,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sensordata::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sensordata::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sensordata.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sensordata::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void sensordata::connectFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_detcMoveToThread_t {
    QByteArrayData data[9];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_detcMoveToThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_detcMoveToThread_t qt_meta_stringdata_detcMoveToThread = {
    {
QT_MOC_LITERAL(0, 0, 16), // "detcMoveToThread"
QT_MOC_LITERAL(1, 17, 15), // "dataChangedSIGN"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 8), // "dataSave"
QT_MOC_LITERAL(4, 43, 8), // "timeOver"
QT_MOC_LITERAL(5, 52, 9), // "dataToQML"
QT_MOC_LITERAL(6, 62, 5), // "index"
QT_MOC_LITERAL(7, 68, 9), // "dataToSQL"
QT_MOC_LITERAL(8, 78, 6) // "m_data"

    },
    "detcMoveToThread\0dataChangedSIGN\0\0"
    "dataSave\0timeOver\0dataToQML\0index\0"
    "dataToSQL\0m_data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_detcMoveToThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       1,   46, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       4,    0,   41,    2, 0x02 /* Public */,
       5,    1,   42,    2, 0x02 /* Public */,
       7,    0,   45,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,    6,
    QMetaType::Void,

 // properties: name, type, flags
       8, QMetaType::QString, 0x00095003,

       0        // eod
};

void detcMoveToThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<detcMoveToThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataChangedSIGN(); break;
        case 1: _t->dataSave(); break;
        case 2: _t->timeOver(); break;
        case 3: { QString _r = _t->dataToQML((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->dataToSQL(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (detcMoveToThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detcMoveToThread::dataChangedSIGN)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (detcMoveToThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&detcMoveToThread::dataSave)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<detcMoveToThread *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->m_data; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<detcMoveToThread *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_data != *reinterpret_cast< QString*>(_v)) {
                _t->m_data = *reinterpret_cast< QString*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject detcMoveToThread::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_detcMoveToThread.data,
    qt_meta_data_detcMoveToThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *detcMoveToThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *detcMoveToThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_detcMoveToThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int detcMoveToThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void detcMoveToThread::dataChangedSIGN()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void detcMoveToThread::dataSave()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
