/// @author Krishna Kant Verma
/// @date April 10 2023
/// @brief Program to Find Maximum Points That We Can Get (0/1 Knapsack)
// Assignment 11

/// @headerfile
#include <iostream>
/// @brief using namespace as standard
using namespace std;

/// @brief main function starts here
int main()
{

	// taking input no of tasks
	cout << "Enter Number of Tasks: ";
	int noOfTask;
	cin >> noOfTask;
	// capacity is 24 (can't  be more than 24)
	int capacity = 24;

	// creating 3 aray to store label,value and time
	string label[noOfTask];
	int value[noOfTask];
	int timeArr[noOfTask];

	// taking input
	for (int i = 0; i < noOfTask; i++)
	{
		cin >> label[i] >> value[i] >> timeArr[i];
	}

	// creating dp array to store computed answer to use it in future calculations
	int dpArray[noOfTask + 1][capacity + 1];
	for (int i = 0; i <= noOfTask; i++)
	{
		for (int j = 0; j <= 24; j++)
		{
			dpArray[i][j] = 0;
		}
	}

	// filling DP array and computing answer
	for (int index = 1; index <= noOfTask; index++)
	{
		int takeCase = -1e9, nonTakeCase = -1e9;
		for (int capacity = 1; capacity <= 24; capacity++)
		{
			// case 1 : take case (if capacity available for the current index profit take that value)
			if (timeArr[index - 1] <= capacity)
			{
				takeCase = value[index - 1] + dpArray[index - 1][capacity - timeArr[index - 1]];
			}
			// case 2 : non take case if we are not considering the current value
			nonTakeCase = dpArray[index - 1][capacity];

			// storing current state (max of takecase and non take case)
			dpArray[index][capacity] = max(takeCase, nonTakeCase);
		}
	}

	// printing answer
	cout << "\nMaximum Points That Can Get: " << dpArray[noOfTask][capacity] << endl;
	cout << "The Task That are Selected are Following : ";

	// backtracking step
	int val = dpArray[noOfTask][capacity];
	int cap = capacity;
	int i = noOfTask;
	while (i > 0 and val >=
						 0)
	{
		// if ith state is same as i-1th state (dont consider and decrement i)
		if (val == dpArray[i - 1][cap])
		{
			i--;
			continue;
		}
		else
		{
			// otherwise backtracking step
			cout << label[i - 1] << " ";
			// decresing value
			val = val - value[i - 1];
			// decresing capacity
			cap = cap - timeArr[i - 1];
			i--;
		}
	}
	return 0;
}

// Time Complexity : O(noOfTask*24);
// Space Complexity : O(noOfTask*24);
