#include "../Instances.h"

namespace cement
{
    template <>
    const int Instances<long>::Type() const
    {
        return 2;
    }

    template <>
    const int Instances<bool>::Type() const
    {
        return 3;
    }

    template <>
    const int Instances<double>::Type() const
    {
        return 4;
    }

    template <>
    const int Instances<std::string>::Type() const
    {
        return 5;
    }

    template <>
    const int Instances<unsigned long>::Type() const
    {
        return 6;
    }

} // end namespace cement