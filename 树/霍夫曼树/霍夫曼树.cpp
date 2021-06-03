/*���������һ������Ϊ100���ַ����������ҽ�����a\b\c\d\e����ַ���
���ݸ��ַ������ɻ��������룬���ҽ�ԭ��ѹ���������*/
//�����ԭ��ѹ���������.txt�ļ��У�����������������������������������������

#include<iostream>
#include<string>
#include<fstream> 
#include<cstdlib>
using namespace std;
struct Htnode
{
	int weight, parent, lchild, rchild;
	char c;
};
struct Htcode//����������
{
	int bit[25], start;
};
int type(int a[]) 
{
	string s;
	string temp;
	int sum = 0;
	cout << "��Ҫ������ַ������г�ʼ��" << endl;
	srand(time(0));
	for (int i = 0; i <= 99; i++)
	{
		temp = 'a' + rand() % 5;
		s = s + temp;
	}
	//cin >> s;
	cout << "---------------------------------------------------------" << endl;
	cout << s << endl;
	cout << "---------------------------------------------------------" << endl;
	for (int i = 0; i < s.size(); i++)
	{
		a[s[i] - 'a']++;
	}
	//cout << "���ֵ���ĸ�����Լ�Ƶ��:" << endl;
	for (int i = 0; i < 26; i++)
	{
		if (a[i] != 0)
		{
			char c = char(i + 'a');
		//	cout << "i:" << i << " c:" << c << ":" << a[i] / (s.size() * 1.0) << endl;
			sum++;
		}
	}
	return sum;
}
//ͨ������ķ�ʽ������������ 
void HufmanTree(Htnode h[], int n, int a[]) 
{
	int i, j, max1, max2, x1, x2;
	for (i = 0; i < 2 * n; i++)
	{
		h[i].weight = 0;
		h[i].parent = -1;
		h[i].lchild = -1;
		h[i].rchild = -1;
		h[i].c = '\0';
	}
	for (i = 0; i < 26; i++)
	{
		if (a[i] != 0) {
			h[i].c = i + 'a';
			h[i].weight = a[i];
		}
	}
	for (i = 0; i < n - 1; i++)
	{
		max1 = 1000, max2 = 1000;
		x1 = -1, x2 = -1;
		for (j = 0; j < n + i; j++) {
			if (h[j].weight < max1 && h[j].parent == -1)
			{
				max2 = max1;
				x2 = x1;
				max1 = h[j].weight;
				x1 = j;
			}
			else if (h[j].weight < max2 && h[j].parent == -1) 
			{
				max2 = h[j].weight;
				x2 = j;
			}
		}
		//����ÿ���ڵ���Ϣ, ������Ϣ�洢���ڵ�������
		h[x1].parent = n + i; h[x2].parent = n + i;
		h[n + i].weight = h[x1].weight + h[x2].weight;
		h[n + i].lchild = x1; h[n + i].rchild = x2;
	}
	for (i = 0; i < 2 * n - 1; i++)
	{
		cout << h[i].weight << " " << h[i].parent << " " << h[i].lchild << " " << h[i].rchild << " " << h[i].c << endl;
	}
}
//����������
//����Ҷ�ӽڵ��λ��, ����path·��01������䵽����������
void  HuffmandeCode(Htnode h[], int n, int a[], Htcode hcode[])
{
	HufmanTree(h, n, a);
	ofstream out;
	out.open("HuffmandeCode.txt", ios::out);
	int i, j;
	for (i = 0; i < n; i++) 
	{
		j = 0;
		int parent = h[i].parent;//��¼��ǰ�ڵ�ĸ��� 
		int c = i;
		while (c != -1)
		{//parent��ɸ��ڵ㲻�ᱻ���� 
			hcode[i].bit[j++] = h[parent].lchild == c ? 0 : 1;//��Ҷ�ӽڵ㵽���ڵ�, Ӧ��ʹ��ջ�ṹ 
			c = parent;
			parent = h[parent].parent;
		}
		hcode[i].start = j - 1;
	}
	for (i = 0; i < n; i++) 
	{
		cout << h[i].c << ":";
		for (j = hcode[i].start - 1; j >= 0; j--) 
		{
			cout << hcode[i].bit[j];
			out << hcode[i].bit[j];
		}
		cout << endl;
	}
	out.close();
}
string load() {
	ifstream in("HuffmandeCode.txt");
	string str;
	char buffer[256];
	if (!in.is_open()) 
	{
		cout << "�����ļ�����" << endl;
		return NULL;
	}
	cout << "��������ļ�" << endl;
	in.getline(buffer, 100, ' ');
	return string(buffer);
}

//����������
// void  HuffmanenCode(string s, int n, Htnode h[]) 
//{
//	int i = 0, j = 0, lchild = 2 * n - 2, rchild = 2 * n - 2;
//	while (s[i] != '\0')
//	{
//		if (s[i] == '0') 
//		{
//			 
//			lchild = h[lchild].lchild;
//			rchild = j = lchild;
//		}
//		if (s[i] == '1') 
//		{
//			rchild = h[rchild].rchild;
//			lchild = j = rchild;
//		}
//		if (h[lchild].lchild == -1 && h[rchild].rchild == -1) 
//		{
//			cout << h[j].c;
//			lchild = rchild = 2 * n - 2;
//			j = 0;
//		}
//		i++;
//	}
//}
int main()
{
	Htnode h[30];
	Htcode hcode[10];
	int a[26] = { 0 };
	string s;
	int n = type(a);
	cout << "n:" << n << endl;
	HuffmandeCode(h, n, a, hcode);
	//HuffmanenCode(load(), n, h);
	return 0;
}
