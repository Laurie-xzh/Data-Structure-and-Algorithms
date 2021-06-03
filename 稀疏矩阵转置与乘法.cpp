#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#define MAXSIZE 200
#define OK 1
#define FALSE 0
#define OVERFLOW -2
#define ERROR -1
typedef int Status;
typedef int ElemType;

using namespace std;

typedef struct
{
    int i, j;
    ElemType e;
}Triple;

typedef struct
{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
}TSMatrix;

void creatMatrix_1(TSMatrix* M)
{
    int i, j, n, k;       //行，列，非零元个数
    int a[50][50] = { 0 };   //存放矩阵，初始值为0 
    ElemType e;
    srand((unsigned)time(NULL) + (unsigned)rand());  //以time()为种子生成随机数
    (*M).mu = rand() % 20 + 10;   //随机行大小，取余是确定范围 
    (*M).nu = rand() % 20 + 10;   //随机列大小
    k = rand() % 10+1;   //随机非零元个数
    

    cout << "这是一个" << (*M).mu << "行"<<(*M).nu<<"列的矩阵 "<<endl;
    (*M).data[0].i = 0;
    for (n = 1; n <= k; n++)   //生成随机数矩阵
    {
        i = rand() % (*M).mu + 1;
        j = rand() % (*M).nu + 1;
        e = rand()%10;
        a[i][j] = e;
    }
    (*M).tu = 1;
    for (i = 1; i <= (*M).mu; i++)  //以行为主序存入三元组
    {
        for (j = 1; j <= (*M).nu; j++)
        {
            if (a[i][j] != 0)
            {
                (*M).data[M->tu].i = i;	//行下标
                (*M).data[M->tu].j = j;	//列下标
                (*M).data[M->tu].e = a[i][j];	//该下标所对应的值
              //  cout << (*M).data[M->tu].i << "    " << (*M).data[M->tu].j << "    " << (*M).data[M->tu].e << endl;
                M->tu++;
            }
        }
    }
    M->tu--;
    cout << M->tu << endl;
    cout << "成功创建了一个稀疏度为1%左右的稀疏矩阵" << endl;

}

void creatMatrix_2(TSMatrix* M)
{
    int i, j, n, k;       //行，列，非零元个数
    int a[50][50] = { 0 };   //存放矩阵，初始值为0 
    ElemType e;
    srand((unsigned)time(NULL) + (unsigned)rand());  //以time()为种子生成随机数
   // (*M).mu = rand() % 20 + 10;   //随机行大小，取余是确定范围 
    (*M).mu =20;
    (*M).nu = 20;   
    k = rand() % 10 + 10;   //随机非零元个数


    cout << "这是一个" << (*M).mu << "行" << (*M).nu << "列的矩阵 " << endl;
    (*M).data[0].i = 0;
    for (n = 1; n <= k; n++)   //生成随机数矩阵
    {
        i = rand() % (*M).mu + 1;
        j = rand() % (*M).nu + 1;
        e = rand() % 10;
        a[i][j] = e;
    }
    (*M).tu = 1;
    for (i = 1; i <= (*M).mu; i++)  //以行为主序存入三元组
    {
        for (j = 1; j <= (*M).nu; j++)
        {
            if (a[i][j] != 0)
            {
                (*M).data[M->tu].i = i;	//行下标
                (*M).data[M->tu].j = j;	//列下标
                (*M).data[M->tu].e = a[i][j];	//该下标所对应的值
              //  cout << (*M).data[M->tu].i << "    " << (*M).data[M->tu].j << "    " << (*M).data[M->tu].e << endl;
                M->tu++;
            }
        }
    }
    M->tu--;
    cout << M->tu << endl;
    cout << "成功创建了一个稀疏度为10%左右的稀疏矩阵" << endl;

}

void printMatrix(TSMatrix*M)
{
    cout << "行" << "    " << "列" << "    " << "数值" << endl;
    int m= 1;
    for (m; m <= M->tu; m = m + 1)
    {
        cout << (*M).data[m].i << "    " << (*M).data[ m].j << "    " << (*M).data[m].e << endl;
    }
    
}


Status TransposeSMatrix(TSMatrix A, TSMatrix& B)
{
    int  p, q, col;
    B.mu = A.nu;
    B.nu = A.mu;
    B.tu = A.tu;

    if (A.tu)
    {
        q = 1;
        for (col = 1; col <= A.nu; ++col)
        {
            for (p = 1; p <= A.tu; ++p)
            {
                if (A.data[p].j == col)
                {
                    B.data[q].i = A.data[p].j;
                    B.data[q].j = A.data[p].i;
                    B.data[q].e = A.data[p].e;
                    ++q;
                }
            }
        }
    }
    return OK;
} // TransposeSMatrix

