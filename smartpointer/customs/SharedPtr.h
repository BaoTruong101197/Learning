#include <iostream>

template <typename T>
class SharedPtr {
private: 
    T* mRawPtr;
    int* mRefCount;
public: 
    SharedPtr(T* ptr = nullptr) : mRawPtr(ptr)
    {
        mRefCount = new int(1);
    }

    SharedPtr(const SharedPtr<T>& other)
    {
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        (*mRefCount)++;
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        (*mRefCount)++;
        return *this;
    }

    SharedPtr(SharedPtr<T>&& other)
    {
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        other.mRawPtr = nullptr;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& other)
    {
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        other.mRawPtr = nullptr;
        return *this;
    }

    ~SharedPtr()
    {
        if (--(*mRefCount) == 0)
        {
            delete mRawPtr;
            mRawPtr = nullptr;
        }
    }

    void reset()
    {
        if (--(*mRefCount) == 0)
        {
            delete mRawPtr;
            mRawPtr = nullptr;
        }
    }

    T& operator*() const
    {
        return *mRawPtr;
    }

    T* operator->() const
    {
        return mRawPtr;
    }

    T* get() const
    {
        return mRawPtr;
    }

    int use_count() const
    {
        return (*mRefCount);
    }
};