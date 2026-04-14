#pragma once
#include <vector>
#include <functional>
#include <algorithm> // 引入 std::swap

// 自定义比较仿函数：小于
template<class T>
class Less
{
public:
    bool operator()(const T& x, const T& y)
    {
        return x < y;
    }
};
// 自定义比较仿函数：大于
template<class T>
class Greater
{
public:
    bool operator()(const T& x, const T& y)
    {
        return x > y;
    }
};

namespace xingguichutu
{
    // 默认底层容器为 vector，默认比较规则为 less（建大堆）
    template <class T, class Container = std::vector<T>, class Compare = std::less<T>>
    class priority_queue
    {
    public:
        priority_queue() = default;

        // 迭代器区间构造：O(N) 效率的向下调整建堆
        template <class InputIterator>
        priority_queue(InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                c.push_back(*first);
                ++first;
            }
            // 从最后一个非叶子节点开始，倒着向上依次做向下调整
            for (int i = (c.size() - 2) / 2; i >= 0; --i)
            {
                AdjustDown(i);
            }
        }

        void push(const T& x)
        {
            c.push_back(x);
            AdjustUp(c.size() - 1); // 尾插后，对最后一个元素向上调整
        }

        void pop()
        {
            // 堆的经典删除：首尾交换，尾删，然后从根节点向下调整
            std::swap(c[0], c[c.size() - 1]); 
            c.pop_back();
            AdjustDown(0);
        }

        const T& top() const 
        {
            return c.front(); 
        }

        bool empty() const
        {
            return c.empty();
        }

        size_t size() const
        {
            return c.size();
        }

    private:
        // 向上调整（用于 push）
        void AdjustUp(int child)
        {
            int parent = (child - 1) / 2;
            while (child > 0)
            {
                if (comp(c[parent], c[child]))
                {
                    std::swap(c[parent], c[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
                else
                {
                    break;
                }
            }
        }

        // 向下调整（用于 pop 和区间构造）
        void AdjustDown(int parent)
        {
            int child = parent * 2 + 1; // 默认先算左孩子
            while (child < c.size())
            {
                // 如果右孩子存在，且右孩子比左孩子更符合条件（比如更大），就选右孩子
                if (child + 1 < c.size() && comp(c[child], c[child + 1]))
                {
                    ++child;
                }

                // 父亲和选出来的强壮孩子比较
                if (comp(c[parent], c[child])) // 【修复 1】：改为 comp() 仿函数调用
                {
                    std::swap(c[parent], c[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
                else
                {
                    break;
                }
            }
        }

    private:
        Container c;   // 底层容器
        Compare comp;  // 比较规则对象（仿函数）
    };
}