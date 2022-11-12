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

        Elem operator[](Id a_id) const;
        Id AddElem(Elem a_index);
        Elem GetElem(Id a_id) const;
        void SetElem(Id a_id, Elem a_elem);
        void RemoveElem(Id a_id);
        Id Find(Elem a_elem) const;
        bool HasId(Id a_id) const;

    private:
        Pool<Elem> m_sparse{100};
        IncrementalId m_inc_ids;
    };

} // end namespace cement
