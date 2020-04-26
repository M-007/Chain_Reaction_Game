#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<time.h>
//main screen begins
void chain(); // Chain Reaction Function
int bc;


//Block Structure 2*D array
struct node
{
	int max,cur,col;
	struct node* l,*r,*u,*d;
} *rx[8][8],*tempx;


int mc=0;
void explodeup(int xc,int yc,int c);
void link1();
int maincheck();
void check(struct node*p);
void link();
void setvalues();
void redball(int xc,int yc);
void blueball(int xc,int yc);
void move();
void table();
void explode(int xc,int yc);
//main
int m=120,n=200,z=205,x,y;
char ch;
int initmouse();
void arrow();
int status;
void text();
void showmouseptr();
void loading();
void second();
void nextpage();
void sajavat();
void concept();
void getmousepos(int *button,int *x,int *y);
union REGS i,o;
int u,v,l=12,button;
//char s[20];
long int r=700;

void main()
 {

	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..//BGI");
	setbkcolor(5);
	status=initmouse();
	if(status==0)
	{}
	else
	{
        showmouseptr();
	    setbkcolor(RED);
	    sajavat();
	    text();
        concept();
	}
	second();
	}
	void second()
	{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"..//BGI");
    while(ch!='q')
    {
    ch=getche();

    // arrow
    if(ch==13 &&n==200)
    {
    chain();
    second();
    }
    delay(0);
    cleardevice();
    sound(600);
    nextpage();
    arrow();
    }
    getch();
	closegraph();


	}



int initmouse()
{
	setbkcolor(RED);
	i.x.ax=0;
	int86(0X33,&i,&o);
	return (o.x.ax);
}
void showmouseptr()
{
	i.x.ax=1;
	int86(0X33,&i,&o);
}
void getmousepos(int *button,int *x,int *y)
{
	i.x.ax=3;
	int86(0X33,&i,&o);
	*button=o.x.bx;
	*x=o.x.cx;
	*y=o.x.dx;
}
void sajavat()
{
	for(u=0;u<=getmaxx();u=u+10)
	{
		setcolor(BLUE);
		outtextxy(u,0,"-*-");
	}
	for(v=0;v<=getmaxy();v=v+10)
	{
		setcolor(YELLOW);
		outtextxy(0,v,"*  ");
	}
	for(u=0;u<=getmaxx();u=u+10)
	{
		setcolor(BLUE);
		outtextxy(u,getmaxy()-8," *");
	}
	for(v=2;v<=getmaxy()-5;v=v+10)
	{
		setcolor(YELLOW);
		outtextxy(getmaxx()-9,v,"*");
	}
}
void text()
{

//while(!kbhit())
//{
for(u=0;u<15;u++)
{
setcolor(u);
setbkcolor(RED);
settextstyle(7,0,6);
outtextxy(180,100,"WELCOME ");
settextstyle(7,0,6);
outtextxy(270,175,"TO ");
settextstyle(7,0,6);
outtextxy(110,250,"GAMING ZONE ");
delay(100);
}
}
//}
void nextpage()
   {
    cleardevice();
    setbkcolor(RED);
    arrow();
    setcolor(1);
    settextstyle(7,0,8);
    outtextxy(95,40,"***GAMES***");
    setcolor(14);
    settextstyle(1,0,4);
    outtextxy(150,185,"   CHAIN REACTION");
    nosound();
  }
void loading()
     {
        setcolor(RED);
        rectangle(250,400,400,450);
        setfillstyle(SOLID_FILL,RED);
        floodfill(260,420,RED);
        setcolor(BLUE) ;
        settextstyle(0,0,2);
        outtextxy(210,400," LOADING");
        rectangle(200,430,370,440);

    for(u=200;u<370;u++)
    {
        for(v=430;v<440;v++)
        {
            setcolor(BLUE);
            rectangle(u,v,370,440);
            setfillstyle(SOLID_FILL,BLUE);
            floodfill(u,v,BLUE);
            sound(r);
            delay(25);
            break;
        }
        r=r+20;
    }
 }
 void concept()
   {
   int x,y;
    getmousepos(&button,&x,&y);
    rectangle(270,410,360,450);
   setfillstyle(SOLID_FILL,YELLOW);
   floodfill(300,425,YELLOW);
   setcolor(4);
   settextstyle(0,0,2);
   outtextxy(275,425,"ENTER");


    while(!kbhit())
    {
    getmousepos(&button,&x,&y);
    if(button==1)
    {
    button=-1;
    if( 270<x && x<320 && 410<y && y<440)
    {
    loading();
    nextpage();

    }
   }
  }
}



