#if !defined(AFX_ERADATETIME_H__EDE805ED_D248_4631_ADB7_1A760DE98D53__INCLUDED_)
#define AFX_ERADATETIME_H__EDE805ED_D248_4631_ADB7_1A760DE98D53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraDateTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEraDateTime window
class CEraDateTime : public CDateTimeCtrl {
// Construction
public:
	CEraDateTime();

// Attributes
public:
  BOOL  m_bFocus;

// Operations
public:
  void SetDate(COleDateTime& Date);
  COleDateTime GetDate();
  CString      GetDDMMYYYY();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraDateTime)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraDateTime();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraDateTime)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDatetimeChange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CEraDateTime& rControl, COleDateTime& Date);
void AFXAPI DDX_DateField(CDataExchange* pDX, int nIDC, CEraDateTime& rControl, COleDateTime& Date, CDaoRecordset* pRecordset);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERADATETIME_H__EDE805ED_D248_4631_ADB7_1A760DE98D53__INCLUDED_)
