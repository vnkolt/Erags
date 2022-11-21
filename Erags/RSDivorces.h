#if !defined(AFX_RSDIVORCES_H__236EF9E7_AD21_43BB_B7D6_753D1DF09368__INCLUDED_)
#define AFX_RSDIVORCES_H__236EF9E7_AD21_43BB_B7D6_753D1DF09368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSDivorces.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSDivorces DAO recordset

class CRSDivorces : public CDaoRecordset
{
public:
	CRSDivorces(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSDivorces)

// Field/Param Data
	//{{AFX_FIELD(CRSDivorces, CDaoRecordset)
	long	m_ID;
	COleDateTime	m_DATEREG;
	short	m_NUMBER;
	long	m_FLAGS;
	CString	m_MARRIAGE_BY;
	short	m_MARRIAGE_NUMBER;
	COleDateTime	m_MARRIAGE_DATE;
	BYTE	m_GROUND_TYPE;
	CString	m_GROUND;
  CString	m_GROUND_NUMBER;
  COleDateTime m_GROUND_DATE;
  BYTE	m_NKIDS;
	BYTE	m_MMARRIAGE_NUMBER;
	CString	m_MOLD_SURNAME;
	CString	m_MNEW_SURNAME;
	CString	m_MNAME;
	CString	m_MPATRONYMIC;
	COleDateTime	m_MBIRTH_DATE;
  CString	m_MBIRTH_COUNTRY;
  CString	m_MBIRTH_REGION;
  CString	m_MBIRTH_DISTRICT;
  CString	m_MBIRTH_CITY;
	CString	m_MCITIZENSHIP;
	CString	m_MRP_COUNTRY;
	CString	m_MRP_REGION;
	CString	m_MRP_DISTRICT;
	CString	m_MRP_CITY;
	CString	m_MRP_STREET;
	CString	m_MRP_HOUSE;
	CString	m_MRP_FLAT;
	BYTE	m_MPASSPORT_TYPE;
	CString	m_MPASSPORT_SERIA;
	CString	m_MPASSPORT_NUMBER;
	COleDateTime	m_MPASSPORT_DATE;
	CString	m_MPASSPORT_BY;
	COleCurrency	m_MDUTY;
	COleCurrency	m_MDUTY2;
	BYTE	m_MMONEY_TYPE;
	CString	m_MCHECK_NUMBER;
	COleDateTime	m_MCHECK_DATE;
	CString	m_MCHECK_BANK;
	CString	m_MCERTIFICATE_SERIA;
	CString	m_MCERTIFICATE_NUMBER;
	CString	m_MNOTICE;
	BYTE	m_WMARRIAGE_NUMBER;
	CString	m_WOLD_SURNAME;
	CString	m_WNEW_SURNAME;
	CString	m_WNAME;
	CString	m_WPATRONYMIC;
	COleDateTime	m_WBIRTH_DATE;
  CString	m_WBIRTH_COUNTRY;
  CString	m_WBIRTH_REGION;
  CString	m_WBIRTH_DISTRICT;
  CString	m_WBIRTH_CITY;
	CString	m_WCITIZENSHIP;
	CString	m_WRP_COUNTRY;
	CString	m_WRP_REGION;
	CString	m_WRP_DISTRICT;
	CString	m_WRP_CITY;
	CString	m_WRP_STREET;
	CString	m_WRP_HOUSE;
	CString	m_WRP_FLAT;
	BYTE	m_WPASSPORT_TYPE;
	CString	m_WPASSPORT_SERIA;
	CString	m_WPASSPORT_NUMBER;
	COleDateTime	m_WPASSPORT_DATE;
	CString	m_WPASSPORT_BY;
	COleCurrency	m_WDUTY;
	COleCurrency	m_WDUTY2;
	BYTE	m_WMONEY_TYPE;
	CString	m_WCHECK_NUMBER;
	COleDateTime m_WCHECK_DATE;
	CString	m_WCHECK_BANK;
	CString	m_WCERTIFICATE_SERIA;
	CString	m_WCERTIFICATE_NUMBER;
	CString	m_WNOTICE;
  CString	m_EXTNOTES;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSDivorces)
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

#endif // !defined(AFX_RSDIVORCES_H__236EF9E7_AD21_43BB_B7D6_753D1DF09368__INCLUDED_)
