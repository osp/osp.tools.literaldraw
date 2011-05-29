/****************************************************************************
** Meta object code from reading C++ file 'draw.h'
**
** Created: Thu Apr 14 15:53:33 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "draw.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'draw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Draw[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    6,    5,    5, 0x05,
      32,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,    5,    5,    5, 0x08,
      69,   65,    5,    5, 0x08,
      93,   89,    5,    5, 0x08,
     118,    5,    5,    5, 0x08,
     134,    5,    5,    5, 0x0a,
     152,  148,    5,    5, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Draw[] = {
    "Draw\0\0,\0posClick(double,double)\0"
    "somethingChange()\0moveCoord(int)\0pos\0"
    "updateCoord(QPoint)\0x,y\0"
    "moveCross(double,double)\0updateSize(int)\0"
    "updateScene()\0w,h\0sceneRect(double,double)\0"
};

const QMetaObject Draw::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Draw,
      qt_meta_data_Draw, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Draw::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Draw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Draw::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Draw))
        return static_cast<void*>(const_cast< Draw*>(this));
    return QWidget::qt_metacast(_clname);
}

int Draw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: posClick((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: somethingChange(); break;
        case 2: moveCoord((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: updateCoord((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: moveCross((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 5: updateSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: updateScene(); break;
        case 7: sceneRect((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Draw::posClick(double _t1, double _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Draw::somethingChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
