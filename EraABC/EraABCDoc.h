// EraABCDoc.h : interface of the CEraABCDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ERAABCDOC_H__C5C55C88_121C_464D_AB9E_EB7242739DA2__INCLUDED_)
#define AFX_ERAABCDOC_H__C5C55C88_121C_464D_AB9E_EB7242739DA2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CNameCache {
public:
  CNameCache();
  ~CNameCache();

// Data:
public:
  BOOL                m_fLoaded;
  CMapStringToString  m_mapM;
  CMapStringToString  m_mapW;
// Operations:
public:
  bool Load(CDaoDatabase* pDB, LPCTSTR szTableName, LPCTSTR szFieldName);
  void FillCombo(CComboBox& cb, const CString& sFieldValue, BOOL fMale, BOOL reFill);
};

extern CNameCache theNames;
extern CNameCache thePatronymics;

class CEraABCDoc : public CDocument {
protected: // create from serialization only
	CEraABCDoc();
	DECLARE_DYNCREATE(CEraABCDoc)

// Attributes
public:

// Operations
public:
  CString   GetHelperPath(LPCTSTR lpszPathName);
  void      FillCaches(LPCTSTR lpszPathName);
  BOOL      RepairDatabase(LPCTSTR lpszPathName);
  BOOL      OpenDatabase(CDaoDatabase& db, LPCTSTR lpszPathName, BOOL fExclusive, BOOL fReadOnly, LPCTSTR szConnect=NULL);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraABCDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEraABCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEraABCDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAABCDOC_H__C5C55C88_121C_464D_AB9E_EB7242739DA2__INCLUDED_)
