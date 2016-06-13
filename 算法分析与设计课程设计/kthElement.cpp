#include <stdio.h>
#include<stdlib.h>
#include <tchar.h>
#include "time.h"

void sort(int n,int a[]) //进行选择排序
{
    int i,temp,j;   
    for(i=0;i<n;i++)
	{       
	 for(j=i+1;j<n;j++)
	 {      
		 if(a[i] > a[j])
		 {         
			 temp = a[i];           
			 a[i] = a[j];             
			 a[j] = temp;          
		 }      
	 }   
	}
}

long select(int k,int* S,int num)//用select算法实现第k小元数的查找
{   
	int p,num2,i,j,m,n1,n2,n3;  
	int temp[5],*M,*S1; 
	int *S3;
	if(num < 44)       //设定阈值为44
	{     
		sort(num,S);  //直接进行排序后输出结果    
		return S[k-1];    
	} 
	else{      
	  p = num / 5;     //进行分组,5个一组,有余的话不进行排序,丢弃这些元素
	  j = 0;              //初始化
	  num2 = 0; 

	  //申请内存空间
	  M= new int[p];
	  S1 = new int[num];
	//  S2 = new int[num];
	  S3 = new int[num];
	  
	  //分组，并找出每组的中位数
	  for(i=0;i<p*5;i++)   
	  {      
		  temp[j] = S[i];         
		  j++;          
		  if(j == 5)
		  {       
			  j = 0;          
			  sort(5,temp);    //每个组中的5个元素进行排序 
			  M[num2] = temp[2];  //得到中位数  
			  num2++;          
		  }      
	  } 

	  //递归调用求解中位数，并设置为划分标准元素
	  m = select((p + 1) / 2,M,p);  //从中位数集合中找到它的中位数 
	 
	  //把数组划分为3个子数组
	  n1 = n2 = n3 = 0;     
	  for(i=0;i<num;i++)
	  {         
		  if(S[i] < m)         //得到小于中位数M的元素集合S1[n1]
		  {              
			  S1[n1] = S[i];          
			  n1++;           
		  }       
		  else if(S[i] == m)      //得到等于中位数M的元素集合S2[n2]
		  {           
			 // S2[n2] = S[i];            
			  n2++;         
		  }        
		  else{          
			  S3[n3] = S[i];         //得到大于中位数M的元素集合S3[n3]  		               
     		  n3++;          
		  }     
	  }

	  //释放内存空间
	  delete []M;
      
	  if(n1 > k) 
	  {
		  //释放内存空间
		 // delete []S2;
		  delete []S3;
		  
		  //递归处理
		  return(select(k,S1,n1));        //在S1中寻找第K小元素
	  }
      else if(n1 + n2 >= k) 
	  {
		  //释放内存空间
		  delete []S1;
		//  delete []S2;
		  delete []S3;

		  //返回结果
		  return m;            //M就是要找的元素
	  }
	  else 
	  {
		  //释放内存空间
		  delete []S1;
		//  delete []S2;

		  //递归处理
		  return(select(k - n1 - n2,S3,n3));     //丢弃S1和S2,在S3中寻找第K小元素
	  }
  }
}

int main()
{
	printf("请输入元素个数N,系统将自动随机生成N个整数，N=");

	int n,k,i;
	int *A,*a;
	scanf("%d",&n);
	
	printf( "请输入需要找的第k（1到%d之间）小元素的k=",n);
	scanf("%d",&k);
	printf("需要在屏幕上显示生成的元素吗？输入y显示，n不显示（y/n）:");
	char flag;
	scanf("%s",&flag);
	if(flag == 'y')
	{
		printf("以下是系统随机生成的%d个元素：",n);
	}

	//文件操作
	FILE *fp;
	fp = fopen("kthElement.txt","w");
	if(!fp)
	{
		printf( "Error to open file to write");
		return 0;
	}
	fprintf(fp,"%d %d\n",n,k);

	A = new int[n]; //申请数组的内存空间
	a = new int[n];

	srand((int)time(0));//设置随机种子
	for(i=0;i<n;i++) //随机生成N个元素
	{
		A[i] = rand(); //随机产生0-10000之间的整数
		a[i] = A[i];
		if(flag == 'y')
		{
			printf("%d ",A[i]);
		}
		fprintf(fp,"%d ",A[i]);
	}

	//cout<< "数据文件生成成功"<<endl;
	int result;  
	clock_t start,finish;
	double duration;
	
	start = clock();	
	result = select(k,A,n); 
    finish = clock();
    duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC);
 
    printf("\n用中位选择法找到的第%d小元素是:%d \n运行时间：%lf 秒\n",k,result,duration); 
	fprintf(fp,"\n用中位选择法找到的第%d小元素是:%d ",k,result);
	fclose(fp);
    delete[]A;
	return 0;
}


