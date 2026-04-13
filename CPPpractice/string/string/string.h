#pragma once
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <string>
namespace xingguichutu
{
    class string
    {
    public:
        // 迭代器类型定义喵 (原生指针的降维打击)
        typedef char* iterator;
        typedef const char* const_iterator;

        // 迭代器接口
        iterator begin() { return _str; }
        const_iterator begin() const { return _str; }
        iterator end(){ return _str + _size;}
        const_iterator end() const {  return _str + _size; }

        // 构造、拷贝构造与析构喵 (注意深拷贝！)
        string(const char* str = "");
        string(const string& str);
        ~string();

        //赋值运算符重载
        string& operator=(const string& str);

        // 内存管理与基础属性喵
        const char* c_str() const { return _str; }  // 返回C风格字符串
        void clear() { _str[0] = '\0'; _size = 0; }  // 清空字符串
        size_t size() const { return _size; }        // 获取长度
        size_t capacity() const { return _capacity; }  // 获取容量
        void reserve(size_t n); // 核心性能优化点：按需预留空间
        void resize(size_t n, char c = '\0');
        // 下标访问 (支持越界 assert 检查)
        char& operator[](size_t pos);
        const char& operator[](size_t pos) const;

        // 数据修改操作 (尾插、拼接、随意插喵)
        void push_back(char ch);
        void append(const char* str);
        string& operator+=(char ch);
        string& operator+=(const char* str);

        void insert(size_t pos, char ch);
        void insert(size_t pos, const char* str);
        void erase(size_t pos, size_t len = npos);

        // 字符串查找与截取喵
        size_t find(char ch, size_t pos = 0);
        size_t find(const char* str, size_t pos = 0);
        string substr(size_t pos = 0, size_t len = npos);
        // 静态常量，用于表示 "未找到" 或 "直到末尾"
        static const size_t npos;
    private:
        char* _str;
        size_t _size;
        size_t _capacity; 


    };

    //  类外全局运算符重载声明喵
    // 关系运算符
    bool operator<(const string& s1, const string& s2);
    bool operator==(const string& s1, const string& s2);
    bool operator<=(const string& s1, const string& s2);
    bool operator>(const string& s1, const string& s2);
    bool operator>=(const string& s1, const string& s2);
    bool operator!=(const string& s1, const string& s2);

    // 流插入与提取运算符
    std::ostream& operator<<(std::ostream& out, const string& s);
    std::istream& operator>>(std::istream& in, string& s);
}
