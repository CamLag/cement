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
        pt_index
    };

    class Property
    {
    public:
        Property(const std::string &a_name, bool a_shared);

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
        virtual void GetValue(size_t a_instance, std::string &a_string_value);
        virtual const std::set<Index *> &GetIndexes() const;

        // concrete
        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value);

        Callback<size_t> m_value_modified;

    protected:
        virtual void SelfDeleteInstance(size_t a_instance) = 0;

    private:
        std::set<Index *> m_index_references;
        std::string m_name;
        bool m_shared;
    };
} // end namespace cement
