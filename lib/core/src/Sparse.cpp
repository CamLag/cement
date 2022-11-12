#include "../Sparse.h"
#include <algorithm>
#include "Common.h"

namespace cement
{
    Sparse::Sparse()
    {

    }

    Sparse::Elem Sparse::operator[](Id a_id) const
    {
        return m_sparse[a_id];
    }

    Id Sparse::AddElem(Sparse::Elem a_index)
    {
        auto id = m_inc_ids.NextId();

        assert(id <= m_sparse.Size() && "id can't be greater than the sparse size");

        if (m_sparse.Size() == id) // new ids
        {
            m_sparse.PushBack(a_index);
        }
        else // reused ids
        {
            m_sparse[id] = a_index;
        }

        return id;
    }

    Sparse::Elem Sparse::GetElem(Id a_id) const
    {
        return m_sparse[a_id];
    }

    void Sparse::SetElem(Id a_id, Sparse::Elem a_elem)
    {
        m_sparse[a_id] = a_elem;
    }

    void Sparse::RemoveElem(Id a_id)
    {
        m_inc_ids.SetFree(a_id);
    }

    Id Sparse::Find(Sparse::Elem a_elem) const
    {
        for (size_t i = m_sparse.Size() - 1; i != NO_VALUE; --i)
        {
            if (m_sparse[i] == a_elem && !m_inc_ids.IsAvailable(i))
            {
                return i;
            }
        }
        return NO_VALUE;
    }

    bool Sparse::HasId(Id a_id) const
    {
        return !m_inc_ids.IsAvailable(a_id);
    }
} // end namespace cement
