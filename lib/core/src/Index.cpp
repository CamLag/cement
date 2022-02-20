#include "../Index.h"

namespace cement
{
    Index::Index(const std::string &a_name, Property *a_indexed) : Instances<unsigned long>(a_name, false), m_indexed(a_indexed)
    {
    }

    void Index::SetValue(size_t a_pos, const unsigned long &a_val)
    {
        Instances<unsigned long>::SetValue(a_pos, a_val);
    }

    PropertyType Index::Type() const
    {
        return pt_index;
    }

    Property *Index::GetIndexed() const
    {
        return m_indexed;
    }

} // end namespace cement
