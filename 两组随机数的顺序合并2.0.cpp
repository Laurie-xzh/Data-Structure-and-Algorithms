/*
Ŀ��:   ������������ϲ���һ��˳����,�������鳤��ʱ���Է�ֹ������С���Լ������ַ�
���ߣ�61520711���Ӻ�
���ڣ�2021.3.9
�汾��2.0
*/


#include<iostream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<ctype.h>
#include <stdlib.h>

#include <sstream>
using namespace std;


//��������ȫ�ֱ�������Ϊ��ͬ�ĺ�����Ҫ����
double* nums1;
double* nums2;
double* num;
/**
*@brief      ������������ĳ���
*
* @param N1   ��һ�����룬Ҫ������Ч���ж�
* @param N2   �ڶ������룬Ҫ������Ч���ж�
*@param   n1  ��һ������ĳ���        ����ʹ�����ã��Ӷ����Զ��⴫��
* @param  n2  �ڶ�������ĳ���        ����ʹ�����ã��Ӷ����Զ��⴫��
* @return  void
*/
//���Ӷ�ΪO(n)
void init_length(string & N1, string & N2,double&n1,double &n2)
{
	/*do
	{
		cout << "���õ�һ�����ĳ���" << endl;
		cin >> n1;
		cout << "���õڶ������ĳ���" << endl;
		cin >> n2;
		cout << "����Ϊ�Ǹ�������" << endl;
	} while (n1 < 0 || n2 < 0 || (int)n1 != n1 || (int)n2 != n2);*/
	int judge_N1 = -1;
	int judge_N2 = -1;
	while (judge_N1 != 0 || judge_N2 != 0)
	{
		cout << "���õ�һ�����ĳ���" << endl;
		cin >> N1;
		cout << "���õڶ������ĳ���" << endl;
		cin >> N2;
		cout << "����Ϊ�Ǹ�������" << endl;

		for (int i = 0; i <= N1.length() - 1; i = i + 1)
		{
			if (isdigit(N1[i]) == 0)
			{
				judge_N1 = -1;
				break;
			}
			else
			{
				judge_N1 = 0;
			}
		}
		for (int i = 0; i <= N2.length() - 1; i = i + 1)
		{
			if (isdigit(N2[i]) == 0)
			{
				judge_N2 = -1;
				break;
			}
			else
			{
				judge_N2 = 0;
			}
		}
		if (judge_N1 == -1)
		{
			cout << "��һ�����������⣬�Ǹ��Ǹ�����������"<<endl;
			cout << "-_-" << endl;
			cout << endl;
		}
		if (judge_N2 == -1)
		{
			cout << "�ڶ������������⣬�Ǹ��Ǹ����������� " << endl;
			cout << "-_-" << endl;
			cout << endl;
		}
		if (judge_N1 == 0 && judge_N2 == 0)
		{
			stringstream ss;
			ss << N1;
			ss >> n1;
			stringstream sss;
			sss << N2;
			sss >> n2;

			break;

			/*
			������һ����Ϊ���ж������Ƿ�Ϊ�Ǹ���������������ǰ����С���븺������Ϊ��.���롰-���������ֶ�������������ж��
			����Ĳ���ûɶ�ã���ע�͵��ˡ�
			��ô�������ˣ�����Ժ��г���Ҫ������С���븺�����������ã��жϵ�һ��Ϊ��-���ͺã���С�����д������������ô����
			�д���һ���Ż�
			�Լ����������������������û���
			*/

			/*if (n1 >= 0  &&  n2 >= 0 && (int)n1 == n1 && (int)n2 == n2)
			{
				break;
			}
			else
			{
				cout << "���ȵ���һ���Ǹ�����������"   <<endl;
				cout << "-_-" << endl;
			}*/

		}
	}

}


