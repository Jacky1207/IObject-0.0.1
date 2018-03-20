#include "IQueue.h"

namespace IObject
{
	namespace ISystemBase
	{
		template <class T>
		IQueue<T>::IQueue(int max) :
				m_nSize(0),
				m_nIndex(0)
		{
			int size = max;
			if(max == 0)
				size = DEFAULT_MAX;
			
			m_pQueue = new T(size);
		}
		
		template <class T>
		IQueue<T>::~IQueue()
		{
			delete m_pQueue;
		}
		
		template <class T>
		bool IQueue<T>::isEmpty() const
		{
			if(m_nSize > 0)
				return true;
			else
				return false;
		}
		
		template <class T>
		int IQueue<T>::size() const
		{
			return m_nSize;
		}
		
		template <class T>
		void IQueue<T>::push(const T &value)
		{
			m_pQueue[m_nIndex] = value;
			m_nSize ++;
		}
		
		template <class T>
		T IQueue<T>::pop()
		{
			if(m_nSize <= 0)
				return 0;
			
			//get first item
			T p = m_pQueue[0];
			m_nSize --;
			
			//move other items
			memcpy(m_pQueue, m_pQueue+1, m_nSize);
			m_pQueue[m_nSize] = 0;
			
			return p;
		}
		
		template <class T>
		void IQueue<T>::clear()
		{
			memset(m_pQueue, 0, sizeof(m_nSize));
			m_nSize = 0;
		}
	}
}