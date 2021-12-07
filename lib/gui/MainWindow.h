#pragma once

#include <QMainWindow>
#include <QTabBar>

#include "lib/core/Registry.h"
#include "lib/gui/RegistryWidget.h"
#include "lib/gui/ConcreteWidget.h"

namespace cement
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT;

    public:
        MainWindow(QWidget *a_parent = nullptr);
        Registry m_registry;
        RegistryWidget *m_registry_widget;
        ConcreteWidget *m_concrete_widget;
    };
} // end namespace cement
