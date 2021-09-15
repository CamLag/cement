#pragma once

#include <QWidget>

#include "lib/core/StringConversions.h"
#include "lib/core/Instances.h"
#include "lib/core/Model.h"
#include "lib/gui/VectorWidget.h"

namespace cement
{
    class Factory
    {
    public:
        Factory() = delete;

        static QWidget *MakeWidget(Property *a_property)
        {
            switch (a_property->Type())
            {
            case 1: // Model
            {
                return new QWidget();
            }
            case 2: // long
            {
                auto widget = new VectorWidget();

                widget->Init<long>(dynamic_cast<Instances<long> *>(a_property)->GetValues());

                return widget;
            }
            case 3: // bool
            {
                auto widget = new VectorWidget();

                widget->Init<bool>(dynamic_cast<Instances<bool> *>(a_property)->GetValues());

                return widget;
            }
            case 4: // double
            {
                auto widget = new VectorWidget();

                widget->Init<double>(dynamic_cast<Instances<double> *>(a_property)->GetValues());

                return widget;
            }
            case 5: // string
            {
                auto widget = new VectorWidget();

                widget->Init<std::string>(dynamic_cast<Instances<std::string> *>(a_property)->GetValues());

                return widget;
            }
            default:
            {
                return nullptr;
            }
            }
        }
    };
} //end namespace cement
