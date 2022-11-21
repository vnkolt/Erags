// SetDefDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "SetDefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDefDlg dialog
CSetDefDlg::CSetDefDlg(CWnd* pParent /*=NULL*/)
           :CDialogEx(CSetDefDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CSetDefDlg)
	m_DontShow = FALSE;
	//}}AFX_DATA_INIT
}


void CSetDefDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDefDlg)
  DDX_Control(pDX, IDC_DONTSHOW, m_CheckBox);
	DDX_Check(pDX, IDC_DONTSHOW, m_DontShow);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSetDefDlg, CDialogEx)
	//{{AFX_MSG_MAP(CSetDefDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDefDlg message handlers
BOOL CSetDefDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_CheckBox.SetCheckBoxImageList(&m_CheckBoxIL);
  }

	m_DontShow = FALSE;
  GetDlgItem(IDC_MSGTEXT)->SetWindowText(m_Text);
  GetDlgItem(IDYES)->SetFocus();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CallSetDefDlg(CWnd* pParent, LPCTSTR szSection, LPCTSTR szShowValue, LPCTSTR szYesNoValue, LPCTSTR szMsg) {
  BOOL fShow = theApp.GetProfileInt(szSection, szShowValue, TRUE);
  int nDlgResult = theApp.GetProfileInt(szSection, szYesNoValue, IDYES);
  if ( FALSE==fShow )
    return nDlgResult;
  CSetDefDlg dlg(pParent);
  dlg.m_Text = szMsg;
  nDlgResult = dlg.DoModal(); 
  if ( dlg.m_DontShow ) {
    theApp.WriteProfileInt(szSection, szShowValue, FALSE);
    theApp.WriteProfileInt(szSection, szYesNoValue, nDlgResult);
  }
  return nDlgResult;
}


