#include "../../spin_queue.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>

namespace check_spin_queue
{
    static int i = 0;
    const static int NUM = 100;

    static common_cplus::spin_queue<int> que;


    void thread_push() {
        while(1) {
            if (i > NUM)
            {
                return;
            }
            que.push(i);
            ++i;
        }
    }

    void thread_pop() {
        while(1) {
            int value = 0;
            if (que.try_pop(value))
            {
        #ifndef GLOBE_TEST
                std::cout << "thread_pop:" << value << std::endl;
        #endif
            }
            if (i > NUM && que.empty())
            {
                return;
            }
        }
    }

    void f1()
    {
        std::vector<std::shared_ptr<std::thread>> vecThread;
        auto obj = std::shared_ptr<std::thread>(new std::thread(thread_push));
        vecThread.push_back(obj);
        auto obj2 = std::shared_ptr<std::thread>(new std::thread(thread_pop));
        vecThread.push_back(obj2);
 
        for (auto it = vecThread.begin(); it != vecThread.end(); ++it)
        {
            (*it)->join();
        }
    }


    bool check_spin_queue()
    {
        	f1();
            return que.empty();
    }

}

#ifndef GLOBE_TEST
int main()
{
    std::cout  << check_spin_queue::check_spin_queue() << std::endl;
    return 0;
}
#endif
