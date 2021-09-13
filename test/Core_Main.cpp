#include "lib/core/Registry.h"
#include <iostream>

int main()
{
    cement::Registry registry;

    auto size = registry.CreateProperty<long>("Size");
    auto color = registry.CreateProperty<std::string>("Color");
    auto candle = registry.CreateModel("Candle");
    candle->AddProperty(size);
    candle->AddProperty(color);
    auto candle1 = candle->Instanciate();
    auto candle2 = candle->Instanciate();
    candle->SetValue<long>(size, candle1, 32);
    candle->SetValue<long>(size, candle2, 10);
    candle->SetValue<std::string>(color, candle1, "Blue");
    candle->SetValue<std::string>(color, candle2, "Red");

    std::cout << registry.Print() << std::endl;
}