void arrow()
{
        setcolor(BROWN);
        line(m,n,m+30,n);
        line(m,n,m,n+10);
        line(m,n+10,m+30,n+10);
        line(m+30,n,m+30,n-10);
        line(m+30,n+10,m+30,n+20);
        line(m+30,n-10,m+40,z);
        line(m+30,n+20,m+40,z);
        setfillstyle(SOLID_FILL,BROWN);
        floodfill(m+5,n+5,BROWN);
}

//main screen end
//chain begin
void chain()
{

     int i;
     link1();
     setvalues();
     link();
     table();
     while(mc<2)
     move();
     while(maincheck()==0)
     move();

     setfillstyle(SOLID_FILL,LIGHTGREEN);
      bar(150,100,460,300);
      setcolor(BLUE);
     settextstyle(0,0,4);
     outtextxy(240,120,"GAME");
     outtextxy(240,160,"OVER");
	//	setcolor(12);
     if(maincheck()==1)
     outtextxy(180,215," RED WINS");
     else
     outtextxy(170,215,"BLUE WINS");


     getch();

     closegraph();
}
void link1()
{
	int i,j;
	for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	{
		tempx=(struct node*)malloc(sizeof(struct node));
		rx[i][j]=tempx;
		rx[i][j]->col=3;
	}
}
void link()
{
	int i=0,j=0;
	for(i=0;i<8;i++)
		for(j=0;j<7;j++)
		rx[i][j]->r=rx[i][j+1];
	for(i=0;i<8;i++)
		for(j=7;j>0;j--)
		rx[i][j]->l=rx[i][j-1];
	for(i=1;i<8;i++)
		for(j=0;j<8;j++)
		rx[i][j]->u=rx[i-1][j];
	for(i=0;i<7;i++)
		for(j=8;j>0;j--)
		rx[i][j]->d=rx[i+1][j];

}
void setvalues()
{
	int i , j;
	//linking and setting values of max ,cul and cur.
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			rx[i][j]->max=3;
			rx[i][j]->cur=0;
			rx[i][j]->col=0;
			if(i==0)
			{
				rx[i][j]->u=NULL;
				rx[i][j]->max--;
			}
			if(j==0)
			{
				rx[i][j]->l=NULL;
				rx[i][j]->max--;
			}
			if(j==7)
			{
				rx[i][j]->r=NULL;
				rx[i][j]->max--;
			}
			if(i==7)
			{
				rx[i][j]->d=NULL;
				rx[i][j]->max--;
			}

		}
	}
}
void table()
{
	int gd=DETECT,gm,i,x=150,y=50;
	initgraph(&gd,&gm,"..\\bgi");

	  setlinestyle(0,0,3);
	setbkcolor(14);
	setcolor(2);
	for(i=0;i<9;i++)
	{
		line(x+(40*i),y,x+(40*i),y+320);
		line(x,y+(40*i),x+320,y+(40*i));
	}


/*setcolor(BLUE);
setfillstyle(SOLID_FILL,BLUE);
circle(x+10,y+20,5);
floodfill(x+10,y+20,BLUE);
outtextxy(500,200,"WELCOME") ;
*/
	getch();

}
void move()
{
	int x=150,y=50,l=1;//gd=DETECT,gm;
	char ch;
	if(mc%2==0)
	l=1;
	else
	l=4;
	//initgraph(&gd,&gm,"..\\bgi");
	setcolor(l);
	setlinestyle(0,0,3);
	rectangle(x,y,x+40,y+40);
	ch=getch();
	while(ch!=13)
	{
		if(ch=='n')
		second();
		if(ch==72&&y>50)
		{
			delay(10);
			setcolor(GREEN);
			rectangle(x,y,x+40,y+40);
			y=y-40;
		}
		else
		if(ch==75&&x>150)
		{
			delay(10);
			setcolor(GREEN);
			rectangle(x,y,x+40,y+40);
			x=x-40;
		}

		else
		if(ch==80&&y<330)
		{
			delay(10);
			setcolor(GREEN);
			rectangle(x,y,x+40,y+40);
			y=y+40;
		}
		else
		if(ch==77&&x<430)
		{
			delay(10);
			setcolor(GREEN);
			rectangle(x,y,x+40,y+40);
			x=x+40;
		}
		setcolor(l);
		rectangle(x,y,x+40,y+40);
		ch=getch();
	}
	setcolor(GREEN);
	rectangle(x,y,x+40,y+40);
	if(mc++%2==0)
	{
		blueball(x,y);

	}
	else
	{
		redball(x,y);
	}
}
void blueball(int xc,int yc)
{

	int i,j,k=0,x=xc,y=yc;
	i=(y-50)/40;

	j=(x-150)/40;
		//increase line by traversing using link
	++rx[i][j]->cur;
	k=rx[i][j]->cur;
	if(rx[i][j]->cur<=rx[i][j]->max && rx[i][j]->col!=1)
	{
		if(k==1)
		{
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,BLUE);
			circle(x+20,y+20,5);
			floodfill(x+20,y+20,BLUE);
		}
		else
		if(k==2)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(x+20,y+20,GREEN);
			setfillstyle(SOLID_FILL,BLUE);
			setcolor(BLUE);
			circle(x+10,y+20,5);
			circle(x+30,y+20,5);
			floodfill(x+30,y+20,BLUE);
			floodfill(x+10,y+20,BLUE)   ;


		}
		else
		if(k==3)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(x+20,y+20,GREEN);
			setcolor(BLUE);
			setfillstyle(SOLID_FILL,BLUE);
			circle(x+10,y+26,5);
			floodfill(x+10,y+26,BLUE);
			circle(x+20,y+13,5);
			floodfill(x+20,y+13,BLUE);
			circle(x+30,y+26,5);
			floodfill(x+30,y+26,BLUE);

		}
		rx[i][j]->col=2;


	}
	else
	if(rx[i][j]->cur>=rx[i][j]->max && rx[i][j]->col!=1)
	{


		rx[i][j]->cur=0;

		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(x+20,y+13,GREEN);
		floodfill(x+20,y+20,GREEN);
		explode(x,y);
	rx[i][j]->col=0;
	}
	else
	{
	mc-- ;
	--rx[i][j]->cur;
	}
}

