#include <stdio.h>
#include <math.h>
#include"time.h"
#define M 100
#define N 100

int v[M],w[M],x[M],c,n; //��������c����Ʒ����n����Ʒ����w�ͼ�ֵv
int m[M][N]; 

int MAX (int a,int b)
{
	if(a>b) return a;
	else return b;
}


int Knapsack(int n,int c,int *w,int *v)
{
	int i,j,jMax=c;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=jMax;j++)
			m[i][j]=0;
	} 

	for(i=1;i<=n;i++)
		for(j=1;j<=jMax;j++)
		{
			if(j>=w[i])     //�������Ʒ�ļ�ֵ���ϱ���ʣ�µĿռ��ܷŵ���Ʒ�ļ�ֵ
				              //������һ��ѡ�����ѷ���,����m[i][j]
			m[i][j]=MAX(m[i-1][j],m[i-1][j-w[i]]+v[i]);
			else m[i][j]=m[i-1][j];
		}
	return m[n][c];
}


void Traceback(int n,int c,int *w,int *v)
{
	while(m[n][c]!=0)
	{
		if (m[n][c]>m[n-1][c])	
		{	
			printf("ѡȡ��Ʒ%d:����Ʒ����Ϊ %d ����ֵΪ %d\n",n,w[n],v[n]); 	
			c-=w[n];	
			n--;	
		}	
		else	
			n--;	
	}
}


void main()
{
	int i,count;
	printf("�����뱳������c����Ʒ����n��");
	scanf("%d %d",&c,&n);
	printf("\n");
	
	printf("��������Ʒ����w�ͼ�ֵv:");
	for(i=1;i<=n;i++){
		scanf("%d %d",&w[i],&v[i]);
	}
	printf("\n");
	
	clock_t start1,finish1,start2,finish2;
	double duration1,duration2;
	
	start1 = clock();
	count=Knapsack(n,c,w,v);
	finish1 = clock();
	duration1 = (double)((finish1 - start1)*1.0/CLOCKS_PER_SEC);
	printf("�����ܼ�ֵ:%d\n",count);
	printf("����ʱ��Ϊ��%lf��\n\n",duration1);

	start2 = clock();
	Traceback(n,c,w,v);
	finish2 = clock();
	duration2 = (double)((finish2 - start2)*1.0/CLOCKS_PER_SEC);
	printf("����ʱ��Ϊ��%lf��\n",duration2);
}
