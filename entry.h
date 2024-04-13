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
    Entry(const Entry& entry);

    const std::string& operator*() const {return value;};
    operator int() const {return count;}
    void operator+=(int add_value) {this->count+=add_value;}
    int operator++(int) {return count++;}

    friend std::istream& operator>>(std::istream& is, Entry& entry);
};

std::ostream& operator<<(std::ostream& os, const Entry& entry);