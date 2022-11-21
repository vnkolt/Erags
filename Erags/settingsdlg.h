#if !defined(AFX_SETTINGSDLG_H__4059E64E_548A_4168_BEAD_99B804521995__INCLUDED_)
#define AFX_SETTINGSDLG_H__4059E64E_548A_4168_BEAD_99B804521995__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingsDlg.h : header file
//

#include "..\Controls\EraControls.h"
#include "..\Controls\BkgndCtrl.h"

#include "..\Controls\GridCtrl\GridCtrl.h"
#include "..\Controls\ColourPicker.h"
#include "..\Controls\XButtonXP.h"
#include "..\Controls\TCToolBar\TCImageList.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageCommon dialog
class CPropertyPageCommon : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageCommon)

// Construction
public:
	CPropertyPageCommon();
	~CPropertyPageCommon();

// Dialog Data
	//{{AFX_DATA(CPropertyPageCommon)
	enum { IDD = IDD_SETTINGS_COMMON };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
	CEraEdit    m_Country;
	CEraEdit	  m_Region;
	CEraEdit    m_District;
	CEraEdit    m_City;
	CEraEdit	  m_Rags;
  // CEraEdit	  m_OKPO;
	CEraEdit	  m_Parent;
	CEraEdit	  m_Boss;
  CEraEdit	  m_Posada;
  CEraEdit	  m_PIBPO;
	CEraEdit	  m_ByUMVS;
	CEraEdit	  m_ToUMVS;
	CEraEdit	  m_ByMil;
	CEraEdit	  m_ToMil;
	CEraEdit	  m_ByCourt;
	CEraEdit	  m_ToTax;
  CEraEdit	  m_ToSocProt;
  CXButtonXP  m_rbBirthes;
  CXButtonXP  m_rbMarriges;
  CXButtonXP  m_rbDivorces;
  CXButtonXP  m_rbChanges;
  CXButtonXP  m_rbDeathes;
	//}}AFX_DATA

  CTCImageList  m_RadioIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageCommon)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void  SetRadio(UINT uForm);
  UINT  GetRadio();
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageCommon)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageBirth dialog
class CPropertyPageBirth : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageBirth)

// Construction
public:
	CPropertyPageBirth();
	~CPropertyPageBirth();

// Dialog Data
	//{{AFX_DATA(CPropertyPageBirth)
	enum { IDD = IDD_SETTINGS_BIRTH };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
  CFrameBG    m_Frame3;
  CFrameBG    m_Frame4;
  CXButtonXP  m_rbOnePage;
  CXButtonXP  m_rbTwoPages;
  CXButtonXP  m_rbOnePageB;
	CEraEdit	  m_Country;
	CEraEdit	  m_Region;
	CEraEdit	  m_District;
	CEraEdit	  m_City;
	CEraEdit	  m_Seria;
	CXButtonXP  m_chkCountry;
	CXButtonXP  m_chkRegion;
	CXButtonXP  m_chkDistrict;
	CXButtonXP  m_chkCity;
	CXButtonXP  m_chkCitizenshipAct;
	CXButtonXP  m_chkCitizenshipCert;
	CXButtonXP  m_chkDistrictOther;
  CEraEdit	  m_DefNotice;
  CEraEdit	  m_DefNotice2;
	//}}AFX_DATA

  CBitmap       m_ActBitmap;
  CStatic       m_ActImage;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageBirth)
	public:
	virtual void OnOK();
	protected:
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage();
	afx_msg void OnOnePageB();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageBirth)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageMarriage dialog
class CPropertyPageMarriage : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageMarriage)

// Construction
public:
	CPropertyPageMarriage();
	~CPropertyPageMarriage();

// Dialog Data
	//{{AFX_DATA(CPropertyPageMarriage)
	enum { IDD = IDD_SETTINGS_MARRIAGE };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
  CFrameBG    m_Frame3;
	CEraEdit	  m_Seria;
  CEraEdit	  m_DefNotice;
  CXButtonXP  m_rbOnePage;
  CXButtonXP  m_rbTwoPages;
  CXButtonXP  m_rbOnePageB;
	CXButtonXP  m_chkCitizenshipAct;
	CXButtonXP  m_chkCitizenshipCert;
	CXButtonXP  m_chkDistrictOther;
	//}}AFX_DATA

  CBitmap       m_ActBitmap;
  CStatic       m_ActImage;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageMarriage)
	public:
	virtual void OnOK();
	protected:
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage();
	afx_msg void OnOnePageB();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageMarriage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDivorce dialog
class CPropertyPageDivorce : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageDivorce)

// Construction
public:
	CPropertyPageDivorce();
	~CPropertyPageDivorce();

