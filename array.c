
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array)
{
	double max = *array;
	double * temparr = array;
	while (*temparr != '\0')
	{
		if (*temparr > max)
		{
			max = *temparr;
		}
		temparr ++;
	}
	return max;
}

// Return minimum element of array
double minArray(int n, double * array)
{
	double min = *array;
	double * temparr = array;
	while(*temparr != '\0')
	{
		if(*temparr < min)
		{
			min = *temparr;
		}
		temparr ++;
	}
	return min;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max)
{
	
	return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array)
{
	double * temparri = array;
	int counti = 0;
	while (counti < n - 1)
	{
		int countj = 0;
		while (countj < n - counti - 1)
		{
			double * temparrj = temparri;
			int i = 0;
			while (i < countj)
			{
				temparrj ++;
				i ++;
			}
			
			if (*temparri > *temparrj)
			{
				double temp = *temparri;
				*temparri = *temparrj;
				*temparrj = temp;
			}
			countj ++;
		}
		temparri ++;
		counti ++;
	}
}

// Print array
void printArray(int n, double * array)
{
	double * temparr = array;
	int count = 0;
	while (*temparr != '\0' && count < n)
	{
		printf("%d:%f\n", count, *temparr);
		count ++;
		temparr ++;
	}
}

