
/**
 * Name: Brianna Zaffina
 */


/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>

namespace CPSC131::MyVector
{

	template <typename T>
	class MyVector
	{
		public:
			
			/*******************
			 * Static constants
			 ******************/
			
			/// Default capacity
			static constexpr size_t DEFAULT_CAPACITY = 64;
			
			/// Minimum capacity
			static constexpr size_t MINIMUM_CAPACITY = 8;
			
			/*****************************
			 * Constructors / Destructors
			 ****************************/
			
			/// Normal constructor
			MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY)
			{
			  size_ = 0;
			  capacity_ = (capacity < MINIMUM_CAPACITY) ? MINIMUM_CAPACITY : capacity; //So that the capacity has some sort of value to 
			  elements_ = new T[capacity_]; //Allocate new memory using capacity
			}
			
			/// Copy constructor
			MyVector(const MyVector& other)
			{
			    size_ = other.size_;
			    capacity_ = other.capacity_;
			    elements_ = new T[capacity_]; //allocate new memory so both arrays dont share 1 memory location
			    std::copy(other.elements_, other.elements_ + other.size_, elements_);
			   /* for (size_t i = 0; i < size_; i++)
			    {
                              elements_[i] = other.elements_[i];
                            }*/
			}
			
			/**
			 * Destructor
			 * Cleanup here.
			*/
			~MyVector()
			{
			  
			  delete[] elements_; //Always need because we initalized new
			  elements_ = nullptr;
			}
			
			/************
			 * Operators
			 ************/
			
			///	Assignment operator
			MyVector& operator=(const MyVector& rhs)
			{
			  if(this!=&rhs)
			  {
			   delete[] elements_;
			   size_ = rhs.size_;
			   capacity_ = rhs.capacity_;
			   elements_ = new T[capacity_];
			   
			   std::copy(rhs.elements_, rhs.elements_ + rhs.size_, elements_);
			  }
				/*for (size_t i = 0; i < size_; i++) //Copies each element from array to one copying it
				 {
				  elements_[i] = rhs.elements_[i]; 
				  }*/
				  
				 return *this;
			}
			
			/// Operator overload to at()
			T& operator[](size_t index) const
			{
				if (index >= size_)
				{
				  throw std::range_error("Index out of bounds.");
				}
			      
                                  return elements_[index];
				//return *(new T());
			}
			
			/************
			 * Accessors
			 ************/
			
			/// Return the number of valid elements in our data
			size_t size() const
			{
				return size_;
			}
			
			/// Return the capacity of our internal array
			size_t capacity() const
			{
				return capacity_;
			}
			
			/**
			 * Check whether our vector is empty
			 * Return true if we have zero elements in our array (regardless of capacity)
			 * Otherwise, return false
			 */
			bool empty() const
			{
				if (size_ == 0) //elements_ can still have allocated memory, therefore use size to see amount of elements in the array.
				{
				  return true;
				}
				
				else
				{
				return false;
				}
			}
			
			/// Return a reference to the element at an index
			T& at(size_t index) const
			{
				if (index >= size_)
				{
				  throw std::range_error("Index out of bounds");
				}
				
				return elements_[index];
			}
			
			/***********
			 * Mutators
			 ***********/
			
			/**
			 * Reserve capacity in advance, if our capacity isn't currently large enough.
			 * Useful if we know we're about to add a large number of elements,
			 *   and we'd like to avoid the overhead of many internal changes to capacity.
			 */
			void reserve(size_t capacity)
			{
			    if (capacity < MINIMUM_CAPACITY)
			    {
			      capacity = MINIMUM_CAPACITY;
			    }
			    
			    if (capacity <= capacity_)
			    {
			    return;
			    }
			    
			    T* elements = new T[capacity];
			    std::copy(elements_, elements_ + size_, elements);  
			    delete[] elements_;
			    elements_ = elements;
			    capacity_ = capacity;
			    
			   /* if (capacity < MINIMUM_CAPACITY)
			    {
			      throw std::range_error("Capacity can not be less than 8.");
			    }*/
			    
			}
			
			/**
			 * Set an element at an index.
			 * Throws range error if outside the size boundary.
			 * Returns a reference to the newly set element (not the original)
			 */
			T& set(size_t index, const T& element)
			{
			
				if (index >= size_)
				{
				  throw std::range_error("Index out of out of bounds");
				}
				elements_[index].~T();
				
				at(index) = element;
				
				return elements_[index];
			}
			
