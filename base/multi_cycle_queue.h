#ifndef _MULTI_CYCLE_QUEUE_H_
#define _MULTI_CYCLE_QUEUE_H_

#include <array>
#include <assert.h>
#include "cycle_queue.h"
#include "spin_lock.h"

#include <iostream>

namespace common_cplus
{
    template <typename T>
    struct CQueueItem
    {
        long long id;
        CCycleQueue<T> item;
    };

    template <typename T>
    class CMultiCycleQueue {
    public:
        // 构造函数
        CMultiCycleQueue(int nSize = 100) // 线程数
        {
           qItem = new CQueueItem<T>[nSize] {};
           m_index = 0;
        }

        ~CMultiCycleQueue(void)
        {
            delete []qItem;
        }

        T pop(void)
        {
            while (true)
            {
                for (int i = 0; i < m_index; ++i)
                {
                    if (!qItem[i].item.empty())
                    {
                        return qItem[i].item.pop();
                    }
                }
            }
        }

        bool empty()
        {
            for (int i = 0; i < m_index; ++i)
            {
                if (!qItem[i].item.empty())
                {
                    return false;
                }
            }
            return true;
        }

        
        int size()
        {
            int n = 0;
            for (int i = 0; i < m_index; ++i)
            {
                if (!qItem[i].item.empty())
                {
                    n += qItem[i].item.size();
                }
            }
            return n;
        }

        bool try_pop(T& a)
        {
            for (int i = 0; i < m_index; ++i)
            {
                if (!qItem[i].item.empty())
                {
                    return qItem[i].item.try_pop(a);
                }
            }
            return false;
        }

        T pop(long long& id)
        {
            while (true)
            {
                for (int i = 0; i < m_index; ++i)
                {
                    if (!qItem[i].item.empty())
                    {
                        id = qItem[i].id;
                        return qItem[i].item.pop();
                    }
                }
            }
        }

        void pop(T& a)
        {
            for (int i = 0; i < m_index; ++i)
            {
                if (!qItem[i].empty())
                {
                    qItem[i].item.pop(a);
                }
            }
        }

        bool push(const long long& id, const T& a)
        {
            for (int i = 0; i < m_index; ++i)
            {
                if (qItem[i].id == id)
                {
                    qItem[i].item.push(a);
                    return true;
                }
            }
            auto_lock lock(&m_lock); // 这里要加锁，避免多个线程同时创建
            qItem[m_index].id = id;
            qItem[m_index].item.push(a);
            m_index = m_index + 1;
            return true;
        }

        bool try_push(const long long& id, const T& a)
        {
            for (int i = 0; i < m_index; ++i)
            {
                if (qItem[i].id == id)
                {
                    return qItem[i].item.try_push(a);
                }
            }
            auto_lock lock(&m_lock); // 这里要加锁，避免多个线程同时创建
            qItem[m_index].id = id;
            qItem[m_index].item.push(a);
            m_index = m_index + 1;
            return true;
        }

    private:
        int m_index;
        CQueueItem<T>* qItem;
        spin_lock m_lock;
    };
}
#endif
