#pragma once
#include <Windows.h>
class CMatrix
{
private:
	char Matrix[16][30][2];	//����
	char game_mode;	//1Ϊ9*9��2Ϊ16*16��3Ϊ16*30
	char mine_num;	//��������9*9Ϊ10����16*16Ϊ40����16*30Ϊ99��
	int row;		//������Ҫ�õ�������
	int line;		//������Ҫ�õ�������
	int TrueFlag;	//�����ȷ�ĵ�����
	int initialpointx;	//��һ�������ڴ��ڵ����λ��X
	int initialpointy;	//��һ�������ڴ��ڵ����λ��Y
	int blocksize;		//�����С
	int blockgap;		//�����϶(blockgap-����߳�=��϶��С)
public:
	CMatrix();
	~CMatrix(void);
	void SetGameMode(char GameMode);	//������Ϸģʽ
	void PaintMatrix(HDC hdc,HINSTANCE h);//��������ͼ
	void InitialMatrix();//��ʼ������
	void RandMines();	//������õ���	
	void CountPeripheralMines();//����ÿ��������Χ�ĵ�����
	void TransToDisp(int x,int y);		//������ҵ���ĸ��Ӻ�������
	void Flag(int x,int y);			//��ұ��
	bool Outcome();					//�ж�ʤ��
	bool CheckMine(int x,int y); //�ж���ҵ�����Ƿ�����
	void InitialGame();			//��ʼ����Ϸ
};

