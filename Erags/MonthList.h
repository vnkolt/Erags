#if !defined(AFX_MONTHLIST_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_)
#define AFX_MONTHLIST_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonthList.h : header file
//

#include "DialogEx.h"

#include "..\Controls\EraControls.h"
#include "..\Controls\TCToolBar\TCImageList.h"

extern SHORT         g_iMonth;
extern COleDateTime  g_RegDate;
extern BOOL          g_fPeriod;
extern BOOL          g_fNoPrintUnknowns;
extern COleDateTime  g_odtFrom;
extern COleDateTime  g_odtTill;

#define PRINT_ALLDOCS   0
#define PRINT_PASPORTS  1
#define PRINT_MILCARS   2

/////////////////////////////////////////////////////////////////////////////
// CMonthList dialog
class CMonthList : public CDialogEx {
// Construction
public:
	CMonthList(UINT idPrintID, BOOL bCheckPeriod, const COleDateTime& odt, CWnd* pParent = NULL);   // standard constructor
  ~CMonthList();

  UINT                m_PrintID;
  CString             m_sCaption;
  CString             m_sDBName;

  CMapStringToString  m_cache;
  CString             m_SectName;

  int                 m_MaxPage1, m_MaxPage2;
  COleDateTime        m_odt;
  BOOL                m_bCheckPeriod;
  static int          m_PrintWhat;
  CTCImageList        m_RadioIL;
  CTCImageList        m_CheckBoxIL;

// Dialog Data
	//{{AFX_DATA(CMonthList)
	enum { IDD = IDD_LISTDLG };
  CFrameBG        m_Frame1;
  CFrameBG        m_Frame2;
  CFrameBG        m_Frame3;
  CFrameBG        m_Frame4;
	CEraComboBox	  m_cmbDistrict;
	CListBox	      m_MonList;
	CEraDateEdit    m_From;
	CEraDateEdit	  m_Till;
	CXButtonXP      m_chkPeriod;
  CXButtonXP      m_btnCommonList;
  CXButtonXP      m_btnPasports;
  CXButtonXP      m_btnMilCards;
  CXButtonXP      m_chkNoUnknowns;
  CXButtonXP      m_chkMakeDBF;
  CComboBox       m_cmbVBScript;
	CEraEdit	      m_Page1;
	CEraEdit	      m_Page2;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonthList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
  void  Resize();
  void  FillVBScriptCombo(LPCTSTR szKey);
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMonthList)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMonlist();
	afx_msg void OnEditChangeComboDistricts();
	afx_msg void OnSelchangeComboDistricts();
	afx_msg void OnChangePage1();
	afx_msg void OnChangePage2();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPeriod();
  afx_msg void OnNoPrintUnknowns();
	afx_msg void OnYes();
	afx_msg void OnCommonlist();
	afx_msg void OnPassports();
	afx_msg void OnMilcars();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTHLIST_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_)
