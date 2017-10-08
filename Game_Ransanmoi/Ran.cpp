#include<Windows.h>
#include <stdio.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include <fstream>
#include <iostream>
//#include "console.h"
#define consoleWidth 25
#define consoleHeight 25;
using namespace std;
//
void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}

void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void TextColor (int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , color);
}
//
enum TrangThai{UP,DOWN,LEFT,RIGHT};

struct ToaDo
{
	int y,x;
};

struct HoaQua
{
	ToaDo td;
	int dem=0;
};

struct Snake
{
	ToaDo dot[30];
	int n;
	TrangThai tt;
};

void KhoiTao(Snake &snake,HoaQua &hq)
{

	snake.n = 1;// xuat hien 1 dot
	snake.dot[0].x=0;// co gia tri
	snake.dot[0].y=0;
	snake.tt=RIGHT;	// dau tien khi vao ran se di ve dang trc
	hq.td.x=10; // moi an o vtri x=10 y=10
	hq.td.x=10;
}
void HienThi(Snake snake,HoaQua hq)
{
clrscr();// xoa man hinh
for(int i=0;i<=25;i++)
{
	gotoXY(50,i);// in ra dong gach
	putchar(179);
}
for(int j=0;j<=50;j++)
{
	gotoXY(j,25);// in ra dong gach
	putchar(196);
}
gotoXY (hq.td.x,hq.td.y);
putchar(3);
for(int i=0;i<snake.n;i++)
	{
	gotoXY (snake.dot[i].x, snake.dot[i].y);
putchar(3);
	}	
		gotoXY(0,25);
			cout<<"\n CHUC BAN CO NHUNG PHUT GIAY CHOI THAT VUI VE !!!";
				cout<<"\n\t Diem cua ban :"<<hq.dem;
}

void DieuKien_DiChuyen(Snake &snake)
{
	for(int i=snake.n - 1; i>0;i--)// Chuyen dot 3 thanh dot 2.....
	snake.dot[i]=snake.dot[i-1];//
	
	if(kbhit())
	{
		int key=_getch();
		if(key=='A'||key=='a'||key==75)// gia tri 75 la ky hieu mui ten trai, 77 la mui ten phai, gia tri 72 la mui ten duoi, 80 len
			snake.tt=LEFT;
		else if(key=='D'||key=='d'||key==77)	
			snake.tt=RIGHT;
		else if(key=='W'||key=='w'||key==72)
			snake.tt=UP;
		else if(key=='S'||key=='s'||key==80)
			snake.tt=DOWN;
	}
	if(snake.tt==UP)
		snake.dot[0].y--;// neu la up thi y giam tuc la di len
	else if(snake.tt==DOWN)
		snake.dot[0].y++;
	else if(snake.tt==LEFT)
		snake.dot[0].x--;
	else if(snake.tt==RIGHT)
		snake.dot[0].x++;
		
}
int XuLy(Snake &snake,HoaQua &hq)
{
	if(snake.dot[0].x==hq.td.x&&snake.dot[0].y==hq.td.y)
	{
		// a hoa qua
		for(int i=snake.n;i>0;i--)
		snake.dot[i]=snake.dot[i-1];
		snake.n++;
		hq.dem++;
		
		if(snake.tt==UP)
		snake.dot[0].y--;
	else if(snake.tt==DOWN)
		snake.dot[0].y++;
	else if(snake.tt==LEFT)
		snake.dot[0].x--;
	else if(snake.tt==RIGHT)
		snake.dot[0].x++;
		hq.td.x=rand()%consoleWidth;
		hq.td.y=rand()%consoleHeight;
		
	}
	if(snake.dot[0].x<0||snake.dot[0].x>50||snake.dot[0].y<0||snake.dot[0].y>25)
	return -1;
	for(int i=1;i<snake.n;i++)
		if(snake.dot[0].x==snake.dot[i].x&&snake.dot[0].y==snake.dot[i].y)
		return -1;
}


