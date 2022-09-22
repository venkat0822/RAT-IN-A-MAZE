#include<iostream>
#include<graphics.h>
#include<conio.h>
using namespace std;
void put_maze(int,int);
void do_fillwall(int,int);
void do_backtrack(int,int);
void do_move(int,int);
void do_moveerase(int,int);
void do_pathprint(int,int,int);
void find_path(int,int);
int maze[50][50],mark[50][50];
int main()
{	
	initwindow(700,700);
	int x,y;
	cout<<"\t\t\t------------------------------------"<<endl;
	cout<<"\t\t\t\t   RAT IN A MAZE "<<endl;
	cout<<"\t\t\t\t  (FINDING PATH) "<<endl;
	cout<<"\t\t\t------------------------------------"<<endl;
	cout<<"Enter the dimensions of the maze: ";
	cin>>x>>y;
	find_path(x,y);
	return 0;
}
void find_path(int m, int n)
{
	int pathstack[m*n][3],startx,starty,exitx,exity,e;
	int move[8][2]={ {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
	cout<<"\nCreating maze in the window.."<<endl;
	put_maze(m,n);
	cout<<"\nEnter the elements row wise: "<<endl;
	for(int c=1;c<=m;c++)
	{
		for(int d=1;d<=n;d++)
		{	
			cin>>e;
			maze[c][d]=e;
			mark[c][d]=e;
			if(maze[c][d]==1)
				do_fillwall(c,d);
		}
	}
	for(int c=0;c<=n+1;c++)
	{
		maze[0][c]=maze[n+1][c]=1;
		maze[c][0]=maze[c][n+1]=1;
	}
	cout<<"\nPrinting the maze: "<<endl;
	for(int c=0;c<=m+1;c++)
	{
		cout<<"\n\t";
		for(int d=0;d<=n+1;d++)
			cout<<maze[c][d]<<" ";
	}
	cout<<"\nEnter the coordinates of starting point: ";
	cin>>startx>>starty;
	cout<<"\nEnter the coordinates of the exit point: ";
	cin>>exitx>>exity;
	if (maze[startx+1][starty+1]==1)
	{
		cout<<"\nNo path, as the starting element is zero!"<<endl;
		getch();
	}
	else if (maze[exitx+1][exity+1]==1)
	{
		cout<<"\nNo path, as the ending element is zero!"<<endl;
		getch();
	}
	else
	{
		int p,q,top=0;
		pathstack[0][0]=startx+1;
	    pathstack[0][1]=starty+1;
	    pathstack[0][2]=0;
	    maze[startx+1][starty+1]=1;
	    mark[startx+1][starty+1]=1;
	    while(top!=-1)
	    {
	    	int i=pathstack[top][0];
	    	int j=pathstack[top][1];
	    	int direc=(pathstack[top][2]+1);
	    	top--;
	    	do_backtrack(p,q);
        	Sleep(500);
	    	while(direc<=8)
	    	{
	    		int g=i+move[direc-1][0];
            	int h=j+move[direc-1][1];
            	if(g==exitx+1 && h==exity+1)
            	{	
					Sleep(500);
	                do_move(i,j);
	                Sleep(500);
	                do_moveerase(i,j);
	                Sleep(500);
	                do_move(g,h);
	                Sleep(500);
	                do_moveerase(g,h);
            		cout<<"\nPrinting the path: "<<endl;
            		for(int i=0;i<=top;i++)
            		{
            			cout<<"-->"<<"("<<pathstack[i][0]-1<<","<<pathstack[i][1]-1<<")"<<endl;
            			do_pathprint(pathstack[i][0],pathstack[i][1],0);
                    	Sleep(500);
                    }
            		cout<<"-->"<<"("<<i-1<<","<<j-1<<")"<<endl;
                	cout<<"-->"<<"("<<exitx<<","<<exity<<")"<<endl;
                	do_pathprint(i,j,0);
               		Sleep(500);
                	do_pathprint(exitx+1,exity+1,0);
                	cout<<"\nThe path has been printed.."<<endl;
                	getch();
                	return;
				}
				else if(maze[g][h]==0 && mark[g][h]==0)
				{
	                mark[g][h]=1;
	                top++;
	                pathstack[top][0]=i;
	                pathstack[top][1]=j;
	                pathstack[top][2]=direc; 
	                do_move(i,j);
                	Sleep(500);
                	do_moveerase(i,j);
                	Sleep(500);
	                i=g;j=h;direc=0;
            	}
            	direc++;
            }
            p=i,q=j;
            do_move(i,j);
        	Sleep(500);
        	do_moveerase(i,j);
        	Sleep(500);
		}
		cout<<"\nNo path found!"<<endl;
		getch();
	}
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
    rectangle(50,50,100,300+(x-4)*50+50);
    floodfill(51,300+(x-4)*50+50-1,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,50,300+(x-4)*50+50,100);
    floodfill(101,99,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(300+(x-4)*50,100,300+(x-4)*50+50,300+(x-4)*50+50);
    floodfill(300+(x-4)*50+1,300+(x-4)*50-1,BLUE);

    Sleep(500);
    setcolor(BLUE);
    setfillstyle(SOLID_FILL,BLUE);
    rectangle(100,300+(x-4)*50,300+(x-4)*50,300+(x-4)*50+50);
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
void do_backtrack(int x,int y)
{
    setcolor(GREEN);
    setfillstyle(SOLID_FILL,GREEN);
    rectangle(100+(y-1)*50+1,100+(x-1)*50+1,100+(y*50)-1,100+(x*50)-1);
    floodfill(100+(y-1)*50+2,100+(x)*50-2,GREEN);

}
void do_move(int x,int y)
{
    setcolor(MAGENTA);
    setfillstyle(SOLID_FILL,MAGENTA);
    rectangle(100+((y-1)*50)+1,100+((x-1)*50)+1,100+((y)*50)-1,100+((x)*50)-1);
    floodfill(100+(y-1)*50+2,100+(x)*50-2,MAGENTA);
}
void do_moveerase(int x,int y)
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(100+(y-1)*50+1,100+(x-1)*50+1,100+(y*50)-1,100+(x*50)-1);
    floodfill(100+(y-1)*50+2,100+(x)*50-2,BLACK);

}
void do_pathprint(int p,int q,int n)
{
    if(n==0)
	{
	    setcolor(WHITE);
	    setfillstyle(SOLID_FILL,WHITE);
	    rectangle(100+((q-1)*50)+1,100+((p-1)*50)+1,100+((q)*50)-1,100+((p)*50)-1);
	    floodfill(100+(q-1)*50+2,100+(p)*50-2,WHITE);
    }
    else
	{
	    setcolor(WHITE);
	    setfillstyle(SOLID_FILL,WHITE);
	    rectangle(800+((q-1)*50)+1,100+((p-1)*50)+1,800+((q)*50)-1,100+((p)*50)-1);
	    floodfill(800+(q-1)*50+2,100+(p)*50-2,WHITE);
    }

}

