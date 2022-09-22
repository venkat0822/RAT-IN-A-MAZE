#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;
int maze[50][50];
void find_shortestpath(int, int , int, int,int,int );
void do_move(int ,int );
void do_moveerase(int ,int );
void put_maze(int ,int );
void do_fillwall(int ,int );
void do_pathprint(int ,int ,int );
int main()
{
	initwindow(700,700);
	int x,y,sx,sy,ex,ey;
	cout<<"\t\t\t------------------------------------"<<endl;
	cout<<"\t\t\t\t   RAT IN A MAZE "<<endl;
	cout<<"\t\t\t\t  (SHORTEST PATH) "<<endl;
	cout<<"\t\t\t------------------------------------"<<endl;
	cout<<"Enter the dimensions of the maze: ";
	cin>>x>>y;
	cout<<"Enter the starting location of the rat: ";
	cin>>sx>>sy;
	cout<<"Enter the ending location of the rat: ";
	cin>>ex>>ey;
	find_shortestpath(sx,sy,ex,ey,x,y);
	return 0;
}
struct queue
{
    int rear, front;
    int size;
    int *st;	
    queue(int s)
    {
       front = rear = -1;
       size = s;
       st = new int[s];
    }
    void add(int val)
	{
        if((rear+1)%size==front)
            cout<<"Queue Is Full"<<endl;
        else
            if(front==-1)
                front=0;
            rear=(rear+1)%size;
            st[rear]=val;
    }
    int delet()
	{
        int data=st[front];
        if(front==-1 && rear==-1)
            cout<<"Queue is empty"<<endl;
        else
            if(front==rear)
                front=rear=-1;
            else
                front=(front+1)%size;
        return data;
    }
};
void find_shortestpath(int startx, int starty, int endx, int endy,int m,int n)
{
	int move[4][2]={ {0,1},{1,0},{0,-1},{-1,0} };
	int beginx,beginy,exitx,exity;
	int nei_x=0,nei_y=0,e;
	int path_len,path_x[100],path_y[100];
	cout<<"\nCreating maze in the window.."<<endl;
	put_maze(m,n);
	cout<<"\nEnter the elements row wise: "<<endl;
	for(int c=1;c<=m;c++)
	{
		for(int d=1;d<=n;d++)
		{	
			cin>>e;
			maze[c][d]=e;
			if(maze[c][d]==1)
				do_fillwall(c,d);
		}
	}
	for(int i=0;i<m+2;i++)
    {
        maze[0][i]=maze[m+1][i]=1;
        maze[i][0]=maze[i][m+1]=1;
	}
	queue q1(100);
	queue q2(100);
	beginx=startx+1;beginy=starty+1;
	exitx=endx+1;exity=endy+1;
	maze[startx+1][starty+1]=2;
	while(true)
	{
		for(int i=0;i<4;i++)
		{
			nei_x=beginx+move[i][0];
            nei_y=beginy+move[i][1];
             if(maze[nei_x][nei_y]==0)
			{
                maze[nei_x][nei_y]=maze[beginx][beginy]+1;
                q1.add(nei_x);
                q2.add(nei_y);
            }
            if(nei_x==exitx && nei_y==exity)
            {	
                 break;
            }
		}
		if(nei_x==exitx && nei_y==exity)
		{
            break;
        }
        else if(q1.front==-1)
		{
            cout<<"NO SHORTEST PATH"<<endl;
            getch();
            break;
        }
        else 
		{
	        beginx=q1.delet();
	        beginy=q2.delet();
        }
	}
	int num=0;
	while(true)
	{
        path_len=maze[exitx][exity]-2;
        beginx=exitx;
        beginy=exity;
        for(int i=path_len;i>=0;i--)
		{
            path_x[num]=beginx;
            path_y[num]=beginy;
            num++;
            for(int j=0;j<4;j++)
			{
                nei_x=beginx+move[j][0];
                nei_y=beginy+move[j][1];
                if(maze[nei_x][nei_y]==maze[beginx][beginy]-1)
				{
					break;
				}
            }
            beginx=nei_x;
            beginy=nei_y;
        }
        break;
    }
   	cout<<"\nThe Maze : "<<endl;
     for(int i=0;i<=(m+1);i++)
	 {
        for(int j=0;j<=(n+1);j++)
		{
            cout<<maze[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"\nShortest path: "<<endl;
    for(int i=num-1;i>=0;i--)
	{
        do_move(path_x[i],path_y[i]);
        Sleep(500);
        do_moveerase(path_x[i],path_y[i]);
        Sleep(500);
    }
    for(int i=num-1;i>=0;i--)
	{
        cout<<"-->"<<"("<<path_x[i]-1<<","<<path_y[i]-1<<")"<<endl;
        do_pathprint(path_x[i],path_y[i],1);
        Sleep(500);
    }
    cout<<"Shortest path has been printed"<<endl;
    getch();
}
void do_move(int i,int j)
{
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL,MAGENTA);
    rectangle(100+((j-1)*50)+1,100+((i-1)*50)+1,100+((j)*50)-1,100+((i)*50)-1);
    floodfill(100+(j-1)*50+2,100+(i)*50-2,MAGENTA);
}
void do_moveerase(int i,int j)
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(100+(j-1)*50+1,100+(i-1)*50+1,100+(j*50)-1,100+(i*50)-1);
    floodfill(100+(j-1)*50+2,100+(i)*50-2,BLACK);

}
void put_maze(int x,int y)
{
    rectangle(100,100,300+(x-4)*50,300+(x-4)*50);
    for(int i=1;i<=x-1;i++)
	{	
		setcolor(LIGHTCYAN);
        line(100+(i*50),100,100+(i*50),300+(x-4)*50);
    }
    for(int i=1;i<=x-1;i++)
	{	
		setcolor(LIGHTCYAN);
        line(100,100+(i*50),300+(x-4)*50,100+(i*50));
    }
    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(50,50,100,300+(x-4)*50+50);//leftmost
    floodfill(51,300+(x-4)*50+50-1,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,50,300+(x-4)*50+50,100);//TOP
    floodfill(101,99,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(300+(x-4)*50,100,300+(x-4)*50+50,300+(x-4)*50+50);//RIGHT
    floodfill(300+(x-4)*50+1,300+(x-4)*50-1,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,300+(x-4)*50,300+(x-4)*50,300+(x-4)*50+50);//BOTTOM WALL
    floodfill(101,300+(x-4)*50+50-1,BLUE);

    setcolor(YELLOW);
    rectangle(50,50,300+(x-4)*50+50,300+(x-4)*50+50);
    setcolor(YELLOW);
    rectangle(100,100,300+(x-4)*50,300+(x-4)*50);   
}
void do_fillwall(int x,int y)
{
    setcolor(RED);
    setfillstyle(SOLID_FILL,RED);
    rectangle(100+(y-1)*50+1,100+(x-1)*50+1,100+(y)*50-1,100+(x)*50-1);
    floodfill(100+(y-1)*50+2,100+(x)*50-2,RED);
}
void do_pathprint(int p,int q,int n)
{
    if(n==0)
	{
	    setcolor(GREEN);
	    setfillstyle(SOLID_FILL,GREEN);
	    rectangle(100+((q-1)*50)+1,100+((p-1)*50)+1,100+((q)*50)-1,100+((p)*50)-1);
	    floodfill(100+(q-1)*50+2,100+(p)*50-2,GREEN);
    }
    else
	{
	    setcolor(GREEN);
	    setfillstyle(SOLID_FILL,GREEN);
	    rectangle(100+((q-1)*50)+1,100+((p-1)*50)+1,100+((q)*50)-1,100+((p)*50)-1);
	    floodfill(100+(q-1)*50+2,100+(p)*50-2,GREEN);
    }

}
