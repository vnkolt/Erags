#if !defined(AFX_RSBIRTHES_H__D66F4504_6D3B_4FBD_A107_5FAA879D7615__INCLUDED_)
#define AFX_RSBIRTHES_H__D66F4504_6D3B_4FBD_A107_5FAA879D7615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSBirthes.h : header file
//

#define BIRTH_G10         0x0001   // Const к_Г10 = 1  ' Графа 10 {Г10: }
#define BIRTH_RENEW       0x0002   // Const к_ПАЗ = 2  ' Поновлений АЗ
#define BIRTH_LONGTERM    0x0004   // Const к_ЗПС = 4  ' З пропуском строку
#define BIRTH_NOINLIST    0x0008   // Const к_МСН = 8  ' Не в списку новонароджених
#define BIRTH_DECL20      0x0010


/////////////////////////////////////////////////////////////////////////////
// CRSBirthes DAO recordset

class CRSBirthes : public CDaoRecordset
{
public:
	CRSBirthes(CDaoDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRSBirthes)

// Field/Param Data
	//{{AFX_FIELD(CRSBirthes, CDaoRecordset)
	long	m_ID;
	short m_NUMBER;
	BOOL	m_SEX;
	COleDateTime	m_DATEREG;
	long	m_RENEW;
	CString	m_SURNAME;
	CString	m_NAME;
	CString	m_PATRONYMIC;
	COleDateTime	m_BIRTH_DATE;
	BOOL	m_BP_FLAG;
	CString	m_BP_COUNTRY;
	CString	m_BP_REGION;
	CString	m_BP_CITY;
	CString	m_BP_DISTRICT;
	BYTE	m_NKIDS;
	BYTE	m_BYCOUNT;
	BOOL	m_ALIVE_FLAG;
	BYTE	m_SOURCE_TYPE;
  CString m_SOURCE_NDOC;
  COleDateTime	m_SOURCE_DATE;
  CString m_SOURCE_BY;
	CString	m_MEDICAL_CERTIFICATE_NUMBER;
	COleDateTime	m_MEDICAL_CERTIFICATE_DATE;
	CString	m_MEDICAL_CERTIFICATE_BY;
	CString	m_FATHER_SURNAME;
	CString	m_FATHER_NAME;
	CString	m_FATHER_PATRONYMIC;
	BOOL	m_FATHER_DOB_FLAG;
	COleDateTime	m_FATHER_BIRTH_DATE;
	CString	m_FATHER_CITIZENSHIP;
	CString	m_FATHER_COUNTRY;
	CString	m_FATHER_REGION;
	CString	m_FATHER_CITY;
	CString	m_FATHER_DISTRICT;
	CString	m_FATHER_STREET;
	CString	m_FATHER_HOUSE;
	CString	m_FATHER_FLAT;
	CString	m_MOTHER_SURNAME;
	CString	m_MOTHER_NAME;
	CString	m_MOTHER_PATRONYMIC;
	BOOL	m_MOTHER_DOB_FLAG;
	COleDateTime	m_MOTHER_BIRTH_DATE;
	CString	m_MOTHER_CITIZENSHIP;
	CString	m_MOTHER_COUNTRY;
	CString	m_MOTHER_REGION;
	CString	m_MOTHER_CITY;
	CString	m_MOTHER_DISTRICT;
	CString	m_MOTHER_STREET;
	CString	m_MOTHER_HOUSE;
	CString	m_MOTHER_FLAT;
  BYTE    m_DECLARANT_TYPE;
	CString	m_DECLARANT_NAME;
	CString	m_DECLARANT_ADDRESS;
	BYTE    m_DECLARANT_PASSPORT_TYPE;
	CString	m_DECLARANT_PASSPORT_SERIA;
	CString	m_DECLARANT_PASSPORT_NUMBER;
	COleDateTime	m_DECLARANT_PASSPORT_DATE;
	CString	m_DECLARANT_PASSPORT_BY;
	CString	m_CERTIFICATE_SERIA;
	CString	m_CERTIFICATE_NUMBER;
	CString	m_NOTICE;
  CString	m_EXTNOTES;
	//}}AFX_FIELD

// Operations:
public:
  CString GetNewSurname(LPCTSTR szMemo=NULL);
  static CString GetNewSurnameFromMemo(const CString& sMemo, const CString& sOldSurname);
  CString GetNewOrOldSurname();
  CString GetNewName(LPCTSTR szMemo=NULL);
  static CString GetNewNameFromMemo(const CString& sMemo, const CString& sOldName);
  CString GetNewOrOldName();
  CString GetNewPatronymic(LPCTSTR szMemo=NULL);
  static CString GetNewPatronymicFromMemo(const CString& sMemo, const CString& sOldPatronymic);
  CString GetNewOrOldPatronymic();
  CString GetNewMotherSurname(LPCTSTR szMemo=NULL);
  CString GetFatherDate(LPCTSTR szMemo=NULL);
  CString GetMotherDate(LPCTSTR szMemo=NULL);


