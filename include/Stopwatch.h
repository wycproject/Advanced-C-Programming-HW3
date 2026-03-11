#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
    std::chrono::high_resolution_clock::time_point start;

public:
    Stopwatch() { reset(); }

    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }

    double read() const {
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        return duration.count() / 1000000.0;  // Convert microseconds to seconds.
    }
};

#endif // STOPWATCH_H
