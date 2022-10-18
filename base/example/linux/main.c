#define GLOBE_TEST


#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include "check_spin_lock.c"
#include "check_spin_vector.c"
#include "check_spin_queue.c"
#include "check_cycle_queue.c"
#include "check_multi_cycle_queue.c"
#include "check_fast_queue_log.c"
#include "check_spin_lock_log.c"

common_cplus::fast_queue_log* common_cplus::fast_queue_log::instance;
common_cplus::spin_lock_log* common_cplus::spin_lock_log::instance;

int main()
{
    std::cout  << "check_spin_lock: " << check_spin_lock::check_spin_lock() << std::endl;
    std::cout  << "check_spin_vector: " << check_spin_vector::check_spin_vector() << std::endl;
    std::cout  << "check_spin_queue: " << check_spin_queue::check_spin_queue() << std::endl;
    std::cout  << "check_cycle_queue: " << check_cycle_queue::check_cycle_queue() << std::endl;
    std::cout  << "check_multi_cycle_queue: " << check_multi_cycle_queue::check_multi_cycle_queue() << std::endl;

    common_cplus::fast_queue_log::init("test_log");
    std::cout  << "check_fast_queue_log: " << check_fast_queue_log::check_fast_queue_log() << std::endl;

    common_cplus::spin_lock_log::init("test_log_");
    std::cout  << "check_spin_lock_log: " << check_spin_lock_log::check_spin_lock_log() << std::endl;
    return 0;
}

