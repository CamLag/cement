#include "../Property.h"

namespace cement
{
    Property::Property(const std::string &a_name, bool a_shared) : m_name(a_name),
                                                                   m_shared(a_shared)
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

    std::vector<std::vector<Property *>> Property::VisitProperties()
    {
        return {{this}};
    }

    bool Property::IsShared() const
    {
        return m_shared;
    }

} // end namespace cement