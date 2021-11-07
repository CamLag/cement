#include "../Property.h"

namespace cement
{
    Property::Property(const std::string &a_name) : m_name(a_name), m_references(1000)
    {
    }

    std::string Property::Print() const
    {
        return m_name;
    }

    const size_t Property::Depth() const
    {
        return 1;
    }

    const size_t Property::PropertyCount() const
    {
        return 1;
    }

    void Property::SetIndex(Property *a_property, size_t a_model_instance, size_t a_property_instance)
    {
    }

    const std::unordered_map<Property *, Pool<size_t>> &Property::Children() const
    {
        static const std::unordered_map<Property *, Pool<size_t>> blank_map;
        return blank_map;
    }

    std::vector<std::vector<Property *>> Property::VisitProperties()
    {
        return {{this}};
    }

    void Property::AddReference(size_t a_instance, Property *a_property, size_t a_model_instance)
    {
        m_references[a_instance][a_property].insert(a_model_instance);
    }

    void Property::RemoveReference(size_t a_instance, Property *a_property, size_t a_model_instance)
    {
        auto map_it = m_references[a_instance].find(a_property);

        if (map_it == m_references[a_instance].end())
        {
            return;
        }

        map_it->second.erase(a_model_instance);

        if (map_it->second.empty())
        {
            m_references[a_instance].erase(a_property);
        }
    }

    bool Property::HasReference(size_t a_instance)
    {
        return m_references[a_instance].size() != 0;
    }

} // end namespace cement