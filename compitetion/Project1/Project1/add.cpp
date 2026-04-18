#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
class Person {
public:
	virtual void BuyTicket() { cout << "买票-全价" << endl; }
private:
	string _name;
};
class Student : public Person {
public:
	virtual void BuyTicket() { cout << "买票-打折" << endl; }
private:
	string _id;
};
class Soldier : public Person {
public:
	virtual void BuyTicket() { cout << "买票-优先" << endl; }
private:
	string _codename;
};
void Func(Person* ptr)
{
	// 这里可以看到虽然都是Person指针Ptr在调用BuyTicket
	// 但是跟ptr没关系，而是由ptr指向的对象决定的。
	ptr->BuyTicket();
}
int main()
{
	
	return 0;
}