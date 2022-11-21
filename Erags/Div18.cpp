// Div18.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "Div18.h"
#include "Defaults.h"
#include "RNames.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_SurnameTo;
extern CString g_NameTo;
extern CString g_PatronymicTo;
extern CString g_RagsTo;
extern BOOL    g_fDivorceDocSex;

/////////////////////////////////////////////////////////////////////////////
// CDiv18 dialog
CDiv18::CDiv18(CWnd* pParent /*=NULL*/, BOOL fSex/*=FALSE*/)
       :CDialogEx(CDiv18::IDD, pParent) {
	//{{AFX_DATA_INIT(CDiv18)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fSex = fSex;
}


void CDiv18::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiv18)
	DDX_Control(pDX, IDC_TORAGS, m_ToRags);
	DDX_Control(pDX, IDC_SURNAME_TO, m_Surname);
	DDX_Control(pDX, IDC_NAME_TO, m_Name);
	DDX_Control(pDX, IDC_PATRONYMIC_TO, m_Patronymic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiv18, CDialogEx)
	//{{AFX_MSG_MAP(CDiv18)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiv18 message handlers
BOOL CDiv18::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  g_fDivorceDocSex = m_fSex;
  if ( m_fSex ) {
    m_Surname.SetWindowText( ManSurname_ZV(m_sSurname) );
    m_Name.SetWindowText(  ManName_ZV(m_sName) );
    m_Patronymic.SetWindowText( ManFather_ZV(m_sPatronymic) );
  }
  else {
    m_Surname.SetWindowText( WomanSurname_ZV(m_sSurname) );
    m_Name.SetWindowText(  WomanName_ZV(m_sName) );
    m_Patronymic.SetWindowText( WomanFather_ZV(m_sPatronymic) );
  }
  CString sTo = m_sToRags;
  if ( theIniCache.IsChildRags( m_sToRags ) ) {
    sTo = theIniCache.GetParent();
  }
  else if ( theIniCache.IsVyconcom(m_sToRags) ) {
    sTo = theIniCache.GetVyconcomParent(m_sToRags);
  }

  sTo = SVRagsC( sTo, RC_RV );
  m_ToRags.SetWindowText( sTo );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiv18::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);

  m_ToRags.GetWindowText( g_RagsTo );
  m_Surname.GetWindowText( g_SurnameTo );
  m_Name.GetWindowText( g_NameTo );
  m_Patronymic.GetWindowText( g_PatronymicTo );

	EndDialog(IDYES);
}

BOOL CDiv18::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
