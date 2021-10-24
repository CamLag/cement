#pragma once

#include <stddef.h>

namespace cement
{
    class Property;

    struct Value
    {
        Property *m_property{nullptr};
        size_t m_index{};
    };
} //end namespace cement