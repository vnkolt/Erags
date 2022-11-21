// MyFileDialog.cpp : implementation file
//

#include "stdafx.h"

#if defined(_ERAGS)
#include "..\Erags\Erags.h"
#include "..\Erags\Defaults.h"
#elif defined(_ERAABC)
#include "..\EraABC\EraABC.h"
#elif defined(_ER2XML)
#include "..\Era2Xml\Era2Xml.h"
#endif

#include "MyFileDialog.h"

#include "..\Common\CyrString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// IDs of controls in Explorer-style dialog, from Spy
#define ID_FILESOFTYPE		0x0441
#define ID_FILENAME			  0x0442
#define ID_LOOKIN				  0x0443

#define ID_GOTO_LAST  40971 // Переход к последней просмотренной папке
#define ID_GOTO_UP    40961 // На один уровень вверх
#define ID_NEWFOLDER  40962 // Создание новой папки
#define ID_VIEWMENU   40970 // Меню "Вид"

#define ID_FILE_OPEN_DLG_FILENAME   0x480

CString RemoveLeftDigits(const CString s) {
  CString sRet = s;
  int nLen = sRet.GetLength();
  for(int i(0); i < nLen; i++ ) {
    TCHAR c = sRet[i];
    if ( isdigit(c) ) {
      sRet.SetAt(i, TCHAR(' '));
    }
    else if ( TCHAR(' ') == c )
      break;
  }
  sRet.TrimLeft();
  return sRet;
}

LPTSTR GetMyFDTT(UINT id) {
  switch(id) {
    case ID_GOTO_LAST : return "Перехід до останньої переглянутої папки"; // 40971 // Переход к последней просмотренной папке
    case ID_GOTO_UP   : return "На один рівень нагору";                   // 40961 // На один уровень вверх
    case ID_NEWFOLDER : return "Створення нової папки";                   // 40962 // Создание новой папки
    case ID_VIEWMENU  : return "Меню \"Вигляд\"";                         // 40970 // Меню "Вид"
  }
  return "";
}

WNDPROC lpfnOldFileDialogProc;
LRESULT CALLBACK PASCAL MyFileDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LONG lParam) {
  if ( WM_NOTIFY==msg ) {
    LPNMHDR pnmh = (LPNMHDR)lParam; 
    switch( pnmh->code ) {
      case TTN_NEEDTEXTA: {
          TOOLTIPTEXTA *pTTTA = (TOOLTIPTEXTA*)lParam;
          strcpy(pTTTA->szText, GetMyFDTT(pnmh->idFrom));
          return 0;
        }
        break;
      case TTN_NEEDTEXTW: {
          TOOLTIPTEXTW *pTTTW = (TOOLTIPTEXTW*)lParam;
          USES_CONVERSION;
          wcscpy(pTTTW->szText, T2OLE(GetMyFDTT(pnmh->idFrom)));
          return 0;
        }
        break;
    }
  }
  return CallWindowProc(lpfnOldFileDialogProc, hWnd, msg, wParam, lParam);
}


