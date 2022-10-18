#include "../../spin_vector.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>

namespace check_spin_vector
{
    static int i = 0;
    const static int NUM = 100;

    static common_cplus::spin_vector<int> vec;

    void thread_push_back() {
        while(1) {
            if (i > NUM)
            {
                return;
            }
            vec.push_back(i);
            ++i;
        }
    }

    void thread_pop_back() {
        while(1) {
            int value = 0;
            if (vec.try_pop_back(value))
            {
            #ifndef GLOBE_TEST
                std::cout << "thread_pop:" << value << std::endl;
            #endif
            }
            if (i > NUM && vec.empty())
            {
                return;
            }
        }
    }

    void f1()
    {
        std::vector<std::shared_ptr<std::thread>> vecThread;
        auto obj = std::shared_ptr<std::thread>(new std::thread(thread_push_back));
        vecThread.push_back(obj);
        auto obj2 = std::shared_ptr<std::thread>(new std::thread(thread_pop_back));
        vecThread.push_back(obj2);
 
        for (auto it = vecThread.begin(); it != vecThread.end(); ++it)
        {
            (*it)->join();
        }
    }


    bool check_spin_vector()
    {
        	f1();
            return vec.empty();
    }
}

#ifndef GLOBE_TEST
int main()
{
    std::cout  << check_terra_spin_vector::check_terra_spin_vector() << std::endl;
    std::cout << check_terra_spin_vector::i << " " << check_terra_spin_vector::NUM << std::endl;
    return 0;
}
#endif


