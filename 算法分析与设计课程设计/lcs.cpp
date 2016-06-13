/*------------------------------------------------
    最长公共子序列LCS算法
	Algorithm LCSLength(x,y,b);
	Algorithm LCS(int i,int j,char[]x,int[]b);
--------------------------------------------------*/

#include<string.h>
#include<stdio.h>
#include"time.h"
#define N 50

void  LCSLength(int m,int n,char x[],char y[],int b[N+1][N+1])
{
       int i,j,s,t;
       int c[N+1][N+1];
       for (i=0;i<=m;i++)
              c[i][0]=0;
       for (i=0;i<=n;i++)
              c[0][i]=0;
       for (i=1;i<=m;i++)
              for (j=1;j<=n;j++)
              {
                     if (x[i]==y[j])
                     {
                            c[i][j]=c[i-1][j-1]+1;
                            b[i][j]=1;
                     }
                     else if (c[i-1][j]>=c[i][j-1])
                     {
                            c[i][j]=c[i-1][j];
                            b[i][j]=2;
                     }
                     else
                     {
                            c[i][j]=c[i][j-1];
                            b[i][j]=3;
                     }
              }
              for (s=0;s<=m;s++)
              {
                 for (t=0;t<=n;t++)
                        printf("%d",c[s][t]);
                        printf("\n");
              }
              printf("最长公共子序列长度为：%d\n",c[m][n]);
}
void LCS(int i,int j,char x[],int b[N+1][N+1])
{
       if (i==0 || j==0)
              return;
       if (b[i][j]==1)
       {
              LCS(i-1,j-1,x,b);
              printf("%c",x[i]);
       }
       else if (b[i][j]==2)
              LCS(i-1,j,x,b);
       else
              LCS(i,j-1,x,b);
}

void main()
{
    int  lx,ly;
    char X[N+1],Y[N+1];
    int b[N+1][N+1];
    printf("请输入X序列：");
    scanf("%s",X+1);
    printf("请输入Y序列：");
    scanf("%s",Y+1);

	lx=strlen(X+1);
	printf("X序列的长度为：%d\n",lx);
	ly=strlen(Y+1);
	printf("Y序列的长度为：%d\n",ly);
	
	clock_t start1,finish1,start2,finish2;
	double duration1,duration2;
	
	start1 = clock();
    LCSLength(lx,ly,X,Y,b);
	finish1 = clock();
	duration1 = (double)((finish1 - start1)*1.0/CLOCKS_PER_SEC) ;
	printf("duration1运行时间为：%lf秒\n",duration1);

	printf("最长公共子序列为：");
	start2 = clock();
    LCS(lx,ly,X,b);
	finish2 = clock();
	duration2 = (double)((finish2 - start2)*1.0/CLOCKS_PER_SEC) ;
	printf("\n");
	printf("duration2运行时间为：%lf秒\n",duration2);
  
    
}