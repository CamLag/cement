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

        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        void DeleteInstance(size_t a_instance);
        virtual const size_t Size() const = 0;
        virtual const size_t Depth() const;
        virtual const size_t PropertyCount() const;
        virtual int Type() const = 0;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        bool IsShared() const;
        const std::string &GetName() const;
        const std::set<Index *> &GetIndexReferences() const;
        void AddIndexReference(Index *a_index);
        virtual void GetValue(size_t a_instance, std::string &a_string_value);
        virtual const std::set<Index *> &GetIndexes() const;

    protected:
        virtual void SelfDeleteInstance(size_t a_instance) = 0;

    private:
        std::set<Index *> m_index_references;
        std::string m_name;
        bool m_shared;
    };
} // end namespace cement