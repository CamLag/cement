#include "../StringConversions.h"

#include <unordered_map>

#include "Property.h"

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
    void StringConversions::FromString(PropertyType &a_value, const std::string &a_string)
    {
        static const std::unordered_map<std::string, PropertyType> values{
            {"model",    pt_model} ,
            {"long",     pt_long}  ,
            {"bool",     pt_bool}  ,
            {"double",   pt_double},
            {"string",   pt_string},
            {"u_long",   pt_u_long},
            {"index",    pt_index} ,
            {"property", pt_property}
        };

        auto it = values.find(a_string);
        a_value = it == values.end() ? pt_none : it->second;
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

    template <>
    void StringConversions::ToString(const PropertyType &a_value, std::string &a_string)
    {
        switch (a_value) {
        case pt_model   :
        {
            a_string = "model";
            break;
        }
        case pt_long    :
        {
            a_string = "long";
            break;
        }
        case pt_bool    :
        {
            a_string = "bool";
            break;
        }
        case pt_double  :
        {
            a_string = "double";
            break;
        }
        case pt_string  :
        {
            a_string = "string";
            break;
        }
        case pt_u_long  :
        {
            a_string = "long";
            break;
        }
        case pt_index   :
        {
            a_string = "index";
            break;
        }
        case pt_property:
        {
            a_string = "property";
            break;
        }
        default         :
        {
            a_string = "none";
            break;
        }
        }
    }

} //end namespace cement
