#pragma once
#include"Red-Black Tree.h"
namespace xingguichutu
{
	template<class K, class V>
	class map
	{
	private:
		RBTree<K, pair<K, V>> _t;

	};
}
