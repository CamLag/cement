#pragma once

#include <stack>
#include <stdint.h>

namespace cement
{
    typedef uint64_t Id;

    class IncrementalId
    {
    public:
        Id NextId();

    private:
        void SetFree(Id a_id);
        std::stack<Id> m_available_ids;
        Id m_next_id{0};
    };
} // end namespace cement
