#include <iostream>
#include <string>
#include <typeinfo>
#include "vectorOf.hxx"

using namespace std;

template <typename Type>
void print(VectorOf<Type>& vector)
{
	cout << "Vector Values...\n";
	int index = 0;
	while (vector.Get(index))
	{
		cout << *vector.Get(index) << '\n';
		index++;
	}
	cout << '\n';
}


template <typename Type>
void run(Type* defaultInitializationValues, const Type* sizedValues, int sizedSize, Type value1, Type value2, Type value3, Type value4)
{
	cout << "Testing Template VectorOf<T> class of T = " << typeid(Type).name() << '\n';
	
	VectorOf<Type> basicVector;
	for (int i = 0; i < 32; i++)
	{
		basicVector.Set(i, defaultInitializationValues[i]);
	}
	cout << "Basic Vector\n";
	print(basicVector);

	VectorOf<Type> sizedVector(sizedSize);
	for (int i = 0; i < sizedSize; i++)
	{
		sizedVector.Set(i, sizedValues[i]);
	}
	cout << "Vector Sized to " << sizedSize << '\n';
	print(sizedVector);

	VectorOf<Type> copiedVector(sizedVector);
	cout << "Copied Vector Upon Initialization from Sized Vector\n";
	print(copiedVector);

	VectorOf<Type> copiedVectorOperator;
	copiedVectorOperator = basicVector;
	cout << "Copied Vector Operator from Basic Vector\n";
	print(copiedVectorOperator);

	cout << "Adding " << value1 << " to the end of Sized Vector\n"; // This should also resize the vector.
	sizedVector.PushBack(value1);

	cout << "Adding " << value2 << " to the end of Sized Vector\n"; // This should not resize the vector.
	sizedVector.PushBack(value2);
	print(sizedVector);

	cout << "Adding " << value3 << " to the beginning of Copied Vector\n"; // This should also resize the vector.
	copiedVector.PushFront(value3);

	cout << "Adding " << value4 << " to the beginning of Copied Vector\n"; // This should not resize the vector.
	copiedVector.PushFront(value4);
	print(copiedVector);

	cout << "Clearing Basic Vector\n";
	basicVector.Clear();
	print(basicVector);
}

int main()
{
	int arraySize = 10;

	// Int
	int* defaultInitializationValuesInt = new int[32];
	for (int i = 0; i < 32; i++)
	{
		defaultInitializationValuesInt[i] = i + 1;
	}

	int* sizedValuesInt = new int[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		sizedValuesInt[i] = i * i;
	}

	int valueInt1 = 50;
	int valueInt2 = -12;
	int valueInt3 = -666;
	int valueInt4 = 999;

	run(defaultInitializationValuesInt, sizedValuesInt, arraySize, valueInt1, valueInt2, valueInt3, valueInt4);
	system("pause");

	// Double
	double counter = 0;
	double* defaultInitializationValuesDbl = new double[32];
	for (int i = 0; i < 32; i++)
	{
		defaultInitializationValuesDbl[i] = counter + (1.3 / (counter + 1));
		counter++;
	}

	counter = 0;
	double* sizedValuesDbl = new double[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		sizedValuesDbl[i] = counter * (counter /(counter + 1)) + 0.1;
		counter++;
	}

	double valueDbl1 = 50.342;
	double valueDbl2 = -12.99;
	double valueDbl3 = -666.99;
	double valueDbl4 = 999.66;

	run(defaultInitializationValuesDbl, sizedValuesDbl, arraySize, valueDbl1, valueDbl2, valueDbl3, valueDbl4);
	system("pause");

	// String
	counter = 0;
	string* defaultInitializationValuesStr = new string[32];
	for (int i = 0; i < 32; i++)
	{
		defaultInitializationValuesStr[i] = "Value = " + to_string(counter + (1.3 / (counter + 1)));
		counter++;
	}

	counter = 0;
	string* sizedValuesStr = new string[arraySize];
	for (int i = 0; i < arraySize; i++)
	{
		sizedValuesStr[i] = "Value = " + to_string(counter * (counter / (counter + 1)) + 0.1);
		counter++;
	}

	string valueStr1 = "Foo";
	string valueStr2 = "Bar";
	string valueStr3 = "Moo";
	string valueStr4 = "Nar";

	run(defaultInitializationValuesStr, sizedValuesStr, arraySize, valueStr1, valueStr2, valueStr3, valueStr4);
	system("pause");
}
