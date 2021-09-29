#pragma once

#include "lib/core/Property.h"
#include "lib/gui/VectorWidget.h"

namespace cement
{
    class PropertyWidget : public VectorWidget
    {
        Q_OBJECT

    public:
        PropertyWidget(Property *a_property, QWidget *a_parent = nullptr);
    };
} //end namespace cement
