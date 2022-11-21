// TCImageList.h: interface for the CTCImageList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCIMAGELIST_H__177F3B4E_94AC_42BB_900A_BFD6CFE60DBC__INCLUDED_)
#define AFX_TCIMAGELIST_H__177F3B4E_94AC_42BB_900A_BFD6CFE60DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxcmn.h>

class CTCImageList : public CImageList  
{
public:
	CTCImageList();
	virtual ~CTCImageList();

	BOOL CreateTC(UINT nID);
  BOOL CreateTC(CBitmap& bitmap);

	BOOL CreateTC(UINT nID, COLORREF colMask);
	BOOL CreateTC(CBitmap& bitmap, COLORREF colMask);

	BOOL CreateTC(UINT nID, int cx);
	BOOL CreateTC(CBitmap& bitmap, int cx);

	BOOL CreateTC(UINT nID, int cx, COLORREF colMask);
	BOOL CreateTC(CBitmap& bitmap, int cx, COLORREF colMask);

	BOOL CreateTC(UINT nID, int cx, int cy);
	BOOL CreateTC(CBitmap& bitmap, int cx, int cy);

	BOOL CreateTC(UINT nID, int cx, int cy, COLORREF colMask);
	BOOL CreateTC(CBitmap& bitmap, int cx, int cy, COLORREF colMask);
};

#endif // !defined(AFX_TCIMAGELIST_H__177F3B4E_94AC_42BB_900A_BFD6CFE60DBC__INCLUDED_)
