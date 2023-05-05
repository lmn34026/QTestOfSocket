/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[15];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "cbbLocalIPChangedEvent"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 13), // "socketOCEvent"
QT_MOC_LITERAL(4, 49, 15), // "socketOCUIEvent"
QT_MOC_LITERAL(5, 65, 7), // "rxEvent"
QT_MOC_LITERAL(6, 73, 7), // "txEvent"
QT_MOC_LITERAL(7, 81, 1), // "s"
QT_MOC_LITERAL(8, 83, 1), // "b"
QT_MOC_LITERAL(9, 85, 19), // "cbbModeChangedEvent"
QT_MOC_LITERAL(10, 105, 18), // "modeChangedUIEvent"
QT_MOC_LITERAL(11, 124, 26), // "TCPClientDisconnectedEvent"
QT_MOC_LITERAL(12, 151, 27), // "TCPServerNewConnectionEvent"
QT_MOC_LITERAL(13, 179, 29), // "TCPServerCloseConnectionEvent"
QT_MOC_LITERAL(14, 209, 18) // "txDatasFormOCEvent"

    },
    "MainWindow\0cbbLocalIPChangedEvent\0\0"
    "socketOCEvent\0socketOCUIEvent\0rxEvent\0"
    "txEvent\0s\0b\0cbbModeChangedEvent\0"
    "modeChangedUIEvent\0TCPClientDisconnectedEvent\0"
    "TCPServerNewConnectionEvent\0"
    "TCPServerCloseConnectionEvent\0"
    "txDatasFormOCEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       6,    1,   87,    2, 0x08 /* Private */,
       9,    1,   90,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      11,    0,   96,    2, 0x08 /* Private */,
      12,    0,   97,    2, 0x08 /* Private */,
      13,    0,   98,    2, 0x08 /* Private */,
      14,    0,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cbbLocalIPChangedEvent(); break;
        case 1: _t->socketOCEvent(); break;
        case 2: _t->socketOCUIEvent(); break;
        case 3: _t->rxEvent(); break;
        case 4: _t->txEvent(); break;
        case 5: _t->txEvent((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->txEvent((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->cbbModeChangedEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->modeChangedUIEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->TCPClientDisconnectedEvent(); break;
        case 10: _t->TCPServerNewConnectionEvent(); break;
        case 11: _t->TCPServerCloseConnectionEvent(); break;
        case 12: _t->txDatasFormOCEvent(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
