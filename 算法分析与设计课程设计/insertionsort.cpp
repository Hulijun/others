#include"stdio.h"
#include"stdlib.h"
//#include <tchar.h>
#include"time.h"

long insertionsort(int a[],int n)
{
	int i,j,x;
	for(i=1;i<n;i++){
		x=a[i];
		j=i-1;
		while(j>=0 && a[j]>x){
			a[j+1]=a[j];
			j=j-1;
		}
		a[j+1]=x;
	}
	return a[i];
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
	fp = fopen("insertionsort.txt","w");
	if(!fp)
	{
		printf("Error to open file to write");
		return 0;
	}
	fprintf(fp,"产生随机数个数%d\n",n);

	//产生随机数
	int* a= (int*)malloc((n)*sizeof(int));
	srand((int)time(0));
    fprintf(fp,"产生随机数列：");
	for(i=0;i<n;i++){
		a[i]=rand();
		if(flag == 'y')
		{
			printf("%d ",a[i]);
		}
		fprintf(fp,"%d ",a[i]);
	}
	
	printf("\n");
	int result;
	clock_t start,finish;
	double duration;
	
	start = clock();
	result = insertionsort(a,n);
	finish = clock();
	duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC) ;
	printf("插入排序为：\n");
	fprintf(fp,"\n\n插入排序结果：");
	for(i=0;i<n;i++){
		
			printf("%d ",a[i]);
			fprintf(fp,"%d ",a[i]);
	}
	fclose(fp);
	printf("\n运行时间为：%lf秒\n",duration);
	delete[]a;
	return 0;
}
