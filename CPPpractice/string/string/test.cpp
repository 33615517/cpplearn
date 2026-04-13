#define _CRT_SECURE_NO_WARNINGS 1
#include "String.h"
#include <iostream>

// 仅引入需要的标准库组件，避免使用 using namespace std; 防止与 std::string 发生命名空间冲突
using std::cout;
using std::cin;
using std::endl;

// ==========================================
// 测试模块 1：三大默认成员函数、迭代器与基础属性
// ==========================================
void test_construct_and_iterator()
{
    cout << "--- [Test 1] 构造、拷贝、迭代器测试 ---" << endl;

    // 明确使用自定义命名空间中的 string
    xingguichutu::string s1("Hello C++");
    cout << "s1 初始状态: " << s1.c_str() << " (size: " << s1.size() << ", capacity: " << s1.capacity() << ")" << endl;

    xingguichutu::string s2(s1);
    cout << "s2 (拷贝自 s1): " << s2.c_str() << endl;

    xingguichutu::string s3;
    s3 = s1;
    cout << "s3 (赋值自 s1): " << s3.c_str() << endl;

    cout << "范围 for 遍历 s1: ";
    for (auto ch : s1)
    {
        cout << ch << " ";
    }
    cout << endl << endl;
}

// ==========================================
// 测试模块 2：空间容量管理与下标访问
// ==========================================
void test_capacity_and_access()
{
    cout << "--- [Test 2] 容量管理与 [] 访问测试 ---" << endl;

    xingguichutu::string s1("Test");

    s1.reserve(100);
    cout << "reserve(100) 后，capacity: " << s1.capacity() << endl;

    s1.resize(10, '!');
    cout << "resize(10, '!') 后: " << s1.c_str() << " (size: " << s1.size() << ")" << endl;

    s1.resize(4);
    cout << "resize(4) 后: " << s1.c_str() << " (size: " << s1.size() << ")" << endl;

    s1[0] = 't';
    cout << "s1[0] 修改后: " << s1.c_str() << endl;

    const xingguichutu::string s2("ConstantString");
    cout << "const 对象读取: " << s2[0] << s2[1] << endl;

    s1.clear();
    cout << "clear() 后，size: " << s1.size() << " (是否为空: " << (s1.size() == 0 ? "是" : "否") << ")" << endl << endl;
}

// ==========================================
// 测试模块 3：数据修改 (增与删)
// ==========================================
void test_modifiers()
{
    cout << "--- [Test 3] 增删改操作测试 ---" << endl;

    xingguichutu::string s1("Hello");

    s1.push_back('-');
    s1.append("World");
    cout << "push_back & append 后: " << s1.c_str() << endl;

    s1 += " is ";
    s1 += 'g';
    s1 += "reat!";
    cout << "+= 操作后: " << s1.c_str() << endl;

    s1.insert(0, "Super ");
    s1.insert(s1.size() - 1, '?');
    cout << "insert 后: " << s1.c_str() << endl;

    s1.erase(0, 6);
    cout << "erase(0, 6) 后: " << s1.c_str() << endl;

    s1.erase(5);
    cout << "erase(5, npos) 后: " << s1.c_str() << endl << endl;
}

// ==========================================
// 测试模块 4：查找、截取与关系比较
// ==========================================
void test_find_substr_compare()
{
    cout << "--- [Test 4] 查找、截取与关系运算符测试 ---" << endl;

    xingguichutu::string s1("hello world, hello C++");

    size_t pos1 = s1.find('w');
    cout << "'w' 的位置: " << pos1 << endl;

    size_t pos2 = s1.find("C++");
    cout << "\"C++\" 的位置: " << pos2 << endl;

    if (pos2 != xingguichutu::string::npos)
    {
        xingguichutu::string sub = s1.substr(pos2, 3);
        cout << "截取出的子串: " << sub.c_str() << endl;
    }

    xingguichutu::string strA("apple");
    xingguichutu::string strB("banana");
    xingguichutu::string strC("apple");

    cout << "strA < strB : " << (strA < strB ? "True" : "False") << endl;
    cout << "strA == strC: " << (strA == strC ? "True" : "False") << endl;
    cout << "strB > strC : " << (strB > strC ? "True" : "False") << endl << endl;
}

// ==========================================
// 测试模块 5：流插入与提取 (<< 与 >>) - 交互版
// ==========================================
void test_stream_io()
{
    cout << "--- [Test 5] 流操作测试 (交互测试) ---" << endl;

    xingguichutu::string s1;

    cout << "请输入一段文字（可以包含前导空格以测试防御机制）：";

    // 等待标准输入
    cin >> s1;

    cout << "读取到的有效内容: [" << s1 << "]" << endl;
    cout << "（注：重载的 >> 运算符应在遇到首个有效字符后的空白符处停止读取）" << endl << endl;
}

// ==========================================
// 主控函数
// ==========================================
int main()
{
    cout << "开始执行 string 容器综合测试...\n\n";

    test_construct_and_iterator();
    test_capacity_and_access();
    test_modifiers();
    test_find_substr_compare();

    // 交互测试放在最后执行
    test_stream_io();

    cout << "测试执行完毕！" << endl;
    return 0;
}