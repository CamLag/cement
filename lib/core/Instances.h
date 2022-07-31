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
        Instances(Id a_id,const std::string &a_name, bool a_shared) : Property(a_id, a_name, a_shared), m_values(1000)
        {
        }

        size_t AddValue(const T &a_val = T{})
        {
            m_values.PushBack(a_val);
            size_t pos = m_values.Size() - 1;
            m_instance_added.Emit(pos);
            return pos;
        }

        void SetValue(Id a_pos, const T &a_val = T{})
        {
            std::cout << "Instances SetValue position " << a_pos << " value " << StringConversions::ToString(a_val) << " size : " << m_values.Size() << std::endl;
            if (a_val != m_values[a_pos])
            {
                m_values[a_pos] = a_val;
                m_instance_changed.Emit(a_pos);
            }
        }

        const T& Get(Id a_pos) const
        {
            return m_values[a_pos];
        }

        // TODO delete, breaks signals
        T& Get(Id a_pos)
        {
            return m_values[a_pos];
        }

        virtual void Get(Id a_instance, std::string &a_string_value) override
        {
            StringConversions::ToString<T>(m_values[a_instance], a_string_value);
        }

        virtual void Set(Id a_instance, const std::string &a_string_value) override
        {
            T val;
            StringConversions::FromString<T>(val, a_string_value);
            SetValue(a_instance, val);
        }

        virtual void GetPointedValue(Id a_instance, std::string &a_string_value) override
        {
            Get(a_instance, a_string_value);
        }

        int CountValues(const T &a_value) const
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

        virtual Id Instanciate() override
        {
            return AddValue();
        }

        virtual void InternalDeleteInstance(Id a_instance) override
        {
            auto size = Size();
            if (m_values.SwapWithLast(a_instance))
            {
                m_instances_swapped.Emit(a_instance, size);
            }
        }

        virtual size_t Size() const override
        {
            return m_values.Size();
        }

        virtual std::string Print() const override
        {
            std::string result;
            result += Property::Print();

            if (m_values.Size() == 0)
            {
                result += "\n";
                return result;
            }

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

        virtual PropertyType Type() const override
        {
            return Property::GetPropType<T>();
        }

        const Pool<T> &GetValues() const
        {
            return m_values;
        }

    protected:
        Pool<T> m_values;
    };
} // end namespace cement
