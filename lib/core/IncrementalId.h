#pragma once

#include <stack>

namespace cement
{
    class IncrementalId
    {
    public:
        size_t NextId();

    private:
        void SetFree(size_t a_id);
        std::stack<size_t> m_available_ids;
        size_t m_next_id{0};
    };
} // end namespace cement