// Dialog Data
	//{{AFX_DATA(CPropertyPageDivorce)
	enum { IDD = IDD_SETTINGS_DIVORCE };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
  CFrameBG    m_Frame3;
  CFrameBG    m_Frame4;
  CXButtonXP  m_rbOnePage;
  CXButtonXP  m_rbTwoPages;
  CXButtonXP  m_rbOnePageB;
	CEraEdit	  m_Seria;
	CEraEdit    m_NoChildren;
  CEraEdit    m_SingleChild;
	CXButtonXP  m_chkCitizenshipAct;
	CXButtonXP  m_chkCitizenshipCert;
	CXButtonXP  m_chkDistrictOther;
	//}}AFX_DATA

  CBitmap       m_ActBitmap;
  CStatic       m_ActImage;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageDivorce)
	public:
	virtual void OnOK();
	protected:
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage();
	afx_msg void OnOnePageB();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageDivorce)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageChange dialog
class CPropertyPageChange : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageChange)

// Construction
public:
	CPropertyPageChange();
	~CPropertyPageChange();

// Dialog Data
	//{{AFX_DATA(CPropertyPageChange)
	enum { IDD = IDD_SETTINGS_CHANGE };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
  CXButtonXP  m_rbOnePage;
  CXButtonXP  m_rbTwoPages;
  CXButtonXP  m_rbOnePageB;
	CEraEdit	  m_Seria;
	CXButtonXP  m_chkCitizenshipAct;
	CXButtonXP  m_chkCitizenshipCert;
	CXButtonXP  m_chkDistrictOther;
	//}}AFX_DATA

  CBitmap       m_ActBitmap;
  CStatic       m_ActImage;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageChange)
	public:
	virtual void OnOK();
	protected:
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage();
	afx_msg void OnOnePageB();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageChange)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageDeath dialog
class CPropertyPageDeath : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageDeath)

// Construction
public:
	CPropertyPageDeath();
	~CPropertyPageDeath();

// Dialog Data
	//{{AFX_DATA(CPropertyPageDeath)
	enum { IDD = IDD_SETTINGS_DEATH };
  CFrameBG    m_Frame1;
  CFrameBG    m_Frame2;
  CFrameBG    m_Frame3;
  CXButtonXP  m_rbOnePage;
  CXButtonXP  m_rbTwoPages;
  CXButtonXP  m_rbOnePageB;
	CEraEdit	  m_Seria;
	CXButtonXP  m_chkCitizenshipAct;
	CXButtonXP  m_chkCitizenshipCert;
	CXButtonXP  m_chkDistrictOther;
  CEraEdit	  m_DefNotice;
	//}}AFX_DATA

  CBitmap       m_ActBitmap;
  CStatic       m_ActImage;
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageDeath)
	public:
	virtual void OnOK();
	protected:
	afx_msg void OnOnePage();
	afx_msg void OnTwoPage();
	afx_msg void OnOnePageB();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageDeath)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageThemes dialog
class CPropertyPageThemes : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageThemes)
// Construction
public:
	CPropertyPageThemes();
  ~CPropertyPageThemes();

// Dialog Data
	//{{AFX_DATA(CPropertyPageThemes)
	enum { IDD = IDD_SETTINGS_APPEARANCE };
  CFrameBG         m_Frame1;
  CFrameBG         m_Frame2;
  CXButtonXP       m_chkGradient;
  CXButtonXP       m_rbStandart;
  CXButtonXP       m_rdSilver;
  CXButtonXP       m_rdSummer;
  CXButtonXP       m_rdRevolution;
  CXButtonXP       m_rdTranquil;
  CXButtonXP       m_rdAlpine;
  CColourPicker    m_ColourBoxLeft;
  CColourPicker    m_ColourBoxRight;
	//}}AFX_DATA
  CTCImageList  m_RadioIL;
  CTCImageList  m_CheckBoxIL;
  COLORREF      m_clrLeft;
  COLORREF      m_clrRight;
  BOOL          m_fUseGradient, m_fUseGradientSaved;
  BOOL          m_fColorChanged;
  BOOL          m_fFontChanged;
  CFont         m_Font;

// Operations
private:
  void  ShowSamplesBox(LOGFONT* pLogFont);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageThemes)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageThemes)
	afx_msg void OnRadioStandart();
	afx_msg void OnRadioSilver();
	afx_msg void OnRadioAlpine();
	afx_msg void OnRadioRevolution();
	afx_msg void OnRadioSummer();
	afx_msg void OnRadioTranquil();
	afx_msg void OnColourPicker();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckUseGradient();
	afx_msg void OnFont();
	//}}AFX_MSG
  afx_msg LONG OnSelEndOK(UINT lParam, LONG wParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageArchive dialog
class CPropertyPageArchive : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageArchive)
// Construction
public:
	CPropertyPageArchive();
  ~CPropertyPageArchive();

