#if !defined(AFX_XCNV_H__DFEA48CB_F37B_44C7_AF78_657F91B4E56A__INCLUDED_)
#define AFX_XCNV_H__DFEA48CB_F37B_44C7_AF78_657F91B4E56A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XCnv.h : header file
//
#include "..\ZipArchive\ZipArchive.h"


//typedef void (*OnKeyword)(LPCTSTR szKeyword, DWORD dwData);

enum CONVERT_TYPE {
  CNV_NONE  = 0,
  CNV_RTF   = 1,
  CNV_ODT   = 2
};


/////////////////////////////////////////////////////////////////////////////
// CXCnv abstract class
class CXCnv : public CObject {
// Construction
public:
	CXCnv();
	virtual ~CXCnv();

// Attributes
protected:
  TCHAR        m_tcKeywordB;
  TCHAR        m_tcKeywordE;
  CString      m_szFilename;
  CString      m_szContent;
  BOOL         m_fError;
  DWORD        m_dwError;
  CONVERT_TYPE m_Cnv;
public:
// Operations
protected:
  virtual BOOL  ReadContent()  = 0;
  virtual BOOL  WriteContent() = 0;
public:
  BOOL  IsError() { return m_fError; }

  CString GetData()                      { return m_szContent;   }
  void    SetData(const CString& szData) { m_szContent = szData; }

public:
  void    SetWorkFile(LPCTSTR szFilename);
  virtual BOOL Read();
  virtual BOOL Read(LPCTSTR szFilename);
  virtual BOOL Write();
  virtual BOOL Write(LPCTSTR szFilename);
  CString GetRow(LPCTSTR pszKeyB, LPCTSTR pszKeyE);
  CString GetKeyword(LPCTSTR pszKeyword);

  void    ReplaceEOLForOO(CString& szReplace, int nKeywordB);
  void    ReplaceSpacesForOO(CString& szReplace);
  void    ReplaceContent(void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData, BOOL fReplaceIfEmpty=true);
  void    ReplaceRow(CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData);
  CString EncodeRow(const CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData);

  friend class CUCnv;
};

/////////////////////////////////////////////////////////////////////////////
// CODTCnv
class CODTCnv : public CXCnv {
// Construction
public:
	CODTCnv();
	virtual ~CODTCnv();

// Attributes
private:
  CZipArchive m_za;
  WORD        m_wCntIndex;
// Operations
protected:
  BOOL  ReadContent();
  BOOL  WriteContent();
  void  InsertUnderlineStyle();

  friend class CUCnv;

};

/////////////////////////////////////////////////////////////////////////////
// CRTFCnv
class CRTFCnv : public CXCnv {
// Construction
public:
	CRTFCnv();
	virtual ~CRTFCnv();

// Attributes
private:
  CFile m_rtf;
// Operations
protected:
  BOOL  ReadContent();
  BOOL  WriteContent();

  friend class CUCnv;

};

#define CNV_FORMAT_UNK  0x0000
#define CNV_FORMAT_ODT  0x0001
#define CNV_FORMAT_RTF  0x0002

/////////////////////////////////////////////////////////////////////////////
// CUCnv
class CUCnv {
public:
  CUCnv();
  ~CUCnv();
  BOOL    Copy(LPCTSTR szIn, LPCTSTR szOut);
private:
  DWORD m_cnvFormat;
protected:
  CODTCnv m_odtCnv;
  CRTFCnv m_rtfCnv;
public:
// Operations
protected:
  BOOL  ReadContent();
  BOOL  WriteContent();
public:
  BOOL  IsError();

  CString GetData();
  void    SetData(const CString& szData);

public:
  void    SetWorkFile(LPCTSTR szFilename);
  virtual BOOL Read();
  virtual BOOL Read(LPCTSTR szFilename);
  void    InsertUnderlineStyle();
  virtual BOOL Write();
  virtual BOOL Write(LPCTSTR szFilename);
  CString GetRow(LPCTSTR pszKeyB, LPCTSTR pszKeyE);
  CString GetKeyword(LPCTSTR pszKeyword);
  void    ReplaceContent(void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData, BOOL fReplaceIfEmpty=true);
  void    ReplaceRow(CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData);
  CString EncodeRow(const CString& szRow, void (*OnKeyword)(LPCTSTR szKeyword, CString& szReplace, DWORD dwData), DWORD dwData);
};
void    UTF8ToWin1251(CString& str);
void    Win1251ToUTF8(CString& str);
CString RTFToWin1251(LPCTSTR szRTF);
CString Win1251ToRTF(LPCTSTR szRTF);

extern CONVERT_TYPE g_ConvertType;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XCNV_H__DFEA48CB_F37B_44C7_AF78_657F91B4E56A__INCLUDED_)
