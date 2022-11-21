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
	CString	m_SURNAME;
	CString	m_NAME;
	CString	m_PATRONYMIC;
	BOOL	m_ALIVE_FLAG;
	//}}AFX_FIELD

// Operations:
public:

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
