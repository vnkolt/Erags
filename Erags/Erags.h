// Erags.h : main header file for the ERAGS application
//

#if !defined(AFX_ERAGS_H__C7E2CF0E_A3FF_49E9_B4D1_A432D520650E__INCLUDED_)
#define AFX_ERAGS_H__C7E2CF0E_A3FF_49E9_B4D1_A432D520650E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "..\Controls\NewMenu.h"

// #define FREE_LICENCE

extern COLORREF g_clrBackColor;
extern COLORREF g_clrForeColor;
extern COLORREF g_clrFocusBackColor;
extern COLORREF g_clrFocusForeColor;
extern BOOL     g_fSuperVisor; 

extern COLORREF g_clrMaleBackColor;
extern COLORREF g_clrFemaleBackColor;
extern COLORREF g_clrMaleForeColor;
extern COLORREF g_clrFemaleForeColor;
extern HBRUSH   g_hEditBrush, g_hFocusEditBrush;
extern BOOL     g_LocalDB;

extern LPCTSTR  g_szDateFormat, g_szDateMask;

#ifndef FREE_LICENCE
extern int      g_LKeyResult;
#endif // FREE_LICENCE


enum REGFLAGS { RF_BIRTH    = 0x0001,
                RF_MARRIAGE = 0x0002,
                RF_DIVORCE  = 0x0004,
                RF_CHANGE   = 0x0008,
                RF_DEATH    = 0x0010
              };

enum PLACETYPE { PT_NONE, PT_BF_CHILD, PT_BF_FATHER, PT_BF_MOTHER,
                 PT_MF_MBIRH, PT_MF_WBIRH, PT_MF_MRESPLACE, PT_MF_WRESPLACE,
                 PT_DIVF_MRESPLACE, PT_DIVF_WRESPLACE,
                 PT_CF_BIRTHPLACE, PT_CF_RESPLACE,
                 PT_DF_BIRTHPLACE, PT_DF_DEATHPLACE, PT_DF_RESPLACE };


#define MS_OFFICE   (UINT)('MS')
#define OPEN_OFFICE (UINT)('OO')

#define OFFICE_INSTALED_MSWORD  0x0001
#define OFFICE_INSTALED_MSEXCEL 0x0002

#define OFFICE_INSTALED_SWRITER 0x0004
#define OFFICE_INSTALED_SCALC   0x0008

class CEragsDoc;
class CWordDocument;
class CWordView;
class COOView;


/////////////////////////////////////////////////////////////////////////////
// CEragsApp:
// See Erags.cpp for the implementation of this class
//
class CEragsApp : public CWinApp {
public:
	CEragsApp();

// Attributes
private:
  BOOL        m_fOfficeChanged;
  CString     m_sDBFolder;
  CString     m_sHelpersMDB;
  UINT        m_nOffice;
public:
  CString     m_sTemplatePath;
  CString     m_sOutPath;

  DWORD       m_dwOfficeInstalled;

  CString     m_szMSWordPath;
  CString     m_szMSExcelPath;
  CString     m_szOOWriterPath;
  CString     m_szOOCalcPath;
  CString     m_szUser;
  CString     m_szPost;

  BOOL        m_fExitApp;
  BOOL        m_fReadOnly;
  BOOL        m_bGeoLoaded;
  BOOL        m_bRegLoaded;
  BOOL        m_fUseHelper;
  BOOL        m_fUkrHelp;
	UINT        m_nCurrentForm;
  CFont       m_Font;


  CWordDocument*     m_pWordActive;
  CWordView*         m_pWordView;
  COOView*           m_pOOView;
  CEragsDoc*         m_pDoc;
  HACCEL             m_AccelNavigators;
  CNewMultiDocTemplate* m_pBirthTemplate;
  CNewMultiDocTemplate* m_pMarriageTemplate;
  CNewMultiDocTemplate* m_pDivorceTemplate;
  CNewMultiDocTemplate* m_pChangeTemplate;
  CNewMultiDocTemplate* m_pDeathTemplate;
  CNewMultiDocTemplate* m_pWordTemplate;
  CNewMultiDocTemplate* m_pOOTemplate;
  CNewMultiDocTemplate* m_pRListTemplate;
  CNewMultiDocTemplate* m_pGeoTemplate;

  CFrameWnd*            m_pRListFrame;
  CFrameWnd*            m_pGeoFrame;
  long                  m_RagsID;

  bool       SetDBFolder(LPCTSTR szDBFileName);
  CDocument* OpenDocument(const CString& sDatabase, int iForm);
  CView*     GetGetActiveForm();
  LPCTSTR    GetFormName(UINT FormID);
  LPCTSTR    GetCyrFormName(UINT FormID);
  void       RefreshForms();

  void       UpdateChildWindows(CWnd* pParent);
  void       UpdateTopFrames();
  LPCTSTR    GetHelpPostfix();

