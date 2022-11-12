#include "gtest/gtest.h"

#include "lib/core/Registry.h"
#include "lib/core/IncrementalId.h"
#include <plog/Appenders/ColorConsoleAppender.h>

TEST(IncrementalIdTest, adding_few_ids_test)
{
    cement::IncrementalId incid;
    ASSERT_EQ(0, incid.NextId()); //0
    incid.NextId(); //1
    incid.NextId(); //2
    ASSERT_EQ(incid.IsAvailable(2), false);
    ASSERT_EQ(incid.IsAvailable(3), true);
    incid.SetFree(1);
    ASSERT_EQ(incid.IsAvailable(1), true);
    incid.NextId(); //1
    ASSERT_EQ(incid.IsAvailable(1), false);
}

TEST(SparseTest, add_and_remove_ids_test)
{
    cement::Sparse sparse;
    cement::Sparse::Elem elem = 56;
    cement::Sparse::Elem elem2 = 85;
    sparse.AddElem(23);
    sparse.AddElem(41);
    cement::Id id = sparse.AddElem(elem);

    ASSERT_EQ(id, 2);
    ASSERT_EQ(sparse[id], elem);
    ASSERT_EQ(sparse.GetElem(id), elem);
    ASSERT_EQ(id, sparse.Find(elem));
    ASSERT_EQ(sparse.Find(elem2), NO_VALUE);

    sparse.SetElem(id, elem2);
    ASSERT_EQ(sparse.GetElem(id), elem2);
    ASSERT_EQ(sparse.Find(elem2), id);

    sparse.RemoveElem(id);
    auto id2 = sparse.Find(elem2);
    ASSERT_EQ(id2, NO_VALUE);
}

TEST(Core, SimpleTest)
{
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender; // Create the 2nd appender.
    plog::init(plog::debug, &consoleAppender);

    cement::Registry m_registry;
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
    size->SetValue(thing_size->Get(th1), 1);

    auto th2 = thing->Instanciate(); // size 2, red
    thing_color->SetValue(th2, red_instance);
    size->SetValue(thing_size->Get(th2), 2);

    auto th3 = thing->Instanciate(); // size 3, blue
    thing_color->SetValue(th3, blue_instance);
    size->SetValue(thing_size->Get(th3), 3);

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

    EXPECT_EQ(size->Get(0), 1);
    EXPECT_EQ(size->Get(1), 2);
    EXPECT_EQ(size->Get(2), 3);
    EXPECT_EQ(color->Get(0), "Blue");
    EXPECT_EQ(color->Get(1), "Red");
    EXPECT_EQ(thing_size->Get(0), 0);
    EXPECT_EQ(thing_size->Get(1), 1);
    EXPECT_EQ(thing_size->Get(2), 2);
    EXPECT_EQ(thing_color->Get(0), 1);
    EXPECT_EQ(thing_color->Get(1), 1);
    EXPECT_EQ(thing_color->Get(2), 0);

    // Removing test

    //thing->DeleteInstance(th2);
    std::cout << m_registry.Print() << std::endl;

    /** At this stage we should have this :
     * size [1,3]
     * color [Blue, Red]
     * thing_size [0,1]
     * thing_color [1,0]
     */
/*
    EXPECT_EQ(size->Get(0), 1);
    EXPECT_EQ(size->Get(1), 3);
    EXPECT_EQ(color->Get(0), "Blue");
    EXPECT_EQ(color->Get(1), "Red");
    EXPECT_EQ(thing_size->Get(0), 0);
    EXPECT_EQ(thing_size->Get(1), 1);
    EXPECT_EQ(thing_color->Get(0), 1);
    EXPECT_EQ(thing_color->Get(1), 0);*/
}

