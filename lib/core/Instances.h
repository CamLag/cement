#pragma once

#include "Property.h"
#include "Common.h"
#include "StringConversions.h"
#include "Sparse.h"
#include <vector>
#include <iostream>
#include <plog/Log.h>

namespace cement
{
    template <typename T>
    class Instances : public Property
    {
    public:
        Instances(Id a_id, const std::string &a_name, bool a_shared) : Property(a_id, a_name, a_shared), m_values(1000)
        {
        }

        Id AddValue(const T &a_val = T{})
        {
            m_values.PushBack(a_val);
            size_t pos = m_values.Size() - 1;
            auto id = m_sparse.AddElem(pos);
            m_instance_added.Emit(id);
            PLOGD << "Value=" << a_val << " " << Print();
            return id;
        }

        void SetValue(Id a_instance, const T &a_val = T{})
        {
            std::cout << "Instances SetValue id " << a_instance << " value " << StringConversions::ToString(a_val) << " size : " << m_values.Size() << std::endl;

            auto pos = m_sparse[a_instance];
            PLOGD << "Instance=" << a_instance << " Value="<< a_val << " " << Print();

            if (a_val != m_values[pos])
            {
                m_values[pos] = a_val;
                m_instance_changed.Emit(a_instance);
            }
        }

        const T& Get(Id a_pos) const
        {
            return m_values[m_sparse[a_pos]];
        }

        // TODO delete, breaks signals
        T& Get(Id a_pos)
        {
            return m_values[m_sparse[a_pos]];
        }

        virtual void Get(Id a_instance, std::string &a_string_value) override
        {
            StringConversions::ToString<T>(m_values[m_sparse[a_instance]], a_string_value);
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
            PLOGD << "a_old_value=" << a_old_value << " a_new_value="<< a_new_value << " " << Print();

            int count = 0;
            for (size_t i = 0; i < m_values.Size(); i++)
            {
                if (m_values[i] == a_old_value)
                {
                    m_values[i] = a_new_value;
                    count++;
                }
            }

            PLOGD << Print();

            return count;
        }

        virtual Id Instanciate() override
        {
            return AddValue();
        }

        virtual void InternalDeleteInstance(Id a_instance) override
        {
            PLOGD << "a_instance=" << a_instance << Print();
            auto size = Size();
            auto pos = m_sparse[a_instance];
            m_values.SwapWithLast(pos);
            m_values.PopBack();
            m_sparse.RemoveElem(a_instance);
            auto last_id = m_sparse.Find(size - 1);
            m_sparse.SetElem(last_id, pos);
            m_instance_deleted.Emit(a_instance);
            PLOGD << Print();
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
        Sparse m_sparse;
        Pool<T> m_values;
    };
} // end namespace cement
