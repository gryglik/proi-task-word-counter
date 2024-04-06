#pragma once
#include <vector>
#include <initializer_list>
#include "entry.h"

class WordCounter
{
private:
    std::vector<Entry> counter;
public:
    WordCounter() = default;
    WordCounter(std::initializer_list<Entry> entry_lst);

    void addWord(std::string& word);
    void addWords(std::istream& is);
    void clear();

    const Entry& operator[](const std::string& value) const;
    Entry& operator[](const std::string& value);

    void operator+=(const std::string& value);

    friend std::istream& operator>>(std::istream& is, WordCounter& counter);

    class LexIterator;
    LexIterator lexBegin() const;
    LexIterator lexEnd() const;

    class FreqIterator;
};

std::ostream& operator<<(std::ostream& os, const WordCounter& counter);

class WordCounter::LexIterator
{
private:
    std::vector<Entry>::const_iterator iterator;
public:
    LexIterator();
    LexIterator(std::vector<Entry>::const_iterator it)
        : iterator(it) {}

    LexIterator operator++(int);
    LexIterator& operator++();
    const Entry& operator*() const {return *iterator;}
    bool operator!=(const LexIterator& it) const;
};

class WordCounter::FreqIterator
{

};
