///
/// \file main.cpp
/// \copyright copyright &copy;2015 Device Controls for Scientific Research, LLC
///
#include <iostream>
#include <vector>

///
/// The main entry point.
///
int main() {
    std::vector<int> vec;
    vec.push_back(999);
    std::cout << "Hello, World! " << vec[0] << std::endl;
    return 0;
}