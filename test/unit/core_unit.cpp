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
    auto size = m_registry.CreateProperty<long>("Size", false);
    auto color = m_registry.CreateProperty<std::string>("Color", true);
    auto thing = m_registry.CreateModel("Thing", true);
    auto thing_size = m_registry.AddProperty(thing, size, "Thing_Size");
    auto thing_color = m_registry.AddProperty(thing, color, "Thing_Color");

    auto blue_instance = color->Instanciate();
    auto red_instance = color->Instanciate();
    color->SetValue(blue_instance, "Blue");
    color->SetValue(red_instance, "Red");

    auto th1 = thing->Instanciate(); // size 1, red
    thing_color->SetValue(th1, red_instance);
    size->SetValue(thing_size->GetValue(th1), 1);

    auto th2 = thing->Instanciate(); // size 2, red
    thing_color->SetValue(th2, red_instance);
    size->SetValue(thing_size->GetValue(th2), 2);

    auto th3 = thing->Instanciate(); // size 3, blue
    thing_color->SetValue(th3, blue_instance);
    size->SetValue(thing_size->GetValue(th3), 3);

    std::cout << m_registry.Print() << std::endl;

    /** At this stage we should have this :
     * size [1,2,3]
     * color [Blue, Red]
     * thing_size [0,1,2]
     * thing_color [1,1,0]
     */

    EXPECT_EQ(thing->Size(), 3);
    EXPECT_EQ(thing->GetIndexes().size(), 2);
    EXPECT_TRUE(thing->GetIndexes().find(thing_size) != thing->GetIndexes().end());
    EXPECT_TRUE(thing->GetIndexes().find(thing_color) != thing->GetIndexes().end());

    EXPECT_EQ(size->GetIndexReferences().size(), 1);
    EXPECT_TRUE(size->GetIndexReferences().find(thing_size) != size->GetIndexReferences().end());
    EXPECT_EQ(color->GetIndexReferences().size(), 1);
    EXPECT_TRUE(color->GetIndexReferences().find(thing_color) != color->GetIndexReferences().end());

    EXPECT_EQ(size->GetValue(0), 1);
    EXPECT_EQ(size->GetValue(1), 2);
    EXPECT_EQ(size->GetValue(2), 3);
    EXPECT_EQ(color->GetValue(0), "Blue");
    EXPECT_EQ(color->GetValue(1), "Red");
    EXPECT_EQ(thing_size->GetValue(0), 0);
    EXPECT_EQ(thing_size->GetValue(1), 1);
    EXPECT_EQ(thing_size->GetValue(2), 2);
    EXPECT_EQ(thing_color->GetValue(0), 1);
    EXPECT_EQ(thing_color->GetValue(1), 1);
    EXPECT_EQ(thing_color->GetValue(2), 0);

    // Removing test

    thing->DeleteInstance(th2);
    std::cout << m_registry.Print() << std::endl;

    /** At this stage we should have this :
     * size [1,3]
     * color [Blue, Red]
     * thing_size [0,1]
     * thing_color [1,0]
     */

    EXPECT_EQ(size->GetValue(0), 1);
    EXPECT_EQ(size->GetValue(1), 3);
    EXPECT_EQ(color->GetValue(0), "Blue");
    EXPECT_EQ(color->GetValue(1), "Red");
    EXPECT_EQ(thing_size->GetValue(0), 0);
    EXPECT_EQ(thing_size->GetValue(1), 1);
    EXPECT_EQ(thing_color->GetValue(0), 1);
    EXPECT_EQ(thing_color->GetValue(1), 0);
}