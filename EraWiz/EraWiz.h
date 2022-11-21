// EraWiz.h : main header file for the ERAWIZ DLL
//

#if !defined(AFX_ERAWIZ_H__4FD614C4_A489_44E2_86B1_EB3DC4128884__INCLUDED_)
#define AFX_ERAWIZ_H__4FD614C4_A489_44E2_86B1_EB3DC4128884__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define WM_SETRAGSLIST_ALL    (WM_USER+10)
#define WM_SETRAGSLIST_CITY   (WM_USER+20)
#define WM_SETRAGSLIST_REGION (WM_USER+30)

struct UKRREGION {
  COLORREF  clr;
  UINT      RegionEmblemID;
  UINT      CityEmblemID;
  LPCTSTR   szCity;
  LPCTSTR   szRegion;
  long      m_RListRegionID;
};

extern CString g_szRagsName;
extern CString g_szFullRagsName;
extern CString g_szRegion;
extern CString g_szDistrict;
extern CString g_szCity;
extern CString g_szCityType;
extern CString g_szParentRags;
extern CString g_szBoss;
extern CString g_szByUMVS;
extern CString g_szToUMVS;
extern CString g_szByMil;
extern CString g_szToMil;
extern CString g_szToTax;
extern CString g_szByCourt;

extern CString g_szBirthRegion;
extern CString g_szBirthDistrict;
extern CString g_szBirthCity;
extern CString g_szBirthCityType;
extern UINT    g_BirthCountryCheck;
extern UINT    g_BirthRegionCheck;
extern UINT    g_BirthDistrictCheck;
extern UINT    g_BirthCityCheck;

extern long    g_RegionID;
extern long    g_DistrictID;
extern long    g_CityID;

/////////////////////////////////////////////////////////////////////////////
// CEraWizApp
// See EraWiz.cpp for the implementation of this class
//

class CEraWizApp : public CWinApp
{
public:
	CEraWizApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEraWizApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CEraWizApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CEraWizApp   theApp;
extern CDaoDatabase theDatabase;

LPCTSTR GetCertSeria();
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERAWIZ_H__4FD614C4_A489_44E2_86B1_EB3DC4128884__INCLUDED_)
