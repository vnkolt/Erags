// TCToolBar.cpp: implementation of the CTCToolBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCToolBar.h"
#include "..\NewMenu.h"
#include "..\ShellType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "TCImageList.h"

BOOL CreateBitmapFromAnotherBitmap(CBitmap& dstBitmap, int width, int height, CBitmap& srcBitmap, int srcX, int srcY) {

  HDC hDcDsk = GetWindowDC(0) ;

  CDC* pDcDsk = CDC::FromHandle(hDcDsk);
  CDC srcDC, dstDC;
  srcDC.CreateCompatibleDC(pDcDsk); 
  dstDC.CreateCompatibleDC(pDcDsk); 

  if ( dstBitmap.m_hObject )
    dstBitmap.DeleteObject();

  if ( false==dstBitmap.CreateCompatibleBitmap(pDcDsk,width,height) )
    return false;
  CBitmap* pOldBitmapSrc = srcDC.SelectObject(&srcBitmap);
  CBitmap* pOldBitmapDst = dstDC.SelectObject(&dstBitmap);

  dstDC.BitBlt(0,0,width,height, &srcDC, srcX, srcY, SRCCOPY);

  dstDC.SelectObject(pOldBitmapDst);
  srcDC.SelectObject(pOldBitmapSrc);
  // Release the desktopdc
  ReleaseDC(0,hDcDsk);

  #ifdef _DEBUG
  BITMAP bmp;
  dstBitmap.GetBitmap(&bmp);
  #endif

  return true;
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CTCToolBar
IMPLEMENT_DYNAMIC(CTCToolBar, CToolBar)
BEGIN_MESSAGE_MAP(CTCToolBar, CToolBar)
	//{{AFX_MSG_MAP(CTCToolBar)
  ON_WM_ERASEBKGND()
  ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

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

BOOL CTCToolBar::SetTCToolBar(UINT uToolBarType, CBitmap& bitmap, int nWidth, COLORREF colMask) {
	CTCImageList cImageList;
	cImageList.CreateTC(bitmap,nWidth,colMask);

	SendMessage(uToolBarType, 0, (LPARAM)cImageList.m_hImageList);
	cImageList.Detach(); 
  return TRUE;
}

BOOL CTCToolBar::OnEraseBkgnd(CDC* pDC) {
	// TODO: Add your message handler code here and/or call default
  if ( g_Shell >= WinXP ) { // to prevent WinXP toolbar bug
  	CRect r;
    GetClientRect(&r);
    GradientEraseBkgnd(pDC, r);
    return true;
  }
  return CToolBar::OnEraseBkgnd(pDC);
}
void CTCToolBar::OnPaint() {
  CToolBar::OnPaint();
}
