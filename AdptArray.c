#include "AdptArray.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement *pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
	PRINT_FUNC printFunc;
} *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
	if (pArr == NULL)
	{
		return NULL;
	}
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc;
	pArr->copyFunc = copyFunc;
	pArr->printFunc = printFunc;
	return pArr;
}
Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement *newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{

		// Extend Array when idx is out of bounds
		if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) == NULL)
		{
			return FAIL;
		}
		// Copy elements to new Array
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;

		// Delete Previous Elements
		if ((pArr->pElemArr)[idx] != NULL)
		{
			pArr->delFunc((pArr->pElemArr)[idx]);
		}

		(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	}
	// Update Array Size
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}
void DeleteAdptArray(PAdptArray pArr)
{
	if (pArr == NULL)
	{
		return;
	}
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
		return pArr->copyFunc((pArr->pElemArr)[idx]);
	}
	return NULL;
}
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
