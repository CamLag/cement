#pragma once

#include "Pool.h"
#include "Callback.h"
#include "IncrementalId.h"
#include "Sparse.h"

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
        pt_property,
        pt_none
    };

    class Property
    {
    public:
        friend class Registry;

        Property(size_t a_id, const std::string &a_name, bool a_shared);
        virtual ~Property();

        // core
        virtual std::string Print() const;
        virtual Id Instanciate() = 0;
        bool HasId(Id a_id) const;
        void DeleteInstance(Id a_instance);
        virtual size_t Size() const = 0;
        virtual size_t Depth() const;
        virtual size_t PropertyCount() const;

        template<typename T>
        static PropertyType GetPropType()
        {
            return pt_none;
        }

        virtual PropertyType Type() const = 0;
        virtual std::vector<std::vector<Property *>> VisitProperties();
        bool IsShared() const;
        std::string& GetName();
        const std::set<Index *> &GetIndexReferences() const;
        virtual void Get(Id a_instance, std::string &a_string_value);
        std::string Get(Id a_instance);
        virtual void Set(Id a_instance, const std::string &a_string_value);

        virtual const std::set<Index *> &GetIndexes() const;
        const Sparse& GetIds() const;

        // concrete
        virtual void GetPointedValue(Id a_instance, std::string &a_string_value);
        virtual std::string PrettyPrint(Id a_instance, int a_depth = 0);

        bool IsLeaf();

        Callback<size_t> m_instance_added;
        Callback<size_t> m_instance_changed;
        Callback<size_t> m_instance_deleted;
        Callback<size_t, size_t> m_instances_swapped;

        const size_t m_id;

    protected:
        virtual void InternalDeleteInstance(Id a_instance) = 0;
        void AddIndexReference(Index *a_index);
        Sparse m_sparse;

    private:
        std::set<Index *> m_index_references;
        std::string m_name;
        bool m_shared;
    };
} // end namespace cement
