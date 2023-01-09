#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include <iostream>
#include <tuple>

void Plus(const long& i1, const long& i2, long& i3)
{
    i3 = i1 + i2;
}

namespace cement
{
    class Helper
    {
    public:
        template<typename T>
        static T& GetValue(const Value& value)
        {
            auto prop = dynamic_cast<Instances<T>*>(value.m_property);
            return prop->Get(value.m_index);
        }

//        template<typename T>
//        static void SetValue(const Value& value, const T& val)
//        {
//            auto prop = dynamic_cast<Instances<T>*>(value.m_property);
//            return prop->SetValue(value.m_index, val);
//        }
    };

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

    class Node
    {
    public:

        Value m_value;
    };

    class Block
    {
    public:
        virtual void Compute() = 0;
        virtual Node& GetNode(size_t index) = 0;
        virtual Node& InputNode(size_t index) = 0;
        virtual Node& OutputNode(size_t index) = 0;

    protected:
        size_t InputSize{};
        size_t OutputSize{};
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

        virtual Node& InputNode(size_t index) override
        {
            return m_inputs[index];
        }

        virtual Node& OutputNode(size_t index) override
        {
            return m_outputs[index];
        }

        std::array<Node, Size> m_nodes;
        std::array<Node, InputSize> m_inputs;
        std::array<Node, OutputSize> m_outputs;

    };
}

int main()
{
    using namespace cement;
    Registry reg;
    auto prop = reg.CreateProperty<long>("a", false);
    auto v1 = prop->Instanciate();
    auto v2 = prop->Instanciate();
    auto v3 = prop->Instanciate();
    prop->Set(v1, "12");
    prop->Set(v2, "2");

    auto bl = FunctionBlock<decltype(&Plus), &Plus>();
    bl.GetNode(0).m_value = Value{prop, v1};
    bl.GetNode(1).m_value = Value{prop, v2};
    bl.GetNode(2).m_value = Value{prop, v3};
    bl.Compute();

    std::cout << prop->Get(v3) << std::endl;
}
