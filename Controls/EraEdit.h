#if !defined(AFX_ERAEDIT_H__D676F857_FC45_4379_8F1B_1FC9944793B2__INCLUDED_)
#define AFX_ERAEDIT_H__D676F857_FC45_4379_8F1B_1FC9944793B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraEdit.h : header file
//

#pragma warning(disable : 4995)

/////////////////////////////////////////////////////////////////////////////
// CEraEdit window
class CEraEdit : public CEdit {
  DECLARE_DYNAMIC(CEraEdit)

// Construction
public:
	CEraEdit();

// Attributes
public:
  BOOL m_fReplaceQuote;
  BOOL m_bFirstUC; // First letter in upper case
  BOOL m_fSelectAll;
protected:
  CEraTextBoxProperties m_Properties;

  bool      m_bFocus, m_bValid;
  CString   m_strFormat;
  CString   m_szAltText;
  COLORREF  m_AltColor;
// Operations
public:
  void    SetFormat(LPCTSTR szFormat);
  CString GetText();
  bool    IsEmpty();
protected:
  void  OnCharDriver(WPARAM& wParam, LPARAM& lParam);
  void  ReplaceSelection();
  void  ClearSelection();
  UINT  MakeFirstUC(UINT nChar);

  virtual void  SetSelection();

// Attributes
public:
  virtual BOOL OverwriteMode();
  void SetAltText(LPCTSTR szText, COLORREF clrAltColor=0) {
        m_szAltText = szText;
        m_AltColor = clrAltColor;
      }
protected:
  POINT GetCaretXY(int& x, int& y);
protected:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraEdit)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraEdit)
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnPaint();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
  //afx_msg LRESULT OnPaint(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

class CEraMaskEdit : public CEraEdit {
  DECLARE_DYNAMIC(CEraMaskEdit)

// Constructors
public:
  CEraMaskEdit();

// Attributes
public:
  virtual bool InsertMode();

// Attributes
  BOOL m_bUseMask;
  BOOL m_isdate; //added this
  CString m_str; //added this
  CString m_strMask;
  CString m_strLiteral;
  CString m_strValid;
  BOOL m_bMaskKeyInProgress;

// Operations
  virtual BOOL CheckChar(UINT& nChar);
  void SetMask(LPCSTR lpMask, LPCSTR lpLiteral = NULL, LPCSTR lpValid = NULL);
  void SendChar(UINT nChar);

// Implementation
public:

protected:
  int isprint(int c);
  // Generated message map functions
  //{{AFX_MSG(CEraMaskEdit)
  afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

class CEraNameEdit : public CEraEdit {
  DECLARE_DYNAMIC(CEraNameEdit)
// Constructors
public:
  CEraNameEdit();
// Operations:
  //virtual BOOL CheckChar(UINT& nChar);

  // Generated message map functions
  //{{AFX_MSG(CEraNameEdit)
  protected:
	afx_msg void OnKillfocus();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

#define ERADATEEDIT_CLASSNAME _T("EraDateEdit")  // Window class name
class CEraDateEdit : public CEraMaskEdit {
  DECLARE_DYNAMIC(CEraDateEdit)

// Constructors
public:
  CEraDateEdit();
  BOOL RegisterWindowClass();

private:
  CRect m_rcDropButton;
  DWORD m_dwBtnStyle;
  bool  m_fDropDown;
  bool  m_fCalendarOn;
  bool  m_fOffByBtn;
  CMonthCalCtrl* m_pCalendarWnd;

  // Implementation
public:
  void SetDate(COleDateTime& Date);
  void SetDate(SYSTEMTIME& st);
  COleDateTime GetDate();
  CString      GetDDMMYYYY();
  BOOL         IsCalendarActive() { return m_fCalendarOn; }


protected:
  virtual void SetSelection();

  void         ShowCalendar();
  void         HideCalendar();
  void         ShowHideCalendar();
  void         OnCalendarKillFocus();

  void         SetDropBtnRect();
  int          GetDatePart();
  void         CorrectionDate(COleDateTime& odt, int y, int m, int d);
  void         OnDelete();
  void         OnDayUp();
  void         OnMonthUp();
  void         OnYearUp();
  void         OnDateUp();
  void         OnDayDown();
  void         OnMonthDown();
  void         OnYearDown();
  void         OnDateDown();
  bool         OnLeft();
  bool         OnRight();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraDateEdit)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

protected:
  void  DrawDropButton(CDC* pDC);
  // Generated message map functions
  //{{AFX_MSG(CEraDateEdit)
	afx_msg void OnPaint();
  afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnDestroy();
	//}}AFX_MSG
  afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnClear(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
  DECLARE_MESSAGE_MAP()
};


class CEraSeriaEdit : public CEraMaskEdit {
  DECLARE_DYNAMIC(CEraSeriaEdit)

// Constructors
public:
  CEraSeriaEdit();

// Implementation
public:

protected:
  // Generated message map functions
  //{{AFX_MSG(CEraSeriaEdit)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


void AFXAPI DDX_FieldTextEraDate(CDataExchange* pDX, int nIDC, COleDateTime& value, CDaoRecordset* pRecordset);
void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CEraDateEdit& rControl, COleDateTime& Date);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CEraNoticeEdit window

class CEraNoticeEdit : public CEraEdit
{
// Construction
public:
	CEraNoticeEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraNoticeEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraNoticeEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraNoticeEdit)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CEraMoneyEdit window
class CEraMoneyEdit : public CEraEdit {
// Construction
public:
	CEraMoneyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraMoneyEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraMoneyEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraMoneyEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAEDIT_H__D676F857_FC45_4379_8F1B_1FC9944793B2__INCLUDED_)
