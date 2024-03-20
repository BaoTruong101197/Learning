template <typename T>
class UniquePtr {
private: 
    T* mRawPtr;
public: 
    UniquePtr(T* ptr = nullptr) : mRawPtr(ptr)
    {
    }

    UniquePtr(const UniquePtr<T>& other) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

    UniquePtr(UniquePtr<T>&& other)    
    {
        mRawPtr = other.mRawPtr;
        other.mRawPtr = nullptr;
    }

    UniquePtr<T>& operator=(UniquePtr<T>&& other)
    {
        if (this != &other)
        {
            delete mRawPtr;
            mRawPtr = other.mRawPtr;
            other.mRawPtr = nullptr;
        }

        return *this;
    }

    T* operator->() const
    {
        return mRawPtr;
    }

    T& operator*() const
    {
        return *mRawPtr;
    }

    T* get() const
    {
        return mRawPtr;
    }
};