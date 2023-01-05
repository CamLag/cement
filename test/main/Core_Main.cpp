#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include <iostream>

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

    template<typename ... T> struct InputTraits
    {

    };

    template<typename T> struct FuncTraits{};
    template<typename R, typename ... In, typename ... Out> struct FuncTraits<R(In..., Out...)>
    {

    };

    template<auto F>
    class FunctionBlock : public Block
    {
    public:
        virtual void Compute() override
        {
        }
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

    Block* bl = new FunctionBlock<Plus>();
    bl->Compute();

    std::cout << prop->Get(v3);
}
