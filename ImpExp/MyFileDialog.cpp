// MyFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ImpExp.h"
#include "MyFileDialog.h"
#include <AtlConv.h>    // USES_CONVERSION declared here


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// IDs of controls in Explorer-style dialog, from Spy
#define ID_FILESOFTYPE		0x0441
#define ID_FILENAME			  0x0442
#define ID_LOOKIN				  0x0443

#define ID_GOTO_LAST  40971 // ������� � ��������� ������������� �����
#define ID_GOTO_UP    40961 // �� ���� ������� �����
#define ID_NEWFOLDER  40962 // �������� ����� �����
#define ID_VIEWMENU   40970 // ���� "���"

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
    case ID_GOTO_LAST : return "������� �� �������� ����������� �����"; // 40971 // ������� � ��������� ������������� �����
    case ID_GOTO_UP   : return "�� ���� ����� ������";                   // 40961 // �� ���� ������� �����
    case ID_NEWFOLDER : return "��������� ���� �����";                   // 40962 // �������� ����� �����
    case ID_VIEWMENU  : return "���� \"������\"";                         // 40970 // ���� "���"
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
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyFileDialog::DoDataExchange(CDataExchange* pDX) {
  CFileDialog::DoDataExchange(pDX);
}

BOOL CMyFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  return CFileDialog::OnNotify(wParam, lParam, pResult);
}

BOOL CMyFileDialog::OnInitDialog() {
  if ( CFileDialog::OnInitDialog() ) {
    if (m_ofn.Flags & OFN_EXPLORER) {
      SetControlText(IDOK,	          m_bOpenFileDialog ? _T("³������") : _T("��������"));
      SetControlText(IDCANCEL,        _T("³���������"));
      SetControlText(ID_LOOKIN,		    _T("�����:"));
      SetControlText(ID_FILENAME,	    _T("��'� �����:"));
      SetControlText(ID_FILESOFTYPE,	_T("��� �����:"));
      CWnd* pParentWnd = GetParent();
      if ( pParentWnd ) {
        lpfnOldFileDialogProc = (WNDPROC)GetWindowLong(pParentWnd->m_hWnd, GWL_WNDPROC);
        SetWindowLong(pParentWnd->m_hWnd, GWL_WNDPROC, (LONG)MyFileDialogProc);
      }
    }
    GetParent()->SetWindowText(m_szFileTitle);
    return TRUE;
  }
	return FALSE;//CFileDialog::OnInitDialog();
}
void CMyFileDialog::OnInitDone() {
  CFileDialog::OnInitDone();
}
int CMyFileDialog::DoModal() {
	if ( (m_ofn.Flags & OFN_EXPLORER) && m_ResourseID ) {
		// Add my custom dialog to bottom
		m_ofn.lpTemplateName = MAKEINTRESOURCE(m_ResourseID);
		m_ofn.Flags |= OFN_ENABLETEMPLATE;
	}
	return CFileDialog::DoModal();
}
