#if !defined(AFX_RSMARRIAGES_H__08B33823_D510_4974_8FA7_C5C53C6D4816__INCLUDED_)
#define AFX_RSMARRIAGES_H__08B33823_D510_4974_8FA7_C5C53C6D4816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSMarriages.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSMarriages DAO recordset

class CRSMarriages : public CDaoRecordset
{
public:
	CRSMarriages(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSMarriages)

// Field/Param Data
	//{{AFX_FIELD(CRSMarriages, CDaoRecordset)
	long	m_ID;
	COleDateTime	m_DATEREG;
	short	m_NUMBER;
	CString	m_MOLD_SURNAME;
	CString	m_MNEW_SURNAME;
	CString	m_MNAME;
	CString	m_MPATRONYMIC;
	CString	m_WOLD_SURNAME;
	CString	m_WNEW_SURNAME;
	CString	m_WNAME;
	CString	m_WPATRONYMIC;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSMarriages)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSMARRIAGES_H__08B33823_D510_4974_8FA7_C5C53C6D4816__INCLUDED_)
