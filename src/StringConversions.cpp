#include "../StringConversions.h"

namespace cement
{

    template <>
    void StringConversions::FromString(std::string &a_value, const std::string &a_string)
    {
        a_value = a_string;
    }

    template <>
    void StringConversions::FromString(long &a_value, const std::string &a_string)
    {
        a_value = std::stol(a_string);
    }

    template <>
    void StringConversions::FromString(unsigned long &a_value, const std::string &a_string)
    {
        a_value = std::stoul(a_string);
    }

    template <>
    void StringConversions::FromString(bool &a_value, const std::string &a_string)
    {
        a_value = a_string[0] == '0' ? false : true;
    }

    template <>
    void StringConversions::FromString(double &a_value, const std::string &a_string)
    {
        a_value = std::stod(a_string);
    }

    template <>
    void StringConversions::ToString(const std::string &a_value, std::string &a_string)
    {
        a_string = a_value;
    }

    template <>
    void StringConversions::ToString(const long &a_value, std::string &a_string)
    {
        a_string = std::to_string(a_value);
    }

    template <>
    void StringConversions::ToString(const unsigned long &a_value, std::string &a_string)
    {
        a_string = std::to_string(a_value);
    }

    template <>
    void StringConversions::ToString(const bool &a_value, std::string &a_string)
    {
        a_string = std::to_string(a_value);
    }

    template <>
    void StringConversions::ToString(const double &a_value, std::string &a_string)
    {
        a_string = std::to_string(a_value);
    }

} //end namespace cement
