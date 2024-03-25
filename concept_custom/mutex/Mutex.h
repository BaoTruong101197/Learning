#include <iostream>
#include <mutex>
#include <pthread.h>

class Mutex {
private: 
    pthread_mutex_t mMutex;
public:
    Mutex() {
        pthread_mutex_init(&mMutex, NULL);
    }

    ~Mutex() {
        pthread_mutex_destroy(&mMutex);
    }

    Mutex(const Mutex& other) = delete;
    Mutex& operator=(const Mutex& other) = delete;
    Mutex(Mutex&& other) = delete;
    Mutex& operator=(Mutex&& other) = delete;

    void lock()
    {
        pthread_mutex_lock(&mMutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&mMutex);
    }

    bool try_lock()
    {
        return pthread_mutex_trylock(&mMutex) == 0;
    }
};