#pragma once
class CPlayer
{
public:
	int n;	//存储通过点击坐标计算的矩阵逻辑坐标
	int m;	//存储通过点击坐标计算的矩阵逻辑坐标
	char game_mode;	//游戏模式
	int blocksize;	//方块大小
	int blockgap;	//方块间隙
public:
	CPlayer(void);
	~CPlayer(void);
	void SetGameMode(char GameMode);//设置游戏模式
	bool CheckClick(int x,int y);	//检测点击位置是否有效
};

