

//
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>


//
#include "MyVector.hpp"
#include "puhp-tests/PuhPTests.hpp"


//
using std::cout, std::cin, std::endl;
using std::string, std::to_string;
using std::vector;


//
using
	PuhPTests::Tests,
	PuhPTests::Test
	;


//
using
	CPSC131::MyVector::MyVector
	;



//	Proto
void preventPrototypeTampering();
MyVector<int> makeVector(size_t count = 100, bool random = false);
std::vector<int> myVectorToStdVector(const MyVector<int>& v);
bool checkIntegerVectorsEqual(const MyVector<int>& v1, const MyVector<int>& v2);
bool checkIntegerVectorsEqual(const MyVector<int>& v1, const std::vector<int>& v2);
void printVector(const MyVector<int>& v, string label = "NoLabel");
void testFreePoint(Tests& tests);
void testBasicCapacity(Tests& tests);
void testPushBack(Tests& tests);
void testPopBack(Tests& tests);
void testClear(Tests& tests);
void testGrowShrink(Tests& tests);
void testReserve(Tests& tests);
void testRanges(Tests& tests);
void testCopying(Tests& tests);
void testErase(Tests& tests);
void testDestructor(Tests& tests);
void testEmpty(Tests& tests);
void testPointerStealing(Tests& tests);
void testMemoryLeaks(Tests& tests);


class MyDTORHelper
{
	public:
		MyDTORHelper() {}
		MyDTORHelper(bool * b)
		{
			this->the_bool_ = b;
			if ( this->the_bool_ != nullptr ) {
				(*this->the_bool_) = false;
			}
		}
		MyDTORHelper(const MyDTORHelper& other)
		{
			this->the_bool_ = other.the_bool_;
		}
		~MyDTORHelper()
		{
			if ( this->the_bool_ != nullptr ) {
				(*this->the_bool_) = true;
			}
		}
	private:
		bool * the_bool_ = nullptr;
};

//
int main()
{
	//
	Tests tests(50);
	
	//
	preventPrototypeTampering();
	
	//
	std::vector<std::function<void(Tests&)>> fs = {
		testFreePoint,
		testBasicCapacity,
		testPushBack,
		testPopBack,
		testClear,
		testGrowShrink,
		testReserve,
		testRanges,
		testErase,
		testCopying,
		testEmpty,
		testDestructor,
		testPointerStealing,
		testMemoryLeaks
	};
	
	//
	for ( auto f : fs ) {
		f(tests);
	}
	
	//
	tests.setResultsFileName("results-cpp.json");
	tests.run();
	
	//
	cout << "Tests complete" << endl;
	
	return 0;
}


//
void preventPrototypeTampering()
{
	//	MyVector
	{
		//
		MyVector<int> t;
		
		//	Getters
		{
			size_t (MyVector<int>::* a)(void) const;
			a = &MyVector<int>::size;
			a = &MyVector<int>::capacity;
			if (a) {}
			
			bool (MyVector<int>::* b)(void) const;
			b = &MyVector<int>::empty;
			if (b) {}
			
			int& (MyVector<int>::* c)(size_t) const;
			c = &MyVector<int>::at;
			if (c) {}
		}
		
		//	Setters
		{
			
			void (MyVector<int>::* a)(size_t);
			a = &MyVector<int>::reserve;
			if (a) {}
			
			int& (MyVector<int>::* b)(size_t, const int&);
			b = &MyVector<int>::set;
			if (b) {}
			
			int& (MyVector<int>::* c)(const int&);
			c = &MyVector<int>::push_back;
			if (c) {}
			
			int (MyVector<int>::* d)(void);
			d = &MyVector<int>::pop_back;
			if (d) {}
			
			int& (MyVector<int>::* e)(size_t, const int&);
			e = &MyVector<int>::insert;
			if (e) {}
			
			int (MyVector<int>::* f)(size_t);
			f = &MyVector<int>::erase;
			if (f) {}
			
			void (MyVector<int>::* g)();
			g = &MyVector<int>::clear;
			if (g) {}
		}
	}
}


//
MyVector<int> makeVector(size_t count, bool random)
{
	MyVector<int> v;
	PuhPTests::Random rand;
	
	for ( size_t i = 0; i < count; i++ ) {
		
		int val;
		
		if ( random ) {
			val = rand.get(0, 1000000000);
		}
		else {
			val = i * 2 - (count / 2);
		}
		
		v.push_back(val);
	}
	
	return v;
}

