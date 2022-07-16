#pragma once

#include "Property.h"
#include <unordered_map>

namespace cement
{
    class Properties : public Property
    {
    public:
        Properties(size_t a_id) : Property(a_id, "Properties", true)
        {
        }

        size_t AddProperty(Property* a_property)
        {
            m_properties[a_property->m_id] = a_property;
        }

        Property* GetProperty(size_t a_id) const
        {
            auto it = m_properties.find(a_id);
            if (it == m_properties.end())
            {
                return nullptr;
            }

            return it->second;
        }

        virtual void Get(size_t a_id, std::string &a_string_value) override
        {
            auto prop = GetProperty(a_id);
            a_string_value = prop->Print();
        }

        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value) override
        {
            Get(a_instance, a_string_value);
        }

        virtual void InternalDeleteInstance(size_t a_id) override
        {
            auto it = m_properties.find(a_id);
            if (it == m_properties.end())
            {
                return;
            }
            m_properties.erase(it);
        }

        virtual size_t Size() const override
        {
            return m_properties.size();
        }

        virtual std::string Print() const override
        {
            std::string result;
            result += Property::Print();
            result += " [";

            for (auto elem : m_properties)
            {
                result += elem.second->Print();
                result += ", ";
            }

            result.pop_back();
            result.pop_back();
            result += "]\n";

            return result;
        }

        virtual PropertyType Type() const override;

    protected:
        std::unordered_map<size_t, Property*> m_properties;
    };
} // end namespace cement
