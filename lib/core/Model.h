#pragma once

#include "Index.h"
#include "Common.h"
#include <unordered_map>
#include <vector>
#include <iostream>

namespace cement
{
    class Model : public Property
    {
    public:
        Model(size_t a_id, const std::string &a_name, bool a_shared);

        virtual Id Instanciate() override;
        virtual size_t Size() const override;
        virtual std::string Print() const override;
        virtual PropertyType Type() const override;
        virtual size_t Depth() const override;
        virtual size_t PropertyCount() const override;
        virtual std::vector<std::vector<Property *>> VisitProperties() override;
        void AddIndex(Index *a_index);
        virtual const std::set<Index *> &GetIndexes() const override;

        virtual void GetPointedValue(Id a_instance, std::string &a_string_value) override;

    protected:
        virtual void InternalDeleteInstance(Id a_instance) override;

    private:
        Sparse m_sparse;
        std::set<Index *> m_indexes;
        size_t m_size;
    };
} // end namespace cement
