#include<stdio.h>
#include<stdlib.h>
#include"time.h"
void merge(int a[], int p, int q, int r)
{
     int i,k;
     int begin1,end1,begin2,end2;
     int* b=(int *)malloc((r-p+1)*sizeof(int));
     begin1= p;
     end1 = q;
     begin2 = q+1;
     end2 = r;
     k = 0;
     while((begin1 <= end1)&&( begin2 <= end2))
     {
          if(a[begin1] < a[begin2])
          {
               b[k] = a[begin1];
			   if(a[begin1]<0){
				  b[k++] = a[begin2++];
			   }
               begin1++;
          }
          else
          {
               b[k] = a[begin2];
			   if(a[begin2]<0){
					b[k++] = a[begin1++];
			   }
               begin2++;
          }
          k++;

     }
	 
     while(begin1<=end1)
     {
        b[k++] = a[begin1++];
     }
     while(begin2<=end2)
     {
         b[k++] = a[begin2++];
     }
	 
     for (i = 0; i < (r-p+1); i++)
          a[p+i] = b[i];
	 delete[]b;
}

void BottomUpSort(int a[],int n)
{
     int t=1,s,i;
     while(t<n)
     {
           s=t;
           t=2*s;
           int i=0;
           while(i+t<=n)
           {
                 merge(a,i+1,i+s,i+t);
                 i=i+t;
           }
           if(i+s<n) merge(a,i+1,i+s,n);
     }
}

int main()
{
	int i,n;
	printf("输入随机数个数n:");
	scanf("%d",&n);

	printf("需要在屏幕上显示生成的元素吗？输入y显示，n不显示（y/n）:");
	char flag;
	scanf("%s",&flag);
	if(flag == 'y')
	{
		printf("以下是系统随机生成的%d个元素：",n);
	}
	//文件操作
	FILE *fp;
	fp = fopen("BottomUpSort.txt","w");
	if(!fp)
	{
		printf("Error to open file to write");
		return 0;
	}
	fprintf(fp,"产生随机数个数%d\n",n);
	//产生随机数
	int* a=(int*)malloc((n)*sizeof(int));
	srand((int)time(0));
	 fprintf(fp,"产生随机数列：");
	for(i=1;i<=n;i++){
		a[i]=rand();
		if(flag == 'y')
		{
			printf("%d ",a[i]);
		}
		fprintf(fp,"%d ",a[i]);
	}
	printf("\n");

	clock_t start,finish;
	double duration;
	
	start = clock();
	BottomUpSort(a,n);
	finish = clock();
	duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC);

	printf("自底向上排序为：\n");
	fprintf(fp,"\n\n自底向上排序结果：");
	for(i=1;i<=n;i++){
		printf("%d ",a[i]);
		fprintf(fp,"%d ",a[i]);
	}
	fclose(fp);	
	printf("\n运行时间为：%lf秒\n",duration);
	delete[]a;
	return 0;
}