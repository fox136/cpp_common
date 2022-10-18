#include "../../spin_lock.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>

namespace check_spin_lock
{
    static int i = 0;

    const static int NUM = 10000;
    static common_cplus::spin_lock lock;

    void thread_print_func() {
        while(1) {
            auto l = common_cplus::auto_lock(&lock);
            if (i >= NUM)
            {
                return;
            }
            ++i;
#ifndef GLOBE_TEST

            std::cout << "this is thread print func!" << i << std::endl;
#endif
        }
    }

    void f1()
    {
        std::vector<std::shared_ptr<std::thread>> vecThread;
        for (int i = 0; i < 5; ++i)
        {
            auto obj = std::shared_ptr<std::thread>(new std::thread(thread_print_func));
            vecThread.push_back(obj);
        }
        for (auto it = vecThread.begin(); it != vecThread.end(); ++it)
        {
            (*it)->join();
        }
    }


    bool check_spin_lock()
    {
        	f1();
            return i == NUM;
    }
}

#ifndef GLOBE_TEST
int main()
{
    std::cout  << check_spin_lock::check_spin_lock() << std::endl;
    return 0;
}
#endif
