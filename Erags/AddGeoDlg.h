#if !defined(AFX_ADDGEODLG_H__D376FF40_E910_4460_B83A_81A6DFD4DDBD__INCLUDED_)
#define AFX_ADDGEODLG_H__D376FF40_E910_4460_B83A_81A6DFD4DDBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddGeoDlg.h : header file
//
#include "..\Controls\EraControls.h"
#include "..\Controls\XButtonXP.h"

#include "DialogEx.h"

enum ERAGSGEOTYPE { GT_COUNTRY, GT_REGION, GT_CITY, GT_DISTRICT, GT_VILLAGE };

class CGeoRecord;

/////////////////////////////////////////////////////////////////////////////
// CAddGeoDlg dialog

class CAddGeoDlg : public CDialogEx
{
// Construction
public:
	CAddGeoDlg(CWnd* pParent, ERAGSGEOTYPE geotype);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddGeoDlg)
	enum { IDD = IDD_ADDGEODLG };
  CStaticBG     m_lblName;
  CStaticBG     m_lblFullName;
  CStaticBG     m_lblType;
	CEraComboBox  m_cmbType;
	CEraNameEdit	m_edtName;
	CEraNameEdit	m_edtFullName;
  CXButtonXP	  m_btnUp;
	//}}AFX_DATA
  ERAGSGEOTYPE  m_GeoType;
	CString       m_sName;
  CString       m_sFullName;
  CString       m_sType;
  CGeoRecord*   m_pParentGeoRecord;
  CGeoRecord*   m_pRecord;
  bool          m_fOk;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddGeoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
  BOOL  CanAdd();
  void  OnUp();

	// Generated message map functions
	//{{AFX_MSG(CAddGeoDlg)
	virtual BOOL OnInitDialog();
	virtual void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDGEODLG_H__D376FF40_E910_4460_B83A_81A6DFD4DDBD__INCLUDED_)
