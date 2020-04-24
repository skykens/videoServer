/****************************************************************************
** Meta object code from reading C++ file 'Texting.h'
**
** Created: Tue Oct 29 13:11:45 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Text_Press/Texting.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Texting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Texting[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      21,    8,    8,    8, 0x0a,
      31,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Texting[] = {
    "Texting\0\0text_show()\0sendMsg()\0"
    "testing_time_show()\0"
};

const QMetaObject Texting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Texting,
      qt_meta_data_Texting, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Texting::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Texting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Texting::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Texting))
        return static_cast<void*>(const_cast< Texting*>(this));
    return QWidget::qt_metacast(_clname);
}

int Texting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: text_show(); break;
        case 1: sendMsg(); break;
        case 2: testing_time_show(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
