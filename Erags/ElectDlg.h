#if !defined(AFX__ELECTDLGT_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_)
#define AFX__ELECTDLGT_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ElectDlg.h : header file
//

#include "DialogEx.h"
#include "..\Controls\XButtonXP.h"
#include "..\Controls\TCToolBar\TCImageList.h"

#include "..\Controls\EraControls.h"

#include "..\Common\Elections.h"

extern SHORT         g_iMonth;
extern COleDateTime  g_RegDate;
extern BOOL          g_fPeriod;
extern COleDateTime  g_odtFrom;
extern COleDateTime  g_odtTill;
extern BOOL          g_fMakeXLS;


void  FillByMarriages(CDaoDatabase* pDB, CPtrArray& array, CStatic* pStatic, CProgressCtrl* pProgress);
void  FillByDivorces(CDaoDatabase* pDB, CPtrArray& array, CStatic* pStatic, CProgressCtrl* pProgress);
void  FillByChanges(CDaoDatabase* pDB, CPtrArray& array, CStatic* pStatic, CProgressCtrl* pProgress);


class CElectItemEx : public CElectItem {
public:
  void      SetNew(LPCTSTR szNewSurname, LPCTSTR szNewName, LPCTSTR szNewPatronymic);
  void      SetOld(LPCTSTR szOldSurname, LPCTSTR szOldName, LPCTSTR szOldPatronymic);
  void      SetBP(CDaoRecordset* pRS, LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity);
  void      SetRP(CDaoRecordset* pRS, LPCTSTR szCountry, LPCTSTR szRegion, LPCTSTR szDistrict, LPCTSTR szCity);
  void      SetAddress(CDaoRecordset* pRS, LPCTSTR szStreet, LPCTSTR szHouse, LPCTSTR szFlat);
};

/////////////////////////////////////////////////////////////////////////////
// CElectDlg dialog
class CElectDlg : public CDialogEx {
// Construction
public:
	CElectDlg(UINT idDialog, CWnd* pParent = NULL);   // standard constructor
  ~CElectDlg();

  int           m_SortID;
  int           m_IDD;
  CString       m_sCaption;
  CPtrArray     m_ElectItems;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Dialog Data
	//{{AFX_DATA(CElectDlg)
	enum { IDD = IDD_ELECTION_CHANGES };
	CEraDateEdit    m_From;
	CEraDateEdit	  m_Till;
  CProgressCtrl   m_Progress;
  CFrameBG        m_Frame1, m_Frame2, m_Frame3, m_Frame4, m_Frame5;

  CXButtonXP      m_rbDontFilter, m_rbFilterYes, m_rbFilterNo;

  CXButtonXP      m_rbSortPib, m_rbSortBirthDate, m_rbSortLivePlace;
  CXButtonXP      m_rbSortPibAfter, m_rbSortPibBefore;
  CXButtonXP      m_chkMarriages, m_chkDicorces, m_chkChanges;

  CXButtonXP      m_chkXLS, m_chkTVKDash, m_rbOneSheet, m_rbManySheets;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CElectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  Sort();

	// Generated message map functions
	//{{AFX_MSG(CElectDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMonlist();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void ElectionsToXLS(CElections* pElections, BOOL fDeath);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__ELECTDLGT_H__426AE85A_7FA9_4B80_AC3D_BC002DFD0AEB__INCLUDED_)
