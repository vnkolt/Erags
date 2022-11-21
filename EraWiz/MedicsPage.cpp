// MedicsPage.cpp : implementation file
//

#include "stdafx.h"
#include "EraWiz.h"
#include "MedicsPage.h"

#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDaoDatabase theDatabase;
/////////////////////////////////////////////////////////////////////////////
// CMedicsPage dialog
CMedicsPage::CMedicsPage(CWnd* pParent /*=NULL*/)
          	:CNewWizPage(CMedicsPage::IDD, pParent) {
	//{{AFX_DATA_INIT(CMedicsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CMedicsPage::DoDataExchange(CDataExchange* pDX) {
	CNewWizPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedicsPage)
  for( int i(0); i < MAX_MEDCONTROLS; i++ ) {
  	DDX_Control(pDX, IDC_PSEUDO1+i, m_Pseudo[i]);
	  DDX_Control(pDX, IDC_HOSPITAL1+i, m_Hospital[i]);
  }
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedicsPage, CNewWizPage)
	//{{AFX_MSG_MAP(CMedicsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedicsPage message handlers
BOOL CMedicsPage::OnInitDialog() {
	CNewWizPage::OnInitDialog();

	// TODO: Add extra initialization here
  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      rs.Open(dbOpenTable, _T("[Hospitals]"));
      int nControl = 0;
      while ( FALSE==rs.IsEOF() ) {
        CString sPseudo   = GetFieldString(&rs, _T("PSEUDO")),
                sHospital = GetFieldString(&rs, _T("HOSPITAL"));
        if ( FALSE==sPseudo.IsEmpty() && FALSE==sHospital.IsEmpty() ) {
          m_Pseudo[nControl].SetWindowText(sPseudo);
          m_Hospital[nControl].SetWindowText(sHospital);
          if ( ++nControl==MAX_MEDCONTROLS ) {
            break;
          }
        }
        rs.MoveNext();
      }
    }
    catch(CDaoException* e) {
      e->ReportError();
      e->Delete();
    }
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMedicsPage::OnSetActive() {
}

LRESULT CMedicsPage::OnWizardNext() {

  if ( theDatabase.IsOpen() ) {
    CDaoRecordset rs(&theDatabase); 
    try {
      rs.Open(dbOpenDynaset, _T("SELECT PSEUDO, HOSPITAL FROM Hospitals"));
      //rs.Open(dbOpenTable, "[Hospitals]");
      for ( int i(0); i < MAX_MEDCONTROLS; i++ ) {
        CString sPseudo, sHospital;
        m_Pseudo[i]  .GetWindowText(sPseudo);
        m_Hospital[i].GetWindowText(sHospital);
        if ( FALSE==sPseudo.IsEmpty() && FALSE==sHospital.IsEmpty() ) {
          try {
            CString szFilter;
            szFilter.Format(_T("PSEUDO='%s'"), sPseudo);
            if ( rs.FindFirst(szFilter) ) {
              rs.Edit();
              rs.SetFieldValue(0, (LPCTSTR)sPseudo);
              rs.SetFieldValue(1, (LPCTSTR)sHospital);
              rs.Update();
            }
            else {
              rs.AddNew();
              rs.SetFieldValue(0, (LPCTSTR)sPseudo);
              rs.SetFieldValue(1, (LPCTSTR)sHospital);
              rs.Update();
            }
          }
          catch(CDaoException* e) {
            #ifdef _DEBUG
            e->ReportError();
            #endif
            e->Delete();
          }
        }
      }
      rs.Close();
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
      e->ReportError();
      #endif
      e->Delete();
    }
	}
  
  return CNewWizPage::OnWizardNext();
}
BOOL CMedicsPage::OnWizardFinish() {
  OnWizardNext();
  return CNewWizPage::OnWizardFinish();
}