/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd) {
  m_ResourseID = 0;
  m_fEnableTemplate = TRUE;
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
  ON_EN_CHANGE(IDC_YEAR, OnYearChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyFileDialog::DoDataExchange(CDataExchange* pDX) {
  CFileDialog::DoDataExchange(pDX);
  if ( m_fEnableTemplate && IDD_FILE_NEW==m_ResourseID ) {
    DDX_Control(pDX, IDC_YEAR, m_Year);
    DDX_Control(pDX, IDC_YEAR_SPIN, m_YearSpin);
  }
}

BOOL CMyFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  return CFileDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CMyFileDialog::OnInitDialog() {
  if ( CFileDialog::OnInitDialog() ) {
    if (m_ofn.Flags & OFN_EXPLORER) {
      LPCTSTR szOkBtnText = m_bOpenFileDialog ? _T("Відкрити") : _T("Записати");
      if ( IDD_FILE_NEW==m_ResourseID ) {
        szOkBtnText = _T("Створити");
      }
      // SetControlText(IDOK,	          m_bOpenFileDialog ? _T("Відкрити") : _T("Записати"));
      SetControlText(IDOK,	szOkBtnText);
      SetControlText(IDCANCEL,        _T("Відмовитись"));
      SetControlText(ID_LOOKIN,		    _T("Папка:"));
      SetControlText(ID_FILENAME,	    _T("Ім'я файлу:"));
      SetControlText(ID_FILESOFTYPE,	_T("Тип файлів:"));
      CWnd* pParentWnd = GetParent();
      if ( pParentWnd ) {
        lpfnOldFileDialogProc = (WNDPROC)GetWindowLong(pParentWnd->m_hWnd, GWL_WNDPROC);
        SetWindowLong(pParentWnd->m_hWnd, GWL_WNDPROC, (LONG)MyFileDialogProc);
      }
    }
    GetParent()->SetWindowText(m_szFileTitle);

    if ( m_fEnableTemplate ) {
      switch(m_ResourseID) {
        case IDD_FILE_NEW: {
            COleDateTime odt = COleDateTime::GetCurrentTime();
            CString sYear;
            sYear.Format(_T("%04d"), odt.GetYear() + ((odt.GetMonth()==12) ? 1 : 0) );
            m_YearSpin.SetRange(1800, 9999);
            m_YearSpin.SetBuddy(&m_Year);
            GetDlgItem(IDC_YEAR)->SetWindowText(sYear);
            OnYearChange();
          }
          break;
      }
    }
    return TRUE;
  }
	return FALSE;//CFileDialog::OnInitDialog();
}
void CMyFileDialog::OnYearChange() {
  CString s, sYear;
  try {
    CWnd* pParent = GetParent();
    GetDlgItem(IDC_YEAR)->GetWindowText(sYear);
    pParent->GetDlgItem(ID_FILE_OPEN_DLG_FILENAME)->GetWindowText(s);
    s = RemoveLeftDigits(s);
    if ( s.IsEmpty() ) {
      #if defined(_ERAGS)
        s = theIniCache.GetRAGS();
      #elif defined(_ERAABC)
        s = theApp.m_szRagsName;
      #endif
        s.Replace(_T("І"), _T("I")); s.Replace(_T("і"), _T("i"));
        s.Replace(_T("  "), _T(" "));
        m_sFileName.Format(_T("%s %s.er3"), Trim(sYear), Trim(s));
    }
    else {
      s.Replace(_T("І"), _T("I")); s.Replace(_T("і"), _T("i"));
      m_sFileName.Format(_T("%s %s"), Trim(sYear), Trim(s));
      if ( m_sFileName.Right(4).CompareNoCase(".er3") != 0 )
        m_sFileName += _T(".er3");
    }
    pParent->GetDlgItem(ID_FILE_OPEN_DLG_FILENAME)->SetWindowText(m_sFileName);
  }
  catch(...) {
  }
}
void CMyFileDialog::OnInitDone() {
  CFileDialog::OnInitDone();
  if ( m_fEnableTemplate && IDD_FILE_NEW==m_ResourseID ) {
    m_Year.SetLimitText(4);
    PostMessage(WM_COMMAND, MAKEWPARAM(IDC_YEAR, EN_CHANGE), (LPARAM)GetDlgItem(IDC_YEAR)->m_hWnd);
  }
}
int CMyFileDialog::DoModal() {
	if ( (m_ofn.Flags & OFN_EXPLORER) && m_ResourseID ) {
		// Add my custom dialog to bottom
		m_ofn.lpTemplateName = MAKEINTRESOURCE(m_ResourseID);
		m_ofn.Flags |= OFN_ENABLETEMPLATE;
	}
	return CFileDialog::DoModal();
}
