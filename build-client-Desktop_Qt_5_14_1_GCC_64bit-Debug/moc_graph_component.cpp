/****************************************************************************
** Meta object code from reading C++ file 'graph_component.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../client/graph_component.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'graph_component.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_graph_component_leaf_t {
    QByteArrayData data[8];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graph_component_leaf_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graph_component_leaf_t qt_meta_stringdata_graph_component_leaf = {
    {
QT_MOC_LITERAL(0, 0, 20), // "graph_component_leaf"
QT_MOC_LITERAL(1, 21, 8), // "set_data"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 30), // "QVector<QPair<QColor,qint32> >"
QT_MOC_LITERAL(4, 62, 4), // "data"
QT_MOC_LITERAL(5, 67, 5), // "clear"
QT_MOC_LITERAL(6, 73, 6), // "remove"
QT_MOC_LITERAL(7, 80, 4) // "mark"

    },
    "graph_component_leaf\0set_data\0\0"
    "QVector<QPair<QColor,qint32> >\0data\0"
    "clear\0remove\0mark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graph_component_leaf[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    0,   32,    2, 0x0a /* Public */,
       6,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    7,

       0        // eod
};

void graph_component_leaf::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<graph_component_leaf *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set_data((*reinterpret_cast< QVector<QPair<QColor,qint32> >(*)>(_a[1]))); break;
        case 1: _t->clear(); break;
        case 2: _t->remove((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject graph_component_leaf::staticMetaObject = { {
    QMetaObject::SuperData::link<QChartView::staticMetaObject>(),
    qt_meta_stringdata_graph_component_leaf.data,
    qt_meta_data_graph_component_leaf,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *graph_component_leaf::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graph_component_leaf::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_graph_component_leaf.stringdata0))
        return static_cast<void*>(this);
    return QChartView::qt_metacast(_clname);
}

int graph_component_leaf::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChartView::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_graph_component_t {
    QByteArrayData data[10];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_graph_component_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_graph_component_t qt_meta_stringdata_graph_component = {
    {
QT_MOC_LITERAL(0, 0, 15), // "graph_component"
QT_MOC_LITERAL(1, 16, 4), // "show"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "num"
QT_MOC_LITERAL(4, 26, 8), // "set_data"
QT_MOC_LITERAL(5, 35, 40), // "QVector<QPair<QColor,QVector<..."
QT_MOC_LITERAL(6, 76, 4), // "data"
QT_MOC_LITERAL(7, 81, 5), // "clear"
QT_MOC_LITERAL(8, 87, 6), // "remove"
QT_MOC_LITERAL(9, 94, 4) // "mark"

    },
    "graph_component\0show\0\0num\0set_data\0"
    "QVector<QPair<QColor,QVector<qint32> > >\0"
    "data\0clear\0remove\0mark"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_graph_component[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       7,    0,   40,    2, 0x0a /* Public */,
       8,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    9,

       0        // eod
};

void graph_component::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<graph_component *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->show((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->set_data((*reinterpret_cast< QVector<QPair<QColor,QVector<qint32> > >(*)>(_a[1]))); break;
        case 2: _t->clear(); break;
        case 3: _t->remove((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject graph_component::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseComponent::staticMetaObject>(),
    qt_meta_stringdata_graph_component.data,
    qt_meta_data_graph_component,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *graph_component::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *graph_component::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_graph_component.stringdata0))
        return static_cast<void*>(this);
    return BaseComponent::qt_metacast(_clname);
}

int graph_component::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseComponent::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
