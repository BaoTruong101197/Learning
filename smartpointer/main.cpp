#include <iostream>
#include "customs/SharedPtr.h"
#include "customs/UniquePtr.h"

int main()
{
    UniquePtr<int> ptr1 = UniquePtr<int>(new int(5));
    {
        UniquePtr<int> ptr2;
        ptr2 = std::move(ptr1);
        std::cout << *ptr2 << std::endl;
    }


    return 0;
}