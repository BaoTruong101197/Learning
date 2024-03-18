#include <iostream>

template <typename T>
class SharedPtr {
private: 
    T* mRawPtr;
    static int mRefCount;
public: 
    SharedPtr(T* ptr = nullptr) : mRawPtr(ptr)
    {
    }

    SharedPtr(const SharedPtr<T>& other)
    {
        mRawPtr = other.mRawPtr;
        ++mRefCount;
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        mRawPtr = other.mRawPtr;
        ++mRefCount;
        return *this;
    }

    SharedPtr(SharedPtr<T>&& other)
    {
        mRawPtr = other.mRawPtr;
        other.mRawPtr = nullptr;
    }

    SharedPtr<T>& operator=(SharedPtr<T>&& other)
    {
        mRawPtr = other.mRawPtr;
        other.mRawPtr = nullptr;
        return *this;
    }

    ~SharedPtr()
    {
        if (--mRefCount == 0)
        {
            delete mRawPtr;
            mRawPtr = nullptr;
        }
    }

    void reset()
    {
        if (--mRefCount == 0)
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
        return mRefCount;
    }
};

template<typename T>
int SharedPtr<T>::mRefCount = 1;