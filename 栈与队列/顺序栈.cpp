#include<iostream>
#define MAXSIZE 100
using namespace std;
//规定1为true , 0为false
typedef struct
{
	double* top;
	double* base;
	int stacksize;
}Sqstack;

void Init(Sqstack& s)
{
	s.base = new double[MAXSIZE];
	if (!s.base)
	{
		cout << "ERROR" << endl;
	}
	s.top = s.base;
	s.stacksize = MAXSIZE;
	cout << "初始化成功" << endl;
}

void Push(Sqstack& s,double new_element)
{
	if ((s.top - s.base) == MAXSIZE)
	{
		cout << "栈满啦-_-"<<endl;
		 
	}
	*s.top = new_element;
	s.top = s.top + 1;
	cout << "压栈成功" << endl;
	
}
void Pop(Sqstack& s)
{
	if (s.base == s.top)
	{
		cout << "已经空了" << endl;
		 
	}
	--s.top;
	 
}
double Get_topElement(Sqstack s)
{
	if (s.base != s.top)
	{
		return *(s.top - 1);
	}
}

int main()
{
	double arr[5] = { 1.1,2.2,3.3,4.4,5.5 };
	Sqstack s;
	Init(s);
	Push(s, arr[0]);
	Push(s, arr[1]);
	Push(s, arr[2]);
	Push(s, arr[3]);
	Push(s, arr[4]);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	Pop(s);
	cout << Get_topElement(s) << endl;
	return 0;
}	

