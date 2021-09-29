#pragma once

#include "Property.h"
#include "Instances.h"
#include "Common.h"
#include <unordered_map>
#include <vector>
#include <iostream>

namespace cement
{
    class Model : public Property
    {
    public:
        Model(const std::string &a_name);

        void AddProperty(Property *a_property); //TODO Manage addition of property to an already instanciated model (instanciation of the property?)

        template <typename T>
        void SetValue(Property *a_property, size_t a_instance, const T &a_value)
        {
            std::cout << "Model SetValue " << a_property->m_name << " instance " << a_instance << " value " << StringConversions::ToString(a_value) << std::endl;
            dynamic_cast<Instances<T> *>(a_property)->SetValue(m_indexes[a_property].at(a_instance), a_value); //TODO manage recursive models // TODO remove at after better error management
        }

        virtual size_t Instanciate() override;
        virtual const size_t Size() const override;
        virtual std::string Print() const override;
        virtual const int Type() const override;
        virtual const size_t Depth() const override;
        virtual const size_t PropertyCount() const override;

        std::unordered_map<Property *, std::vector<size_t>> m_indexes;
        size_t m_size;
    };
} //end namespace cement