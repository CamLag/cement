#include "../Sparse.h"

namespace cement
{
    Id Sparse::AddElem(Sparse::Elem a_index)
    {
        m_sparse.PushBack(a_index);
        return static_cast<Id>(m_sparse.Size() - 1);
    }

    Sparse::Elem Sparse::GetElem(Id a_id)
    {
        return m_sparse[a_id];
    }

    void Sparse::SetElem(Id a_id, Sparse::Elem a_elem)
    {
        m_sparse[a_id] = a_elem;
    }
} // end namespace cement
