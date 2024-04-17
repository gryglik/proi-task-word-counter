#include <vector>
#include <list>
#include <initializer_list>
#include <algorithm>
#include "entry.h"

class WordCounter
{
private:
    static const int indexHashTableSize = 100000;
    std::vector<Entry> counter;
    std::vector<std::vector<unsigned int>> indexHashTable;

    inline int hashFn(const std::string& word) const;

    const Entry& getEntry(const std::string& word) const;
    Entry& getEntry(const std::string& word, bool add=false);
public:
    WordCounter();
    WordCounter(std::initializer_list<Entry> entry_lst);

    const Entry& operator[](const std::string& word) const
        {return this->getEntry(word);}
    Entry& operator[](const std::string& word)
        {return this->getEntry(word);}

    void operator+=(const WordCounter& word_cnter);

    void addWord(const Entry& entry);
    void addWord(const std::string& word, int count = 1)
        {this->addWord(Entry(word, count));}
    void addWords(std::istream& is);

    void clear();

    class LexIterator;
    LexIterator lexBegin() const;
    LexIterator lexEnd() const;

    class FreqIterator;
    FreqIterator freqBegin() const;
    FreqIterator freqEnd() const;

    friend std::istream& operator>>(std::istream& is, WordCounter& word_cnter);
    friend std::ostream& operator<<(std::ostream& os, const WordCounter& word_cnter);
};

class WordCounter::LexIterator
{
private:
    int index;
    std::vector<std::vector<Entry>::const_iterator> iteratorTable;

    std::vector<Entry>::const_iterator counterBegin;
    std::vector<Entry>::const_iterator counterEnd;
public:
    LexIterator(std::vector<Entry>::const_iterator it,
        std::vector<Entry>::const_iterator cnt_begin,
        std::vector<Entry>::const_iterator cnt_end);

    LexIterator& operator++();
    LexIterator operator++(int);
    const Entry& operator*() const {return *(this->iteratorTable[index]);}
    bool operator!=(const LexIterator& it) const
        {return this->iteratorTable[this->index] != it.iteratorTable[it.index];}
};

class WordCounter::FreqIterator
{
private:
    std::vector<Entry>::const_iterator iterator;

    std::vector<Entry>::const_iterator counterBegin;
    std::vector<Entry>::const_iterator counterEnd;
public:
    FreqIterator(std::vector<Entry>::const_iterator it,
        std::vector<Entry>::const_iterator cnt_begin,
        std::vector<Entry>::const_iterator cnt_end)
        : iterator(it), counterBegin(cnt_begin), counterEnd(cnt_end) {}

    FreqIterator& operator++();
    FreqIterator operator++(int);
    const Entry& operator*() const {return *iterator;}
    bool operator!=(const FreqIterator& it) const
        {return this->iterator != it.iterator;}

};
