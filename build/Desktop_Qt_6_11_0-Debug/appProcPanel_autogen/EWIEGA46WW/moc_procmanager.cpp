/****************************************************************************
** Meta object code from reading C++ file 'procmanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../procmanager.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'procmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
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
struct qt_meta_tag_ZN11ProcManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ProcManager::qt_create_metaobjectdata<qt_meta_tag_ZN11ProcManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ProcManager",
        "procModelChanged",
        "",
        "cpuUsageChanged",
        "memUsageChanged",
        "stopProc",
        "pid",
        "resumeProc",
        "terminateProc",
        "sort",
        "column",
        "Qt::SortOrder",
        "order",
        "procModel",
        "ProcessModel*",
        "cpuUsage",
        "memUsage"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'procModelChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'cpuUsageChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'memUsageChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'stopProc'
        QtMocHelpers::MethodData<void(int)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'resumeProc'
        QtMocHelpers::MethodData<void(int)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'terminateProc'
        QtMocHelpers::MethodData<void(int)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 6 },
        }}),
        // Method 'sort'
        QtMocHelpers::MethodData<void(int, Qt::SortOrder)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { 0x80000000 | 11, 12 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'procModel'
        QtMocHelpers::PropertyData<ProcessModel*>(13, 0x80000000 | 14, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag | QMC::StdCppSet | QMC::Final, 0),
        // property 'cpuUsage'
        QtMocHelpers::PropertyData<double>(15, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 1),
        // property 'memUsage'
        QtMocHelpers::PropertyData<double>(16, QMetaType::Double, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet | QMC::Final, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ProcManager, qt_meta_tag_ZN11ProcManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ProcManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ProcManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ProcManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN11ProcManagerE_t>.metaTypes,
    nullptr
} };

void ProcManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ProcManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->procModelChanged(); break;
        case 1: _t->cpuUsageChanged(); break;
        case 2: _t->memUsageChanged(); break;
        case 3: _t->stopProc((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->resumeProc((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->terminateProc((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->sort((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<Qt::SortOrder>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ProcManager::*)()>(_a, &ProcManager::procModelChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcManager::*)()>(_a, &ProcManager::cpuUsageChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ProcManager::*)()>(_a, &ProcManager::memUsageChanged, 2))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ProcessModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<ProcessModel**>(_v) = _t->procModel(); break;
        case 1: *reinterpret_cast<double*>(_v) = _t->cpuUsage(); break;
        case 2: *reinterpret_cast<double*>(_v) = _t->memUsage(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setProcModel(*reinterpret_cast<ProcessModel**>(_v)); break;
        case 1: _t->setCpuUsage(*reinterpret_cast<double*>(_v)); break;
        case 2: _t->setMemUsage(*reinterpret_cast<double*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *ProcManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN11ProcManagerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ProcManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ProcManager::procModelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ProcManager::cpuUsageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ProcManager::memUsageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