//
std::vector<int> myVectorToStdVector(const MyVector<int>& v)
{
	std::vector<int> sv;
	
	//
	for ( size_t i = 0; i < v.size(); i++ ) {
		sv.push_back( v[i] );
	}
	
	return sv;
}

//
bool checkIntegerVectorsEqual(const MyVector<int>& v1, const MyVector<int>& v2)
{
	//
	if ( v1.size() != v2.size() ) {
		return false;
	}
	
	for ( size_t i = 0; i < v1.size(); i++ ) {
		if ( v1.at(i) != v2.at(i) ) {
			return false;
		}
	}
	
	return true;
}

//
bool checkIntegerVectorsEqual(const MyVector<int>& v1, const std::vector<int>& v2)
{
	//
	if ( v1.size() != v2.size() ) {
		return false;
	}
	
	for ( size_t i = 0; i < v1.size(); i++ ) {
		if ( v1.at(i) != v2.at(i) ) {
			return false;
		}
	}
	
	return true;
}

//
void printVector(const MyVector<int>& v, string label)
{
	if ( !label.empty() ) {
		cout << label << endl;
	}
	for (size_t i = 0; i < v.size(); i++) {
		cout << v.at(i) << endl;
	}
	cout << endl;
}

//
void testFreePoint(Tests& tests)
{
	//
	auto t = tests.createTest("Free point test(s)");
	
	//
	t->setFixedPointsPossible(1);
	
	//
	t->assertTrue(true, 1, "Free point for trying.");
}

//
void testPushBack(Tests& tests)
{
	//
	auto t = tests.createTest("push_back");
	
	//
	t->setFixedPointsPossible(10);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Checking capacity growth while pushing
	t->assertNoException(
		[t]()
		{
			{
				MyVector<int> v;
				v.push_back(1);
				t->assertEqual(v.capacity(), MyVector<int>::DEFAULT_CAPACITY, 1, "Push back shouldn't shrink capacity.");
			}
			
			{
				auto v = makeVector(500);
				t->assertEqual(v.size(), 500ULL, 1, "Size should be 500 after push_back 500 elements.");
				t->assertEqual(v.capacity(), 512ULL, 1, "Check capacity");
				for ( int i : {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) {
					v.push_back(i);
				}
				t->assertEqual(v.capacity(), 512ULL, 1, "Check capacity");
				v.push_back(5);
				t->assertEqual(v.capacity(), 1024ULL, 1, "Check capacity");
				t->assertEqual(v.size(), 513ULL, 1, "Size should be 513 after additional pushes");
			}
			
		}, 1, "Checking growth during pushes"
	);
	
	//
	t->assertNoException(
		[t]()
		{
			auto v = makeVector(1100);
			t->assertEqual(v.size(), 1100ULL, 1, "Size should be 1100 after push_back 1100 elements.");
			t->assertEqual(v.capacity(), 2048ULL, 1, "Capacity should be 2048 after pushing back 110 elements.");
			
		}, 1, "Check capacity after larger number of pushed"
	);
}

//
void testPopBack(Tests& tests)
{
	//
	auto t = tests.createTest("pop_back");
	
	//
	t->setFixedPointsPossible(7);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Checking capacity while popping
	t->assertNoException(
		[t]()
		{
			{
				MyVector<int> v;
				v.push_back(1);
				v.reserve(10000);
				v.pop_back();
				t->assertEqual(v.capacity(), MyVector<int>::MINIMUM_CAPACITY, 1, "One push_back followed by reserve(10000) followed by one pop_back of a vector should result in minimum capacity. i.e., Shrinking logic should find the most appropriate capacity.");
			}
			
			{
				auto v = makeVector(1000);
				for ( size_t i = 0; i < 659; i++ ) {
					v.pop_back();
				}
				t->assertEqual(v.capacity(), 1024ULL, 1, "Check capacity after pops");
				t->assertEqual(v.size(), 341ULL, 1, "Size should be 341 after popping 659 times from a 1000 size vector.");
				
				v.pop_back();
				t->assertEqual(v.capacity(), 512ULL, 1, "Check capacity after edge case pop");
				t->assertEqual(v.size(), 340ULL, 1, "Size should decrease by one after a pop");
			}
			
		}, 1, "Checking capacity and size while popping"
	);
	
	//	Make sure popped values are correct
	t->assertNoException(
		[t]()
		{
			auto v = makeVector(1000, true);
			auto vs = myVectorToStdVector(v);
			
			size_t sz = v.size();
			for ( size_t i = 0; i < sz; i++ ) {
				
				int val1 = v.pop_back();
				int val2 = vs[ vs.size() - 1 ];
				vs.pop_back();
				
				if ( val1 != val2 ) {
					t->assertEqual(val1, val2, 1, "Checking popped values are correct.");
				}
			}
			
		}, 1, "Check for correct popped values"
	);
}

//
void testClear(Tests& tests)
{
	//
	auto t = tests.createTest("Clear");
	
	//
	t->setFixedPointsPossible(5);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			PuhPTests::Random rand;
			
			{
				//	Minimum'ed then cleared vector should have cap == default
				MyVector<int> v(0);
				v.clear();
				t->assertEqual(v.capacity(), MyVector<int>::DEFAULT_CAPACITY, 1, "Capacity should be defaulted after clear().");
			}
			{
				//	Large then cleared vector should have cap == default
				auto v = makeVector(500);
				v.clear();
				t->assertEqual(v.capacity(), MyVector<int>::DEFAULT_CAPACITY, 1, "Capacity should be defaulted after clear().");
			}
			
			{
				//	Vector should still function after multiple clears
				auto v1 = makeVector(500);
				std::vector<int> v2;
				v1.clear();
				v1.clear();
				for ( size_t i = 0; i < 10000; i++ ) {
					int r = rand.get(0, 1000000000);
					v1.push_back(r);
					v2.push_back(r);
				}
				t->assertTrue(checkIntegerVectorsEqual(v1, v2), 1, "Clear shouldn't corrupt vectors");
				v1.clear();
				v1.clear();
				v2.clear();
				for ( size_t i = 0; i < 10000; i++ ) {
					int r = rand.get(0, 1000000000);
					v1.push_back(r);
					v2.push_back(r);
				}
				t->assertTrue(checkIntegerVectorsEqual(v1, v2), 1, "Clear shouldn't corrupt vectors");
			}
			
		}, 1, "Clear tests"
	);
}

