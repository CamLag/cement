#pragma once

#include <tuple>
#include <vector>

namespace cement
{
    class BlockBase
    {
    public:
        virtual void Eval() = 0;

    };

    template<typename T>
    struct FunctionTraits
    {

    };

    template<typename R, typename ... Args>
    struct FunctionTraits<R(*)(Args...)>
    {
        using ArgsTuple = std::tuple<Args...>;

        static constexpr size_t ArgCount = sizeof...(Args);

        template<size_t N>
        using Arg = std::tuple_element<N, ArgsTuple>;
    };

    template<typename Func>
    class Block
    {
    public:

        using R = typename FunctionTraits<Func>::R;

        template<size_t N>
        using Arg = typename FunctionTraits<Func>::template Arg<N>;

        //R Evaluate(std::make_integer_sequence(N) Args ...)
    };

} //end namespace cement
