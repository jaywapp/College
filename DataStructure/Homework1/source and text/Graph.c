#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable:4996)

#define MAX_NUM_OF_VERTEX 20
#define MAX_NAME 15
#define MAX_STACK 50
#define TRUE	1
#define FALSE	0
#define MIN2(x,y) ((x)<(y) ? (x):(y))

typedef struct node *nodePt;
typedef struct node
{
	int vertex;
	nodePt link;
}node;
typedef struct string
{
	char name[MAX_NAME];
}string;
typedef struct Stack
{
	int num1;
	int num2;
}stack;
nodePt graph[MAX_NUM_OF_VERTEX];
string vertex[MAX_NUM_OF_VERTEX];
short int mark[MAX_NUM_OF_VERTEX];
int matrix[MAX_NUM_OF_VERTEX][MAX_NUM_OF_VERTEX];
int dfn[MAX_NUM_OF_VERTEX];
int low[MAX_NUM_OF_VERTEX];
stack Stack[MAX_STACK];
int Articulation[MAX_NUM_OF_VERTEX];
int ConnectedList[MAX_NUM_OF_VERTEX];
int LowList[MAX_NUM_OF_VERTEX];
int count_point=0;
int count_Connect=0;
int count_bi=0;
int Connect=0;
int num = 0;
int top = -1;
void ClearMark();
void Initialize();
int findVertex(char* name);
void init(int count);
void connected(int count);
void dfs(int v);
void bicon(int u, int v);
void push(int x, int y);
void pop(int* x, int* y);
int search(int A[MAX_NUM_OF_VERTEX], int i );
int search2(int A[MAX_NUM_OF_VERTEX], int i );
void main()
{
	int i=0;
	int j=0;
	int k=0;
	printf("Welcome to \"See Route Development System\"\n");
	while(1)
	{
		FILE * filein;
		FILE * fileout;
		char openFile[MAX_NAME] = "";
		char closeFile[MAX_NAME] = "";
		char temp[20] ;
		char line[10000] = {NULL};
		char *str1,*str2=NULL;
		int index1=-1;
		int index2=-1;
		int NumofVertex = 0;
		int NumofArticulation = 0;
		Initialize();
		
		//----------------------파일 불러오기---------------------------
		while(1)//파일stream부분
		{
			printf("Enter the input file name (press q to stop) : ");
			scanf("%s",openFile);
			if((openFile[0]=='q' || openFile[0]=='Q') || openFile==NULL) 
				return;
			printf("Enter the output file name (press q to stop) : ");
			scanf("%s",closeFile);
			if((closeFile[0]=='q' || closeFile[0]=='Q') || closeFile==NULL) 
				return;
			filein=fopen(openFile,"rt");
			fileout=fopen(closeFile,"w+");
			if(filein!=NULL)
				break;
			printf("- Connot find file. retry\n");
		}
		fgets(temp,sizeof(temp),filein);
		NumofVertex = atoi(temp);
		if(NumofVertex>MAX_NUM_OF_VERTEX)
		{
			printf("Number of vertex in file excess Maximum Size!\n");
			break;
		}
		for(i = 0; i<NumofVertex;i++)
		{
			for(j=0;j<NumofVertex;j++)
				matrix[i][j]=0;
		}
		for(i = 0; i<NumofVertex;i++)
		{
			fscanf(filein,"%s",vertex[i].name);
		}
		fgets(line,sizeof(line),filein);
		while(!feof(filein))
		{
			fgets(line,sizeof(line),filein);
			str1 = strtok(line," ");
			str2 = str1;
			str1 = strtok(NULL,"\n");
			index1 = findVertex(str2);
			index2 = findVertex(str1);
			matrix[index1][index2]=1;
			matrix[index2][index1]=1;
		}
		for(i=0;i<NumofVertex;i++)
		{
			mark[i]=0;
		}

		init(NumofVertex);
		connected(NumofVertex);
		if(Connect==1) // Articulation Point 찾고, biconnected graph가 되도록 경로 추가
		{
			fprintf(fileout,"The route do connect all the islands\n");//Connected 판단
			//##############################################
			// Articulation Point @@@@
			bicon(0,-1); 
			for(i=0;Articulation[i]!=-1;i++) 
			{
				NumofArticulation=i;
			}
			if(Articulation[NumofArticulation]==0)
				Articulation[NumofArticulation]=-1;
			fprintf(fileout,"Attentions  : ");
			for(i=0;Articulation[i]!=-1;i++)
			{
				fprintf(fileout,"%s ",vertex[Articulation[i]].name);
			}
			if(Articulation[0]==-1)
				fprintf(fileout,"<blank>");
			fprintf(fileout,"\n");
			//##############################################
			// Connected -> biconnected @@@@
			for(i=0;Articulation[i]!=-1;i++)
			{
				low[Articulation[i]]=-1;
			}
			for(i=0;i<NumofVertex;i++)
			{
				for(j=0;j<NumofVertex;j++)
				{
					if(i==low[j] && low[j]!=-1)
					{
						LowList[count_bi++]=j;
						j=NumofVertex;
					}
				}
			}
			fprintf(fileout,"Recommendations  : ");
			for(i=0;LowList[i+1]!=-1;i++)
			{
				fprintf(fileout,"%s-%s ",vertex[LowList[i]].name,vertex[LowList[i+1]].name);
			}
			if(LowList[1]==-1)
				fprintf(fileout,"<blank>");
			fprintf(fileout,"\n");
			//##############################################
			

		}
		else if(Connect==0) // Articulation Point 없음, connected graph가 되도록 경로 추가
		{
			fprintf(fileout,"The route do not connect all the islands\n"); //Connected 판단
		
			fprintf(fileout,"Attentions  : ");
			for(i=0;ConnectedList[i]!=-1;i++)
			{
				printf("%d\n",ConnectedList[i]);
				bicon(ConnectedList[i],-1); 
				for(j=0;Articulation[j]!=-1;j++) 
				{
					NumofArticulation=j;
				}
				Articulation[NumofArticulation]=-1;
				
				for(j=0;Articulation[j]!=-1;j++)
				{
					fprintf(fileout,"%s ",vertex[Articulation[j]].name);
				}
				if(Articulation[0]==-1 && i==0)
					fprintf(fileout,"<blank>");
				for(j=0;j<NumofVertex;j++)
				{
					Articulation[j]=-1;
				}
				count_point=0;
				NumofArticulation=0;

			}
			fprintf(fileout,"\n");
			//	fprintf(fileout,"Attentions : <blank>\n"); //Connected Graph가 아니면 AP없음.
			//##############################################
			// Non-Connected -> Connected @@@@
			fprintf(fileout,"Recommendations  : ");
			for(i=0;ConnectedList[i+1]!=-1;i++)
			{
				fprintf(fileout,"%s-%s ",vertex[ConnectedList[i]].name,vertex[ConnectedList[i+1]].name);
			}
			if(ConnectedList[1]==-1)
				fprintf(fileout,"<blank>");
			fprintf(fileout,"\n");
			//##############################################
		}
		fclose(fileout);
		fclose(filein);
	}
}


