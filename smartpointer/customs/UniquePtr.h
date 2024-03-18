#include <iostream>

template<typename T>
class UniquePtr {
private:
    T* mRawPtr;
public: 
    UniquePtr(T* ptr = nullptr) : mRawPtr(ptr) 
    {
    }

    // Copy constructor is deleted
    UniquePtr(const UniquePtr<T>& unique) = delete;
    UniquePtr<T> operator=(const UniquePtr<T>& unique) = delete;

    UniquePtr(UniquePtr<T>&& unique) noexcept
    {
        mRawPtr = unique.mRawPtr;
        unique.mRawPtr = nullptr;
    }

    UniquePtr<T>& operator=(UniquePtr<T>&& unique) noexcept
    {
        if (this != &unique)
        {
            delete mRawPtr;
            mRawPtr = unique.mRawPtr;
            unique.mRawPtr = nullptr;
        }
        return *this;
    }

    ~UniquePtr()
    {
        delete mRawPtr;
        mRawPtr = nullptr;
    }

    T& operator*()
    {
        return *mRawPtr;
    }

    T* operator->()
    {
        return mRawPtr;
    }
};