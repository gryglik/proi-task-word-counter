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

    std::cout << "Create time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Lexicographical iteration time
    start_time = std::chrono::high_resolution_clock::now();
    for (auto it = wc.lexBegin(); it != wc.lexEnd(); it++) {}
    end_time = std::chrono::high_resolution_clock::now();

    std::cout << "Lexicographical iteration time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    return 0;
}