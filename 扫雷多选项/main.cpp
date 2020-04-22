#include <Windows.h>
#include "resource.h"
#include "Matrix.h"
#include "Player.h"
#include "Tableau.h"
//全局变量
HWND hMain;			//主菜单窗口句柄
HWND hGameWin=NULL;	//游戏窗口句柄
HINSTANCE hIn;		//实例句柄
CTableau Tableau;	//画主菜单背景对象
CMatrix Matrix;		//地雷矩阵对象
CPlayer Player;		//玩家控制对象
int BUTTONDOWN_X=0,BUTTONDOWN_Y=0;	//按下鼠标时的坐标
//函数声明
LRESULT CALLBACK MainWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);	//主菜单窗口回掉函数
LRESULT CALLBACK GameWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);	//游戏窗口回调函数

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevhInstance,LPSTR lpCmdline,int CmdShow)
{
	WNDCLASS MainWin;
	WNDCLASS GameWin;
	HWND MainhWnd;
	MSG msg;
	
	hIn=hInstance;

	MainWin.cbClsExtra=NULL;
	MainWin.cbWndExtra=NULL;
	MainWin.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	MainWin.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	MainWin.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	MainWin.hInstance=hInstance;
	MainWin.lpfnWndProc=MainWinCallBack;
	MainWin.lpszClassName="MainWindow";
	MainWin.lpszMenuName=NULL;
	MainWin.style=CS_HREDRAW|CS_VREDRAW;

	RegisterClass(&MainWin);

	GameWin.cbClsExtra=NULL;
	GameWin.cbWndExtra=NULL;
	GameWin.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	GameWin.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR2));
	GameWin.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	GameWin.hInstance=hInstance;
	GameWin.lpfnWndProc=GameWinCallBack;
	GameWin.lpszClassName="GameWindow";
	GameWin.lpszMenuName=NULL;
	GameWin.style=CS_HREDRAW|CS_VREDRAW;

	RegisterClass(&GameWin);
	//创建主菜单窗口
	hMain=MainhWnd=CreateWindow("MainWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,350,100,704,600,NULL,NULL,hInstance,NULL);
	//显示主菜单窗口
	ShowWindow(MainhWnd,SW_SHOW);
	//消息循环
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK MainWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int wmId;		//点击的控件id
	PAINTSTRUCT ps;
	static HWND hNightBtn;	//9*9矩阵按钮
	static HWND hSixteenBtn;	//16*16矩阵按钮
	static HWND hthirtyBtn;		//16*32矩阵按钮
	static HWND hExit;			//退出按钮
	switch(message)
	{
case WM_CREATE:
	hNightBtn=CreateWindow("button","9×9", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,270,350,150,50,hWnd,(HMENU)1001,hIn,0);
	hSixteenBtn=CreateWindow("button","16×16", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,270,400,150,50,hWnd,(HMENU)1002,hIn,0);
	hthirtyBtn=CreateWindow("button","16×30", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,270,450,150,50,hWnd,(HMENU)1003,hIn,0);
	hExit=CreateWindow("button","退出", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*扁平样式*/,270,500,150,50,hWnd,(HMENU)1004,hIn,0);
	break;
case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//返回主菜单后销毁游戏窗口
		if(hGameWin!=NULL)
		{
			DestroyWindow(hGameWin);
			hGameWin=NULL;
		}
		Tableau.PaintMenuPicture(hdc,hIn);
		EndPaint(hWnd,&ps);
	break;
case WM_COMMAND:
	wmId    = LOWORD(wParam);
	switch(wmId)
	{
		//根据选中的游戏模式对Matrix对象初始化，并创建对应的游戏窗口
	case 1001:Matrix.SetGameMode(1);Player.SetGameMode(1);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,50,50,1017,635,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1002:Matrix.SetGameMode(2);Player.SetGameMode(2);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,100,0,1377,825,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1003:Matrix.SetGameMode(3);Player.SetGameMode(3);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,100,0,1377,825,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1004:SendMessage(hWnd,WM_DESTROY,0,0);break;	//退出游戏
	}
	break;
case WM_DESTROY:
	if(hGameWin!=NULL)
	{
		//销毁游戏窗口
		DestroyWindow(hGameWin);
	}
	PostQuitMessage(0);
	break;
	}


	return DefWindowProc(hWnd,message,wParam,lParam);
}


