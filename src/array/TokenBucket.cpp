#include <iostream>
#include <vector> 
#include <chrono>
#include <cassert>

struct TokenBucket {

    TokenBucket(int frequency, int duration_in_seconds) :
        _frequency(frequency),
        _duration(std::chrono::seconds(duration_in_seconds))
    {
        time_points.resize(frequency,std::chrono::system_clock::now());
    }

    [[nodiscard]] bool withdraw() {
        _index = ((_index + 1) % _frequency);
        
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - time_points[_index]);
        std::cout << seconds.count();

        return seconds <= _duration && (++count <= _frequency);
    }

    std::vector<std::chrono::time_point<std::chrono::system_clock>> time_points;
    int _frequency = 0;
    std::chrono::seconds _duration;

    int _index = -1;
    int count = 0;
};

// int main() {
//     TokenBucket tb(1,1);

//     assert(tb.withdraw());
//     assert(tb.withdraw() == false);

// }