#include"HashTable.h"
int main()
{
	//int a[] = { 19,30,52,63,11,22 };
	int a[] = { 19,30,5,36,13,20,21,12};
	HashTable<int,int>ht;
	for (auto e : a)
	{
		ht.Insert({ e,e });
	}
	ht.Erase(30);
	if (ht.Find(20))
	{
		cout << "找到了" << endl;
	}
	if (ht.Find(30))
	{
		cout << "找到了" << endl;
	}
	else
	{
		cout << "没找到了" << endl;
	}
	
	return 0;
}