#include <iostream>
#include <string>
 #include "vector.h" 
using namespace std;

// 写一个通用的打印函数，顺便测试 const 迭代器和范围 for 循环
template<typename T>
void print_vector(const xingguichutu::vector<T>& v, const string& name)
{
    cout << name << ": ";
    for (auto e : v)
    {
        cout << e << " ";
    }
    cout << "\n";
}

void test_basic()
{
    cout << "========== 1. 测试基础功能 (int) ==========" << endl;

    xingguichutu::vector<int> v1;

    // 测试尾插和扩容
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    print_vector(v1, "v1 (尾插1,2,3,4)");

    // 测试尾删
    v1.pop_back();
    print_vector(v1, "v1 (尾删一次)");

    // 测试 insert (头部插入)
    v1.insert(v1.begin(), 0);
    print_vector(v1, "v1 (头插 0)");

    // 测试 erase (删除中间的 2)
    v1.erase(v1.begin() + 2);
    print_vector(v1, "v1 (删除第三个元素 2)");

    // 测试拷贝构造
    xingguichutu::vector<int> v2(v1);
    print_vector(v2, "v2 (拷贝自 v1)");

    // 测试赋值重载
    xingguichutu::vector<int> v3;
    v3.push_back(100);
    v3 = v1;
    print_vector(v3, "v3 (赋值自 v1)");
}

void test_string_deep_copy()
{
    cout << "\n========== 2. 测试深拷贝避坑 (std::string) ==========" << endl;

    xingguichutu::vector<string> vs;
    vs.push_back("Hello");
    vs.push_back("World");

    // 故意循环多次尾插，强行触发底层的 reserve 扩容逻辑
    for (int i = 0; i < 5; ++i)
    {
        vs.push_back("C++");
    }

    print_vector(vs, "vs");
    cout << "当前 size: " << vs.size() << ", capacity: " << vs.capacity() << endl;
    cout << "--> 如果你看到了这行字且程序没有崩溃，恭喜你！深拷贝避坑成功！" << endl;
}

int main()
{
    test_basic();
    test_string_deep_copy();

    return 0;
}