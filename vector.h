#pragma once

#include <iostream>
//#include <memory>
#include <cstring>


template<typename T>
class Vector
{
private:
	T* m_ptr = nullptr;
	size_t m_size = 0;
	//size_t m_capacity = 0;

public:
	void push_back(T& data);
	void push_back(T&& data);

	void resize(size_t size);
	//void reserve(size_t size);

	void erase(size_t dst);
	void erase(size_t src, size_t dst);

	void clear();

	size_t size() const;
	//size_t capacity() const;

	T& operator[](size_t index) const;

public:
	Vector();
	Vector(std::initializer_list<T> list);
	Vector(size_t size);

	~Vector();
};

template<typename T>
void Vector<T>::push_back(T& data)
{
	if (!(m_size < 0))
	{
		resize(m_size + 1);
	}

	new (m_ptr + m_size) T(data);
	m_size++;
}

template<typename T>
void Vector<T>::push_back(T&& data)
{
	if (!(m_size < 0))
	{
		resize(m_size + 1);
	}

	new (m_ptr + m_size) T(data);
	m_size++;
}

template<typename T>
void Vector<T>::resize(size_t size)
{
	if (m_size != size && size != 0)
	{
		if (m_size == 0)
		{
			m_ptr = new T[size]();

			m_size = size;
		}
		else
		{
			T* temp_ptr = new T[size]();

			std::uninitialized_copy(m_ptr, m_ptr + size, temp_ptr);

			delete[] m_ptr;
			m_ptr = temp_ptr;
			m_size = size;
		}
	}
}

template<typename T>
void Vector<T>::erase(size_t dst)
{
	if(dst < m_size)
	{
		if ((m_size - dst) == 1)
		{
			m_ptr[dst].~T();
			m_size--;
		}
		else {
			m_ptr[dst].~T();

			std::uninitialized_copy(m_ptr + (dst + 1), (m_ptr + (dst + 1)) + (m_size - (dst + 1)), m_ptr + dst);
			m_size--;
		}
	}
}

template<typename T>
void Vector<T>::erase(size_t src, size_t dst)
{
	if (src <= dst && dst < m_size)
	{
		if ((m_size - src) == 1)
		{
			for (int i = dst; i >= src; i--)
			{
				m_ptr[i].~T();
			}
			m_size--;
		}
		else {
			for (int i = dst; i >= src; i--)
			{
				m_ptr[i].~T();
			}

			if(!((m_size - dst) == 1)) std::uninitialized_copy(m_ptr + (dst + 1), (m_ptr + (dst + 1)) + (m_size - (dst + 1)), m_ptr + src);

			m_size -= (dst - src) + 1;
		}
	}
}

template<typename T>
void Vector<T>::clear()
{
	for (int i = m_size - 1; i >= 0; i--)
	{
		m_ptr[i].~T();
	}

	m_size = 0;
}

template<typename T>
size_t Vector<T>::size() const
{
	return m_size;
}

template<typename T>
T& Vector<T>::operator[](size_t index) const
{
	if (index < m_size) {
		return *(m_ptr + index);
	}
	else {
		throw std::out_of_range("error: index out of range");
	}
}

template<typename T>
Vector<T>::Vector()
{}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list)
{
	resize(list.size());

	for (auto element : list)
	{
		this->push_back(element);
	}
}

template<typename T>
Vector<T>::Vector(size_t size)
{
	resize(size);
}

template<typename T>
Vector<T>::~Vector()
{
	if(m_size != 0) delete[] m_ptr;
}
