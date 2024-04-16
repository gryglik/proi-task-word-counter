#include "word_counter.h"

inline int WordCounter::hashFn(const std::string& word) const
{
    std::hash<std::string> hash_fn;
    return hash_fn(word) % indexHashTableSize;
}

const Entry& WordCounter::getEntry(const std::string& word) const
{
    const std::vector<unsigned int>& index_chain = this->indexHashTable[this->hashFn(word)];

    auto it = std::find_if(
        index_chain.begin(), index_chain.end(),
        [=](int index){return *(this->counter[index]) == word;});

    if (it == index_chain.end())
        throw(std::invalid_argument("Given word does not exist in word counter."));
    return this->counter[*it];
}

Entry& WordCounter::getEntry(const std::string& word, bool add)
{
    std::vector<unsigned int>& index_chain = this->indexHashTable[this->hashFn(word)];

    auto it = std::find_if(
        index_chain.begin(), index_chain.end(),
        [=](int index){return *(this->counter[index]) == word;});

    if (it != index_chain.end())
        return this->counter[*it];

    if (add)
    {
        this->counter.push_back(Entry(word));
        index_chain.push_back(this->counter.size() - 1);
        return this->counter.back();
    }
    throw(std::invalid_argument("Given word does not exist in word counter."));
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
   return this->getEntry(word);
}

Entry& WordCounter::operator[](const std::string& word)
{
    return this->getEntry(word);
}

void WordCounter::operator+=(const WordCounter& word_cnter)
{
    for (const Entry& ent : word_cnter.counter)
        this->addWord(ent);
}

void WordCounter::addWord(const Entry& ent)
{
    if ((*ent).empty())
        throw(std::invalid_argument("Word cannot be empty"));
    this->getEntry(*ent, true) += int(ent);
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

std::istream& operator>>(std::istream& is, WordCounter& word_cnter)
{
    Entry ent;
    while (is >> ent)
        word_cnter.addWord(ent);
    return is;
}

std::ostream& operator<<(std::ostream& os, const WordCounter& word_cnter)
{
    if (word_cnter.counter.size())
    {
        os << *word_cnter.counter.begin();
        for (std::vector<Entry>::const_iterator it = ++word_cnter.counter.begin();
            it != word_cnter.counter.end();
            it++)
            os << " " << *it;
    }
    return os;
}

WordCounter::LexIterator WordCounter::lexBegin() const
{
    return WordCounter::LexIterator(
    std::min_element(this->counter.begin(), this->counter.end(),
        [](const Entry& ent1, const Entry& ent2){return *(ent1) < *(ent2);}),
        this->counter.begin(), this->counter.end());
}

WordCounter::LexIterator WordCounter::lexEnd() const
{
   return WordCounter::LexIterator(this->counter.end(), this->counter.end(), this->counter.end());
}

WordCounter::LexIterator::LexIterator(std::vector<Entry>::const_iterator it,
    std::vector<Entry>::const_iterator cnt_begin,
    std::vector<Entry>::const_iterator cnt_end)
    {
        this->counterBegin = cnt_begin;
        this->counterEnd = cnt_end;

        for (std::vector<Entry>::const_iterator iterator = cnt_begin; iterator!=cnt_end; iterator++)
        {
            this->iteratorTable.push_back(iterator);
        }

        sort(iteratorTable.begin(), iteratorTable.end(),
        [=](auto i1, auto i2){return **i1 < **i2;});
        this->iteratorTable.push_back(cnt_end);

        for (int i=0; i != this->iteratorTable.size(); i++)
        {
            if (this->iteratorTable[i] == it)
            {
                this->index = i;
                break;
            }
        }
    }

WordCounter::LexIterator& WordCounter::LexIterator::operator++()
{
    index++;
    return *this;
}

WordCounter::LexIterator WordCounter::LexIterator::operator++(int)
{
    WordCounter::LexIterator old_it = *this;
    this->operator++();
    return old_it;
}