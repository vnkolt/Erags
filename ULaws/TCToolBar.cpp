// TCToolBar.cpp: implementation of the CTCToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCToolBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "TCImageList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCToolBar::CTCToolBar()
{

}

CTCToolBar::~CTCToolBar()
{

}

BOOL CTCToolBar::LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot, UINT uDisabled)
{
	return LoadTCToolBar(nWidth, uNormal, uHot, uDisabled, RGB(255,255,255));
}

BOOL CTCToolBar::LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot, UINT uDisabled, COLORREF colMask)
{
	if (!SetTCToolBar(TB_SETIMAGELIST, uNormal, nWidth, colMask))
		return FALSE;
	
	if (!SetTCToolBar(TB_SETHOTIMAGELIST, uHot, nWidth, colMask))
		return FALSE;
	
	if (uDisabled) 
		if (!SetTCToolBar(TB_SETDISABLEDIMAGELIST, uDisabled, nWidth, colMask))
			return FALSE;
		
		return TRUE;
}


BOOL CTCToolBar::SetTCToolBar(UINT uToolBarType, UINT uToolBar, int nWidth, COLORREF colMask)
{
	CTCImageList cImageList;
	cImageList.CreateTC(uToolBar,nWidth,colMask);

	SendMessage(uToolBarType, 0, (LPARAM)cImageList.m_hImageList);
	cImageList.Detach(); 
	
	return TRUE;
}

