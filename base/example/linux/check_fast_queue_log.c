#include "../../fast_queue_log.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

namespace check_fast_queue_log
{
    static int i = 0;
    static int i2 = 0;

    const static int NUM = 5000000;
    static common_cplus::CMultiCycleQueue<int> que;
    
    
        void thread_push() {
            while(1) {
                if (i > NUM)
                {
                    return;
                }
                common_cplus::fast_queue_log::debug("test_log");
                ++i;
            }
        }

        void thread_push2() {
            while(1) {
                if (i2 > NUM)
                {
                    return;
                }
                common_cplus::fast_queue_log::debug("test_log");
                ++i2;
            }
        }
    
        void f1()
        {
            std::vector<std::thread*> vecThread;
            auto obj = new std::thread(thread_push);
            vecThread.push_back(obj);
            auto obj3 = new std::thread(thread_push2);
            vecThread.push_back(obj3);
     
            for (auto it = vecThread.begin(); it != vecThread.end(); ++it)
            {
                //(*it)->detach();
                (*it)->join();
            }
        }


    int check_fast_queue_log()
    {
            std::time_t seconds_since_epoch = std::time(nullptr);
        	f1();
            return std::time(nullptr) - seconds_since_epoch;
    }
}


#ifndef GLOBE_TEST
common_cplus::fast_queue_log* common_cplus::fast_queue_log::instance;
int main()
{
    common_cplus::fast_queue_log::init("test_log");
    std::cout  << check_fast_queue_log::check_fast_queue_log() << std::endl;
    common_cplus::fast_queue_log::debug("test_log main");
    common_cplus::fast_queue_log::debug("test_log main %s,%d", "yuan", 100);
    common_cplus::fast_queue_log::debug("test_log main %s", "wei");
    common_cplus::fast_queue_log::debug("test_log main %d", 123456);

    common_cplus::fast_queue_log::warn("test_log main");
    common_cplus::fast_queue_log::warn("test_log main %s,%d", "yuan", 100);
    common_cplus::fast_queue_log::warn("test_log main %s", "wei");
    common_cplus::fast_queue_log::warn("test_log main %d", 123456);

    common_cplus::fast_queue_log::error("test_log main");
    common_cplus::fast_queue_log::error("test_log main %s,%d", "yuan", 100);
    common_cplus::fast_queue_log::error("test_log main %s", "wei");
    common_cplus::fast_queue_log::error("test_log main %d", 123456);
    return 0;
}
#endif

