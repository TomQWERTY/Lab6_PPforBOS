// Lab_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int Method_1(int* mas, int size)
{
	const int part_count = 10;
	int part_sums[part_count] = {};
	int part_length = size / part_count;
	int sum = 0;
#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < part_count; i++)
	{
		int part_adder = i * part_length;
		for (int j = 0; j < part_length; j++)
		{
			sum += mas[part_adder + j];
		}
	}
	return sum;
}

/*int Method_2(int* mas, int size)
{
	do
	{
#pragma omp parallel for
		for (int i = 0; i < size / 2; i++)
		{
			int end = size - 1 - i;
			mas[i] += mas[end];
		}
		size = size / 2 + size % 2;
	} while (size > 1);
	int sum = mas[0];
	return sum;
}
*/

int Method_2(int* mas, int size_given)
{
#pragma omp parallel num_threads(size_given / 2)
	{
		int i = omp_get_thread_num();
		int size = size_given;
		do
		{
			if (i < size / 2)
			{
				int end = size - 1 - i;
				mas[i] += mas[end];
			}
#pragma omp barrier
			size = size / 2 + size % 2;
		} while (size > 1);
	}
	int sum = mas[0];
	return sum;
}

int main()
{
	const int size = 1000;
	int mas[size] = {};
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		mas[i] = i;
		sum += i;
	}
	cout << "Simple sum: " << sum << endl;

	sum = Method_1(mas, size);
	cout << "Method 1 sum: " << sum << endl;

	sum = Method_2(mas, size);
	cout << "Method 2 sum: " << sum << endl;

	srand(time(NULL));
	int ind = rand() % 1000;
	int min = -20;
	mas[ind] = -20;
	cout << "Negative " << min << " number is on " << ind << " position" << endl;
	ind = -1;
	min = INT_MAX;
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		if (mas[i] < min)
		{
			min = mas[i];
			ind = i;
		}
	}
	cout << "Minimal number is " << min << " on " << ind << " position" << endl;

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
