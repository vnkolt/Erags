// UnzipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "UnzipDlg.h"

#include "..\ZipArchive\ZipArchive.h"
#include "..\ZipArchive\Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog
CUnzipDlg::CUnzipDlg(CWnd* pParent /*=NULL*/) : CDialog(CUnzipDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CUnzipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CUnzipDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnzipDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUnzipDlg, CDialog)
	//{{AFX_MSG_MAP(CUnzipDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg message handlers
BOOL CUnzipDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
  CenterWindow();
  ShowWindow(SW_SHOW);

  int berr = 0;
  int nCount = 0, i;
  CZipArchive zip;
  DWORD dwTotalSize = 0;
  try {
    zip.Open(theApp.m_szSourceZip, CZipArchive::zipOpenReadOnly);
    nCount = zip.GetCount();
    m_Progress.SetRange32(0, nCount);
    for( i = 0; i < nCount; i++ ) {
      CZipFileHeader fh;
      zip.GetFileInfo(fh, (WORD)i);
      zip.ExtractFile((WORD)i, theApp.m_szUnzipFolder);
      m_Progress.OffsetPos(1);
    }
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

  try {
    zip.Close();
  }
	catch (CException* e) {
		e->Delete();
		berr = true;
	}

  EndDialog(IDOK);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