			/**
			 * Add an element onto the end of our vector.
			 * Returns a reference to the newly inserted element.
			 */
			T& push_back(const T& element)
			{
				if(size_ == capacity_)
				{
				 reserve(capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * 2); //Fix this
				}
				
				elements_[size_] = element;
				return elements_[size_++];
				
			}
			
			/**
			 * Remove the last element in our vector.
			 * Should throw std::range_error if the vector is already empty.
			 * Returns a copy of the element removed.
			 */
			T pop_back()
			{
			  if (size_ == 0)
			  {
			    throw std::range_error("Vector is empty.");
			  }
			  
			  T elementRemoved = elements_[size_ -1];
			  
			  elements_[size_ -1].~T();
			  --size_;
			
			  while(size_ < capacity_ / 3 && capacity_ > MINIMUM_CAPACITY)
			  {
			  changeCapacity(capacity_ / 2);
			  }
                          
			  return elementRemoved;
			}
			
			/**
			 * Insert an element at some index in our vector
			 * 
			 * Example:
			 * 	 Insert a 9 at index 2
			 *   Contents before: [6, 2, 7, 4, 3]
			 *   Contents after:  [6, 2, 9, 7, 4, 3]
			 * 
			 * Returns a reference to the newly added element (not the original).
			 */
			T& insert(size_t index, const T& element)
			{
			      
				 
				 if (index > size_)
				 {
				 throw std::range_error("Index out of bounds.");
				 }
				 
				 if(size_ >= capacity_)
				{
				 reserve(capacity_ == 0 ? DEFAULT_CAPACITY : capacity_ * 2);
				 }
				 
				 std::move_backward(elements_ + index, elements_ + size_, elements_ + size_ + 1);
				 
				 elements_[index] = element;
				 
				 ++size_;
				 
				 return elements_[index];
			}
			
			/**
			 * Erase one element in our vector at the specified index
			 * 
			 * Throws std::range_error if the index is out of bounds.
			 * 
			 * Example:
			 *   Erase index 2
			 *   Contents before: [8, 4, 3, 9, 1]
			 *   Contents after:  [8, 4, 9, 1]
			 * 
			 * Returns a copy of the erased element.
			 * Hint: call DTOR on original after making the copy.
			 */
			T erase(size_t index)
			{
			  if (index >= size_)
			    {
				throw std::range_error("Index out of bounds.");
			    }
			      T element = elements_[index];
				std::copy(elements_ + index + 1, elements_ + size_, elements_ + index);
				
				elements_[size_].~T();
				--size_;
				
				while(size_ < capacity_ / 3 && capacity_ > MINIMUM_CAPACITY)
			  {
			  changeCapacity(capacity_ / 2);
			  }
				
				return element;
			}
			
			/**
			 * Removes all elements (i.e., size=0 and DTORs called)
			 * 
			 * Should also reset capacity, if needed
			*/
			void clear()
			{
			    while(size_ != 0)
			    {
			      pop_back();
			    }
			    
			    changeCapacity(DEFAULT_CAPACITY);
			}
		
		/**
		 * Begin private members and methods.
		 * You may add your own private helpers here, if you wish.
		*/
		private:
			
			/// Number of valid elements currently in our vector
			size_t size_ = 0;
			
			/// Capacity of our vector; The actual size of our internal array
			size_t capacity_ = 0;
			
			/**
			 * Our internal array of elements of type T.
			 * Starts off as a null pointer.
			 */
			T* elements_ = nullptr;
			
			/**
			 * Helper function that is called whenever we need to change the capacity of our vector.
			 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
			 */
			void changeCapacity(size_t c)
			{
			  if (c < MINIMUM_CAPACITY)
			  {
			  c = MINIMUM_CAPACITY;
			  }
			      if (c < size_)
			      {
			        throw std::range_error("Capacity cannot hold the existing elements.");
			      }
			      
			    T* elements = new T[c];
			    std::copy(elements_, elements_ + size_, elements);
			    
			    delete[] elements_;
			    elements_ = elements;
			    capacity_ = c;
			}
	};

}


// Sources: Provided 5_FixedVector_Sparse_Arrays.odp file in our files
//          Provided 06 Vector Anaylsis.pptx file in our files
//          I used ChatGPT to help with debugging
//          I also had the help of someone on the discord server.
