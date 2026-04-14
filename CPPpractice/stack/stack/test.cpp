#include <iostream>
#include <vector>
#include <list>
#include "stack.h" 
using namespace std;
int main()
{
    cout << "========== 测试 1：默认底层容器 (deque) ==========" << endl;
    xingguichutu::stack<int> st1;

    st1.push(10);
    st1.push(20);
    st1.push(30);
    st1.push(40);

    cout << "st1 的大小: " << st1.size() << endl;
    cout << "st1 出栈顺序: ";
    while (!st1.empty())
    {
        cout << st1.top() << " ";
        st1.pop();
    }
    cout << "\n\n";

    cout << "========== 测试 2：更换底层容器为 vector ==========" << endl;
    // 展现适配器魅力的时刻！只需修改模板参数，底层瞬间换成 vector
    xingguichutu::stack<int, std::vector<int>> st2;

    st2.push(100);
    st2.push(200);
    st2.push(300);

    cout << "st2 (vector底层) 出栈顺序: ";
    while (!st2.empty())
    {
        cout << st2.top() << " ";
        st2.pop();
    }
    cout << "\n\n";

    cout << "========== 测试 3：更换底层容器为 list ==========" << endl;
    // 同理，底层瞬间换成 list，上层用法完全不变！
    xingguichutu::stack<int, std::list<int>> st3;

    st3.push(1000);
    st3.push(2000);
    st3.push(3000);

    cout << "st3 (list底层) 出栈顺序: ";
    while (!st3.empty())
    {
        cout << st3.top() << " ";
        st3.pop();
    }
    cout << "\n";

    return 0;
}