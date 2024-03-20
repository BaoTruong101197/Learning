#include "SharedPtr.h"

template <typename T>
class WeakPtr {
private: 
    T* mRawPtr;
    RefCount* mRefCount;

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
        mRefCount->weak_ref = true;
    }

    WeakPtr<T>& operator=(const SharedPtr<T>& ptr)
    {
        mRawPtr = ptr.get();
        mRefCount = ptr.mRefCount;
        mRefCount->weak_ref = true;

        return *this;
    }

    WeakPtr(WeakPtr<T>&& ptr)
    {
        mRawPtr = std::move(ptr.mRawPtr);
        mRefCount = std::move(ptr.mRefCount);
    }

    ~WeakPtr()
    {
        std::cout << "Destructor WeakPtr weak_ref: " << mRefCount->weak_ref << std::endl;
        std::cout << "Destructor WeakPtr count: " << *mRefCount->count << std::endl;
        if (mRefCount->weak_ref && *mRefCount->count == 0)
        {
            std::cout << "Delete count in WeakPtr " << mRefCount->count << std::endl;
            delete mRefCount->count;
            mRefCount->count = nullptr;
            delete mRefCount;
            mRefCount = nullptr;
        }
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
        return *mRefCount->count;
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
            return SharedPtr<T>(new T(*mRawPtr));
        }
    }
};