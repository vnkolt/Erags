// PassportsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "PassportsDlg.h"

#include "Caches.h"
#include "Defaults.h"
#include "RSBirthes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassportsDlg dialog


CPassportsDlg::CPassportsDlg(CRSBirthes*         pSet,
                             CEraEdit*           pWndMemo,
                             CEraPassportButton* pWndType1,
                             CEraSeriaEdit*      pWndSeria1,
                             CEraEdit*           pWndNumber1,
                             CEraDateEdit*       pWndDate1,
                             CEraComboBox*       pWndBy1,
                             CWnd*               pParent /*=NULL*/)
            	:CDialogEx(CPassportsDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CPassportsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pSet        = pSet;
  m_pWndMemo    = pWndMemo;
  m_pWndType1   = pWndType1;
  m_pWndSeria1  = pWndSeria1;
  m_pWndNumber1 = pWndNumber1;
  m_pWndDate1   = pWndDate1;
  m_pWndBy1     = pWndBy1;
  m_date1       = m_pWndDate1->GetDate();
  m_date2       = COleDateTime::GetCurrentTime();
}

void CPassportsDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassportsDlg)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_TYPE1, m_Type1);
	DDX_Control(pDX, IDC_TYPE2, m_Type2);
	DDX_Control(pDX, IDC_SERIA1, m_Seria1);
	DDX_Control(pDX, IDC_SERIA2, m_Seria2);
	DDX_Control(pDX, IDC_NUMBER1, m_Number1);
	DDX_Control(pDX, IDC_NUMBER2, m_Number2);
	DDX_Control(pDX, IDC_DATE1, m_Date1);
	DDX_Control(pDX, IDC_DATE2, m_Date2);
	DDX_Control(pDX, IDC_BY1, m_By1);
	DDX_Control(pDX, IDC_BY2, m_By2);
	DDX_Control(pDX, IDC_EXTNOTICE, m_ExtNotice);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPassportsDlg, CDialogEx)
	//{{AFX_MSG_MAP(CPassportsDlg)
	ON_BN_CLICKED(IDC_TYPE2, OnAll2)
	ON_EN_CHANGE(IDC_SERIA2, OnAll2)
	ON_EN_CHANGE(IDC_NUMBER2, OnAll2)
	ON_EN_CHANGE(IDC_DATE2, OnAll2)
	ON_CBN_SELCHANGE(IDC_BY2, OnAll2)
	ON_CBN_SELENDOK(IDC_BY2, OnAll2)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassportsDlg message handlers

BOOL CPassportsDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here

  m_Type1.SetIndex( m_pWndType1->GetIndex() );
  m_Seria1.SetWindowText( m_pWndSeria1->GetText() );
  m_Number1.SetWindowText( m_pWndNumber1->GetText() );
	m_Date1.SetDate( m_date1 );

  CString s = m_pWndBy1->GetCurText();
  theMIAs.FillCombo( m_By1, s );
  if ( !s.IsEmpty() )
    m_By1.SelectString(-1, s);

  theMIAs.FillCombo( m_By2, s );

  m_By1.SetDefault( theIniCache.GetByROVD() );
  m_By2.SetDefault( theIniCache.GetByROVD() );

  CString sMemo = m_pWndMemo->GetText();
  m_Type2.SetIndex( m_pSet->GetPassport2Type(sMemo) );
  m_Seria2.SetWindowText( m_pSet->GetPassport2Seria(sMemo) );
  m_Number2.SetWindowText( m_pSet->GetPassport2Number(sMemo) );
  m_Date2.SetWindowText( m_pSet->GetPassport2Date(sMemo) );

  s = m_pSet->GetPassport2By();
  if ( FALSE==s.IsEmpty() ) {
    int nIndex = m_By2.FindStringExact(-1, s);
    if ( CB_ERR==nIndex )
      nIndex = m_By2.AddString(s);
    m_By2.SetCurSel(nIndex);
  }
  
  m_ExtNotice.SetWindowText( sMemo );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPassportsDlg::OnAll2() {
  if ( false==m_Seria2.IsEmpty() && false==m_Number2.IsEmpty() ) {
    CString sMemo;
    sMemo = m_pSet->SetPassport2( m_ExtNotice.GetText(), m_Type2.GetIndex(), m_Seria2.GetText(), m_Number2.GetText(), m_Date2.GetDate(), m_By2.GetCurText() );
    m_ExtNotice.SetWindowText( sMemo );
  }
}

BOOL CPassportsDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
	switch( wCtrlId ) {
    case IDC_TYPE2:
      if ( BN_CLICKED==wNotifyCode ) {
        BOOL bRet = CDialogEx::OnCommand(wParam, lParam);
        OnAll2();
        return bRet;
      }
      break;
    case IDC_BY2:
      if ( CBN_SELCHANGE==wNotifyCode || CBN_EDITCHANGE==wNotifyCode )
        OnAll2();
      break;
  }
	
	return CDialogEx::OnCommand(wParam, lParam);
}

void CPassportsDlg::OnYes() {
	// TODO: Add your control notification handler code here
	if ( UpdateData(TRUE) ) {
    m_pWndType1->SetIndex( m_Type1.GetIndex() );
    m_pWndSeria1->SetWindowText( m_Seria1.GetText() );
    m_pWndNumber1->SetWindowText( m_Number1.GetText() );
    m_pWndDate1->SetDate( m_Date1.GetDate() );
    m_pWndBy1->SetCurText( m_By1.GetCurText() );
    m_sMemo = Trim(m_ExtNotice.GetText());
  }
  EndDialog(IDYES);
}