//
void testGrowShrink(Tests& tests)
{
	//
	auto t = tests.createTest("Grow/Shrink");
	
	//
	t->setFixedPointsPossible(29);
	t->setNormalizedPointsPossibleTarget(10);
	
	//
	t->assertNoException(
		[t]()
		{
			
			for ( int growShrinkType = 0; growShrinkType <= 1; growShrinkType++ ) {
				
				std::string typeLabel;
				if ( growShrinkType == 0 ) {
					typeLabel = "push/pop";
				}
				else if ( growShrinkType == 1) {
					typeLabel = "insert/erase";
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				
				auto v = makeVector(0);
				t->assertEqual(v.size(), 0ULL, 1, "[" + typeLabel + "] Size should be 0 initially.");
				t->assertEqual(v.capacity(), v.DEFAULT_CAPACITY, 1, "[" + typeLabel + "] Check initial capacity.");
				
				//	Grow
				for ( int i = 0; i < 1023; i++ ) {
					if ( growShrinkType == 0 ) {
						v.push_back(i * 3);
					}
					else if ( growShrinkType == 1 ) {
						v.insert(0, i * 3);
					}
					else {
						throw std::runtime_error("Invalid growShrinkType in tester");
					}
				}
				t->assertEqual(v.capacity(), 1024ULL, 1, "[" + typeLabel + "] Check capacity after initial growth.");
				t->assertEqual(v.capacity(), 1024ULL, 1, "[" + typeLabel + "] Check capacity after initial growth.");
				
				//
				if ( growShrinkType == 0 ) {
					v.push_back(44444);
				}
				else if ( growShrinkType == 1 ) {
					v.insert(0, 44444);
				}
				else {
					throw std::runtime_error("[" + typeLabel + "] Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 1024ULL, 1, "[" + typeLabel + "] Check edge-case capacity while growing.");
				
				//
				if ( growShrinkType == 0 ) {
					v.push_back(55555);
				}
				else if ( growShrinkType == 1 ) {
					v.insert(0, 55555);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 2048ULL, 1, "[" + typeLabel + "] Check edge-case capacity while growing.");
				
				//
				if ( growShrinkType == 0 ) {
					v.push_back(66666);
				}
				else if ( growShrinkType == 1 ) {
					v.insert(0, 66666);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 2048ULL, 1, "[" + typeLabel + "] Check edge-case capacity while growing.");
				
				//	Shrink
				for ( int i = 0; i < 343; i++ ) {
					if ( growShrinkType == 0 ) {
						v.pop_back();
					}
					else if ( growShrinkType == 1 ) {
						v.erase(0);
					}
					else {
						throw std::runtime_error("Invalid growShrinkType in tester");
					}
				}
				t->assertEqual(v.capacity(), 2048ULL, 1, "[" + typeLabel + "] Check edge-case capacity at size " + to_string(v.size()) + " (shrink).");
				
				//
				if ( growShrinkType == 0 ) {
					v.pop_back();
				}
				else if ( growShrinkType == 1 ) {
					v.erase(0);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 2048ULL, 1, "[" + typeLabel + "] Check edge-case capacity at size " + to_string(v.size()) + " (shrink).");
				
				//
				if ( growShrinkType == 0 ) {
					v.pop_back();
				}
				else if ( growShrinkType == 1 ) {
					v.erase(0);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 1024ULL, 1, "[" + typeLabel + "] Check edge-case capacity at size " + to_string(v.size()) + " (shrink).");
				
				//	Grow again
				for ( int i = 0; i < 20000; i++ ) {
					if ( growShrinkType == 0 ) {
						v.push_back(i * 3);
					}
					else if ( growShrinkType == 1 ) {
						v.insert(0, i * 3);
					}
					else {
						throw std::runtime_error("Invalid growShrinkType in tester");
					}
				}
				t->assertEqual(v.capacity(), 32768ULL, 1, "[" + typeLabel + "] Check edge-case capacity after second grow.");
				
				//	Shrink again
				for ( int i = 0; i < 9759; i++ ) {
					if ( growShrinkType == 0 ) {
						v.pop_back();
					}
					else if ( growShrinkType == 1 ) {
						v.erase(0);
					}
					else {
						throw std::runtime_error("Invalid growShrinkType in tester");
					}
				}
				t->assertEqual(v.capacity(), 32768ULL, 1, "[" + typeLabel + "] Check edge-case capacity (shrink).");
				
				//
				if ( growShrinkType == 0 ) {
					v.pop_back();
				}
				else if ( growShrinkType == 1 ) {
					v.erase(0);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 16384ULL, 1, "[" + typeLabel + "] Check edge-case capacity (shrink).");
				
				//
				if ( growShrinkType == 0 ) {
					v.pop_back();
				}
				else if ( growShrinkType == 1 ) {
					v.erase(0);
				}
				else {
					throw std::runtime_error("Invalid growShrinkType in tester");
				}
				t->assertEqual(v.capacity(), 16384ULL, 1, "[" + typeLabel + "] Check edge-case capacity (shrink).");
			}
			
		}, 1, "Grow/Shrink tests"
	);
}

//
void testReserve(Tests& tests)
{
	//
	auto t = tests.createTest("Reserve");
	
	//
	t->setFixedPointsPossible(7);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Reserve grow/shrink
	t->assertNoException(
		[t]()
		{
			//	Make a MyVector with a mirror to a normal std::vector
			auto v = makeVector(1000);
			std::vector<int> sv;
			for ( size_t i = 0; i < v.size(); i++ ) {
				sv.push_back(v.at(i));
			}
			
			//	Check reserve as an increase
			v.reserve(10000);
			t->assertEqual(v.capacity(), 10000ULL, 1, "Capacity should match new 10000 value");
			t->assertTrue(checkIntegerVectorsEqual(v, sv), 1, "reserve() shouldn't have corrupted vector data");
			
			//	Check reserve does not cause a shrink
			v.reserve(1000);
			t->assertEqual(v.capacity(), 10000ULL, 1, "reserve() requests should not result in less capacity than already held");
			
		}, 1, "Reserve grow shrink tests"
	);
	
	//	No capacity change detected while pushing toward a large reserve
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector(1);
			t->assertEqual(v.capacity(), MyVector<int>::DEFAULT_CAPACITY, 0, "Just double checking a vector of size=1 would have default capacity.");
			
			//
			v.reserve(20000);
			t->assertEqual(v.capacity(), 20000ULL, 1, "Call to reserve of higher capacity should result in exactly that capacity.");
			
			//
			for ( size_t i = 0; i < 9999; i++ ) {
				v.push_back(i);
			}
			
			t->assertEqual(v.capacity(), 20000ULL, 1, "Pushing along the way to a large reserved capacity should not reduce capacity.");
			
		}, 1, "Checking capacity doesn't change while pushing toward large reserve"
	);
}

//
void testBasicCapacity(Tests& tests)
{
	//
	auto t = tests.createTest("Basic capacity");
	
	//
	t->setFixedPointsPossible(3);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Minimum capacity
	t->assertNoException(
		[t]()
		{
			//	Minimum cap not tampered
			t->assertEqual(MyVector<int>::MINIMUM_CAPACITY, 8ULL, 1, "Minimum capacity should not have been tampered.");
			
			{
				MyVector<int> v(0);
				t->assertEqual(v.capacity(), MyVector<int>::MINIMUM_CAPACITY, 1, "Capacity should be no less than the minimum.");
			}
			
		}, 1, "Minimum capacity tests"
	);
}

//
void testRanges(Tests& tests)
{
	//
	auto t = tests.createTest("Range");
	
	//
	t->setFixedPointsPossible(24);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Try to grab invalid index
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.at(-1);
		}, 1, "Grab invalid index"
	);
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.at(100);
		}, 1, "Grab invalid index"
	);
	//	Try to grab valid index!
	t->assertNoException(
		[t]()
		{
			auto v = makeVector(100);
			t->assertEqual(v.at(0), -50, 1, "Check for correct number at index 0");
			t->assertEqual(v.at(35), 20, 1, "Check for correct number at index 35");
			t->assertEqual(v.at(99), 148, 1, "Check for correct number at index 99");
			
		}, 1, "Grab some values"
	);
	
	//	Try to insert at invalid index
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.insert(-1, 1);
		}, 1, "Insert at invalid index"
	);
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.insert(101, 1);
		}, 1, "Insert at invalid index 101"
	);
	
	//	Try to insert at valid index and check the result
	t->assertNoException(
		[t]()
		{
			auto v = makeVector(100);
			v.insert(77, 22);
			t->assertEqual(v.at(76), 102, 1, "Check for correct number at index 76");
			t->assertEqual(v.at(77), 22, 1, "Check for correct number at index 77");
			t->assertEqual(v.at(78), 104, 1, "Check for correct number at index 78");
		}, 1, "Grab invalid index"
	);
	
	//	Try to erase at invalid index
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.erase(-1);
		}, 1, "Erase at invalid index"
	);
	t->assertException(
		[]()
		{
			auto v = makeVector(100);
			v.erase(100);
		}, 1, "Erase at invalid index"
	);
	
	//	Check that the [] operator works
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector();
			t->assertEqual(v[1], -48, 1, "Check access operator [] at index 1");
			t->assertEqual(v[27], 4, 1, "Check access operator [] at index 27");
			t->assertEqual(v[97], 144, 1, "Check access operator [] at index 97");
			
		}, 1, "Check access operator"
	);
	
	//	Check that the [] operator throws for invalid index -1
	t->assertException(
		[]()
		{
			auto v = makeVector();
			v[-1];
			
		}, 1, "Check access operator throws for index -1"
	);
	//	Check that the [] operator throws for invalid index 100
	t->assertException(
		[]()
		{
			auto v = makeVector();
			v[100];
			
		}, 1, "Check access operator throws for index 100"
	);
	
	// Check pop_back
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector(1);
			v.pop_back();
			t->assertTrue(v.empty(), 1, "Single-element vector should become empty after pop_back");
			
			//
			v.push_back(1);
			v.push_back(2);
			v.pop_back();
			t->assertTrue(v.size() == 1ULL && v[0] == 1, 1, "Checking pop_back logic");
			
		}, 1, "Valid pop_back operations shouldn't throw an exception"
	);
	t->assertException(
		[]()
		{
			auto v = makeVector(0);
			v.pop_back();
			
		}, 1, "Pop back should throw on an empty vector"
	);
}

