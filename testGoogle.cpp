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

TEST(EntryTest, increase_operator_typical)
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
        {"kontrowersja", 1}, {"artur", 33}};
    ASSERT_EQ(int(wc["urobek"]), 1911);
    ASSERT_EQ(int(wc["kontrowersja"]), 1);
    ASSERT_EQ(int(wc["artur"]), 33);
}

TEST(WordCounterTest, increase_operator_typical)
{
    WordCounter wc1{{"urobek", 1911},
        {"kontrowersja", 1}, {"artur", 33}};
    WordCounter wc2{{"urobek", 2},
        {"pragmatyzm", 1}, {"inkubacja", 1}};
    wc1 += wc2;
    ASSERT_EQ(int(wc1["urobek"]), 1913);
    ASSERT_EQ(int(wc1["kontrowersja"]), 1);
    ASSERT_EQ(int(wc1["artur"]), 33);
    ASSERT_EQ(int(wc1["pragmatyzm"]), 1);
    ASSERT_EQ(int(wc1["inkubacja"]), 1);

    EXPECT_THROW(wc2["kontrowersja"], std::invalid_argument);
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
    std::stringstream data("anna idzie do kina z marianem anna i marian są malzenstwem");
    wc.addWords(data);
    ASSERT_EQ(int(wc["anna"]), 2);
    ASSERT_EQ(int(wc["idzie"]), 1);
    ASSERT_EQ(int(wc["do"]), 1);
    ASSERT_EQ(int(wc["kina"]), 1);
    ASSERT_EQ(int(wc["z"]), 1);
    ASSERT_EQ(int(wc["marianem"]), 1);
    ASSERT_EQ(int(wc["i"]), 1);
    ASSERT_EQ(int(wc["marian"]), 1);
    ASSERT_EQ(int(wc["są"]), 1);
    ASSERT_EQ(int(wc["malzenstwem"]), 1);
}

TEST(WordCounterTest, addWords_spaces)
{
    WordCounter wc;
    std::stringstream data(" anna anna  anna  anna"  );
    wc.addWords(data);
    ASSERT_EQ(int(wc["anna"]), 4);
}

TEST(WordCounterTest, addWords_new_lines)
{
    WordCounter wc;
    std::stringstream data("anna\nanna \nanna \n anna anna   \n  anna");
    wc.addWords(data);
    ASSERT_EQ(int(wc["anna"]), 6);
}

