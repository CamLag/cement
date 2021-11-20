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
        Property(const std::string &a_name);

        std::string m_name;

        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        virtual void DeleteInstance(size_t a_instance) = 0;
        virtual const size_t Size() const = 0;
        virtual const size_t Depth() const;
        virtual const size_t PropertyCount() const;
        virtual const int Type() const = 0;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        void AddReference(size_t a_instance, Property *a_property, size_t a_model_instance);
        void RemoveReference(size_t a_instance, Property *a_property, size_t a_model_instance);
        bool HasReference(size_t a_instance);

        Pool<std::map<Property *, std::set<size_t>>> m_references;

        std::set<Index *> m_index_references;
    };
} // end namespace cement