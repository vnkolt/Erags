// Dlg27.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "Dlg27.h"

#include "Caches.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_Declarant;
extern CString g_ChangeAddr;
extern CString g_ChangePrImPb;
extern CString g_OldPrImPb, g_NewPrImPb;

/////////////////////////////////////////////////////////////////////////////
// CDlg27 dialog
CDlg27::CDlg27(CWnd* pParent /*=NULL*/)
    	 :CDialogEx(CDlg27::IDD, pParent) {
	//{{AFX_DATA_INIT(CDlg27)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_fSex = FALSE;
}


void CDlg27::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg27)
	DDX_Control(pDX, IDC_OLDSURNAME, m_OldSurname);
	DDX_Control(pDX, IDC_OLDPATRONYMIC, m_OldPatronymic);
	DDX_Control(pDX, IDC_OLDNAME, m_OldName);
	DDX_Control(pDX, IDC_NEWSURNAME, m_NewSurname);
	DDX_Control(pDX, IDC_NEWPATRONYMIC, m_NewPatronymic);
	DDX_Control(pDX, IDC_NEWNAME, m_NewName);
	DDX_Control(pDX, IDC_ADDRESS, m_Address);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg27, CDialogEx)
	//{{AFX_MSG_MAP(CDlg27)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg27 message handlers
BOOL CDlg27::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here

  m_OldSurname.SetWindowText( m_sOldSurname );
  m_NewSurname.SetWindowText( m_sNewSurname );
  theMNames.FillCombo( m_OldName, m_sOldName, FALSE );
  theMNames.FillCombo( m_NewName, m_sNewName, FALSE );
  theMPatronymics.FillCombo( m_OldPatronymic, m_sOldPatronymic, FALSE );
  theMPatronymics.FillCombo( m_NewPatronymic, m_sNewPatronymic, FALSE );
	m_Address.SetWindowText( m_sAddress );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg27::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);

  m_Address.GetWindowText(g_ChangeAddr);

  CString s;

  m_sOldSurname = Trim(m_OldSurname.GetText());
  m_sNewSurname = Trim(m_NewSurname.GetText());

  m_sOldName = Trim(m_OldName.GetCurText());
  m_sNewName = Trim(m_NewName.GetCurText());

  m_sOldPatronymic = Trim(m_OldPatronymic.GetCurText());
  m_sNewPatronymic = Trim(m_NewPatronymic.GetCurText());

  g_Declarant = MakeFIO(m_sOldSurname, m_sOldName, m_sOldPatronymic);

  g_OldPrImPb.Empty();
  g_NewPrImPb.Empty();

  if ( m_sOldSurname != m_sNewSurname ) {
    s = _T("прізвища");
    g_OldPrImPb = m_sOldSurname;
    g_NewPrImPb = m_sNewSurname;
  }
  if ( m_sOldName != m_sNewName ) {
    if ( !s.IsEmpty() ) {
      s += _T(", ");
      g_OldPrImPb += _T(", ");
      g_NewPrImPb += _T(", ");
    }
    s += _T("імені");
    g_OldPrImPb += m_sOldName;
    g_NewPrImPb += m_sNewName;
  }
  if ( m_sOldPatronymic != m_sNewPatronymic ) {
    if ( !s.IsEmpty() ) {
      s += _T(", ");
      g_OldPrImPb += _T(", ");
      g_NewPrImPb += _T(", ");
    }
    s += _T("по батькові");
    g_OldPrImPb += m_sOldPatronymic;
    g_NewPrImPb += m_sNewPatronymic;
  }
  g_ChangePrImPb = s;

	EndDialog(IDYES);
}

BOOL CDlg27::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
