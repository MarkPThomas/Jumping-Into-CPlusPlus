#include <iostream>
#include "vector.h"

using namespace std;
using namespace MPT;

void print(JICPP::VectorOfInt& vector);

int main()
{
	JICPP::VectorOfInt basicVector;
	for (int i = 0; i < 32; i++)
	{
		basicVector.SetInt(i, i + 1);
	}
	cout << "Basic Vector\n";
	print(basicVector);

	int vectorSize = 10;
	JICPP::VectorOfInt sizedVector(vectorSize);
	for (int i = 0; i < vectorSize; i++)
	{
		sizedVector.SetInt(i, i * i);
	}
	cout << "Vector Sized to " << vectorSize << '\n';
	print(sizedVector);

	JICPP::VectorOfInt copiedVector(sizedVector);
	cout << "Copied Vector Upon Initialization from Sized Vector\n";
	print(copiedVector);

	JICPP::VectorOfInt copiedVectorOperator;
	copiedVectorOperator = basicVector;
	cout << "Copied Vector Operator from Basic Vector\n";
	print(copiedVectorOperator);

	int value1 = 50;
	cout << "Adding " << value1 << " to the end of Sized Vector\n"; // This should also resize the vector.
	sizedVector.PushBack(value1);

	int value2 = -12;
	cout << "Adding " << value2 << " to the end of Sized Vector\n"; // This should not resize the vector.
	sizedVector.PushBack(value2);
	print(sizedVector);

	int value3 = -666;
	cout << "Adding " << value3 << " to the beginning of Copied Vector\n"; // This should also resize the vector.
	copiedVector.PushFront(value3);

	int value4 = 999;
	cout << "Adding " << value4 << " to the beginning of Copied Vector\n"; // This should not resize the vector.
	copiedVector.PushFront(value4);
	print(copiedVector);

	cout << "Clearing Basic Vector\n";
	basicVector.Clear();
	print(basicVector);
}

void print(JICPP::VectorOfInt& vector)
{
	cout << "Vector Values...\n";
	int index = 0;
	while (vector.GetInt(index))
	{
		cout << *vector.GetInt(index) << '\n';
		index++;
	}
	cout << '\n';
}