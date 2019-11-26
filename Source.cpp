/* Bobitan Denisa-Ioana

   Task:

   Implement correctly and efficiently Quick Sort, Heap Sort and Quick Search.
   Compare the 2 sorting methods in average case and compare the worst and best case for quick sort.

   Observations:

   Comparing the 2 sorting methods, in the average case, we observe that as total number of operations, quick sort is more efficient.
   In the best case, quick sort presents a complexity of O(nlogn).
   In the worst case, this method has complexity O(n^2).

   Conclusion:

   Quick sort is more efficient than the heap sort.

*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Profiler.h"

#pragma warning(disable : 4996)

#define MAX_SIZE 10000

FILE *f = fopen("output.txt", "w");

Profiler profiler("BestCase_QSort");

int assignQS, assignHS, compQS, compHS, totalQS, totalHS;

int parent(int i)
{
	return i / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void swapElements(int *a, int i, int j) //swaps elements from position i and j in array a
{
	int aux = a[i];
	a[i] = a[j];
	a[j] = aux;
}

void maxHeapify(int *a, int i, int n)
{
	int l = left(i);
	int r = right(i);
	int max;
	compHS++;
	if ((l < n) && (a[l] > a[i]))
	{
		max = l;
	}
	else
		max = i;
	compHS++;
	if ((r < n) && (a[r] > a[max]))
	{
		max = r;
	}
	if (max != i)
	{
		swapElements(a, i, max);
		assignHS += 3;
		maxHeapify(a, max, n);
	}
}

void buildMaxHeap(int *a, int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		maxHeapify(a, i, n);
}

void heapSort(int *a, int n)
{
	buildMaxHeap(a, n);
	for (int i = n - 1; i >= 1; i--)
	{
		swapElements(a, 0, i);
		assignHS += 3;
		n--;
		maxHeapify(a, 0, n);
	}
}

int partition(int *a, int start, int end)
{
	int x = a[end];
	assignQS++;
	int index = start - 1;
	for (int i = start; i <= end - 1; i++)
	{
		compQS++;
		if (a[i] <= x)
		{
			index++;
			swapElements(a, i, index);
			assignQS += 3;
		}
	}
	swapElements(a, end, index + 1);
	assignQS += 3;
	return index + 1;
}

void quickSort(int *a, int start, int end)
{
	if (start < end)
	{
		int p = partition(a, start, end); //pivot is taken the last element 
		quickSort(a, start, p - 1);
		quickSort(a, p + 1, end);
	}
}

void quickSortBestCase(int *a, int start, int end) //the pivot is chosen in the middle
{
	int s, f;
	s = start;
	f = end;
	int p = (start + end) / 2;
	while (s <= f)
	{
		compQS++;
		while (a[s] < a[p])
		{
			s++;
			compQS++;
		}
		compQS++;
		while (a[f] > a[p])
		{
			f--;
			compQS++;
		}
		if (s <= f)
		{
			swapElements(a, s, f);
			assignQS += 3;
			s++;
			f--;
		}
	}
	if (s < end)
	{
		quickSortBestCase(a, start, s);
	}
	if (f > start)
	{
		quickSortBestCase(a, f, end);
	}
}

int partitionRand(int *a, int start, int end) //the only difference from the simple partition function is the random index choice; after that, the element on that position and the last element are swapped
{
	int pos = rand() % ((end - 1) + start);
	int x = a[pos];
	assignQS++;
	swapElements(a, pos, end);
	int index = start - 1;
	for (int i = start; i <= end - 1; i++)
	{
		compQS++;
		if (a[i] <= x)
		{
			index++;
			swapElements(a, i, index);
			assignQS += 3;
		}
	}
	swapElements(a, end, index + 1);
	assignQS += 3;
	return index + 1;
}

int quickSelect(int *a, int k, int start, int end)
{
	if (start >= end)
	{
		return a[start];
	}
	int p = partitionRand(a, start, end);
	int rel_pos = p - start + 1;
	if (rel_pos == k)
	{
		return a[p];
	}
	else if (rel_pos > k)
	{
		return quickSelect(a, k, start, p - 1);
	}
	else //rel_pos<k
	{
		return quickSelect(a, k - rel_pos, p + 1, end);
	}
}

void scanArray(int *a, int *n)
{
	printf("Enter array length: ");
	scanf("%d", n);
	printf("Enter array: ");
	for (int i = 0; i < *n; i++)
	{
		scanf("%d", &a[i]);
	}
}

void printArray(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		fprintf(f, "%d ", a[i]);
	}
	fprintf(f, "\n");
}

void testQSort(int *a, int n)
{
	int *b = (int*)malloc(n * sizeof(int));
	CopyArray(b, a, n);

	quickSort(a, 0, n - 1);
	fprintf(f, "Array sorted with quick sort (pivot chosen last): ");
	printArray(a, n);

	quickSortBestCase(b, 0, n - 1);
	fprintf(f, "Array sorted with quick sort (pivot chosen in the middle): ");
	printArray(a, n);
}

void testHSort(int *a, int n)
{
	heapSort(a, n);
	fprintf(f, "Array sorted with heap sort: ");
	printArray(a, n);
}

void testQSelect(int *a, int n)
{
	int k;
	printf("Enter k: ");
	scanf("%d", &k);
	int x = quickSelect(a, k, 0, n - 1);
	fprintf(f, "The %d-th element in the sorted array is %d\n", k, x);
}

void initializeGlobalVariables()
{
	assignQS = 0;
	assignHS = 0;
	compQS = 0;
	compHS = 0;
	totalQS = 0;
	totalHS = 0; //inititalize global variables
}

void profilerOperations(const char *aqs, const char *ahs, const char *cqs, const char *chs, const char *tqs, const char *ths)
{
	//function to avoid writing the createGroup methods multiple times in multiple functions

	if ((aqs != NULL) && (ahs != NULL) && (cqs != NULL) && (chs != NULL) && (tqs != NULL) && (ths != NULL)) //if all parameters exist, display them
	{
		profiler.createGroup("Assignments", aqs, ahs);
		profiler.createGroup("Comparisons", chs, cqs);
		profiler.createGroup("TotalOperations", ths, tqs);
	}
	if ((aqs != NULL) && (cqs != NULL) && (tqs != NULL)) //if parameters for quick sort exist, display them separately
	{
		profiler.createGroup("AssignQS", aqs);
		profiler.createGroup("CompQS", cqs);
		profiler.createGroup("TotalQS", tqs);
	}
	if ((ahs != NULL) && (chs != NULL) && (ths != NULL)) //if parameters for heap sort exist, display them separately
	{
		profiler.createGroup("AssignHS", ahs);
		profiler.createGroup("CompHS", chs);
		profiler.createGroup("TotalHS", ths);
	}
}

void profilerReportBest() //for the best case, we use the quick sort method that chooses the pivot in the middle
{
	int a[MAX_SIZE], b[MAX_SIZE];

	FillRandomArray(a, MAX_SIZE, 10, 50000, true, 1); //the array must be sorted ascendingly

	for (int i = 100; i < MAX_SIZE; i += 100)
	{
		initializeGlobalVariables();

		CopyArray(b, a, i);
		quickSortBestCase(b, 0, i - 1);

		totalQS = assignQS + compQS;

		profiler.countOperation("assignQS", i, assignQS);
		profiler.countOperation("compQS", i, compQS);
		profiler.countOperation("totalQS", i, totalQS);
	}
	profilerOperations("assignQS", "", "compQS", "", "totalQS", "");
}

void profilerReportWorst() //for the worst case, we take the array sorted ascendingly, so that the chosen pivot is always the maximum element in the array
{
	profiler.reset("WorstCase_QSort");

	int a[MAX_SIZE], b[MAX_SIZE];

	FillRandomArray(a, MAX_SIZE, 10, 50000, true, 1);

	for (int i = 100; i < MAX_SIZE; i += 100)
	{
		initializeGlobalVariables();

		CopyArray(b, a, i);
		quickSort(b, 0, i - 1);

		totalQS = assignQS + compQS;

		profiler.countOperation("assignQS", i, assignQS);
		profiler.countOperation("compQS", i, compQS);
		profiler.countOperation("totalQS", i, totalQS);
	}
	profilerOperations("assignQS", "", "compQS", "", "totalQS", "");
}

void profilerReportAverage()
{
	profiler.reset("AverageCase_HSort_QSort");

	int a[MAX_SIZE], b[MAX_SIZE];

	for (int i = 100; i < MAX_SIZE; i += 100)
	{
		initializeGlobalVariables();

		for (int j = 0; j < 5; j++)
		{
			FillRandomArray(a, i, 10, 50000, true, 0);

			CopyArray(b, a, i);
			heapSort(b, i);

			CopyArray(b, a, i);
			quickSort(b, 0, i - 1);
		}

		assignHS /= 5;
		compHS /= 5;
		totalHS = assignHS + compHS;

		assignQS /= 5;
		compQS /= 5;
		totalQS = assignQS + compQS;

		profiler.countOperation("assignHS", i, assignHS);
		profiler.countOperation("compHS", i, compHS);
		profiler.countOperation("totalHS", i, totalHS);

		profiler.countOperation("assignQS", i, assignQS);
		profiler.countOperation("compQS", i, compQS);
		profiler.countOperation("totalQS", i, totalQS);
	}
	profilerOperations("assignQS", "assignHS", "compQS", "compHS", "totalQS", "totalHS");
}

int main()
{
	/*
	int a[100], b[100], n;

	scanArray(a, &n);

	CopyArray(b, a, n);
	testHSort(b, n);

	CopyArray(b, a, n);
	testQSort(b, n);


	CopyArray(b, a, n);
	testQSelect(b, n);

	fclose(f);
	*/

	//profilerReportBest();
	profilerReportWorst();
	//profilerReportAverage();

	profiler.showReport();
	
	return 0;
}