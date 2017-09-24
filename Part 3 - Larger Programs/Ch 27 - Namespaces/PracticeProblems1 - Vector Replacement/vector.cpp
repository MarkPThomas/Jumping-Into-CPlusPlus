#include "vector.h"

namespace MPT
{
	namespace JICPP
	{
		/// <summary>
		/// Initializes a new instance of the <see cref="VectorOfInt"/> class by allocateing a 32-element vector.
		/// </summary>
		VectorOfInt::VectorOfInt()
		{
			_integersLength = 32;
			_integersLengthUsed = _integersLength;
			_integers = new int[_integersLengthUsed];
		}

		/// <summary>
		/// Initializes a new instance of the <see cref="VectorOfInt"/> class to the specified size.
		/// </summary>
		/// <param name="initialSize">The initial size.</param>
		VectorOfInt::VectorOfInt(int initialSize)
		{
			_integersLength = initialSize;
			_integersLengthUsed = _integersLength;
			_integers = new int[_integersLengthUsed];
		}

		VectorOfInt::VectorOfInt(const VectorOfInt& other)
		{
			CopyValues(other);
		}

		VectorOfInt::~VectorOfInt()
		{
			delete[] _integers;
		}

		int* VectorOfInt::GetInt(int index) const
		{
			if ((index < 0) ||
				(index > _integersLengthUsed - 1))
			{
				return nullptr;
			}

			return &_integers[index];
		}

		void VectorOfInt::SetInt(int index, int value) const
		{
			if ((index < 0) ||
				(index > _integersLengthUsed - 1))
			{
				return;
			}

			_integers[index] = value;
		}

		/// <summary>
		/// // Adds element to the end of the array.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>int.</returns>
		void VectorOfInt::PushBack(int value)
		{
			_integersLengthUsed++;
			if (_integersLengthUsed > _integersLength)
			{
				_integers = growArray(_integers, &_integersLength);
			}
			_integers[_integersLengthUsed - 1] = value;
		}

		/// <summary>
		/// Adds element to the front of the array.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>int.</returns>
		void VectorOfInt::PushFront(int value)
		{
			_integersLengthUsed++;
			if (_integersLengthUsed > _integersLength)
			{
				_integers = growArray(_integers, &_integersLength);
			}

			// Shift all vaues forward by 1 index.
			for (int i = _integersLengthUsed; i > 0; i--)
			{
				_integers[i] = _integers[i - 1];
			}
			_integers[0] = value;
		}

		void VectorOfInt::Clear()
		{
			_integersLength = 0;
			_integersLengthUsed = _integersLength;
			delete _integers;
			_integers = new int[_integersLength];
		}

		VectorOfInt& VectorOfInt::operator=(const VectorOfInt& other)
		{
			if (this == &other)
			{
				return *this;
			}

			delete[] _integers;
			_integers = nullptr;

			CopyValues(other);

			return *this;
		}

		void VectorOfInt::CopyValues(const VectorOfInt& other)
		{
			_integersLength = other._integersLength;
			_integers = new int[_integersLength];

			_integersLengthUsed = other._integersLengthUsed;
			for (int i = 0; i < _integersLengthUsed; i++)
			{
				int* value = other.GetInt(i);
				if (value)
				{
					_integers[i] = *value;
				}
			}
		}

		int* VectorOfInt::growArray(int* p_values, int* size)
		{
			// Double the size of the array.
			// It is more efficient to always make the array larger than needed, than to increase the size of the array with each additional element.
			*size *= 2;

			// Create a new array of the new size and copy all current array values over.
			int* p_newvalues = new int[*size];
			for (size_t i = 0; i < *size; i++)
			{
				p_newvalues[i] = p_values[i];
			}

			// Remove the current array to free up memory (i.e. avoid a memory leak).
			delete[] p_values;

			return p_newvalues;
		}
	}
}