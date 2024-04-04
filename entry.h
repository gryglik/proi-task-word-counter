#pragma once
#include <string>
#include <iostream>

class Entry
{
private:
    std::string value;
    int count = 0;
public:
    Entry() = default;
    Entry(const std::string& value, int count = 0);

    int operator++();
    const std::string& operator*() const;
    operator int() const;
};

std::ostream& operator<<(std::ostream& is, Entry& ent);
std::ostream& operator>>(std::ostream& is, Entry& ent);


