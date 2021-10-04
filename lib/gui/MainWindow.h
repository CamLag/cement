#pragma once

#include <QMainWindow>

#include "lib/core/Registry.h"
#include "lib/gui/RegistryWidget.h"

namespace cement
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT;

    public:
        MainWindow(QWidget *a_parent = nullptr);
        Registry m_registry;
        RegistryWidget *m_registry_widget;
    };
} //end namespace cement
