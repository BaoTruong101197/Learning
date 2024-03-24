#include <iostream>
#include <pthread.h>
#include <functional>

class Thread {
private:
    pthread_t mThreadId;
    bool mIsJoinable;

    static void* createFunction(void* args)
    {
        if (args == nullptr)
            throw std::invalid_argument("Null function pointer");
        
        std::function<void()> *func = reinterpret_cast<std::function<void()>*>(args);
        (*func)();
        delete func;
        return nullptr;
    }

public:
    Thread() : mIsJoinable(false)
    {
    }

    template <typename Function, typename ...Args>
    explicit Thread(Function&& func, Args&&... args) : mIsJoinable(true)
    {
        auto threadFunc = std::bind(std::forward<Function>(func), std::forward<Args>(args)...);
        auto* funcPtr = new std::function<void()>(threadFunc);
        int ret = pthread_create(&mThreadId, nullptr, &Thread::createFunction, funcPtr);
        if (ret != 0)
            throw std::runtime_error("Fail to create thread");
    }

    Thread(const Thread& other) = delete;
    Thread& operator=(const Thread& other) = delete;

    ~Thread()
    {
        if (mIsJoinable)
        {
            std::terminate();
        }
    }

    bool joinable() const
    {
        return mIsJoinable;
    }

    void join() {
        if (!mIsJoinable) {
            throw std::logic_error("Thread is not joinable");
        }
        pthread_join(mThreadId, nullptr);
        mIsJoinable = false;
    }

    void detach() {
        if (!mIsJoinable) {
            throw std::logic_error("Thread is not joinable");
        }
        pthread_detach(mThreadId);
        mIsJoinable = false;
    }
};