#pragma once

#include "Property.h"
#include "Common.h"
#include "StringConversions.h"
#include <vector>
#include <iostream>

namespace cement
{
    template <typename T>
    class Instances : public Property
    {
    public:
        Instances(const std::string &a_name, bool a_shared) : Property(a_name, a_shared), m_values(1000)
        {
        }

        size_t AddValue(const T &a_val = T{})
        {
            m_values.PushBack(a_val);
            size_t size = m_values.Size() - 1;
            return size;
        }

        virtual void SetValue(size_t a_pos, const T &a_val = T{})
        {
            std::cout << "Instances SetValue position " << a_pos << " value " << StringConversions::ToString(a_val) << " size : " << m_values.Size() << std::endl;
            m_values[a_pos] = a_val;
        }

        const T &GetValue(size_t a_pos) const
        {
            return m_values[a_pos];
        }

        T &GetValue(size_t a_pos)
        {
            return m_values[a_pos];
        }

        virtual void GetValue(size_t a_instance, std::string &a_string_value) override
        {
            StringConversions::ToString<T>(m_values[a_instance], a_string_value);
        }

        virtual void GetPointedValue(size_t a_instance, std::string &a_string_value) override
        {
            GetValue(a_instance, a_string_value);
        }

        int CountValues(const T &a_value)
        {
            // TODO improve with std::count after iterator addition in pool
            int count = 0;
            for (size_t i = 0; i < m_values.Size(); i++)
            {
                if (m_values[i] == a_value)
                {
                    count++;
                }
            }

            return count;
        }

        int ReplaceValues(const T &a_old_value, const T &a_new_value)
        {
            // TODO improve with std::count after iterator addition in pool
            int count = 0;
            for (size_t i = 0; i < m_values.Size(); i++)
            {
                if (m_values[i] == a_old_value)
                {
                    m_values[i] = a_new_value;
                    count++;
                }
            }

            return count;
        }

        virtual size_t Instanciate() override
        {
            return AddValue();
        }

        virtual void SelfDeleteInstance(size_t a_instance) override
        {
            m_values.Delete(a_instance);
        }

        virtual size_t Size() const override
        {
            return m_values.Size();
        }

        virtual std::string Print() const override
        {
            std::string result;
            result += Property::Print();
            result += " [";

            for (size_t i = 0; i != m_values.Size() - 1; i++)
            {
                result += StringConversions::ToString(m_values[i]);
                result += ", ";
            }

            result += StringConversions::ToString(m_values.Back());
            result += "]\n";

            return result;
        }

        virtual PropertyType Type() const override;

        const Pool<T> &GetValues() const
        {
            return m_values;
        }

    protected:
        Pool<T> m_values;
    };
} // end namespace cement
