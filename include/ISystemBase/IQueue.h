#ifndef IQUEUE_H
#define IQUEUE_H

namespace IObject
{
	namespace ISystemBase
	{
		template <class T>
		class IQueue
		{
		public:
			IQueue(int max = 0);
			~IQueue();
			
			void push(const T &value);
			T pop();
			
			bool isEmpty() const;
			int size() const;
			
			void clear();
		private:
		#define DEFAULT_MAX		128
			int m_nSize;
			T *m_pQueue;
			
			//index
			int m_nIndex;
		};
	}
}

#endif