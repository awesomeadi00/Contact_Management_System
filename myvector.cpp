#include "contact.h"
#include "myvector.h"

//===========================================================================================
//One Argument Constructor: Updates the capacity with cap (0 by default) and creates a vector with this new capacity. Size is 0
template <typename T> MyVector<T>::MyVector(int cap) {
    v_size = 0;
    v_capacity = cap;
    data = new Contact*[cap];
}

//===========================================================================================
//Destructor: Clears up memory of vector.
template <typename T> MyVector<T>::~MyVector() {
    delete[] data;
}

//===========================================================================================
//Push_Back: Adds an element at the end of the vector.
template <typename T> void MyVector<T>::push_back(T element) {
   if(v_size == v_capacity) {
       reserve(max(1, 2*v_capacity));
    }

    data[v_size] = element;
    v_size++;
}

//===========================================================================================
//Insert: Adds an element at a specific index within the scope of the vector size. If the index exceeds the vector size, it will display an error.
template <typename T> void MyVector<T>::insert(int index, T element){
    if(index > v_size-1) {
        throw runtime_error("Index is Greater than the Vector Size!");
    }

    else {
        for(int i = v_size-1; i >= index; i--) {
            if(v_size == v_capacity) {
                reserve(max(1, 2*v_capacity));
                data[i+1] = data[i];
            }
            
            else
                data[i+1] = data[i];
        }
        
        data[index] = element;
        v_size++;
    }
}

//===========================================================================================
//Erase: Removes an element from a specific index.
template <typename T> void MyVector<T>::erase(int index) {
    if(index > v_size-1 || index < 0) {
        throw runtime_error("Index is Greater than Vector Size!");
    }
    
    else if(index + 1 == v_size) {
        v_size--;
    }
    
    else {
        int j = index + 1;
        int i = index;
        while(j < v_size) {
            data[i] = data[j];
            j++;
            i++;
        }
        v_size--;
    }
}

//===========================================================================================
//At: Returns the reference of the element at a specific index.
template <typename T> T& MyVector<T>::at(int index) {
    if(index < 0 || index > v_size) {
        throw runtime_error("Index is Out of Vector Bound!");
    }
    
    return (data[index]);
}

//===========================================================================================
//Front: Returns the reference of the first element in the vector.
template <typename T> const T& MyVector<T>::front() {
    if(empty()) {
        throw runtime_error("Vector is Empty!");
    }
    
    return (data[0]);
}

//===========================================================================================
//Back: Returns reference of the last element in the vector.
template <typename T> const T& MyVector<T>::back() {
    if(empty()) {
        throw runtime_error("Vector is Empty!");
    }

    return (data[v_size-1]);
}

//===========================================================================================
//Size: Returns the current size of the vector.
template <typename T> int MyVector<T>::size() const {
    return (v_size);
}

//===========================================================================================
//Capacity: Returns the capacity of the vector.
template <typename T> int MyVector<T>::capacity() const {
    return (v_capacity);
}

//Empty: Returns true if the vector is empty, false otherwise.
template <typename T> bool MyVector<T>::empty() const {
    return (v_size == 0);
}

//===========================================================================================
//Shrink_to_fit: Reduces vector capcaity to fit its size, hence capcaity = size.
template <typename T> void MyVector<T>::shrink_to_fit(){
    v_capacity = v_size;
}

//===========================================================================================
//This function displays the one contact within the vector.
template <typename T> void MyVector<T>::display() {
    for(int i = 0; i < v_capacity; i++) {
        if(i == v_capacity-1) {
            cout << data[i] << "." << endl;
        }
        
        else {
            cout << data[i] << ", ";
        }
    }
}

//===========================================================================================
//Increases the size of the vector by new_size
template <typename T> void MyVector<T>::reserve(int new_size) {
    if(v_capacity < new_size) {
        T *temp = new Contact*[new_size];
        
        for(int i = 0; i < v_size; i++) {
            temp[i] = data[i];
        }
       
        if(data != NULL) {
            delete[] data;
        }
        
        data = temp;
        v_capacity = new_size;
    }
}
//===========================================================================================
template class MyVector<Contact*>;

