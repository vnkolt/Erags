#if !defined(AFX_FORMABC_H__9A35BC3B_86C7_4DB5_9CB5_A27436FA5712__INCLUDED_)
#define AFX_FORMABC_H__9A35BC3B_86C7_4DB5_9CB5_A27436FA5712__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormABC.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CFormABC form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"

class CRSBirthes;
class CRSMarriages;
class CRSDivorces;
class CRSChanges;
class CRSDeathes;
class CABCList;

//#define CFormABCBase CDaoRecordViewBG
#define CFormABCBase CDaoRecordView
class CFormABC : public CFormABCBase {
protected: // create from serialization only
  CFormABC(UINT idd);
	DECLARE_DYNAMIC(CFormABC)

public:
	//{{AFX_DATA(CFormABC)
	CDaoRecordset* m_pSet;
	//}}AFX_DATA
  BOOL        m_bEnabled;
  CPPToolTip  m_tooltip;

// Data members:
protected:
  CString     m_szFormName;
  BOOL        m_fInitialized;
  BOOL        m_fFilled;
  BOOL        m_fGoTo;
  long        m_ID;
  BOOL        m_fEnableRelayEvent;
  WORD        m_ShownCtrlId;

// Attributes
public:
	CEraABCDoc*     GetDocument();
  CABCList*       GetListCtrl();

// Operations
public:
  virtual void    SetFocusToFirstControl() = 0;
  virtual void    SetScaleFlags(CWnd* pWnd, WORD& wFlags);
  virtual void    EnableControls(BOOL fEnable=TRUE);
  virtual void    ClearControls();
  virtual void    GoTo(long lID, BOOL fSave=TRUE);
  long            RecordNew();
  bool            SetDefaultNumber();
  void            SetDefaultDateReg();
  void            SetFilled();

protected:
  virtual void OnClickSex(){}

// Form Data
public:
	//{{AFX_DATA(CFormABC)
	enum { IDD = IDD_YESNO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
  void  CloseRecordSet();
  BOOL  SaveData();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormABC)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
	virtual void DoDataExchange(CDataExchange* pDX, long lID);    // DDX/DDV support

// Implementation
protected:
	virtual ~CFormABC();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  void          GoToPrevRecord();
  void          GoToNextRecord();
  virtual void  BeforeGoToNextRecord();

  virtual void SetTooltips();
  virtual void ScrollToControl(CWnd* pWnd);

	// Generated message map functions
	//{{AFX_MSG(CFormABC)
  afx_msg void OnDestroy();
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnRecordFirst();
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrev();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordNew(CCmdUI* pCmdUI);
	afx_msg void OnRecordNew();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnRecordDelete();
	//}}AFX_MSG
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FormABC.cpp
inline CEraABCDoc* CFormABC::GetDocument()
   { return (CEraABCDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMABC_H__9A35BC3B_86C7_4DB5_9CB5_A27436FA5712__INCLUDED_)
