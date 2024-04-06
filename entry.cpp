#include "entry.h"

std::istream& operator>>(std::istream& is, Entry& entry)
{
    char left, right;
    std::string value;
    int count;

    is >> left;
    if (is.eof())
        return is;
    is >> value >> count >> right;
    if (left != '[' || right != ']')
        throw std::invalid_argument("Invalid entry in >> operator.");

    entry.value  = value;
    entry.count = count;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Entry& entry)
{
    return os << '[' << *entry << " " << int(entry) << ']';
}