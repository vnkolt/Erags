// Defaults.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "Erags.h"

#include "UnivalsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

extern CString g_sIniFileName;


extern "C" SHORT PASCAL EXPORT IniDlg(LPCTSTR lpCountry,
                                      LPCTSTR lpRegion,
                                      LPCTSTR lpCity,
                                      LPCTSTR lpDistrict) {

  AFX_MANAGE_STATE(AfxGetStaticModuleState());

  CUnivalsDlg dlg;
  dlg.m_sCountry = lpCountry;
  dlg.m_sRegion = lpRegion;
  if(dlg.m_sRegion.Right(1) == _T("א"))
    dlg.m_sRegion += _T(" מבכ.");
  dlg.m_sCity = lpCity;
  if(dlg.m_sRegion.GetLength()>=0)
    dlg.m_sCity = _T("ל. ") + dlg.m_sCity;
  dlg.m_sDistrict = lpDistrict;
  if(dlg.m_sDistrict.Right(1) == _T("י"))
    dlg.m_sDistrict += _T(" נאימם");
  return (SHORT)(dlg.DoModal()==IDOK);
}