int XuLy2(Snake &snake,HoaQua &hq)
{
	if(snake.dot[0].x==hq.td.x&&snake.dot[0].y==hq.td.y)
	{
		// a hoa qua
		for(int i=snake.n;i>0;i--)
		snake.dot[i]=snake.dot[i-1];
		snake.n++;
		hq.dem++;
		if(snake.tt==UP)
		snake.dot[0].y--;
	else if(snake.tt==DOWN)
		snake.dot[0].y++;
	else if(snake.tt==LEFT)
		snake.dot[0].x--;
	else if(snake.tt==RIGHT)
		snake.dot[0].x++;
		hq.td.x=rand()%consoleWidth;
		hq.td.y=rand()%consoleHeight;
		
	}
	if(snake.dot[0].x<0)
		snake.dot[0].x=49;
		else if(snake.dot[0].x>49)
				snake.dot[0].x=0;
				else if(snake.dot[0].y<0)
					snake.dot[0].y=24;
						else if(snake.dot[0].y>24)
						snake.dot[0].y=0;
	
	for(int i=1;i<snake.n;i++)
		if(snake.dot[0].x==snake.dot[i].x&&snake.dot[0].y==snake.dot[i].y)
		return -1;
}
int main()
{
		srand(time(NULL));//khoi tao sinh so ngau nhien
		Snake snake;
		HoaQua hq;
		KhoiTao(snake,hq);
		int ma,ma2;
		char ten[20];
		cout<<"Nhap ten nguoi choi : ";
		cin>>ten;
		std::cin.clear();
		char luachon[20];
		char mucdo[20];
		char mucdo2;
		int lc;
		do
		{
			cout<<"\n\t Che do choi 1: Co dien---2:Hien dai";
		cout<<"\n\t Nhap lua chon :";
		fflush(stdin);
		gets(luachon);
		std::cin.clear();
		lc = atoi(luachon);
			if(lc==0)
				{
					cout<<"\n\t Nhap lai ";
				}
		}
		while(lc!=1&&lc!=2);
		do
		{
			cout<<"1:de--2 Trung binh --3 Kho";
		cout<<"\n\t Muc do :";
		fflush(stdin);
		gets(mucdo);
		std::cin.clear();
		mucdo2 = atoi(mucdo);
			if(mucdo2==0)
				{
					cout<<"\n\t Nhap lai ";
				}
		}while(mucdo2!=1&&mucdo2!=2&&mucdo2!=3);
		
	if(lc==1)
	{
	while(1)
	{
		TextColor(8+rand()%8);
		HienThi(snake,hq);
		DieuKien_DiChuyen(snake);
		//xu ly
	//	ma=	XuLy(snake,hq);
	//	if(ma==-1)
	//	{
	//	gotoXY(10,10);
	//	cout<<"\n\t "<<ten<<" choi thua roi !!";
	//		while(_getch()!=13);
	//		break;
	//	}
		///xu ly 2
		ma2=	XuLy2(snake,hq);
		if(ma2==-1)
		{
		gotoXY(10,10);
		cout<<"\n\t "<<ten<<" choi thua roi !!";
		gotoXY(10,11);
		cout<<"\n\t Cam on "<<ten<<" da choi !!";
	
		
			while(_getch()!=13);
			break;
		}
		if(mucdo2==1)
		Sleep(300);
			else if(mucdo2==2)
			Sleep(200);
				else 
				Sleep(50);
	}
	}
	else if(lc==2)
	{
	while(1)
	{
		TextColor(8+rand()%8);
		HienThi(snake,hq);
		DieuKien_DiChuyen(snake);
		//xu ly
		ma=	XuLy(snake,hq);
		if(ma==-1)
		{
		gotoXY(10,10);
		cout<<"\n\t "<<ten<<" choi thua roi !!";
		gotoXY(10,11);
		cout<<"\n\t Cam on "<<ten<<" da choi !!";
		
			while(_getch()!=13);
			break;
		}
		///xu ly 2
	//	ma2=	XuLy2(snake,hq);
	//	if(ma2==-1)
	//	{
	//	gotoXY(10,10);
	//	cout<<"\n\t "<<ten<<" choi thua roi !!";
	//		while(_getch()!=13);
	//		break;
	//	}
			if(mucdo2==1)
		Sleep(300);
			else if(mucdo2==2)
			Sleep(200);
				else 
				Sleep(50);
	}	
	
	}
	

	return 0;
}
