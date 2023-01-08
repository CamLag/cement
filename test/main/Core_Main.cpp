#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include <iostream>
#include <tuple>

void PlusHM(const long& i1, const long& i2, long& i3)
{
    i3 = i1 + i2;
}

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

    template<typename T>
    using IfConst = std::conditional_t<std::is_const_v<T>, std::tuple<T>, std::tuple<>>;

    template<typename T>
    using IfNotConst = std::conditional_t<std::is_const_v<T>, std::tuple<>, std::tuple<T>>;

    template<typename ... T>
    using FilterConst = decltype(std::tuple_cat(std::declval<IfNotConst<T>>()...));

    template<typename ... T>
    using FilterNotConst = decltype(std::tuple_cat(std::declval<IfConst<T>>()...));

    template<typename  T> struct FuncTraits{};

    template<typename R, typename... Args>
    struct FuncTraits<R(Args...)>
    {
        using ArgsTuple = std::tuple<Args ...>;
        using Return = R;
        using Inputs = FilterConst<Args...>;
        using Outputs = FilterNotConst<Args...>;
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
        virtual Node& InputNode(size_t index) = 0;
        virtual Node& OutputNode(size_t index) = 0;

    protected:
        size_t InputSize{};
        size_t OutputSize{};
    };

    template<auto F>
    class FunctionBlock : public Block
    {
    public:
        using ReturnType = typename FuncTraits<decltype(F)>::Return;
        using InputTypes = typename FuncTraits<decltype(F)>::Inputs;
        using OutputTypes = typename FuncTraits<decltype(F)>::Outputs;
        static auto InputSize = FuncTraits<decltype(F)>::InputSize;
        static auto OutputSize = FuncTraits<decltype(F)>::OutputSize;

        FunctionBlock()
        {
        }

        virtual void Compute() override
        {
        }

        template<size_t... Is>
        InputTypes BuildInputs()
        {
            std::make_integer_sequence<size_t, InputSize> input_sequence;
            return std::make_tuple(Helper::GetValue<std::tuple_element_t<Is>>(Inputs[input_sequence]...));
        }

        virtual Node& InputNode(size_t index) override
        {
            return Inputs[index];
        }

        virtual Node& OutputNode(size_t index) override
        {
            return Outputs[index];
        }

        std::array<Node, InputSize> Inputs;
        std::array<Node, OutputSize> Outputs;

    };

    template<>
    class FunctionBlock<PlusHM> : public Block
    {
    public:
        FunctionBlock<PlusHM>()
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
            PlusHM(i1, i2, i3);
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

    //std::cout << prop->Get(v3) << std::endl;
}
