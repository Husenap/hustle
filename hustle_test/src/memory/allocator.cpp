#include <array>
#include <vector>

#include <gtest/gtest.h>
#include <hustle/memory.hpp>

template <template <class T> class Alloc>
void RunTheTest() {
    struct Data {
        float a, b, c, d;
        int   e, f, g;
        bool  h;
    };
    std::vector<Data, Alloc<Data>> nums;

    for (int n = 0; n < 1000; ++n) {
        for (int i = 0; i < 100; ++i) {
            nums.push_back(Data());
        }
        nums.clear();
        nums.shrink_to_fit();
    }
}

TEST(memory, custom_allocator) {
    RunTheTest<hustle::allocator>();
}

TEST(memory, std_allocator) {
    RunTheTest<std::allocator>();
}
