// AgreementPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "AgreementPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgreementPage dialog
CAgreementPage::CAgreementPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CAgreementPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgreementPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAgreementPage::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgreementPage)
	DDX_Control(pDX, IDC_AGREEMENT, m_reAgreement);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgreementPage, CNewWizPage)
	//{{AFX_MSG_MAP(CAgreementPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgreementPage message handlers

BOOL CAgreementPage::OnInitDialog() 
{
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here

//  CRect r;
//  m_Frame.GetWindowRect(&r);
//  ScreenToClient(&r);
//  m_reAgreement.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_BORDER|WS_TABSTOP|ES_LEFT|ES_MULTILINE/*|ES_NOHIDESEL*/, r, this, IDC_AGREEMENT);

  HRSRC hResource = FindResource(NULL, MAKEINTRESOURCE(IDR_EULA), _T("RTF"));
  if ( hResource ) {
  	HGLOBAL hResData = LoadResource(NULL, hResource);
    if ( hResData ) {
      CString sRTF((char*)hResData);
      int nLen = sRTF.GetLength();
      m_reAgreement.SetRTF(sRTF);
      m_reAgreement.SetFocus();
    }
  	FreeResource(hResData);
  }
  #ifdef _DEBUG
    CheckDlgButton(IDC_AGREE, TRUE);
  #endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CAgreementPage::OnWizardNext() {
  if (IsDlgButtonChecked(IDC_AGREE)) {
    return 0;
  }
  MessageBox(_T("Ви повинні погодитися з умовами Угоди, щоб продовжити установку ПК ЕРАГС."),
             _T("Попередження"), MB_OK|MB_ICONWARNING
            );
  return -1;
}
