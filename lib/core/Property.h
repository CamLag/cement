#pragma once

#include "Value.h"
#include "Pool.h"
#include "Callback.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>

namespace cement
{
    class Index;

    enum PropertyType
    {
        pt_model,
        pt_long,
        pt_bool,
        pt_double,
        pt_string,
        pt_u_long,
        pt_index,
        pt_property
    };

    class Property
    {
    public:
        Property(size_t a_id, const std::string &a_name, bool a_shared);

        // core
        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        void DeleteInstance(size_t a_instance);
        virtual size_t Size() const = 0;
        virtual size_t Depth() const;
        virtual size_t PropertyCount() const;
        virtual PropertyType Type() const = 0;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        bool IsShared() const;
        const std::string &GetName() const;
        const std::set<Index *> &GetIndexReferences() const;
        void AddIndexReference(Index *a_index);
        virtual void Get(size_t a_instance, std::string &a_string_value);
        virtual void Set(size_t a_instance, const std::string &a_string_value);
        virtual const std::set<Index *> &GetIndexes() const;

        // concrete
        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value);

        Callback<size_t> m_instance_added;
        Callback<size_t> m_instance_changed;
        Callback<size_t> m_instance_deleted;
        Callback<size_t, size_t> m_instances_swapped;

        const size_t m_id;

    protected:
        virtual void InternalDeleteInstance(size_t a_instance) = 0;

    private:
        std::set<Index *> m_index_references;
        std::string m_name;
        bool m_shared;
    };
} // end namespace cement
