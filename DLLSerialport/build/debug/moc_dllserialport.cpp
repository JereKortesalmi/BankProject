/****************************************************************************
** Meta object code from reading C++ file 'dllserialport.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dllserialport.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dllserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSDLLSerialportENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSDLLSerialportENDCLASS = QtMocHelpers::stringData(
    "DLLSerialport",
    "sendCardNumber",
    "",
    "signalNameSet",
    "signalVendorSet",
    "getVendorID",
    "getName",
    "getVendor",
    "setName",
    "setVendor",
    "openSerialPort",
    "closeSerialPort",
    "readData"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSDLLSerialportENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[14];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[16];
    char stringdata5[12];
    char stringdata6[8];
    char stringdata7[10];
    char stringdata8[8];
    char stringdata9[10];
    char stringdata10[15];
    char stringdata11[16];
    char stringdata12[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSDLLSerialportENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSDLLSerialportENDCLASS_t qt_meta_stringdata_CLASSDLLSerialportENDCLASS = {
    {
        QT_MOC_LITERAL(0, 13),  // "DLLSerialport"
        QT_MOC_LITERAL(14, 14),  // "sendCardNumber"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 13),  // "signalNameSet"
        QT_MOC_LITERAL(44, 15),  // "signalVendorSet"
        QT_MOC_LITERAL(60, 11),  // "getVendorID"
        QT_MOC_LITERAL(72, 7),  // "getName"
        QT_MOC_LITERAL(80, 9),  // "getVendor"
        QT_MOC_LITERAL(90, 7),  // "setName"
        QT_MOC_LITERAL(98, 9),  // "setVendor"
        QT_MOC_LITERAL(108, 14),  // "openSerialPort"
        QT_MOC_LITERAL(123, 15),  // "closeSerialPort"
        QT_MOC_LITERAL(139, 8)   // "readData"
    },
    "DLLSerialport",
    "sendCardNumber",
    "",
    "signalNameSet",
    "signalVendorSet",
    "getVendorID",
    "getName",
    "getVendor",
    "setName",
    "setVendor",
    "openSerialPort",
    "closeSerialPort",
    "readData"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSDLLSerialportENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   80,    2, 0x06,    1 /* Public */,
       3,    0,   81,    2, 0x06,    2 /* Public */,
       4,    0,   82,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   83,    2, 0x0a,    4 /* Public */,
       6,    0,   84,    2, 0x0a,    5 /* Public */,
       7,    0,   85,    2, 0x0a,    6 /* Public */,
       8,    1,   86,    2, 0x0a,    7 /* Public */,
       9,    1,   89,    2, 0x0a,    9 /* Public */,
      10,    0,   92,    2, 0x08,   11 /* Private */,
      11,    0,   93,    2, 0x08,   12 /* Private */,
      12,    0,   94,    2, 0x08,   13 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::UShort,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::UShort,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject DLLSerialport::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSDLLSerialportENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSDLLSerialportENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSDLLSerialportENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<DLLSerialport, std::true_type>,
        // method 'sendCardNumber'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signalNameSet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signalVendorSet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getVendorID'
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'getName'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'getVendor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setName'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setVendor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<quint16, std::false_type>,
        // method 'openSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeSerialPort'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void DLLSerialport::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DLLSerialport *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sendCardNumber(); break;
        case 1: _t->signalNameSet(); break;
        case 2: _t->signalVendorSet(); break;
        case 3: { quint16 _r = _t->getVendorID();
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = std::move(_r); }  break;
        case 4: { QString _r = _t->getName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->getVendor(); break;
        case 6: _t->setName((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->setVendor((*reinterpret_cast< std::add_pointer_t<quint16>>(_a[1]))); break;
        case 8: _t->openSerialPort(); break;
        case 9: _t->closeSerialPort(); break;
        case 10: _t->readData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DLLSerialport::*)();
            if (_t _q_method = &DLLSerialport::sendCardNumber; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DLLSerialport::*)();
            if (_t _q_method = &DLLSerialport::signalNameSet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DLLSerialport::*)();
            if (_t _q_method = &DLLSerialport::signalVendorSet; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *DLLSerialport::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DLLSerialport::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSDLLSerialportENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DLLSerialport::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DLLSerialport::sendCardNumber()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DLLSerialport::signalNameSet()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DLLSerialport::signalVendorSet()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
