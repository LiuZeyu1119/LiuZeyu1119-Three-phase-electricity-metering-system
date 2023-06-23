/****************************************************************************
** Meta object code from reading C++ file 'sqlite.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../APP/sqlite/sqlite.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sqlite.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sqlite_t {
    QByteArrayData data[13];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sqlite_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sqlite_t qt_meta_stringdata_sqlite = {
    {
QT_MOC_LITERAL(0, 0, 6), // "sqlite"
QT_MOC_LITERAL(1, 7, 12), // "modelChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 16), // "dataModelChanged"
QT_MOC_LITERAL(4, 38, 8), // "setModel"
QT_MOC_LITERAL(5, 47, 1), // "m"
QT_MOC_LITERAL(6, 49, 11), // "refreshList"
QT_MOC_LITERAL(7, 61, 11), // "refreshData"
QT_MOC_LITERAL(8, 73, 11), // "targetTable"
QT_MOC_LITERAL(9, 85, 9), // "dataToQML"
QT_MOC_LITERAL(10, 95, 5), // "index"
QT_MOC_LITERAL(11, 101, 5), // "model"
QT_MOC_LITERAL(12, 107, 9) // "dataModel"

    },
    "sqlite\0modelChanged\0\0dataModelChanged\0"
    "setModel\0m\0refreshList\0refreshData\0"
    "targetTable\0dataToQML\0index\0model\0"
    "dataModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sqlite[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   46,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       6,    0,   49,    2, 0x02 /* Public */,
       7,    1,   50,    2, 0x02 /* Public */,
       9,    1,   53,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::QString, QMetaType::Int,   10,

 // properties: name, type, flags
      11, QMetaType::QStringList, 0x00495003,
      12, QMetaType::QStringList, 0x00495003,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void sqlite::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<sqlite *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modelChanged(); break;
        case 1: _t->dataModelChanged(); break;
        case 2: _t->setModel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->refreshList(); break;
        case 4: _t->refreshData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: { QString _r = _t->dataToQML((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (sqlite::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlite::modelChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (sqlite::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&sqlite::dataModelChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<sqlite *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QStringList*>(_v) = _t->m_model; break;
        case 1: *reinterpret_cast< QStringList*>(_v) = _t->m_dataModel; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<sqlite *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->m_model != *reinterpret_cast< QStringList*>(_v)) {
                _t->m_model = *reinterpret_cast< QStringList*>(_v);
                Q_EMIT _t->modelChanged();
            }
            break;
        case 1:
            if (_t->m_dataModel != *reinterpret_cast< QStringList*>(_v)) {
                _t->m_dataModel = *reinterpret_cast< QStringList*>(_v);
                Q_EMIT _t->dataModelChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject sqlite::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_sqlite.data,
    qt_meta_data_sqlite,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *sqlite::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sqlite::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sqlite.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int sqlite::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void sqlite::modelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void sqlite::dataModelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
