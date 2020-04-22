#include <Windows.h>
#include "resource.h"
#include "Matrix.h"
#include "Player.h"
#include "Tableau.h"
//ȫ�ֱ���
HWND hMain;			//���˵����ھ��
HWND hGameWin=NULL;	//��Ϸ���ھ��
HINSTANCE hIn;		//ʵ�����
CTableau Tableau;	//�����˵���������
CMatrix Matrix;		//���׾������
CPlayer Player;		//��ҿ��ƶ���
int BUTTONDOWN_X=0,BUTTONDOWN_Y=0;	//�������ʱ������
//��������
LRESULT CALLBACK MainWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);	//���˵����ڻص�����
LRESULT CALLBACK GameWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);	//��Ϸ���ڻص�����

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
	//�������˵�����
	hMain=MainhWnd=CreateWindow("MainWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,350,100,704,600,NULL,NULL,hInstance,NULL);
	//��ʾ���˵�����
	ShowWindow(MainhWnd,SW_SHOW);
	//��Ϣѭ��
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK MainWinCallBack(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int wmId;		//����Ŀؼ�id
	PAINTSTRUCT ps;
	static HWND hNightBtn;	//9*9����ť
	static HWND hSixteenBtn;	//16*16����ť
	static HWND hthirtyBtn;		//16*32����ť
	static HWND hExit;			//�˳���ť
	switch(message)
	{
case WM_CREATE:
	hNightBtn=CreateWindow("button","9��9", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,270,350,150,50,hWnd,(HMENU)1001,hIn,0);
	hSixteenBtn=CreateWindow("button","16��16", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,270,400,150,50,hWnd,(HMENU)1002,hIn,0);
	hthirtyBtn=CreateWindow("button","16��30", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,270,450,150,50,hWnd,(HMENU)1003,hIn,0);
	hExit=CreateWindow("button","�˳�", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT/*��ƽ��ʽ*/,270,500,150,50,hWnd,(HMENU)1004,hIn,0);
	break;
case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		//�������˵���������Ϸ����
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
		//����ѡ�е���Ϸģʽ��Matrix�����ʼ������������Ӧ����Ϸ����
	case 1001:Matrix.SetGameMode(1);Player.SetGameMode(1);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,50,50,1017,635,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1002:Matrix.SetGameMode(2);Player.SetGameMode(2);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,100,0,1377,825,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1003:Matrix.SetGameMode(3);Player.SetGameMode(3);hGameWin=CreateWindow("GameWindow","Minesweeper",WS_MINIMIZEBOX|WS_SYSMENU,100,0,1377,825,NULL,LoadMenu(hIn,MAKEINTRESOURCE(IDR_MENU1)),hIn,NULL);ShowWindow(hWnd,SW_HIDE);ShowWindow(hGameWin,SW_SHOW);break;
	case 1004:SendMessage(hWnd,WM_DESTROY,0,0);break;	//�˳���Ϸ
	}
	break;
case WM_DESTROY:
	if(hGameWin!=NULL)
	{
		//������Ϸ����
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
		Matrix.PaintMatrix(hdc,hIn);	//��Ҫ�ػ�ʱ��������ǰ״̬
		EndPaint(hGameWnd,&ps);
		break;
	case WM_LBUTTONDOWN:
		//�������������ʱ�Ƿ��ھ��󷽸���
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		{
			//���´�ʱ��������꣬����ͷ�ʱ������Ͱ��µ�������ͬһ�����ڣ�������Ч��������Ч
			BUTTONDOWN_X= Player.m;
			BUTTONDOWN_Y=Player.n;
		}
		break;
	case WM_LBUTTONUP:
		//�������Ҽ�����ʱ�Ƿ��ھ��󷽸���
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		if(BUTTONDOWN_X==Player.m && BUTTONDOWN_Y==Player.n)	//����ͷźͰ���ʱ����������Ƿ���ͬһ��
		{
			Matrix.TransToDisp(Player.n,Player.m);	//�����Ч����Ǳ�����ķ���Ϊ����������÷�����Χ���ף�������Χ���з���Ϊ����
			hdc=GetDC(hGameWnd);
			Matrix.PaintMatrix(hdc,hIn);			//��������
			if(Matrix.CheckMine(Player.n,Player.m))	//��������Ƿ�Ϊ��
			{
				MessageBox(hGameWnd,"����","�����ˣ�",MB_OK);
				Matrix.InitialGame();			//��ʼ����Ϸ
				Matrix.PaintMatrix(hdc,hIn);	//������
			}else if(Matrix.Outcome())			//����������ʤ����
			{
				MessageBox(hGameWnd,"Ӯ��","��Ӯ�ˣ�",MB_OK);
				Matrix.InitialGame();			//��ʼ����Ϸ
				Matrix.PaintMatrix(hdc,hIn);	//������
			}
		}
		break;
	case WM_RBUTTONDOWN:
		//����Ҽ����λ���Ƿ���Ч
		Player.CheckClick(LOWORD(lParam),HIWORD(lParam));
		//���°���ʱ������
		BUTTONDOWN_X= Player.m;
		BUTTONDOWN_Y=Player.n;
		break;
	case WM_RBUTTONUP:
		//����Ҽ����λ���Ƿ���Ч
		if(Player.CheckClick(LOWORD(lParam),HIWORD(lParam)))
		{
			//����Ҽ�����ʱ���ͷ�ʱ�Ƿ���ͬһ����
			if(BUTTONDOWN_X==Player.m && BUTTONDOWN_Y==Player.n)
			{
				
				Matrix.Flag(Player.n,Player.m);		//������
				hdc=GetDC(hGameWnd);
				Matrix.PaintMatrix(hdc,hIn);		//�ػ����
				if(Matrix.Outcome())				//����Ƿ������ʤ����
				{
					MessageBox(hGameWnd,"Ӯ��","��Ӯ�ˣ�",MB_OK);
					Matrix.InitialGame();			//��ʼ����Ϸ
					Matrix.PaintMatrix(hdc,hIn);	//������
				}
				DeleteDC(hdc);
			}
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		switch(wmId)
		{
		case ID_Menu:SendMessage(hGameWnd,WM_DESTROY,0,0);break;	//�������˵�
		case ID_Exit:SendMessage(hMain,WM_DESTROY,0,0);break;		//����Ϸ�����˳���Ϸ
		case ID_NewGame:Matrix.InitialGame();hdc=GetDC(hGameWnd);Matrix.PaintMatrix(hdc,hIn);break;//����Ϸ
		case ID_About: MessageBox(hGameWnd,"Santhink����\nQQ��947596534","����",MB_OK);break;	//��������Ϣ
		}
		break;
	case WM_DESTROY:
		//������Ϸ���ڣ���ʾ���˵�����
		ShowWindow(hGameWnd,SW_HIDE);
		ShowWindow(hMain,SW_SHOW);
		break;

	}

	return DefWindowProc(hGameWnd,message,wParam,lParam);
}