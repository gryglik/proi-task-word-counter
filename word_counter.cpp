#include "word_counter.h"

int WordCounter::hashFn(const std::string& word) const
{
    std::hash<std::string> hash_fn;
    return hash_fn(word) % HASH_TABLE_SIZE;
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
    std::vector<std::reference_wrapper<Entry>>::const_iterator i = std::find_if(
        entries_refs_chain.begin(), entries_refs_chain.end(),
        [&word](const std::reference_wrapper<Entry> &entry_ref){return *(entry_ref.get()) == word;});

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

void WordCounter::addWord(const std::string& word)
{
    if (this->isWord(word))
        this->operator[](word)++;
    else
    {
        this->counter.push_back(Entry(word, 1));
        this->getHashChain(word).push_back(std::ref(*counter.rbegin()));
    }
}