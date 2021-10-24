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
        Instances(const std::string &a_name) : Property(a_name), m_values(1000)
        {
        }

        size_t AddValue(const T &a_val = T{})
        {
            m_values.PushBack(a_val);
            size_t size = m_values.Size() - 1;
            return size;
        }

        void SetValue(size_t a_pos, const T &a_val = T{})
        {
            std::cout << "Instances SetValue position " << a_pos << " value " << StringConversions::ToString(a_val) << " size : " << m_values.Size() << std::endl;
            m_values[a_pos] = a_val;
        }

        virtual size_t Instanciate() override
        {
            return AddValue();
        }

        virtual void DeleteInstance(size_t a_index) override
        {
            auto last_index = m_values.Size() - 1;
            m_values.Delete(a_index);
            for (auto &reference : m_references[a_index])
            {
                *reference = last_index;
            }
        }

        virtual const size_t Size() const override
        {
            return m_values.Size();
        }

        virtual std::string Print() const override
        {
            std::string result;
            result += Property::Print();
            result += " [";

            // for (auto it = m_values.begin(); it != m_values.end() - 1; it++)
            // {
            //     result += StringConversions::ToString(*it);
            //     result += ", ";
            // }

            result += StringConversions::ToString(m_values.Back());
            result += "]\n";

            return result;
        }

        virtual const int Type() const override;

        const Pool<T> &GetValues() const
        {
            return m_values;
        }

    private:
        Pool<T> m_values;
    };
} // end namespace cement
