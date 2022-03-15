#pragma once

namespace ssh 
{

	struct List
	{
		List* next;
		int filling;
	};

	void ADD(List* head, int filling);

	void ADDPOS(List* head, int filling, int position);

	void PRINT(List* head);

	void CLEAR(List* head);

	void AddToArr(int* array, int n, int position, int filling);

	void PrintArr(int* array, int n);
	void PrintArr(int* array, int n);
}