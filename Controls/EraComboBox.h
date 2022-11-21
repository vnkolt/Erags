#if !defined(AFX_ERACOMBOBOX_H__C0639D49_D57D_4A3A_BFED_578C211595AD__INCLUDED_)
#define AFX_ERACOMBOBOX_H__C0639D49_D57D_4A3A_BFED_578C211595AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraComboBox.h : header file
//
#include "EraControls.h"
#include "EraEdit.h"

class CSexTableCache;
class CTypeAheadCombo;

#pragma warning(disable : 4995)

class CDaoRecordset;

/////////////////////////////////////////////////////////////////////////////
// CComboEdit window

class CComboEdit : public CEraEdit {
  DECLARE_DYNAMIC(CComboEdit)
// Construction
public:
	CComboEdit();

// Attributes
protected:
	int					m_nStartAfter;
	bool				m_bHighlighted;
	bool				m_bBackspace;
	bool				m_bDelete;
	CString			m_SearchString;
	WORD				m_nPos;

// Operations
protected:
	void DoFind(UINT nChar);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo window

class CTypeAheadCombo : public CComboBox {
  DECLARE_DYNAMIC(CTypeAheadCombo)
// Construction
public:
	CTypeAheadCombo();

// Attributes
public:

	CComboEdit	m_xEdit;

// Operations
public:
  CString GetCurText();
  int     SetCurText(const CString& sText);
  DWORD   GetCurData();
  BOOL    IsEmpty();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTypeAheadCombo)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTypeAheadCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTypeAheadCombo)
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CEraComboBox window

class CEraComboBox : public CTypeAheadCombo {
  DECLARE_DYNAMIC(CEraComboBox)
// Construction
public:
	CEraComboBox();

// Attributes
protected:
  CEraComboBoxProperties m_Properties;
  bool          m_bFocus;
  CString       m_sDefValue;
public:
  bool          m_bFilled;
  CEraComboBox* m_pFatherCmb;
  CEraComboBox* m_pGrandFaCmd;

// Operations
public:
  LONG     SetStyle(LONG lStyle);
  void     SetDefault(LPCTSTR szDefValue);
  CString  GetDefault() { return m_sDefValue; }
  //void  ChangeColor();

  BOOL     IsCurDefault();
  void     UpdateByDefault();
  int      FindData(long lData);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraComboBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraComboBox)
	afx_msg void OnSetfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CEraNameComboBox : public CEraComboBox {
  DECLARE_DYNAMIC(CEraNameComboBox)
public:
  CEraNameComboBox();

protected:
  int   m_MaleFemale;
public:
  BOOL  IsMale();
  BOOL  IsFemale();
  void  SetMale();
  void  SetFemale();
  void  SetAltText(LPCTSTR szText, COLORREF clrAltColor=0);
	// Generated message map functions
protected:
	//{{AFX_MSG(CEraNameComboBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

void AFXAPI DDX_CBData(CDataExchange* pDX, int nIDC, long& ldata);
void AFXAPI DDX_FieldCBData(CDataExchange* pDX, int nIDC, long& ldata, CDaoRecordset* pRecordset);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERACOMBOBOX_H__C0639D49_D57D_4A3A_BFED_578C211595AD__INCLUDED_)
