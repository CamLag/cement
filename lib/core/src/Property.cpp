#include "../Property.h"

namespace cement
{
    Property::Property(const std::string &a_name) : m_name(a_name)
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

} //end namespace cement