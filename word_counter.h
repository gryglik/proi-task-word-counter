#pragma once
#include <vector>
#include "entry.h"

class WordCounter
{
private:
    std::vector<Entry> counter;
public:
    WordCounter();

    void addWord(std::string& word);
    void clear();
};
