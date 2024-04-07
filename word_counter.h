#include <vector>
#include <initializer_list>
#include "entry.h"

const int HASH_TABLE_SIZE = 10;

class WordCounter
{
private:
    std::vector<Entry> counter;
    std::vector<std::reference_wrapper<Entry>> hashTable[HASH_TABLE_SIZE];

    int hashFn(const std::string& word) const;

    const std::vector<std::reference_wrapper<Entry>>& getHashChain(const std::string& word) const;
    std::vector<std::reference_wrapper<Entry>>& getHashChain(const std::string& word);

    const Entry& getEntry(const std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word) const;
    Entry& getEntry(std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word);

    bool isWord(const std::string& word) const;
public:
    WordCounter() = default;
    WordCounter(std::initializer_list<Entry> entry_lst);

    const Entry& operator[](const std::string& word) const;
    Entry& operator[](const std::string& word);

    void operator+=(const std::string& word);

    friend std::istream& operator>>(std::istream& is, WordCounter& counter);

    void addWord(const std::string& word);
    void addWords(const std::istream& is);
    void clear();

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
