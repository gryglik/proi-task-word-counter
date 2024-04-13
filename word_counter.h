#include <vector>
#include <initializer_list>
#include "entry.h"


class WordCounter
{
private:
    static const int hashTableSize = 10000;

    std::vector<Entry> counter;
    std::vector<std::vector<std::reference_wrapper<Entry>>> hashTable;

    int hashFn(const std::string& word) const;

    const std::vector<std::reference_wrapper<Entry>>& getHashChain(const std::string& word) const;
    std::vector<std::reference_wrapper<Entry>>& getHashChain(const std::string& word);

    const Entry& getEntry(const std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word) const;
    Entry& getEntry(std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word);

    bool isWord(const std::string& word) const;
public:
    WordCounter();
    WordCounter(std::initializer_list<Entry> entry_lst);

    const Entry& operator[](const std::string& word) const;
    Entry& operator[](const std::string& word);

    void operator+=(const std::string& word);

    void addWord(const std::string& word, int count = 1);
    void addWord(const Entry& entry);
    void addWords(std::istream& is);

    void clear();

    class LexIterator;
    LexIterator lexBegin() const;
    LexIterator lexEnd() const;

    class FreqIterator;

    friend std::istream& operator>>(std::istream& is, WordCounter& counter);
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
