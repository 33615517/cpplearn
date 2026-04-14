#pragma once
#include <assert.h>
#include <algorithm> // 提供 std::swap

namespace xingguichutu
{
    template<class T>
    class vector
    {
    public:
        // 在我们手写的 vector 中，迭代器的本质其实就是原生指针。
        // 这也是为什么 vector 支持极速随机访问的原因。
        typedef T* iterator;             // 可修改元素的迭代器
        typedef const T* const_iterator; // 只读迭代器，保障 const 对象的安全访问

        // ==========================================
        // 1. 默认成员函数
        // ==========================================

        // 强制编译器生成默认的无参构造函数
        // 因为我们在 private 处给了缺省值 nullptr，所以这里什么都不写也是安全的
        vector() = default;

        // 拷贝构造函数
        // 用法：vector<int> v2(v1);
        vector(const vector<T>& v)
        {
            reserve(v.size()); // 提前一次性开好空间，避免 push_back 时频繁扩容
            for (auto& u : v)
            {
                push_back(u);  // 逐个尾插，复用现成代码
            }
        }

        // 赋值运算符重载（极其精妙的现代 C++ 写法：Copy & Swap）
        // 注意参数是按值传递的（vector<T> v），这意味着传参时会调用拷贝构造生成一个临时的 v
        vector<T>& operator=(vector<T> v)
        {
            // 我们直接把这个临时对象 v 的底层指针和我们自己的指针交换。
            // 相当于我们“偷”走了 v 开辟好的新空间和数据，把我们的旧垃圾给了 v。
            swap(v);
            // 函数结束时，局部变量 v 出作用域被销毁，顺便帮我们自动释放了旧空间的内存！
            return *this;
        }

        // 析构函数：释放动态开辟的数组空间
        ~vector()
        {
            if (_start)
            {
                delete[] _start;
                _start = _finish = _end_of_storage = nullptr; // 防野指针的好习惯
            }
        }

        // ==========================================
        // 2. 迭代器与容量接口
        // ==========================================

        iterator begin() { return _start; }
        iterator end() { return _finish; } // 注意：end 指向的是最后一个有效数据的【下一个位置】

        const_iterator begin() const { return _start; }
        const_iterator end()   const { return _finish; }

        // 指针相减的魔法：同类型指针相减，结果并不是地址差的字节数，而是它们之间【相隔的元素个数】
        size_t size()     const { return _finish - _start; }           // 获取当前有效数据个数
        size_t capacity() const { return _end_of_storage - _start; }   // 获取当前底层的总容量
        bool   empty()    const { return _finish == _start; }          // 判空：首尾指针相遇即为空

        // ==========================================
        // 3. 核心容量管理：扩容与调整大小
        // ==========================================

        // 【经典大坑反例演示：浅拷贝导致的崩溃】
        // 如果 T 是内置类型(如 int)，这段代码没问题。
        // 但如果 T 是自定义类型(如 string)，memcpy 只会按字节进行浅拷贝。
        // 当执行 delete[] _start 时，旧空间里的 string 会调用析构函数释放堆内存，
        // 导致新空间 tmp 里的 string 全部变成指向已被释放内存的野指针！一用就崩溃！
        /*
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                size_t old_size = size();
                T* tmp = new T[n];
                if (_start)
                {
                    memcpy(tmp, _start, sizeof(T) * old_size); // 致命错误：浅拷贝
                    delete[] _start;
                }
                _start = tmp;
                _finish = tmp + old_size;
                _end_of_storage = tmp + n;
            }
        }
        */

        // 正确的 reserve：只负责开辟物理空间，不填充有效数据（size 不变，capacity 变）
        void reserve(size_t n)
        {
            if (n > capacity())
            {
                // 【避坑1】：必须提前保存旧元素的个数！
                // 因为下面 _start 会指向新空间，一旦 _start 变了，再去调用 size() 算出来的就是垃圾值。
                size_t old_size = size();
                T* tmp = new T[n]; // 步骤1：向操作系统申请一块更大的连续新空间

                if (_start)
                {
                    // 步骤2：安全搬家。使用 for 循环触发对象自身的赋值重载。
                    // 这样当 T 为 string 时，会自动调用 string 的深拷贝，完美避开 memcpy 的大坑。
                    for (size_t i = 0; i < old_size; ++i)
                    {
                        tmp[i] = _start[i];
                    }
                    delete[] _start; // 步骤3：销毁旧房子
                }

                // 步骤4：更新内部的三个核心指针，让它们指向新房子
                _start = tmp;
                _finish = tmp + old_size; // 利用前面保存的 old_size 准确定位有效数据尾部
                _end_of_storage = tmp + n;
            }
        }

