//2010. 10. 26
//�������2 : �ù����̼� ���α׷���

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int intro()
{
	printf("Ajou University\n");
	printf("Information & Computer Engineering\n");
	printf("Programing �������2 : Simulation Program\n\n");
	printf("�к� : ������ǻ�Ͱ��к�\n");
	printf("�й� : 201020268\n");
	printf("�̸� : ���ؿ�\n\n\n");
	printf("�ؽù����̼� Ƚ���� integer�������� �Է����ּ���\n");
	printf("dart���Ӱ� Buffon�� �ٴù����� �ù����̼� �� ������ �����Ͻÿ�.\n");
}


float dartprocess(int num)
{
	float x,y,len;
	float result;
	int k=0,hit=0;

	
	while(k<=num)
	{
		x=rand()/16383.5;
		y=rand()/16383.5;
		x=(1-x)*(1-x);
		y=(1-y)*(1-y);
		len=sqrt(x+y);
		if(len<=1)
			hit=hit+1;
		k=k+1;
	}

	result=(float)num/(float)hit;
	return result;
}
int dart()
{	
	int num;
	float result;
	printf("�ù����̼� Ƚ�� -> ");
	scanf("%d",&num);
	result=dartprocess(num);
	printf("�ù����̼��� %dȸ �����Ͽ����� try/hit�� %.3f�̴�.\n",num,result);
	choice();
}
float Buffonprocess(int num)
{
	int hit=0;
	int k=0;
	float ylow,yhigh,result;
	float rad,rad1,rad2;
	

	while(k<=num)
	{
		
		ylow=rand()/16383.5;
		rad1=rand()%180;
		rad2=rand()/32767;
		rad=rad1+rad2;
		yhigh=ylow+sin(rad*(3.14/180));
		if(yhigh>=2)
			hit=hit+1;
		k=k+1;
	}

	result=(float)num/(float)hit;
	return result;

}
int Buffon()
{
	int num;
	float result;
	printf("�ù����̼� Ƚ�� -> ");
	scanf("%d",&num);
	result=Buffonprocess(num);
	printf("�ù����̼��� %dȸ �����Ͽ����� try/hit�� %.3f�̴�.\n",num,result);
	choice();
}
int choice()
{
	char A;
	
	printf("��� �����Ͻðڽ��ϱ�?(Y/N) -> ");
	fflush(stdin);
	scanf("%c",&A);
	if(A=='Y')
		select();
}
int select()
{
	int a;
	printf("\n� �ù����̼��� �����Ͻðڽ��ϱ�?\n(1)dart����(2)Buffon�� �ٴù��� -> ");
	scanf("%d",&a);

	if(a==1)
		dart();
	else if(a==2)
		Buffon();
}
int main()
{
	srand(time(NULL));
	intro();
	select();

}