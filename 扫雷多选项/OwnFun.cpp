#pragma comment(lib,"msimg32.lib")
#include "OwnFun.h"
void LoadTransparentBM(HINSTANCE h,HDC hdc,int ID,int  nXOriginDest,int  nYOriginDest,int nWidthDest,int  hHeightDest,int nXOriginSrc,int nYOriginSrc, int nWidthSrc,int nHeightSrc, UINT crTransparent )
{
	HBITMAP hbitmap;
	HDC BitMapDc;
	hbitmap =LoadBitmap(h,MAKEINTRESOURCE(ID));
	BitMapDc=CreateCompatibleDC(hdc);
	SelectObject(BitMapDc,hbitmap);
	//»­±³¾°Í¸Ã÷Î»Í¼
	TransparentBlt(hdc,nXOriginDest,nYOriginDest,nWidthDest,hHeightDest,BitMapDc,nXOriginSrc,nYOriginSrc,nWidthSrc,nHeightSrc,crTransparent);
	DeleteDC(BitMapDc);
	DeleteObject(hbitmap);
}