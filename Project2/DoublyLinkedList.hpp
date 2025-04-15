#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP

/**
 * Name: Brianna Zaffina
 */

/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add helper methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom and DLL !
 */
namespace CPSC131::DoublyLinkedList
{
	/**
	 * Implement our DoublyLinkedList class !
	 */
	template <class T>
	class DoublyLinkedList
	{
		public:
			
			/**
			 * Node class, representing a single item in our linked list
			 */
			// TODO: Complete all class methods
			class Node
			{
				public:
					
					/// CTORS
					/// Member initialization lists?
					Node() : element_(), prev_(nullptr), next_(nullptr){}
					Node(T element) : element_(element), prev_(nullptr), next_(nullptr){}
					Node(T element, Node* prev, Node* next) : element_(element), prev_(prev), next_(next){}
					
					/// Set the pointer to the previous element
					void setPrevious(Node* prev) {prev_ = prev;}
					
					/// Set the pointer to the previous element
					void setPrev(Node* prev) {prev_ = prev;}
					
					/// Get a pointer to the previous element
					Node* getPrevious() {return prev_;}
					
					/// Get a pointer to the previous element
					Node* getPrev() {return prev_;}
					
					/// Set the pointer to the next node
					void setNext(Node* next) {next_ = next;}
					
					/// Get a pointer to the next node
					Node* getNext() {return next_;}
					
					/// Set the element this node holds
					void setElement(T element) {element_ = element;}
					
					/// Get the element this node holds
					///	YOUR WELCOME
					T& getElement() { return this->element_; }
					
					/// Return a reference to the element
					///	YOUR WELCOME
					T& operator*() { return this->element_; }
					
				private:
					T element_;
					Node* prev_;
					Node* next_;
			};
			
			/**
			 * Nested Iterator class.
			 * This allows user code to refer to the Iterator's type as:
			 * 
			 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
			 * 
			 * (as opposed to specifying the template argument two times)
			 */
			class Iterator
			{
				public:
					
					///	Constructor that does nothing; YOUR WELCOME
					Iterator()
					{
						/// yw
					}
					
					///	Constructor taking a head and tail pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail) : head_(head), tail_(tail)
					{
						this->cursor_ = this->end();	/// yw
					}
					
					///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
					
					///	Get a pointer to the head node, or end() if this list is empty
					Node* begin()
					{
						if (head_ == nullptr) //since head_ is set to nullptr orginally, it will check to see if it is still this (therefore no info)
						{
						return end();
						}
						
						else //if it isnt, itll return the head_ node
						{
						return this->head_; //this-> since using same name
						}
						
					}
					
					///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
					Node* end()
					{
					      return nullptr;
					}
					
					///	Get the node to which this iterator is currently pointing
					Node* getCursor()
					{
						return this->cursor_; //this since same name
					}
					
					///	Return true if this iterator has hit its end; false otherwise
					/// YOUR WELCOME
					bool isAtEnd()
					{
						return this->cursor_ == nullptr;
					}
					
					/**
					 * Assignment operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator=(const Iterator& other)
					{
					      head_ = other.head_;
					      tail_ = other.tail_;
					      cursor_ = other.cursor_;
					      
					      return *this;
					}
					
					///	Comparison operator
					bool operator==(const Iterator& other)
					{
						return cursor_ == other.cursor_; //Dont need to compare everything else since iterator is just comparing the node they are pointing to
					}
					///	Inequality comparison operator
					bool operator!=(const Iterator& other)
					{
						return cursor_ != other.cursor_; //Same issue as above
					}
					
					/**
					 * Addition operator
					 */
					Iterator operator +(size_t add)
					{
					  Iterator temp = *this;
						for (size_t i = 0; i < add && temp.cursor_ != nullptr; i++)
						{
						temp.cursor_ = temp.cursor_->getNext();
						}
						
						return temp;
					}
					
					/**
					 * Subtraction operator
					 */
					Iterator operator -(size_t subtract)
					{
					Iterator temp = *this;
						for (size_t i = 0; i < subtract && temp.cursor_ != nullptr; i++)
						{
						  temp.cursor_ = temp.cursor_->getPrev();
						}
						  
						return temp;
					}
					
					/**
					 * Prefix increment operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator++()
					{
						if (cursor_ != nullptr)
						{
							cursor_ = cursor_->getNext();
						}
						
						return *this;
					}
					
					/**
					 * Postfix increment
					 * Return a copy of this Iterator, BEFORE it was modified
					 */
					Iterator operator++(int)
					{
						Iterator temp = *this;
						++(*this); //Uses previous function
						
						return temp; //Returns the orginal output
					}
					
