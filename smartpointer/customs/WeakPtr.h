#include "SharedPtr.h"

template <typename T>
class WeakPtr {
private: 
    T* mRawPtr;
    int* mRefCount;

public: 
    WeakPtr() 
    {
        mRawPtr = nullptr;
        mRefCount = nullptr;    
    }

    WeakPtr(const SharedPtr<T>& ptr)
    {
        mRawPtr = ptr.get();
        mRefCount = ptr.mRefCount;
    }

    WeakPtr<T>& operator=(const SharedPtr<T>& ptr)
    {
        mRawPtr = ptr.get();
        mRefCount = ptr.mRefCount;

        return *this;
    }

    WeakPtr(WeakPtr<T>&& ptr)
    {
        mRawPtr = std::move(ptr.mRawPtr);
        mRefCount = std::move(ptr.mRefCount);
    }

    WeakPtr<T>& operator=(WeakPtr<T>&& ptr)
    {
        if (this != &ptr)
        {
            delete mRawPtr;
            delete mRefCount;
            mRawPtr = std::move(ptr.mRawPtr);
            mRefCount = std::move(ptr.mRefCount);
        }

        return *this;
    }

    int use_count() const
    {
        return (mRefCount != nullptr) ? *mRefCount : 0;
    }

    bool expired() const
    {
        return use_count() == 0;
    }

    SharedPtr<T> lock() const
    {
        if (expired())
        {
            return SharedPtr<T>(nullptr);
        }
        else 
        {
            SharedPtr<T> ptr = SharedPtr<T>(new T(*mRawPtr));
            ptr.mRefCount = new int(*mRefCount);
            return ptr;
        }
    }


};