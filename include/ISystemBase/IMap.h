#pragma once

/*
	 The IMap class is a template class that provides a red-black-tree-based dictionary.
	 It stores (key, value) pairs and provides fast lookup of the value associated with a key.
	 Here's an example QMap with QString keys and int values:
	 
	   IMap<IString, int> map;
	 
	 To insert a (key, value) pair into the map, you can use operator[]():
	 
	   map["one"] = 1;
	   map["three"] = 3;
	   map["seven"] = 7;
 */
#include "IList.h"

namespace IObject
{
	namespace ISystemBase
	{
		/*
		 *	IMapNode
		 *	
		 *
		 */
		template <class Key, class T>
		class IMapNode
		{
		public:
			inline IMapNode(const Key &key, const T &val);
			~IMapNode();

			inline IMapNode *nextNode(){return next;}
			inline IMapNode *prevNode(){return prev;}
			inline void setValue(const T &val){_value = val;}
			inline Key&	key() {return _key;}
			inline T&	value() {return _value;}
		private:
			IMapNode *next;
			IMapNode *prev;

			Key	_key;
			T	_value;
		};

		template <class Key, class T>
		inline IMapNode<Key, T>::IMapNode(const Key &key, const T &val) : 
			_key(key),
			_value(val)
		{
			next = NULL;
			prev = NULL;
		}
		template <class Key, class T>
		IMapNode<Key, T>::~IMapNode()
		{
		}

		template <class Key, class T>
		class IMap
		{
		public:
			typedef IMapNode<Key, T>	Node;

			IMap();
			IMap(const IMap &map);
			~IMap();

			void clear();
			int  size()	const;
			int	count()	const;

			T value(const Key &key);
			void insert(const Key &key, const T &val);
			void append(const Key &key, const T &val);

			bool contains(const Key &key) const;
			void remove(const Key &key);

			T &operator[](const Key &key);
			IMap<Key, T> &operator=(const IMap<Key, T> &map);
			bool operator==(const IMap<Key, T> &map);
		private:
			IList<Node *> _pNodeList;
			inline Node *findNode(const Key &key) const
			{
				Node *nodeT = NULL;
				for(int i=0;i<_pNodeList.size();i++)
				{
					Node *node = _pNodeList.at(i);
					if(node->key() == key)
					{
						nodeT = node;
						break;
					}
				}
				return nodeT;
			}
			inline int getNodePos(const Key &key) const
			{
				int pos = -1;
				for(int i=0;i<_pNodeList.size();i++)
				{
					Node *node = _pNodeList.at(i);
					if(node->key() == key)
					{
						pos = i;
						break;
					}
				}
				return pos;
			}
		};

		template <class Key, class T>
		IMap<Key, T>::IMap()
		{

		}

		template <class Key, class T>
		IMap<Key, T>::IMap(const IMap &map)
		{
			
		}

		template <class Key, class T>
		IMap<Key, T>::~IMap()
		{
			clear();
		}

		template <class Key, class T>
		void IMap<Key, T>::clear()
		{
			if(_pNodeList.size() > 0)
			{
				_pNodeList.clear();
			}
		}

		template <class Key, class T>
		int IMap<Key, T>::size()	const
		{
			return _pNodeList.size();
		}

		template <class Key, class T>
		int IMap<Key, T>::count()	const
		{
			return _pNodeList.size();
		}

		template <class Key, class T>
		void IMap<Key, T>::append(const Key &key, const T &val)
		{
			Node *node = new Node(key, val);
			_pNodeList.append(node);
		}

		template <class Key, class T>
		void IMap<Key, T>::insert(const Key &key, const T &val)
		{
			for(int i=0;i<_pNodeList.size();i++)
			{
				Node *node = _pNodeList.at(i);
				if(node->key() == key)
				{
					node->setValue(val);
					return;
				}
			}
			append(key, val);
		}

		template <class Key, class T>
		T IMap<Key, T>::value(const Key &key)
		{
			for(int i=0;i<_pNodeList.size();i++)
			{
				Node *node = _pNodeList.at(i);
				if(node->key() == key)
					return node->value();
			}
			return static_cast<T>(0);
		}

		template <class Key, class T>
		bool IMap<Key, T>::contains(const Key &key) const
		{
			if(getNodePos(key) < 0)
				return false;
			return true;
		}

		template <class Key, class T>
		void IMap<Key, T>::remove(const Key &key)
		{
			_pNodeList.remove(getNodePos(key));
		}

		template <class Key, class T>
		T &IMap<Key, T>::operator[](const Key &key)
		{
			return value(key);
		}

		template <class Key, class T>
		IMap<Key, T> &IMap<Key, T>::operator=(const IMap<Key, T> &map)
		{
			_pNodeList.clear();
			for(int i=0; i<map.size();i++)
			{
				Node *node = map.at(i);
				_pNodeList.append(node);
			}
			return *this;
		}

		template <class Key, class T>
		bool IMap<Key, T>::operator==(const IMap<Key, T> &map)
		{
			if(this->size() != map.size())
				return false;
			for(int i=0; i<map.size();i++)
			{
				Node *node = map.at(i);
				if(node != _pNodeList.at(i))
					return false;
			}

			return true;
		}
	}
}
