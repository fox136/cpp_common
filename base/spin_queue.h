#ifndef __SPIN_QUEUE__
#define __SPIN_QUEUE__

#include <queue>
#include "spin_lock.h"


namespace common_cplus
{
	template<typename T, typename Container = std::deque<T>	>
	class spin_queue
	{
	public:
		typedef typename std::queue<T, Container>	queue_t;
		typedef typename queue_t::value_type		value_type;
		typedef typename queue_t::reference			reference;
		typedef typename queue_t::const_reference	const_reference;
		typedef typename queue_t::size_type			size_type;
		typedef typename queue_t::container_type	container_type;

	protected:
		queue_t m_queue;
		spin_lock m_lock;
		
	public:
		bool empty()
		{
			auto_lock lock(&m_lock);
			return m_queue.empty();
		}

		size_type size()
		{
			auto_lock lock(&m_lock);
			return m_queue.size();
		}

		size_type unsafe_size()
		{
			auto_lock lock(&m_lock);
			return m_queue.size();
		}

		void push(const value_type& value)
		{
			auto_lock lock(&m_lock);
			m_queue.push(value);
		}

		bool try_pop(value_type& result)
		{
			auto_lock lock(&m_lock);
			if (!m_queue.empty())
			{
				result = m_queue.front();
				m_queue.pop();
				return true;
			}
			else
				return false;
		}

	};
}

#endif // __SPIN_QUEUE__

