#include "../Property.h"

namespace cement
{
    Property::Property(const std::string &a_name) : m_name(a_name)
    {
    }

    std::string Property::Print()
    {
        return m_name;
    }

} //end namespace cement