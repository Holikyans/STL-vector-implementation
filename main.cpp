#include "vector.h"
#include <vector>
#include <iostream>


const int foo(int x)
{
    return x * 2;
}
int main()
{
    int res = foo(3);
    res++;
    std::cout << res;
    return 0;
}




