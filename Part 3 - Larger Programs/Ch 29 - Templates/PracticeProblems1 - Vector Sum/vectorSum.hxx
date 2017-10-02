#pragma once
#include <vector>

template <typename  Type>
class VectorSum
{
public:
	VectorSum();
	Type sum(const std::vector<Type>& vector);
};

template <typename Type>
VectorSum<Type>::VectorSum()
{}

template <typename Type>
Type VectorSum<Type>::sum(const std::vector<Type>& vector)
{
	Type sum = 0;
	for (typename std::vector<Type>::const_iterator itr = vector.begin(), end = vector.end();
		 itr != end;
		 ++itr)
	{
		sum += *itr;
	}
	
	return sum;
}