					/**
					 * Prefix decrement operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator--()
					{
						if (cursor_ != nullptr)
						{
						cursor_ = cursor_->getPrev();
						}
					
						return *this;
					}
					
					/**
					 * Postfix decrement operator
					 * Return a copy of this Iterator BEFORE it was modified
					 */
					Iterator operator--(int)
					{
						Iterator temp = *this;
						--(*this); 
						
						return temp;
					}
					
					/**
					 * AdditionAssignment operator
					 * Return a copy of the current iterator, after modification
					*/
					Iterator operator +=(size_t add)
					{
					      for (size_t i = 0; i < add && cursor_ != nullptr; i++)
						{
						cursor_ = cursor_->getNext();
						}
						
						return *this;
					}
					/**
					 * SubtractionAssignment operator
					 * Return a copy of the current iterator, after modification
					 */
					Iterator operator -=(size_t add)
					{
						for (size_t i = 0; i < add && cursor_ != nullptr; i++)
						{
						cursor_ = cursor_->getPrev();
						}
						
						return *this;
					}
					
					/**
					 * AdditionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator +=(int add)
					{
						for (int i = 0; i < add && cursor_ != nullptr; i++)
						{
						cursor_ = cursor_->getNext();
						}
						
						return *this;
					}
					
					/**
					 * SubtractionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator -=(int subtract)
					{
						for (int i = 0; i < subtract && cursor_ != nullptr; i++)
						{
						cursor_ = cursor_->getPrev();
						}
						
						return *this;
					}
					
					/**
					 * Dereference operator returns a reference to the ELEMENT contained with the current node
					 */
					T& operator*()
					{
						return cursor_->getElement();
					}
				
				private:
					
					/// Pointer to the head node
					Node* head_ = nullptr;
					
					/// Pointer to the tail node
					Node* tail_ = nullptr;
					
					/**
					 * Pointer to the cursor node.
					 */
					Node* cursor_ = nullptr;
				
				friend class DoublyLinkedList;
			};
			
			/// Default constructor
			DoublyLinkedList()
			{
					head_ = nullptr;
			        tail_ = nullptr;
			        size_ = 0;
			}
			
			///	Copy Constructor
			DoublyLinkedList(DoublyLinkedList& other)
			{
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
				
				for (Node* current = other.head_; current != nullptr; current = current->getNext())
				{
				push_back(current->getElement());
				}
			}
			
			/// DTOR
			~DoublyLinkedList()
			{
				clear();
			}
			
			/**
			 * Clear the list and assign the same value, count times.
			 * 
			 * Example:
			 *   T is an int
			 *   count is 5
			 *   value = 3
			 * 
			 * Our list would become:
			 *   {3, 3, 3, 3, 3}
			 */
			void assign(size_t count, const T& value)
			{
			    clear();
			        
				for (size_t i = 0; i < count; i++)
				{
				push_back(value);
				}
			}
			
			/**
			 * Clear the list and assign values from another list.
			 * The 'first' iterator points to the first item copied from the other list.
			 * The 'last' iterator points to the last item copied from the other list.
			 * 
			 * Example:
			 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
			 * 	Suppose first points to the 4 node
			 *	Suppose last points to the 7 node
			 * 	We should end up with our list becoming: {4, 3, 2, 7}
			 *
			 * If the user code sends out-of-order iterators,
			 * 	just copy from 'first' to the end of the source list
			 * 
			 * Example:
			 *  If we have the same source list {8, 4, 3, 2, 7, 1},
			 *  and first points to the 7 node,
			 *  and last points to the 4 node,
			 *  we would end up with: {7, 1}
			 */
			void assign(Iterator first, Iterator last)
			{
				clear();
				
				Iterator temp = first;
				
				
				while((temp.getCursor() != nullptr) && (last.getCursor() == nullptr || temp.getCursor() != last.getCursor()->getNext())) // While the temp iterator isnt last and isnt at the end of the list
				{
				push_back(*temp); //push back the element that temp points to
				temp++; //go through uuntil temp is the last variable
				}
				
				/*if(temp == last) //When temp is equal to the last item in the list
				{
				push_back(*temp); //then push back into the list
				}*/
			      
			}
			
			/// Return a pointer to the head node, if any
			Node* head() const
			{
				return head_;
			}
			
			/// Return a pointer to the tail node, if any
			Node* tail() const
			{
				return tail_;
			}
			
