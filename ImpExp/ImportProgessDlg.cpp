// ImportProgessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImpExp.h"
#include "ImportProgessDlg.h"

#include "EraToEr3.h" // Импорт из БД старого формата
#include "Er3ToEr3.h" // Импорт из БД нового формата

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImportProgessDlg dialog


CImportProgessDlg::CImportProgessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportProgessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportProgessDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nImportedRecords = 0;
  m_fCanClose = false;
}

void CImportProgessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportProgessDlg)
	DDX_Control(pDX, IDC_MESSAGE_LIST, m_MessageList);
	DDX_Control(pDX, IDC_TOTAL_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_INFOBOX, m_InfoBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportProgessDlg, CDialog)
	//{{AFX_MSG_MAP(CImportProgessDlg)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportProgessDlg message handlers
BOOL CImportProgessDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CenterWindow();
  ShowWindow(SW_SHOW);
  m_ImageList.Create(IDIL_MESSAGES, 16, 0, RGB(0xFF, 0, 0xFF));

  m_MessageList.InsertColumn(0, _T("Повідомлення")    , LVCFMT_LEFT,500);
  m_MessageList.SetImageList(&m_ImageList, LVSIL_SMALL);
	
  g_pMessageList = &m_MessageList;
  g_pProgress    = &m_Progress;
  g_pInfoBox     = &m_InfoBox;

  g_pImportProgessDlg = this;
  m_fCanClose = false;

  PumpMessages();

  if ( g_TargetDB.IsOpen() ) {
    if (      OpenNewDB(g_SourceDB, g_szSourceFile) ) { // БД-источник в новом формате?
      m_nImportedRecords = ImportFromEr3();
      g_SourceDB.Close();
    }
    else if ( OpenOldDB(g_SourceDB, g_szSourceFile) ) { // БД-источник в старом формате?
      m_nImportedRecords = ImportFromEra();
      g_SourceDB.Close();
    }
    else {
      CString s;
      s.Format(_T("Формат файла \"%s\" не відповідає умовам імпорту."), g_szSourceFile);
      OnMessage(MT_ERROR, s);
    }
    g_TargetDB.Close();
  }
  m_fCanClose = true;
  GetDlgItem(IDOK)->EnableWindow(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportProgessDlg::PumpMessages() {
    // Must call Create() before using the dialog
    ASSERT(m_hWnd!=NULL);

    MSG msg;
    // Handle dialog messages
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if(!IsDialogMessage(&msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);  
      }
    }
}

void CImportProgessDlg::OnClose() {
	// TODO: Add your message handler code here and/or call default
	if ( m_fCanClose )  {
	  CDialog::OnClose();
  }
}
