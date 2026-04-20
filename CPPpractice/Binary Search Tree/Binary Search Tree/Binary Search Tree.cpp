#include <iostream>
#include <string>
using namespace std;
#include "Binary Search Tree.h" 

// ==========================================
// 测试 1：纯 Key 模型的二叉搜索树
// ==========================================
/*
int main()
{
    int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
    key::BSTree<int> t;
    for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
    {
        t.insert(a[i]);
    }
    t.InOrder();

    t.insert(16);
    t.InOrder();

    t.erase(3);
    t.InOrder();

    return 0;
}
*/

// ==========================================
// 测试 2：Key-Value 模型的字典翻译系统
// ==========================================

int main()
{
    key_value::BSTree<string, string> dict;
    // 测试拷贝构造（目前被注释，若需要可打开验证深拷贝）
    // key_value::BSTree<string, string> copy = dict;

    dict.insert("left", "左边");
    dict.insert("right", "右边");
    dict.insert("insert", "插入");
    dict.insert("string", "字符串");

    string str;
    while (cin >> str)
    {
        auto ret = dict.Find(str); // ret 类型是 string*
        if (ret)
        {
            // 修复：ret 是原生指针，直接解引用即可拿到 Value
            cout << "->" << *ret << endl;
        }
        else
        {
            cout << "无此单词，请重新输入" << endl;
        }
    }
    return 0;
}


 //==========================================
// 测试 3：Key-Value 模型的高频词统计（当前激活状态）
// ==========================================
//int main()
//{
//    string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜",
//                     "苹果", "香蕉", "苹果", "香蕉" };
//
//    key_value::BSTree<string, int> countTree;
//
//    for (const auto& str : arr)
//    {
//        // ret 的类型是 int*
//        auto ret = countTree.Find(str);
//
//        if (ret == nullptr)
//        {
//            // 1、不在，说明水果第一次出现，则插入<水果, 1>
//            countTree.insert(str, 1);
//        }
//        else
//        {
//            // 2、在，则查找到的结点中水果对应的次数++
//            // 修复：对 int* 解引用，然后自增
//            (*ret)++;
//        }
//    }
//
//    countTree.InOrder();
//    return 0;
//}