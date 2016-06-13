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
	printf("�������������n:");
	scanf("%d",&n);

	printf("��Ҫ����Ļ����ʾ���ɵ�Ԫ��������y��ʾ��n����ʾ��y/n��:");
	char flag;
	scanf("%s",&flag);
	if(flag == 'y')
	{
		printf("������ϵͳ������ɵ�%d��Ԫ�أ�",n);
	}
	//�ļ�����
	FILE *fp;
	fp = fopen("insertionsort.txt","w");
	if(!fp)
	{
		printf("Error to open file to write");
		return 0;
	}
	fprintf(fp,"�������������%d\n",n);

	//���������
	int* a= (int*)malloc((n)*sizeof(int));
	srand((int)time(0));
    fprintf(fp,"����������У�");
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
	printf("��������Ϊ��\n");
	fprintf(fp,"\n\n������������");
	for(i=0;i<n;i++){
		
			printf("%d ",a[i]);
			fprintf(fp,"%d ",a[i]);
	}
	fclose(fp);
	printf("\n����ʱ��Ϊ��%lf��\n",duration);
	delete[]a;
	return 0;
}
