#pragma once

#include "Property.h"
#include <unordered_map>

namespace cement
{
    class Properties : public Property
    {
    public:
        Properties(size_t a_id);

        size_t AddProperty(Property* a_property);

        Property* GetProperty(size_t a_id) const;

        virtual void Get(size_t a_id, std::string &a_string_value) override;

        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value) override;

        virtual void InternalDeleteInstance(size_t a_id) override;

        virtual size_t Size() const override;

        virtual std::string Print() const override;

        virtual PropertyType Type() const override;

    protected:
        std::unordered_map<size_t, Property*> m_properties;
    };
} // end namespace cement
