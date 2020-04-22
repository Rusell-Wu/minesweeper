#include "Matrix.h"
#include <time.h>
#include "OwnFun.h"
#include "resource.h"

CMatrix::CMatrix()
{
	initialpointx=275;
	initialpointy=100;
	//方块尺寸
	blocksize=40;
	blockgap=10;
	//游戏模式
	game_mode=1;
	//列与行数
	row=9;
	line=9;
	//雷数
	mine_num=10;
	//标记正确的旗子数
	TrueFlag=0;
	//初始化矩阵
	InitialMatrix();
	//生成随机雷
	RandMines();
	//计算每个方格周围雷数
	CountPeripheralMines();
}
CMatrix::~CMatrix(void)
{

}


void CMatrix::PaintMatrix(HDC hdc,HINSTANCE h)//画出矩阵图
{
	int i=0,j=0;
	HBITMAP hbitmap;
	HDC BitMapDc;
	switch(game_mode)
	{
		//根据不同游戏模式选择不同的游戏背景
	case 1:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround1));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	case 2:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround2));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	case 3:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround2));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	}
	//IDB_BITMAP1-IDB_BITMAP9为0个雷到8个雷的方块，IDB_Mine为地雷，IDB_Block为未翻开方块，IDB_Flag为标记的区域，IDB_unknown为未知的区域
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			//画不同状态的方块
			if(Matrix[i][j][0]==0)
			{
				//LoadTransparentBM是自定义函数，包含在OwnFun.h头文件中
				LoadTransparentBM(h,BitMapDc,IDB_Block,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,639,639,RGB(255,255,255));
			}else if(Matrix[i][j][0]==2)
			{
				LoadTransparentBM(h,BitMapDc,IDB_Flag,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,639,639,RGB(255,255,255));
			}else if(Matrix[i][j][0]==3)
			{
				LoadTransparentBM(h,BitMapDc,IDB_unknown,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,639,639,RGB(255,255,255));
			}else
			{
				switch(Matrix[i][j][1])
				{
					case 0:LoadTransparentBM(h,BitMapDc,IDB_BITMAP1,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 1:LoadTransparentBM(h,BitMapDc,IDB_BITMAP2,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 2:LoadTransparentBM(h,BitMapDc,IDB_BITMAP3,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 3:LoadTransparentBM(h,BitMapDc,IDB_BITMAP4,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 4:LoadTransparentBM(h,BitMapDc,IDB_BITMAP5,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 5:LoadTransparentBM(h,BitMapDc,IDB_BITMAP6,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 6:LoadTransparentBM(h,BitMapDc,IDB_BITMAP7,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 7:LoadTransparentBM(h,BitMapDc,IDB_BITMAP8,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 8:LoadTransparentBM(h,BitMapDc,IDB_BITMAP9,initialpointx+j*blockgap,initialpointy+i*blockgap,blocksize,blocksize,0,0,657,657,RGB(255,255,255));break;
					case 9:LoadTransparentBM(h,BitMapDc,IDB_Mine,initialpointx+j*blockgap,initialpointy+i*(blockgap-1),blocksize,blocksize,0,0,180,180,RGB(255,255,255));break;
				}
			}

		}
	}
	//根据不同游戏模式贴背景
	switch(game_mode)
	{
	case 1:BitBlt(hdc,0,0,1017,635,BitMapDc,0,0,SRCCOPY);break;
	case 2:BitBlt(hdc,0,0,1525,913,BitMapDc,0,0,SRCCOPY);break;
	case 3:BitBlt(hdc,0,0,1525,913,BitMapDc,0,0,SRCCOPY);break;
	}
	DeleteDC(BitMapDc);
	DeleteObject(hbitmap);
}

void CMatrix::InitialMatrix()//初始化矩阵
{
	int i,j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			Matrix[i][j][0]=0;
			Matrix[i][j][1]=0;
		}
	}
}

void CMatrix::RandMines()	//随机放置地雷	9代表地雷
{
	int i;
	int rand_i,rand_j;
	srand((unsigned int)time(NULL));
	for(i=0;i<mine_num;)
	{
		rand_i=rand()%row;
		rand_j=rand()%line;
		if(Matrix[rand_i][rand_j][1]==0)
		{
			Matrix[rand_i][rand_j][1]=9;
			i++;
		}
	}
}

void CMatrix::CountPeripheralMines()//计算每个格子周围的地雷数
{
	int i,j,x,y;
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			if(Matrix[i][j][1]==9)
			{
				for(x=i-1;x<=i+1;x++)
				{
					for(y=j-1;y<=j+1;y++)
					{
						if(x>=0 && y>=0 && x<row && y<line &&Matrix[x][y][1]!=9 )
						{
							Matrix[x][y][1]++;
						}
					}
				}
			}
		}
	}
}

void CMatrix::TransToDisp(int x,int y)		//翻开玩家点击的格子和无雷区
{
	int i=0,j=0;
	if(Matrix[x][y][1]==0)
	{
		Matrix[x][y][0]=1;
		for(i=x-1;i<=x+1;i++)
		{
			for(j=y-1;j<=y+1;j++)
			{
				if(i>=0 && j>=0 && i<row && j<line &&Matrix[i][j][0]!=1)
				TransToDisp(i,j);	//如果周围没有地雷，则递归显示周围的区域
			}
		}
	}else if(Matrix[x][y][0]==0)
	{
		Matrix[x][y][0]=1;
	}
}

void CMatrix::Flag(int x,int y)			//玩家标记
{
	switch(Matrix[x][y][0])
	{
	case 0:Matrix[x][y][0]=2;if(Matrix[x][y][1]==9) TrueFlag++;break;
	case 2:Matrix[x][y][0]=3;if(Matrix[x][y][1]==9) TrueFlag--;break;
	case 3:Matrix[x][y][0]=0;break;
	}

}

bool CMatrix::Outcome()					//判断胜负
{
	switch(game_mode)
	{
	case 1:if(TrueFlag==10) return true;break;
	case 2:if(TrueFlag==40) return true;break;
	case 3:if(TrueFlag==99) return true;break;
	}
	return false;
}

void CMatrix::SetGameMode(char GameMode)	//设置游戏模式
{
	switch(GameMode)
	{
	case 1:game_mode=1;blocksize=40;blockgap=50;initialpointx=275;initialpointy=100;row=9;line=9;TrueFlag=0;mine_num=10;InitialMatrix();RandMines();CountPeripheralMines();break;
	case 2:game_mode=2;blocksize=30;blockgap=40;initialpointx=360;initialpointy=110;row=16;line=16;TrueFlag=0;mine_num=40;InitialMatrix();RandMines();CountPeripheralMines();break;
	case 3:game_mode=3;blocksize=30;blockgap=40;initialpointx=100;initialpointy=110;row=16;line=30;TrueFlag=0;mine_num=99;InitialMatrix();RandMines();CountPeripheralMines();break;
	}
}

void  CMatrix::InitialGame()		//初始化游戏
{
	InitialMatrix();
	RandMines();
	CountPeripheralMines();
	TrueFlag=0;
}


bool CMatrix::CheckMine(int x,int y)	//检测某方格是否为雷
{
	return (Matrix[x][y][1]==9);
}
	
	