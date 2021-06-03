#include<iostream>

using namespace std;

typedef struct StackNode
{
	double data;
	struct StackNode* next;
}StackNode, * LinkStack;

double InitStack(LinkStack& s)
{
	s = NULL;
	return 1;
}

double Push(LinkStack& s, double new_element)
{
	StackNode* p = new StackNode;
	p->next = s;
	p->data = new_element;
	s = p;
	return 1;
}

double Pop(LinkStack& s, double element_poped)
{
	if (s == NULL)
	{
		return -1;
	}
	element_poped = s->data;
	
	StackNode* p = s;
	s = s->next;
	delete p;
	return element_poped;
}
int Pop(LinkStack& s )
{
	if (s == NULL)
	{
		return -1;
	}
	//element_poped = s->data;

	StackNode* p = s;
	s = s->next;
	delete p;
	return 1;
}

double GetTop(LinkStack s)
{
	if (s != NULL)
	{
		return s->data;
	}
}

int main()
{
	double  arr[5] = { 1,2,3,4,5 };
	LinkStack s;
	InitStack(s);
	for (int i = 0; i <= 4; i++)
	{
		Push(s, arr[i]);
	}
	for (int i = 0; i <= 4; i++)
	{
		cout<<GetTop(s)<<endl;
		Pop(s);
	}
	return 0;

}