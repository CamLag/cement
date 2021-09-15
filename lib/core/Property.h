#pragma once

#include <string>

namespace cement
{
    class Property
    {
    public:
        Property(const std::string &a_name);

        std::string m_name;

        virtual std::string Print();
        virtual size_t Instanciate() = 0;
        virtual size_t Size() = 0;

        virtual int Type() = 0;
    };
} //end namespace cement