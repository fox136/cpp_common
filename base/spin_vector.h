#ifndef __TERRA_SPIN_VECTOR__
#define __TERRA_SPIN_VECTOR__

#include <queue>
#include "spin_lock.h"


namespace common_cplus
{

	template<typename T>
	class spin_vector
	{
	public:
		typedef typename std::vector<T>	vector_t;
		typedef typename vector_t::value_type		value_type;
		typedef typename vector_t::reference		reference;
		typedef typename vector_t::const_reference	const_reference;
		typedef typename vector_t::size_type		size_type;
		typedef typename vector_t::iterator			iterator;
		typedef typename vector_t::const_iterator	const_iterator;

	protected:
		vector_t m_vector;
		spin_lock m_lock;
		
	public:
		bool empty()
		{
			auto_lock lock(&m_lock);
			return m_vector.empty();
		}

		reference operator[](size_type pos)
		{
			auto_lock lock(&m_lock);
			return m_vector[pos];
		}

		void push_back(const T& value)
		{
			auto_lock lock(&m_lock);
			m_vector.push_back(value);
		}

		const T pop_back()
		{
			auto_lock lock(&m_lock);
			return m_vector.pop_back();
		}

		bool try_pop_back(T& value)
		{
			auto_lock lock(&m_lock);
			if (m_vector.size() > 0)
			{
				value = m_vector.back();
				m_vector.pop_back();
				return true;
			}
			return false;
		}

		const_iterator begin() const
		{
            // Export iterator is vulnerable.
            // Iterator may be invalidated by other thread. 
			return m_vector.begin();
		}

		const_iterator end() const
		{
            // Export iterator is vulnerable.
            // Iterator may be invalidated by other thread. 
			return m_vector.end();
		}

	};
}

#endif // __SPIN_VECTOR__