void bicon(int u, int v)
{
	nodePt ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
//	int count=0;
	for(ptr=graph[u]; ptr;ptr = ptr->link)
	{

		w = ptr->vertex;
		if(v!=w && dfn[w]<dfn[u])
			push(u,w);
		if(dfn[w]<0)
		{
			bicon(w,u);
			low[u] = MIN2(low[u],low[w]);
			if(low[w] >= dfn[u])
			{
				//printf("New biconnected component : ");
				do
				{
					pop(&x,&y);
					//printf("<%d, %d>",x,y);
				}while(!((x==u) && (y==w)));
				//printf("\n");
			}
		}
		else if(w!=v)
		{
			low[u] = MIN2(low[u],dfn[w]);
		}
	}
	if(dfn[v] <=low[u])
	{
		if(search(Articulation,v)==0)
		{
			Articulation[count_point++] = v;
		}
	}

};
void push(int x, int y)
{
	Stack[++top].num1=x;
	Stack[top].num2=y;
}
void pop(int* x, int* y)
{
	*x=Stack[top].num1;
	*y=Stack[top--].num2;
}

int findVertex(char* name)
{
	int i;
	for(i =0 ; i<MAX_NUM_OF_VERTEX ; i++)
	{
		if(strcmp(vertex[i].name,name)==0)
			return i;
	}
	return -1;
};
void Initialize()
{

	int i=0,j=0;
	num = 0;
	top = -1;
	Connect = NULL;
	count_point = 0;
	count_Connect=0;
	count_bi=0;
	for(i=0;i<MAX_NUM_OF_VERTEX;i++)
	{
		LowList[i]=-1;
		ConnectedList[i]=-1;
		mark[i] = -1;
		Articulation[i]=-1;
		dfn[i] = -1;
		low[i] = -1;
		for(j=0;j<MAX_NAME;j++)
			vertex[i].name[j]=NULL;
		for(j=0;j<MAX_NUM_OF_VERTEX;j++)
			matrix[i][j]=-1;
	}
	for(i=0;i<MAX_STACK;i++)
	{
		Stack[i].num1=NULL;
		Stack[i].num2=NULL;
	}
	ClearMark();
};
void ClearMark()
{
	int i;
	for(i=0;i<MAX_NUM_OF_VERTEX;i++)
		mark[i] = -1;
};
void init(int count)   
{ 
    int x,y, i; 
	nodePt move=NULL;          
    nodePt st=NULL;          
    nodePt tmp=NULL;          
	for(x=0; x<count; x++) 
    { 
        st = graph[x];         
        for(y=0; y<count; y++) 
        { 
            if(matrix[x][y] != FALSE)  
            { 
				tmp = (nodePt)malloc(sizeof(node)); 
                 tmp->vertex = y;      
                 if(graph[x] == st)    
                 {      
			         move = tmp;     
				     graph[x] = tmp;
                 } 
                 else       
                 {    
                     move->link = tmp; 
                     move = tmp; 
                 } 
             } 
        } 
        tmp->link = NULL;      
	} 

};
void connected(int count)
{
	int i,j;
	Connect=1;
	for(i=0;i<count;i++)
	{
		if(!mark[i])
		{
			ConnectedList[count_Connect++]=i;
			dfs(i);
			
			for(j=0;j<count;j++)
			{
				if(mark[j]==0)
				{
					Connect=0;
				}
			}
		}
	}
};
void dfs(int v)  
 { 
	nodePt w; 
    mark[v] = TRUE;
    for(w=graph[v]; w; w = w->link) 
	if(!mark[w->vertex]) 
		 dfs(w->vertex); 
 };  
int search(int A[MAX_NUM_OF_VERTEX], int i )
{
	int a;
	for(a=0;a<MAX_NUM_OF_VERTEX;a++)
	{
		if(A[a]==i)
			return 1;
	}
	
	return 0;
};
int search2(int A[MAX_NUM_OF_VERTEX], int i )
{
	int a;
	for(a=0;a<MAX_NUM_OF_VERTEX;a++)
	{
		if(A[a]==i)
			return a;
	}
	
	return -1;
};