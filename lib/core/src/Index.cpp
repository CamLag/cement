#include "../Index.h"

namespace cement
{
    Index::Index(const std::string &a_name, Property *a_indexed) : Instances<unsigned long>(a_name, false), m_indexed(a_indexed)
    {
    }

    void Index::SetValue(size_t a_pos, const unsigned long &a_val)
    {
        auto &index_pointer = m_values[a_pos];
        if (a_val == NO_VALUE)
        {
            m_indexed->RemoveReference(a_val, this, index_pointer);
            Instances<unsigned long>::SetValue(a_pos, a_val);
        }
        else if (index_pointer == NO_VALUE) // the property is shared and this instance has never been set
        {
            Instances<unsigned long>::SetValue(a_pos, a_val);
            m_indexed->AddReference(a_val, this, index_pointer);
        }
        else if (index_pointer != a_val) // the instance points elsewhere
        {
            m_indexed->RemoveReference(a_val, this, index_pointer);
            Instances<unsigned long>::SetValue(a_pos, a_val);
            m_indexed->AddReference(a_val, this, index_pointer);
        }
    }

    Property *Index::GetIndexed() const
    {
        return m_indexed;
    }

} // end namespace cement
