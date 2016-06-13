#include <stdio.h>
#include <math.h>
#include"time.h"
#define M 100
#define N 100

int v[M],w[M],x[M],c,n; //背包容量c，物品个数n，物品重量w和价值v
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
			if(j>=w[i])     //如果此物品的价值加上背包剩下的空间能放的物品的价值
				              //大于上一次选择的最佳方案,更新m[i][j]
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
			printf("选取物品%d:其物品重量为 %d ，价值为 %d\n",n,w[n],v[n]); 	
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
	printf("请输入背包容量c和物品数量n：");
	scanf("%d %d",&c,&n);
	printf("\n");
	
	printf("请输入物品重量w和价值v:");
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
	printf("背包总价值:%d\n",count);
	printf("运行时间为：%lf秒\n\n",duration1);

	start2 = clock();
	Traceback(n,c,w,v);
	finish2 = clock();
	duration2 = (double)((finish2 - start2)*1.0/CLOCKS_PER_SEC);
	printf("运行时间为：%lf秒\n",duration2);
}
