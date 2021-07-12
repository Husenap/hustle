[![build](https://github.com/Husenap/hustle/actions/workflows/build.yml/badge.svg)](https://github.com/Husenap/hustle/actions/workflows/build.yml)

# hustle

HUssein's Standard Template Library Extension.

This library is supposed to complement the STL by extending the functonality.

## Features
* algorithm
  * cleaner erase interface

## Example Usage

```cpp
#include <hustle/algorithm.hpp>
int main() {
    std::vector<int> nums{9, 8, 7};
    hustle::erase(nums, 8);
    // nums = {9, 7}

    std::string text = "Hello, World!";
    hustle::erase_if_not(text, ::islower);
    // text = "elloorld"
}
```


## The Name
Special thanks to [Joel](https://github.com/joerinn) for helping choose this awesome name!