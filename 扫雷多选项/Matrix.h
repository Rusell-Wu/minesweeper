#pragma once
#include <Windows.h>
class CMatrix
{
private:
	char Matrix[16][30][2];	//矩阵
	char game_mode;	//1为9*9，2为16*16，3为16*30
	char mine_num;	//地雷数，9*9为10个，16*16为40个，16*30为99个
	int row;		//矩阵需要用到的行数
	int line;		//矩阵需要用到的列数
	int TrueFlag;	//标记正确的地雷数
	int initialpointx;	//第一个方块在窗口的相对位置X
	int initialpointy;	//第一个方块在窗口的相对位置Y
	int blocksize;		//方块大小
	int blockgap;		//方块间隙(blockgap-方块边长=间隙大小)
public:
	CMatrix();
	~CMatrix(void);
	void SetGameMode(char GameMode);	//设置游戏模式
	void PaintMatrix(HDC hdc,HINSTANCE h);//画出矩阵图
	void InitialMatrix();//初始化矩阵
	void RandMines();	//随机放置地雷	
	void CountPeripheralMines();//计算每个格子周围的地雷数
	void TransToDisp(int x,int y);		//翻开玩家点击的格子和无雷区
	void Flag(int x,int y);			//玩家标记
	bool Outcome();					//判断胜负
	bool CheckMine(int x,int y); //判断玩家点击的是否是雷
	void InitialGame();			//初始化游戏
};

