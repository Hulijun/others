#include <stdio.h>
#include<stdlib.h>
#include <tchar.h>
#include "time.h"

void sort(int n,int a[]) //����ѡ������
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

long select(int k,int* S,int num)//��select�㷨ʵ�ֵ�kСԪ���Ĳ���
{   
	int p,num2,i,j,m,n1,n2,n3;  
	int temp[5],*M,*S1; 
	int *S3;
	if(num < 44)       //�趨��ֵΪ44
	{     
		sort(num,S);  //ֱ�ӽ��������������    
		return S[k-1];    
	} 
	else{      
	  p = num / 5;     //���з���,5��һ��,����Ļ�����������,������ЩԪ��
	  j = 0;              //��ʼ��
	  num2 = 0; 

	  //�����ڴ�ռ�
	  M= new int[p];
	  S1 = new int[num];
	//  S2 = new int[num];
	  S3 = new int[num];
	  
	  //���飬���ҳ�ÿ�����λ��
	  for(i=0;i<p*5;i++)   
	  {      
		  temp[j] = S[i];         
		  j++;          
		  if(j == 5)
		  {       
			  j = 0;          
			  sort(5,temp);    //ÿ�����е�5��Ԫ�ؽ������� 
			  M[num2] = temp[2];  //�õ���λ��  
			  num2++;          
		  }      
	  } 

	  //�ݹ���������λ����������Ϊ���ֱ�׼Ԫ��
	  m = select((p + 1) / 2,M,p);  //����λ���������ҵ�������λ�� 
	 
	  //�����黮��Ϊ3��������
	  n1 = n2 = n3 = 0;     
	  for(i=0;i<num;i++)
	  {         
		  if(S[i] < m)         //�õ�С����λ��M��Ԫ�ؼ���S1[n1]
		  {              
			  S1[n1] = S[i];          
			  n1++;           
		  }       
		  else if(S[i] == m)      //�õ�������λ��M��Ԫ�ؼ���S2[n2]
		  {           
			 // S2[n2] = S[i];            
			  n2++;         
		  }        
		  else{          
			  S3[n3] = S[i];         //�õ�������λ��M��Ԫ�ؼ���S3[n3]  		               
     		  n3++;          
		  }     
	  }

	  //�ͷ��ڴ�ռ�
	  delete []M;
      
	  if(n1 > k) 
	  {
		  //�ͷ��ڴ�ռ�
		 // delete []S2;
		  delete []S3;
		  
		  //�ݹ鴦��
		  return(select(k,S1,n1));        //��S1��Ѱ�ҵ�KСԪ��
	  }
      else if(n1 + n2 >= k) 
	  {
		  //�ͷ��ڴ�ռ�
		  delete []S1;
		//  delete []S2;
		  delete []S3;

		  //���ؽ��
		  return m;            //M����Ҫ�ҵ�Ԫ��
	  }
	  else 
	  {
		  //�ͷ��ڴ�ռ�
		  delete []S1;
		//  delete []S2;

		  //�ݹ鴦��
		  return(select(k - n1 - n2,S3,n3));     //����S1��S2,��S3��Ѱ�ҵ�KСԪ��
	  }
  }
}

int main()
{
	printf("������Ԫ�ظ���N,ϵͳ���Զ��������N��������N=");

	int n,k,i;
	int *A,*a;
	scanf("%d",&n);
	
	printf( "��������Ҫ�ҵĵ�k��1��%d֮�䣩СԪ�ص�k=",n);
	scanf("%d",&k);
	printf("��Ҫ����Ļ����ʾ���ɵ�Ԫ��������y��ʾ��n����ʾ��y/n��:");
	char flag;
	scanf("%s",&flag);
	if(flag == 'y')
	{
		printf("������ϵͳ������ɵ�%d��Ԫ�أ�",n);
	}

	//�ļ�����
	FILE *fp;
	fp = fopen("kthElement.txt","w");
	if(!fp)
	{
		printf( "Error to open file to write");
		return 0;
	}
	fprintf(fp,"%d %d\n",n,k);

	A = new int[n]; //����������ڴ�ռ�
	a = new int[n];

	srand((int)time(0));//�����������
	for(i=0;i<n;i++) //�������N��Ԫ��
	{
		A[i] = rand(); //�������0-10000֮�������
		a[i] = A[i];
		if(flag == 'y')
		{
			printf("%d ",A[i]);
		}
		fprintf(fp,"%d ",A[i]);
	}

	//cout<< "�����ļ����ɳɹ�"<<endl;
	int result;  
	clock_t start,finish;
	double duration;
	
	start = clock();	
	result = select(k,A,n); 
    finish = clock();
    duration = (double)((finish - start)*1.0/CLOCKS_PER_SEC);
 
    printf("\n����λѡ���ҵ��ĵ�%dСԪ����:%d \n����ʱ�䣺%lf ��\n",k,result,duration); 
	fprintf(fp,"\n����λѡ���ҵ��ĵ�%dСԪ����:%d ",k,result);
	fclose(fp);
    delete[]A;
	return 0;
}


