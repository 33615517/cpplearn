#pragma once
#pragma once
#include <deque>

namespace xingguichutu
{
    // 同样使用 std::deque 作为默认底层容器
    template<class T, class Container = std::deque<T>>
    class queue
    {
    public:
        // 入队 -> 本质是调用底层容器的尾插
        void push(const T& x)
        {
            _con.push_back(x);
        }

        // 出队 -> 本质是调用底层容器的头删
        // 注意：这里体现了 deque 的优势！如果是 vector 做底层就没有 pop_front 接口了，会直接报错
        void pop()
        {
            _con.pop_front();
        }

        // 获取队头 -> 本质是获取底层容器的头部元素
        const T& front() const
        {
            return _con.front();
        }

        // 获取队尾 -> 本质是获取底层容器的尾部元素
        const T& back() const
        {
            return _con.back();
        }

        size_t size() const
        {
            return _con.size();
        }

        bool empty() const
        {
            return _con.empty();
        }

    private:
        Container _con; // 底层打工人
    };
}
