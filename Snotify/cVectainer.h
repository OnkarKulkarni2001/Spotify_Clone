#pragma once
#include <string>
#include <iostream>

template <typename T>
class cVectainer	// Vector + Container = Vectainer??? seems creative enough?
{
private:
	T* m_pData;							// this will store any type of data as it's a void pointer
	unsigned int m_currentEndIndex;					// self-sufficient variable name, no need to explain I guess...
	const unsigned int STARTING_CAPACITY = 8;			// starting capacity
	unsigned int m_capacity;		// this will be expandable furthermore	

public:

	cVectainer();
	~cVectainer();

    cVectainer(const cVectainer<T>& other);
    cVectainer<T>& operator=(const cVectainer<T>& other);

	T& getAt(int index);			
	bool resize(unsigned int newCapacity);

	bool addAtEnd(const T& newData);
	bool clear();					// this will clear whole vectainer (delete all data from vectainer)

	unsigned int getSize();			// will return capacity

	bool isEmpty();					// will return true if the vectainer is empty

    bool removeAt(unsigned int index);   // wanted this because the streetname file had headers on first index, instead of removing by hard coding I thought this will be good idea to have in my container
    template<typename Compare>
    void sort(Compare compareFunc);
    template<typename Compare>
    void quickSort(int low, int high, Compare compareFunc);
    template<typename Compare>
    int partition(int low, int high, Compare compareFunc);
    void swap(T* a, T* b);
    //void sort(std::function<bool(const T&, const T&)> compareFunc);
};

template <typename T>
cVectainer<T>::cVectainer(const cVectainer<T>& other)
{
    this->m_capacity = other.m_capacity;
    this->m_currentEndIndex = other.m_currentEndIndex;

    // Allocate new memory
    this->m_pData = new T[m_capacity];

    // Deep copy the data
    for (unsigned int i = 0; i < m_currentEndIndex; i++) {
        m_pData[i] = other.m_pData[i];
    }
}


template <typename T>
cVectainer<T>& cVectainer<T>::operator=(const cVectainer<T>& other)
{
    // Self-assignment check
    if (this == &other)
        return *this;

    // Free existing data
    delete[] m_pData;

    // Copy data from 'other' to 'this'
    this->m_capacity = other.m_capacity;
    this->m_currentEndIndex = other.m_currentEndIndex;

    // Allocate new memory
    m_pData = new T[m_capacity];

    // Deep copy the data
    for (unsigned int i = 0; i < m_currentEndIndex; i++) {
        m_pData[i] = other.m_pData[i];
    }

    return *this;
}


// Needed templating so that while retrieving data I dont need to cast it to actual class/struct or whatever appropriate type
template <typename T>
bool cVectainer<T>::resize(unsigned int newCapacity)
{
    if (newCapacity <= m_capacity) return false; // Avoid resizing if the new capacity is not greater

    // Allocate new memory for the resized container
    T* newData = new T[newCapacity];

    // Copy existing data into the new container
    for (unsigned int i = 0; i < m_currentEndIndex; ++i)
    {
        newData[i] = m_pData[i];
    }

    // Free the old memory
    delete[] m_pData;

    // Point to the new memory
    m_pData = newData;
    m_capacity = newCapacity;

    return true;
}

template <typename T>
cVectainer<T>::cVectainer() : m_currentEndIndex(0), m_capacity(STARTING_CAPACITY)
{
    // Allocate initial memory for the vectainer
    m_pData = new T[m_capacity];
}

template <typename T> cVectainer<T>::~cVectainer()
{
    // Clear any allocated data before deleting the array
    clear();
    delete[] m_pData;
}

template <typename T>
T& cVectainer<T>::getAt(int index)
{
    // Ensure the index is valid
    if (index < 0 || index > m_currentEndIndex)
    {
        std::cout << "Index out of range" << std::endl;
    }
    return m_pData[index];
}

template <typename T>
bool cVectainer<T>::addAtEnd(const T& newData)
{
    // If we're at capacity, resize the vectainer
    if (m_currentEndIndex >= m_capacity)
    {
        resize(m_capacity * 2); // Double the capacity
    }

    // Add the new data at the end
    m_pData[m_currentEndIndex] = newData;
    ++m_currentEndIndex;

    return true;
}

template <typename T>
bool cVectainer<T>::clear()
{
    m_currentEndIndex = 0;
    return true;
}

template <typename T>
unsigned int cVectainer<T>::getSize()
{
    return m_currentEndIndex;
}

template <typename T>
bool cVectainer<T>::isEmpty()
{
    return m_currentEndIndex == 0;
}

template <typename T>
bool cVectainer<T>::removeAt(unsigned int index)
{
    if (index < 0 || index > m_currentEndIndex) {
        std::cout << "Index out of range" << std::endl;
        return false;
    }

    // Shift elements to the left
    for (unsigned int i = index; i < m_currentEndIndex; ++i)
    {
        m_pData[i] = m_pData[i + 1];
    }

    // Decrease the current size
    --m_currentEndIndex;
    return true;
}

template <typename T>
template <typename Compare>
void cVectainer<T>::sort(Compare compareFunc)
{
    if (m_pData != nullptr && m_currentEndIndex > 0)
    {
        quickSort(0, m_currentEndIndex - 1, compareFunc);
    }
}

template <typename T>
template <typename Compare>
void cVectainer<T>::quickSort(int low, int high, Compare compareFunc)
{
    if (low < high)
    {
        int pivotIndex = partition(low, high, compareFunc);
        quickSort(low, pivotIndex - 1, compareFunc);
        quickSort(pivotIndex + 1, high, compareFunc);
    }
}

template <typename T>
template <typename Compare>
int cVectainer<T>::partition(int low, int high, Compare compareFunc)
{
    T pivot = m_pData[high];    // Choose the rightmost element as pivot
    int i = low - 1;           // Index of smaller element

    for (int j = low; j < high; j++)
    {
        // If current element is "less than" pivot according to compareFunc
        if (compareFunc(m_pData[j], pivot))
        {
            i++;
            swap(&m_pData[i], &m_pData[j]);
        }
    }
    swap(&m_pData[i + 1], &m_pData[high]);
    return i + 1;
}

template <typename T>
void cVectainer<T>::swap(T* a, T* b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}