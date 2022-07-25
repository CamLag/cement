#include "../IncrementalId.h"

namespace cement
{
    void IncrementalId::SetFree(size_t a_id)
    {
        m_available_ids.push(a_id);
    }

    size_t IncrementalId::NextId()
    {
        if (m_available_ids.empty())
        {
            ++m_next_id;
            return m_next_id - 1;
        }
        else
        {
            auto id = m_available_ids.top();
            m_available_ids.pop();
            return id;
        }
    }

} // end namespace cement
