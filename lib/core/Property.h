#pragma once

#include "Value.h"
#include "Pool.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

namespace cement
{
    class Property
    {
    public:
        Property(const std::string &a_name);

        std::string m_name;

        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        virtual void DeleteInstance(size_t a_index) = 0;
        virtual const size_t Size() const = 0;
        virtual const size_t Depth() const;
        virtual const size_t PropertyCount() const;
        virtual const int Type() const = 0;
        virtual const std::unordered_map<Property *, Pool<size_t>> &Children() const;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        void AddReference(size_t a_instance, size_t *a_pointer);
        void RemoveReference(size_t a_instance, size_t *a_pointer);
        bool HasReference(size_t a_instance);

        Pool<std::set<size_t *>> m_references;
    };
} //end namespace cement