TEST(InstancesTest, add_and_remove_long_values_test)
{
    cement::Instances<long> prop(0, "LongProperty", false);
    auto id1 = prop.Instanciate();
    auto id2 = prop.AddValue(25);
    ASSERT_EQ(id1, 0);
    ASSERT_EQ(id2, 1);
    ASSERT_EQ(prop.Size(), 2);

    auto val1 = prop.Get(id1);
    auto val2 = prop.Get(id2);
    ASSERT_EQ(val1, 0);
    ASSERT_EQ(val2, 25);

    std::string val2_str;
    prop.Get(id2, val2_str);
    ASSERT_EQ(val2_str, "25");

    prop.SetValue(id1, 123);
    ASSERT_EQ(prop.Get(id1), 123);

    prop.Set(id2, "256");
    ASSERT_EQ(prop.Get(id2), 256);

    std::string val1_str;
    prop.GetPointedValue(id1, val1_str);
    ASSERT_EQ(val1_str, "123");
    ASSERT_EQ(prop.CountValues(123), 1);

    prop.AddValue(123);
    ASSERT_EQ(prop.CountValues(123), 2);

    prop.ReplaceValues(123, 124);
    ASSERT_EQ(prop.CountValues(123), 0);
    ASSERT_EQ(prop.CountValues(124), 2);
    ASSERT_EQ(prop.Size(), 3);

    prop.InternalDeleteInstance(id2);
    ASSERT_EQ(prop.Size(), 2);
    ASSERT_EQ(prop.Get(id1), 124);
    ASSERT_FALSE(prop.HasId(id2));
    ASSERT_EQ(prop.Get(id2), 0); // log error
    ASSERT_EQ(prop.Instanciate(), id2);
}

TEST(Core, modeltest)
{
    cement::Registry reg;
    auto day_p = reg.CreateProperty<long>("day", false);
    auto month_p = reg.CreateProperty<long>("month", false);
    auto year_p = reg.CreateProperty<long>("year", false);

    auto date_m = reg.CreateModel("date", false);
    auto date_day_i = reg.AddProperty(date_m, day_p, "day");
    auto date_month_i = reg.AddProperty(date_m, month_p, "month");
    auto date_year_i = reg.AddProperty(date_m, year_p, "year");

    auto firstname_p = reg.CreateProperty<std::string>("firstname", false);
    auto surname_p = reg.CreateProperty<std::string>("surname", false);
    auto isfemale_p = reg.CreateProperty<bool>("isfemale", false);

    auto person_m = reg.CreateModel("person", false);
    auto person_firstname_i = reg.AddProperty(person_m, firstname_p, "firstname");
    auto person_surname_i = reg.AddProperty(person_m, surname_p, "surname");
    auto person_isfemale_i = reg.AddProperty(person_m, isfemale_p, "isfemale");
    auto person_birthdate_i = reg.AddProperty(person_m, date_m, "birthdate");

    auto patricia = person_m->Instanciate();
    person_firstname_i->SetPointedValue<std::string>(patricia, "patricia");
    person_surname_i->SetPointedValue<std::string>(patricia, "porter");
    person_isfemale_i->SetPointedValue(patricia, true);

    auto patricia_birthday = person_birthdate_i->Get(patricia);
    auto patricia_birthday_day = date_day_i->Get(patricia_birthday);
    auto patricia_birthday_month = date_month_i->Get(patricia_birthday);
    auto patricia_birthday_year = date_year_i->Get(patricia_birthday);

    day_p->SetValue(patricia_birthday_day, 10);
    month_p->SetValue(patricia_birthday_month, 11);
    year_p->SetValue(patricia_birthday_year, 1992);

    std::cout << reg.Print();
    std::cout << person_m->PrettyPrint(patricia);
}

TEST(Core, idtest)
{
    cement::Registry registry;
    auto prop1 = registry.CreateProperty<bool>("prop", false);
    auto id = prop1->m_id;
    auto prop2 = registry.CreateProperty<bool>("prop2", false);
    ASSERT_EQ(prop2->m_id, id + 1);
    //TODO delete
}
