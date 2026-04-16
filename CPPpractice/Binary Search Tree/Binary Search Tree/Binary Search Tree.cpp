#include<iostream>
using namespace std;
#include"Binary Search Tree.h"
//int main()
//{
//	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
//	key::BSTree<int>t;
//	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
//	{
//		t.insert(a[i]);
//	}
//	t.InOrder();
//	t.insert(16);
//	t.InOrder();
//	t.erase(3);
//	t.InOrder();
//	
//	return 0;
//}
//int main()
//{
//	key_value::BSTree<string, string> dict;
//	//key_value::BSTree<string, string> copy = dict;
//	dict.insert("left", "左边");
//	dict.insert("right", "右边");
//	dict.insert("insert", "插入");
//	dict.insert("string", "字符串");
//	string str;
//	while (cin >> str)
//	{
//		auto ret = dict.Find(str);
//		if (ret)
//		{
//			cout << "->" << ret->_value << endl;
//		}
//		else
//		{
//			cout << "无此单词，请重新输入" << endl;
//		}
//	}
//	return 0;
//}

int main()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
		"苹果", "香蕉", "苹果", "香蕉" };
	key_value::BSTree<string, int> countTree;
	for (const auto& str : arr)
	{
		// 先查找水果在不在搜索树中
		// 1、不在，说明水果第一次出现，则插入<水果, 1>
		// 2、在，则查找到的结点中水果对应的次数++
		//BSTreeNode<string, int>* ret = countTree.Find(str);
		auto ret = countTree.Find(str);
		if (ret == NULL)
		{
			countTree.insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}
	countTree.InOrder();
	return 0;
}


