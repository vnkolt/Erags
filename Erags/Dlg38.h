#if !defined(AFX_DLG38_H__2C1120EA_E417_4126_BB96_D74DA99756C6__INCLUDED_)
#define AFX_DLG38_H__2C1120EA_E417_4126_BB96_D74DA99756C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg38.h : header file
//

#include "..\Controls\BkgndCtrl.h"

#include "DialogEx.h"
#include "..\Controls\EraControls.h"


class CFormMarriage;

/////////////////////////////////////////////////////////////////////////////
// CDlg38 dialog
class CDlg38 : public CDialogEx {
// Construction
public:
	CDlg38(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg38)
	enum { IDD = IDD_ANTENUPTIAL };
	CFrameBG      m_Frame1;
	CFrameBG      m_Frame2;
	CEraComboBox	m_cmbOwner;

	CEraNameEdit	m_MOldSurname;
	CEraNameEdit	m_MPatronymic;
	CEraNameEdit	m_MName;

	CEraNameEdit	m_WOldSurname;
	CEraNameEdit	m_WName;
	CEraNameEdit	m_WPatronymic;

	CEraEdit	    m_MarriageNum;
	CEraDateEdit	m_MarriageDR;
	CEraComboBox	m_cmbRagsMarriage;
	CEraEdit	    m_edtRagsMarriage;

	CEraNameEdit	m_MNewSurname;
	CEraNameEdit	m_WNewSurname;

	CEraEdit	    m_DivorceNum;
	CEraDateEdit	m_DivorceDR;
	CEraComboBox	m_cmbRagsDivorce;
	CEraEdit	    m_edtRagsDivorce;
	//}}AFX_DATA

  CFormMarriage*  m_pMarriageForm;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg38)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  OnSelendOkR(CEraComboBox& cmb, CEraEdit& edt);
  void  OnEditChangeR(CEraComboBox& cmb, CEraEdit& edt);

	// Generated message map functions
	//{{AFX_MSG(CDlg38)
	virtual BOOL OnInitDialog();
  afx_msg void OnSelendOkChangeOwner();
  afx_msg void OnSelendOkRMarriage();
  afx_msg void OnEditChangeRMarriage();
  afx_msg void OnSelendOkRDivorce();
  afx_msg void OnEditChangeRDivorce();
  afx_msg void OnYes();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG38_H__2C1120EA_E417_4126_BB96_D74DA99756C6__INCLUDED_)
