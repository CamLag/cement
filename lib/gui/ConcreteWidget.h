#pragma once

#include <QWidget>
#include "lib/core/Registry.h"

namespace cement
{
    class ConcreteWidget : public QWidget
    {
        Q_OBJECT

    public:
        ConcreteWidget(Registry *a_registry, QWidget *a_parent = nullptr);

    protected:
        Registry *m_registry;
    };
} // end namespace cement
