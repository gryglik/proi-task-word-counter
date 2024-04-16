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
    std::vector<std::vector<Entry>::const_iterator> iteratorLexTable;
    std::vector<std::vector<unsigned int>> indexHashTable;

    inline int hashFn(const std::string& word) const;

    const Entry& getEntry(const std::string& word) const;
    Entry& getEntry(const std::string& word, bool add=false);
public:
    WordCounter();
    WordCounter(std::initializer_list<Entry> entry_lst);

    const Entry& operator[](const std::string& word) const;
    Entry& operator[](const std::string& word);

    void operator+=(const WordCounter& word_cnter);

    void addWord(const Entry& entry);
    void addWord(const std::string& word, int count = 1);
    void addWords(std::istream& is);

    void clear();

    class LexIterator;
    LexIterator lexBegin();
    LexIterator lexEnd() const;

    class FreqIterator;

    friend std::istream& operator>>(std::istream& is, WordCounter& word_cnter);
    friend std::ostream& operator<<(std::ostream& os, const WordCounter& word_cnter);
};

class WordCounter::LexIterator
{
private:
    std::vector<Entry>::const_iterator counterBegin;
    std::vector<Entry>::const_iterator counterEnd;

    std::vector<std::vector<Entry>::const_iterator> iteratorTable;
    int index;
public:
    LexIterator(std::vector<Entry>::const_iterator it,
        std::vector<Entry>::const_iterator cnt_begin,
        std::vector<Entry>::const_iterator cnt_end);

    LexIterator& operator++();
    LexIterator operator++(int);
    const Entry& operator*() const {return *(this->iteratorTable[index]);}
    bool operator!=(const LexIterator& it) const
        {return this->iteratorTable[this->index] != it.iteratorTable[it.index];};
};

class WordCounter::FreqIterator
{

};
