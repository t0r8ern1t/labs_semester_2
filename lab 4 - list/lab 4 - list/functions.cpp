#include <iostream>
#include "functions.hpp"

using namespace std;

namespace ssh {

	void ADD(List* head, int filling)
	{
		List* p = new List;
		p->filling = filling;

		p->next = head->next;
		head->next = p;
	}


	void ADDPOS(List* head, int filling, int position)
	{
		int i = 0;
		List* q = head;
		while (i != position) {
			q = q->next;
			++i;
		}
		ADD(q, filling);
	}

	void PRINT(List* head)
	{
		List* p = head->next;
		while (p != nullptr)
		{
			cout << p->filling << " ";
			p = p->next;
		}
		cout << endl;
	}

	void CLEAR(List* head)
	{
		List* t;
		List* p = head->next;
		while (p != nullptr)
		{
			t = p;
			p = p->next;
			delete t;
		}
	}

	void AddToArr(int* array, int n, int position, int filling)
	{
		for (int i = n + 1; i > position; --i)
		{
			array[i] = array[i - 1];
		}
		array[position] = filling;
	}

	void PrintArr(int* array, int n)
	{
		for (int i = 0; i < n; ++i)
		{
			cout << array[i] << " ";
		}
		cout << endl;
	}
}