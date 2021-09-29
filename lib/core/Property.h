#pragma once

#include <string>

namespace cement
{
    class Property
    {
    public:
        Property(const std::string &a_name);

        std::string m_name;

        virtual std::string Print() const;
        virtual size_t Instanciate() = 0;
        virtual const size_t Size() const = 0;
        virtual const size_t Depth() const;
        virtual const size_t PropertyCount() const;
        virtual const int Type() const = 0;
    };
} //end namespace cement