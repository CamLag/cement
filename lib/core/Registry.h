#pragma once

#include "Model.h"
#include "Instances.h"
#include "Properties.h"
#include "Callback.h"
#include "IncrementalId.h"

#include <stack>
#include <unordered_map>

namespace cement
{
    class Registry
    {
    public:
        Registry();
        ~Registry();

        template <typename T>
        Instances<T> *CreateProperty(const std::string &a_name, bool a_shared)
        {
            auto property = new Instances<T>(m_inc_id.NextId(), a_name, a_shared);
            m_properties->AddProperty(property);
            m_property_created.Emit(property);
            return property;
        }

        Property* CreateProperty(PropertyType a_type, const std::string &a_name, bool a_shared);
        Property* GetProperty(size_t a_row);
        Property* GetProperty(const std::string &a_name);

        Index *AddProperty(Model *a_model, Property *a_property, const std::string &a_name);
        // TODO Manage addition of property to an already instanciated model (instanciation of the property?)
        Model *CreateModel(const std::string &a_name, bool a_shared);

        std::string Print();
        std::vector<std::vector<Property *>> Visit();

        Callback<Property*> m_property_created;
        Callback<Property*> m_property_deleted;

        Properties* m_properties;

    private:
        IncrementalId m_inc_id;
    };

} // end namespace cement
