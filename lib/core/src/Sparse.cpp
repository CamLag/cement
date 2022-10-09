#include "../Sparse.h"

namespace cement
{
    Id Sparse::AddElem(Sparse::Elem a_index)
    {
        auto id = m_inc_ids.NextId();

        assert(id <= m_sparse.Size() && "id can't be greater than the sparse size");

        if (m_sparse.Size() == id - 1) // new ids
        {
            m_sparse.PushBack(a_index);
        }
        else // reused ids
        {
            m_sparse[id] = a_index;
        }

        return id;
    }

    Sparse::Elem Sparse::GetElem(Id a_id)
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
} // end namespace cement
