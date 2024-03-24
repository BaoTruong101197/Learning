#include "thread/Thread.h"
#include <thread>

int main() {
    std::thread a([]() {
        std::cout << "AAAA";
    });

    return 0;
}