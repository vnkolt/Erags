#if !defined(AFX_RSDEATHES_H__FDCBB637_DBE5_424E_B438_254EEB190B5D__INCLUDED_)
#define AFX_RSDEATHES_H__FDCBB637_DBE5_424E_B438_254EEB190B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSDeathes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSDeathes DAO recordset

class CRSDeathes : public CDaoRecordset
{
public:
	CRSDeathes(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSDeathes)

// Field/Param Data
	//{{AFX_FIELD(CRSDeathes, CDaoRecordset)
	long	m_ID;
	BOOL	m_SEX;
	COleDateTime	m_DATEREG;
	short	m_NUMBER;
	CString	m_SURNAME;
	CString	m_NAME;
	CString	m_PATRONYMIC;
	//}}AFX_FIELD

// Operations:
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSDeathes)
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

#endif // !defined(AFX_RSDEATHES_H__FDCBB637_DBE5_424E_B438_254EEB190B5D__INCLUDED_)
