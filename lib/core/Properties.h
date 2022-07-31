#pragma once

#include "Property.h"
#include <unordered_map>

namespace cement
{
    class Properties : public Property
    {
    public:
        Properties(Id a_id);
        virtual ~Properties();
        Id AddProperty(Property* a_property);
        Property* GetProperty(Id a_id) const;
        const std::map<Id, Property*>& GetProperties();
        virtual Id Instanciate() override;
        virtual void Get(Id a_id, std::string &a_string_value) override;
        virtual void GetPointedValue(Id a_instance, std::string &a_string_value) override;
        virtual void InternalDeleteInstance(Id a_id) override;
        virtual size_t Size() const override;
        virtual std::string Print() const override;
        virtual PropertyType Type() const override;

    protected:
        std::map<Id, Property*> m_properties;
    };
} // end namespace cement
