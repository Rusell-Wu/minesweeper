#include "Tableau.h"
#include "resource.h"

CTableau::CTableau(void)
{

}


CTableau::~CTableau(void)
{
}


void CTableau::PaintMenuPicture(HDC hdc,HINSTANCE h)//ª≠≤Àµ•ΩÁ√Ê±≥æ∞Õº
{
	HBITMAP hbitmap;
	HDC BitMapDc;
	hbitmap=LoadBitmap(h,MAKEINTRESOURCE(IDB_minesweeper));
	BitMapDc=CreateCompatibleDC(hdc);
	SelectObject(BitMapDc,hbitmap);
	BitBlt(hdc,0,0,704,600,BitMapDc,0,0,SRCCOPY);
	DeleteDC(BitMapDc);
	DeleteObject(hbitmap);
}

