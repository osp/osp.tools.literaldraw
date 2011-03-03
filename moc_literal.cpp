/****************************************************************************
** Meta object code from reading C++ file 'literal.h'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "literal.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'literal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Literal[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      23,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   36,    8,    8, 0x0a,
      67,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Literal[] = {
    "Literal\0\0textChanged()\0posChanged()\0"
    "x,y\0insertPoint(double,double)\0"
    "updateNamesView()\0"
};

const QMetaObject Literal::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Literal,
      qt_meta_data_Literal, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Literal::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Literal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Literal::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Literal))
        return static_cast<void*>(const_cast< Literal*>(this));
    return QWidget::qt_metacast(_clname);
}

int Literal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textChanged(); break;
        case 1: posChanged(); break;
        case 2: insertPoint((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: updateNamesView(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Literal::textChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Literal::posChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
