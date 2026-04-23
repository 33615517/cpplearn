#pragma once
#include"HashTable.h"
namespace xingguichutu
{
	template<class K>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		bool insert(const K& key)
		{
			return _ht.Insert(key);
		}
	private:
		hash_bucket::HashTable<K, K, SetKeyOfT>_ht;
	};
}