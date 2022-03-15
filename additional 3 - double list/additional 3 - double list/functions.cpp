#include <iostream>
#include "functions.hpp"

using namespace std;

namespace ssh {

	void ADD(List* head, int filling)
	{
		List* newone = new List;
		List* t = new List;
		newone->filling = filling;
		t = head->next;

		head->next = newone;
		newone->next = t;
		newone->next->previous = newone;
		newone->previous = head;
	}


	void ADDPOS(List* head, int filling, int position)
	{
		int i = 0;
		List* q = head;
		while (i != position) {
			q = q->previous;
			++i;
		}
		ADD(q, filling);
	}

	void PRINTBEG(List* head)
	{
		List* p = head->previous;
		cout << head->filling << " ";
		while (p != head) //не циклится потому что используются указатели
		{
			cout << p->filling << " ";
			p = p->previous;
		}
		cout << endl;
	}

	void PRINTEND(List* head)
	{
		List* p = head->next;
		while (p != head)
		{
			cout << p->filling << " ";
			p = p->next;
		}
		cout << head->filling << " ";
		cout << endl;
	}

	void DELETE(List* head)
	{
		List* prev;
		List* next;
		next = head->next;
		prev = head->previous;
		head->next->previous = prev;
		head->previous->next = next;
		delete head;
	}

	void CLEAR(List* head)
	{
		List* t;
		List* p = head->next;
		while (p != head)
		{
			t = p;
			p = p->next;
			delete t;
		}
	}
}