//
void testCopying(Tests& tests)
{
	//
	auto t = tests.createTest("Copy");
	
	//
	t->setFixedPointsPossible(7);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			auto v1 = makeVector();
			MyVector<int> v2, v3(v1);
			
			//
			v2 = v1;
			
			//
			t->assertTrue(checkIntegerVectorsEqual(v1, v2), 1, "Assignment operator (equality check)");
			t->assertTrue(v1.size() == v2.size(), 1, "Assignment operator (size)");
			t->assertTrue(v1.capacity() == v2.capacity(), 1, "Assignment operator (size)");
			
			//
			t->assertTrue(checkIntegerVectorsEqual(v1, v3), 1, "Copy constructor (equality check)");
			t->assertTrue(v1.size() == v3.size(), 1, "Copy constructor (size)");
			t->assertTrue(v1.capacity() == v3.capacity(), 1, "Copy constructor (size)");
			
		}, 1, "Copy tests"
	);
}

//
void testErase(Tests& tests)
{
	//
	auto t = tests.createTest("Erase");
	
	//
	t->setFixedPointsPossible(10);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector(100);
			
			//
			auto erased_value_1 = v.erase(47);
			t->assertTrue(v.size() == 99ULL, 1, "Erase an element in the middle (size)");
			t->assertTrue(v.capacity() == 128ULL, 1, "Erase an element in the middle (capacity)");
			t->assertEqual(erased_value_1, 44, 1, "Erased element should be returned");
			t->assertEqual(v.at(88), 128, 1, "Erase an element in the middle (check another element)");
			
			//
			auto erased_value_2 = v.erase(0);
			t->assertTrue(v.size() == 98ULL, 1, "Erase first element (size)");
			t->assertTrue(v.capacity() == 128ULL, 1, "Erase first element (capacity)");
			t->assertEqual(erased_value_2, -50, 1, "Erased element should be returned");
			t->assertEqual(v.at(88), 130, 1, "Erase first element (check another element)");
			
		}, 1, "First half of deletion tests"
	);
	
	//
	t->assertException(
		[]()
		{
			//
			auto v = makeVector(1);
			
			//
			v.erase(0);
			v.erase(0);
			
		}, 1, "Erasing 2 elements from a 1 element vector should throw exception"
	);
}

