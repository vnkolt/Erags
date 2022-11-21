#if !defined(AFX_RSCHANGESDEP_H__B918DECD_5754_435D_93F3_8E57AF5349C7__INCLUDED_)
#define AFX_RSCHANGESDEP_H__B918DECD_5754_435D_93F3_8E57AF5349C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSChangesDep.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSChangesDep DAO recordset

class CRSChangesDep : public CDaoRecordset
{
public:
	CRSChangesDep(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSChangesDep)

// Field/Param Data
	//{{AFX_FIELD(CRSChangesDep, CDaoRecordset)
	long	m_ID;
	BYTE	m_TYPE;
	short	m_NUMBER;
	COleDateTime	m_DATEREG;
	CString	m_REGISTRAR;
  CString	m_PERSON;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSChangesDep)
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

#endif // !defined(AFX_RSCHANGESDEP_H__B918DECD_5754_435D_93F3_8E57AF5349C7__INCLUDED_)
