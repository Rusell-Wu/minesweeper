#pragma once
#include <Windows.h>
class CTableau
{
private:
	char game_mode;
public:
	CTableau(void);
	~CTableau(void);
	void PaintMenuPicture(HDC hdc,HINSTANCE h);//���˵����汳��ͼ
};

