#include "../Instances.h"

namespace cement
{
    template <>
    int Instances<long>::Type() const
    {
        return 2;
    }

    template <>
    int Instances<bool>::Type() const
    {
        return 3;
    }

    template <>
    int Instances<double>::Type() const
    {
        return 4;
    }

    template <>
    int Instances<std::string>::Type() const
    {
        return 5;
    }

    template <>
    int Instances<unsigned long>::Type() const
    {
        return 6;
    }

} // end namespace cement