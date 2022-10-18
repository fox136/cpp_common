#include "../../common_time.h"
#include <thread>
#include <iostream>
#include <vector>
#include <memory>

namespace check_common_time
{
    bool check_common_time()
    {
#ifndef GLOBE_TEST
        std::cout << common_cplus::GetSysTimeMicros() <<std::endl;
        std::cout << common_cplus::get_datetime_by_sec() <<std::endl;
        std::cout << common_cplus::get_datetime_by_msec() <<std::endl;
        std::cout << common_cplus::get_datetime_by_usec() <<std::endl;
#endif
        return true;
    }
}

#ifndef GLOBE_TEST
int main()
{
    std::cout  << check_common_time::check_common_time() << std::endl;
    return 0;
}
#endif
