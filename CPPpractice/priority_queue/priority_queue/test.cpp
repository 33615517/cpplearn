#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include "priority_queue.h" 

using namespace std;

int main()
{
    cout << "========== 测试 1：默认大堆 (Less) ==========" << endl;
    // 默认使用 std::less，父亲 < 孩子时会交换，大的浮在上面 -> 大堆
    xingguichutu::priority_queue<int> pq_max;

    pq_max.push(3);
    pq_max.push(9);
    pq_max.push(1);
    pq_max.push(7);

    cout << "大堆出队顺序: ";
    while (!pq_max.empty())
    {
        cout << pq_max.top() << " ";
        pq_max.pop();
    }
    cout << "\n\n";

    cout << "========== 测试 2：切换为小堆 (Greater) ==========" << endl;
    // 传入自定义的 Greater 仿函数，父亲 > 孩子时会交换，小的浮在上面 -> 小堆
    xingguichutu::priority_queue<int, std::vector<int>, Greater<int>> pq_min;

    pq_min.push(3);
    pq_min.push(9);
    pq_min.push(1);
    pq_min.push(7);

    cout << "小堆出队顺序: ";
    while (!pq_min.empty())
    {
        cout << pq_min.top() << " ";
        pq_min.pop();
    }
    cout << "\n";

    return 0;
}
