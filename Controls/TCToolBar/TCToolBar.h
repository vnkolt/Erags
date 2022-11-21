// TCToolBar.h: interface for the CTCToolBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_)
#define AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxext.h>

class CTCToolBar : public CToolBar {
	DECLARE_DYNAMIC(CTCToolBar)
public:
	CTCToolBar();
	virtual ~CTCToolBar();

	BOOL LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot,	UINT uDisabled);
	BOOL LoadTCToolBar(int nWidth, UINT uNormal, UINT uHot,	UINT uDisabled, COLORREF colMask);
	
	BOOL SetTCToolBar(UINT uToolBarType, CBitmap& bitmap, int nWidth, COLORREF colMask);
private:
	BOOL SetTCToolBar(UINT uToolBarType, UINT uToolBar, int nWidth, COLORREF colMask);

// Generated message map functions
protected:
	//{{AFX_MSG(CTCToolBar)
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

BOOL CreateBitmapFromAnotherBitmap(CBitmap& dstBitmap, int width, int height, CBitmap& srcBitmap, int srcX, int srcY);


#endif // !defined(AFX_TCTOOLBAR_H__F9325075_3513_4F62_B485_C7B9333C5F8E__INCLUDED_)
