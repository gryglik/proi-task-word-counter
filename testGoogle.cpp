#include <gtest/gtest.h>
#include <sstream>
#include "word_counter.h"

TEST(EntryTest, create_default)
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
