#pragma once
#include"HashTable.h"
namespace xingguichutu
{
	template<class K, class V>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		bool insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
	private:
		hash_bucket::HashTable<K, pair<K, V>, MapKeyOfT> _ht;
	};
}
