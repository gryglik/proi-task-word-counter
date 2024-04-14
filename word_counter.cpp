#include "word_counter.h"

int WordCounter::hashFn(const std::string& word) const
{
    std::hash<std::string> hash_fn;
    return hash_fn(word) % indexHashTableSize;
}

const std::vector<unsigned int>& WordCounter::getIndexChain(const std::string& word) const
{
    return this->indexHashTable[this->hashFn(word)];
}

std::vector<unsigned>& WordCounter::getIndexChain(const std::string& word)
{
    return this->indexHashTable[this->hashFn(word)];
}

const Entry& WordCounter::getEntry(const std::vector<unsigned int>& index_chain, const std::string& word) const
{
    auto it = std::find_if(
        index_chain.begin(), index_chain.end(),
        [=](int index){return *(this->counter[index]) == word;});

    if (it == index_chain.end())
        return this->counter[*(index_chain.begin())];
    return this->counter[*it];
}

Entry& WordCounter::getEntry(std::vector<unsigned int>& index_chain, const std::string& word)
{
    const WordCounter& constWC = *this;
    return const_cast<Entry&>(constWC.getEntry(index_chain, word));
}

bool WordCounter::isWord(const std::string& word) const
{
    if (this->getIndexChain(word).size() != 0)
    {
        const Entry& entry = this->getEntry(this->getIndexChain(word), word);
        if (*entry == word)
            return true;
    }
    return false;
}

WordCounter::WordCounter()
{
    this->indexHashTable.resize(this->indexHashTableSize);
}

WordCounter::WordCounter(std::initializer_list<Entry> entry_lst)
{
    this->indexHashTable.resize(this->indexHashTableSize);
    for (const Entry& entry : entry_lst)
        this->addWord(Entry(entry));
}

const Entry& WordCounter::operator[](const std::string& word) const
{
    if (! this->isWord(word))
        throw(std::invalid_argument("Given word does not exist in word counter."));

    return this->getEntry(this->getIndexChain(word), word);
}

Entry& WordCounter::operator[](const std::string& word)
{
    const WordCounter& constWC = *this;
    return const_cast<Entry&>(constWC[word]);
}

void WordCounter::operator+=(const std::string& word)
{
    this->addWord(word);
}

void WordCounter::addWord(const Entry& entry)
{
    if ((*entry).empty())
        throw(std::invalid_argument("Word cannot be empty"));
    if (this->isWord(*entry))
        this->operator[](*entry) += int(entry);
    else
    {
        this->counter.push_back(entry);
        int index = this->counter.end() - this->counter.begin() - 1;
        this->getIndexChain(*entry).push_back(index);
    }
}

void WordCounter::addWord(const std::string& word, int count)
{
    this->addWord(Entry(word, count));
}

void WordCounter::addWords(std::istream& is)
{
    Entry entry;
    while (is >> entry)
        this->addWord(entry);
}

void WordCounter::clear()
{
    this->counter.clear();
    this->indexHashTable.clear();
    this->indexHashTable.resize(this->indexHashTableSize);
}

std::istream& operator>>(std::istream& is, WordCounter& counter)
{
    std::string word;
    while (is >> word)
        counter.addWord(word);
    return is;
}
