#include "Matrix.h"
#include <time.h>
#include "OwnFun.h"
#include "resource.h"

CMatrix::CMatrix()
{
	initialpointx=275;
	initialpointy=100;
	//����ߴ�
	blocksize=40;
	blockgap=10;
	//��Ϸģʽ
	game_mode=1;
	//��������
	row=9;
	line=9;
	//����
	mine_num=10;
	//�����ȷ��������
	TrueFlag=0;
	//��ʼ������
	InitialMatrix();
	//���������
	RandMines();
	//����ÿ��������Χ����
	CountPeripheralMines();
}
CMatrix::~CMatrix(void)
{

}


void CMatrix::PaintMatrix(HDC hdc,HINSTANCE h)//��������ͼ
{
	int i=0,j=0;
	HBITMAP hbitmap;
	HDC BitMapDc;
	switch(game_mode)
	{
		//���ݲ�ͬ��Ϸģʽѡ��ͬ����Ϸ����
	case 1:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround1));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	case 2:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround2));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	case 3:hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_BackGround2));BitMapDc=CreateCompatibleDC(hdc);SelectObject(BitMapDc,hbitmap);break;
	}
	//IDB_BITMAP1-IDB_BITMAP9Ϊ0���׵�8���׵ķ��飬IDB_MineΪ���ף�IDB_BlockΪδ�������飬IDB_FlagΪ��ǵ�����IDB_unknownΪδ֪������
	for(i=0;i<row;i++)
	{
		for(j=0;j<line;j++)
		{
			//����ͬ״̬�ķ���
			if(Matrix[i][j][0]==0)
			{
				//LoadTransparentBM���Զ��庯����������OwnFun.hͷ�ļ���
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
	//���ݲ�ͬ��Ϸģʽ������
	switch(game_mode)
	{
	case 1:BitBlt(hdc,0,0,1017,635,BitMapDc,0,0,SRCCOPY);break;
	case 2:BitBlt(hdc,0,0,1525,913,BitMapDc,0,0,SRCCOPY);break;
	case 3:BitBlt(hdc,0,0,1525,913,BitMapDc,0,0,SRCCOPY);break;
	}
	DeleteDC(BitMapDc);
	DeleteObject(hbitmap);
}

void CMatrix::InitialMatrix()//��ʼ������
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

void CMatrix::RandMines()	//������õ���	9�������
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

void CMatrix::CountPeripheralMines()//����ÿ��������Χ�ĵ�����
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

void CMatrix::TransToDisp(int x,int y)		//������ҵ���ĸ��Ӻ�������
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
				TransToDisp(i,j);	//�����Χû�е��ף���ݹ���ʾ��Χ������
			}
		}
	}else if(Matrix[x][y][0]==0)
	{
		Matrix[x][y][0]=1;
	}
}

void CMatrix::Flag(int x,int y)			//��ұ��
{
	switch(Matrix[x][y][0])
	{
	case 0:Matrix[x][y][0]=2;if(Matrix[x][y][1]==9) TrueFlag++;break;
	case 2:Matrix[x][y][0]=3;if(Matrix[x][y][1]==9) TrueFlag--;break;
	case 3:Matrix[x][y][0]=0;break;
	}

}

bool CMatrix::Outcome()					//�ж�ʤ��
{
	switch(game_mode)
	{
	case 1:if(TrueFlag==10) return true;break;
	case 2:if(TrueFlag==40) return true;break;
	case 3:if(TrueFlag==99) return true;break;
	}
	return false;
}

void CMatrix::SetGameMode(char GameMode)	//������Ϸģʽ
{
	switch(GameMode)
	{
	case 1:game_mode=1;blocksize=40;blockgap=50;initialpointx=275;initialpointy=100;row=9;line=9;TrueFlag=0;mine_num=10;InitialMatrix();RandMines();CountPeripheralMines();break;
	case 2:game_mode=2;blocksize=30;blockgap=40;initialpointx=360;initialpointy=110;row=16;line=16;TrueFlag=0;mine_num=40;InitialMatrix();RandMines();CountPeripheralMines();break;
	case 3:game_mode=3;blocksize=30;blockgap=40;initialpointx=100;initialpointy=110;row=16;line=30;TrueFlag=0;mine_num=99;InitialMatrix();RandMines();CountPeripheralMines();break;
	}
}

void  CMatrix::InitialGame()		//��ʼ����Ϸ
{
	InitialMatrix();
	RandMines();
	CountPeripheralMines();
	TrueFlag=0;
}


bool CMatrix::CheckMine(int x,int y)	//���ĳ�����Ƿ�Ϊ��
{
	return (Matrix[x][y][1]==9);
}
	
	