#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include <iostream>
#include <tuple>

void Plus(const long& i1, const long& i2, long& i3)
{
    i3 = i1 + i2;
}

int Sum(double) {return 32;}

namespace cement
{
    class Helper
    {
    public:
        template<typename T>
        static const T& GetValue(const Value& value)
        {
            auto prop = dynamic_cast<Instances<T>*>(value.m_property);
            return prop->Get(value.m_index);
        }

        template<typename T>
        static void SetValue(const Value& value, const T& val)
        {
            auto prop = dynamic_cast<Instances<T>*>(value.m_property);
            return prop->SetValue(value.m_index, val);
        }
    };

    class Node
    {
    public:

        Value m_value;
    };

    class Block
    {
    public:
        virtual size_t InputSize() = 0;
        virtual size_t OutputSize() = 0;
        virtual void Compute() = 0;

    protected:
        std::vector<Node> m_inputs;
        std::vector<Node> m_outputs;
    };

    // ********************************* first try
    template<typename Elem, typename Tuple, size_t I, size_t N>
    struct TupleConcatHelper
    {
        using Result = std::tuple<Elem, typename std::tuple_element<I, Tuple>::type>;
    };

    template<typename Elem, typename Tuple, size_t N>
    struct TupleConcatHelper<Elem, Tuple, 0, N>
    {
        using Result = std::tuple<Elem, typename std::tuple_element<0, Tuple>::type>;
    };

    template<typename Elem, typename Tuple, size_t N>
    struct TupleConcatHelper<Elem, Tuple, N, N>
    {
        using Result = typename TupleConcatHelper<Elem, Tuple, N - 1, N>::Result;
    };

    template<typename Elem, typename Tuple>
    struct TupleConcat
    {
        //using Result = typename TupleConcatHelper<Elem, Tuple, sizeof (Tuple) + 1>::Result;
    };

    // second try
    template<class Elem, class Tuple, size_t...Is>
    auto TupleConcat2(std::index_sequence<Is...>)
        -> std::tuple<std::tuple_element_t<Is, Tuple>..., Elem>;

    template<class Elem, class Tuple>
    using ConcatTuple2 = decltype (TupleConcat2<Elem, Tuple>(std::index_sequence<std::tuple_size_v<Tuple> - 1>()));

    //  ****************************************************************************  Draft

    template<size_t... Seq1, size_t... Seq2, size_t... Seq3>
    auto concat3_impl(std::index_sequence<Seq1...>,
                      std::index_sequence<Seq2...>,
                      std::index_sequence<Seq3...>)
      -> std::index_sequence<Seq1..., Seq2..., Seq3...>;

    template<class...Ts>
    using concat3 = decltype(concat3_impl(Ts{}...));

    template<size_t start, size_t max, bool = (start < max) >
    struct in_order;

    template<size_t start, size_t max>
    using in_order_t = typename in_order<start, max>::type;

    template<size_t start, size_t max, bool >
    struct in_order {
        using type = concat3<in_order_t<2*start + 1, max>,
                             std::index_sequence<start>,
                             in_order_t<2*start + 2, max>>;
    };

    template<size_t start, size_t max >
    struct in_order<start, max, false> {
        using type = std::index_sequence<>;
    };

    template<class Tuple, size_t...Is>
    auto reorder_by_index_impl(std::index_sequence<Is...>)
        -> std::tuple<std::tuple_element_t<Is, Tuple>...>;

    template<class Tuple, class Index>
    using reorder_by_index = decltype(reorder_by_index_impl<Tuple>(Index{}));

    template<class Tuple>
    using reorder_tuple = reorder_by_index<Tuple, in_order_t<0, std::tuple_size<Tuple>{}>>;
    //  ****************************************************************************  Draft

    template<typename ... Args>
    struct TupleFusion
    {
    };

    template<typename Input, typename Output, typename Elem>
    struct TupleFusion<
            Input,
            Output,
            Elem,
            std::enable_if_t<std::is_const_v<Elem>>>
    {
        using NewInput = decltype (std::tuple_cat<Input, std::tuple<Elem>>);
        using NewOutput = Output;
    };

    template<typename Input, typename Output, typename Elem>
    struct TupleFusion<
            Input,
            Output,
            Elem,
            std::enable_if_t<!std::is_const_v<Elem>>>
    {
        using NewInput = Input;
        using NewOutput = typename TupleConcat<Elem, Output>::Result;
    };

    // *************************
    template<typename T>
    using IfConst = std::conditional_t<std::is_const_v<T>, std::tuple<T>, std::tuple<>>;

    template<typename T>
    using IfNotConst = std::conditional_t<std::is_const_v<T>, std::tuple<>, std::tuple<T>>;

    template<typename ... T>
    using FilterConst = decltype(std::tuple_cat(std::declval<IfNotConst<T>>()...));

    template<typename ... T>
    using FilterNotConst = decltype(std::tuple_cat(std::declval<IfConst<T>>()...));

    template<typename T> struct FuncTraits{};

    template<typename R, typename ... Args>
    struct FuncTraits<R(Args...)>
    {
        using ArgsTuple = std::tuple<Args ...>;
        using Return = R;
    };

    template<auto F>
    class FunctionBlock : public Block
    {
    public:
        virtual void Compute() override
        {
        }

        using Inputs = FuncTraits<&Plus>::Return;
    };

    template<>
    class FunctionBlock<Plus> : public Block
    {
    public:
        FunctionBlock<Plus>()
        {
            m_inputs.emplace_back();
            m_inputs.emplace_back();
            m_outputs.emplace_back();
        }

        virtual void Compute() override
        {
            auto& i1 = Helper::GetValue<long>(m_inputs[0].m_value);
            auto& i2 = Helper::GetValue<long>(m_inputs[1].m_value);
            long i3;
            Plus(i1, i2, i3);
            Helper::SetValue<long>(m_outputs[0].m_value, i3);
        }
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
    prop->Set(v1, "1");
    prop->Set(v2, "2");

    //Block* bl = new FunctionBlock<Plus>();
    //bl->Compute();

    using Var = ConcatTuple2<int, std::tuple<double, std::string, float>>;
    Var l;
    auto i = std::get<0>(l);
    auto j = std::get<1>(l);
    auto k = std::get<2>(l);
    auto m = std::get<3>(l);
    //std::cout << prop->Get(v3) << std::endl;
    return 1 - 1 ;
}
