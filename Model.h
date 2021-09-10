#pragma once

#include "Property.h"
#include "Instances.h"
#include "Common.h"
#include <unordered_map>
#include <vector>

namespace cement
{
    class Model : public Property
    {
    public:
        Model(const std::string &a_name);

        void AddProperty(Property *a_property);

        template <typename T>
        void SetValue(Property *a_property, size_t a_instance, const T &a_value)
        {
            dynamic_cast<Instances<T> *>(a_property)->SetValue(m_indexes[a_property][a_instance], a_value);
        }

        virtual size_t Instanciate() override;
        virtual size_t Size() override;
        virtual std::string Print() override;

        std::unordered_map<Property *, std::vector<size_t>> m_indexes;
        size_t m_size;
    };
} //end namespace cement