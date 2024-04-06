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
    Entry(const std::string& val, int cnt = 0)
        : value(val), count(cnt) {}

    const std::string& operator*() const {return value;};
    operator int() const {return count;}
    int operator++(int) {return count++;}

    friend std::istream& operator>>(std::istream& is, Entry& entry);
};

std::ostream& operator<<(std::ostream& os, const Entry& entry);