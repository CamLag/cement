#pragma once

#include <QMainWindow>
#include "lib/gui/VectorWidget.h"
#include "lib/core/Registry.h"

namespace cement
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT;

    public:
        MainWindow(QWidget *a_parent = nullptr);
        Registry m_registry;
    };
} //end namespace cement
