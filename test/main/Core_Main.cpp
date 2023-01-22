#include "lib/core/Registry.h"
#include "lib/core/Value.h"
#include "lib/core/Functions.h"
#include "lib/core/Node.h"
#include "lib/core/Block.h"
#include <iostream>
#include <tuple>

int main()
{
    using namespace cement;
    Registry reg;
    auto prop = reg.CreateProperty<long>("a", false);
    auto v1 = prop->Instanciate();
    auto v2 = prop->Instanciate();
    auto v3 = prop->Instanciate();

    auto bl = FunctionBlock<decltype(&Plus), &Plus>();
    bl.GetNode(0).m_value = Value{prop, v1};
    bl.GetNode(1).m_value = Value{prop, v2};
    bl.GetNode(2).m_value = Value{prop, v3};

    prop->Set(v1, "50");
    prop->Set(v2, "12");
    bl.Compute();

    std::cout << reg.Print() << std::endl;

    auto bl2 = FunctionBlock<decltype(&Minus), &Minus>();
    bl2.GetNode(0).m_value = Value{prop, v1};
    bl2.GetNode(1).m_value = Value{prop, v2};
    bl2.GetNode(2).m_value = Value{prop, v3};
    bl2.Compute();

    std::cout << reg.Print() << std::endl;
}
