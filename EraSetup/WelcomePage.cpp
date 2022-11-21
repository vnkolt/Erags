// WelcomePage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "WelcomePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage dialog


CWelcomePage::CWelcomePage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CWelcomePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWelcomePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWelcomePage::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWelcomePage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWelcomePage, CNewWizPage)
	//{{AFX_MSG_MAP(CWelcomePage)
	ON_BN_CLICKED(IDC_RADIO_UKR, OnRadioUkr)
	ON_BN_CLICKED(IDC_RADIO_RUS, OnRadioRus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWelcomePage message handlers
BOOL CWelcomePage::OnInitDialog() {
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here
  CheckRadioButton(IDC_RADIO_UKR, IDC_RADIO_RUS, IDC_RADIO_UKR);
  theApp.m_HelpLang = IDC_RADIO_UKR;

  GetDlgItem(IDC_WELCOME)->SetFont(&theApp.m_Font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWelcomePage::OnRadioUkr() {
	// TODO: Add your control notification handler code here
	theApp.m_HelpLang = IDC_RADIO_UKR;
}

void CWelcomePage::OnRadioRus() {
	// TODO: Add your control notification handler code here
	theApp.m_HelpLang = IDC_RADIO_RUS;
}
