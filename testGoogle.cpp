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

TEST(EntryTest, right_shift_no_word)
{
    Entry ent1;
    std::stringstream is1, is2, is3, is4, is5, is6;
    is1 << "[1551]";
    EXPECT_THROW(is1 >> ent1, std::invalid_argument);
    is2 << "[ 1551]";
    EXPECT_THROW(is2 >> ent1, std::invalid_argument);
    is3 << "[  1551]";
    EXPECT_THROW(is3 >> ent1, std::invalid_argument);
    is4 << "[urobek]";
    EXPECT_THROW(is4 >> ent1, std::invalid_argument);
    is5 << "[urobek ]";
    EXPECT_THROW(is5 >> ent1, std::invalid_argument);
    is6 << "[urobek  ]";
    EXPECT_THROW(is6 >> ent1, std::invalid_argument);
}

TEST(EntryTest, right_shift_too_many_args)
{
    Entry ent1;
    std::stringstream is1, is2, is3, is4, is5, is6;
    is1 << "[analiza 12 2]";
    EXPECT_THROW(is1 >> ent1, std::invalid_argument);
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

TEST(WordCounterTest, addWord_string)
{
    WordCounter wc;
    wc.addWord("urobek");
    ASSERT_EQ(int(wc["urobek"]), 1);
    wc.addWord("urobek");
    ASSERT_EQ(int(wc["urobek"]), 2);
    wc.addWord("pragmatyzm");
    ASSERT_EQ(int(wc["pragmatyzm"]), 1);
}

TEST(WordCounterTest, addWord_Entry)
{
    WordCounter wc;
    wc.addWord(Entry("urobek", 11009));
    ASSERT_EQ(int(wc["urobek"]), 11009);
    wc.addWord(Entry("urobek", 889));
    ASSERT_EQ(int(wc["urobek"]), 11009+889);
}

TEST(WordCounterTest, create_list)
{
    WordCounter wc{{"urobek", 1911},
        {"kontrowersja", 1}, {"Artur", 33}};
    ASSERT_EQ(int(wc["urobek"]), 1911);
    ASSERT_EQ(int(wc["kontrowersja"]), 1);
    ASSERT_EQ(int(wc["Artur"]), 33);
}

TEST(WordCounterTest, addWord_empty)
{
    WordCounter wc;
    EXPECT_THROW(wc.addWord(""), std::invalid_argument);
    EXPECT_THROW(wc.addWord(Entry()), std::invalid_argument);
}

TEST(WordCounterTest, addWords_typical)
{
    WordCounter wc;
    std::stringstream data("[urobek 1234] [pragmatyzm 18111] [Inkubacja 15]");
    wc.addWords(data);
    ASSERT_EQ(int(wc["urobek"]), 1234);
    ASSERT_EQ(int(wc["pragmatyzm"]), 18111);
    ASSERT_EQ(int(wc["Inkubacja"]), 15);
}

TEST(WordCounterTest, addWords_spaces)
{
    WordCounter wc;
    std::stringstream data("[urobek 1234] [pragmatyzm 18111]  [Inkubacja 15] ");
    wc.addWords(data);
    ASSERT_EQ(int(wc["urobek"]), 1234);
    ASSERT_EQ(int(wc["pragmatyzm"]), 18111);
    ASSERT_EQ(int(wc["Inkubacja"]), 15);
}

TEST(WordCounterTest, addWords_no_word)
{
    WordCounter wc;
    std::stringstream data("[ 1234] [pragmatyzm 18111]  [Inkubacja 15] ");
    EXPECT_THROW(wc.addWords(data), std::invalid_argument);
}

TEST(WordCounterTest, clear_typical)
{
    WordCounter wc;
    wc.addWord("urobek");
    wc.addWord("urobek");
    wc.addWord("pragmatyzm");
    ASSERT_EQ(int(wc["urobek"]), 2);
    ASSERT_EQ(int(wc["pragmatyzm"]), 1);
    wc.clear();
    EXPECT_THROW(wc["urobek"], std::invalid_argument);
    EXPECT_THROW(wc["pragmatyzm"], std::invalid_argument);
}

TEST(WordCounterTest, right_shift_operator_typical)
{
    WordCounter wc;
    std::stringstream data("Anna idzie do kina z Marianem Anna i Marian są małżeństwem");
    data >> wc;
    ASSERT_EQ(int(wc["Anna"]), 2);
    ASSERT_EQ(int(wc["idzie"]), 1);
    ASSERT_EQ(int(wc["do"]), 1);
    ASSERT_EQ(int(wc["kina"]), 1);
    ASSERT_EQ(int(wc["z"]), 1);
    ASSERT_EQ(int(wc["Marianem"]), 1);
    ASSERT_EQ(int(wc["i"]), 1);
    ASSERT_EQ(int(wc["Marian"]), 1);
    ASSERT_EQ(int(wc["są"]), 1);
    ASSERT_EQ(int(wc["małżeństwem"]), 1);
}

TEST(WordCounterTest, right_shift_operator_spaces)
{
    WordCounter wc;
    std::stringstream data("Anna Anna  Anna  Anna");
    data >> wc;
    ASSERT_EQ(int(wc["Anna"]), 4);
}

TEST(WordCounterTest, right_shift_operator_enters)
{
    WordCounter wc;
    std::stringstream data("Anna\nAnna \nAnna \n Anna Anna   \n  Anna");
    data >> wc;
    ASSERT_EQ(int(wc["Anna"]), 6);
}

TEST(WordCounterTest, right_shift_operator_enters_many_words)
{
    WordCounter wc;
    std::stringstream data("Anna\nMarian \nMarian \n Anna Anna\nMarian\nMarian   \n  Anna");
    data >> wc;
    ASSERT_EQ(int(wc["Anna"]), 4);
    ASSERT_EQ(int(wc["Marian"]), 4);
}