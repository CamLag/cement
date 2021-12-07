#pragma once

#include <QScrollArea>
#include "lib/core/Registry.h"

namespace cement
{
    class ConcreteWidget : public QScrollArea
    {
        Q_OBJECT

    public:
        ConcreteWidget(Registry *a_registry, QWidget *a_parent = nullptr);

    protected:
        Registry *m_registry;
    };
} // end namespace cement
