// MenuPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraSetup.h"
#include "MenuPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuPage dialog
CMenuPage::CMenuPage(CWnd* pParent /*=NULL*/)
	: CNewWizPage(CMenuPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMenuPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMenuPage::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMenuPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMenuPage, CNewWizPage)
	//{{AFX_MSG_MAP(CMenuPage)
	ON_BN_CLICKED(IDC_RADIO_UKR, OnRadioUkr)
	ON_BN_CLICKED(IDC_RADIO_RUS, OnRadioRus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuPage message handlers
BOOL CMenuPage::OnInitDialog() {
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here
  CheckRadioButton(IDC_RADIO_UKR, IDC_RADIO_RUS, IDC_RADIO_UKR);
  theApp.m_HelpLang = IDC_RADIO_UKR;

  GetDlgItem(IDC_WELCOME)->SetFont(&theApp.m_Font);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMenuPage::OnRadioUkr() {
	// TODO: Add your control notification handler code here
	theApp.m_HelpLang = IDC_RADIO_UKR;
}

void CMenuPage::OnRadioRus() {
	// TODO: Add your control notification handler code here
	theApp.m_HelpLang = IDC_RADIO_RUS;
}
