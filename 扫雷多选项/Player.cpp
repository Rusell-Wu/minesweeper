#include "Player.h"


CPlayer::CPlayer(void)
{
	n=0;
	m=0;
	game_mode=1;
	blocksize=40;
	blockgap=50;
}


CPlayer::~CPlayer(void)
{
}
bool CPlayer::CheckClick(int x,int y)
{
	int a=275,b=100;
	switch(game_mode)
	{
	case 1:a=275;b=100;break;
	case 2:a=360;b=110;break;
	case 3:a=100;b=110;break;
	default:return false;
	}
	int i=0;
	while(1)
	{
		if((a+blocksize)<x)
		{
			a+=blockgap;
		}else if(a>x)	return false;	//�����겻�ڷ�����˵�������Ч
		else break;
		i++;
	}
	CPlayer::m=i;		//�����Чʱת��Ϊ��ǰ�����ھ����λ��
	i=0;
	while(1)
	{
		if((b+blocksize)<y)
		{
			b+=blockgap;
		}else if(b>y)	return false;	//�����겻�ڷ�����˵�������Ч
		else break;
		i++;
	}
	CPlayer::n=i;		//�����Чʱת��Ϊ��ǰ�����ھ����λ��
	return true;
}

//������Ϸģʽ
void CPlayer::SetGameMode(char GameMode)
{
	game_mode=GameMode;
	switch(game_mode)
	{
	case 1:	blocksize=40;blockgap=50;break;
	case 2:blocksize=30;blockgap=40;break;
	case 3:blocksize=30;blockgap=40;break;
	}
}