TEST(WordCounterTest, addWords_new_lines_many_words)
{
    WordCounter wc;
    std::stringstream data("anna\nmarian \nmarian \n anna anna\nmarian\nmarian   \n  anna");
    wc.addWords(data);
    ASSERT_EQ(int(wc["anna"]), 4);
    ASSERT_EQ(int(wc["marian"]), 4);
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

TEST(WordCounterTest, right_shift_operator_import_typical)
{
    WordCounter wc;
    std::stringstream data("[urobek 1234] [pragmatyzm 18111] [Inkubacja 15]");
    data >> wc;
    ASSERT_EQ(int(wc["urobek"]), 1234);
    ASSERT_EQ(int(wc["pragmatyzm"]), 18111);
    ASSERT_EQ(int(wc["Inkubacja"]), 15);
}

TEST(WordCounterTest, right_shift_operator_import_spaces)
{
    WordCounter wc;
    std::stringstream data("[urobek 1234] [pragmatyzm 18111]  [Inkubacja 15] ");
    data >> wc;
    ASSERT_EQ(int(wc["urobek"]), 1234);
    ASSERT_EQ(int(wc["pragmatyzm"]), 18111);
    ASSERT_EQ(int(wc["Inkubacja"]), 15);
}

TEST(WordCounterTest, right_shift_operator_import_no_word)
{
    WordCounter wc;
    std::stringstream data("[ 1234] [pragmatyzm 18111]  [Inkubacja 15] ");
    EXPECT_THROW(data >> wc, std::invalid_argument);
}

TEST(WordCounterTest, left_shift_operator_export_typical)
{
    WordCounter wc;
    std::stringstream input("[urobek 1234] [pragmatyzm 18111] [Inkubacja 15]");
    input >> wc;

    std::stringstream output;
    output << wc;
    ASSERT_EQ(output.str(),"[urobek 1234] [pragmatyzm 18111] [Inkubacja 15]");
}

TEST(WordCounterLexIteratorTest, lexBegin_typical)
{
    WordCounter wc;
    std::stringstream data("anna idzie do kina z marianem anna i marian są malzenstwem");
    wc.addWords(data);
    ASSERT_EQ(*(*wc.lexBegin()), "anna");
}

TEST(WordCounterLexIteratorTest, lexBegin_same_chars)
{
    WordCounter wc;
    std::stringstream data("annam anno anna");
    wc.addWords(data);
    ASSERT_EQ(*(*wc.lexBegin()), "anna");
}

TEST(WordCounterLexIteratorTest, post_incrementation)
{
    WordCounter wc;
    std::stringstream data("annam anno anna marek");
    wc.addWords(data);
    auto it = wc.lexBegin();
    ASSERT_EQ(**it++, "anna");
    ASSERT_EQ(**it, "annam");
}

TEST(WordCounterLexIteratorTest, pre_incrementation)
{
    WordCounter wc;
    std::stringstream data("annam anno anna marek");
    wc.addWords(data);
    auto it = wc.lexBegin();
    ASSERT_EQ(**++it, "annam");
    ASSERT_EQ(**it, "annam");
}

TEST(WordCounterLexIteratorTest, lexEnd_iteration_typical)
{
    WordCounter wc;
    std::stringstream data("marianem anna z marianem");
    wc.addWords(data);
    auto it = wc.lexBegin();
    ASSERT_EQ(**it++, "anna");
    ASSERT_EQ(int(*it), 2);
    ASSERT_EQ(**it++, "marianem");
    ASSERT_EQ(**it++, "z");
    ASSERT_EQ(it != wc.lexEnd(), false);
}

TEST(WordCounterFreqIteratorTest, freqBegin_typical)
{
    WordCounter wc;
    std::stringstream data("idzie anna do kina z marianem anna i marian są malzenstwem");
    wc.addWords(data);
    ASSERT_EQ(*(*wc.freqBegin()), "anna");
}

TEST(WordCounterFreqIteratorTest, freqBegin_same_count)
{
    WordCounter wc;
    std::stringstream data("idzie anna idzie anna");
    wc.addWords(data);
    ASSERT_EQ(*(*wc.freqBegin()), "idzie");
}

TEST(WordCounterFreqIteratorTest, post_incrementation)
{
    WordCounter wc;
    std::stringstream data("tomek anna marek marek zosia");
    wc.addWords(data);
    auto it = wc.freqBegin();
    ASSERT_EQ(**it++, "marek");
    ASSERT_EQ(**it, "tomek");
}

TEST(WordCounterFreqIteratorTest, pre_incrementation)
{
    WordCounter wc;
    std::stringstream data("tomek anna marek marek zosia");
    wc.addWords(data);
    auto it = wc.freqBegin();
    ASSERT_EQ(**++it, "tomek");
    ASSERT_EQ(**it, "tomek");
}

TEST(WordCounterFreqIteratorTest, freqBegin_full_iteration)
{
    WordCounter wc;
    std::stringstream data("idzie anna z marianem z marianem anna z marianem anna idzie marianem idzie anna");
    wc.addWords(data);
    auto freq_it = wc.freqBegin();
    ASSERT_EQ(**freq_it++, "anna");
    ASSERT_EQ(**freq_it++, "marianem");
    ASSERT_EQ(**freq_it++, "idzie");
    ASSERT_EQ(**freq_it++, "z");
    ASSERT_EQ(freq_it != wc.freqEnd(), false);
}