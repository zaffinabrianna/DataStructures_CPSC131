
/**
 * You don't have to modify this source file, but can if you want.
 * This will not be used for grading, so you can use it to debug your
 * vector class.
 * This is the program that runs with "make run"
 */

///	Your welcome
#include <iostream>
#include "MyVector.hpp"

///	Your welcome
using namespace CPSC131::MyVector;
using std::cout, std::endl;

//
int main()
{
	//
	cout << "Hello! Maybe use this source file for debugging?" << endl;
	
	MyVector<int> vecTest(1024);
	
	for (int i = 0; i < 2000; ++i)
	{
	  vecTest.push_back(i);
	}
	
	for (int i = 0; i < 1900; ++i)
	{
	vecTest.pop_back();
	}
	
	return 0;
}


