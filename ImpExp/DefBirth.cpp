// DefBirth.cpp : implementation file
//

#include "stdafx.h"
#include "ImpExp.h"
#include "DefBirth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString sCHILD_BP_COUNTRY;
CString sCHILD_BP_REGION;
CString sCHILD_BP_DISTRICT;
CString sCHILD_BP_CITY;

/////////////////////////////////////////////////////////////////////////////
// CDefBirth dialog


CDefBirth::CDefBirth(CWnd* pParent /*=NULL*/)
	: CDialog(CDefBirth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDefBirth)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDefBirth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDefBirth)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDefBirth, CDialog)
	//{{AFX_MSG_MAP(CDefBirth)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDefBirth message handlers

void CDefBirth::OnOK() {
	// TODO: Add extra validation here
  GetDlgItem(IDC_COUNTRY)->GetWindowText(sCHILD_BP_COUNTRY);
  GetDlgItem(IDC_REGION)->GetWindowText(sCHILD_BP_REGION);
  GetDlgItem(IDC_CITY)->GetWindowText(sCHILD_BP_CITY);
  GetDlgItem(IDC_DISTRICT)->GetWindowText(sCHILD_BP_DISTRICT);
	CDialog::OnOK();
}

BOOL CDefBirth::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  GetDlgItem(IDC_EDIT1)->SetWindowText(_T("Визначте, будь ласка, місце народження за умовченням для актових записів про НАРОДЖЕННЯ. У базі даних старого формату місцем народження, якщо воно не було зазначено явно, вважалося географічне місце відділу реєстрації. Після назви населенного пункту обов'язково повинен бути вказан його тип: м. (місто), с-ще (селище), смт (селище мыського типу) або с. (село), наприклад:\r\n")
                                       _T("Світлодарськ м.\r\n")
                                       _T("Великоновосілківка смт"));

  GetDlgItem(IDC_COUNTRY)->SetWindowText(sCHILD_BP_COUNTRY);
  GetDlgItem(IDC_REGION)->SetWindowText(sCHILD_BP_REGION);
  GetDlgItem(IDC_CITY)->SetWindowText(sCHILD_BP_CITY);
  GetDlgItem(IDC_DISTRICT)->SetWindowText(sCHILD_BP_DISTRICT);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
