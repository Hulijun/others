#include"stdio.h"
#include"stdlib.h"
#include"time.h"

//划分算法split subrout

int spilt(int A[],int low,int high) //将数组分为A[low..q-1] 和A[q+1..high]  
{                                 
    int x,i,j,temp;  
  
    x = A[low];  //将第一个值保存在x中  
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


//快速排序 
void quickSort(int A[],int low,int high)  
{  
    int q;  
    if(low<high)               //如果low>=high,程序不执行  
    {  
        q = spilt(A,low,high);  //调用分治法 找到q的值  
        quickSort(A,low,q-1);  
        quickSort(A,q+1,high);  
    }  
}  

int main()
{
    int i,n;
    //int n=0;
	printf("请输入随机数的个数n:");
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
	fp = fopen("quicksort.txt","w");
	if(!fp)
	{
		printf("Error to open file to write");
		return 0;
	}
	fprintf(fp,"随机数的个数%d\n",n);

    //产生随机数
    int* A= (int*)malloc((n)*sizeof(int));
	srand((int)time(0));
	fprintf(fp,"产生随机数列：");
    for(i=0;i<n;i++){
        A[i]=rand();
        if(flag == 'y')
		{
			printf("%d ",A[i]);
		}
		fprintf(fp,"%d ",A[i]);
    }
	
    printf("\n");

	//测量一个事件的持续时间 
	clock_t start,finish;
	double duration;
    start=clock();
    quickSort(A,0,n-1);
	finish=clock();

    printf("快速排序结果：\n");
	fprintf(fp,"\n\n快速排序结果：");
    for(i=0;i<n;i++){
        printf("%d ",A[i]);
		fprintf(fp,"%d ",A[i]);
    }
	fclose(fp);
	duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC) ;
    printf("\n运行时间：%lf s\n",duration);
	//system("PAUSE");
    printf("\n");
	delete[]A;
    return 0;

}