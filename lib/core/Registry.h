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
        Instances<T> *CreateProperty(const std::string &a_name, bool a_shared)
        {
            auto property = new Instances<T>(a_name, a_shared);
            m_properties[a_name] = property;
            return property;
        }

        Index *AddProperty(Model *a_model, Property *a_property, const std::string &a_name);
        // TODO Manage addition of property to an already instanciated model (instanciation of the property?)

        Model *CreateModel(const std::string &a_name, bool a_shared);
        std::string Print();
        std::vector<std::vector<Property *>> Visit();

        std::unordered_map<std::string, Property *> m_properties;
    };

} // end namespace cement