//
void testDestructor(Tests& tests)
{
	//
	auto t = tests.createTest("Destructor");
	
	//
	t->setFixedPointsPossible(5);
	t->setNormalizedPointsPossibleTarget(5);
	
	//	Do stuff
	t->assertNoException(
		[t]()
		{
			bool
				dtor_activated1,
				dtor_activated2,
				dtor_activated3,
				dtor_activated4,
				dtor_activated5
				;
			
			//	Calling MyVector DTOR multiple times shouldn't crash
			{
				t->log("Calling vector's DTOR multiple times shouldn't crash");
				auto v = makeVector(500);
				v.~MyVector();
				v.~MyVector();
				v.~MyVector();
				v.~MyVector();
				v.~MyVector();
			}
			
			//	clear() should call DTORs
			{
				//
				MyVector<MyDTORHelper> v;
				v.push_back(MyDTORHelper(&dtor_activated1));
				v.push_back(MyDTORHelper(&dtor_activated2));
				v.push_back(MyDTORHelper(&dtor_activated3));
				v.push_back(MyDTORHelper(&dtor_activated4));
				v.push_back(MyDTORHelper(&dtor_activated5));
				
				dtor_activated1 = false;
				dtor_activated2 = false;
				dtor_activated3 = false;
				dtor_activated4 = false;
				dtor_activated5 = false;
				v.clear();
				t->assertTrue(
					(
						dtor_activated1
						&& dtor_activated2
						&& dtor_activated3
						&& dtor_activated4
						&& dtor_activated5
					),
					1,
					"clear() should call element DTOR"
				);
			}
			
			//	pop_back() should call element DTOR
			{
				MyVector<MyDTORHelper> v(0);
				v.push_back(MyDTORHelper(&dtor_activated1));
				v.push_back(MyDTORHelper(&dtor_activated2));
				v.push_back(MyDTORHelper(&dtor_activated3));
				v.push_back(MyDTORHelper(&dtor_activated4));
				v.push_back(MyDTORHelper(&dtor_activated5));
				
				dtor_activated1 = false;
				dtor_activated2 = false;
				dtor_activated3 = false;
				dtor_activated4 = false;
				dtor_activated5 = false;
				v.pop_back();
				t->assertTrue(
					(
						!dtor_activated1
						&& !dtor_activated2
						&& !dtor_activated3
						&& !dtor_activated4
						&& dtor_activated5
					),
					1,
					"pop_back() should call element DTOR"
				);
			}
			
			//	erase(index) should call element DTOR
			{
				//
				MyVector<MyDTORHelper> v(0);
				v.push_back(MyDTORHelper(&dtor_activated1));
				v.push_back(MyDTORHelper(&dtor_activated2));
				v.push_back(MyDTORHelper(&dtor_activated3));
				v.push_back(MyDTORHelper(&dtor_activated4));
				v.push_back(MyDTORHelper(&dtor_activated5));
				
				dtor_activated1 = false;
				dtor_activated2 = false;
				dtor_activated3 = false;
				dtor_activated4 = false;
				dtor_activated5 = false;
				v.erase(2);
				t->assertTrue
				(
					(
						!dtor_activated1
						&& !dtor_activated2
						&& dtor_activated3
						&& !dtor_activated4
						&& !dtor_activated5
					),
					1,
					"erase() should call element DTOR"
				);
			}
			
			//	set() should also call DTOR
			{
				//
				MyVector<MyDTORHelper> v(0);
				v.push_back(MyDTORHelper(&dtor_activated1));
				v.push_back(MyDTORHelper(&dtor_activated2));
				v.push_back(MyDTORHelper(&dtor_activated3));
				v.push_back(MyDTORHelper(&dtor_activated4));
				v.push_back(MyDTORHelper(&dtor_activated5));
				
				dtor_activated1 = false;
				dtor_activated2 = false;
				dtor_activated3 = false;
				dtor_activated4 = false;
				dtor_activated5 = false;
				v.set(3, MyDTORHelper(nullptr));
				t->assertTrue(
					(
						!dtor_activated1
						&& !dtor_activated2
						&& !dtor_activated3
						&& dtor_activated4
						&& !dtor_activated5
					),
					1,
					"set() should call element DTOR"
				);
			}
			
		}, 1, "DTOR Tests"
	);
}

