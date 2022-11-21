#if !defined(AFX_BIRTHPAGE_H__9455AC30_DE64_4F3B_B7CA_FF1B224EA109__INCLUDED_)
#define AFX_BIRTHPAGE_H__9455AC30_DE64_4F3B_B7CA_FF1B224EA109__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BirthPage.h : header file
//

#include "NewWizPage.h"
#include "WizButton.h"
#include "WizEdit.h"
#include "WizComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CBirthPage dialog

class CBirthPage : public CNewWizPage
{
// Construction
public:
	CBirthPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBirthPage)
	enum { IDD = IDW_SETBIRTH };
	CWizEdit	m_edtSeriaBirth;
	CWizEdit	m_edtSeriaMarriage;
	CStatic	      m_Title1;
	CStatic	      m_Title2;
	CWizButton	  m_chkCountry;
	CWizButton	  m_chkRegion;
	CWizButton	  m_chkDistrict;
	CWizButton	  m_chkCity;
	CWizComboBox	m_cmbCityType;
	CWizEdit	    m_BirthCountry;
	CWizEdit	    m_BirthRegion;
	CWizEdit	    m_BirthDistrict;
	CWizEdit	    m_BirthCity;
	//}}AFX_DATA

  CFont       m_Font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBirthPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  virtual void OnSetActive();
  virtual LRESULT OnWizardNext();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBirthPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIRTHPAGE_H__9455AC30_DE64_4F3B_B7CA_FF1B224EA109__INCLUDED_)
