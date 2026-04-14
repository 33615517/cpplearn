#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>

namespace xingguichutu
{
    // ==========================================
    // 1. 链表节点结构 (已完成)
    // ==========================================
    template<class T>
    struct list_node
    {
        list_node<T>* _prev;
        list_node<T>* _next;
        T _data;

        list_node(const T& x = T())
            : _prev(nullptr)
            , _next(nullptr)
            , _data(x)
        {
        }
    };

    // ==========================================
    // 2. 迭代器结构封装
    // 核心设计：用模板参数 Ref 和 Ptr 区分普通和 const 迭代器
    // ==========================================
    template<class T, class Ref, class Ptr>
    struct list_iterator
    {
        typedef list_node<T> Node;
        typedef list_iterator<T, Ref, Ptr> Self;

        Node* _node; // 内部封装的节点指针

        // 构造函数
        list_iterator(Node* node)
            :_node(node)
        {
        }

        // 遍历操作 (++/--)
        Self& operator++()      // 前置++
        {
            _node = _node->_next;
            return *this;
        }
        Self operator++(int)    // 后置++
        {
            Self tmp(*this);
            _node = _node->_next;
            return tmp;
        }
        Self& operator--()      // 前置--
        {
            _node = _node->_prev;
            return *this;
        }
        Self operator--(int)    // 后置--
        {
            Self tmp(*this);
            _node = _node->_prev;
            return tmp;
        }

        // 比较操作
        bool operator!=(const Self& s)
        {
            return _node != s._node;
        }
        bool operator==(const Self& s)
        {
            return _node == s._node;
        }

        // 访问操作 (* / ->)
        Ref operator*()
        {
            return _node->_data;
        }
        Ptr operator->()
        {
            return &_node->_data;
        }
    };

    // ==========================================
    // 3. 链表主类
    // ==========================================
    template<class T>
    class list
    {
        typedef list_node<T> Node;
    public:
        // 声明普通迭代器与 const 迭代器
        typedef list_iterator<T, T&, T*> iterator;
        typedef list_iterator<T, const T&, const T*> const_iterator;

        // ------------------------------------------
        // 构造、拷贝、赋值与析构
        // ------------------------------------------
        list()                                  // 默认构造
        {
            empty_init();
        }
        list(const list<T>& lt)                 // 拷贝构造
        {
            empty_init();
            for (auto& u : lt)
            {
                push_back(u);
            }
        }

        list<T>& operator=(list<T> lt)          // 赋值重载 (现代写法)
        {
            swap(lt);
            return *this;
        }
        ~list()                                 // 析构函数
        {
            clear();
            delete _head;
            _head = nullptr;
        }

        // ------------------------------------------
        // 迭代器接口
        // ------------------------------------------
        iterator begin()
        {
            return _head->_next;//隐式类型转换=return iterator(_head->next)
        }
        const_iterator begin() const
        {
            return _head->_next;
        }
        iterator end()
        {
            return _head;
        }
        const_iterator end() const
        {
            return _head;
        }

        // ------------------------------------------
        // 容量接口
        // ------------------------------------------
        size_t size() const
        {
            return _size;
        }
        bool empty() const
        {
            return _size == 0;
        }

        // ------------------------------------------
        // 增删查改接口
        // ------------------------------------------
        iterator insert(iterator pos, const T& x) // 指定位置前插入
        {
            Node* cur = pos._node;
            Node* prev = cur->_prev;
            Node* new_node = new Node(x);

            prev->_next = new_node;
            new_node->_prev = prev;
            new_node->_next = cur;
            cur->_prev = new_node;
            _size++;
            return iterator(new_node);
        }
        void push_back(const T& x)                // 尾插
        {
            insert(end(), x);
        }
        void push_front(const T& x)               // 头插
        {
            insert(begin(), x);
        }
        iterator erase(iterator pos)             // 删除指定位置节点
        {
            assert(pos != end());
            Node* cur = pos._node;
            Node* prev = cur->_prev;
            Node* next = cur->_next;

            prev->_next = next;
            next->_prev = prev;
            delete cur;
            _size--;
            return iterator(next);
        }
        void pop_back()                           // 尾删
        {
            erase(--end());
        }
        void pop_front()                          // 头删
        {
            erase(begin());
        }

        void clear()                              // 清空有效节点
        {
            iterator it = begin();
            while (it != end())
            {
                it = erase(it);
            }
        }
        void swap(list<T>& lt)                    // 交换底层指针
        {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }
    private:
        void empty_init() // 私有工具函数：初始化哨兵位
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
            _size = 0;
        }

        Node* _head;       // 指向哨兵位节点
        size_t _size;      // 记录有效节点数量，实现 O(1) 的 size() 接口
    };
}

