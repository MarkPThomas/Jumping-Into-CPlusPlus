#pragma once

template <typename  Type>
class VectorOf
{
public:
	VectorOf(); // Allocates a 32-element vector
	VectorOf(int initialSize);
	VectorOf(const VectorOf<Type>& other);
	~VectorOf();

	Type * Get(int  index) const;
	void Set(int index, Type  value) const;

	void PushBack(Type  value); // Adds element to the end of the array
	void PushFront(Type  value); // Adds element to the front of the array
	void Clear();

	VectorOf<Type>& operator=(const VectorOf<Type>& other);
private:
	Type* _values;
	int _valuesLengthUsed;
	int _valuesLength;

	void CopyValues(const VectorOf<Type>& other);
	static Type * growArray(Type * p_values, int* size);
};

/// <summary>
/// Initializes a new instance of the <see cref="VectorOfInt"/> class by allocateing a 32-element vector.
/// </summary>
template <typename Type>
VectorOf<Type>::VectorOf()
{
	_valuesLength = 32;
	_valuesLengthUsed = _valuesLength;
	_values = new Type[_valuesLengthUsed];
}

/// <summary>
/// Initializes a new instance of the <see cref="VectorOfInt"/> class to the specified size.
/// </summary>
/// <param name="initialSize">The initial size.</param>
template <typename Type>
VectorOf<Type>::VectorOf(int initialSize)
{
	_valuesLength = initialSize;
	_valuesLengthUsed = _valuesLength;
	_values = new Type[_valuesLengthUsed];
}

template <typename Type>
VectorOf<Type>::VectorOf(const VectorOf<Type>& other)
{
	CopyValues(other);
}

template <typename Type>
VectorOf<Type>::~VectorOf()
{
	delete[] _values;
}

template <typename Type>
Type* VectorOf<Type>::Get(int index) const
{
	if ((index < 0) ||
		(index > _valuesLengthUsed - 1))
	{
		return nullptr;
	}

	return &_values[index];
}

template <typename Type>
void VectorOf<Type>::Set(int index, Type value) const
{
	if ((index < 0) ||
		(index > _valuesLengthUsed - 1))
	{
		return;
	}

	_values[index] = value;
}

/// <summary>
/// // Adds element to the end of the array.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>int.</returns>
template <typename Type>
void VectorOf<Type>::PushBack(Type value)
{
	_valuesLengthUsed++;
	if (_valuesLengthUsed > _valuesLength)
	{
		_values = growArray(_values, &_valuesLength);
	}
	_values[_valuesLengthUsed - 1] = value;
}

/// <summary>
/// Adds element to the front of the array.
/// </summary>
/// <param name="value">The value.</param>
/// <returns>int.</returns>
template <typename Type>
void VectorOf<Type>::PushFront(Type value)
{
	_valuesLengthUsed++;
	if (_valuesLengthUsed > _valuesLength)
	{
		_values = growArray(_values, &_valuesLength);
	}

	// Shift all vaues forward by 1 index.
	for (int i = _valuesLengthUsed; i > 0; i--)
	{
		_values[i] = _values[i - 1];
	}
	_values[0] = value;
}

template <typename Type>
void VectorOf<Type>::Clear()
{
	_valuesLength = 0;
	_valuesLengthUsed = _valuesLength;
	delete[] _values;
	_values = new Type[_valuesLength];
}

template <typename Type>
VectorOf<Type>& VectorOf<Type>::operator=(const VectorOf<Type>& other)
{
	if (this == &other)
	{
		return *this;
	}

	delete[] _values;
	_values = nullptr;

	CopyValues(other);

	return *this;
}

template <typename Type>
void VectorOf<Type>::CopyValues(const VectorOf<Type>& other)
{
	_valuesLength = other._valuesLength;
	_values = new Type[_valuesLength];

	_valuesLengthUsed = other._valuesLengthUsed;
	for (int i = 0; i < _valuesLengthUsed; i++)
	{
		Type* value = other.Get(i);
		if (value)
		{
			_values[i] = *value;
		}
	}
}

template <typename Type>
Type* VectorOf<Type>::growArray(Type* p_values, int* size)
{
	int oldSize = *size;
	// Double the size of the array.
	// It is more efficient to always make the array larger than needed, than to increase the size of the array with each additional element.
	*size *= 2;

	// Create a new array of the new size and copy all current array values over.
	Type* p_newvalues = new Type[*size];
	for (size_t i = 0; i < oldSize; i++)
	{
		p_newvalues[i] = p_values[i];
	}

	// Remove the current array to free up memory (i.e. avoid a memory leak).
	delete[] p_values;

	return p_newvalues;
}