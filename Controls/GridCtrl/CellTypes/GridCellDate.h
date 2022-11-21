// GridCellDate.h: interface for the CGridCellDate class.
//
// Provides the implementation for a datetime picker cell type of the
// grid control.
//
// For use with CGridCtrl v2.22+
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATECELL_H__A0B7DA0A_0AFE_4D28_A00E_846C96D7507A__INCLUDED_)
#define AFX_DATECELL_H__A0B7DA0A_0AFE_4D28_A00E_846C96D7507A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../GridCell.h"
#include "afxdtctl.h"	// for CDateTimeCtrl

class CGridCellDate : public CGridCell  
{
  friend class CGridCtrl;
  DECLARE_DYNCREATE(CGridCellDate)

  COleDateTime  m_odt;
  DWORD         m_dwStyle;

public:
	CGridCellDate();
	CGridCellDate(DWORD dwStyle);
	virtual ~CGridCellDate();

  // editing cells
public:
	void Init(DWORD dwStyle);
  virtual BOOL  Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
  virtual CWnd* GetEditWnd() const;
  virtual void  EndEdit();


  COleDateTime GetDate() {return m_odt;}
};

#endif // !defined(AFX_DATECELL_H__A0B7DA0A_0AFE_4D28_A00E_846C96D7507A__INCLUDED_)