  BOOL       IsMsOffice()          { return (MS_OFFICE==m_nOffice); }
  BOOL       IsMSWordInstalled()   { return (m_dwOfficeInstalled & OFFICE_INSTALED_MSWORD) != 0;  }
  BOOL       IsMSExcelInstalled()  { return (m_dwOfficeInstalled & OFFICE_INSTALED_MSEXCEL) != 0; }
  BOOL       IsOOWriterInstalled() { return (m_dwOfficeInstalled & OFFICE_INSTALED_SWRITER) != 0; }
  BOOL       IsOOCalcInstalled()   { return (m_dwOfficeInstalled & OFFICE_INSTALED_SCALC) != 0;   }

// Helpers:
  const CString& GetHelperMDB()  { return m_sHelpersMDB; }
// Setting
  void SetDefaultForm(UINT uForm);
  UINT GetDefaultForm();

  void SetOffice(UINT nOffice);
  UINT GetOffice();

  void CreateFont(const LOGFONT* lpLogFont);
  void ResetFont();
  void SaveFont();
  void RestoreFont();
  void Wizard(BOOL bRunWizard);

	static BOOL PreInitInstance();

  void  OnHelp(LPCTSTR szHtmFileName, LPCTSTR szReference=_T(""));

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEragsApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
  virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	virtual void AddToRecentFileList(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CEragsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnUpdateBirth(CCmdUI* pCmdUI);
	afx_msg void OnBirth();
	afx_msg void OnUpdateChange(CCmdUI* pCmdUI);
	afx_msg void OnChange();
	afx_msg void OnUpdateDeath(CCmdUI* pCmdUI);
	afx_msg void OnDeath();
	afx_msg void OnUpdateDivorce(CCmdUI* pCmdUI);
	afx_msg void OnDivorce();
	afx_msg void OnUpdateMarriage(CCmdUI* pCmdUI);
	afx_msg void OnMarriage();
	afx_msg void OnUpdateMedics(CCmdUI* pCmdUI);
	afx_msg void OnMedics();
	afx_msg void OnUpdatePolice(CCmdUI* pCmdUI);
	afx_msg void OnPolice();
	afx_msg void OnUpdateRegistrars(CCmdUI* pCmdUI);
	afx_msg void OnRegistrars();
	afx_msg void OnUpdateGeography(CCmdUI* pCmdUI);
	afx_msg void OnGeography();
	afx_msg void OnUpdateCitizenships(CCmdUI* pCmdUI);
	afx_msg void OnCitizenships();
	afx_msg void OnUpdateDeathcauses(CCmdUI* pCmdUI);
	afx_msg void OnDeathcauses();
	afx_msg void OnUpdateNames(CCmdUI* pCmdUI);
	afx_msg void OnNames();
	afx_msg void OnUpdatePatronymics(CCmdUI* pCmdUI);
	afx_msg void OnPatronymics();
	afx_msg void OnUpdateStreets(CCmdUI* pCmdUI);
	afx_msg void OnStreets();
	afx_msg void OnUpdateBank(CCmdUI* pCmdUI);
	afx_msg void OnBank();
	afx_msg void OnFileNew();
	afx_msg void OnFileOpen();
  afx_msg void OnUpdateZipDB(CCmdUI* pCmdUI);
  afx_msg void OnZipDB();
  afx_msg void OnUpdateUnzip(CCmdUI* pCmdUI);
  afx_msg void OnUnzip();
  afx_msg void OnUpdateImport(CCmdUI* pCmdUI);
  afx_msg void OnImport();
	afx_msg void OnUpdateFileRecent(CCmdUI* pCmdUI);
	afx_msg void OnFileRecent();
	afx_msg void OnUpdateSettings(CCmdUI* pCmdUI);
	afx_msg void OnSettings();
	afx_msg void OnUpdateHelp(CCmdUI* pCmdUI);
	afx_msg void OnHelp();
	afx_msg void OnUpdateHelper(CCmdUI* pCmdUI);
	afx_msg void OnHelper();
	afx_msg void OnUpdateHelpUkr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateHelpRus(CCmdUI* pCmdUI);
	afx_msg void OnHelpLanguage();
	//}}AFX_MSG
//  afx_msg void MyMRUFileHandler(UINT i);
  //LRESULT OnDoZip(WPARAM, LPARAM);
  void  OnMessage(int MessageType, LPCTSTR lpszFormat, ...);

	DECLARE_MESSAGE_MAP()
};

BOOL PeekAndPump();
void ProgressRoutine(int nCount, int nProcessed, void* lpData);
void __cdecl ErrorBox(LPCTSTR format,...);

extern CEragsApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAGS_H__C7E2CF0E_A3FF_49E9_B4D1_A432D520650E__INCLUDED_)