LRESULT CALLBACK GameWinCallBack(HWND hGameWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int wmId;
	switch(message)
	{
	case WM_PAINT:
		hdc=BeginPaint(hGameWnd,&ps);
		Matrix.PaintMatrix(hdc,hIn);	//需要重绘时画出矩阵当前状态
		EndPaint(hGameWnd,&ps);
		break;
	case WM_LBUTTONDOWN:
		//检测鼠标左键按下时是否在矩阵方格内
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		{
			//记下此时的鼠标坐标，如果释放时的坐标和按下的坐标在同一个格内，则点击有效，否则无效
			BUTTONDOWN_X= Player.m;
			BUTTONDOWN_Y=Player.n;
		}
		break;
	case WM_LBUTTONUP:
		//检测鼠标右键按下时是否在矩阵方格内
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		if(BUTTONDOWN_X==Player.m && BUTTONDOWN_Y==Player.n)	//检测释放和按下时的鼠标坐标是否在同一格
		{
			Matrix.TransToDisp(Player.n,Player.m);	//点击有效，标记被点击的方格为翻开，如果该方格周围无雷，则标记周围所有方格为翻开
			hdc=GetDC(hGameWnd);
			Matrix.PaintMatrix(hdc,hIn);			//画出矩阵
			if(Matrix.CheckMine(Player.n,Player.m))	//检测点击的是否为雷
			{
				MessageBox(hGameWnd,"输了","你输了！",MB_OK);
				Matrix.InitialGame();			//初始化游戏
				Matrix.PaintMatrix(hdc,hIn);	//画矩阵
			}else if(Matrix.Outcome())			//经检测满足获胜条件
			{
				MessageBox(hGameWnd,"赢了","你赢了！",MB_OK);
				Matrix.InitialGame();			//初始化游戏
				Matrix.PaintMatrix(hdc,hIn);	//画矩阵
			}
		}
		break;
	case WM_RBUTTONDOWN:
		//检测右键点击位置是否有效
		Player.CheckClick(LOWORD(lParam),HIWORD(lParam));
		//记下按下时的坐标
		BUTTONDOWN_X= Player.m;
		BUTTONDOWN_Y=Player.n;
		break;
	case WM_RBUTTONUP:
		//检测右键点击位置是否有效
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		{
			//检测右键按下时与释放时是否在同一方格
			if(BUTTONDOWN_X==Player.m && BUTTONDOWN_Y==Player.n)
			{
				
				Matrix.Flag(Player.n,Player.m);		//立旗子
				hdc=GetDC(hGameWnd);
				Matrix.PaintMatrix(hdc,hIn);		//重绘矩阵
				if(Matrix.Outcome())				//检测是否满足获胜条件
				{
					MessageBox(hGameWnd,"赢了","你赢了！",MB_OK);
					Matrix.InitialGame();			//初始化游戏
					Matrix.PaintMatrix(hdc,hIn);	//画矩阵
				}
				DeleteDC(hdc);
			}
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		switch(wmId)
		{
		case ID_Menu:SendMessage(hGameWnd,WM_DESTROY,0,0);break;	//返回主菜单
		case ID_Exit:SendMessage(hMain,WM_DESTROY,0,0);break;		//在游戏窗口退出游戏
		case ID_NewGame:Matrix.InitialGame();hdc=GetDC(hGameWnd);Matrix.PaintMatrix(hdc,hIn);break;//新游戏
		case ID_About: MessageBox(hGameWnd,"Santhink制作\nQQ：947596534","关于",MB_OK);break;	//制作者信息
		}
		break;
	case WM_DESTROY:
		//隐藏游戏窗口，显示主菜单窗口
		ShowWindow(hGameWnd,SW_HIDE);
		ShowWindow(hMain,SW_SHOW);
		break;

	}

	return DefWindowProc(hGameWnd,message,wParam,lParam);
}