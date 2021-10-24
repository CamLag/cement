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

    const std::unordered_map<Property *, Pool<size_t>> &Property::Children() const
    {
        static const std::unordered_map<Property *, Pool<size_t>> blank_map;
        return blank_map;
    }

    std::vector<std::vector<Property *>> Property::VisitProperties()
    {
        return {{this}};
    }

    void Property::AddReference(size_t a_instance, size_t *a_pointer)
    {
        m_references[a_instance].insert(a_pointer);
    }

    void Property::RemoveReference(size_t a_instance, size_t *a_pointer)
    {
        m_references[a_instance].erase(a_pointer);
    }

    bool Property::HasReference(size_t a_instance)
    {
        return m_references[a_instance].size() != 0;
    }

} //end namespace cement