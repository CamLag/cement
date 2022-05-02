#pragma once

#include "Model.h"
#include "Instances.h"
#include "Callback.h"

#include <unordered_map>

namespace cement
{
    class Registry
    {
    public:
        template <typename T>
        Instances<T> *CreateProperty(const std::string &a_name, bool a_shared)
        {
            if (m_properties.find(a_name) != m_properties.end())
            {
                return nullptr;
            }

            auto property = new Instances<T>(a_name, a_shared);
            m_properties[a_name] = property;
            m_property_created.Emit(property);
            return property;
        }

        Index *AddProperty(Model *a_model, Property *a_property, const std::string &a_name);
        // TODO Manage addition of property to an already instanciated model (instanciation of the property?)

        Property* GetProperty(size_t a_row);

        Model *CreateModel(const std::string &a_name, bool a_shared);
        std::string Print();
        std::vector<std::vector<Property *>> Visit();

        Callback<Property*> m_property_created;
        Callback<Property*> m_property_deleted;

        std::unordered_map<std::string, Property *> m_properties;
    };

} // end namespace cement
