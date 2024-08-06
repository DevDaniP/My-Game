
#pragma once
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <string> 
#include "potions.h"
#include <iostream>
#include <cstring> 
#include <stdexcept> 
using std::string;
using std::swap;
using std::cout;
using std::endl;

template<class T>
class DynamicArray
{
private:
    T* m_array;
    int m_elements;

public:
    DynamicArray() : m_elements(0), m_array(nullptr) {}
    ~DynamicArray() {
        m_elements = 0;
        delete[] m_array;
        m_array = nullptr;
    }

    DynamicArray(const DynamicArray& copy) : m_array(copy.m_array), m_elements(copy.m_elements) {}

    DynamicArray& operator=(const DynamicArray& rhs) {
        if (this != &rhs) {
            delete[] m_array;
            m_elements = rhs.m_elements;
            m_array = new T[rhs.m_elements];
            for (int i = 0; i < rhs.m_elements; ++i) {
                m_array[i] = rhs.m_array[i];
            }
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& rhs) noexcept {
        if (this != &rhs) {
            swap(m_array, rhs.m_array);
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= m_elements) {
            throw std::out_of_range("Index out of range");
        }
        if (!m_array) {
            throw std::runtime_error("Array is uninitialized");
        }
        return m_array[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= m_elements) {
            throw std::out_of_range("Index out of range");
        }
        if (!m_array)
        {
            throw std::runtime_error("Array is unitialized");
        }
        return m_array[index];
    }

    int GetElements() const {
        return m_elements;
    }

    void Insert(const T& to_add) {
        try {
            T* temp = new T[m_elements + 1];
            for (int i = 0; i < m_elements; ++i) {
                temp[i] = m_array[i];
            }
            temp[m_elements] = to_add;
            delete[] m_array;
            m_array = temp;
            ++m_elements;
        }
        catch (const std::bad_alloc) {
            throw std::runtime_error(" Memory allocation failed");
        }
    }

    void Delete(const T& to_delete) {
        int target_slot = Find(to_delete);
        if (target_slot != -1) {
            try {
                T* temp = new T[m_elements - 1];
                int j = 0;
                for (int i = 0; i < m_elements; ++i) {
                    if (i != target_slot) {
                        temp[j++] = m_array[i];
                    }
                }
                delete[] m_array;
                m_array = temp;
                --m_elements;
            }  catch (const std::bad_alloc) {
                throw std::runtime_error("Memory allocation failed");
            }
        }
    }
    int Find(const T& target) {
        if (!m_array) {
            throw std::runtime_error("array is uninitiliazed");
        }
        for (int i = 0; i < m_elements; ++i) {
            if (m_array[i] == target) {
                return i;
            }
        }
        return -1;
    }
    void Display(int index) const {
        if (index >= 0 && index < m_elements) {
            cout << m_array[index] << endl;
        }
        else {
            cout << "Error: Index out of range" << endl;
        }
    }
};
#endif 


