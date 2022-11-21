#if !defined(AFX_DBGRID_H__0B6C83C3_E053_429B_8DB4_765D20DBDBE7__INCLUDED_)
#define AFX_DBGRID_H__0B6C83C3_E053_429B_8DB4_765D20DBDBE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBGrid.h : header file
//

#include "..\Controls\GridCtrl\GridCtrl.h"
#include "..\Controls\GridCtrl\InPlaceEdit.h"

#pragma warning(disable : 4995)

/////////////////////////////////////////////////////////////////////////////
// CDBGrid window

class CDBGrid : public CGridCtrl {
  DECLARE_DYNCREATE(CDBGrid)
// Construction
public:
	CDBGrid();

// Attributes
public:
  CDaoDatabase*   m_pDB;
  CString         m_TableName;
  CString         m_InsertSQL;

  CWordArray      m_FieldTypes;
  CStringArray    m_FieldNames;

  
  short           m_LastNumber;
  COleDateTime    m_LastDateReg;

// Operations
public:
  virtual bool AddRow(int newRow);
  void  SetCellFormats(int row, CDaoRecordset* pRS=NULL);
  virtual bool Load();
  bool  Insert(int newRow);
  bool  Update(int row, int col, const CString& s);
  bool  Delete(int row);

  short         GetNextNumber();
  COleDateTime  GetNextDateReg();

  void          SelectRow(int row);

// editing cells
public:
    virtual void  OnEditCell(int nRow, int nCol, CPoint point, UINT nChar);
    virtual void  OnDelete();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBGrid)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDBGrid();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDBGrid)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
  afx_msg void OnEndInPlaceEdit(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

int CALLBACK pfnDBGridCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBGRID_H__0B6C83C3_E053_429B_8DB4_765D20DBDBE7__INCLUDED_)
