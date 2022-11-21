// AddRsnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "AddRsnDlg.h"

#include "DataManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_PSEUDO_LEN  16

bool AddReason(const CString& sPseudo, const CString& sCause) {
  LPCTSTR szSQL = _T("SELECT PSEUDONYM, CAUSE FROM CausesOfDeath");
  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    rs.Open(dbOpenDynaset, szSQL);
    if ( rs.CanAppend() ) {
      rs.AddNew();
      rs.SetFieldValue(0, (LPCTSTR)sPseudo);
      rs.SetFieldValue(1, (LPCTSTR)sCause);
      rs.Update();
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
    return false;
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////
// CAddRsnDlg dialog


CAddRsnDlg::CAddRsnDlg(CWnd* pParent /*=NULL*/)
        	 :CDialogEx(CAddRsnDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CAddRsnDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CAddRsnDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRsnDlg)
	DDX_Control(pDX, IDC_PSEUDO, m_Pseudo);
	DDX_Control(pDX, IDC_DEATH_REASON, m_Reason);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRsnDlg, CDialogEx)
	//{{AFX_MSG_MAP(CAddRsnDlg)
	ON_EN_CHANGE(IDC_PSEUDO, OnChangePseudo)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddRsnDlg message handlers
void CAddRsnDlg::OnChangePseudo() {
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
  GetDlgItem(IDYES)->EnableWindow( !m_Pseudo.IsEmpty() );
  	
}

BOOL CAddRsnDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  m_Pseudo.SetLimitText(MAX_PSEUDO_LEN);
  m_Reason.SetWindowText(m_sReason);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CAddRsnDlg::OnYes() {
  UpdateData(TRUE);
	m_Pseudo.GetWindowText(m_sPseudo);
  m_Reason.GetWindowText(m_sReason);

  m_sPseudo = Trim(m_sPseudo);
  m_sReason = Trim(m_sReason);
  if ( !m_sPseudo.IsEmpty() && !m_sReason.IsEmpty() ) {
    AddReason(m_sPseudo, m_sReason);
  }
  EndDialog(IDYES);
}
