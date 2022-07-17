#include "../Properties.h"

namespace cement
{
    Properties::Properties(size_t a_id) : Property(a_id, "Properties", true)
    {
    }

    Properties::~Properties()
    {
        for (auto pair : m_properties)
        {
            if (pair.second != this)
            {
                delete pair.second;
            }
        }
    }

    size_t Properties::AddProperty(Property *a_property)
    {
        m_properties[a_property->m_id] = a_property;
        return a_property->m_id;
    }

    Property *Properties::GetProperty(size_t a_id) const
    {
        auto it = m_properties.find(a_id);
        if (it == m_properties.end())
        {
            return nullptr;
        }

        return it->second;
    }

    const std::unordered_map<size_t, Property *> &Properties::GetProperties()
    {
        return m_properties;
    }

    size_t Properties::Instanciate()
    {
        return 0;
    }

    void Properties::Get(size_t a_id, std::string &a_string_value)
    {
        auto prop = GetProperty(a_id);
        a_string_value = prop->Print();
    }

    void Properties::GetPointedValue(size_t a_instance, std::string &a_string_value)
    {
        Get(a_instance, a_string_value);
    }

    void Properties::InternalDeleteInstance(size_t a_id)
    {
        auto it = m_properties.find(a_id);
        if (it == m_properties.end())
        {
            return;
        }
        m_properties.erase(it);
    }

    size_t Properties::Size() const
    {
        return m_properties.size();
    }

    std::string Properties::Print() const
    {
        std::string result;
        result += Property::Print();
        result += " [";

        for (auto elem : m_properties)
        {
            if (elem.second != this)
            {
                result += elem.second->Print();
            }
            else
            {
                result += elem.second->Property::Print();
            }
            result += ", ";
        }

        result.pop_back();
        result.pop_back();
        result += "]\n";

        return result;
    }

    PropertyType cement::Properties::Type() const
    {
        return pt_property;
    }

} // end namespace cement
