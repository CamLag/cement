#pragma once

#include <vector>
#include <stdint.h>
#include <unordered_set>

namespace cement
{
    typedef uint64_t Id;

    class IncrementalId
    {
    public:
        Id NextId();
        void SetFree(Id a_id);
        bool IsAvailable(Id a_id) const;

    private:
        std::unordered_set<Id> m_available_ids;
        Id m_next_id{0};
    };
} // end namespace cement
