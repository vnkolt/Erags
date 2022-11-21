#if !defined(AFX_ZIPDBDLG_H__B134E869_D851_407F_B06C_8CFF8C5DDF81__INCLUDED_)
#define AFX_ZIPDBDLG_H__B134E869_D851_407F_B06C_8CFF8C5DDF81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZipDBDlg.h : header file
//

#include "..\Controls\AutoRichEditCtrl.h"
#include "DialogEx.h"

class CZipFileHeader;
class CZipFileInfo {
public:
  CString   m_szFileName;
  time_t    m_ftModiTime;
  DWORD     m_dwLength;
  BOOL      m_fIsReadOnly;
  BOOL      m_fDoZip;
  WORD      m_ZipIndex;
  CZipFileInfo();
};
#define PACK_OK         0
#define PACK_CANT_OPEN  1

/////////////////////////////////////////////////////////////////////////////
// CZipDBDlg dialog
class CZipDBDlg : public CDialogEx {
// Construction
public:
	CZipDBDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CZipDBDlg)
	enum { IDD = IDD_ZIPDB };
	CListCtrl	        m_FileList;
	//CAutoRichEditCtrl	m_Info;
  CStaticBG         m_Info;
	//}}AFX_DATA
protected:
  BOOL        m_fYesButton;
  CImageList  m_ImageList;
  //CString     m_szEmptyRTF;
  CString     m_szDBPath;
  CArray <CZipFileInfo, CZipFileInfo&> m_Files;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZipDBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  SetCurrentItem(int nItem);
  void  AddToLog(LPCTSTR sz, BOOL fPar=FALSE, BOOL fBold=FALSE, BOOL fRed=FALSE);
  void  PrepareFileList(LPCTSTR szRoot, LPCTSTR szPath);
  void  SetDoZip(CZipFileHeader* pZipFileHeader, WORD wZipIndex);
  int   Pack(LPCTSTR szFileName, int nItem);
  BOOL  DoZip();

	// Generated message map functions
	//{{AFX_MSG(CZipDBDlg)
	virtual BOOL OnInitDialog();
	virtual void OnYes();
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

void ZipIfItsNeed(const CString& szDatabase);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPDBDLG_H__B134E869_D851_407F_B06C_8CFF8C5DDF81__INCLUDED_)
