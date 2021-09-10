#pragma once

#include "Property.h"
#include "StringConversions.h"
#include <vector>

namespace cement
{
    template <typename T>
    class Instances : public Property
    {
    public:
        Instances(const std::string &a_name) : Property(a_name)
        {
        }

        size_t AddValue(const T &a_val = T{})
        {
            m_values.push_back(a_val);

            return m_values.size() - 1;
        }

        void SetValue(size_t a_pos, const T &a_val = T{})
        {
            m_values[a_pos] = a_val;
        }

        virtual size_t Instanciate() override
        {
            return AddValue();
        }

        virtual size_t Size() override
        {
            return m_values.size();
        }

        virtual std::string Print() override
        {
            std::string result;
            result += Property::Print();
            result += " [";

            for (auto it = m_values.begin(); it != m_values.end() - 1; it++)
            {
                result += StringConversions::ToString(*it);
                result += ", ";
            }

            result += StringConversions::ToString(m_values.back());
            result += "]\n";

            return result;
        }

        std::vector<T> m_values;
    };
} //end namespace cement
