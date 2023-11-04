/****************************************************************************
** Meta object code from reading C++ file 'pcie_memory_rw.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../pcie_memory_rw/pcie_memory_rw.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pcie_memory_rw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
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
struct qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS = QtMocHelpers::stringData(
    "pcie_memory_rw",
    "wavFileDropped",
    "",
    "filePath",
    "startProcessing",
    "on_btnSnd_clicked",
    "on_wavProcessButton_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS_t {
    uint offsetsAndSizes[14];
    char stringdata0[15];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[16];
    char stringdata5[18];
    char stringdata6[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS_t qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "pcie_memory_rw"
        QT_MOC_LITERAL(15, 14),  // "wavFileDropped"
        QT_MOC_LITERAL(30, 0),  // ""
        QT_MOC_LITERAL(31, 8),  // "filePath"
        QT_MOC_LITERAL(40, 15),  // "startProcessing"
        QT_MOC_LITERAL(56, 17),  // "on_btnSnd_clicked"
        QT_MOC_LITERAL(74, 27)   // "on_wavProcessButton_clicked"
    },
    "pcie_memory_rw",
    "wavFileDropped",
    "",
    "filePath",
    "startProcessing",
    "on_btnSnd_clicked",
    "on_wavProcessButton_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSpcie_memory_rwENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    0,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   42,    2, 0x08,    4 /* Private */,
       6,    0,   43,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject pcie_memory_rw::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSpcie_memory_rwENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<pcie_memory_rw, std::true_type>,
        // method 'wavFileDropped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'startProcessing'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnSnd_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_wavProcessButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void pcie_memory_rw::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<pcie_memory_rw *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->wavFileDropped((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->startProcessing(); break;
        case 2: _t->on_btnSnd_clicked(); break;
        case 3: _t->on_wavProcessButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (pcie_memory_rw::*)(const QString & );
            if (_t _q_method = &pcie_memory_rw::wavFileDropped; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (pcie_memory_rw::*)();
            if (_t _q_method = &pcie_memory_rw::startProcessing; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *pcie_memory_rw::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *pcie_memory_rw::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSpcie_memory_rwENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int pcie_memory_rw::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void pcie_memory_rw::wavFileDropped(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void pcie_memory_rw::startProcessing()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
