#include<iostream>
using namespace std;
//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//};
//void Func(Person* ptr)
//{
//	// 这里可以看到虽然都是Person指针Ptr在调用BuyTicket
//	// 但是跟ptr没关系，而是由ptr指向的对 象决定的。
//	ptr->BuyTicket();
//}
//class Animal
//{
//public:
//	virtual void talk() const
//	{
//	}
//};
//class Dog : public Animal
//{
//public:
//	virtual void talk() const
//	{
//		std::cout << "汪汪" << std::endl;
//	}
//};
//
//class Cat : public Animal
//{
//public:
//	virtual void talk() const
//	{
//		std::cout << "(>^ω^<)喵" << std::endl;
//	}
//};
//
//void letsHear(const Animal& animal)
//{
//	animal.talk();
//}
//
//class A
//{
//public:
//	virtual void func(int val = 1) { std::cout << "A->" << val << std::endl; }
//	virtual void test() { func(); }
//};
//class B : public A
//{
//public:
//	void func(int val = 0) { std::cout << "B->" << val << std::endl; }
//};
//int main(int argc, char* argv[])
//{
//	B* p = new B;
//	p->func();
//	return 0;
//}
//int main()
//{
//	/*Person ps;
//	Student st;
//	Func(&ps);
//	Func(&st);*/
//	Cat cat;
//	Dog dog;
//	letsHear(cat);
//	letsHear(dog);
//	return 0;
//}
//int main()
//{
//
//	return 0;
//}

//class A {};
//class B : public A {};
//
//class Person {
//public:
//	virtual A* BuyTicket()
//	{
//		cout << "买票-全价" << endl;
//		return nullptr;
//	}
//};
//
//class Student : public Person {
//public:
//	virtual B* BuyTicket()
//	{
//		cout << "买票-打折" << endl;
//		return nullptr;
//	}
//};
//
//void Func(Person* ptr)
//{
//	ptr->BuyTicket();
//}
//
//int main()
//{
//	Person ps;
//	Student st;
//
//	Func(&ps);
//	Func(&st);
//	return 0;
//}

//class A
//{
//public:
//	virtual ~A()
//	{
//		cout << "~A()" << endl;
//	}
//};
//
//class B : public A
//{
//public:
//	virtual ~B()
//	{
//		cout << "~B()->delete:" << _p << endl;
//		delete _p;
//	}
//	void push() {}
//protected:
//	int* _p = new int[10];
//};
//
//// 只有派生类Student的析构函数重写了Person的析构函数，下面的delete对象调用析构函数，才能
////构成多态，才能保证p1和p2指向的对象正确的调用析构函数。
//int main()
//{
//	A* p1 = new A;
//	A* p2 = new B;
//	delete p1;
//	delete p2;
//	return 0;
//}
//
//class Car {
//public:
//	virtual void Dirve()
//	{
//	}
//};
//class Benz :public Car {
//public:
//	virtual void Drive() override { cout << "Benz-舒适" << endl; }
//};
//int main()
//{
//	return 0;
//}
//class Car
//{
//public:
//	virtual void Drive() = 0;
//};
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-操控" << endl;
//	}
//};
//int main()
//{
//	// 编译报错：error C2259: “Car”: 无法实例化抽象类
//	//Car car;
//	Car* pBenz = new Benz;
//	pBenz->Drive();
//	Car* pBMW = new BMW;
//	pBMW->Drive();
//	return 0;
//}
//

//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Func1()" << endl;
//	}
//protected:
//	int _b = 1;
//	char _ch = 'x';
//};
//
//int main()
//{
//	Base b;
//	cout << sizeof(b) << endl;
//	return 0;
//}
//class Person {
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//private:
//	string _name;
//};
//class Student : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-打折" << endl; }
//private:
//	string _id;
//};
//class Soldier : public Person {
//public:
//	virtual void BuyTicket() { cout << "买票-优先" << endl; }
//private:
//	string _codename;
//};
//void Func(Person* ptr)
//{
//	// 这里可以看到虽然都是Person指针Ptr在调用BuyTicket
//	// 但是跟ptr没关系，而是由ptr指向的对象决定的。
//	ptr->BuyTicket();
//}
//int main()
//{
//	// 其次多态不仅仅发生在派生类对象之间，多个派生类继承基类，重写虚函数后
//	// 多态也会发生在多个派生类之间。
//	Person ps;
//	Student st;
//	Soldier sr;
//	Func(&ps);
//	Func(&st);
//	Func(&sr);
//	return 0;
//}
class Base {
public:
	virtual void func1() { cout << "Base::func1" << endl; }
	virtual void func2() { cout << "Base::func2" << endl; }
	void func5() { cout << "Base::func5" << endl; }
protected:
	int a = 1;
};
class Derive : public Base
{
public:
	// 重写基类的func1
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func1" << endl; }
	void func4() { cout << "Derive::func4" << endl; }
protected:
	int b = 2;
};
//int main()
//{
//	Base b;
//	Derive d;
//	return 0;
//}
int main()
{
	int i = 0;
	static int j = 1;
	int* p1 = new int;
	const char* p2 = "xxxxxxxx";
	printf("栈:%p\n", &i);
	printf("静态区:%p\n", &j);
	printf("堆:%p\n", p1);
	printf("常量区:%p\n", p2);
	Base b;
	Derive d;
	Base* p3 = &b;
	Derive* p4 = &d;
	printf("Person虚表地址:%p\n", *(int*)p3);
	printf("Student虚表地址:%p\n", *(int*)p4);
	printf("虚函数地址:%p\n", &Base::func1);
	printf("普通函数地址:%p\n", &Base::func5);
	return 0;
}

