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

    const std::unordered_map<Property *, std::vector<size_t>> &Property::Children() const
    {
        static const std::unordered_map<Property *, std::vector<size_t>> blank_map;
        return blank_map;
    }

    std::vector<std::vector<Property *>> Property::VisitProperties()
    {
        return {{this}};
    }

} //end namespace cement