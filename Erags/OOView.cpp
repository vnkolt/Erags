// OOView.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "OOView.h"

#include "MainFrm.h"

#include "..\Common\FHelpers.h"
#include "..\Controls\EraControls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COOView

IMPLEMENT_DYNCREATE(COOView, CHtmlView)

COOView::COOView()
{
	//{{AFX_DATA_INIT(COOView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

COOView::~COOView()
{
}

void COOView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COOView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COOView, CHtmlView)
	//{{AFX_MSG_MAP(COOView)
	ON_WM_DESTROY()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateEnabledCmd)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COOView diagnostics

#ifdef _DEBUG
void COOView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void COOView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

BOOL COOView::GetOpenOfficePath(HKEY hKey, const CString& szKey, CString& szPath) {
  CString szSubkey;
  TCHAR szBuf[MAX_PATH];
  DWORD dwSize = MAX_PATH;
  DWORD dwIndex = 0;
  while ( ERROR_SUCCESS==RegEnumKeyEx(hKey, dwIndex, szBuf, &dwSize, NULL, NULL, NULL, NULL) ) {
    szSubkey.Format(_T("%s\\%s"), szKey, szBuf);
  }
  return false;
}
BOOL COOView::MakeSourcePage(LPCSTR szOOFilename) {
  CString szFilename, szContent;
  CString szSO_ActiveX_CLSID, szCodebase;

  if ( m_szURL.Find(' ', 0) >= 0 ) {
    m_szURL.Format(_T("\"%s.html\""), szOOFilename);
  }
  else {
    m_szURL.Format(_T("%s.html"), szOOFilename);
  }

  // AfxMessageBox(m_szURL);

  CLSID clsid;
  HRESULT hRes = CLSIDFromProgID(L"so_activex.SOActiveX", &clsid);
  if ( SUCCEEDED(hRes) ) {
    CString szKey;
    szSO_ActiveX_CLSID.Format(_T("%8X-%4X-%4X-%02X%02X-%02X%02X%02X%02X%02X%02X"),
                              clsid.Data1, clsid.Data2, clsid.Data3, 
                              clsid.Data4[0], clsid.Data4[1],
                              clsid.Data4[2], clsid.Data4[3],
                              clsid.Data4[4], clsid.Data4[5],
                              clsid.Data4[6], clsid.Data4[7]
                             );

    szKey.Format(_T("SOFTWARE\\Classes\\CLSID\\{%s}\\InprocServer32"), szSO_ActiveX_CLSID);

    HKEY hKey;
    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
      TCHAR  sz[MAX_PATH];
      DWORD dwSize = sizeof(sz);
      DWORD dwType = REG_SZ;
      RegQueryValueEx(hKey, NULL, NULL, &dwType, (LPBYTE)sz, &dwSize);
      szCodebase = sz;
      RegCloseKey(hKey);
    }
    else {
      false;
    }
  }
  else {
    CString szKey, szOpenOfficePath;
    HKEY hKey;
    szSO_ActiveX_CLSID = _T("67F2A879-82D5-4A6D-8CC5-FFB3C114B69D");
    szKey = _T("SOFTWARE\\OpenOffice.org");
    if( RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
      // OpenOffice.org не инсталлирован. “ребуетс€ инсталл€ци€ OpenOffice.org
      return false;
    }
    if ( false==GetOpenOfficePath(hKey, szKey, szOpenOfficePath) ) {
      RegCloseKey(hKey);
      return false;
    }
    RegCloseKey(hKey);
    return false;
  }

/*
  CRect r;
  GetClientRect(&r);
  GetParent()->ShowWindow(SW_MAXIMIZE);
  ShowWindow(SW_MAXIMIZE);
  GetClientRect(&r);
*/
  szFilename = szOOFilename;
  szFilename.Replace('\\', '/');

  szContent.Format("<HTML>\n"
                   "<HEAD>\n"
                   "<TITLE>%s</TITLE>\n"
                   "</HEAD>\n"
                   "<BODY>\n"
                   "<OBJECT CLASSID=\"clsid:%s\" width=\"100%%\" height=\"100%%\">\n"
                   //"<OBJECT CLASSID=\"clsid:%s\" width=\"%d\" height=\"%d\">\n"
                   "CODEBASE=\"%s\">"
                   "<PARAM NAME=\"src\" VALUE=\"file:///%s\">\n"
                   //"<PARAM NAME=\"readonly\" VALUE=\"false\">\n"
                   "</OBJECT>\n"
                   "</BODY>\n"
                   "</HTML>\n",
                   szFilename, szSO_ActiveX_CLSID, szCodebase, szFilename
                   // szFilename, szSO_ActiveX_CLSID, 500, 500, szCodebase, szFilename
                   );

#if _MFC_VER < 0x0800
  FILE* f = fopen(m_szURL, "w+b");
#else
  FILE* f = NULL;
  fopen_s(&f, m_szURL, "w+b");
#endif
  if ( f ) {
    fwrite((LPCTSTR)szContent, 1, szContent.GetLength(), f);
    fclose(f);
    return true;
  }
  else {
    AfxMessageBox("Cant create URL file.");
  }
  return false;
}
/////////////////////////////////////////////////////////////////////////////
// COOView message handlers
void COOView::OnInitialUpdate() {
	//TODO: This code navigates to a popular spot on the web.
	//Change the code to go where you'd like.
  theApp.m_pOOView = this;

  ((CMainFrame*)AfxGetMainWnd())->EnablePreviewBar(true);

  CDocument* pDoc = GetDocument();
  if ( pDoc ) {
    if ( MakeSourcePage(pDoc->GetPathName()) ) {
  	  Navigate2(m_szURL,NULL,NULL);
    }
  }
}

void COOView::OnNavigateComplete2(LPCTSTR strURL) {
	// TODO: Add your specialized code here and/or call the base class
	CHtmlView::OnNavigateComplete2(strURL);
  // DeleteFile(m_szURL);

/*
  CWnd* pWnd = this;
  CString szText;
  while ( pWnd ) {
    pWnd->GetWindowText(szText);
    pWnd->ShowWindow(SW_MAXIMIZE);
    pWnd = pWnd->GetWindow(GW_CHILD);
  }
*/
}
void COOView::OnDestroy() {
  theApp.m_pOOView = NULL;
	CHtmlView::OnDestroy();
  ((CMainFrame*)AfxGetMainWnd())->EnablePreviewBar(false);
}

void COOView::OnUpdateEnabledCmd(CCmdUI* pCmdUI)  {
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(true);
}

HWND COOView::FindSaltSubFrame(HWND hParent) {
  HWND hFound = NULL;
  HWND hWnd = ::GetWindow(hParent, GW_CHILD);
  while ( hWnd ) {
    hFound = ::FindWindowEx(hWnd, NULL, _T("SALTMPSUBFRAME"), NULL);
    if ( hFound ) {
      return hFound;
    }
    hFound = FindSaltSubFrame(hWnd);
    if ( hFound ) {
      return hFound;
    }
    hWnd = ::GetWindow(hWnd, GW_HWNDNEXT);
  }
  return NULL;
}
void COOView::OnFileSaveAs() {
  HWND hWnd = FindSaltSubFrame(m_hWnd);
  if ( hWnd ) {
    SendKeys('S', VK_CONTROL, VK_SHIFT);
  }
}
void COOView::OnFilePrint() {
  HWND hWnd = FindSaltSubFrame(m_hWnd);
  if ( hWnd ) {
    // ::ShowWindow(hWnd, SW_MAXIMIZE);
    SendKeys('P', VK_CONTROL);
  }
}
