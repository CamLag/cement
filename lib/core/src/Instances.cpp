#include "../Instances.h"

namespace cement
{
    template <>
    int Instances<long>::Type()
    {
        return 2;
    }

    template <>
    int Instances<bool>::Type()
    {
        return 3;
    }

    template <>
    int Instances<double>::Type()
    {
        return 4;
    }

    template <>
    int Instances<std::string>::Type()
    {
        return 5;
    }

} //end namespace cement