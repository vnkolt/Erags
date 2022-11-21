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
	long	m_FLAGS;
	BOOL	m_SEX;
	CString	m_OLDSURNAME;
	CString	m_NEWSURNAME;
	CString	m_OLDNAME;
	CString	m_NEWNAME;
	CString	m_OLDPATRONYMIC;
	CString	m_NEWPATRONYMIC;
	COleDateTime	m_BIRTH_DATE;
	CString	m_BIRTH_COUNTRY;
	CString	m_BIRTH_REGION;
	CString	m_BIRTH_DISTRICT;
	CString	m_BIRTH_CITY;
	short	m_BIRTHACT_NUMBER;
	COleDateTime	m_BIRTHACT_DATE;
	CString	m_BIRTHACT_BY;
	CString	m_CITIZENSHIP;
	CString	m_COUNTRY;
	CString	m_REGION;
	CString	m_DISTRICT;
	CString	m_CITY;
	CString	m_STREET;
	CString	m_HOUSE;
	CString	m_FLAT;
  COleCurrency m_DUTY;
	CString	m_CHECKNUM;
	COleDateTime	m_CHECKDATE;
	CString	m_CHECKBANK;
	BYTE	  m_PASSPORT_TYPE;
  CString	m_PASSPORT_SERIA;
	CString	m_PASSPORT_NUMBER;
	COleDateTime	m_PASSPORT_DATE;
	CString	m_PASSPORT_BY;
	CString	m_CERTIFICATE_SERIA;
	CString	m_CERTIFICATE_NUMBER;
	CString	m_NOTICE;
  CString	m_EXTNOTES;
	//}}AFX_FIELD

// Operations:
public:
  static CString GetTypeName(BYTE bType);

  bool    IsNoticeBirthDate();
  CString GetNoticeBirthDateDDMMMYYYY();
  CString GetNotices();

  LPCTSTR GetNewSurnameOrLine();
  LPCTSTR GetNewNameOrLine();
  LPCTSTR GetNewPatronymicOrLine();

  CString GetNewOrOldSurname();
  CString GetNewOrOldName();
  CString GetNewOrOldPatronymic();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSChanges)
	public:
	virtual CString GetDefaultDBName();		// Default database name
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
	virtual void DoFieldExchange(CDaoFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

  virtual void Delete();

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSCHANGES_H__D6F83B43_FD1F_4080_BBE0_08821387C7C9__INCLUDED_)
