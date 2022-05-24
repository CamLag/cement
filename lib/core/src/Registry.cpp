#include "../Registry.h"

namespace cement
{
    Property *Registry::CreateProperty(PropertyType a_type, const std::string &a_name, bool a_shared)
    {
        switch (a_type) {
        case pt_model:
        {
            return CreateModel(a_name, a_shared);
        }
        case pt_long:
        {
            return CreateProperty<long>(a_name, a_shared);
        }
        case pt_bool:
        {
            return CreateProperty<bool>(a_name, a_shared);
        }
        case pt_double:
        {
            return CreateProperty<double>(a_name, a_shared);
        }
        case pt_string:
        {
            return CreateProperty<std::string>(a_name, a_shared);
        }
        case pt_u_long:
        {
            return CreateProperty<unsigned long>(a_name, a_shared);
        }
        default:
        {
            return nullptr;
        }
    }
    }

    Index* Registry::AddProperty(Model* a_model, Property *a_property, const std::string &a_name)
    {
        auto index = new Index(a_name, a_property, a_model);
        m_properties[a_name] = index;
        a_model->AddIndex(index);
        a_property->AddIndexReference(index);
        m_property_created.Emit(index);
        return index;
    }

    Property *Registry::GetProperty(size_t a_row)
    {
        auto it = m_properties.begin();
        std::advance(it, a_row);
        return it->second;
    }

    Property *Registry::GetProperty(const std::string &a_name)
    {
        auto it = m_properties.find(a_name);

        if (it == m_properties.end())
        {
            return nullptr;
        }

        return it->second;
    }

    Model *Registry::CreateModel(const std::string &a_name, bool a_shared)
    {
        auto model = new Model(a_name, a_shared);
        m_properties[a_name] = model;
        return model;
    }

    std::string Registry::Print()
    {
        std::string result;
        for (auto &pair : m_properties)
        {
            if (pair.second->Type() != 7) // Indexes are printed within the model
            {
                result += pair.second->Print();
            }
        }
        return result;
    }

    std::vector<std::vector<Property *>> Registry::Visit()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &pair : m_properties)
        {
            for (auto &child : pair.second->VisitProperties())
            {
                result.push_back(child);
            }
        }

        return result;
    }
} // end namespace cement