/**
*@brief      ����������
*
*@param   double* arr  ��Ҫ��ӡ������
* @param  n ����ĳ��ȣ�������������б���
* @return  void
*/
void print(double* arr, double n)
{
	for (int i = 0; i <= n - 1; i = i + 1)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

/**
*@brief      ���������ʼ��nums1��nums2,���Ҵ�ӡ
*
*@param    n1  nums1�ĳ���
* @param   n2  nums2�ĳ���
* @return   void
*/

//���Ӷ�ΪO(n)
void init_nums(double n1, double n2)
{
	
	nums1 = new double[n1];
	nums2 = new double[n2];
	//��һ������ʼ��ʼ��
	for (int i = 0; i <= n1 - 1; i = i + 1)
	{
		//nums1[i] = rand() % 100;
		// (unsigned int)((rand() << 16) + rand()) % (size * 10)
		nums1[i] = (unsigned int)((rand() << 16) + rand()) % (100 * 10);     //���������
	}
	//�ڶ�������ʼ��ʼ��
	for (int j = 0; j <= n2 - 1; j = j + 1)
	{
		//nums2[j] = rand() % 100;
		nums2[j] = (unsigned int)((rand() << 16) + rand()) % (100 * 10);
	}


	cout << "��һ���������ֵ" << endl;
	print(nums1, n1);
	cout << endl;

	cout << "�ڶ����������ֵ" << endl;
	print(nums2, n2);
	cout << endl;
}


/**
*@brief         �������������
*
*@param      double* arr  Ҫ���������
* @param     left  ���/�����ڱ�����������
* @param     right  �ҽ�/(���ڱ�����������)
* @return     void
*/
//���Ӷ�Ϊnlgn
void quicksort(double* arr, int left, int right)
{

	int i, j, t;
	double temp;
	if (left > right)
	{
		return;
	}
	temp = arr[left];
	i = left;
	j = right;
	while (i != j)
	{
		while (arr[j] >= temp && i < j)
		{
			j--;
		}
		while (arr[i] <= temp && i < j)
		{
			i++;
		}
		if (i < j)
		{
			t = arr[i];
			arr[i] = arr[j];
			arr[j] = t;
		}
	}
	arr[left] = arr[i];
	arr[i] = temp;

	quicksort(arr, left, i - 1);
	quicksort(arr, i + 1, right);
}

/**
*@brief         ��nums1��nums2����������кϲ�
*
*@param      double* nums1  Ҫ����ĵ�һ����
* @param     double* nums2  Ҫ����ĵڶ�����
* @param     n1  ��һ�����ĳ���
* @param     n2  �ڶ������ĳ���
* @return     void
*/
//���Ӷ�ΪO(n1+n2)=O(n)
void merge(double* nums1, double* nums2, double n1, double n2)
{
	num = new double[n1 + n2];
	int x = 0;
	int y = 0;
	int n = 0;
	while (x < n1 && y < n2)
	{
		if (nums1[x] <= nums2[y])
		{
			num[n] = nums1[x];
			x++;
			n++;
		}
		else
		{
			num[n] = nums2[y];
			y++;
			n++;
		}
	}
	while (x < n1)
	{
		num[n] = nums1[x];
		x++;
		n++;
	}
	while (y < n2)
	{
		num[n] = nums2[y];
		y++;
		n++;
	}
	/*for (int i = 0; i <= n1+n2 - 1; i = i + 1)
	{
		cout << num[i] << " ";
	}*/
	cout << "�ϲ����Ч��" << endl;
	print(num, n1 + n2);
	cout << endl;
}

/**
*@brief     �ͷ��ڴ�
*
* @return  void
*/
void release()
{
	if (nums1)
	{
		delete[]nums1;
	}
	if (nums2)
	{
		delete[]nums2;
	}
	if (num)
	{
		delete[]num;
	}
}

int main()
{
	string N1 = " ";
	string N2 = " ";


	double n1 = 0;
	double n2 = 0;
	init_length(N1, N2,n1,n2);
	init_nums(n1, n2);
	quicksort(nums1, 0, n1 - 1);
	quicksort(nums2, 0, n2 - 1);

	cout << "��һ��������������" << endl;
	print(nums1, n1);
	cout << endl;

	cout << "�ڶ���������������" << endl;
	print(nums2, n2);
	cout << endl;

	merge(nums1, nums2, n1, n2);
	release();
	return 0;
	//ȡ���и��Ӷȵ����ֵ��ӦΪnlgn
}
