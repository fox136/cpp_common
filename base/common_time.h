#ifndef __COMMON_TIME_H_
#define __COMMON_TIME_H_

#include <string>

namespace common_cplus
{
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif  // _WIND32

    // 获取系统的当前时间，单位微秒(us)
    long GetSysTimeMicros();

    std::string get_datetime_by_sec(long t = time(0));
    std::string get_datetime_by_msec(long t = GetSysTimeMicros() / 1000);
    std::string get_datetime_by_usec(long t = GetSysTimeMicros());

    // 获取系统的当前时间，单位微秒(us)
    long GetSysTimeMicros()
    {
#ifdef _WIN32
        // 从1601年1月1日0:0:0:000到1970年1月1日0:0:0:000的时间(单位100ns)
#define EPOCHFILETIME   (116444736000000000UL)
        FILETIME ft;
        LARGE_INTEGER li;
        int64_t tt = 0;
        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        // 从1970年1月1日0:0:0:000到现在的微秒数(UTC时间)
        tt = (li.QuadPart - EPOCHFILETIME) / 10;
        return tt;
#else
        timeval tv;
        gettimeofday(&tv, 0);
        return (long)tv.tv_sec * 1000000 + (long)tv.tv_usec;
#endif // _WIN32
        return 0;
    }

    std::string get_datetime_by_sec(long t)
    {
        struct tm* m = localtime((time_t*)&t);
        std::string moon = std::to_string(m->tm_mon + 1);
        if (moon.size() == 1)
        {
            moon = "0" + moon;
        }
        std::string day = std::to_string(m->tm_mday);
        if (day.size() == 1)
        {
            day = '0' + day;
        }
        std::string hour = std::to_string(m->tm_hour);
        if (hour.size() == 1)
        {
            hour = "0" + hour;
        }
        std::string min = std::to_string(m->tm_min);
        if (min.size() == 1)
        {
            min = "0" + min;
        }
        std::string sec = std::to_string(m->tm_sec);
        if (sec.size() == 1)
        {
            sec = "0" + sec;
        }
        std::string str = std::to_string(1900 + m->tm_year) + "-" + moon + "-" + day;
        str += " " + hour + ":" + min + ":" + sec;
        return str;
    }

    std::string get_datetime_by_msec(long t)
    {
        t = t / 1000;
        int ms = t % 1000;
        return get_datetime_by_sec(t) + ":" + std::to_string(ms);
    }

    std::string get_datetime_by_usec(long t)
    {
        t = t / 1000000;
        int us = t % 1000000;
        return get_datetime_by_sec(t) + ":" + std::to_string(us);
    }
}

#endif