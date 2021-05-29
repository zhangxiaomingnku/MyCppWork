// vector::at
#include <iostream>
#include <vector>

/*
g++ -std=c++11 sizeof_test.cpp
*/

int main ()
{
    int* ptr = nullptr;
    std::cout << "size of ptr is " << sizeof(ptr) << std::endl;
    int x = 1;
    std::cout << "size of int is " << sizeof(x) << std::endl;
    char y = 'a';
    std::cout << "size of uint32_t is " << sizeof(uint32_t) << std::endl;
    
    return 0;
}
