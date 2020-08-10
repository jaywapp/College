#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)
#define NAME_LEN 10
#define MAX_SIZE 50
#define NUM_OF_ROUTE 10
int top=-1, t_t=-1;
typedef struct{
	int x;//row, vert
	int y;//col, horiz
}point;
typedef struct{
	int vert;//x, row
	int horiz;//y, col
}Move;
typedef struct{
	int row; //x, vert
	int col; //y, horiz
	int dir;
}element;
element stack[MAX_SIZE];
element trial[MAX_SIZE];
Move move[8];
void move_setting();
void push_t (element item);
void push (element item);
element pop ();


int main()
{
	while(1)
	{
	FILE *fileopen;
	FILE *filewrite;
	while(1)
	{
	//#####################file part################
	char str1[NAME_LEN];//파일이름
	char str2[NAME_LEN];//파일이름
	char indata[NAME_LEN];	//입력스트링
	char tok=NULL;
	char* tok1, *tok2;
	point Point;
	element Element;
	/*  출발점, 도착점, 방향 */
	point SP[NUM_OF_ROUTE];
	point EP[NUM_OF_ROUTE];
	char DI[NUM_OF_ROUTE][NUM_OF_ROUTE];
	int DIR[NUM_OF_ROUTE]; 
	int maze[MAX_SIZE+2][MAX_SIZE+2];
	int mark[MAX_SIZE+2][MAX_SIZE+2];
	//**************************
	int x=0,y=0,i=0,j=0,k=0,a=0,turn=0,count=0; 
	int option=0;
	int OP_point=0;
	int nextcol=0,nextrow=0;
	move_setting();//move structure setting
	/*               파일 open 및 생성					*/
	while(1)
	{
		*str1=NULL;
		*str2=NULL;
		printf("Enter the input file name (press q to stop) : ");
		scanf("%s",&str1);
		if((str1[0]=='q' || str1[0]=='Q')&& str1[1]==NULL) 
		{	
			return 0;
		}
		printf("Output file name (press q to stop) : ");
		scanf("%s",&str2);
		if((str2[0]=='q' || str2[0]=='Q')&&str2[1]==NULL) 
		{
			return 0;
		}
		fileopen=fopen(str1,"rt");
		if(fileopen!=NULL)
		{
			break;
		}
		printf("- Connot find file. retry\n");
		*str1=NULL;
		*str2=NULL;
	}
	/*          SP EP DIR 초기화           */
	for(a=0;a<NUM_OF_ROUTE;a++)
	{
		SP[a].x=0;
		SP[a].y=0;
		EP[a].x=0;
		EP[a].y=0;
		DIR[a]=8;
	}
	//********************************************************
	/*                      maze size                        */
	tok=fgetc(fileopen);
	Point.x=atoi(&tok);
	tok=fgetc(fileopen);
	while(tok!='x')
	{
		Point.x=10*Point.x;
		Point.x=Point.x+atoi(&tok);
		tok=fgetc(fileopen);
	}
	tok=fgetc(fileopen);
	Point.y=atoi(&tok);
	tok=fgetc(fileopen);
	while(tok!='\n')
	{
		Point.y=10*Point.y;
		Point.y=Point.y+atoi(&tok);
		tok=fgetc(fileopen);
	}
	if(Point.x==1 && Point.y==1)
	{
		printf("wrong type : %d x %d. retry.\n",Point.x,Point.y);
		return 0;
	}
	else if(Point.x>50 && Point.y>50)
	{
		printf("Size is bigger than Max size : %d x %d. retry.\n",Point.x,Point.y);
		return 0;
	}
	//****************************************************************
	i=0;//입력받은 좌표를  maze에 입력하기위한 옵션
	for(i=0;i<MAX_SIZE+2;i++)
	{
		for(j=0;j<MAX_SIZE+2;j++)
		{
			maze[i][j]=1;
			mark[i][j]=0;
		}
	}
	option=1;
	while(1)
	{
		if(fgets(indata,sizeof(indata),fileopen)==NULL || strstr(indata,"-----")!=NULL)
		{break;}
		else if(option!=0)
		{
			tok1=strtok(indata," ");
			tok2=strtok(NULL,"\n");
			maze[atoi(tok1)][atoi(tok2)]=0;
		}
		option=1;
	}
	i=0;
	while(1)
	{
	fscanf(fileopen,"(%d %d) (%d %d) %s\n",&SP[i].x,&SP[i].y,&EP[i].x,&EP[i].y,&DI[i]);
		if(SP[i].x==0 && SP[i].y==0 && EP[i].x==0 && EP[i].y==0)
		{
			break;
		}
	i++;
	}
	for(j=0;j<i;j++)
	{
			DIR[j]=Direction(DI[j]);
	}
	turn=i;
	filewrite=fopen(str2,"w+"); 
	/*                 file part 끝               */

	//#################Maze part###################
	for(i=0;i<turn;i++)
	{
	top=-1;
	t_t=-1;
	option=0;
	count=0;
	for(a=0;a<MAX_SIZE;a++)
	{
		for(k=0;k<MAX_SIZE;k++)
		mark[a][k]=0;
	}
	Element.row=SP[i].x;
	Element.col=SP[i].y;
	Element.dir=DIR[i];	
	mark[Element.row][Element.col]=1;
		while(1)
		{
		nextrow = Element.row+move[Element.dir].vert;
		nextcol = Element.col+move[Element.dir].horiz;
	

		if(Element.row==EP[i].x && Element.col==EP[i].y)
		{
			push(Element);
			break;
		}
		if(maze[nextrow][nextcol]==0 && mark[nextrow][nextcol]==0)
		{
			push(Element);
			Element.row=nextrow;
			Element.col=nextcol;
			push_t(Element);
			mark[Element.row][Element.col]=1;
			Element.dir=DIR[i];
		}
		else if(maze[nextrow][nextcol]!=0 || mark[nextrow][nextcol]!=0)
		{
			Element.dir++;
			if(Element.dir==8)
				Element.dir=0;
			if(Element.dir==DIR[i])
			{
				Element=pop();
				if(top==-1)
				{
					option=1;
					break;
				}
				push_t(Element);
				if(DIR[i]!=7)
					Element.dir=DIR[i]+1;
				else if(DIR[i]==7)
					Element.dir=0;
				if(Element.dir==8)
					Element.dir=0;
			}
			
		}
		}
		if(option==0)
		{
			fprintf(filewrite,"(%d %d) (%d %d) %s\n",SP[i].x,SP[i].y,EP[i].x,EP[i].y,DI[i]);
			fprintf(filewrite,"path : ");
			for(a=0;a<=top;a++)
			{
				fprintf(filewrite,"(%d %d) ",stack[a].row,stack[a].col);
			}
			fprintf(filewrite,"\n");
			fprintf(filewrite,"trial : ");
			fprintf(filewrite,"(%d %d) ",SP[i].x,SP[i].y);
			for(a=0;a<=t_t;a++)
			{
				fprintf(filewrite,"(%d %d) ",trial[a].row,trial[a].col);
			}
			fprintf(filewrite,"\n");
		}
		else if(option!=0)
		{
			fprintf(filewrite,"%d's goal : there is no path.\n",i+1);
		}
	}
}
	fclose(filewrite);
	fclose(fileopen);
	}
}

	
int Direction(char* C)
{
	char fir,sec;
	fir=C[0];
	if(C[1]=='E' || C[1]=='W')
		sec=C[1];
		
	else
		sec=NULL;
		
	if(fir=='N' && sec==NULL)
		return 0;
	else if(fir=='N' && sec=='E')
		return 1;
	else if(fir=='E' && sec==NULL)
		return 2;
	else if(fir=='S' && sec=='E')
		return 3;
	else if(fir=='S' && sec==NULL)
		return 4;
	else if(fir=='S' && sec=='W')
		return 5;
	else if(fir=='W' && sec==NULL)
		return 6;
	else if(fir=='N' && sec=='W')
		return 7;
	else
		return 8;
}
void move_setting()
{
	int i;
	for(i=0;i<8;i++)
		{
			switch(i)
			{
				case 0:
					{
						move[i].vert=-1;
						move[i].horiz=0;
						break;
					}
				case 1:
					{
						move[i].vert=-1;
						move[i].horiz=1;
						break;
					}
				case 2:
					{
						move[i].vert=0;
						move[i].horiz=1;
						break;
					}
				case 3:
					{
						move[i].vert=1;
						move[i].horiz=1;
						break;
					}
				case 4:
					{
						move[i].vert=1;
						move[i].horiz=0;
						break;
					}
				case 5:
					{
						move[i].vert=1;
						move[i].horiz=-1;
						break;
					}
				case 6:
					{
						move[i].vert=0;
						move[i].horiz=-1;
						break;
					}
				case 7:
					{
						move[i].vert=-1;
						move[i].horiz=-1;
						break;
					}
			}
		}//move struct 초기화

}

void push (element item)
{
if (top >=MAX_SIZE-1) 
	{
		return;
	}
	stack[++top] = item;
}
void push_t (element item)
{
if (t_t >=MAX_SIZE-1) 
	{
		return;
	}
	trial[++t_t] = item;
}
element pop ()
{
if (top == -1)
	{
	return;
	}
	return stack[top--];
}