// Dialog Data
	//{{AFX_DATA(CPropertyPageArchive)
	enum { IDD = IDD_SETTINGS_ARCHIVE };
  CFrameBG         m_Frame1;
  CXButtonXP       m_rbNever;
  CXButtonXP       m_rbMonday;
  CXButtonXP       m_rbTuesday;
  CXButtonXP       m_rbWednesday;
  CXButtonXP       m_rbThursday;
  CXButtonXP       m_rbFriday;
  CXButtonXP       m_rbSaturday;
  CXButtonXP       m_rbEveryday;
	//}}AFX_DATA
  CTCImageList     m_RadioIL;
  int              m_nCheck;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageArchive)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  void OnRadio();

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageArchive)
	afx_msg void OnRadioNever();
	afx_msg void OnRadioMonday();
	afx_msg void OnRadioTuesday();
	afx_msg void OnRadioWednesday();
	afx_msg void OnRadioThursday();
	afx_msg void OnRadioFriday();
	afx_msg void OnRadioSaturday();
	afx_msg void OnRadioEveryday();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CPropertyPageOffice dialog
class CPropertyPageOffice : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageOffice)
// Construction
public:
	CPropertyPageOffice();
  ~CPropertyPageOffice();

// Dialog Data
	//{{AFX_DATA(CPropertyPageOffice)
	enum { IDD = IDD_SETTINGS_OFFICE};
	//}}AFX_DATA
  CFrameBG         m_Frame1;
  CXButtonXP       m_rdMSOffice;
  CXButtonXP       m_rdOpenOffice;
  CXButtonXP       m_rdUnderline;
  CXButtonXP       m_rdPrintSingle;
  CStatic          m_SampleImage;
  CBitmap          m_bmpSample;
  CTCImageList     m_RadioIL;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageOffice)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageOffice)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioUnderline();
	afx_msg void OnRadioPrintSingle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageUsers dialog
class CPropertyPageUsers : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageUsers)
// Construction
public:
	CPropertyPageUsers();
  ~CPropertyPageUsers();

// Dialog Data
	//{{AFX_DATA(CPropertyPageUsers)
	enum { IDD = IDD_SETTINGS_USERS};
  CListCtrl  m_Users;
  CXButtonXP m_btnAddNew;
  CXButtonXP m_btnDelete;
  CEdit      m_User;
  CEdit      m_Post;
  CEdit      m_Password1;
  CEdit      m_Password2;
	//}}AFX_DATA
  int        m_nCurUser;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageUsers)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  afx_msg void OnItemChangedUsers(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void OnChange();
  afx_msg void OnAddNew();
  afx_msg void OnDelete();
  afx_msg void OnShowPassword();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageUsers)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

*/

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageStamps dialog
class CPropertyPageStamps : public CPropertyPageBG {
	DECLARE_DYNCREATE(CPropertyPageStamps)
// Construction
public:
	CPropertyPageStamps();
  ~CPropertyPageStamps();

// Dialog Data
	//{{AFX_DATA(CPropertyPageStamps)
	enum { IDD = IDD_SETTINGS_STAMPS};
  CFrameBG   m_Frame1;
  CFrameBG   m_Frame2;
  CXButtonXP m_btnCheck1;
  CXButtonXP m_btnCheck2;
  CEraEdit   m_Edit1;
  CEraEdit   m_Edit2;
	//}}AFX_DATA
  CTCImageList  m_CheckBoxIL;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageStamps)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPropertyPageStamps)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg
class CSettingsDlg : public CPropertySheetBG {
	DECLARE_DYNAMIC(CSettingsDlg)

// Construction
public:
//	CSettingsDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSettingsDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

	CXButtonXP m_btnCancel;
	CXButtonXP m_btnOk;

  CPropertyPageCommon   m_pageCommon;
  CPropertyPageBirth    m_pageBirth;
  CPropertyPageMarriage m_pageMarriage;
  CPropertyPageDivorce  m_pageDivorce;
  CPropertyPageChange   m_pageChange;
  CPropertyPageDeath    m_pageDeath;
  CPropertyPageThemes   m_pageThemes;
  CPropertyPageArchive  m_pageArchive;
  CPropertyPageOffice   m_pageOffice;
  // CPropertyPageUsers    m_pageUsers;
  CPropertyPageStamps   m_pageStamps;
  CImageList            m_ImageList;
protected:
  BOOL       m_fYes, m_fNo;
// Operations
protected:
  void  OnYes();
  void  OnNo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingsDlg)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSettingsDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSettingsDlg)
  afx_msg BOOL OnHelpInfo(HELPINFO*);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGSDLG_H__4059E64E_548A_4168_BEAD_99B804521995__INCLUDED_)
