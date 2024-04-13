#include "word_counter.h"

int WordCounter::hashFn(const std::string& word) const
{
    std::hash<std::string> hash_fn;
    return hash_fn(word) % hashTableSize;
}

const std::vector<std::reference_wrapper<Entry>>& WordCounter::getHashChain(const std::string& word) const
{
    return this->hashTable[this->hashFn(word)];
}

std::vector<std::reference_wrapper<Entry>>& WordCounter::getHashChain(const std::string& word)
{
    return this->hashTable[this->hashFn(word)];
}

const Entry& WordCounter::getEntry(const std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word) const
{
    auto i = std::find_if(
        entries_refs_chain.begin(), entries_refs_chain.end(),
        [&word](const std::reference_wrapper<Entry> &entry_ref){return *(entry_ref.get()) == word;});

    if (i == entries_refs_chain.end())
        i = entries_refs_chain.begin();
    return (*i).get();
}

Entry& WordCounter::getEntry(std::vector<std::reference_wrapper<Entry>>& entries_refs_chain, const std::string& word)
{
    const WordCounter& constWC = *this;
    return const_cast<Entry&>(constWC.getEntry(entries_refs_chain, word));
}

bool WordCounter::isWord(const std::string& word) const
{
    if (this->getHashChain(word).size() != 0)
    {
        const Entry& entry = this->getEntry(this->getHashChain(word), word);
        if (*entry == word)
            return true;
    }
    return false;
}

WordCounter::WordCounter()
{
    hashTable.resize(this->hashTableSize);
}

const Entry& WordCounter::operator[](const std::string& word) const
{
    if (! this->isWord(word))
        throw(std::invalid_argument("Given word does not exist in word counter."));

    return this->getEntry(this->getHashChain(word), word);
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

void WordCounter::addWord(const std::string& word, int count)
{
    if (word.empty())
        throw(std::invalid_argument("Word cannot be empty"));
    if (this->isWord(word))
        this->operator[](word)+=count;
    else
    {
        this->counter.push_back(Entry(word, count));
        this->getHashChain(word).push_back(std::ref(*counter.rbegin()));
    }
}
