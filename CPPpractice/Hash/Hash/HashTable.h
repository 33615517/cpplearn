#pragma once
#include<iostream>
#include<vector>
#include<string>
using namespace std;
enum State
{
	EXIST,
	EMPTY,
	DELETE
};
template<class K,class V>
struct HashData
{
	pair<K, V>_kv;
	State _state = EMPTY;
};
template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};
template<>
struct HashFunc<string>
{
	size_t operator()(const string& s)
	{
		size_t hash = 0;
		for (auto ch : s)
		{
			hash += ch;
		}
		return hash;
	}
};
inline unsigned long __stl_next_prime(unsigned long n)
{
	// Note: assumes long is at least 32 bits.
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] = {
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473, 4294967291
	};
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	const unsigned long* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}
namespace open_adress
{
	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		HashTable()
			:_tables(11)
			, _n(0)
		{
		}
		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;
			//负载因子>=0.7
			if (_tables.empty() || _n * 10 / _tables.size() >= 7)
			{
				//vector<HashData<K, V>>newtables(_tables.size() * 2);
				//for (auto& data : _tables)
				//{
				//	//旧表的数据映射到新表
				//	if (data._state == EXIST)
				//	{
				//		size_t hash0 = data.kv.first % newtables.size();
				//		//...
				//	}
				//}
				//_tables.swap(newtables);
				HashTable<K, V, Hash> newht;
				//newht._tables.resize(_tables.size() * 2);
				newht._tables.resize(__stl_next_prime(_tables.size() + 1));
				for (auto& data : _tables)
				{
					//旧表的数据映射到新表
					if (data._state == EXIST)
					{
						newht.Insert(data._kv);
					}
				}
				_tables.swap(newht._tables);

			}
			Hash hash;
			size_t hash0 = hash(kv.first) % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			int flag = 1;
			while (_tables[hashi]._state == EXIST)
			{
				hashi = (hash0 + i) % _tables.size();
				++i;
				//hashi = (hash0 + i * i * flag) % _tables.size();
				//// 1. 提前对步长取模，防止 i*i 本身越界导致无符号溢出喵
				//size_t step = (i * i) % _tables.size();
				//if (flag == 1)
				//{
				//	// 2. 正向探测：按正常逻辑相加再取模
				//	hashi = (hash0 + step) % _tables.size();
				//}
				//else
				//{
				//	// 3. 反向探测（核心修复点）：加上 _tables.size() 兜底！
				//	// 这样 A - B 就变成了 (A + N - B) % N，完美规避无符号数下溢出喵！
				//	hashi = (hash0 + _tables.size() - step) % _tables.size();
				//}
				//if (flag == 1)flag = -1;
				//else
				//{
				//	flag = 1;
				//	++i;
				//}
			}
			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_n;
			return true;
		}
		HashData<K, V>* Find(const K& key)
		{
			if (_tables.empty())return nullptr;
			Hash hash;
			size_t hash0 = hash(key) % _tables.size();
			size_t hashi = hash0;
			size_t i = 1;
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state == EXIST && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}
				hashi = (hash0 + i) % _tables.size();
				++i;
				if (hashi == hash0) break;// 极端防御：防止死循环
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_n;
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		vector<HashData<K, V>>_tables;
		size_t _n;//记录数据个数
	};
}
namespace hash_bucket
{
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			,_next(nullptr)
		{
		}
	};

	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		HashTable()
			:_tables(__stl_next_prime(0))
			, _n(0)
		{
		}
		HashTable(const HashTable& hash)
		{
			_tables.resize(hash._tables.size(), nullptr);
			_n = hash._n;
			for (size_t i = 0; i < hash._tables.size(); ++i)
			{
				Node* cur = hash._tables[i];
				while (cur)
				{
					// 顺着链表拷贝，为了保持顺序可以使用尾插，这里为了简单直接头插（顺序会反，但不影响哈希表功能）
					Node* newNode = new Node(cur->_kv);
					newNode->_next = _tables[i];
					_tables[i] = newNode;
					cur = cur->_next;
				}
			}
		}
		HashTable& operator=(HashTable hash)
		{
			_tables.swap(hash._tables);
			std::swap(_n, hash._n);
			return *this;
		}
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}
		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))return false;
			Hash hash;
			// 负载因子 == 1时扩容
			if (_n == _tables.size())
			{
				/*HashTable<K, V> newht;
				newht._tables.resize(__stl_next_prime(_tables.size() + 1));
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						newht.Insert(cur->_kv);
						cur = cur->_next;
					}
				}   

				_tables.swap(newht._tables);*/

				vector<Node*> newTatble(__stl_next_prime(_tables.size()+1));
				for (size_t i = 0; i < _tables.size(); i++)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;
						// 头插到新表
						size_t hashi = hash(cur->_kv.first) % newTatble.size();
						cur->_next = newTatble[hashi];
						newTatble[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;

				}

				_tables.swap(newTatble);
			}

			size_t hashi = hash(kv.first) % _tables.size();
			// 头插
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;

			return true;
		}
		Node* Find(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}
		bool Erase(const K& key)
		{
			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* pre = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					if (pre == nullptr)
					{
						//头结点
						_tables[hashi] = cur->_next;
					}
					else
					{
						pre->_next = cur->_next;
					}
					delete cur;
					--_n;
					return true;
				}
				else
				{
					pre = cur;
					cur = cur->_next;
				}
			}
			return false;
		}
	private:
		vector<Node*>_tables;
		size_t _n = 0;
	};
};