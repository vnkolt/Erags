#if !defined(AFX_NAMESDLG_H__09D75A28_23A8_4977_92B8_2E4C8B33D9D8__INCLUDED_)
#define AFX_NAMESDLG_H__09D75A28_23A8_4977_92B8_2E4C8B33D9D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NamesDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "..\Controls\BkgndCtrl.h"
#include "..\Controls\XButtonXP.h"

#define CNamesDlgBase CDialog

/////////////////////////////////////////////////////////////////////////////
// CNamesDlg dialog
class CNamesDlg : public CNamesDlgBase {
// Construction
public:
	CNamesDlg(LPCTSTR szCaption, LPCTSTR szTableName, LPCTSTR szFieldName, LPCTSTR szColumnName, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNamesDlg)
	enum { IDD = IDD_NAMES };
	CListCtrl	m_List;
	CEraNameEdit	m_Name;
	CXButtonXP    m_btnNew;
	CXButtonXP    m_btnDelete;
	//}}AFX_DATA

private:
  CString       m_szCaption;
  CString       m_szTableName;
  CString       m_szFieldName;
  CString       m_szColumnName;
  BOOL          m_fChangeName;

// Attributes
public:
  CImageList  m_ImageList;

// Operations
protected:
  void  AddNewRecord(const CString& s, bool fSex);
  void  UpdateRecord(int nItem, LPCTSTR szName, bool fSex);
  void  Fill();
  void  ChangeSex();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNamesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNamesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClickNamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownNamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeName();
	afx_msg void OnRecordNew();
	afx_msg void OnRecordDelete();
	afx_msg void OnDblclkNamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEditNamelist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedNamelist(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMESDLG_H__09D75A28_23A8_4977_92B8_2E4C8B33D9D8__INCLUDED_)
