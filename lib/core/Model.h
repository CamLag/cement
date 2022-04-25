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
        Model(const std::string &a_name, bool a_shared);

        virtual size_t Instanciate() override;
        virtual size_t Size() const override;
        virtual std::string Print() const override;
        virtual PropertyType Type() const override;
        virtual size_t Depth() const override;
        virtual size_t PropertyCount() const override;
        virtual std::vector<std::vector<Property *>> VisitProperties() override;
        void AddIndex(Index *a_index);
        virtual const std::set<Index *> &GetIndexes() const override;

        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value) override;

    protected:
        virtual void InternalDeleteInstance(size_t a_instance) override;

    private:
        std::set<Index *> m_indexes;
        size_t m_size;
    };
} // end namespace cement
