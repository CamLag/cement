#pragma once

#include "IncrementalId.h"
#include "Pool.h"

namespace cement
{
    class Sparse
    {
    public:
        Sparse();

        typedef Id Elem; // id is used as an index to find element in spare

        Id AddElem(Elem a_index);
        Elem GetElem(Id a_id);
        void SetElem(Id a_id, Elem a_elem);
        void RemoveElem(Id a_id);

    private:
        Pool<Elem> m_sparse{100};
        IncrementalId m_inc_ids;
    };

} // end namespace cement
