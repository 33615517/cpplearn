#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include <cstdio>
#include <string>
#include <functional>

//using namespace std;
struct Date
{
	int _year;
	int _month;
	int _day;
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
	}
	~Date()
	{
		std::cout << "~Date()" << std::endl;
	}
};
namespace xingguichutu
{
	template<class T>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			: _ptr(ptr)
			, _pcount(new int(1))
		{
		}
		template<class D>
		shared_ptr(T* ptr, D del)
			: _ptr(ptr)
			, _pcount(new int(1))
			, _del(del)
		{

		}
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _del(sp._del)
		{
			++(*_pcount);
		}
		~shared_ptr()
		{
			if ((--(*_pcount)) == 0)
			{
				//delete _ptr;
				_del(_ptr);
				delete _pcount;
			}
		}
		/*shared_ptr<T>& operator=(shared_ptr<T> sp)
		{
			swap(_ptr, sp._ptr);
			swap(_pcount, sp._pcount);
			return *this;
		}*/
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			//if (this != &sp)
			if (_ptr != sp._ptr)
			{
				if (--(*_pcount) == 0)
				{
					delete _ptr;
					delete _pcount;
				}
				_ptr = sp._ptr;
				_pcount = sp._pcount;
				(*_pcount)++;
			}
			return *this;
		}
		T* get() const
		{
			return _ptr;
		}
		int use_count() const
		{
			return *_pcount;
		}
		T& operator*()
		{
			return *_ptr;
		}
		T* operator->()
		{
			return _ptr;
		}
	private:
		T* _ptr;
		int* _pcount;
		std::function<void(T*)> _del = [](T* ptr) {delete ptr; };
	};

}
class Fclose
{
public:
	void operator()(FILE* ptr) const
	{
		std::cout << "fclose:" << ptr << std::endl;
		fclose(ptr);
	}
};
template<class T>
void DelteArrayFunc(T* ptr)
{
	delete[] ptr;
}
//int main()
//{
//	xingguichutu::shared_ptr<Date> sp1(new Date);
//	xingguichutu::shared_ptr<Date> sp3(new Date[10], [](Date* ptr) {delete[] ptr; });
//	return 0;
//}
//int main()
//{ 
//	//std::shared_ptr<Date[]> sp1(new Date[10]);
//	/*std::shared_ptr<Date[]> sp1(new Date[10],DelteArrayFunc<Date>);*/
//	//std::shared_ptr<Date> sp1(new Date[10], [](Date* ptr)
//	//	{delete[] ptr; });
//	//std::unique_ptr<Date[]>sp2(new Date[10]);
//	//std::shared_ptr<FILE> sp5(fopen("zhinengzhizhen.cpp", "r"),Fclose());
//	/*std::shared_ptr<FILE> sp5(fopen("zhinengzhizhen.cpp", "r"), [](FILE* ptr)
//		{
//			if (ptr != nullptr) {
//				std::cout << "fclose: " << ptr  << std::endl;
//				fclose(ptr);
//			}
//			else {
//				std::cout << "文件未打开，拦截到空指针，安全退出喵！" << std::endl;
//			}
//		});*/
//	std::unique_ptr<Date[]>sp6(new Date[10]);
//	//std::unique_ptr<FILE,decltype(Fclose())>sp7(fopen("zhinengzhizhen.cpp", "r"));
//	std::unique_ptr < FILE, decltype([](FILE* ptr) {if (ptr != nullptr) {
//		std::cout << "fclose: " << ptr << std::endl;
//		fclose(ptr);
//	}
//	else {
//		std::cout << "文件未打开，拦截到空指针，安全退出喵！" << std::endl;
//	} }) > sp8(fopen("zhinengzhizhen.cpp", "r"));
//	return 0;
//}
//int main()
//{
//	std::shared_ptr<Date> sp1(new Date(2026,4,28));
//	std::shared_ptr<Date> sp2 = std::make_shared<Date>(2026, 4, 28);
//	std::shared_ptr<Date> sp4;
//	if (sp1)
//		std::cout << "sp1 is not nullptr" << std::endl;
//	//if (!sp4)
//	if (!sp4.operator bool())
//		std::cout << "sp4 is nullptr" << std::endl;
//	return 0;
//}

struct ListNode
{
	int _data;
	/*ListNode* _next;
	ListNode* _prev;*/
	/*std::shared_ptr<ListNode> _next;
	std::shared_ptr<ListNode> _prev;*/
	std::weak_ptr<ListNode> _next;
	std::weak_ptr<ListNode> _prev;
	~ListNode()
	{
		std::cout << "~ListNode()" << std::endl;
	}
};
//int main()
//{
//	std::shared_ptr<ListNode> n1(new ListNode);
//	std::shared_ptr<ListNode> n2(new ListNode);
//	std::cout << n1.use_count() << std::endl;
//	std::cout << n2.use_count() << std::endl;
//	n1->_next = n2;
//	n2->_next = n1;
//	std::cout << n1.use_count() << std::endl;
//	std::cout << n2.use_count() << std::endl;
//	return 0;
//}
int main()
{
	std::shared_ptr<std::string> sp1(new std::string("11111"));
	std::shared_ptr<std::string> sp2(sp1);
	std::weak_ptr<std::string> wp = sp1;
	std::cout << wp.expired() << std::endl;
	std::cout << wp.use_count() << std::endl;
	sp1 = std::make_shared<std::string>("22222");
	std::cout << wp.expired() << std::endl;
	std::cout << wp.use_count() << std::endl;
	sp2 = std::make_shared<std::string>("3333");
	std::cout << wp.expired() << std::endl;
	std::cout << wp.use_count() << std::endl;
	wp = sp1;
	auto sp3 = wp.lock();
	std::cout << wp.expired() << std::endl;
	std::cout << wp.use_count() << std::endl;
	return 0;
}