void redball(int xc,int yc)
{
	int i,j,k=0,x=xc,y=yc;
	i=(y-50)/40;
	j=(x-150)/40;
		//increase line by traversing using link
	++rx[i][j]->cur;
	k=rx[i][j]->cur;
	if(rx[i][j]->cur<=rx[i][j]->max && rx[i][j]->col!=2)
	{
		if(k==1)
		{
			setcolor(RED);
			setfillstyle(SOLID_FILL,RED);
			circle(x+20,y+20,5);
			floodfill(x+20,y+20,RED);
		}
		else
		if(k==2)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(x+20,y+20,GREEN);
			setfillstyle(SOLID_FILL,RED);
			setcolor(RED);
			circle(x+10,y+20,5);
			circle(x+30,y+20,5);
			floodfill(x+30,y+20,RED);
			floodfill(x+10,y+20,RED)  ;
		}
		else
		if(k==3)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			floodfill(x+20,y+20,GREEN);
			setcolor(RED);
			setfillstyle(SOLID_FILL,RED);
			circle(x+10,y+26,5);
			floodfill(x+10,y+26,RED);
			circle(x+20,y+13,5);
			floodfill(x+20,y+13,RED);
			circle(x+30,y+26,5);
			floodfill(x+30,y+26,RED);
		}
		rx[i][j]->col=1;
	}
	else
	if(rx[i][j]->cur>=rx[i][j]->max && rx[i][j]->col!=2)
	{



	       rx[i][j]->cur=0;

		setfillstyle(SOLID_FILL,YELLOW);
		floodfill(x+20,y+13,GREEN);
		floodfill(x+20,y+20,GREEN);
		explode(x,y);
		rx[i][j]->col=0;
	}
	else
	{
		mc--    ;
		--rx[i][j]->cur;
	}

}
int maincheck()
{
	int b=0,r=0,i=0,j=0;
	for(i=0;i<8;i++)
	for(j=0;j<8;j++)
	{
		if(rx[i][j]->col==1)
		b=1;
		else
		if(rx[i][j]->col==2)
		r=1;
	}
	if(r==0)
	return 1;
	else
	if(b==0)
	return 2;
	else
	return 0;

}
void explode(int xc,int yc)
{
	int i,j,x=xc,y=yc;
	i=(y-50)/40;
	j=(x-150)/40;
    if(rx[i][j]->col!=2)
	{
		explodeup(x,y,4);
		if(rx[i][j]->u!=NULL)
		{
            rx[i-1][j]->col=rx[i][j]->col;
            redball(x,y-40);

		}
		if(rx[i][j]->d!=NULL)
		{
            rx[i+1][j]->col=rx[i][j]->col;
            redball(x,y+40);
		}
		if(rx[i][j]->l!=NULL)
		{
            rx[i][j-1]->col=rx[i][j]->col;
            redball(x-40,y);
		}
		if(rx[i][j]->r!=NULL)
		{
            rx[i][j+1]->col=rx[i][j]->col;
            redball(x+40,y);
		}
	}
	else
	if(rx[i][j]->col!=1)
	{
		explodeup(x,y,1);
	if(rx[i][j]->u!=NULL)
	{
	      rx[i-1][j]->col=rx[i][j]->col;

	    blueball(x,y-40);


	}

	if(rx[i][j]->d!=NULL)
	{
	      rx[i+1][j]->col=rx[i][j]->col;

	    blueball(x,y+40);
		}

	if(rx[i][j]->l!=NULL)
	{
	      rx[i][j-1]->col=rx[i][j]->col;

	      blueball(x-40,y);

	}

	if(rx[i][j]->r!=NULL)
	{
	      rx[i][j+1]->col=rx[i][j]->col;

	     blueball(x+40,y);

	}
	}
}
void explodeup(int xc,int yc,int c)
{
	void *p;int i,j,x=xc,y=yc; int area;
	area=imagesize(x+5,y-45,x+45,y+45);
       p=malloc(area);
       getimage(x+5,y-45,x+45,y+45,p);
       setcolor(c);
       for(i=0;i<40;i++)
       {                if(y>50)
			{
			setcolor(GREEN);
			setlinestyle(0,0,3);
			line(x,y,x+40,y);
			setcolor(c);
			setlinestyle(SOLID_FILL,0,2);
			circle(x+20,y+20-i,5);
	      //	rectangle(x,y,);
			setfillstyle(SOLID_FILL,c);

			floodfill(x+20,y+20-i,c);
			setcolor(YELLOW);
			setlinestyle(SOLID_FILL,0,2);
			arc(x+20,y+20-i,180,360,6);
				}
			 if(y<330)
			 {
			setcolor(GREEN);
			setlinestyle(0,0,3);
			line(x,y+40,x+40,y+40);
			setcolor(c);
			setlinestyle(SOLID_FILL,0,2);
			circle(x+20,y+20+i,5);
	      //    /	rectangle(x,y,);
			setfillstyle(SOLID_FILL,c);

			floodfill(x+20,y+20+i,c);
			setcolor(YELLOW);
			setlinestyle(SOLID_FILL,0,2);
			arc(x+20,y+20+i,0,180,6);
			}
			if(x>150)
		       {
			setcolor(GREEN);
			setlinestyle(0,0,3);
			line(x,y,x,y+40);
			setcolor(c);
			setlinestyle(SOLID_FILL,0,2);
			circle(x+20-i,y+20,5);
	      //	rectangle(x,y,);
			setfillstyle(SOLID_FILL,c);

			floodfill(x+20-i,y+20,c);
			setcolor(YELLOW);
			setlinestyle(SOLID_FILL,0,2);
			arc(x+20-i,y+20,270,90,6);
			}
			if(x<430)
			{
			setcolor(GREEN);
			setlinestyle(0,0,3);
			line(x+40,y,x+40,y+40);
			setcolor(c);
			setlinestyle(SOLID_FILL,0,2);
			circle(x+20+i,y+20,5);
	      //	rectangle(x,y,);
			setfillstyle(SOLID_FILL,c);

			floodfill(x+20+i,y+20,c);
			setcolor(YELLOW);
			setlinestyle(SOLID_FILL,0,2);
			arc(x+20+i,y+20,90,270,6);
			}

	    delay(7);
	   // putimage(x+5,y-45,p,COPY_PUT);
	   // delay(10);
       }


}
//chain end
