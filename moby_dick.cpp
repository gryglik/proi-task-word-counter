#include "word_counter.h"
#include <fstream>
#include <chrono>

int main()
{
    WordCounter wc;
    std::ifstream in;
    // Creation time
    in.open("moby_dick.txt");
    auto start_time = std::chrono::high_resolution_clock::now();
    wc.addWords(in);
    auto end_time = std::chrono::high_resolution_clock::now();
    in.close();

    std::cout << "Creation time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Lexicographical iteration time (pre-incrementation)
    std::ofstream out("LEX_pre.txt");
    start_time = std::chrono::high_resolution_clock::now();
    auto it = wc.lexBegin();
    auto end = wc.lexEnd();
    while (it != end)
    {
        out << *it;
        ++it;
    }
    end_time = std::chrono::high_resolution_clock::now();
    out.close();
    std::cout << "Lexicographical iteration time (pre-incrementation): "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Lexicographical iteration time (post-incrementation)
    std::ofstream out2("LEX_post.txt");
    start_time = std::chrono::high_resolution_clock::now();
    it = wc.lexBegin();
    end = wc.lexEnd();
    while (it++ != end)
    {
        out2 << *it;
    }
    end_time = std::chrono::high_resolution_clock::now();
    out2.close();
    std::cout << "Lexicographical iteration time (pre-incrementation): "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    //Frequency iteration time
    std::ofstream out3("FREQ.txt");
    start_time = std::chrono::high_resolution_clock::now();
    auto it2 = wc.freqBegin();
    auto end2 = wc.freqEnd();
    while (it2 != end2)
    {
        out3 << *it2;
        ++it2;
    }
    end_time = std::chrono::high_resolution_clock::now();
    out3.close();
    std::cout << "Frequency iteration time: "
    << (end_time - start_time) / std::chrono::milliseconds(1) << " ms.\n";

    return 0;
}