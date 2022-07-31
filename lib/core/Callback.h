#pragma once

#include <functional>
#include <list>
#include <iostream>
#include <memory>

namespace cement
{
    template <typename ... Args>
    class Callback
    {
    public:

        using Slot = std::function<void(Args ...)>;

        class Connection
        {
            using Iterator = typename std::list<Slot>::iterator;
            friend class Callback;

            Connection(Iterator a_it): m_it(a_it) {}

        private:
            Iterator m_it;
        };

        void Emit(Args ... args)
        {
//            std::cout << "Emitting " << m_slots.size() << std::endl;
            for (auto slot : m_slots)
            {
                slot(args ...);
            }
        }

        Connection Connect(Slot a_slot)
        {
            m_slots.push_back(a_slot);
            return { m_slots.end() };
        }

        void Disconnect(Connection a_connection)
        {
            m_slots.erase(a_connection.m_it);
        }

    private:
        std::list<Slot> m_slots;
    };
} //end namespace cement
