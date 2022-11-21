#if !defined(AFX_RSMARRIAGES_H__08B33823_D510_4974_8FA7_C5C53C6D4816__INCLUDED_)
#define AFX_RSMARRIAGES_H__08B33823_D510_4974_8FA7_C5C53C6D4816__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSMarriages.h : header file
//

#include "..\Common\EraDate.h"

/////////////////////////////////////////////////////////////////////////////
// CRSMarriages DAO recordset
class CRSMarriages : public CDaoRecordset {
public:
	CRSMarriages(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSMarriages)

// Field/Param Data
	//{{AFX_FIELD(CRSMarriages, CDaoRecordset)
	long	   m_ID;
	COleDateTime m_DATEREG;
	short    m_NUMBER;
	long	   m_FLAGS;
	CString	 m_MOLD_SURNAME;
	CString	 m_MNEW_SURNAME;
	CString	 m_MNAME;
	CString	 m_MPATRONYMIC;
	COleDateTime m_MBIRTH_DATE;
	CString	 m_MBIRTH_COUNTRY;
	CString	 m_MBIRTH_REGION;
	CString	 m_MBIRTH_DISTRICT;
	CString	 m_MBIRTH_CITY;
	CString	 m_MCITIZENSHIP;
	CString	 m_MRP_COUNTRY;
	CString	 m_MRP_REGION;
	CString	 m_MRP_DISTRICT;
	CString	 m_MRP_CITY;
	CString	 m_MRP_STREET;
	CString	 m_MRP_HOUSE;
	CString	 m_MRP_FLAT;
	BYTE	   m_MPASSPORT_TYPE;
	CString	 m_MPASSPORT_SERIA;
	CString	 m_MPASSPORT_NUMBER;
	COleDateTime m_MPASSPORT_DATE;
	CString	 m_MPASSPORT_BY;
	BYTE	   m_MFAMILY_STATUS;
	short	   m_MACT_NUMBER;
	COleDateTime m_MACT_DATE;
	CString	 m_MACT_BY;
	CString  m_WOLD_SURNAME;
	CString  m_WNEW_SURNAME;
	CString  m_WNAME;
	CString  m_WPATRONYMIC;
	COleDateTime m_WBIRTH_DATE;
	CString	 m_WBIRTH_COUNTRY;
	CString	 m_WBIRTH_REGION;
	CString  m_WBIRTH_DISTRICT;
	CString  m_WBIRTH_CITY;
	CString	 m_WCITIZENSHIP;
	CString	 m_WRP_COUNTRY;
	CString	 m_WRP_REGION;
	CString	 m_WRP_DISTRICT;
	CString	 m_WRP_CITY;
	CString	 m_WRP_STREET;
	CString	 m_WRP_HOUSE;
	CString	 m_WRP_FLAT;
	BYTE	   m_WPASSPORT_TYPE;
	CString	 m_WPASSPORT_SERIA;
	CString	 m_WPASSPORT_NUMBER;
	COleDateTime m_WPASSPORT_DATE;
	CString	 m_WPASSPORT_BY;
	BYTE	   m_WFAMILY_STATUS;
	short	   m_WACT_NUMBER;
	COleDateTime m_WACT_DATE;
	CString	 m_WACT_BY;
	CString	 m_CERTIFICATE_SERIA;
	CString	 m_CERTIFICATE_NUMBER;
	CString	 m_MNOTICE;
	CString	 m_WNOTICE;
  CString	 m_EXTNOTES;
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
