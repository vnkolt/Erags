#if !defined(AFX_RSDEATHES_H__FDCBB637_DBE5_424E_B438_254EEB190B5D__INCLUDED_)
#define AFX_RSDEATHES_H__FDCBB637_DBE5_424E_B438_254EEB190B5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSDeathes.h : header file
//

#include "DateFunc.h"

extern LPCTSTR g_szBirthDate;
extern LPCTSTR g_szDeathDate;

/////////////////////////////////////////////////////////////////////////////
// CRSDeathes DAO recordset

class CRSDeathes : public CDaoRecordset
{
public:
	CRSDeathes(CDaoDatabase* pDatabase = NULL);
  ~CRSDeathes();
	DECLARE_DYNAMIC(CRSDeathes)

// Field/Param Data
	//{{AFX_FIELD(CRSDeathes, CDaoRecordset)
	long    m_ID;
	BOOL    m_SEX;
	CString	m_DATEREG;
	short   m_NUMBER;
	long    m_FLAGS;
	BOOL	  m_RENEW;
	CString	m_SURNAME;
	CString	m_NAME;
	CString	m_PATRONYMIC;
	CString	m_CITIZENSHIP;
	CString	m_NATIONALITY;
	BOOL	  m_DOD_FLAG;
  COleDateTime m_DeathDate;
	CString	m_DEATH_DATE;
	CString	m_DP_COUNTRY;
	CString	m_DP_REGION;
	CString	m_DP_DISTRICT;
	CString	m_DP_CITY;
	CString	m_CAUSE_OF_DEATH;
	BOOL	  m_DOB_FLAG;
  COleDateTime m_BirthDate;
	CString	m_BIRTH_DATE;
	CString	m_BP_COUNTRY;
	CString	m_BP_REGION;
	CString	m_BP_DISTRICT;
	CString	m_BP_CITY;
	CString	m_RP_ZIPCODE;
	CString	m_RP_COUNTRY;
	CString	m_RP_REGION;
	CString	m_RP_DISTRICT;
	CString	m_RP_CITY;
	CString	m_RP_STREET;
	CString	m_RP_HOUSE;
	CString	m_RP_FLAT;
	BYTE	  m_PASSPORT_TYPE;
	CString	m_PASSPORT_SERIA;
	CString	m_PASSPORT_NUMBER;
	CString	m_PASSPORT_DATE;
	CString	m_PASSPORT_BY;
	CString	m_TAX_CODE;
	CString	m_MEDICAL_CERT_TYPE;
	CString	m_MEDICAL_CERT_NUMBER;
	CString	m_MEDICAL_CERT_BY;
	CString	m_MEDICAL_CERT_DATE;
	CString	m_DECLARANT_NAME;
	CString	m_DECLARANT_ADDRESS;
	BYTE    m_DECLARANT_PASSPORT_TYPE;
	CString	m_DECLARANT_PASSPORT_SERIA;
	CString	m_DECLARANT_PASSPORT_NUMBER;
	CString	m_DECLARANT_PASSPORT_DATE;
	CString	m_DECLARANT_PASSPORT_BY;
	CString	m_CERTIFICATE_SERIA;
	CString	m_CERTIFICATE_NUMBER;
	CString	m_NOTICE;
	CString	m_EXTNOTES;
	//}}AFX_FIELD

  COleDateTime  m_odtDateReg;

// Operations:
public:
  void    ClearFields();
  void    Read();

  CString MakeKey();

  BOOL    InPeriod(COleDateTime& odtFrom, COleDateTime& odtTill);


  CString GetSvNeVidano();
  bool    IsNoticeBirthDate();
  CString GetNoticeBirthDateDDMMMYYYY();
  CString GetNoticeBirthDay();
  CString GetNoticeBirthMonth();
  CString GetNoticeBirthYear();

  bool    IsNoticeDeathDate();
  CString GetNoticeDeathDateDDMMMYYYY();
  CString GetNoticeDeathDay();
  CString GetNoticeDeathMonth();
  CString GetNoticeDeathYear();
  CString GetNotices();
  CString GetNDov();

  bool    IsPassport();
  CString GetMilitaryCardSeria();
  CString GetMilitaryCardNumber();
  CString GetMilitaryCardDate();
  CString GetMilitaryCardBy();

  CString SetMilitaryCard(CString& sMemo, const CString& sSeria, const CString& sNumber, const COleDateTime& odt, const CString& sBy); 

  LPCTSTR  GetIsNotRecognized();
  Duration GetAge();

  void     ParseDeclarantFIO(CString& szSurname, CString& szName, CString& szPatronymic, CString& szOrganization);
  void     ParseDeclarantAddress(CString& szCountry, CString& szRegion, CString& szDistrict, CString& szCity,
                                 TCHAR& cStreetType, CString& szStreet, CString& szBuild, CString& szFlat);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSDeathes)
	public:
	virtual CString GetDefaultSQL();		// Default SQL for Recordset
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
