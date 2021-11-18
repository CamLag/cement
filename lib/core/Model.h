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
        Model(const std::string &a_name);

        virtual size_t Instanciate() override;
        virtual void DeleteInstance(size_t a_instance) override;
        virtual const size_t Size() const override;
        virtual std::string Print() const override;
        virtual const int Type() const override;
        virtual const size_t Depth() const override;
        virtual const size_t PropertyCount() const override;
        virtual std::vector<std::vector<Property *>> VisitProperties() override;

        std::set<Index *> GetIndexes() const;

    private:
        std::set<Index *> m_indexes;
        size_t m_size;
    };
} // end namespace cement