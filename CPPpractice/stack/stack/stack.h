#pragma once
#pragma once
#include <deque>

namespace xingguichutu
{
    // 【核心设计】：第二个模板参数 Container 默认赋予 std::deque<T>
    // 只要传入的容器支持 push_back, pop_back, back 等操作，就能作为栈的底层引擎！
    template<class T, class Container = std::deque<T>>
    class stack
    {
    public:
        // 压栈 -> 本质是调用底层容器的尾插
        void push(const T& x)
        {
            _con.push_back(x);
        }

        // 出栈 -> 本质是调用底层容器的尾删
        void pop()
        {
            _con.pop_back();
        }

        // 获取栈顶 -> 本质是获取底层容器的尾部元素
        const T& top() const
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
        Container _con; // 实例化一个底层容器对象，它负责实际的“体力活”
    };
}
