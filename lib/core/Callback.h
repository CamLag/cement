#pragma once

#include <functional>
#include <list>
#include <iostream>

namespace cement
{
    template <typename ... Args>
    class Callback
    {
    public:

        using Slot = std::function<void(Args ...)>;

        class Connection
        {
        private:
            typename std::list<Slot>::iterator it;
        };

        void Emit(Args ... args)
        {
            std::cout <<"Emitting " << m_slots.size() << std::endl;;
            for (auto slot : m_slots)
            {
                slot(args ...);
            }
        }

        /*Connection*/void Connect(Slot a_slot)
        {
            m_slots.push_back(a_slot);
//            return Connection(m_slots.end());
        }

        void Disconnect(Connection a_connection)
        {
            m_slots.erase(a_connection.it);
        }

    private:
        std::list<Slot> m_slots;
    };
} //end namespace cement
