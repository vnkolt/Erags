// RagsInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "RagsInfoDlg.h"

#include "Defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRagsInfoDlg dialog


CRagsInfoDlg::CRagsInfoDlg(CWnd* pParent /*=NULL*/)
             :CDialogEx(CRagsInfoDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CRagsInfoDlg)
	m_szCity = _T("");
	m_szDistrict = _T("");
	m_szRegion = _T("");
	//}}AFX_DATA_INIT
}

void CRagsInfoDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRagsInfoDlg)
	DDX_Control(pDX, IDC_RTREE, m_RTree);
	DDX_Text(pDX, IDC_CITY, m_szCity);
	DDX_Text(pDX, IDC_DISTRICT, m_szDistrict);
	DDX_Text(pDX, IDC_REGION, m_szRegion);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRagsInfoDlg, CDialogEx)
	//{{AFX_MSG_MAP(CRagsInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CRagsInfoDlg message handlers
BOOL CRagsInfoDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	// TODO: Add extra initialization here
  GetDlgItem(IDC_COUNTRY)->SetWindowText( theIniCache.GetCOUNTRY() );
  GetDlgItem(IDC_REGION)->SetWindowText( theIniCache.GetREGION() );
  GetDlgItem(IDC_DISTRICT)->SetWindowText( theIniCache.GetDISTRICT() );
  GetDlgItem(IDC_CITY)->SetWindowText( theIniCache.GetCITY() );
/************************************** : by VK at 07.10.2005 22:08:38 **\
  GetDlgItem(IDC_RAGS)->SetWindowText( theIniCache.GetRAGS() );
\************************************** : by VK at 07.10.2005 22:08:40 **/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
