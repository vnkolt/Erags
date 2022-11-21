#if !defined(AFX_SETGEOPLACE_H__D250F888_8F8F_4696_A24E_E9DDE29B7EA9__INCLUDED_)
#define AFX_SETGEOPLACE_H__D250F888_8F8F_4696_A24E_E9DDE29B7EA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetGeoPlace.h : header file
//

#include "NewWizPage.h"
#include "WizEdit.h"
#include "WizComboBox.h"

/////////////////////////////////////////////////////////////////////////////
// CSetGeoPlace dialog

class CSetGeoPlace : public CNewWizPage
{
// Construction
public:
	CSetGeoPlace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetGeoPlace)
	enum { IDD = IDW_SETGEOPLACE };
	CWizEdit	m_edtBoss;
	CWizEdit	m_edtToTax;
	CWizEdit	m_edtByCourt;
	CWizEdit	m_edtToUMVS;
	CWizEdit	m_edtToMil;
	CWizEdit	m_edtParent;
	CWizEdit	m_edtCity;
	CWizEdit	m_ByUMVS;
	CWizEdit	m_edtByMil;
	CWizEdit	m_edtDistrict;
	CWizEdit	m_edtRegion;
	CWizComboBox	m_cmbCityType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetGeoPlace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  void OnSetActive();
	virtual LRESULT OnWizardNext();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetGeoPlace)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETGEOPLACE_H__D250F888_8F8F_4696_A24E_E9DDE29B7EA9__INCLUDED_)
