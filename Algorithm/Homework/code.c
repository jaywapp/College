#include stdio.h
#include string.h
#include stdlib.h
#pragma warning (disable4996)

#define FILENAME 100

int d;
int count_d;
int answer;
int SET_LENGTH;
int NUM_SUBSET;

int (subset);
int set;
int stack;
int temp_stack;
int top = -1;

void add_Answerlist(int sub);
void sub_Answerlist(int sub);
int check_Answerlist();
void find(int start);
void push(int item);
int pop();
void display();
void reset();
void saveStack();


void main()
{
	int i,j; for문 사용시
	char temp[50];
	int buf;
	char pt1;
	FILE file;
	file = NULL;
	while(1)
	{
		printf(file  );
		scanf(%s,temp);
		file = fopen(temp,rt);
		if(file !=NULL)
			break;
		printf(%sn,temp);
	}
	
	1st Line  원소의 갯수
	2st Line  Subset의 갯수
	3st Line 부터는 subset
	
			1st Line	  
	fgets(temp,100,file);
	SET_LENGTH = atoi(temp);
			2nd Line	  
	fgets(temp,100,file);
	NUM_SUBSET=atoi(temp);
	
	printf(Union length = %dn,SET_LENGTH);
	printf(Number of subset = %dn,NUM_SUBSET);
	1,2번째 라인을 통해 입력받은 set과 subset 메모리 할당
	set = (int)malloc(sizeof(int)SET_LENGTH);
	set[SET_LENGTH] = NULL;
	answer = (int)malloc(sizeof(int)SET_LENGTH);
	answer[SET_LENGTH] = NULL;
	stack = (int)malloc(sizeof(int)NUM_SUBSET);
	temp_stack = (int)malloc(sizeof(int)NUM_SUBSET);
	subset = (int) malloc(sizeof(int)  NUM_SUBSET);
	Union setting
	for(i=0;iSET_LENGTH;i++)
	{
		set[i] = i+1;
	} 
	for(i=0; iNUM_SUBSET ;i++)
	{
		fgets(temp,100,file);
		pt1 = strtok(temp, );		
		j=0;
		subset[i] = (int)malloc(sizeof(int)SET_LENGTH);
		while(pt1!=NULL)
		{
			printf(%s,pt1);
			buf = atoi(pt1);
			subset[i][j] = buf;
				pt1 = strtok(NULL, );
			j++;
		}
		subset[i][j] = NULL;
	}
    d=NUM_SUBSET;
	count_d = 0;
	
	for(i=0;iNUM_SUBSET;i++)
	{
		for(j=0;jSET_LENGTH;j++)
			answer[j] = 0;
	}
	for(i=0;iNUM_SUBSET;i++)
		find(i);
	printf(%d n,d);
}
void saveStack()
{
	int i;
	for(i=0;iNUM_SUBSET;i++)
		temp_stack[i] = NULL;
	for(i=0;i=top;i++)
	{
		temp_stack[i] = stack[i];
	}

}
void find(int start)
{
	int i ,j;
	int temp;
	count_d++;
	push(start);
	
	add_Answerlist(subset[start]);
	temp = check_Answerlist();
	if(temp == 1)
	{
		d=count_d;
		pop();
		count_d--;
		sub_Answerlist(subset[start]);
		saveStack();
		display();
		return;
	}
	else if(temp != 1 && dcount_d+1)
	{
		for(i=start+1;iNUM_SUBSET;i++)
		{
			find(i);
		}
	}
	count_d--;
	pop();
	sub_Answerlist(subset[start]);
};


void add_Answerlist(int sub)
{
	int i = 0;  
	while(sub[i]!=NULL)
	{
		answer[sub[i]-1]++;
		i++;
	}

};
void sub_Answerlist(int sub)
{
	int i = 0;
	while(sub[i]!=NULL)
	{
		answer[sub[i]-1]--;
		i++;
	}
};
int check_Answerlist()
{
	int i=0;
	for(i=0;iSET_LENGTH;i++)
	{
		if(answer[i] == 0)
			return 0;
	}
	return 1;
};

void push(int item)
{
	stack[++top]=item;
};
int pop()
{
	return stack[top--];
};
void display()
{
	int i;
	printf(subsets  );
	for(i=top;i=0;i--)
		printf(%d ,stack[i]);
	printf(n);
};
void reset()
{
	int i ;
	for(i=top;i=0;i--)
		stack[i] =NULL;
	top = -1;
	
};