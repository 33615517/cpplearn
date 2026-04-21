#pragma once
#include<iostream>
#include<vector>
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
template<class K,class V>
class HashTable
{
public:
	HashTable()
		:_tables(11)
		, _n(0)
	{}
	bool Insert(const pair<K, V>& kv)
	{
		if (Find(kv.first))
			return false;
		//负载因子>=0.7
		if (_n*10 / _tables.size() >= 7)
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
			HashTable<K, V> newht;
			newht._tables.resize(_tables.size()*2);
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
		size_t hash0 = kv.first % _tables. size();
		size_t hashi = hash0;
		size_t i = 1;
		int flag = 1;
		while (_tables[hashi]._state == EXIST)
		{
			hashi = (hash0 + i * i * flag) % _tables.size();
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
		size_t hash0 = key % _tables.size();
		size_t hashi = hash0;
		size_t i = 1;
		while (_tables[hashi]._state != EMPTY)
		{
			if (_tables[hashi]._state==EXIST&&_tables[hashi]._kv.first == key)
			{
				return &_tables[hashi];
			}
			hashi = (hash0 + i) % _tables.size();
			++i;
		}
		return nullptr;
	}
	bool Erase(const K& key)
	{
		HashData<K, V>* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			return true;
		}
		else
		{
			false;
		}
	}
private:
	vector<HashData<K, V>>_tables;
	size_t _n;//记录数据个数
};