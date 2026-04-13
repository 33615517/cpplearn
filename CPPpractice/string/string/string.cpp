#define _CRT_SECURE_NO_WARNINGS 1
#include"String.h"
namespace xingguichutu
{
	const size_t string::npos = -1;
	void string::reserve(size_t n)
	{
		if (n > _capacity)
		{
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[] _str;
			_str = tmp;
			_capacity = n;
		}
	}
	// 调整有效字符长度，可指定填充字符
	void string::resize(size_t n, char ch)
	{
		if (n <= _size)
		{
			//删除，保留前n个
			_size = n;
			_str[_size] = '\0';
		}
		else 
		{
			reserve(n);
			for (size_t i = _size; i < n; i++)
			{
				_str[i] = ch;
			}
			_size = n;
			_str[_size] = '\0';
		}
	}
	//构造函数
	string::string(const char* str)
		: _size(strlen(str))
	{
		_capacity = _size;
		_str = new char[_capacity + 1];
		strcpy(_str, str);
	}
	//拷贝构造函数
	string::string(const string& str)
	{
		_str = new char[str._capacity + 1];
		strcpy(_str, str._str);
		_size = str._size;
		_capacity = str._capacity;
	}
    //构析函数
	string::~string()
	{
		delete[] _str;
		_str = nullptr;
		_size = _capacity = 0;
	}
	string& string::operator=(const string& str)
	{
		if (this != &str)
		{
			delete[] _str;
			_str = new char[str._capacity + 1];
			strcpy(_str, str._str);
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	char& string::operator[](size_t pos)
	{
		assert(pos < _size);
		return _str[pos];
	}
	const char& string::operator[](size_t pos) const 
	{
		assert(pos < _size);
		return _str[pos];
	}
	void string::push_back(char ch)
	{
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		_str[_size] = ch;
		++_size;
		_str[_size] = '\0';
	}
	void string::append(const char* str)
	{
		size_t len = strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		strcpy(_str + _size, str);
		_size += len;
	}
	string& string::operator+=(char ch) { push_back(ch); return *this; }
	string& string::operator+=(const char* str) { append(str); return *this; }
	// 小于运算符
	bool operator<(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) < 0;
	}
	// 等于运算符
	bool operator==(const string& s1, const string& s2)
	{
		return strcmp(s1.c_str(), s2.c_str()) == 0;
	}
	// 其他运算符可以通过复用上面的实现
	bool operator<=(const string& s1, const string& s2) { return s1 < s2 || s1 == s2; }
	bool operator>(const string& s1, const string& s2) { return !(s1 <= s2); }
	bool operator>=(const string& s1, const string& s2) { return !(s1 < s2); }
	bool operator!=(const string& s1, const string& s2) { return !(s1 == s2); }
	// 插入字符
	void string::insert(size_t pos, char ch)
	{
		assert(pos <= _size);  // 允许在末尾插入
		if (_size == _capacity)
		{
			reserve(_capacity == 0 ? 4 : _capacity * 2);
		}
		// 从后往前挪动数据
		size_t end= _size + 1;
		while (end > pos)
		{
			_str[end] = _str[end - 1];
			--end;
		}
		_str[pos] = ch;
		++_size;
	}

	// 插入字符串
	void string::insert(size_t pos, const char* str)
	{
		assert(pos <= _size);
		size_t len
			= strlen(str);
		if (_size + len > _capacity)
		{
			reserve(_size + len > 2 * _capacity ? _size + len : 2 * _capacity);
		}
		// 挪动数据腾出空间
		size_t end= _size + len;
		while (end > pos + len - 1)
		{
			_str[end] = _str[end - len];
			--end;
		}
		// 拷贝插入字符串
		for (size_t i = 0; i < len; ++i)
		{
			_str[pos + i] = str[i];
		}
		_size+= len;  // 更新size
	}
	void string::erase(size_t pos, size_t len)
	{
		assert(pos < _size);

		if (len >= _size - pos)
		{
			// 删除到末尾
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			// 向前挪动数据覆盖要删除的部分
			for (size_t i = pos; i < _size - len; ++i)
			{
				_str[i] = _str[i + len];
			}
			_size -= len;
			_str[_size] = '\0';  // 添加结束符
		}
	}
	// 查找字符
	size_t string::find(char ch, size_t pos)
	{
		for (size_t i = pos; i < _size; ++i)  
		{
			if (_str[i] == ch)
			{
				return i;
			}
		}
		return npos;  // 未找到
	}
	// 查找子串
	size_t string::find(const char* str, size_t pos)  
	{
		assert(pos < _size);
		const char* tmp = strstr(_str + pos, str);
		if (tmp == nullptr)
		{
			return npos;
		}
		else
		{
			return tmp - _str;  // 计算相对起始位置
		}
	}
	string string::substr(size_t pos, size_t len)
	{
		assert(pos < _size);
		// 处理长度超出剩余部分的情况
		if (len > _size - pos)
		{
			len = _size - pos;
		}
		string sub;
		sub.reserve(len);  // 预留空间，提高效率
		for (size_t i = 0; i < len; ++i)
		{
			sub += _str[pos + i];
		}
		return sub;
	}
	// 输出运算符
	std::ostream& operator<<(std::ostream& out, const string& s)
	{
		// 利用迭代器遍历输出
		for (auto x : s)
		{
			out << x;
		}
		return out;
	}
	std::istream& operator>>(std::istream& in, string& s)
	{
		s.clear(); // [cite: 332] 这一步清空做得非常好喵！

		char ch = in.get();

		// 🛡️ 防御机制 1：跳过前导空白字符（包括空格和换行）
		// 只有遇到真正的有效字符，才停止跳过，开始进入下面的收集环节
		while (ch == ' ' || ch == '\n')
		{
			ch = in.get();
		}

		const int N = 256;
		char buff[N];
		int i = 0;

		// 🛡️ 防御机制 2：加上 ch != EOF，防止读取文件末尾时发生死循环！
		while (ch != ' ' && ch != '\n' && ch != EOF)
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}

		if (i > 0)
		{
			buff[i] = '\0';
			s += buff;
		}

		return in; 
	}

}