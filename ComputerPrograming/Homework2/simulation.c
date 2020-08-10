//2010. 10. 26
//설계과제2 : 시물레이션 프로그래밍

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>


int intro()
{
	printf("Ajou University\n");
	printf("Information & Computer Engineering\n");
	printf("Programing 설계과제2 : Simulation Program\n\n");
	printf("학부 : 정보컴퓨터공학부\n");
	printf("학번 : 201020268\n");
	printf("이름 : 박준영\n\n\n");
	printf("※시물레이션 횟수를 integer범위내에 입력해주세요\n");
	printf("dart게임과 Buffon의 바늘문제중 시물레이션 할 문제를 선택하시오.\n");
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
	printf("시물레이션 횟수 -> ");
	scanf("%d",&num);
	result=dartprocess(num);
	printf("시물레이션을 %d회 수행하였으며 try/hit는 %.3f이다.\n",num,result);
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
	printf("시물레이션 횟수 -> ");
	scanf("%d",&num);
	result=Buffonprocess(num);
	printf("시물레이션을 %d회 수행하였으며 try/hit는 %.3f이다.\n",num,result);
	choice();
}
int choice()
{
	char A;
	
	printf("계속 진행하시겠습니까?(Y/N) -> ");
	fflush(stdin);
	scanf("%c",&A);
	if(A=='Y')
		select();
}
int select()
{
	int a;
	printf("\n어떤 시물레이션을 선택하시겠습니까?\n(1)dart게임(2)Buffon의 바늘문제 -> ");
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