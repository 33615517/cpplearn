#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm> // 用于 swap
using namespace std;

#include "AVL.h"

// 基础测试：固定数据集的插入与平衡测试
void TestAVLTree1()
{
	cout << "========== Test 1: 基础插入测试 ==========" << endl;
	AVLTree<int, int> t;
	// 特殊的带有双旋场景的测试用例
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}
	t.InOrder();
	cout << "当前树是否平衡: " << (t.IsBalanceTree() ? "True" : "False") << endl;
	cout << endl;
}

// 性能与大数据量插入、查找测试
void TestAVLTree2()
{
	cout << "========== Test 2: 百万级数据插入与查找测试 ==========" << endl;
	const int N = 1000000;
	vector<int> v;
	v.reserve(N);
	srand((unsigned int)time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i); // 保证有一定的随机性和递增性
	}

	size_t begin2 = clock();
	AVLTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}
	size_t end2 = clock();

	cout << "Insert " << N << " nodes time: " << end2 - begin2 << " ms" << endl;
	cout << "Is Balance Tree: " << (t.IsBalanceTree() ? "True" : "False") << endl;
	cout << "Tree Height: " << t.Height() << endl;
	cout << "Tree Size: " << t.Size() << endl;

	size_t begin1 = clock();
	// 随机查找测试
	for (size_t i = 0; i < N; i++)
	{
		t.Find((rand() + i));
	}
	size_t end1 = clock();
	cout << "Find " << N << " times time: " << end1 - begin1 << " ms" << endl;
	cout << endl;
}

// 核心验证：大体量随机乱序删除测试
void TestAVLTreeDelete()
{
	cout << "========== Test 3: 大体量乱序删除与平衡校验测试 ==========" << endl;
	const int N = 100000; // 删除操作耗时较长，这里采用十万级数据进行高压测试
	vector<int> v;
	v.reserve(N);
	srand((unsigned int)time(0));

	for (size_t i = 0; i < N; i++)
	{
		v.push_back(rand() + i);
	}

	AVLTree<int, int> t;
	for (auto e : v)
	{
		t.Insert(make_pair(e, e));
	}

	cout << "插入完成，初始节点数量: " << t.Size() << endl;
	cout << "初始状态是否平衡: " << (t.IsBalanceTree() ? "True" : "False") << endl;

	// 【关键点】利用洗牌算法打乱数组，模拟在真实的业务场景下，随机删除树的内部节点和叶子节点
	for (size_t i = 0; i < v.size(); i++)
	{
		swap(v[i], v[rand() % v.size()]);
	}

	size_t begin3 = clock();

	// 阶段 1：删除一半的节点，验证树在经历剧烈结构变化后是否仍能维持严格的 AVL 特性
	size_t deleteCount = N / 2;
	for (size_t i = 0; i < deleteCount; i++)
	{
		t.Erase(v[i]);

		// 极限压测注：如果你想绝对严谨，可以取消下方注释，在每次删除后校验。
		// 但这会导致时间复杂度飙升至 O(N^2)，跑完需要很久，通常仅在小数据量(N=1000) Debug 时开启。
		/*
		if (!t.IsBalanceTree()) {
			cout << "在删除节点 " << v[i] << " 后发生失衡崩溃！" << endl;
			return;
		}
		*/
	}
	size_t end3 = clock();

	cout << "随机删除了 " << deleteCount << " 个节点，耗时: " << end3 - begin3 << " ms" << endl;
	cout << "删除一半后，当前节点数量: " << t.Size() << endl;
	cout << "删除一半后，是否依然平衡: " << (t.IsBalanceTree() ? "True" : "False") << endl;

	// 阶段 2：删除剩余的所有节点，验证空树状态机是否正常
	for (size_t i = deleteCount; i < N; i++)
	{
		t.Erase(v[i]);
	}

	cout << "删除全部节点后，当前节点数量: " << t.Size() << endl;
	cout << "清空后是否依然平衡(空树): " << (t.IsBalanceTree() ? "True" : "False") << endl;
	cout << endl;
}

int main()
{
	// 1. 简单校验插入逻辑
	TestAVLTree1();

	// 2. 校验大数据量插入与查找性能
	TestAVLTree2();

	// 3. 校验最复杂的删除状态机与平衡维持
	TestAVLTreeDelete();

	return 0;
}