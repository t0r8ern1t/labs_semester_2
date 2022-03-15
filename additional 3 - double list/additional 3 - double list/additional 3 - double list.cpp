#include <iostream>
#include "functions.hpp"

using namespace ssh;

int main()
{
    List* head = new List;
    head->previous = head;
    head->next = head;
    head->filling = 0;

    ADD(head, 1);
    ADD(head, 2);
    ADD(head, 3);
    ADD(head, 4);
    ADD(head, 1);
    PRINTBEG(head);
    ADDPOS(head, 5, 1);
    ADDPOS(head, 123, 5);
    ADDPOS(head, 111, 8);
    PRINTBEG(head);
    DELETE(head->next);
    DELETE(head->previous);
    PRINTEND(head);

    CLEAR(head);
    delete head;
}