        // resize：既开辟物理空间，又填充有效数据（size 会变）
        void resize(size_t n, T val = T())
        {
            // 场景 A：想要的大小比现在小，直接“挥刀自宫”截断数据，容量不变
            if (n < size())
            {
                _finish = _start + n;
            }
            // 场景 B：想要的大小比现在大，需要填补空缺
            else
            {
                reserve(n); // 先确保底层房间足够多
                // 从当前的尾部开始，不断向后填补指定的默认值 val，直到总数达到 n 个
                while (_finish < _start + n)
                {
                    *_finish = val;
                    ++_finish;
                }
            }
        }

        // ==========================================
        // 4. 数据访问接口
        // ==========================================

        // 像使用普通数组一样使用 vector，越界会触发 assert 报错
        T& operator[](size_t pos) { assert(pos < size()); return _start[pos]; }
        const T& operator[](size_t pos) const { assert(pos < size()); return _start[pos]; }

        // ==========================================
        // 5. 增删查改接口
        // ==========================================

        void push_back(const T& x)
        {
            // 尾插前检查：如果房间满了，就扩容。初始容量为 0 时给 4，后续按 2 倍增长。
            if (_finish == _end_of_storage)
            {
                reserve(capacity() == 0 ? 4 : capacity() * 2);
            }
            *_finish = x; // 在当前尾部写入数据
            ++_finish;    // 尾部指针向后挪动一位
        }

        void pop_back()
        {
            assert(!empty()); // 空容器不能再删了
            --_finish; // 尾删极其简单粗暴，直接把尾指针往前挪一位即可（旧数据会在下次插入时被覆盖）
        }

        iterator insert(iterator pos, const T& x)
        {
            assert(pos >= _start && pos <= _finish); // pos 可以等于 _finish，相当于尾插

            // 扩容检查
            if (_finish == _end_of_storage)
            {
                // 【致命大坑：迭代器失效】
                // 扩容会导致底层换新空间，_start 变了，但传入的 pos 还是指向那块已经被 delete 的旧空间！
                // 解决方案：提前算好 pos 距离 _start 的相对距离，扩容后再把 pos 加回去。
                size_t len = pos - _start;
                reserve(capacity() == 0 ? 4 : capacity() * 2);
                pos = _start + len; // 修复失效的 pos
            }

            // 挪动数据：要把 pos 及之后的数据全部往后挪一位，给新数据腾出位置
            // 【细节】：必须从后往前挪（从最后一个有效数据开始挪），否则前面的数据会把后面的数据覆盖掉。
            iterator end = _finish - 1;
            while (end >= pos)
            {
                *(end + 1) = *end;
                --end;
            }

            *pos = x;  // 把新数据塞进腾出来的空位
            ++_finish; // 有效数据加一

            return pos; // 规定：返回新插入元素的位置，方便外部同步更新迭代器，防失效
        }

        iterator erase(iterator pos)
        {
            assert(pos >= _start && pos < _finish); // pos 不能等于 _finish，那里没数据

            // 挪动数据：要把 pos 之后的数据全部往前挪一位，像推土机一样把要删除的数据盖住
            // 【细节】：必须从前往后挪（从 pos+1 开始），依次往前覆盖。
            iterator it = pos + 1;
            while (it < _finish)
            {
                *(it - 1) = *it;
                ++it;
            }
            --_finish; // 有效数据减一

            return pos; // 规定：返回被删除元素的下一个位置（因为后面的数据填补上来了，所以其实还是 pos 的地址）
        }

        void swap(vector<T>& v)
        {
            // 直接交换彼此底层的三个核心指针，不需要拷贝数组里面的数据，实现 O(1) 极速交换
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_end_of_storage, v._end_of_storage);
        }

    private:
        // 【核心底层的三个大将】
        // C++ 标准库的 vector 本质上并不是靠 size 和 capacity 两个整数来管理的，
        // 而是单纯依靠这三个原生指针来掌控整个连续的内存块。

        // 1. 指向分配的内存空间的起始位置（即第一个有效元素）
        iterator _start = nullptr;

        // 2. 指向有效数据的尾部（即最后一个有效元素的下一个位置）
        iterator _finish = nullptr;

        // 3. 指向整个已分配容量的尾部（即整个可用空间的下一个位置）
        iterator _end_of_storage = nullptr;
    };
}