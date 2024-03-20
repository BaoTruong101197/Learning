#include <iostream>
#include "customs/WeakPtr.h"
#include <memory>

int main()
{      
    WeakPtr<int> ptr;
    {
        SharedPtr<int> ptr1 = SharedPtr<int>(new int(5));
        ptr = ptr1;
        SharedPtr<int> ptr2 = ptr1;

        std::cout << "count of ptr: " << ptr.use_count() << std::endl;
        std::cout << "expired of ptr: " << ptr.expired() << std::endl;
        {
            SharedPtr<int> temp = ptr.lock();
        }
        std::cout << "out scope of temp" << std::endl;

        if (ptr.lock() == nullptr)
        {
            std::cout << "ptr is nullptr" << std::endl;
        }
        else 
        {
            std::cout << *ptr.lock() << std::endl;
            std::cout << "count of ptr: " << ptr.use_count() << std::endl;
        }
    }
    std::cout << "out scope of shared ptr" << std::endl;
    if (ptr.lock() == nullptr)
    {
        std::cout << "ptr is nullptr" << std::endl;
    }
    else 
    {
        std::cout << *ptr.lock() << std::endl;
        std::cout << "count of ptr: " << ptr.use_count() << std::endl;
    }
    std::cout << "count of ptr: " << ptr.use_count() << std::endl;
    std::cout << "expired of ptr: " << ptr.expired() << std::endl;
    return 0;
}