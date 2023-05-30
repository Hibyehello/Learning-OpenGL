#pragma once

#include <cstdlib>
#include <cstring>
#include <iostream>

template<typename T>
class Vector {
private:
	int m_length;
	int m_size;
	T* m_arr;
public:
	Vector();
    void push(T obj);
    T pop();
    int insert(T obj, int index);
    T remove(int index);
private:
    static T* Vmalloc(size_t size);
    static T* Vrealloc(T* arr, size_t size);
};

template<typename T>
Vector<T>::Vector() {
    m_arr = Vector<T>::Vmalloc(sizeof(T));
    m_length = 0;
    m_size = 1;
}

template<typename T>
void Vector<T>::push(T obj) {
    if(m_length == m_size) {
        m_arr = Vector<T>::Vrealloc(m_arr, (sizeof(T)*m_size)+((sizeof(T)*m_size)/2));
        m_size = m_size + (m_size/2);
    }
    
    m_arr[m_length++] = obj;
}

template<typename T>
T Vector<T>::pop() {
    T value = m_arr[m_length-1];
    
    m_length--;
    
    return value;
}

template<typename T>
int Vector<T>::insert(T obj, int index) {
    if(index == m_size) {
        push(obj);
        return m_length;
    }
    else if(index > m_size+1) {
        std::cerr << "Error: index out of bounds" << std::endl;
        return -1;
    }
    
    int size = (m_length - index)*sizeof(T);
    T* temp = Vector<T>::Vmalloc(size);
    memcpy(temp, m_arr+index, size);
    m_arr[index] = obj;
    m_length++;
    
    if(m_length+1 == m_size) {
        m_arr = Vector<T>::Vrealloc(m_arr, 1+(m_size*sizeof(T)));
    }
    
    memmove(m_arr + index + 1, temp, size);
    
    free(temp);
    
    return m_length;
}

template<typename T>
T Vector<T>::remove(int index) {
    if(index > m_length-1) {
        std::cerr << "index of bounds: " << index << " vs " << m_length-1 << std::endl;
        throw -1;
    }
    
    T value = m_arr[index];
    
    memmove(m_arr + index, m_arr + index + 1, (m_size-index+1) * sizeof(T));
    
    m_length--;
    return value;
}

template<typename T>
T* Vector<T>::Vmalloc(size_t size) {
    T* ret = reinterpret_cast<T*>(malloc(size));
    if(ret == NULL) {
        std::cerr << "malloc failed" << std::endl;
        abort();
    }
    return ret;
}

template<typename T>
T* Vector<T>::Vrealloc(T* arr, size_t size) {
    T* ret = reinterpret_cast<T*>(realloc(arr, size));
    if(ret == NULL) {
        std::cerr << "malloc failed" << std::endl;
        abort();
    }
    return ret;
}


