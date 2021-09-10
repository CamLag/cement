#pragma once

#include <string>

namespace cement
{
    class StringConversions
    {
    public:
        StringConversions() = delete;

        template <typename T>
        static void FromString(T &a_value, const std::string &a_string);

        template <typename T>
        static void ToString(const T &a_value, std::string &a_string);

        template <typename T>
        static T FromString(const std::string &a_string)
        {
            T a_value;
            FromString(a_value, a_string);
            return a_value;
        }

        template <typename T>
        static std::string ToString(const T &a_value)
        {
            std::string a_string;
            ToString(a_value, a_string);
            return a_string;
        }
    };

} //end namespace cement
