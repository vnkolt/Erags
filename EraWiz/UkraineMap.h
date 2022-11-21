#if !defined(AFX_UKRAINEMAP_H__8DB852AC_6E2E_4F60_B62D_78980B51F5AA__INCLUDED_)
#define AFX_UKRAINEMAP_H__8DB852AC_6E2E_4F60_B62D_78980B51F5AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UkraineMap.h : header file
//

#include "..\Controls\CPPTooltip\PPTooltip.h"

/////////////////////////////////////////////////////////////////////////////
// CUkraineMap window
class CUkraineMap : public CStatic {
// Construction
public:
	CUkraineMap();

// Attributes
private:
  HCURSOR     m_hHandCursor;
  HCURSOR     m_hTreeCursor;
  BOOL        m_fRegionDefined;
  BOOL        m_fCityDefined;
  BOOL        m_fAll;
  int         m_nRegion;
  CPPToolTip  m_tooltip;

  CBitmap       m_Bitmap;
  CPalette      m_Palette;
  BITMAP        m_bmp;
  BYTE*         m_bmpBuffer;
  PALETTEENTRY  m_palEntries[256];

// Operations
private:
  COLORREF  getPixel(int x, int y);
  COLORREF  GetRegionOfCity(CDC* pDC, CPoint p);
  void      FindRegion(CPoint& p);

 

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUkraineMap)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUkraineMap();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUkraineMap)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
  afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UKRAINEMAP_H__8DB852AC_6E2E_4F60_B62D_78980B51F5AA__INCLUDED_)
