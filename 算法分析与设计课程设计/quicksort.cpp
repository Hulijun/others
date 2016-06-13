#include"stdio.h"
#include"stdlib.h"
#include"time.h"

//�����㷨split subrout

int spilt(int A[],int low,int high) //�������ΪA[low..q-1] ��A[q+1..high]  
{                                 
    int x,i,j,temp;  
  
    x = A[low];  //����һ��ֵ������x��  
    i = low;   
    for( j=low+1; j<=high; j++)  
    {  
        if(A[j]<=x)  
        {  
            i++;
            if(i!=j){//exchange
                temp = A[i]; 
                A[i] = A[j];  
                A[j] = temp; 
            }
        }  
    }  
  
    temp = A[i];  //exchange A[low]and A[i] 
    A[i] = A[low];  
    A[low] = temp;  
  
    return i;   
}  


//�������� 
void quickSort(int A[],int low,int high)  
{  
    int q;  
    if(low<high)               //���low>=high,����ִ��  
    {  
        q = spilt(A,low,high);  //���÷��η� �ҵ�q��ֵ  
        quickSort(A,low,q-1);  
        quickSort(A,q+1,high);  
    }  
}  

int main()
{
    int i,n;
    //int n=0;
	printf("������������ĸ���n:");
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
	fp = fopen("quicksort.txt","w");
	if(!fp)
	{
		printf("Error to open file to write");
		return 0;
	}
	fprintf(fp,"������ĸ���%d\n",n);

    //���������
    int* A= (int*)malloc((n)*sizeof(int));
	srand((int)time(0));
	fprintf(fp,"����������У�");
    for(i=0;i<n;i++){
        A[i]=rand();
        if(flag == 'y')
		{
			printf("%d ",A[i]);
		}
		fprintf(fp,"%d ",A[i]);
    }
	
    printf("\n");

	//����һ���¼��ĳ���ʱ�� 
	clock_t start,finish;
	double duration;
    start=clock();
    quickSort(A,0,n-1);
	finish=clock();

    printf("������������\n");
	fprintf(fp,"\n\n������������");
    for(i=0;i<n;i++){
        printf("%d ",A[i]);
		fprintf(fp,"%d ",A[i]);
    }
	fclose(fp);
	duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC) ;
    printf("\n����ʱ�䣺%lf s\n",duration);
	//system("PAUSE");
    printf("\n");
	delete[]A;
    return 0;

}