#pragma once
class CPlayer
{
public:
	int n;	//�洢ͨ������������ľ����߼�����
	int m;	//�洢ͨ������������ľ����߼�����
	char game_mode;	//��Ϸģʽ
	int blocksize;	//�����С
	int blockgap;	//�����϶
public:
	CPlayer(void);
	~CPlayer(void);
	void SetGameMode(char GameMode);//������Ϸģʽ
	bool CheckClick(int x,int y);	//�����λ���Ƿ���Ч
};

