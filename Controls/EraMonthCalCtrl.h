#if !defined(AFX_ERAMONTHCALCTRL_H__D7259F7A_6084_4E05_B87D_EE9E3DCE5428__INCLUDED_)
#define AFX_ERAMONTHCALCTRL_H__D7259F7A_6084_4E05_B87D_EE9E3DCE5428__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EraMonthCalCtrl.h : header file
//

/************************************** : by VK 05.05.2005 at 11:59:08 **\
typedef struct tagEMCALNMHDR {
    HWND  hwndFrom;
    UINT  idFrom;
    UINT  code;         // NM_ code
}   EMCALNMHDR;
typedef EMCALNMHDR FAR * LPEMCALNMHDR;
\************************************** : by VK 05.05.2005 at 11:59:10 **/

/////////////////////////////////////////////////////////////////////////////
// CEraMonthCalCtrl window

class CEraMonthCalCtrl : public CMonthCalCtrl
{
// Construction
public:
	CEraMonthCalCtrl();

// Attributes
public:

// Operations
private:
  void  SendNotifyToOwner(UINT code);
  void  NotifyDateChange();
  void  CloseCalendar();
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraMonthCalCtrl)
		protected:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraMonthCalCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEraMonthCalCtrl)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAMONTHCALCTRL_H__D7259F7A_6084_4E05_B87D_EE9E3DCE5428__INCLUDED_)
