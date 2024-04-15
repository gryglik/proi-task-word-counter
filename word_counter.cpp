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

void WordCounter::operator+=(const WordCounter& word_cnter)
{
    for (const Entry& ent : word_cnter.counter)
        this->addWord(ent);
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
   std::string word;
    while (is >> word)
        this->addWord(word);
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

std::ostream& operator<<(std::ostream& os, const WordCounter& counter)
{
    return os;
}

WordCounter::LexIterator WordCounter::lexBegin() const
{
    return WordCounter::LexIterator(
    std::max_element(this->counter.begin(), this->counter.end(),
        [](const Entry& ent1, const Entry& ent2){return *(ent1) > *(ent2);}),
        this->counter.begin(), this->counter.end());
}

WordCounter::LexIterator WordCounter::lexEnd() const
{
   return WordCounter::LexIterator(this->counter.end(), this->counter.begin(), this->counter.end());
}

WordCounter::LexIterator& WordCounter::LexIterator::operator++()
{
    std::vector<Entry>::const_iterator old_it = this->iterator;

    std::vector<Entry>::const_iterator new_it = this->counterEnd;
    for (std::vector<Entry>::const_iterator it = this->counterBegin;
        it != counterEnd;
        it++)
        if (**it > **old_it)
        {
            new_it = it;
            break;
        }
    for (std::vector<Entry>::const_iterator it = this->counterBegin;
        it != this->counterEnd && new_it != this->counterEnd;
        it++)
        if (**old_it < **it && **it < **new_it)
            new_it = it;
    this->iterator = new_it;
    return *this;
}

WordCounter::LexIterator WordCounter::LexIterator::operator++(int)
{
    WordCounter::LexIterator old_it = *this;
    this->operator++();
    return old_it;
}