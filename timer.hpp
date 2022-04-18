#pragma once
#include <chrono>
#include <cmath>
#include <ctime>
#include <iostream>

class timer {
public:
    void start_count() {
        start = std::chrono::system_clock::now();
        running = true;
    }

    void stop_count() {
        end = std::chrono::system_clock::now();
        running = false;
    }

    int elapsedMilliseconds() {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (running) {
            endTime = std::chrono::system_clock::now();
        } else {
            endTime = end;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - start).count();
    }
private:
    std::chrono::time_point<std::chrono::system_clock> start;
    std::chrono::time_point<std::chrono::system_clock> end;
    bool running = false;
};