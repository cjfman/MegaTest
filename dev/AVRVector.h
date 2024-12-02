// AVRVector
// Original Source : http://webcache.googleusercontent.com/search?q=cache:tTum-KUosqoJ:forum.arduino.cc/index.php/topic,45626.0.html+avr+container+objects&client=safari&hl=en&gl=us&strip=1
// Minimal class to replace std::vector

#ifndef AVRVECTOR_h
#define AVRVECTOR_h

#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

namespace MegaTest {

template<typename Data>
class AVRVector {
   uint16_t d_size;     // Stores no. of actually stored objects
   uint16_t d_capacity; // Stores allocated capacity
   Data *d_data;        // Stores data

   public:
     AVRVector(); // Default constructor
     AVRVector(AVRVector const &other); // Copy constuctor
     AVRVector(Data d);
     ~AVRVector(); // Destructor
     AVRVector<Data>& operator=(AVRVector const &other); // Needed for memory management
     void push_back(Data const &x); // Adds new value. If needed, allocates more space
     uint16_t size(); // Size getter
     const Data operator[](uint16_t idx) const; // Const getter
     Data& operator[](uint16_t idx); // Changeable getter

   private:
     void resize();	// Allocates double the old space
};

template<typename Data>
AVRVector<Data>::AVRVector() : d_size(0), d_capacity(0), d_data(0) {

}

template<typename Data>
AVRVector<Data>::AVRVector(AVRVector<Data> const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { 
  d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
  //memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
  for (unsigned int i = 0; i < other.d_size; i++) {
    d_data[i] = other.d_data[i];
  }
}

template<typename Data>
AVRVector<Data>::AVRVector(Data d) : d_size(0), d_capacity(0), d_data(0){
	this->push(d);
}

template<typename Data>
AVRVector<Data>::~AVRVector() { 
  free(d_data); 
}

template<typename Data>
AVRVector<Data>& AVRVector<Data>::operator=(AVRVector<Data> const &other) { 
  if (this == &other) return *this; // protect against invalid self-assignment
  free(d_data); 
  d_size = other.d_size; 
  d_capacity = other.d_capacity; 
  d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
  //memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
  for (unsigned int i = 0; i < other.d_size; i++) {
    d_data[i] = other.d_data[i];
  }
  return *this; 
}

template<typename Data>
void AVRVector<Data>::push_back(Data const &x) { 
  if (d_capacity == d_size) resize(); 
  d_data[d_size++] = x; 
}

template<typename Data>
uint16_t AVRVector<Data>::size() { 
  return d_size; 
}

template<typename Data>
const Data AVRVector<Data>::operator[](uint16_t idx) const { 
  return d_data[idx]; 
}

template<typename Data>
Data& AVRVector<Data>::operator[](uint16_t idx) { 
  return d_data[idx]; 
}


/***********************
Private
***********************/

template<typename Data>
void AVRVector<Data>::resize() { 
  d_capacity = d_capacity ? d_capacity*2 : 1; 
  Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); 
  for (unsigned int i = 0; i < d_size; i++) {
    newdata[i] = d_data[i];
  }
  free(d_data); 
  d_data = newdata; 
}

} //namespace

#endif // Whole File