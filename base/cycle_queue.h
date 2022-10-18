#ifndef _CYCLE_QUEUE_H_
#define _CYCLE_QUEUE_H_

#include <array>
#include <assert.h>
#include <iostream>

namespace common_cplus
{
    template <typename T>
    class CCycleQueue {
    public:
        // 构造函数
        CCycleQueue(int size = 1000)
        {
            assert(10000 > size);
            m_nSize = size;
            w = 0;
            r = 0;
        }

        bool empty(void)
        {
            return w == r;
        }

        int size(void)
        {
            if (w < r)
            {
                return w + m_nSize - r;
            }
            else
            {
                return w - r;
            }
        }

        T pop(void)
        {
            while (r == w);
            int tmpR = r;
            r = (r + 1) % m_nSize;
            return m_array[tmpR];
        }

        bool try_pop(T& a)
        {
            if (r != w)
            {
                a = m_array[r];
                r = (r + 1) % m_nSize;
                return true;
            }
            return false;
        }

        void push(const T& a)
        {
            while ((w + 1) % m_nSize == r);
            m_array[w] = a;
            w = (w + 1) % m_nSize;
        }

        bool try_push(const T& a)
        {
            if ((w + 1) % m_nSize != r)
            {
                m_array[w] = a;
                w = (w + 1) % m_nSize;
                return true;
            }
            else
            {
                return false;
            }
        }

    private:
        std::array<T, 10000> m_array;  // 最大容量是10000
        int r; // r == w 表示空, (w + 1) % size == r 表示满了
        int w;
        int m_nSize;
    };
}
#endif
