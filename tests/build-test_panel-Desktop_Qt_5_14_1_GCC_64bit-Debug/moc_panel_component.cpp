/****************************************************************************
** Meta object code from reading C++ file 'panel_component.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../client/panel_component.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panel_component.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_panel_component_leaf_t {
    QByteArrayData data[4];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_panel_component_leaf_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_panel_component_leaf_t qt_meta_stringdata_panel_component_leaf = {
    {
QT_MOC_LITERAL(0, 0, 20), // "panel_component_leaf"
QT_MOC_LITERAL(1, 21, 8), // "get_data"
QT_MOC_LITERAL(2, 30, 21), // "QPair<QString,qint32>"
QT_MOC_LITERAL(3, 52, 0) // ""

    },
    "panel_component_leaf\0get_data\0"
    "QPair<QString,qint32>\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_panel_component_leaf[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    3, 0x0a /* Public */,

 // slots: parameters
    0x80000000 | 2,

       0        // eod
};

void panel_component_leaf::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<panel_component_leaf *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QPair<QString,qint32> _r = _t->get_data();
            if (_a[0]) *reinterpret_cast< QPair<QString,qint32>*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject panel_component_leaf::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_panel_component_leaf.data,
    qt_meta_data_panel_component_leaf,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *panel_component_leaf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *panel_component_leaf::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_panel_component_leaf.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int panel_component_leaf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_panel_component_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_panel_component_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_panel_component_t qt_meta_stringdata_panel_component = {
    {
QT_MOC_LITERAL(0, 0, 15), // "panel_component"
QT_MOC_LITERAL(1, 16, 8), // "get_data"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "panel_component\0get_data\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_panel_component[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void panel_component::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<panel_component *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->get_data(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject panel_component::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseComponent::staticMetaObject>(),
    qt_meta_stringdata_panel_component.data,
    qt_meta_data_panel_component,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *panel_component::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *panel_component::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_panel_component.stringdata0))
        return static_cast<void*>(this);
    return BaseComponent::qt_metacast(_clname);
}

int panel_component::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseComponent::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
