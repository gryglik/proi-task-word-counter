#include "word_counter.h"
#include <fstream>
#include <chrono>

int main()
{
    WordCounter wc;
    std::ifstream in;
    // Create time
    in.open("moby_dick.txt");
    auto start_time = std::chrono::high_resolution_clock::now();
    wc.addWords(in);
    auto end_time = std::chrono::high_resolution_clock::now();
    in.close();

    std::cout << "Creation time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Lexicographical iteration time
    std::ofstream out("LEX.txt");
    auto it = wc.lexBegin();
    auto end = wc.lexEnd();
    start_time = std::chrono::high_resolution_clock::now();
    while (it != end)
    {
        out << *it;
        ++it;
    }
    end_time = std::chrono::high_resolution_clock::now();
    out.close();
    std::cout << "Lexicographical iteration time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Frequency iteration time
    std::ofstream out2("FREQ.txt");
    auto it2 = wc.freqBegin();
    auto end2 = wc.freqEnd();
    start_time = std::chrono::high_resolution_clock::now();
    while (it2 != end2)
    {
        out2 << *it2;
        ++it2;
    }
    end_time = std::chrono::high_resolution_clock::now();
    out2.close();
    std::cout << "Frequency iteration time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    return 0;
}