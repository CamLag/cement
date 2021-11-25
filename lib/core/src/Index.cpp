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

    unsigned long Index::GetValue(size_t a_pos)
    {
        return m_values[a_pos];
    }

    Property *Index::GetIndexed() const
    {
        return m_indexed;
    }

    int Index::Count(size_t a_property_instance)
    {
        // TODO improve with std::count after iterator addition in pool
        int count = 0;
        for (size_t i = 0; i < m_values.Size(); i++)
        {
            if (m_values[i] == a_property_instance)
            {
                count++;
            }
        }

        return count;
    }

    int Index::Replace(size_t a_new_property_instance, size_t a_old_property_instance)
    {
        // TODO improve with std::count after iterator addition in pool
        int count = 0;
        for (size_t i = 0; i < m_values.Size(); i++)
        {
            if (m_values[i] == a_old_property_instance)
            {
                m_values[i] = a_new_property_instance;
                count++;
            }
        }

        return count;
    }

} // end namespace cement
