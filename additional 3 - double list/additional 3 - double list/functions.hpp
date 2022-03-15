#pragma once

namespace ssh 
{

	struct List
	{
		List* next;
		List* previous;
		int filling;
	};

	void ADD(List* head, int filling);

	void ADDPOS(List* head, int filling, int position);

	void PRINTBEG(List* head);

	void PRINTEND(List* head);

	void DELETE(List* head);

	void CLEAR(List* head);
}