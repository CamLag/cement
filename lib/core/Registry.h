#pragma once

#include "Model.h"
#include "Instances.h"

#include <unordered_map>

namespace cement
{
    class Registry
    {
    public:
        template <typename T>
        Instances<T> *CreateProperty(const std::string &a_name)
        {
            auto property = new Instances<T>(a_name);
            m_properties[a_name] = property;
            return property;
        }

        Model *CreateModel(const std::string &a_name);
        std::string Print();
        std::vector<std::vector<Property *>> Visit();

        std::unordered_map<std::string, Property *> m_properties;
    };

} //end namespace cement