			/**
			 * Return an iterator that points to the head of our list
			 */
			Iterator begin() const
			{
				return Iterator(this->head_, this->tail_, this->head_);
			}
			
			/**
			 * Return an iterator that points to the last element (tail) of our list
			 */
			Iterator last() const
			{
				return Iterator(head_, tail_, tail_);
			}
			
			/**
			 * Should return an iterator that represents being past the end of our nodes,
			 * or just that we are finished.
			 * 
			 * You can make this a nullptr or use some other scheme of your choosing,
			 * 	as long as it works with the logic of the rest of your implementations.
			 */
			Iterator end() const
			{
				return Iterator(head_, tail_, nullptr);
			}
			
			/**
			 * Returns true if our list is empty
			 */
			bool empty() const
			{
				return size_ == 0;
			}
			
			/**
			 * Returns the current size of the list
			 * 
			 * Should finish in constant time!
			 * (keep track of the size elsewhere)
			 */
			size_t size() const
			{
				return size_;
			}
			
			/**
			 * Clears our entire list, making it empty
			 */
			void clear()
			{
				Node* temp = head_;
				
				while (temp != nullptr)
				{
				Node* next = temp->getNext(); 
				delete temp;
				temp = next;
				}
				
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
			}
			
			/**
			 * Insert an element after the node pointed to by the pos Iterator
			 * 
			 * If the list is currently empty,
			 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
			 * 
			 * If the incoming iterator is this->end(),
			 *   insert the element as the new tail
			 * 
			 * Should return an iterator that points to the newly added node
			 */
			Iterator insert_after(Iterator pos, const T& value)
			{
				if (this->empty())
				{
				Node* newNode = new Node(value);
				
				this->head_ = newNode;
				this->tail_ = newNode;
				this->size_++;
				
				return Iterator(this->head_, this->tail_, newNode);
				}
				
				if(pos.isAtEnd())
				{
				  return push_back(value);
				}
				
				//Normal Case:
				Node* temp = pos.getCursor();
				
				Node* newNode = new Node(value);
				
				if (temp == nullptr)
				{
					throw std::range_error("Iterator is not valid.");
				}
				
				//Set them
				newNode->setPrev(temp);
				newNode->setNext(temp->getNext());
				
				if (temp->getNext() != nullptr)
				{
				temp->getNext()->setPrev(newNode);
				}

				if (temp == this->tail_)
				{
				this->tail_ = newNode;
				}
				
				temp->setNext(newNode);
				
				this->size_++;
				
				return Iterator(this->head_, this->tail_, newNode);

			}
			
			/**
			 * Insert a new element after the index pos.
			 * Should work with an empty list.
			 * 
			 * Should return an iterator pointing to the newly created node
			*/
			Iterator insert_after(size_t pos, const T& value)
			{
				if (this->empty())
				{
				Node* temp = new Node(value);
				this->head_ = temp;
				this->tail_ = temp;
				this->size_++;
				
				return Iterator(this->head_, this->tail_, temp);
				}
				
				if (pos > this->size_)
				{
				return push_back(value);
				}

				
				//idek why i named it search i used it to go through the loop but its not even searcihng too lazy to fix tbh.
				Node* search = this->head_;
				
				for (size_t i = 0; i < pos; i++)
				{
				search = search->getNext();
				}
				
				Node* temp = new Node(value);
				Node* nextNode = search->getNext();
				
				search->setNext(temp);
				temp->setPrev(search);
				
				if(nextNode != nullptr)
				{
				temp->setNext(nextNode);
				nextNode->setPrev(temp);
				}
				
				else
				{
				this->tail_ = temp;
				}
				
				this->size_++;
				
				return Iterator(this->head_, this->tail_, temp);
			}
			
			/**
			 * Erase the node pointed to by the Iterator's cursor.
			 * 
			 * If the 'pos' iterator does not point to a valid node,
			 * 	throw an std::range_error
			 * 
			 * Return an iterator to the node AFTER the one we erased,
			 * 	or this->end() if we just erased the tail
			 */
			Iterator erase(Iterator pos)
			{

				Node* tempErase = pos.getCursor();
				
				if (tempErase == nullptr)
				{
					throw std::range_error("Iterator does not point to a valid node");
				}
				
				if (tempErase == head_)
				{
					head_ = tempErase->getNext();
					
					if (head_ != nullptr)
					{
						head_->setPrev(nullptr);
					}
				}
				
				else
				{
					Node* prevNode = tempErase->getPrev();
					
					if (prevNode != nullptr)
					{
						prevNode->setNext(tempErase->getNext());
					}
				}
				
				if (tempErase == tail_)
				{
					tail_ = tempErase->getPrev();
					
					if (tail_ != nullptr)
					{
						tail_->setNext(nullptr);
					}
				}
				
				else
				{
					Node* nextNode = tempErase->getNext();
					if (nextNode != nullptr)
					{
						nextNode->setPrev(tempErase->getPrev());
					}
				}
				
				delete tempErase;
				size_--;
				
				if (head_ == nullptr)
				{
					return end();
				}
				
				Node* finalDest = (tail_ == nullptr) ? nullptr : head_;
				
				return Iterator(head_, tail_, finalDest);
			}
			
