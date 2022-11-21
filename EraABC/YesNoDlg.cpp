// YesNoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "YesNoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYesNoDlg dialog


CYesNoDlg::CYesNoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CYesNoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYesNoDlg)
	m_sMessage = _T("");
	m_sQuestion = _T("");
	//}}AFX_DATA_INIT
}


void CYesNoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYesNoDlg)
	DDX_Text(pDX, IDC_YNMESSAGE, m_sMessage);
	DDX_Text(pDX, IDC_YNQUESTION, m_sQuestion);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CYesNoDlg, CDialogEx)
	//{{AFX_MSG_MAP(CYesNoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYesNoDlg message handlers
BOOL CYesNoDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	if ( m_sMessage.IsEmpty() )
    GetDlgItem(IDC_YNMESSAGE)->ShowWindow(SW_HIDE);
  if ( m_sQuestion.IsEmpty() )
    GetDlgItem(IDC_YNQUESTION)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// YNDlg function
BOOL PASCAL EXPORT YNDlg(CWnd* pParent, LPCTSTR szMessage, LPCTSTR szQuestion){
  CYesNoDlg dlg(pParent);
	dlg.m_sMessage = szMessage;
	dlg.m_sQuestion = szQuestion;

	int iDlg = dlg.DoModal();

  return ( IDOK==iDlg || IDYES==iDlg);
}

BOOL PASCAL EXPORT YNDlg(CWnd* pParent, UINT uMessageID, UINT uQuestionID) {
  CYesNoDlg dlg(pParent);
	dlg.m_sMessage.LoadString(uMessageID);
	dlg.m_sQuestion.LoadString(uQuestionID);

	int iDlg = dlg.DoModal();

  return ( IDOK==iDlg || IDYES==iDlg);
}