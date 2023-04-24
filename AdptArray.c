#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Define a struct to represent an adaptive array
typedef struct AdptArray_
{
	int ArrSize;
	PElement *pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
} *PAdptArray;

// Create a new adaptive array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc)
{
	// Allocate memory for the adaptive array struct
	PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (pArr == NULL)
	{
		return NULL;
	}
	// Initialize the fields of the adaptive array struct
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc;
	pArr->copyFunc = copyFunc;
	pArr->printFunc = printFunc;
	return pArr;
}
// Set an element in the adaptive array at the given index
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement *newpElemArr;
	if (pArr == NULL)
		return FAIL;

	// If the index is out of bounds, extend the array
	if (idx >= pArr->ArrSize)
	{

		// Extend Array when idx is out of bounds
		if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
		{
			return FAIL;
		}
		// Copy elements to the new array
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		// Free the old array
		free(pArr->pElemArr);
		// Update the pointer to the array to point to the new array
		pArr->pElemArr = newpElemArr;

		// Delete Previous Elements
		if ((pArr->pElemArr)[idx] != NULL)
		{
			pArr->delFunc((pArr->pElemArr)[idx]);
		}
		// Copy the new element to the array at the index
		(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	}
	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}
// Delete the adaptive array
void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return;
	}
	// Delete each element in the array and free the array
	for (int i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL)
		{
			pArr->delFunc((pArr->pElemArr)[i]);
		}
	}
	free(pArr->pElemArr);
	free(pArr);
}
// Get the element at the given index in the adaptive array
PElement GetAdptArrayAt(PAdptArray pArr, int idx)
{
	if (pArr == NULL)
	{
		return NULL;
	}
	if ((idx >= pArr->ArrSize) || idx < 0)
	{
		return FAIL;
	}
	if (pArr->pElemArr[idx] != NULL)
	{	
		// Saves a copy of the element in the specific index
		return pArr->copyFunc((pArr->pElemArr)[idx]);
	}
	return NULL;
}
// Gets the size of the adaptive array
int GetAdptArraySize(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return -1;
	}
	else
	{
		return pArr->ArrSize;
	}
}
// Prints each element in the adaptive array 
void PrintDB(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return;
	}
	for (int i = 0; i < pArr->ArrSize; i++)
	{
		if (pArr->pElemArr[i] != NULL)
		{
			pArr->printFunc(pArr->pElemArr[i]);
		}
	}
}
