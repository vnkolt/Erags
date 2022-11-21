// TCToolBar.h: interface for the CTCToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_)
#define AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxext.h>

class CTCToolBar : public CToolBar  
{
public:
	CTCToolBar();
	virtual ~CTCToolBar();

	BOOL LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot,	UINT uDisabled);
	BOOL LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot,	UINT uDisabled, COLORREF colMask);
	
private:
	BOOL SetTCToolBar(UINT uToolBarType, UINT uToolBar, int nWidth, COLORREF colMask);
};

#endif // !defined(AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_)
