#pragma once

namespace MPT
{
	namespace JICPP
	{
		class VectorOfInt
		{
		public:
			VectorOfInt(); // Allocates a 32-element vector
			VectorOfInt(int initialSize);
			VectorOfInt(const VectorOfInt& other);
			~VectorOfInt();

			int* GetInt(int index) const;
			void SetInt(int index, int value) const;

			void PushBack(int value); // Adds element to the end of the array
			void PushFront(int value); // Adds element to the front of the array
			void Clear();

			VectorOfInt& operator=(const VectorOfInt& other);
		private:
			int* _integers;
			int _integersLengthUsed;
			int _integersLength;

			void CopyValues(const VectorOfInt& other);
			static int* growArray(int* p_values, int* size);
		};
	}
}