//
void testEmpty(Tests& tests)
{
	//
	auto t = tests.createTest("Empty");
	
	//
	t->setFixedPointsPossible(5);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector(0);
			
			//
			t->assertTrue(v.empty(), 1, "empty() should work with empty vector");
			
			//
			v.push_back(1);
			t->assertFalse(v.empty(), 1, "empty() should not work with non-empty vector");
			
			//
			v.erase(0);
			t->assertTrue(v.empty(), 1, "empty() should work with empty vector (again)");
			
			//
			v.push_back(1);
			v.push_back(1);
			v.push_back(1);
			v.push_back(1);
			v.push_back(1);
			v.clear();
			t->assertTrue(v.empty(), 1, "empty() should work with empty vector (again)");
			
		}, 1, "Empty tests"
	);
}

//
void testPointerStealing(Tests& tests)
{
	//
	auto t = tests.createTest("Pointer Stealing");
	
	//
	t->setFixedPointsPossible(11);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			auto v = makeVector(1);
			for ( int i = 0; i < 1000; i++ ) {
				v.push_back(i * 5);
			}
			auto u = v;
			
			//
			u[333]--;
			
			//
			t->assertFalse(v[333] == u[333], 10, "Checking for copying that engages in pointer-stealing");
			
		}, 1, "Pointer stealing"
	);
}

//
void testMemoryLeaks(Tests& tests)
{
	//
	auto t = tests.createTest("Memory Leaks");
	
	//
	t->setFixedPointsPossible(11);
	t->setNormalizedPointsPossibleTarget(5);
	
	//
	t->assertNoException(
		[t]()
		{
			//
			string stdout, stderr, message;
			bool leakCheckResult = PuhPTests::Memory::checkMemoryLeaks
			(
				{"make", "leak-checker"},
				"leak-checker",
				stdout, stderr, message
			);
			
			//
			if ( !leakCheckResult ) {
				t->log("Leak Check Result :: STDOUT\n" + stdout);
				t->log("Leak Check Result :: STDERR\n" + stderr);
			}
			t->assertTrue(leakCheckResult, 10, "Checking for memory leaks: " + message);
			
		}, 1, "Memory leaks"
	);
}



