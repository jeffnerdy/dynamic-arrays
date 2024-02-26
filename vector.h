#pragma once

#include <iostream>
#include <cstring>


template<typename T>
class Vector
{
private:
	T* m_ptr;
	T* m_tempptr;
	size_t m_size;
	size_t m_tempsize;
	size_t m_reserved;
	size_t m_index;

public:
	void push_back(T data);

	void resize(size_t size);
	void reserve(size_t size);
	void erase(size_t dst);
	void erase(size_t dst, size_t src);

	void clear();

	size_t size() const;
	size_t capacity() const;

	T& operator[](size_t index) const;

	void reallocate(size_t reserved, size_t size);

public:
	Vector();
	Vector(std::initializer_list<T> list);
	Vector(size_t size);

	~Vector();
};

template<typename T>
void Vector<T>::push_back(T data)
{
	if (!(m_index < m_reserved))
	{
		this->reallocate(m_size + 1, m_size);

		if (m_reserved < m_tempsize) m_reserved = m_tempsize;
		m_tempsize = 0;
	}

	m_ptr[m_index] = data;
	m_index++;

	if (!(m_index < m_size))
	{
		m_size = m_index;
	}
}

template<typename T>
void Vector<T>::resize(size_t size)
{
	if (m_size != size)
	{
		if (size < m_size)
		{
			this->reallocate(size, size);
			m_reserved = size;
			m_index = size;
		}
		else {
			this->reallocate(size, m_size);
		}

		m_size = m_tempsize;
		m_tempsize = 0;
	}
}

template<typename T>
void Vector<T>::reserve(size_t size)
{
	if (size > m_reserved)
	{
		this->reallocate(size, m_size);

		m_reserved = m_tempsize;
		m_tempsize = 0;
	}
}

template<typename T>
void Vector<T>::clear()
{
	m_tempptr = new T[m_size];
	delete[] m_ptr;
	m_ptr = m_tempptr;
	m_tempptr = nullptr;

	m_index = 0;
}

template<typename T>
void Vector<T>::erase(size_t dst)
{
	if(dst < m_size)
	{
		if ((m_size - dst) == 1)
		{
			m_size--;
			m_index--;
		}
		else {
			std::memcpy(m_ptr + dst, m_ptr + (dst + 1), (m_size - (dst + 1)) * sizeof(T));
			m_size--;
			m_index--;
		}
	}
}

template<typename T>
void Vector<T>::erase(size_t dst, size_t src)
{
	if (dst < src && src < m_size)
	{
		if ((m_size - dst) == 1)
		{
			m_size--;
			m_index--;
		}
		else {
			std::memcpy(m_ptr + dst, m_ptr + (src + 1), (m_size - (src + 1)) * sizeof(T));
			m_size -= (src - dst) + 1;
			m_index = m_size;
		}
	}
}

template<typename T>
size_t Vector<T>::size() const
{
	return this->m_size;
}

template<typename T>
size_t Vector<T>::capacity() const
{
	return this->m_reserved;
}

template<typename T>
T& Vector<T>::operator[](size_t index) const
{
	if (index < m_index) return *(m_ptr + index);
}

template<typename T>
void Vector<T>::reallocate(size_t reserved, size_t size)
{
	m_tempsize = reserved;
	m_tempptr = new T[m_tempsize];
	std::memcpy(m_tempptr, m_ptr, size * sizeof(T));
	delete[] m_ptr;
	m_ptr = m_tempptr;
	m_tempptr = nullptr;
}

template<typename T>
Vector<T>::Vector() : m_ptr(nullptr), m_tempptr(nullptr), m_size(0), m_tempsize(0), m_reserved(0), m_index(0)
{}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> list) : m_tempptr(nullptr), m_size(0), m_tempsize(0), m_reserved(0), m_index(0)
{
	m_ptr = new T[list.size()];
	for (auto element : list)
	{
		this->push_back(element);
	}
	//std::cout << "Constructed!" << std::endl;
}

template<typename T>
Vector<T>::Vector(size_t size) : m_tempptr(nullptr), m_size(size), m_tempsize(0), m_reserved(size), m_index(0)
{
	m_ptr = new T[m_size];
	//std::cout << "Constructed!" << std::endl;
}

template<typename T>
Vector<T>::~Vector()
{
	delete[] m_ptr;
	//std::cout << "Destructed!" << std::endl;
}