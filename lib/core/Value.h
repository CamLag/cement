#pragma once

#include <stddef.h>
#include "Instances.h"

namespace cement
{
    struct Value
    {
        Property* m_property{nullptr};
        size_t m_index{};
    };

    class Helper
    {
    public:
        template<typename T>
        static T& GetValue(const Value& value)
        {
            auto prop = dynamic_cast<Instances<T>*>(value.m_property);
            return prop->Get(value.m_index);
        }
    };
} //end namespace cement
