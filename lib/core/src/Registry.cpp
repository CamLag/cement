#include "../Registry.h"

namespace cement
{
    Registry::Registry()
    {
        m_properties = new Properties(GetCurrentId());
        m_properties->AddProperty(m_properties);
    }

    Registry::~Registry()
    {
        delete m_properties;
    }

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
        auto index = new Index(GetCurrentId(), a_name, a_property, a_model);
        m_properties->AddProperty(index);
        a_model->AddIndex(index);
        a_property->AddIndexReference(index);
        m_property_created.Emit(index);
        return index;
    }

    Property* Registry::GetProperty(size_t a_id)
    {
        return m_properties->GetProperty(a_id);
    }

    Property* Registry::GetProperty(const std::string &/*a_name*/)
    {
        return nullptr;
    }

    Model *Registry::CreateModel(const std::string &a_name, bool a_shared)
    {
        auto model = new Model(GetCurrentId(), a_name, a_shared);
        m_properties->AddProperty(model);
        return model;
    }

    std::string Registry::Print()
    {
        return m_properties->Print();
    }

    std::vector<std::vector<Property *>> Registry::Visit()
    {
        std::vector<std::vector<Property *>> result;

        for (auto &pair : m_properties->GetProperties())
        {
            for (auto &child : pair.second->VisitProperties())
            {
                result.push_back(child);
            }
        }

        return result;
    }

    size_t Registry::GetCurrentId()
    {
        if (m_available_ids.empty())
        {
            ++m_last_id;
            return m_last_id - 1;
        }
        else
        {
            auto id = m_available_ids.top();
            m_available_ids.pop();
            return id;
        }
    }

    void Registry::SetFree(size_t a_id)
    {
        m_available_ids.push(a_id);
    }
} // end namespace cement
