// MegaVector.h

// The MIT License (MIT)
// Copyright (c) 2013, Charles Jessup Franklin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

// Original Source : http://webcache.googleusercontent.com/search?q=cache:tTum-KUosqoJ:forum.arduino.cc/index.php/topic,4MEGA_MAX_TESTS26.0.html+avr+container+objects&client=safari&hl=en&gl=us&strip=1
// Minimal class to replace std::vector
//
// Note: The class uses the defined constant MEGA_MAX_TESTS to determin if there will be
//       a fixed storage size, or if dynamic memory allocation will be used or not.

#ifndef MEGAVECTOR_h
#define MEGAVECTOR_h

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "MegaTest_Default_Configuration.h"

namespace MegaTest {

template<typename Data>
class MegaVector {
   uint16_t d_size;     // Stores no. of actually stored objects
   uint16_t d_capacity; // Stores allocated capacity
#ifndef MEGA_MAX_TESTS
   Data *d_data;
#else
   Data d_data[MEGA_MAX_TESTS];        // Stores data
#endif

   public:
     MegaVector(); // Default constructor
     MegaVector(MegaVector const &other); // Copy constuctor
     MegaVector(Data d);
     ~MegaVector(); // Destructor
     MegaVector<Data>& operator=(MegaVector const &other); // Needed for memory management
     bool push_back(Data const &x); // Adds new value. If needed, allocates more space
     uint16_t size(); // Size getter
     const Data operator[](uint16_t idx) const; // Const getter
     Data& operator[](uint16_t idx); // Changeable getter

   private:
#ifndef MEGA_MAX_TESTS
     void resize();	// Allocates double the old space
#endif
};

/*
 * MegaVector::Constructor
 *
 * description: The default constructor that makes an empty vector
 *
 */
#ifndef MEGA_MAX_TESTS
template<typename Data>
MegaVector<Data>::MegaVector() : d_size(0), d_capacity(0), d_data(0) {

}
#else
template<typename Data>
MegaVector<Data>::MegaVector() : d_size(0), d_capacity(MEGA_MAX_TESTS) {

}
#endif

/*
 * MegaVector::Copy Constructor
 */
#ifndef MEGA_MAX_TESTS
template<typename Data>
MegaVector<Data>::MegaVector(MegaVector<Data> const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { 
  d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
  //memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
  for (unsigned int i = 0; i < other.d_size; i++) {
    d_data[i] = other.d_data[i];
  }
}
#else
template<typename Data>
MegaVector<Data>::MegaVector(MegaVector<Data> const &other) : d_size(other.d_size), d_capacity(other.d_capacity) { 
  //d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
  //memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
  for (unsigned int i = 0; i < other.d_size; i++) {
    d_data[i] = other.d_data[i];
  }
}
#endif

/*
 * MegaVector::Constructor with start data
 *
 * parameters: d, the data to be stored in the vector
 *
 * description: Constructs a vector and places the data in the first index
 *
 */
#ifndef MEGA_MAX_TESTS
template<typename Data>
MegaVector<Data>::MegaVector(Data d) : d_size(0), d_capacity(0), d_data(0){
  this->push_back(d);
}
#else
template<typename Data>
MegaVector<Data>::MegaVector(Data d) : d_size(0), d_capacity(MEGA_MAX_TESTS) {
	this->push_back(d);
}
#endif

/*
 * MegaVector::Destructor
 */
template<typename Data>
MegaVector<Data>::~MegaVector() { 
#ifndef MEGA_MAX_TESTS
  free(d_data); 
#endif
}

/*
 * MegaVector::Assignment Operator
 */
template<typename Data>
MegaVector<Data>& MegaVector<Data>::operator=(MegaVector<Data> const &other) { 
  if (this == &other) return *this; // protect against invalid self-assignment
  d_size = other.d_size; 
#ifndef MEGA_MAX_TESTS
  free(d_data); 
  d_capacity = other.d_capacity; 
  d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
  memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
#endif
  for (unsigned int i = 0; i < other.d_size; i++) {
    d_data[i] = other.d_data[i];
  }
  return *this; 
}

/*
 * MegaVector::push_back
 *
 * parameter: x, the data to be added to the vector
 *
 * returns: (bool) True if the data was successfully added to the vector, false otherwise.
 *
 * description: The data is placed at the next empty index. If dynamic memory allocation
 *              is used and the vector is full, the vector is resized. If the size is
 *              fixed, then the method simply returns false and does nothing.
 *
 */
template<typename Data>
bool MegaVector<Data>::push_back(Data const &x) { 
  if (d_capacity == d_size) {
#ifndef MEGA_MAX_TESTS
    resize(); 
#else
    return false;
#endif
  }
  d_data[d_size++] = x;
  return true;
}

/*
 * MegaVector::size
 *
 * returns: (uint16_t) the number of indexes that are occupied with valid data
 *
 */
template<typename Data>
uint16_t MegaVector<Data>::size() { 
  return d_size; 
}

/*
 * MegaVector::[] operator
 *
 * returns: (const Data) The data at the specified index. The data cannot be changed.
 *
 */
template<typename Data>
const Data MegaVector<Data>::operator[](uint16_t idx) const { 
  return d_data[idx]; 
}

/*
 * MegaVector::[] operator
 *
 * returns: (Data) The data at the specified index. The data can be changed.
 *
 */
template<typename Data>
Data& MegaVector<Data>::operator[](uint16_t idx) { 
  return d_data[idx]; 
}


/***********************
Private
***********************/

/*
 * MegaVector::resize
 *
 * description: doubles the capacity of the vector, or makes the capacity 1 if the 
 *              previous capacity was 0.
 *
 */
#ifndef MEGA_MAX_TESTS
template<typename Data>
void MegaVector<Data>::resize() { 
  d_capacity = d_capacity ? d_capacity*2 : 1; 
  Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); 
  for (unsigned int i = 0; i < d_size; i++) {
    newdata[i] = d_data[i];
  }
  free(d_data); 
  d_data = newdata;
}
#endif

} //namespace

#endif // Whole File