			/**
			 * Add an element just after the one pointed to by the 'pos' iterator
			 * 
			 * Should return an iterator pointing to the newly created node
			 */
			Iterator push_after(Iterator pos, const T& value)
			{
			
			    if (this->empty())
				{
				Node* newNode = new Node(value);
				
				this->head_ = newNode;
				this->tail_ = newNode;
				this->size_++;
				
				return Iterator(this->head_, this->tail_, newNode);
				}
				
				if(pos.isAtEnd())
				{
				  return push_back(value);
				}
				
				Node* temp = new Node(value);
				Node* tempNext = pos.getCursor()->getNext();
				
				pos.getCursor()->setNext(temp);
				temp->setPrev(pos.getCursor());
				temp->setNext(tempNext);
				
				if (tempNext != nullptr)
				{
				tempNext->setPrev(temp);
				}
				else
				{
				this->tail_ = temp;
				}
				
				size_++;
				
				return Iterator(this->head_, this->tail_, temp);
				
			}
			
			/**
			 * Add a new element to the front of our list.
			 */
			void push_front(const T& value)
			{
				Node* temp = new Node(value);
				
				if(this->empty())
				{
				head_ = temp;
				tail_ = temp;
				temp->setPrev(nullptr);
				temp->setNext(nullptr);
				}
				
				else
				{
				temp->setPrev(nullptr);
				temp->setNext(head_);
				head_->setPrev(temp);
				head_ = temp;
				}
				
				size_++;
			}
			
			/**
			 * Add an element to the end of this list.
			 * 
			 * Should return an iterator pointing to the newly created node.
			 */
			Iterator push_back(const T& value)
			{
				Node* temp = new Node(value);
				
				if(this->empty())
				{
				head_ = temp;
				tail_ = temp;
				temp->setPrev(nullptr);
				temp->setNext(nullptr);
				}
				
				else
				{
				temp->setPrev(tail_);
				temp->setNext(nullptr);
				tail_->setNext(temp);
				tail_ = temp;
				}
				
				size_++;
				
				return Iterator(head_, tail_, temp);
			}
			
			/**
			 * Remove the node at the front of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_front()
			{
			
			        if (this->empty())
			        {
			        throw std::range_error("List is empty.");
			        }
			        
				
				Node* tempHead = head_;
				
				head_ = head_->getNext();
				
				if(head_ != nullptr)
				{
				head_->setPrev(nullptr);
				}
				else
				{
				head_ = nullptr;
				}
				
				if (head_ == nullptr)
				{
					tail_ = nullptr;
				}
				
			        delete tempHead;
			        
			        size_--;
			  }      
			
			/**
			 * Remove the node at the end of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_back()
			{
				if (this->empty())
			        {
			        throw std::range_error("List is empty.");
			        }
				
				Node* tempTail = tail_;
				
				tail_ = tail_->getPrev();
				
				if(tail_ != nullptr)
				{
				tail_->setNext(nullptr);
				}
				else
				{
				head_ = nullptr;
				}
				
				if (tail_ == nullptr)
				{
					head_ = nullptr;
				}
				
				delete tempTail;
				
				size_--;
			}
			
			/**
			 * Return a reference to the element at the front.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& front()
			{
				if (this->empty())
				{
				throw std::range_error("List is empty.");
				}
				
				return head_->getElement();
			}
			
			/**
			 * Return a reference to the element at the back.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& back()
			{
				if (this->empty())
				{
				throw std::range_error("List is empty.");
				}
				
				return tail_->getElement();
			}
			
			/**
			 * Return the element at an index
			 * 
			 * Should throw a range_error is out of bounds
			 */
			T& at(size_t index)
			{
			      if (index >= size_)
			      {
			      throw std::range_error("Index is out of bounds");
			      }
			      
			      Node* temp = head_;
			      
			      for(size_t i = 0; i < index; i++)
			      {
			      temp = temp->getNext();
			      }
			      
			      return temp->getElement();
			      
			}
			