  void    SetNewSurname(LPCTSTR szNewSurname, CString& szMemo);
  void    SetNewName(LPCTSTR szNewName, CString& szMemo);
  void    SetNewPatronymic(LPCTSTR szNewPatronymic, CString& szMemo);


  CString SetNewSNP(CString& sMemo,
                    const CString& sNewS,
                    const CString& sNewN,
                    const CString& sNewP,
                    const CString& sNewMotherSurname,
                    const CString& sFatherDate,
                    const CString& sMotherDate,
                    const CString& sGrg10);

  CString GetSvNeVidano();
  CString GetNotices();
  CString GetNDov();

  int      GetPassport2Type(LPCTSTR szMemo=NULL);
  CString  GetPassport2Seria(LPCTSTR szMemo=NULL);
  CString  GetPassport2Number(LPCTSTR szMemo=NULL);
  CString  GetPassport2Date(LPCTSTR szMemo=NULL);
  COleDateTime GetPassport2ODT(LPCTSTR szMemo=NULL);
  CString  GetPassport2By(LPCTSTR szMemo=NULL);
  CString  GetGr10(LPCTSTR szMemo=NULL);

  CString      GetVerdictOf(LPCTSTR szMemo=NULL);
  void         SetVerdictOf(LPCTSTR szVerdictOf, CString& szMemo);
  COleDateTime GetVerdictDate(LPCTSTR szMemo=NULL);
  void         SetVerdictDate(COleDateTime dtVerdictDate, CString& szMemo);
  CString      GetVerdictNumber(LPCTSTR szMemo=NULL);
  void         SetVerdictNumber(LPCTSTR szVerdictNumber, CString& szMemo);
  COleDateTime GetNewBirthDate(LPCTSTR szMemo=NULL);
  CString      GetNewBirthDate(BOOL fStrikeOut);
  void         SetNewBirthDate(COleDateTime dtNewBirthDate, CString& szMemo);

  CString      GetNewBirthCountry(BOOL fStrikeOut, LPCTSTR szMemo=NULL);
  void         SetNewBirthCountry(LPCTSTR szNewCountry, CString& szMemo);
  CString      GetNewBirthRegion(BOOL fStrikeOut, LPCTSTR szMemo=NULL);
  void         SetNewBirthRegion(LPCTSTR szNewRegion, CString& szMemo);
  CString      GetNewBirthCity(BOOL fStrikeOut, LPCTSTR szMemo=NULL);
  void         SetNewBirthCity(LPCTSTR szNewCity, CString& szMemo);
  CString      GetNewBirthDistrict(BOOL fStrikeOut, LPCTSTR szMemo=NULL);
  void         SetNewBirthDistrict(LPCTSTR szNewDistrict, CString& szMemo);

  CString SetPassport2(CString& sMemo, int nType, const CString& sSeria, const CString& sNumber, const COleDateTime& odt, const CString& sBy); 

  BOOL    IsDeclarantIn20() { return (m_RENEW & BIRTH_DECL20) ? TRUE : FALSE; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRSBirthes)
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

#endif // !defined(AFX_RSBIRTHES_H__D66F4504_6D3B_4FBD_A107_5FAA879D7615__INCLUDED_)
