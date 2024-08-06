#include "DynamicArray.h"
#include "potions.h"
#include <iostream>
#include <cstring> 
using std::string;
using std::swap; 
using std::cout; 
using std::endl; 
template<class T >
DynamicArray<T>::DynamicArray() : m_elements(0), m_array(nullptr)
{
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
	m_elements = 0;

	delete[] m_array;
	m_array = nullptr;
}
template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray& copy) : m_array(copy.m_array), m_elements(copy.m_elements)
{

}
template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& rhs)
{
	if (this != &rhs)
	{
		delete[] m_array;
		m_elements = rhs.m_elements;
		m_array = new potions[rhs.m_elements];
		for (int i = 0; i < rhs.m_elements; ++i)
		{
			m_array[i] = rhs.m_array[i];
		}
	}
	return *this;
}
template<class T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& rhs) noexcept {
	if (this != &rhs) {
		swap(m_array, rhs.m_array);
	}
	return *this;
}
template<class T>
T& DynamicArray<T>::operator[](int index)
{
	if (index < 0 || index >= m_elements)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_array[index]; 
}
template<class T>
const T& DynamicArray<T>::operator[](int index) const
	{
	if (index < 0 || index >= m_elements)
	{
		throw std::out_of_range("Index out of range");
		}
	return m_array[index]; 
	}
template<class T>
int DynamicArray<T>::GetElements() const
{
	return m_elements;
}
template<class T>
void DynamicArray<T>::Insert(const T& to_add)
{
	
		T* temp = new T[m_elements + 1];

		for (int i = 0; i < m_elements; ++i)
		{
			temp[i] = m_array[i];
		}

		temp [m_elements] = to_add;
		delete[] m_array;
		m_array = temp;
		++m_elements;
	
}
template<class T>
void DynamicArray<T>::Delete(const T& to_delete)
{
	int target_slot = Find(to_delete);
	if (target_slot != -1)
	{
		T* temp = new T[m_elements - 1];
		int j = 0;
		for (int i = 0; i < m_elements; ++i)
		{
			if (i != target_slot)
			{
				temp[j++] = m_array[i];
			}
		}
		delete[] m_array;
		m_array = temp;
		--m_elements;
	}

}
template<class T>
int DynamicArray<T>::Find(const T& target)
{
	for (int i = 0; i < m_elements; ++i)
	{
		if (m_array[i] == target)
		{
			return i;
		}
	}
	return -1; 
}
template<class T>
void DynamicArray<T>::Display(int index) const
{
	if (index >= 0 && index < m_elements)
	{
		std::cout << m_array[index] << std::endl;
	}
	else
	{
		std::cout << "Error: Index out of range" << std::endl;
	}
}

