#if !defined(AFX_RSDIVORCES_H__236EF9E7_AD21_43BB_B7D6_753D1DF09368__INCLUDED_)
#define AFX_RSDIVORCES_H__236EF9E7_AD21_43BB_B7D6_753D1DF09368__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSDivorces.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRSDivorces DAO recordset
class CRSDivorces : public CDaoRecordset {
public:
  CRSDivorces(CDaoDatabase* pDatabase = NULL);
  DECLARE_DYNAMIC(CRSDivorces)

// Field/Param Data
  //{{AFX_FIELD(CRSDivorces, CDaoRecordset)
  long  m_ID;
  COleDateTime  m_DATEREG;
  short  m_NUMBER;
  CString  m_MOLD_SURNAME;
  CString  m_MNEW_SURNAME;
  CString  m_MNAME;
  CString  m_MPATRONYMIC;
  CString  m_WOLD_SURNAME;
  CString  m_WNEW_SURNAME;
  CString  m_WNAME;
  CString  m_WPATRONYMIC;
  //}}AFX_FIELD

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CRSDivorces)
  public:
  virtual CString GetDefaultDBName();    // Default database name
  virtual CString GetDefaultSQL();    // Default SQL for Recordset
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
