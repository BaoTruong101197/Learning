#include <iostream>
#include <memory>

struct RefCount {
    bool weak_ref = false;
    int* count;
};

template <typename T>
class WeakPtr;
template <typename T>
class SharedPtr {
private: 
    T* mRawPtr;
    RefCount* mRefCount;
public: 
    friend class WeakPtr<T>;
    
    SharedPtr(T* ptr = nullptr) : mRawPtr(ptr)
    {
        mRefCount = new RefCount();
        mRefCount->count = new int(1);
        std::cout << "create a new count with reference: " << mRefCount->count << std::endl;
        mRefCount->weak_ref = false;
    }

    SharedPtr(const SharedPtr<T>& other)
    {
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        (*mRefCount->count)++;
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other)
    {
        if (mRawPtr != nullptr)
        {
            std::cout << "delete raw pointer before: " << mRefCount->count << std::endl;
            delete mRawPtr;
            delete mRefCount->count;
            delete mRefCount;
        }
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        (*mRefCount->count)++;
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
        if (mRawPtr != nullptr)
        {
            std::cout << "delete raw pointer before: " << mRefCount->count << std::endl;
            delete mRawPtr;
            delete mRefCount->count;
            delete mRefCount;
        }
        mRawPtr = other.mRawPtr;
        mRefCount = other.mRefCount;
        other.mRawPtr = nullptr;
        return *this;
    }

    ~SharedPtr()
    {
        std::cout << "Destructor SharedPtr weak_ref: " << mRefCount->weak_ref << std::endl;
        std::cout << "Destructor SharedPtr count: " << *mRefCount->count << std::endl;
        if (--(*mRefCount->count) == 0)
        {
            delete mRawPtr;
            mRawPtr = nullptr;

            if (mRefCount->weak_ref == false)
            {
                std::cout << "Delete count in Shared_ptr " << mRefCount->count << std::endl;
                delete mRefCount->count;
                mRefCount->count = nullptr;
                delete mRefCount;
                mRefCount = nullptr;
            }
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

    bool operator==(std::nullptr_t) const
    {
        return this->mRawPtr == nullptr;
    }

    T* get() const
    {
        return mRawPtr;
    }

    int use_count() const
    {
        return (*mRefCount->count);
    }
};
