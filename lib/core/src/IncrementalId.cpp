#include "../IncrementalId.h"

#include <algorithm>

namespace cement
{
    void IncrementalId::SetFree(Id a_id)
    {
        m_available_ids.push_back(a_id);
    }

    bool IncrementalId::IsAvailable(Id a_id) const
    {
        if (a_id >= m_next_id)
        {
            return true;
        }
        else
        {
            return std::find(m_available_ids.begin(), m_available_ids.end(), a_id) != m_available_ids.end();
        }
    }

    Id IncrementalId::NextId()
    {
        if (m_available_ids.empty())
        {
            ++m_next_id;
            return m_next_id - 1;
        }
        else
        {
            auto id = m_available_ids.back();
            m_available_ids.pop_back();
            return id;
        }
    }

} // end namespace cement
