#if !defined(AFX_RSCHANGES_H__D6F83B43_FD1F_4080_BBE0_08821387C7C9__INCLUDED_)
#define AFX_RSCHANGES_H__D6F83B43_FD1F_4080_BBE0_08821387C7C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSChanges.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSChanges DAO recordset

class CRSChanges : public CDaoRecordset
{
public:
	CRSChanges(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSChanges)

// Field/Param Data
	//{{AFX_FIELD(CRSChanges, CDaoRecordset)
	long	m_ID;
	short	m_NUMBER;
	COleDateTime	m_DATEREG;
	BOOL	m_SEX;
	CString	m_OLDSURNAME;
	CString	m_NEWSURNAME;
	CString	m_OLDNAME;
	CString	m_NEWNAME;
	CString	m_OLDPATRONYMIC;
	CString	m_NEWPATRONYMIC;
	//}}AFX_FIELD

// Operations:
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSChanges)
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

#endif // !defined(AFX_RSCHANGES_H__D6F83B43_FD1F_4080_BBE0_08821387C7C9__INCLUDED_)
