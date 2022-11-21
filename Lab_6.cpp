// Lab_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

int main()
{
	const int size = 2000;
	int mas[size] = {};
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		mas[i] = i;
		sum += i;
	}
	cout << "Simple sum: " << sum << endl;

	const int part_count = 10;
	int part_sums[part_count] = {};
	int part_length = size / part_count;
	for (int i = 0; i < part_count; i++)
	{
		int part_adder = i * part_length;
		for (int j = 0; j < part_length; j++)
		{
			part_sums[i] += mas[part_adder + j];
		}
	}
	sum = 0;
	for (int i = 0; i < part_count; i++)
	{
		sum += part_sums[i];
	}
	cout << "Method 1 sum: " << sum << endl;

	int size_to_modify = size;
	do
	{
		for (int i = 0; i < size_to_modify / 2; i++)
		{
			int end = size_to_modify - 1 - i;
			mas[i] += mas[end];
		}
		size_to_modify = size_to_modify / 2 + size_to_modify % 2;
	}
	while (size_to_modify > 1);
	sum = mas[0];
	cout << "Method 2 sum: " << sum << endl;

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
