#pragma once

#include "Node.h"
#include <tuple>
#include <vector>


namespace cement
{
    template<typename T>
    using IfConst = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>, std::tuple<T>, std::tuple<>>;

    template<typename T>
    using IfNotConst = std::conditional_t<std::is_const_v<std::remove_reference_t<T>>, std::tuple<>, std::tuple<T>>;

    template<typename ... T>
    using FilterConst = decltype(std::tuple_cat(std::declval<IfConst<T>>()...));

    template<typename ... T>
    using FilterNotConst = decltype(std::tuple_cat(std::declval<IfNotConst<T>>()...));

    template<typename  T> struct FuncTraits{};

    template<typename R, typename... Args>
    struct FuncTraits<R(*)(Args...)>
    {
        using Return = R;
        using Arguments = std::tuple<Args ...>;
        using Inputs = FilterConst<Args...>;
        using Outputs = FilterNotConst<Args...>;
        static constexpr auto Size = std::tuple_size_v<Arguments>;
        static constexpr auto InputSize = std::tuple_size_v<Inputs>;
        static constexpr auto OutputSize = std::tuple_size_v<Outputs>;
    };

    class Block
    {
    public:
        virtual void Compute() = 0;
        virtual Node& GetNode(size_t index) = 0;
    };

    template<typename F, F f>
    class FunctionBlock : public Block
    {
    public:
        using ReturnType = typename FuncTraits<F>::Return;
        using InputTypes = typename FuncTraits<F>::Inputs;
        using OutputTypes = typename FuncTraits<F>::Outputs;
        using Arguments = typename FuncTraits<F>::Arguments;
        static constexpr auto Size = FuncTraits<F>::Size;
        static constexpr auto InputSize = FuncTraits<F>::InputSize;
        static constexpr auto OutputSize = FuncTraits<F>::OutputSize;

        FunctionBlock()
        {
        }

        virtual void Compute() override
        {
            CallFunction<Arguments>(m_nodes);
        }

        template<typename Tuple, size_t N, size_t I>
        static auto GetNodeValue(const std::array<Node, N>& a_array) -> std::tuple_element_t<I, Tuple>
        {
            using Type = std::decay_t<std::tuple_element_t<I, Tuple>>;
            return Helper::GetValue<Type>(a_array[I].m_value);
        }

        template<typename Tuple, size_t N, size_t... I>
        static Tuple GetNodeValues(const std::array<Node, N>& a_array, std::index_sequence<I...>)
        {
            return {GetNodeValue<Tuple, N, I>(a_array)...};
        }

        template<typename Tuple, size_t N, typename = std::enable_if_t<(N == std::tuple_size_v<Tuple>)>>
        static Tuple GetNodeValues(const std::array<Node, N>& a_array)
        {
            return GetNodeValues<Tuple, N>(a_array, std::make_index_sequence<N>{});
        }

        template<typename Tuple, size_t N, size_t... I>
        static void CallFunction(const std::array<Node, N>& a_array, std::index_sequence<I...>)
        {
            std::invoke(f, GetNodeValue<Tuple, N, I>(a_array)...);
        }

        template<typename Tuple, size_t N, typename = std::enable_if_t<(N == std::tuple_size_v<Tuple>)>>
        static void CallFunction(const std::array<Node, N>& a_array)
        {
            CallFunction<Tuple, N>(a_array, std::make_index_sequence<N>{});
        }

        virtual Node& GetNode(size_t index) override
        {
            return m_nodes[index];
        }

        std::array<Node, Size> m_nodes;
    };
}
