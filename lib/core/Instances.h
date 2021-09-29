#pragma once

#include "Property.h"
#include "StringConversions.h"
#include <vector>
#include <iostream>

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
            std::cout << "Instances SetValue position " << a_pos << " value " << StringConversions::ToString(a_val) << " size : " << m_values.size() << std::endl;
            m_values[a_pos] = a_val;
        }

        virtual size_t Instanciate() override
        {
            return AddValue();
        }

        virtual const size_t Size() const override
        {
            return m_values.size();
        }

        virtual std::string Print() const override
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

        virtual const int Type() const override;

        const std::vector<T> &GetValues() const
        {
            return m_values;
        }

    private:
        std::vector<T> m_values;
    };
} //end namespace cement
