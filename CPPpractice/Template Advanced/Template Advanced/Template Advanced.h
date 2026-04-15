#pragma once
#include<iostream>
using namespace std;
namespace xingguichutu
{
    // 定义一个模板类型的静态数组
    // T 是类型形参，N 是非类型形参 (默认值为 10)
    template<class T, size_t N = 10>
    class array
    {
    public:
        T& operator[](size_t index) { return _array[index]; }
        const T& operator[](size_t index) const { return _array[index]; }

        size_t size() const { return _size; }
        bool empty() const { return 0 == _size; }

    private:
        T _array[N]; // 直接将非类型参数 N 当作常量用来定义数组大小
        size_t _size;
    };
}
// 函数模板 -- 参数匹配
template<class T>
bool Less(T left, T right)
{
    return left < right;
}

int main()
{
    cout << Less(1, 2) << endl;    // 可以比较，结果正确

    Date d1(2022, 7, 7);
    Date d2(2022, 7, 8);
    cout << Less(d1, d2) << endl;   // 可以比较，结果正确

    Date* p1 = &d1;
    Date* p2 = &d2;
    cout << Less(p1, p2) << endl;   // 可以比较，结果错误

    return 0;
}
