#ifndef __SPIN_LOCK_RAII__
#define __SPIN_LOCK_RAII__

#ifdef Linux
#include <pthread.h>
#else
#include <mutex>
#endif

namespace common_cplus {

#ifdef Linux
    class spin_lock
    {
    public:
        spin_lock()
        {
            pthread_spin_init(&_lock, PTHREAD_PROCESS_PRIVATE);
        }
        void lock()
        {
            pthread_spin_lock(&_lock);
        }
        void unlock()
        {
            pthread_spin_unlock(&_lock);
        }
    private:
        pthread_spinlock_t  _lock;
    };

#else
    /* Has not tuned performance on Windows.
     */
    class spin_lock
    {
    public:
        spin_lock()
        {}
        void lock()
        {
            _mutex.lock();
        }
        void unlock()
        {
            _mutex.unlock();
        }
    private:
        std::mutex _mutex;
    };        
#endif

    class auto_lock
    {
    public:
        auto_lock(spin_lock * lock) 
        {
            _lock = lock;
            _lock->lock();
        }

        ~auto_lock()
        {
            _lock->unlock();
        }
    private:
        spin_lock * _lock;
    };


}





#endif
