#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
#include <vector>
#include "queue.h" 
using namespace std;
int main()
{
    cout << "========== 测试 1：默认底层容器 (deque) ==========" << endl;
    xingguichutu::queue<int> q1;

    q1.push(10);
    q1.push(20);
    q1.push(30);
    q1.push(40);

    cout << "q1 的大小: " << q1.size() << endl;
    cout << "q1 队头元素: " << q1.front() << endl;
    cout << "q1 队尾元素: " << q1.back() << endl;

    cout << "q1 出队顺序: ";
    while (!q1.empty())
    {
        cout << q1.front() << " ";
        q1.pop();
    }
    cout << "\n\n";

    cout << "========== 测试 2：更换底层容器为 list ==========" << endl;
    // queue 需要高频的头删 (pop_front) 和尾插 (push_back)
    // list 完美支持这两个接口，所以可以作为 queue 的底层引擎！
    xingguichutu::queue<int, std::list<int>> q2;

    q2.push(100);
    q2.push(200);
    q2.push(300);

    cout << "q2 (list底层) 出队顺序: ";
    while (!q2.empty())
    {
        cout << q2.front() << " ";
        q2.pop();
    }
    cout << "\n\n";

    cout << "========== 致命测试：为什么不能用 vector？ ==========" << endl;
    xingguichutu::queue<int, std::vector<int>> q3;
    q3.push(1);
    q3.pop();
    /* * 💣 危险动作请勿模仿：
     * xingguichutu::queue<int, std::vector<int>> q3;
     * q3.push(1);
     * q3.pop(); 5// <--- 编译到这一行会直接报错！
     * * 原因揭秘：
     * queue 的 pop() 底层调用的是 _con.pop_front()。
     * 但是 std::vector 为了保证内存连续性，根本没有提供 pop_front() 这个接口！
     * 如果强行头删，vector 需要挪动所有元素，效率极低（O(N)）。
     * 这也是为什么 STL 默认选择 deque，而不是大家最熟悉的 vector 来做 queue 底层的原因！
     */
    cout << "详细原因请看代码注释！(完美体现了适配器的接口依赖性)" << endl;

    return 0;
}