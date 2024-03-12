#include <iostream>

template <typename T>
class SharedPtr {
public:
    SharedPtr(T* ptr = nullptr) : mRawPtr(ptr)
    {
    }

    SharedPtr(const SharedPtr<T>& other) 
    {
        mRawPtr = other.mRawPtr;
        mCount = other.mCount;
        ++mCount;
    }

    SharedPtr(SharedPtr<T>&& other) noexcept
    {
        mRawPtr = other.mRawPtr;
        mCount = other.mCount;
        other.mRawPtr = nullptr;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept
    {
        mRawPtr = other.mRawPtr;
        mCount = other.mCount;
        other.mRawPtr = nullptr;
        return *this;
    }

    ~SharedPtr()
    {
        --mCount;
        if (mCount == 0)
        {
            delete mRawPtr;
        }
    }

    int use_count() const
    {
        return mCount;
    }

    void reset() 
    {
        --mCount;
        if (mCount == 0)
        {
            delete mRawPtr;
        }
    }

    T* get() const
    {
        return mRawPtr;
    }

    T* operator->() const
    {
        return mRawPtr;
    }

    T& operator*() const
    {
        return *mRawPtr;
    }

private:
    T* mRawPtr;
    static int mCount;
};

template <typename T>
int SharedPtr<T>::mCount = 1;