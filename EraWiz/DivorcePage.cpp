// DivorcePage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "DivorcePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString ReadFromDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
void WriteToDefaults(CDaoRecordset* prs, LPCTSTR szSect, LPCTSTR szKey, LPCTSTR szDefVal);
/////////////////////////////////////////////////////////////////////////////
// CDivorcePage dialog
CDivorcePage::CDivorcePage(CWnd* pParent /*=NULL*/)
	           :CNewWizPage(CDivorcePage::IDD, pParent) {
	//{{AFX_DATA_INIT(CDivorcePage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDivorcePage::DoDataExchange(CDataExchange* pDX)
{
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDivorcePage)
	DDX_Control(pDX, IDC_SERIA_DEATH, m_edtSeriaDeath);
	DDX_Control(pDX, IDC_SERIA_CHANGE, m_edtSeriaChange);
	DDX_Control(pDX, IDC_SERIA_DIVORCE, m_edtSeriaDivorce);
	DDX_Control(pDX, IDC_SINGLECHILD, m_edtSingleChild);
	DDX_Control(pDX, IDC_NOCHILDREN, m_edtNoChildren);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDivorcePage, CNewWizPage)
	//{{AFX_MSG_MAP(CDivorcePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDivorcePage message handlers

BOOL CDivorcePage::OnInitDialog() {
	CNewWizPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Font.CreateFont(-12, 0, 0, 0, 
		FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

	GetDlgItem(IDC_TITLE1)->SetFont(&m_Font, TRUE);
	GetDlgItem(IDC_TITLE2)->SetFont(&m_Font, TRUE);
	GetDlgItem(IDC_TITLE3)->SetFont(&m_Font, TRUE);

  LPCTSTR szSeria = GetCertSeria();

  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");

      s = ReadFromDefaults(&rs, _T("DIVORCE_FORM"), _T("SERIA"), szSeria);
      m_edtSeriaDivorce.SetWindowText(s);

      s = ReadFromDefaults(&rs, _T("DIVORCE_FORM"), _T("NOCHILDREN"), _T("Немає."));
      m_edtNoChildren.SetWindowText(s);

      s = ReadFromDefaults(&rs, _T("DIVORCE_FORM"), _T("SINGLECHILD"), _T("Одна дитина."));
      m_edtSingleChild.SetWindowText(s);

      s = ReadFromDefaults(&rs, _T("CHANGE_FORM"), _T("SERIA"), szSeria);
      m_edtSeriaChange.SetWindowText(s);

      s = ReadFromDefaults(&rs, _T("DEATH_FORM"), _T("SERIA"), szSeria);
      m_edtSeriaDeath.SetWindowText(s);

      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CDivorcePage::OnWizardNext() {
  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      CString s;
      rs.Open(dbOpenTable, "[DEFAULTS]");

      m_edtSeriaDivorce.GetWindowText(s);
      WriteToDefaults(&rs, _T("DIVORCE_FORM"), _T("SERIA"), s);

      m_edtNoChildren.GetWindowText(s);
      WriteToDefaults(&rs, _T("DIVORCE_FORM"), _T("NOCHILDREN"), s);

      m_edtSingleChild.GetWindowText(s);
      WriteToDefaults(&rs, _T("DIVORCE_FORM"), _T("SINGLECHILD"), s);

      m_edtSeriaChange.GetWindowText(s);
      WriteToDefaults(&rs, _T("CHANGE_FORM"), _T("SERIA"), s);

      m_edtSeriaDeath.GetWindowText(s);
      WriteToDefaults(&rs, _T("DEATH_FORM"), _T("SERIA"), s);

      rs.Close();
    }
    catch (CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
  	}
  }
  return CNewWizPage::OnWizardNext();
}