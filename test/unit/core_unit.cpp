#include "gtest/gtest.h"

#include "lib/core/Registry.h"

class CoreTest : public ::testing::Test
{
public:
    static cement::Registry m_registry;
};

cement::Registry CoreTest::m_registry;

TEST_F(CoreTest, SimpleTest)
{
    // auto size = m_registry.CreateProperty<long>("Size");
    // auto color = m_registry.CreateProperty<std::string>("Color");
    // auto candle = m_registry.CreateModel("Candle");
    // // candle->AddProperty(size);
    // // candle->AddProperty(color);
    // auto candle1 = candle->Instanciate();
    // auto candle2 = candle->Instanciate();
    // candle->SetValue<long>(size, candle1, 32);
    // candle->SetValue<long>(size, candle2, 10);
    // candle->SetValue<std::string>(color, candle1, "Blue");
    // candle->SetValue<std::string>(color, candle2, "Red");
}