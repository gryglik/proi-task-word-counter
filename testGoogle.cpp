#include <gtest/gtest.h>
#include <sstream>
#include "word_counter.h"

TEST(EntryTest, create_default_int_and_indirection_operators)
{
    Entry ent1;
    ASSERT_EQ(int(ent1), 0);
    ASSERT_EQ(*(ent1), "");
}

TEST(EntryTest, create_typical)
{
    Entry ent1("urobek", 5);
    ASSERT_EQ(int(ent1), 5);
    ASSERT_EQ(*(ent1), "urobek");
}

TEST(EntryTest, create_copy)
{
    Entry ent1("urobek", 18811);
    ASSERT_EQ(int(ent1), 18811);
    Entry ent2(ent1);
    ASSERT_EQ(*(ent2), "urobek");
    ASSERT_EQ(int(ent2), 18811);
    ent2++;
    ASSERT_EQ(int(ent1), 18811);
    ASSERT_EQ(int(ent2), 18812);
}

TEST(EntryTest, addition_operator_typical)
{
    Entry ent1("urobek", 5);
    ASSERT_EQ(int(ent1), 5);
    ent1 += 11;
    ASSERT_EQ(int(ent1), 16);
}

TEST(EntryTest, post_increment_operator_typical)
{
    Entry ent1("urobek", 5);
    ASSERT_EQ(ent1++, 5);
    ASSERT_EQ(int(ent1), 6);
}

TEST(EntryTest, right_shift_operator_typical)
{
    Entry ent1;
    std::stringstream is;
    is << "[urobek 1551]";
    is >> ent1;
    ASSERT_EQ(*ent1, "urobek");
    ASSERT_EQ(int(ent1), 1551);
}

TEST(EntryTest, right_shift_operator_invalid_format)
{
    Entry ent1;
    std::stringstream is;
    is << "urobek 1551";
    EXPECT_THROW(is >> ent1, std::invalid_argument);
}

TEST(EntryTest, left_shift_operator_typical)
{
    Entry ent1("urobek", 1551);
    std::stringstream is;
    is << ent1;
    ASSERT_EQ(is.str(), "[urobek 1551]");
}

TEST(WordCounterTest, addWordc_create_indexOperator_typical)
{
    WordCounter wc;
    wc.addWord("urobek");
    ASSERT_EQ(int(wc["urobek"]), 1);
    wc.addWord("urobek");
    ASSERT_EQ(int(wc["urobek"]), 2);
    wc.addWord("pragmatyzm");
    ASSERT_EQ(int(wc["pragmatyzm"]), 1);
}

// TEST(WordCounterTest, create_list)
// {
//     WordCounter wc
//     {
//         {"urobek", 1911},
//         {"kontrowersja", 1},
//         {"Artur", 33}
//     };
//     ASSERT_EQ(int(wc["urobek"]), 1911);
//     ASSERT_EQ(int(wc["ukontrowersja"]), 1);
//     ASSERT_EQ(int(wc["Artur"]), 33);
// }

TEST(WordCounterTest, addWord_empty)
{
    WordCounter wc;
    EXPECT_THROW(wc.addWord(""), std::invalid_argument);
}