Status  FastTransposeSMatrix(TSMatrix  A, TSMatrix& B)
{
    int col, t, p, q;
    int num[100], cpot[100];
    B.mu = A.nu;
    B.nu = A.mu;
    B.tu = A.tu;

    if (B.tu)
    {
        for (col = 1; col <= A.nu; ++col)
        {
            num[col] = 0;
        }
        for (t = 1; t <= A.tu; ++t) // 求M 中每一列所含非零元的个数
        {
            ++num[A.data[t].j];
        }
        cpot[1] = 1;

        // 求M 中每一列的第一个非零元在b.data 中的序号
        for (col = 2; col <= A.nu; ++col)
        {
            cpot[col] = cpot[col - 1] + num[col - 1];
        }
        for (p = 1; p <= A.tu; ++p)
        {
            col = A.data[p].j;
            q = cpot[col];
            B.data[q].i = A.data[p].j;
            B.data[q].j = A.data[p].i;
            B.data[q].e = A.data[p].e;  ++cpot[col];
        }
    }

    return OK;
} // FastTransposeSMatrix


void multiply(TSMatrix& A, TSMatrix& B,TSMatrix &C)
{
   
    if (A.nu != B.mu)
    {
        cout << "不能相乘" << endl;
    }
    else
    {
        C.mu = A.mu;
        C.nu = B.nu;
        C.tu = 1;
       // int  m,n = 1;
        int m = 1;
        int n = 1;
        for ( m ; m <= A.tu; m++)
        {
            for ( n ; n <= B.tu; n++)
            {
                if (A.data[m].j == B.data[n].i)
                {
                    C.data[C.tu].e += A.data[m].e * B.data[n].e;
                    C.data[C.tu].i = A.data[m].i;
                    C.data[C.tu].j = B.data[n].j;
                }
               
            }
            if (C.data[C.tu].e != 0)
            {
                cout << (C).data[C.tu-1].i << "    " << (C).data[C.tu-1].j << "    " << (C).data[C.tu - 1].e << endl;
                C.tu += 1;
            }
        }

        C.tu--;
    }
}
Status multiMatrix_1(TSMatrix& T,TSMatrix&S) {
    TSMatrix T1;
   creatMatrix_2(&T1);
    cout << "自动生成的另一个稀疏矩阵" << endl;
    printMatrix(&T1);
    int arry[21][21] = { 0 };
    int arry1[21][21] = { 0 };
    int arry2[21][21] = { 0 };
    for (int i = 1; i <= T.tu; i++) arry1[T.data[i].i][T.data[i].j] = T.data[i].e;
    
    for (int i = 1; i <= T1.tu; i++) arry2[T1.data[i].i][T1.data[i].j] = T1.data[i].e;
    for (int i = 1; i <= 20; i++)
    {  //行  
        for (int j = 1; j <= 20; j++)
        {  //列  
            int sum = 0;
            for (int k = 1; k <= 20; k++)
            {
                sum += arry1[i][k] * arry2[k][j];
                arry[i][j] = sum;
                

            }
        }
    }
    
    S.tu = 0;
    for (int i = 1; i <20; i++)
    {
        for (int j = 1; j < 20; j++)
        {
            if (arry[i][j] != 0)
            {
                S.tu += 1;
                S.mu = T.mu;
                S.nu = T1.nu;
                S.data[S.tu].i = i;
                S.data[S.tu].j = j;
                S.data[S.tu].e = arry[i][j];
            }
        }
    }
    system("pause");
    return OK;
}
 
int main()
{
    TSMatrix M,B,N1,N2,N3;
    creatMatrix_1(&M);
 //   printMatrix(&M);
   // TransposeSMatrix(M, B);
    
    FastTransposeSMatrix(M, B);
  //  printMatrix(&B);

    creatMatrix_2(&N1);
    printMatrix(&N1);
    creatMatrix_2(&N2);
    printMatrix(&N2);

    cout << "-----------------------------------------------------------" << endl;
   //multiply(N1, N2, N3);
   //printMatrix(&N3);
    multiMatrix_1(N1,N3);
    cout << "相乘后的矩阵为" << endl;
    cout << "**************************************" << endl;
    cout << "   ";
    printMatrix(&N3);
    cout << "**************************************" << endl;
    return 0;
}