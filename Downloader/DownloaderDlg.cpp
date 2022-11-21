
// DownloaderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Downloader.h"
#include "DownloaderDlg.h"
#include "RegReader.h"
#include "semail.h"

#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"

#include <Winhttp.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LC_NAME     0
#define LC_DATETIME 1
#define LC_SIZE     2

BOOL PeekAndPump() {
  static MSG msg;
  while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
    if (!AfxGetApp()->PumpMessage()) {
      ::PostQuitMessage(0);
      return false;
    }
  }
  return true;
}



// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog {
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/*
void TimetToFileTime( time_t t, LPFILETIME pft ) {
  LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
  pft->dwLowDateTime = (DWORD) ll;
  pft->dwHighDateTime = ll >>32;
}
*/

// CDownloaderDlg dialog


CDownloaderDlg::CDownloaderDlg(FIArray* pFIArray, CWnd* pParent /*=NULL*/)
	             :CDialog(CDownloaderDlg::IDD, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_pFIArray = pFIArray;
  m_DownloadSize = m_cbDownloaded = 0;
}

void CDownloaderDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_FILES, m_FileList);
  DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}

BEGIN_MESSAGE_MAP(CDownloaderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
  ON_BN_CLICKED(IDOK, &CDownloaderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CDownloaderDlg message handlers
BOOL CDownloaderDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
  ListView_SetExtendedListViewStyle(m_FileList.m_hWnd, LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES);

  m_FileList.InsertColumn(LC_NAME     , _T("Ім'я файлу")    , LVCFMT_LEFT , 260);
  m_FileList.InsertColumn(LC_DATETIME , _T("Дата/Час")      , LVCFMT_LEFT , 120);
  m_FileList.InsertColumn(LC_SIZE     , _T("Розмір (байт)") , LVCFMT_RIGHT, 100);
  int nFiles = m_pFIArray->GetSize();
  int nItem = 0;
  for( int i(0); i < nFiles; i++ ) {
    SFileInfo& fi = m_pFIArray->GetAt(i);
    if ( fi.fDownload ) {
      CString s;
      m_FileList.InsertItem(nItem, fi.szFilename);

      // FILETIME ft;
      // TimetToFileTime(fi.lUnixFileTime, &ft);
      // COleDateTime odt( (time_t)fi.lUnixFileTime );
      COleDateTime odt( fi.ft );
      s.Format(_T("%02d.%02d.%04d %02d:%02d:%02d"),
               odt.GetDay(), odt.GetMonth(), odt.GetYear(),
               odt.GetHour(), odt.GetMinute(), odt.GetSecond()
              );
      m_FileList.SetItemText(nItem, LC_DATETIME, s);

      s.Format(_T("%lu"), fi.dwFilesize);
      m_FileList.SetItemText(nItem, LC_SIZE, s);

      m_DownloadSize += fi.dwFilesize;
      fi.nItem = nItem;
      nItem++;
    }
  }

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDownloaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CDownloaderDlg::OnPaint() {
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDownloaderDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDownloaderDlg::Download(LPCTSTR szServer, LPCTSTR szUrl, LPCTSTR szTarget, FILETIME& ft, DWORD dwFilesize) {
	//Variables 
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPBYTE pszOutBuffer;
	BOOL  bResults = false;

  CComBSTR bstrServer(szServer);
  CComBSTR bstrUrl(szUrl);

  HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;
	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen( L"PKErags Downloader/1.0", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
	// Specify an HTTP server.
  if (hSession)
    hConnect = WinHttpConnect( hSession, bstrServer /*L"sites.google.com"*/, INTERNET_DEFAULT_HTTP_PORT, 0);

  // Create an HTTP request handle.
	if (hConnect)
		hRequest = WinHttpOpenRequest( hConnect, L"GET", bstrUrl/*L"/site/pkerags/Files/FileInfo.txt"*/, NULL, WINHTTP_NO_REFERER, NULL, NULL);

	// Send a request.
  if (hRequest) {
		bResults = WinHttpSendRequest( hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
  }
	// End the request.
	if (bResults)    
		bResults = WinHttpReceiveResponse( hRequest, NULL );/**/
	// Keep checking for data until there is nothing left.
  if (bResults) {
  	HANDLE hFile = CreateFile(szTarget, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if ( INVALID_HANDLE_VALUE != hFile ) {
  		do {
	  		// Check for available data.
		  	dwSize = 0;        
        if (!WinHttpQueryDataAvailable( hRequest, &dwSize)) {
				  ; // printf( "Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
        }
	  		// Allocate space for the buffer.       
		  	pszOutBuffer = new byte[dwSize+1];
			  if (!pszOutBuffer) {
				  // printf("Out of memory\n");
          bResults = false;
	  			dwSize = 0;
		  	}
			  else {       
  				// Read the Data.
	  			ZeroMemory(pszOutBuffer, dwSize+1);
		  		if (!WinHttpReadData( hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded)) {
			  		; // printf( "Error %u in WinHttpReadData.\n", GetLastError());
				  }
  				else {
	  				//printf("%s", pszOutBuffer);
		  			DWORD wmWritten = 0;
			  		BOOL fWrite = WriteFile(hFile, pszOutBuffer, dwSize, &wmWritten, NULL);
				  	int n = GetLastError();
            m_cbDownloaded += wmWritten;
            m_Progress.SetPos(m_cbDownloaded);
            PeekAndPump();
				  }
				  // Free the memory allocated to the buffer.
				  delete [] pszOutBuffer;
			  }
		  } while (dwSize>0);
      SetFileTime(hFile, &ft, NULL, &ft);
		  CloseHandle(hFile);
      bResults = (m_cbDownloaded==dwFilesize);
    }
  }
  // Report any errors.
/*
  if (!bResults) {
    // return false
  }
*/
  // Close any open handles.
  if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
  return bResults;
}

CString GetServerFromUrl(const CString& szUrl) {
  CString szServer;
  int nLength = szUrl.GetLength();
  int nFound = szUrl.Find(_T("//"));
  if ( nFound >=0 ) {
    nFound += 2;
  }
  while ( nFound < nLength ) {
    TCHAR c = szUrl.GetAt(nFound);
    if ( c=='/' ) {
      break;
    }
    szServer += c;
    nFound++;
  }
  return szServer;
}

CString GetSubUrlFromFullUrl(const CString& szUrl) {
  CString sz;
  int nFound = szUrl.Find(_T("//"));
  if ( nFound >=0 ) {
    nFound += 2;
  }
  nFound = szUrl.Find('/', nFound);
  if ( nFound >= 0 ) {
    sz = szUrl.Mid(nFound);
  }
  return sz;
}

void CDownloaderDlg::OnBnClickedOk() {
  // TODO: Add your control notification handler code here
  m_Progress.ShowWindow(SW_SHOW);

  m_Progress.SetRange32(0, (int)m_DownloadSize);

  int nDownloads = 0;
  int nFiles = m_pFIArray->GetSize();

  for( int i(0); i < nFiles; i++ ) {
    SFileInfo& fi = m_pFIArray->GetAt(i);
    if ( fi.fDownload ) {
      CString szServer, szUrl, szFilePath, szDownloadPath;
      szServer = GetServerFromUrl(fi.szUrl);
      szUrl    = GetSubUrlFromFullUrl(fi.szUrl);
      szFilePath.Format(_T("%s\\%s"), theApp.m_szDownloadPath, fi.szFilename);
      szDownloadPath = GetFilePath(szFilePath);
      if ( CreateFileFolder(szDownloadPath) ) {
        if ( Download(szServer, szUrl, szFilePath, fi.ft, fi.dwFilesize) ) {
          m_FileList.SetCheck(fi.nItem, true);
          PeekAndPump();
          nDownloads++;
        }
      }
    }
  }
#ifdef _DEBUG
  nDownloads = 13;
#endif

  CRegReader rr;
  if ( rr.OpenKey() ) {
    CStringArray sa;
    sa.Add( _T("DB") ); sa[0].AppendFormat(_T(": %s\r\n"), rr.GetDatabase());
    sa.Add( _T("VO") ); sa[1].AppendFormat(_T(": %s\r\n"), rr.GetValidOwner());
    sa.Add( _T("RT") ); sa[2].AppendFormat(_T(": %s\r\n"), rr.GetRegTimerData());
    rr.CloseKey();
    bool fResult = sendemail(sa);
  }

  if ( nDownloads==nFiles ) {
    CString szUpdater;
    szUpdater.Format(_T("%s\\Updater.zip"), theApp.m_szDownloadPath);
    if ( FileExists(szUpdater) ) {
      int berr = 0;
      CZipArchive zip;
      COptions    zoptions;
      do {
        try {
          zip.Open(szUpdater, CZipArchive::zipOpen, zoptions.m_bTdComp ? 1 : 0 );
          berr = 0;
        }
        catch (CZipException* e) {
    			if (e->m_iCause == CZipException::cdirNotFound)
	    			berr = -1;
		    	else
			    	berr = 1;
			    e->Delete();
        }
    		catch (CException* e) {
	  		  e->Delete();
		  	  berr = 1;
        }
  		  // thrown in the STL version
  		  catch (CZipException e) {
	  		  if (e.m_iCause == CZipException::cdirNotFound)
		  		  berr = -1;
  		  	else
	  		  	berr = 1;
  		  }
  	  	catch(...) {
	  		  berr = 1;
		    }
		    if (berr == -1) {
			    if (AfxMessageBox(_T("The central directory was not found. If you're opening a multi-disk archive, make sure you have inserted the last disk. Retry?"), MB_ICONSTOP|MB_YESNO) == IDNO)
  				  berr = 1;
	  		  else
		  		  zip.Close(true);
		    }

		    if (berr == 1) {
			    AfxMessageBox(_T("Помилка при спробі відкрити архівний файл."), MB_ICONSTOP);
			    return;
		    }
      } while (berr == -1);
      CZipFileHeader fh;
      int iCount = zip.GetCount();
      for (int i = 0; i < iCount; i++) {
        CString szExctractPath;
        zip.GetFileInfo(fh, (WORD)i);
        CString szFilename = (LPCTSTR)fh.GetFileName();
        BOOL fSuccess = zip.ExtractFile(i, theApp.m_szTargetFilePath, true);
        int j = i;
      }
    }
    // Email
    
    // End

  }
  OnOK();
}
