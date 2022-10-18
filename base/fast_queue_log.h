#ifndef __FAST_QUEUE_LOG_H__
#define __FAST_QUEUE_LOG_H__

#include <string>
#include <vector>
#include <unordered_map>
#ifndef __linux__
#include "windows.h"
#else
#include "unistd.h"
#endif
#include <thread>
#include <fstream>
#include <sstream>
#include <stdarg.h>
#include "multi_cycle_queue.h"

// 结论，这样写能比带锁的log速度快10倍左右

namespace common_cplus
{
#ifndef LOG_BUF_LEN
#define LOG_BUF_LEN 1024*10
//#define LOG_BUF_LEN 50
#endif
	class fast_queue_log
	{
	private:        
		static fast_queue_log* instance;
		common_cplus::CMultiCycleQueue<std::string> que;
        std::ofstream outfile;
        int m_iNewFile;
        std::string strLogName;


    private:
        fast_queue_log(void)
        {
            m_iNewFile = 0;
        }

    public:
        void set_strLogName(const std::string& str)
        {
            strLogName = str;
        }
        
    static int write_and_publish(void)
    {
        auto p = getInstance();

        while(1)
        {
            if (p->outfile.tellp() > 64*1024*1024) // log分割文件太小有可能会出现重名文件，若出现旧文件会被覆盖
            {
                p->outfile.close();
			    p->log_open_file(p->strLogName);
            }
            std::string str;
            if(p->que.try_pop(str))
            {
                p->outfile << str << std::endl;
            }
        }

        return 0;
    }

    static void time_thread(void)
    {
        auto p = getInstance();
        auto& outfile = p->outfile;
        while(1)
        {
            //std::time_t seconds_since_epoch = std::time(nullptr);
            sleep(1);
            auto& outfile = getInstance()->outfile;
            if (outfile.is_open())
            {
                outfile.flush();
            }
        }
    }

    
	public:        
		static fast_queue_log* getInstance()
		{
			if (instance == nullptr)
			{
				instance = new fast_queue_log();
			}
			return instance;
		}

		int log_open_file(const std::string& file_name)
		{
			char filepath[256] = {0};
			time_t timestamp;
			struct tm time_fmt;
			time(&timestamp);
			localtime_r(&timestamp, &time_fmt);

			snprintf(filepath, sizeof(filepath), "%s%04d%02d%02d.log-%02d%02d%02d.log",
				file_name.c_str(),
				time_fmt.tm_year + 1900,
				time_fmt.tm_mon + 1,
				time_fmt.tm_mday,
				time_fmt.tm_hour,
				time_fmt.tm_min,
				time_fmt.tm_sec);

            outfile.open(filepath, std::ios::binary | std::ios::app | std::ios::in | std::ios::out);
            
			return 0;
		}


		static int init(const std::string& file_name)
		{
		    getInstance()->strLogName = file_name;
			getInstance()->log_open_file(file_name);
			std::thread write_thread(fast_queue_log::write_and_publish);
            write_thread.detach();
            std::thread t(fast_queue_log::time_thread);
            t.detach();
			return 0;
		}

		void impl(const std::string& level, const char* fmt, va_list list)
		{
            char buf[LOG_BUF_LEN] = {0};
            int len = vsnprintf(buf, LOG_BUF_LEN, fmt, list);
            std::ostringstream   oss;
            oss << std::this_thread::get_id();
            std::string str = oss.str();
            que.push(atoll(str.c_str()), str + " " + level + " " + buf);
		}

		static void debug(const char* fmt, ...)
		{
			va_list ap;
			va_start(ap, fmt);
			getInstance()->impl("D", fmt, ap);
			va_end(ap);
		}

        static void warn(const char* fmt, ...)
		{
			va_list ap;
			va_start(ap, fmt);
			getInstance()->impl("W", fmt, ap);
			va_end(ap);
		}

        static void error(const char* fmt, ...)
		{
			va_list ap;
			va_start(ap, fmt);
			getInstance()->impl("E", fmt, ap);
			va_end(ap);
		}
	};
}

#endif

