#include <vector>

#include <gtest/gtest.h>
#include <hustle/memory.hpp>

template <typename T>
using myVector = std::vector<T, hustle::allocator<T>>;

TEST(memory, allocator) {
    struct Data {
        float a, b, c, d;
        int   e, f, g;
        bool  h;
    };
    myVector<Data> nums;
    std::cout << nums.get_allocator().get_memory_usage();
    for (int i = 0; i < 1000; ++i) {
        nums.push_back(Data());
    }
    nums.clear();
    for (int i = 0; i < 1000; ++i) {
        nums.push_back(Data());
    }
    std::cout << nums.get_allocator().get_memory_usage();
    nums.clear();
}
