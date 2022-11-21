// Div23.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "Div23.h"

#include "Defaults.h"
#include "RNames.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_RagsTo;
extern CString g_sMSurname_OV, g_sWSurname_OV;
extern CString g_sMName_OV, g_sWName_OV;
extern CString g_sMPatronymic_OV, g_sWPatronymic_OV;
/////////////////////////////////////////////////////////////////////////////
// CDiv23 dialog


CDiv23::CDiv23(CWnd* pParent /*=NULL*/)
       :CDialogEx(CDiv23::IDD, pParent) {
	//{{AFX_DATA_INIT(CDiv23)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDiv23::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiv23)
	DDX_Control(pDX, IDC_TORAGS, m_TORAGS);
	DDX_Control(pDX, IDC_MSURNAME, m_MSURNAME);
	DDX_Control(pDX, IDC_MPATRONYMIC, m_MPATRONYMIC);
	DDX_Control(pDX, IDC_MNAME, m_MNAME);
	DDX_Control(pDX, IDC_WSURNAME, m_WSURNAME);
	DDX_Control(pDX, IDC_WPATRONYMIC, m_WPATRONYMIC);
	DDX_Control(pDX, IDC_WNAME, m_WNAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiv23, CDialogEx)
	//{{AFX_MSG_MAP(CDiv23)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiv23 message handlers
BOOL CDiv23::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  m_MSURNAME.SetWindowText( ManSurname_OV(m_sMSurname) );
  m_MNAME.SetWindowText( ManName_OV(m_sMName) );
  m_MPATRONYMIC.SetWindowText( ManFather_OV(m_sMPatronymic) );

  m_WSURNAME.SetWindowText( WomanSurname_OV(m_sWSurname) );
  m_WNAME.SetWindowText( WomanName_OV(m_sWName) );
  m_WPATRONYMIC.SetWindowText( WomanFather_OV(m_sWPatronymic) );

  CString sTo = m_sToRags;
  if ( theIniCache.IsChildRags( m_sToRags ) ) {
    sTo = theIniCache.GetParent();
  }
  else if ( theIniCache.IsVyconcom(m_sToRags) ) {
    sTo = theIniCache.GetVyconcomParent(m_sToRags);
  }

  sTo = SVRagsC( sTo, RC_RV );
  m_TORAGS.SetWindowText( sTo );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDiv23::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  m_TORAGS.GetWindowText( g_RagsTo );

  m_MSURNAME.GetWindowText(g_sMSurname_OV);
  m_WSURNAME.GetWindowText(g_sWSurname_OV);
  m_MNAME.GetWindowText( g_sMName_OV );
  m_WNAME.GetWindowText( g_sWName_OV );
  m_MPATRONYMIC.GetWindowText( g_sMPatronymic_OV );
  m_WPATRONYMIC.GetWindowText( g_sWPatronymic_OV );

/************************************** : by VK at 09.02.2004 4:35:36 **\
  m_Surname.GetWindowText( g_SurnameTo );
  m_Name.GetWindowText( g_NameTo );
  m_Patronymic.GetWindowText( g_PatronymicTo );
\************************************** : by VK at 09.02.2004 4:35:38 **/
	EndDialog(IDYES);
}

BOOL CDiv23::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
