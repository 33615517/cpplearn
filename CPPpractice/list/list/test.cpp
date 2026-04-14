#include <iostream>
#include <string>
#include "list.h" 
using namespace std;
template<typename T>
void print_list(const xingguichutu::list<T>& lt, const string& name)
{
    cout << name << ": ";
    for (auto e : lt)
    {
        cout << e << " ";
    }
    cout << "\n";
}
int main()
{
    xingguichutu::list<int> lt1;

    // 测试增
    lt1.push_back(10);
    lt1.push_back(20);
    lt1.push_front(5);
    lt1.insert(lt1.end(), 30);
    print_list(lt1, "插入数据后 lt1"); // 预期: 5 10 20 30

    // 测试删
    lt1.pop_front();
    lt1.pop_back();
    print_list(lt1, "头尾各删一次 lt1"); // 预期: 10 20

    // 测试拷贝和赋值 (Copy & Swap)
    xingguichutu::list<int> lt2(lt1);
    print_list(lt2, "拷贝构造 lt2"); // 预期: 10 20

    xingguichutu::list<int> lt3;
    lt3.push_back(999);
    lt3 = lt2;
    print_list(lt3, "赋值重载 lt3"); // 预期: 10 20

    return 0;
}