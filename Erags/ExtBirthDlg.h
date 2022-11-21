#if !defined(AFX_EXTBIRTHDLG_H__575FAA6C_A1FF_4FD4_9AB0_1224FD549DD5__INCLUDED_)
#define AFX_EXTBIRTHDLG_H__575FAA6C_A1FF_4FD4_9AB0_1224FD549DD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExtBirthDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "rsBirthes.h"
#include "DialogEx.h"

#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CExtBirthDlg dialog
class CExtBirthDlg : public CDialogEx {
// Construction
public:
	CExtBirthDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExtBirthDlg)
	enum { IDD = IDD_EXTBIRTH };
  CFrameBG          m_Frame1;
  CFrameBG          m_Frame2;
  CFrameBG          m_Frame3;
	CEraNameEdit      m_edtNewSurname;
	CEraNameComboBox	m_cmbNewName;
	CEraNameComboBox	m_cmbNewPatronymic;
	CEraEdit          m_edtFatherDate;
	CEraEdit	        m_edtMotherDate;
	CEraNameEdit	    m_edtNewMotherSurname;
	CEraEdit	        m_edtGr10;
	CXButtonXP        m_chkGr10;
	CXButtonXP        m_chkWitnesses;
	CEraEdit	        m_edtMemo;
	//}}AFX_DATA
  CTCImageList      m_CheckBoxIL;
  CRSBirthes*   m_pSet;
  BOOL          m_fSex;
  CString       m_Surname, m_Name, m_Patronymic;
  CString       m_FatherSurname, m_FatherName;
  COleDateTime  m_FatherDate;
  CString       m_MotherSurname;
  COleDateTime  m_MotherDate;

  CString       m_sMemo;

  CString       m_sGr10, m_sNewGr10;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExtBirthDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CExtBirthDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAll();
	afx_msg void OnYes();
	afx_msg void OnGr10();
	afx_msg void OnGrSvid();
  afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTBIRTHDLG_H__575FAA6C_A1FF_4FD4_9AB0_1224FD549DD5__INCLUDED_)
