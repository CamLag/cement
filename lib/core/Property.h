#pragma once

#include "Value.h"
#include "Pool.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

namespace cement
{
    class Index;

    class Property
    {
    public:
        Property(const std::string &a_name, bool a_shared);

        std::string m_name;

        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        void DeleteInstance(size_t a_instance);
        virtual const size_t Size() const = 0;
        virtual const size_t Depth() const;
        virtual const size_t PropertyCount() const;
        virtual const int Type() const = 0;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        bool IsShared() const;

        std::set<Index *> m_index_references;

    protected:
        virtual void SelfDeleteInstance(size_t a_instance) = 0;

    private:
        bool m_shared;
    };
} // end namespace cement