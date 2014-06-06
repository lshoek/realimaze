#ifndef LISTOFLINES
#define lISTOFLINES
#include <stdlib.h>
#include <stdio.h> 
#include "Line.h"

typedef struct Node
{
	Line data;
	Node * next;
};

class LineList
{	
public:
	Node * head;
	LineList()
	{
		head = nullptr;
	}
	~LineList()
	{
		printf("dellette");
		while (head != nullptr)
		{
			Node * n = head->next;
			delete head;
			head = n;
		}
	}	
	void add(Line l);
};

void LineList::add(Line l)
{
	Node * n = new Node();
	n->data = l;
	n->next = head;
	head = n;
}

#endif
