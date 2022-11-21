// ChekDateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "EraForm.h"
#include "CheckDateDlg.h"

#include "DateFunc.h"
#include "..\Controls\EraEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCheckDateDlg dialog


CCheckDateDlg::CCheckDateDlg(CWnd* pParent /*=NULL*/)
          	:CDialogEx(CCheckDateDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CCheckDateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_RadioID = IDC_RADIO2;
}


void CCheckDateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCheckDateDlg)
	DDX_Control(pDX, IDC_RADIO1, m_Radio1);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCheckDateDlg, CDialogEx)
	//{{AFX_MSG_MAP(CCheckDateDlg)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckDateDlg message handlers
BOOL CCheckDateDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_Radio1.SetRadioImageList(&m_RadioIL); m_Radio1.SetRadio(IDC_RADIO1, IDC_RADIO2);
    m_Radio2.SetRadioImageList(&m_RadioIL); m_Radio2.SetRadio(IDC_RADIO1, IDC_RADIO2);
  }

  CString s;
  s.Format(_T("Перейти до редагування дати %s"), m_szNameBefore);
  GetDlgItem(IDC_RADIO1)->SetWindowText(s);
  s.Format(_T("Перейти до редагування дати %s"), m_szNameAfter);
  GetDlgItem(IDC_RADIO2)->SetWindowText(s);
  GetDlgItem(IDNO)->ShowWindow(SW_HIDE);
  GetDlgItem(IDC_MESSAGE)->SetWindowText(m_szMessage);

  m_Font.CreateFont(-12, 0, 0, 0, 
		                FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));

  GetDlgItem(IDC_WHAT_TODO)->SetFont(&m_Font);
//  GetDlgItem(IDC_ATTICON)->ShowWindow(SW_SHOW);
  CheckRadioButton(IDC_RADIO1, IDC_RADIO2, m_RadioID);
  SetFocus();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CCheckDateDlg::OnRadio1() {
	// TODO: Add your control notification handler code here
  m_RadioID = IDC_RADIO1;
}

void CCheckDateDlg::OnRadio2() {
	// TODO: Add your control notification handler code here
  m_RadioID = IDC_RADIO2;
}

BOOL CheckDates(CEraDateEdit* pBefore, LPCTSTR szNameBefore, CEraDateEdit* pAfter, LPCTSTR szNameAfter, BOOL fBeforeDef) {
 
  if ( theApp.m_fExitApp )
    return TRUE;

  COleDateTime DateBefore = pBefore->GetDate();
  COleDateTime DateAfter  = pAfter->GetDate();

  if ( DateBefore.GetStatus()!=COleDateTime::valid || DateAfter.GetStatus()!=COleDateTime::valid )
    return TRUE;

  if ( !IsFocusChild(pBefore->GetParent()) )
    return TRUE;

  static int inbody = 0;
  if ( inbody )
    return TRUE;

  inbody++;
  BOOL fRet = TRUE;
  if ( DateBefore > DateAfter ) {
    CCheckDateDlg dlg(pBefore->GetParent());
    if ( fBeforeDef ) {
      dlg.m_szMessage.Format(_T("Ви намагаєтесь визначити дату %s %s у той час, як ")
                             _T("дата %s визначена як %s\n")
                             _T("Таким чином, дата %s більше, ніж дата %s."),
                             szNameBefore, GetDateDDMMYYYYr(DateBefore),
                             szNameAfter, GetDateDDMMYYYYr(DateAfter),
                             szNameBefore, szNameAfter);
    }
    else {
      dlg.m_szMessage.Format(_T("Ви намагаєтесь визначити дату %s %s у той час, як ")
                             _T("дата %s визначена як %s\n")
                             _T("Таким чином, дата %s менше, ніж дата %s."),
                             szNameAfter, GetDateDDMMYYYYr(DateAfter),
                             szNameBefore, GetDateDDMMYYYYr(DateBefore),
                             szNameAfter, szNameBefore);
    }
    dlg.m_szNameBefore = szNameBefore;
    dlg.m_szNameAfter  = szNameAfter;
    dlg.m_RadioID = fBeforeDef ? IDC_RADIO1 : IDC_RADIO2;
    dlg.DoModal();

    if (IDC_RADIO1==dlg.m_RadioID) {
      pBefore->SetFocus();
    }
    else {
      pAfter->SetFocus();
    }
    fRet = FALSE;
  }
  inbody--;

  return fRet;
}
