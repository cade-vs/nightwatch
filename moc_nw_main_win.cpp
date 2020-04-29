/****************************************************************************
** Meta object code from reading C++ file 'nw_main_win.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "nw_main_win.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'nw_main_win.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NWPoster_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NWPoster_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NWPoster_t qt_meta_stringdata_NWPoster = {
    {
QT_MOC_LITERAL(0, 0, 8) // "NWPoster"

    },
    "NWPoster"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NWPoster[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void NWPoster::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject NWPoster::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NWPoster.data,
      qt_meta_data_NWPoster,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NWPoster::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NWPoster::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NWPoster.stringdata0))
        return static_cast<void*>(const_cast< NWPoster*>(this));
    return QWidget::qt_metacast(_clname);
}

int NWPoster::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_NWTreeWidget_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NWTreeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NWTreeWidget_t qt_meta_stringdata_NWTreeWidget = {
    {
QT_MOC_LITERAL(0, 0, 12) // "NWTreeWidget"

    },
    "NWTreeWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NWTreeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void NWTreeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject NWTreeWidget::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_NWTreeWidget.data,
      qt_meta_data_NWTreeWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NWTreeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NWTreeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NWTreeWidget.stringdata0))
        return static_cast<void*>(const_cast< NWTreeWidget*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int NWTreeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_NWMainWindow_t {
    QByteArrayData data[37];
    char stringdata0[483];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NWMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NWMainWindow_t qt_meta_stringdata_NWMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NWMainWindow"
QT_MOC_LITERAL(1, 13, 17), // "toggleSortColumns"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 5), // "enter"
QT_MOC_LITERAL(4, 38, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(5, 55, 4), // "item"
QT_MOC_LITERAL(6, 60, 12), // "enterCurrent"
QT_MOC_LITERAL(7, 73, 15), // "actionTriggered"
QT_MOC_LITERAL(8, 89, 8), // "QAction*"
QT_MOC_LITERAL(9, 98, 6), // "action"
QT_MOC_LITERAL(10, 105, 21), // "switchLayoutDirection"
QT_MOC_LITERAL(11, 127, 17), // "slotItemActivated"
QT_MOC_LITERAL(12, 145, 6), // "column"
QT_MOC_LITERAL(13, 152, 22), // "slotCurrentItemChanged"
QT_MOC_LITERAL(14, 175, 7), // "current"
QT_MOC_LITERAL(15, 183, 8), // "previous"
QT_MOC_LITERAL(16, 192, 20), // "slotLoadCurrentImage"
QT_MOC_LITERAL(17, 213, 13), // "slotNewWindow"
QT_MOC_LITERAL(18, 227, 8), // "slotGoUp"
QT_MOC_LITERAL(19, 236, 10), // "slotThumbs"
QT_MOC_LITERAL(20, 247, 16), // "slotCreateThumbs"
QT_MOC_LITERAL(21, 264, 14), // "slotJPEGThumbs"
QT_MOC_LITERAL(22, 279, 16), // "slotSmoothThumbs"
QT_MOC_LITERAL(23, 296, 13), // "slotDirThumbs"
QT_MOC_LITERAL(24, 310, 13), // "slotChangeDir"
QT_MOC_LITERAL(25, 324, 11), // "slotHomeDir"
QT_MOC_LITERAL(26, 336, 13), // "slotReloadDir"
QT_MOC_LITERAL(27, 350, 16), // "slotShowDirsOnly"
QT_MOC_LITERAL(28, 367, 10), // "slotGoNext"
QT_MOC_LITERAL(29, 378, 10), // "slotGoPrev"
QT_MOC_LITERAL(30, 389, 13), // "slotGoNextDir"
QT_MOC_LITERAL(31, 403, 13), // "slotGoPrevDir"
QT_MOC_LITERAL(32, 417, 15), // "slotSortColumn1"
QT_MOC_LITERAL(33, 433, 15), // "slotSortColumn3"
QT_MOC_LITERAL(34, 449, 14), // "slotRandomItem"
QT_MOC_LITERAL(35, 464, 8), // "slotHelp"
QT_MOC_LITERAL(36, 473, 9) // "slotAbout"

    },
    "NWMainWindow\0toggleSortColumns\0\0enter\0"
    "QTreeWidgetItem*\0item\0enterCurrent\0"
    "actionTriggered\0QAction*\0action\0"
    "switchLayoutDirection\0slotItemActivated\0"
    "column\0slotCurrentItemChanged\0current\0"
    "previous\0slotLoadCurrentImage\0"
    "slotNewWindow\0slotGoUp\0slotThumbs\0"
    "slotCreateThumbs\0slotJPEGThumbs\0"
    "slotSmoothThumbs\0slotDirThumbs\0"
    "slotChangeDir\0slotHomeDir\0slotReloadDir\0"
    "slotShowDirsOnly\0slotGoNext\0slotGoPrev\0"
    "slotGoNextDir\0slotGoPrevDir\0slotSortColumn1\0"
    "slotSortColumn3\0slotRandomItem\0slotHelp\0"
    "slotAbout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NWMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  154,    2, 0x0a /* Public */,
       3,    1,  155,    2, 0x0a /* Public */,
       6,    0,  158,    2, 0x0a /* Public */,
       7,    1,  159,    2, 0x0a /* Public */,
      10,    0,  162,    2, 0x0a /* Public */,
      11,    2,  163,    2, 0x0a /* Public */,
      13,    2,  168,    2, 0x0a /* Public */,
      16,    0,  173,    2, 0x0a /* Public */,
      17,    0,  174,    2, 0x0a /* Public */,
      18,    0,  175,    2, 0x0a /* Public */,
      19,    0,  176,    2, 0x0a /* Public */,
      20,    0,  177,    2, 0x0a /* Public */,
      21,    0,  178,    2, 0x0a /* Public */,
      22,    0,  179,    2, 0x0a /* Public */,
      23,    0,  180,    2, 0x0a /* Public */,
      24,    0,  181,    2, 0x0a /* Public */,
      25,    0,  182,    2, 0x0a /* Public */,
      26,    0,  183,    2, 0x0a /* Public */,
      27,    0,  184,    2, 0x0a /* Public */,
      28,    0,  185,    2, 0x0a /* Public */,
      29,    0,  186,    2, 0x0a /* Public */,
      30,    0,  187,    2, 0x0a /* Public */,
      31,    0,  188,    2, 0x0a /* Public */,
      32,    0,  189,    2, 0x0a /* Public */,
      33,    0,  190,    2, 0x0a /* Public */,
      34,    0,  191,    2, 0x0a /* Public */,
      35,    0,  192,    2, 0x0a /* Public */,
      36,    0,  193,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,   12,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 4,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NWMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NWMainWindow *_t = static_cast<NWMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleSortColumns(); break;
        case 1: _t->enter((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->enterCurrent(); break;
        case 3: _t->actionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->switchLayoutDirection(); break;
        case 5: _t->slotItemActivated((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slotCurrentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 7: _t->slotLoadCurrentImage(); break;
        case 8: _t->slotNewWindow(); break;
        case 9: _t->slotGoUp(); break;
        case 10: _t->slotThumbs(); break;
        case 11: _t->slotCreateThumbs(); break;
        case 12: _t->slotJPEGThumbs(); break;
        case 13: _t->slotSmoothThumbs(); break;
        case 14: _t->slotDirThumbs(); break;
        case 15: _t->slotChangeDir(); break;
        case 16: _t->slotHomeDir(); break;
        case 17: _t->slotReloadDir(); break;
        case 18: _t->slotShowDirsOnly(); break;
        case 19: _t->slotGoNext(); break;
        case 20: _t->slotGoPrev(); break;
        case 21: _t->slotGoNextDir(); break;
        case 22: _t->slotGoPrevDir(); break;
        case 23: _t->slotSortColumn1(); break;
        case 24: _t->slotSortColumn3(); break;
        case 25: _t->slotRandomItem(); break;
        case 26: _t->slotHelp(); break;
        case 27: _t->slotAbout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject NWMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_NWMainWindow.data,
      qt_meta_data_NWMainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NWMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NWMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NWMainWindow.stringdata0))
        return static_cast<void*>(const_cast< NWMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int NWMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
