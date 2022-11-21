// BanksDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "BanksDlg.h"
#include "Defaults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_BANKS 20

/////////////////////////////////////////////////////////////////////////////
// CBanksDlg dialog
BEGIN_MESSAGE_MAP(CBanksDlg, CDialogEx)
	//{{AFX_MSG_MAP(CBanksDlg)
	ON_BN_CLICKED(IDYES, OnYes)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBanksDlg::CBanksDlg(CWnd* pParent /*=NULL*/):CDialogEx(CBanksDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CBanksDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBanksDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBanksDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
  DDX_GridControl(pDX, IDC_GRID, m_Grid);
}

/////////////////////////////////////////////////////////////////////////////
// CBanksDlg message handlers
BOOL CBanksDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	m_Grid.SetColumnCount(2);
  m_Grid.SetFixedColumnCount(1);
  m_Grid.SetRowCount(MAX_BANKS+1);
  m_Grid.SetFixedRowCount(1);
  m_Grid.SetColumnWidth(0, 22);
  m_Grid.SetColumnWidth(1, 560);
  m_Grid.SetItemText(0, 0, _T("№"));
  m_Grid.SetItemText(0, 1, _T("Назва фінансової установи"));
  for( int i(1); i < MAX_BANKS+1; i++ ) {
    CString s, sKey, sValue;
    s.Format(_T("%d"), i);
    m_Grid.SetItemText(i, 0, s);
    sKey.Format(_T("%02d"), i);
    sValue = theIniCache.GetSVal(_T("Banks"), sKey, _T(""));
    m_Grid.SetItemText(i, 1, sValue);
  }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBanksDlg::OnYes() {
  UpdateData(TRUE);
  for( int row(1); row < MAX_BANKS+1; row++ ) {
    CString sKey, sValue;
    sKey.Format(_T("%02d"), row);
    sValue = m_Grid.GetItemText(row, 1);
    if ( !sValue.IsEmpty() )
      theIniCache.SetSVal(_T("Banks"), sKey, sValue);
  }
  theIniCache.FillBanks();
  EndDialog(IDYES);
}

BOOL CBanksDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("Lists"), _T("#Banks"));
  return TRUE;
}