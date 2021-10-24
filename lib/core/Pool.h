#pragma once

#include <vector>
#include <assert.h>

namespace cement
{
    template <typename T>
    class Pool
    {
    public:
        typedef std::vector<T> Sink;

        // class Iterator
        // {
        //     friend class Pool<T>;
        //     Iterator(Pool<T> *a_pool)
        //     {
        //     }
        //     std::vector<T>::iterator m_it;
        // };

        Pool(size_t a_size) : m_sink_size(a_size)
        {
        }

        void AddSink()
        {
            m_sinks.emplace_back();
            m_sinks.back().reserve(m_sink_size);
        }

        void Delete(const size_t a_position)
        {
            if (Size() != 1 && a_position < Size() - 1)
            {
                std::swap(operator[](a_position), Back());
            }
            PopBack();
        }

        void PushBack(const T &a_value)
        {
            if (Size() == 0 or m_sinks.back().size() == m_sink_size)
            {
                AddSink();
            }
            m_sinks.back().push_back(a_value);
        }

        void PopBack()
        {
            m_sinks.back().pop_back();
            if (m_sinks.back().size() == 0)
            {
                m_sinks.pop_back();
            }
        }

        void Clear()
        {
            m_sinks.clear();
        }

        T &operator[](const size_t a_position)
        {
            return m_sinks[a_position / m_sink_size][a_position % m_sink_size];
        }

        const T &operator[](const size_t a_position) const
        {
            return m_sinks[a_position / m_sink_size][a_position % m_sink_size];
        }

        T &At(const size_t a_position)
        {
            if (a_position >= Size())
            {
                assert(false && "position is greater than capacity");
            }

            return operator[](a_position);
        }

        T &Back()
        {
            return m_sinks.back().back();
        }

        const T &Back() const
        {
            return m_sinks.back().back();
        }

        size_t Size() const
        {
            if (m_sinks.size() == 0)
            {
                return 0;
            }

            return ((m_sinks.size() - 1) * m_sink_size) + m_sinks.back().size();
        }

        std::vector<Sink> m_sinks;
        const size_t m_sink_size;
    };

} // end namespace cement
