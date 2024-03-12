#include <iostream>
#include "customs/SharedPtr.h"

int main()
{
    SharedPtr<int> ptr1 = SharedPtr<int>(new int(5));
    {
        std::cout << "ptr1 count: " << ptr1.use_count() << std::endl;
        SharedPtr<int> ptr2 = ptr1;
        std::cout << "ptr1 count: " << ptr1.use_count() << std::endl;
        std::cout << "ptr2 count: " << ptr2.use_count() << std::endl;
    }

    std::cout << "ptr1 count: " << ptr1.use_count() << std::endl;

    return 0;
}