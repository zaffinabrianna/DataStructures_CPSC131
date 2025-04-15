

//
#include <iostream>


//
#include "DoublyLinkedList.hpp"


//
using
	std::cout, std::endl
	;


void leaker()
{
	//
	CPSC131::DoublyLinkedList::DoublyLinkedList<int> dll;
	
	//
	for ( int i = 0; i < 100; i++ ) {
		dll.push_front(i * 2);
		dll.push_back(i * 2);
	}
	for ( int i = 0; i < 100; i++ ) {
		dll.pop_front();
		dll.pop_back();
	}
	
	dll.push_front(5);
	dll.erase(dll.begin());
	
	dll.assign(276, 100);
	dll.erase(dll.begin() + 26);
	
	dll.insert_after(50, 200);
	dll.insert_after(dll.begin() + 50, 200);
	dll.push_after(dll.begin() + 50, 200);
	
	{
		CPSC131::DoublyLinkedList::DoublyLinkedList<int> dll2;
		dll2.assign(277, 1000);
		dll2.assign(dll.begin() + 7, dll.begin() + 99);
		auto dll3 = dll2;
		dll3.clear();
	}
	
	//
	{
		// cout << "Enter assignment operator overload" << endl;
		CPSC131::DoublyLinkedList::DoublyLinkedList<int> t1 = dll;
		CPSC131::DoublyLinkedList::DoublyLinkedList<int> t2(dll);
	}
	
	//
	dll.assign(100, 1000);
	dll.reverse();
}

//
int main()
{
	//
	cout << "Hello, my name is Quiche Hollandaise!" << endl;
	
	//
	leaker();
	
	return 0;
}

