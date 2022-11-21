// Dlg43.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "Dlg43.h"

#include "Defaults.h"

#include "..\Common\CyrString.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString CDlg43::m_sTo;
CString CDlg43::m_sNumber;

extern CString g_sFullBabyNameRV;
/////////////////////////////////////////////////////////////////////////////
// CDlg43 dialog
CDlg43::CDlg43(int nDoc, CWnd* pParent /*=NULL*/)
	     :CDialogEx(CDlg43::IDD, pParent) {
	//{{AFX_DATA_INIT(CDlg43)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_nDoc = nDoc;
  m_fSex = TRUE;
}


void CDlg43::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg43)
	DDX_Control(pDX, IDC_D43_TO, m_To);
	DDX_Control(pDX, IDC_D43_NUMBER, m_Number);
  DDX_Control(pDX, IDC_D43_ABOUT, m_About);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg43, CDialogEx)
	//{{AFX_MSG_MAP(CDlg43)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg43 message handlers

BOOL CDlg43::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString sSurname    = GetTokSpace(m_sTo, 0),
          sName       = GetTokSpace(m_sTo, 1),
          sPatronymic = GetTokSpace(m_sTo, 2);

  if ( sPatronymic.GetLength()>0 && sPatronymic.Right(1)==_T("ч") ) {
    m_sTo = MakeFIO(ManSurname_DV(sSurname), ManName_DV(sName), ManFather_DV(sPatronymic));
  }
  else {
    m_sTo = MakeFIO(WomanSurname_DV(sSurname), WomanName_DV(sName), WomanFather_DV(sPatronymic));
  }

  CString sCaption = _T("Якщо потрібно, виправте інформацію для довідки про ");

  m_To.SetWindowText( m_sTo );
  switch( m_nDoc ) {
    case 41:
      m_Number.SetWindowText(theIniCache.GetNext41Num());
      sCaption += _T("народження");
      break;
    case 42:
      m_Number.SetWindowText(theIniCache.GetNext42Num());
      sCaption += _T("народження");
      GetDlgItem(IDC_LBL_ABOUT)->ShowWindow(SW_SHOW);
      GetDlgItem(IDC_D43_ABOUT)->ShowWindow(SW_SHOW);

      sSurname    = GetTokSpace(g_sFullBabyNameRV, 0),
      sName       = GetTokSpace(g_sFullBabyNameRV, 1),
      sPatronymic = GetTokSpace(g_sFullBabyNameRV, 2);
      if ( m_fSex )
        g_sFullBabyNameRV = MakeFIO(ManSurname_RV(sSurname), ManName_RV(sName), ManFather_RV(sPatronymic));
      else
        g_sFullBabyNameRV = MakeFIO(WomanSurname_RV(sSurname), WomanName_RV(sName), WomanFather_RV(sPatronymic));
      m_About.SetWindowText(g_sFullBabyNameRV);
      GetDlgItem(IDC_LBL_ABOUT)->SetWindowText(_T("про народження"));
      break;
    case 43:
      m_Number.SetWindowText(theIniCache.GetNext43Num());
      sCaption += _T("смерть");
      break;
  }
  SetWindowText(sCaption);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg43::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);
  
  switch( m_nDoc ) {
    case 41:
      m_sTo     = m_To.GetText();
      m_sNumber = m_Number.GetText();
      theIniCache.Set41Num( m_sNumber );
      break;
    case 42:
      m_sTo     = m_To.GetText();
      m_sNumber = m_Number.GetText();
      g_sFullBabyNameRV  = m_About.GetText();
      theIniCache.Set42Num( m_sNumber );
      break;
    case 43:
      m_sTo     = m_To.GetText();
      m_sNumber = m_Number.GetText();
      theIniCache.Set43Num( m_sNumber );
      break;
  }
  EndDialog(IDYES);	
}

BOOL CDlg43::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
