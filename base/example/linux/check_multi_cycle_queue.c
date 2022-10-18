#include "../../multi_cycle_queue.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

namespace check_multi_cycle_queue
{
    static int i = 0;
    static int i2 = 0;

    const static int NUM = 10;
    static common_cplus::CMultiCycleQueue<int> que;
    
    
        void thread_push() {
            while(1) {
                if (i > NUM)
                {
                    return;
                }
                std::ostringstream   oss;
                oss << std::this_thread::get_id();
                std::string str = oss.str();
                //std::cout << "thread_push:  " << str << std::endl;
                long long id = atoll(str.c_str());
                que.push(id, i);
                ++i;
            }
        }

        void thread_push2() {
            while(1) {
                if (i2 > NUM)
                {
                    return;
                }
                std::ostringstream   oss;
                oss << std::this_thread::get_id();
                std::string str = oss.str();
                //std::cout << "thread_push2: " << str << std::endl;
                long long id = atoll(str.c_str());
                que.push(id, i2);
                ++i2;
            }
        }
    
        void thread_pop() {
            while(1) {
                int value = 0;
                if (que.try_pop(value))
                {
        #ifndef GLOBE_TEST
                    std::cout << "thread_pop:" << value <<std::endl;
        #endif
                }
                if (i > NUM && i2 > NUM && que.empty())
                {
                    return;
                }
            }
        }
    
        void f1()
        {
            std::vector<std::thread*> vecThread;
            auto obj = new std::thread(thread_push);
            vecThread.push_back(obj);
            auto obj3 = new std::thread(thread_push2);
            vecThread.push_back(obj3);
            auto obj2 = new std::thread(thread_pop);
            vecThread.push_back(obj2);
     
            for (auto it = vecThread.begin(); it != vecThread.end(); ++it)
            {
                (*it)->join();
            }
        }


    bool check_multi_cycle_queue()
    {
        	f1();
            return que.empty();
    }
}

#ifndef GLOBE_TEST
int main()
{
    std::cout  << check_multi_cycle_queue::check_multi_cycle_queue() << std::endl;
    return 0;
}
#endif
