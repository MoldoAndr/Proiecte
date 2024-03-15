#ifndef VECTOR_H
#define VECTOR_H
#include "Exceptie_Logica.h"

template<class T>
	class Vector
{
public:
	Vector() :
		data{ nullptr }, capacity{ 0 }, size{ 0 } {}
	~Vector()
	{
		for (size_t i{}; i < size; ++i)
		{
			if (data[i] != nullptr)
			delete data[i];
		}
		delete[] data;
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	void push_back(const T& value)
	{
		if (size >= capacity)
		{
			if (capacity == 0)
			{
				capacity = 1;
			}
			else
			{
				capacity *= 2;
			}
			T* aux_data = new T[capacity];
			for (size_t i{}; i < size; ++i)
				aux_data[i] = data[i];
			delete[] data;
			data = aux_data;
		}
		data[size++] = value;
	}
	const T& at(size_t index) const
	{
		if (index >= size || index < 0)
			throw Exceptie_Logica(1);
		return data[index];
	}
	size_t getSize() const
	{
		return size;
	}
	T& operator[](size_t index)
	{
		if (index >= size || index < 0)
			throw Exceptie_Logica(1);
		return data[index];
	}
	friend std::ostream& operator<<
		(std::ostream& out, Vector& vect)
	{
		for (size_t i{}; i < vect.getSize(); ++i)
			out << vect[i] << ' ';
		out << '\n';
		return out;
	}
private:
	T*			data{ nullptr };
	size_t		capacity{};
	size_t		size{};
};

#endif