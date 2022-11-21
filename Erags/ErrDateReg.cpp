// ErrDateReg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "ErrDateReg.h"
#include "DataManager.h"

#include "Defaults.h"
#include "EraForm.h"
#include "FormMarriage.h"

#include "..\Controls\EraControls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrDateReg dialog


CErrDateReg::CErrDateReg(CWnd* pParent /*=NULL*/)
	          :CDialogEx(CErrDateReg::IDD, pParent) {
	//{{AFX_DATA_INIT(CErrDateReg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CErrDateReg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrDateReg)
  DDX_Control(pDX, IDC_CURDB, m_ErrMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CErrDateReg, CDialogEx)
	//{{AFX_MSG_MAP(CErrDateReg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrDateReg message handlers
BOOL CErrDateReg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString s;
  s.Format(_T("У поточному файлі бази даних повинні буди дані за %d рік,\n")
           _T("а Ви намагаєтесь вказати в даті реєстрації %d рік."),
           theDataManager.m_Year, m_ErrYear);
  GetDlgItem(IDC_CURDB)->SetWindowText(s);
/*
  CenterWindow();
  GetParent()->ShowWindow(SW_SHOW);
  ShowWindow(SW_SHOW);
  InvalidateRect(NULL);
  PumpMessages();
*/

/*
  CRect rcYes;
  m_btnOk.GetWindowRect(&rcYes);
  ScreenToClient(rcYes);
  CPoint p( (rcYes.left + rcYes.right)/2, (rcYes.top + rcYes.bottom)/2 );
  SendMessage(WM_MOUSEMOVE, (WPARAM)0, MAKELPARAM(p.x, p.y) );
*/
  
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CheckDateReg(CEraForm* pForm, CEraDateEdit* pDateEdit, BOOL fNewRecord) {
  if ( theApp.m_fExitApp || -1==theDataManager.m_Year )
    return TRUE;
  COleDateTime odt = pDateEdit->GetDate();
  if ( odt.GetStatus()!=COleDateTime::valid)
    return TRUE;
  int checkYear = odt.GetYear();
  CEraForm* pParent = (CEraForm*)pDateEdit->GetParent();
  CWnd* pFocus = CWnd::GetFocus();
  if ( pFocus && pFocus->GetParent()!=pParent )
    return TRUE;
  static int inbody = 0;
  if ( inbody )
    return TRUE;
  inbody++;
  BOOL fRet = TRUE;
  if ( !pParent->IsKindOf(RUNTIME_CLASS(CFormMarriage)) ) {
    if ( odt > COleDateTime::GetCurrentTime() ) {
      pForm->HideTooltip();
      pDateEdit->GetParent()->MessageBox(_T("Увага, ця дата ще не наступила."), _T("Помилка"), MB_OK|MB_ICONWARNING);
      fRet = FALSE;
    }
  }
  if ( fRet && checkYear != theDataManager.m_Year ) {
    pForm->HideTooltip();
    CErrDateReg dlg(AfxGetMainWnd());//(pDateEdit->GetParent());
    dlg.m_ErrYear = checkYear;
    if (IDYES==dlg.DoModal() ) {
      fRet = FALSE;
    }
  }

#ifndef FREE_LICENCE
  if ( LK_INVALID_LICENCE==g_LKeyResult && fNewRecord ) {
    theIniCache.SetDateCount(odt);
  }
#endif // FREE_LICENCE
  if ( pFocus )
    pFocus->SetFocus();
  inbody--;
  return fRet;
}
