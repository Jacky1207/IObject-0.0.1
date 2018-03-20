#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/*
 *						IVector
 * 	this class is a vector. it will alloc fixation size, 
 *	if data size is lager then it, it will resize.
 *
 *  vector is faster then list in read datas.
 *
 */
namespace IObject
{
	namespace ISystemBase
	{
		#define 	MAX_VECTOR		10
		
		template<class T>
		class IVector
		{
		public:
			IVector();
			~IVector();
			
			//return size of list.
			int size();
			//push item
			void append(const T &value);
			void append(const IVector<T> &value);
			void prepend(const T &value);
			void prepend(const IVector<T> &value);
			void insert(int i, const T &value);
			void replace(int i, const T &value);

			void clear();
			void erase(int pos);
			void remove(int pos);
			
			//return item at index
			const T at(int index);
			T first();
			
			T last();
			bool isEmpty();
			
			//operators
			bool 		 operator!=(const IVector<T> &other) const;
			bool 		 operator==(const IVector<T> &other) const;
			IVector<T> 	 &operator+(const IVector<T> &other) const;
			IVector<T>   &operator+=(const IVector<T> &other);
			IVector<T> 	 &operator+=(const T &value);
			IVector<T>   &operator<<(const IVector<T> &other);
			IVector<T>   &operator<<(const T &value);
			IVector<T>   &operator=(const IVector<T> &other);
			T 			 &operator[](int i);
			const T      &operator[](int i) const;
		private:
			unsigned int _size;
			unsigned int _totalSize;
			unsigned int _index;
			T *_pVector;
			
			void resizeVector()
			{
				_totalSize += MAX_VECTOR;
				T *p = new T[_totalSize];
				if(p == NULL)
				{
					perror("mollac fail");
					return;
				}
				/*here can't use memcpy for copy data.
				*
				*	memcpy(p, _pVector, _size * sizeof(T));
				*/
				for(int i=0;i<_size;i++)
				{
					p[i] = _pVector[i];
				}
				
				delete [] _pVector;
				_pVector = p;
			}
		};

		/************************************************************************************/
		template<class T> IVector<T>::IVector() : 
			_totalSize(0),
			_pVector(NULL)
		{
			_size = 0;
			_pVector = new T[MAX_VECTOR];
			_totalSize += MAX_VECTOR;
		}

		template<class T> IVector<T>::~IVector()
		{
			delete [] _pVector;
			_pVector = NULL;
		}

		template<class T> int IVector<T>::size()
		{
			return _size;
		}
		
		template<class T> const T IVector<T>::at(int index)
		{
			return _pVector[index];
		}
		
		template<class T> T IVector<T>::first()
		{
			return this->at(0);
		}
			
		template<class T> T IVector<T>::last()
		{
			return this->at(_size - 1);
		}

		template<class T> bool IVector<T>::isEmpty()
		{
			if(_size == 0)
				return true;
			else
				return false;
		}
		
		/*
		 *	push item into vector
		 *	and resize the vector when its oversize
		 */
		template<class T> void IVector<T>::append(const T &value)
		{
			if(_size + 1 > _totalSize)
				resizeVector();
			_pVector[_size] = value;
			_size++;
		}
		
		template<class T> void IVector<T>::append(const IVector<T> &value)
		{
			for(int i=0; i< value.size(); i++)
			{
				append(value.at(i));
			}
		}
		
		template<class T> void IVector<T>::prepend(const T &value)
		{
			insert(0, value);
		}
		
		template<class T> void IVector<T>::prepend(const IVector<T> &value)
		{
			for(int i=value.size()-1; i>0; i--)
			{
				prepend(value.at(i));
			}
		}
		
		template<class T> void IVector<T>::insert(int i, const T &value)
		{
			if(_size + 1 > _totalSize)
				resizeVector();
			
			for(int n= size(); n > i; n--)
			{
				_pVector[n] = _pVector[n-1];
			}
			_pVector[i] = value;
			
			_size ++;
		}

		template<class T> void IVector<T>::replace(int i, const T &value)
		{
			_pVector[i] = value;
		}
		
		template<class T> void IVector<T>::clear()
		{
			_size = 0;
		}
		
		template<class T> void IVector<T>::erase(int pos)
		{
			//memmove(_pVector+pos, _pVector+pos+1, (size()-1-pos) * sizeof(T));
			for(int n = pos; n<size()-1; n++)
			{
				_pVector[n] = _pVector[n+1];
			}
			_size --;
		}
		
		template<class T> void IVector<T>::remove(int pos)
		{
			for(int n = pos; n<size()-1; n++)
			{
				_pVector[n] = _pVector[n+1];
			}
			_size --;
		}		
		
		template<class T> bool 		 	IVector<T>::operator!=(const IVector<T> &other) const
		{
			if(size() != other.size())
				return true;

			for(int i=0; i<size(); i++)
			{
				if(at(i) != other.at(i))
				{
					return true;
				}
			}

			return false;
		}
		
		template<class T> bool 		 	IVector<T>::operator==(const IVector<T> &other) const
		{
			return !operator!=(other);
		}
		
		template<class T> IVector<T>   &IVector<T>::operator+(const IVector<T> &other) const
		{
			this->append(other);
			return *this;
		}
		
		template<class T> IVector<T>   &IVector<T>::operator+=(const IVector<T> &other)
		{
			return operator+(other);
		}
		template<class T> IVector<T>   &IVector<T>::operator+=(const T &value)
		{
			this->append(value);
			return *this;
		}
		
		template<class T> IVector<T>   &IVector<T>::operator<<(const IVector<T> &other)
		{
			return operator+(other);
		}
		
		template<class T> IVector<T>   &IVector<T>::operator<<(const T &value)
		{
			return operator+=(value);
		}
		
		template<class T> IVector<T>   &IVector<T>::operator=(const IVector<T> &other)
		{
			this->clear();
			for(int i=0; i<other.size(); i++)
			{
				append(other.at(i));
			}
			
			_size = other.size();
		}
		
		template<class T> T 		   &IVector<T>::operator[](int i)
		{
			return this->at(i);
		}
		
		template<class T> const T      &IVector<T>::operator[](int i) const
		{
			return this->at(i);
		}
	}
}
