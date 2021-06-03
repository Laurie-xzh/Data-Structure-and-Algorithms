#include<iostream>
#include<string>
#define MAXLEN 255

using namespace std;
typedef struct 
{
	char ch[MAXLEN + 1];
	int length;
}SString;


void get_nextval(SString T, int nextval[])
{
	//cout << "------------- "<< endl;
	int i = 1;
	//cout << "-----" << endl;
	nextval[1] = 0;
	int j = 0;
	//cout <<"------"<< endl;
	while (i < T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			++i;
			++j;
			if (T.ch[i] != T.ch[j])
			{
				nextval[i] = j;
			}
			else
			{
				nextval[i] = nextval[j];
			}
		}
		else
		{
			j = nextval[j];
		}
	}


}
int Index_KMP(SString S, SString T)
{
	int next[255];
	int i = 0;
	int j = 0;
	cout << S.length << endl;
	cout << T.length << endl;

	get_nextval(T,next);
	while (i <S.length && j < T.length)//这里不能加等号
	{
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	if (j >= T.length)
	{
		cout << "yep" << endl;
		return i - T.length;
	}
	else
	{
		cout << "锤子，failed" << endl;
		return 0;
	}
}



int main()
{

	string s = "abcdeefghijklmnn";
	SString S;
	for(int i = 0;i<=s.length();i++)
	{
		S.ch[i] = s[i];
	}
	S.length = s.length();
	cout << S.ch << endl;
	string t;
	SString T;
	cout << "输入你要的模式串" << endl;
	cin >> t;
	int j = t.length();
	for (int i = 0; i <=j; i++)//等号不能丢
	{
		 T.ch[i]=t[i];
	}
	T.length = t.length();
	cout << T.ch << endl;
	cout << Index_KMP(S, T);
	return 0;
}