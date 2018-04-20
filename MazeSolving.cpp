#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Mat.h"
#define MAXSIZE 50 //规定地图最大值
#include <windows.h>  

int Maze[MAXSIZE+2][MAXSIZE+2];
int start_x,start_y,end_x,end_y;
long seed1;	

typedef struct{
	int x,y,di;
}SElemType;//定义节点的数据类型

typedef struct{
	SElemType e[MAXSIZE*MAXSIZE];
	int top;
}Stack; //定义一个顺序栈 

void Init(Stack &s)
{
	s.top=0;
}
void Push(Stack &s,SElemType e1)
{
	s.e[s.top]=e1;
	s.top++;
}
void Pop(Stack &s)
{
	s.top--;
}
void GetTop(Stack s,SElemType &e1)
{
	if(s.top==0)
		return;
	e1=s.e[s.top-1];
}
int JudgeEmpty(Stack s)
{
	if(s.top==0)
		return 1;
	else
		return 0;
}
void WalkedMark(SElemType e)
{
	Maze[e.x][e.y]=2;//代表走过了 
}
void NoWayMark(SElemType e) 
{
    Maze[e.x][e.y] =3;//代表是死路节点 
}
int Pass(SElemType &e) 
{
    int cache_x,cache_y;
    while(e.di < 4)
	 {
        e.di++;
        switch(e.di) 
		{
            case 1:cache_x = e.x;cache_y = e.y + 1;break;
            case 2:cache_x = e.x + 1;cache_y = e.y;break;
            case 3:cache_x = e.x;cache_y = e.y - 1;break;
            case 4:cache_x = e.x - 1;cache_y = e.y;break;
        }
        if (Maze[cache_x][cache_y] == 0) {
            e.x = cache_x;
            e.y = cache_y;
            e.di = 0;
            return 1;
        }
    }
    return 0;
}
void printPath(Stack S) 
{
    int i;
    printf("一条通路如下\n");
    for (i = 0; i < S.top; i++) {
        printf("(%d, %d)\t", S.e[i].x, S.e[i].y);
    }
}
int MazePath(int n)
{
	Stack s;
	SElemType e;
	e.x=start_x;e.y=start_y;e.di=0;
	Init(s);Push(s,e);WalkedMark(e);
	while(!JudgeEmpty(s))
	{
		GetTop(s,e);
		if(e.x==end_x&&e.y==end_y)
		{
			printPath(s);
			return 1;
		}
		if(Pass(e))
		{
			Push(s,e);
			WalkedMark(e);
		}
		else
		{
			Pop(s);
			NoWayMark(e);	
		}
	}
	 return 0;

}
void InitMaze(int n)
{
    int i, j;
   // srand( (unsigned)time(NULL));
   srand(seed1);
    for (i=0; i<n+2; i++) {
        for (j=0; j<n+2; j++) {
            if (i==0 || i==n+1 || j==0 || j==n+1) {
                Maze[i][j] = 1;
            } else {
                Maze[i][j] = rand()%2;
            }
        }
    }

}
void InitMazeWithP(int n,double p)
{
    int walls=p*n*n;
    int i,j;
    int cache_x,cache_y;
    //srand((unsigned)time(NULL));
    srand(seed1);

	for (i=0; i<n+2; i++) 
        for (j=0; j<n+2; j++) 
            if (i==0 || i==n+1 || j==0 || j==n+1) 
                Maze[i][j] = 1;
    for (i=1; i<n+1; i++) 
        for (j=1; j<n+1; j++) 
            Maze[i][j] = 0;


    while(walls>0)
	{
		cache_x=rand()%n+1;
		cache_y=rand()%n+1;
		if(Maze[cache_x][cache_y]==1)
			continue;
		else
		{
			Maze[cache_x][cache_y]=1;
			walls--;
		}
	}

    
}
void PrintMaze(int n) {
    int i, j;
    printf("\n");
    for (i=0; i<n+2; i++) {
        for (j=0; j<n+2; j++) 
		{
			if(Maze[j][i]==1)
            printf("1 ", Maze[j][i]);
            else 
            printf("0 ");
        }
        printf("\n");
    }
}
void PrintMap(int n)
{
	Mat p;
	MatInitial(p,50*(n+3),50*(n+3));
	int i, j;
    for (i=0; i<n+2; i++) 
	{

        for (j=0; j<n+2; j++) 
		{
			if(Maze[i][j]==1)
			MatRect(p,i*50,j*50,i*50+50,j*50+50,136,177,239);
       		else if(Maze[i][j]==2)
       		MatRect(p,i*50,j*50,i*50+50,j*50+50,249,243,227);
	    }

    }
    printf("\n");
   	MatRect(p,start_x*50,start_y*50,start_x*50+50,start_y*50+50,249,243,227);
    MatRect(p,0,0,(n+2)*50,50,100,100,100);
    MatRect(p,0,(n+1)*50,(n+2)*50,(n+2)*50,100,100,100);
    MatRect(p,0,0,50,(n+2)*50,100,100,100);
    MatRect(p,(n+1)*50,0,(n+2)*50,(n+2)*50,100,100,100);
        for (i=0; i<n+2; i++) 
	{
      	MatRect(p,0,i*50,(n+2)*50,1+i*50,246,218,217);
     	MatRect(p,i*50,0,1+i*50,(n+2)*50,246,218,217);
     }

    	    MatOutput(p,"test");
    	    printf("地图已经绘制并保存\n");

}


int main()
{
	int n;
	double p;
	seed1=time(NULL)*time(NULL);	
	printf("请输入n，然后创建一个n*n的迷宫,n在1~50\n");
	scanf("%d",&n);
	printf("请输入p，为墙体密度:(大于0小于1)\n");
	scanf("%lf",&p);
	printf("请输入起点坐标，x y\n");
	scanf("%d%d",&start_x,&start_y);
	printf("请输入终点坐标，x y\n");
	scanf("%d%d",&end_x,&end_y);
	InitMazeWithP(n,p);
	Maze[start_x][start_y] = Maze[end_x][end_y] = 0; /* 起点和终点 */

	while (!MazePath(n))
	 {
        printf("这次尝试没有成功哦，重试一次~\n");
        seed1++;
       	InitMazeWithP(n,p); 
    }
    PrintMaze(n);
	PrintMap(n);
		
}