			/**
			 * Reverse the current list
			 */
			void reverse()
			{
				if (head_ == nullptr)
				{
				return;
				}
				
				Node* tempStart = head_;
				Node* temp = nullptr;
				
				while(tempStart != nullptr)
				{
				temp = tempStart->getNext();
				tempStart->setNext(tempStart->getPrev());
				tempStart->setPrev(temp);
				
				tempStart = temp;
				
				/*if (temp != nullptr)
				{
				head_ = temp->getPrev();
				}*/
				}
				
				tail_ = head_;
				head_ = temp;
					
			}
			
			/**
			 * I bet you're happy I'm not making you do this.
			 * No tests will be run against this function,
			 * 	but feel free to try it out, as a challenge!
			 * 
			 * If I were doing this and didn't care too much for efficiency,
			 * 	I would probably create an extra helper function to swap two
			 * 	positions in the current list.
			 * Then I would simply sweep through the list and perform
			 *  the bubble-sort algorithm. Perhaps selection sort.
			 * 
			 * If you want a huge challenge, try implementing quicksort.
			 * 
			 * (but again, don't worry about this method; it will not be tested)
			 */
			void sort()
			{
				//	TODO: Your code here
			}
			
			/**
			 * Assignment operator
			 * 
			 * Clear this list and fill it with the others' values
			 * (by value, not by reference)
			 * 
			 * Return a reference to this list
			 */
			DoublyLinkedList<T>& operator =(DoublyLinkedList<T>& other)
			{
				if (this == &other)
				{
				return *this;
				}
				
				clear();
				
				Node* temp = other.head_;
				while (temp != nullptr)
				{
				push_back(temp->getElement());
				temp = temp->getNext();
				}
				
				return *this;
			}
			
			/**
			 * Return true if the lists are "equal"
			 * 
			 * "Equal" here is defined as:
			 * - Same size
			 * - Elements at the same indexes would return true for their own comparison operators
			 * 
			 * In other words: "They contain all the same values"
			 * (no need for their pointers or addresses to be the same)
			 */
			bool operator ==(DoublyLinkedList<T>& other)
			{
				if (size_ != other.size_)
				{
				return false;
				}
				
				Node* temp1 = head_;
				Node* temp2 = other.head_;
				
				while(temp1 != nullptr && temp2 != nullptr)
				{
				if (temp1->getElement() != temp2->getElement())
				{
				return false;
				}
				
				temp1 = temp1->getNext();
				temp2 = temp2->getNext();
				}
				
				return true;
			}
			
			/**
			 * Return true if the lists are "not equal"
			 * 
			 * See the operator== stub for definition of "equal"
			 */
			bool operator !=(DoublyLinkedList<T>& other)
			{
				return !(*this == other);
			}
			
		private:
			
			Node* head_ = nullptr;
			Node* tail_ = nullptr;
			size_t size_ = 0;
	};
};

#endif


/*==31760== Memcheck, a memory error detector
==31760== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==31760== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==31760== Command: ./leak-checker
==31760== 
Hello, my name is Quiche Hollandaise!
==31760== 
==31760== HEAP SUMMARY:
==31760==     in use at exit: 2,400 bytes in 100 blocks
==31760==   total heap usage: 1,601 allocs, 1,501 frees, 113,128 bytes allocated
==31760== 
==31760== 2,400 (24 direct, 2,376 indirect) bytes in 1 blocks are definitely lost in loss record 2 of 2
==31760==    at 0x4846FA3: operator new(unsigned long) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==31760==    by 0x109966: CPSC131::DoublyLinkedList::DoublyLinkedList<int>::push_back(int const&) (DoublyLinkedList.hpp:774)
==31760==    by 0x109F2D: CPSC131::DoublyLinkedList::DoublyLinkedList<int>::assign(unsigned long, int const&) (DoublyLinkedList.hpp:387)
==31760==    by 0x1096EF: leaker() (leak_checker.cpp:58)
==31760==    by 0x1097E2: main (leak_checker.cpp:69)
==31760== 
==31760== LEAK SUMMARY:
==31760==    definitely lost: 24 bytes in 1 blocks
==31760==    indirectly lost: 2,376 bytes in 99 blocks
==31760==      possibly lost: 0 bytes in 0 blocks
==31760==    still reachable: 0 bytes in 0 blocks
==31760==         suppressed: 0 bytes in 0 blocks
==31760== 
==31760== For lists of detected and suppressed errors, rerun with: -s
==31760== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
*/
