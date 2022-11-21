// Dlg38.cpp : implementation file
//
#include "stdafx.h"
#include "Erags.h"
#include "Defaults.h"
#include "Dlg38.h"
#include "FormMarriage.h"
#include "RList.h"
#include "RNames.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_szSurnameM_RV, g_szNameM_RV, g_szPatronymicM_RV;
extern CString g_szSurnameW_RV, g_szNameW_RV, g_szPatronymicW_RV;
extern CString g_szNewSurnameM, g_szNewSurnameW;
extern CString g_szRagsMarriage, g_szRagsDivorce;
extern CString g_MarriageNum, g_DivorceNum;
extern COleDateTime g_MarriageDR, g_DivorceDR;
extern CString g_Declarant;

/////////////////////////////////////////////////////////////////////////////
// CDlg38 dialog
CDlg38::CDlg38(CWnd* pParent /*=NULL*/):CDialogEx(CDlg38::IDD, pParent) {
	//{{AFX_DATA_INIT(CDlg38)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pMarriageForm = (CFormMarriage*)pParent;
}

void CDlg38::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg38)
	DDX_Control(pDX, IDC_FRAME1, m_Frame1);
	DDX_Control(pDX, IDC_FRAME2, m_Frame2);
	DDX_Control(pDX, IDC_WNEWSURNAME, m_WNewSurname);
	DDX_Control(pDX, IDC_RMARRIAGE_EDIT, m_edtRagsMarriage);
	DDX_Control(pDX, IDC_RMARRIAGE_COMBO, m_cmbRagsMarriage);
	DDX_Control(pDX, IDC_RDIVORCE_EDIT, m_edtRagsDivorce);
	DDX_Control(pDX, IDC_RDIVORCE_COMBO, m_cmbRagsDivorce);
	DDX_Control(pDX, IDC_NUMBER_MARRIAGE, m_MarriageNum);
	DDX_Control(pDX, IDC_NUMBER_DIVORCE, m_DivorceNum);
	DDX_Control(pDX, IDC_MNEWSURNAME, m_MNewSurname);
	DDX_Control(pDX, IDC_DATEREG_DIVORCE, m_DivorceDR);
	DDX_Control(pDX, IDC_DATEREG_MARRIAGE, m_MarriageDR);
	DDX_Control(pDX, IDC_OWNER, m_cmbOwner);
	DDX_Control(pDX, IDC_MPATRONYMIC, m_MPatronymic);
	DDX_Control(pDX, IDC_MOLD_SURNAME, m_MOldSurname);
	DDX_Control(pDX, IDC_MNAME, m_MName);
	DDX_Control(pDX, IDC_WOLD_SURNAME, m_WOldSurname);
	DDX_Control(pDX, IDC_WNAME, m_WName);
	DDX_Control(pDX, IDC_WPATRONYMIC, m_WPatronymic);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg38, CDialogEx)
	//{{AFX_MSG_MAP(CDlg38)
  ON_CBN_SELENDOK(IDC_OWNER, OnSelendOkChangeOwner)
  ON_CBN_SELENDOK(IDC_RMARRIAGE_COMBO, OnSelendOkRMarriage)
  ON_CBN_EDITCHANGE(IDC_RMARRIAGE_COMBO, OnEditChangeRMarriage)
  ON_CBN_SELENDOK(IDC_RDIVORCE_COMBO, OnSelendOkRDivorce)
  ON_CBN_EDITCHANGE(IDC_RDIVORCE_COMBO, OnEditChangeRDivorce)
  ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg38 message handlers
BOOL CDlg38::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
 
  m_cmbOwner.AddString( MakeFullName(m_pMarriageForm->m_MOldSurname.GetText(),
                                     m_pMarriageForm->m_MName.GetCurText(),
                                     m_pMarriageForm->m_MPatronymic.GetCurText(),
                                     true, RC_DV
                                    )
                      );

	
  m_cmbOwner.AddString( MakeFullName(m_pMarriageForm->m_WOldSurname.GetText(),
                                     m_pMarriageForm->m_WName.GetCurText(),
                                     m_pMarriageForm->m_WPatronymic.GetCurText(),
                                     false, RC_DV
                                    )
                      );

  m_cmbOwner.SetCurSel(1);

	m_MOldSurname.SetWindowText( ManSurname_RV(m_pMarriageForm->m_MOldSurname.GetText()) );
	m_MName.SetWindowText( ManName_RV(m_pMarriageForm->m_MName.GetCurText()) );
	m_MPatronymic.SetWindowText( ManFather_RV(m_pMarriageForm->m_MPatronymic.GetCurText()) );

	m_WOldSurname.SetWindowText( WomanSurname_RV(m_pMarriageForm->m_WOldSurname.GetText()) );
	m_WName.SetWindowText( WomanName_RV(m_pMarriageForm->m_WName.GetCurText()) );
	m_WPatronymic.SetWindowText( WomanFather_RV(m_pMarriageForm->m_WPatronymic.GetCurText()) );

  m_MarriageNum.SetWindowText( m_pMarriageForm->m_Number.GetText() );
  m_MarriageDR.SetDate( m_pMarriageForm->m_DateReg.GetDate() );


  m_cmbRagsMarriage.SetDefault(theIniCache.GetRAGS());
  theRList.FillRegCB(m_cmbRagsMarriage, theIniCache.GetRAGS());

  m_MNewSurname.SetWindowText( m_pMarriageForm->m_MNewSurname.GetText() );
  m_WNewSurname.SetWindowText( m_pMarriageForm->m_WNewSurname.GetText() );

  m_cmbRagsDivorce.SetDefault(theIniCache.GetRAGS());
  theRList.FillRegCB(m_cmbRagsDivorce, theIniCache.GetRAGS());

  OnEditChangeRMarriage();
  OnEditChangeRDivorce();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlg38::OnSelendOkChangeOwner() {
}

void CDlg38::OnSelendOkR(CEraComboBox& cmb, CEraEdit& edt) {
  int nSel = cmb.GetCurSel();
  if ( nSel >= 0 ) {
    CString szText;
    cmb.GetLBText(nSel, szText);
    edt.SetWindowText(SVRagsC(szText, RC_MV));
  }
}
void CDlg38::OnEditChangeR(CEraComboBox& cmb, CEraEdit& edt) {
  CString szLBText;
  int nSel = cmb.GetCurSel();
  if ( nSel >= 0 ) {
    cmb.GetLBText(nSel, szLBText);
  }
  CString szEditText = cmb.GetCurText();
  if ( false==szLBText.IsEmpty() && DBFind(szLBText, szEditText)==0 ) {
    edt.SetWindowText(SVRagsC(szLBText, RC_MV));
  }
  else {
    edt.SetWindowText(SVRagsC(szEditText, RC_MV));
  }
}

void CDlg38::OnSelendOkRMarriage() {
  OnSelendOkR(m_cmbRagsMarriage, m_edtRagsMarriage);
}
void CDlg38::OnEditChangeRMarriage() {
  OnEditChangeR(m_cmbRagsMarriage, m_edtRagsMarriage);
}
void CDlg38::OnSelendOkRDivorce() {
  OnSelendOkR(m_cmbRagsDivorce, m_edtRagsDivorce);
}
void CDlg38::OnEditChangeRDivorce() {
  OnEditChangeR(m_cmbRagsDivorce, m_edtRagsDivorce);
}
void CDlg38::OnYes() {
  UpdateData(true);

  g_Declarant        = m_cmbOwner.GetCurText();
  g_szSurnameM_RV    = m_MOldSurname.GetText();
  g_szNameM_RV       = m_MPatronymic.GetText();
  g_szPatronymicM_RV = m_MName.GetText();

  g_szSurnameW_RV    = m_WOldSurname.GetText();
  g_szNameW_RV       = m_WPatronymic.GetText();
  g_szPatronymicW_RV = m_WName.GetText();

  g_szNewSurnameM = m_MNewSurname.GetText();
  g_szNewSurnameW = m_WNewSurname.GetText();

  g_MarriageNum = m_MarriageNum.GetText();
  g_DivorceNum  = m_DivorceNum.GetText();
  g_MarriageDR  = m_MarriageDR.GetDate();
  g_DivorceDR   = m_DivorceDR.GetDate();

  g_szRagsMarriage = m_edtRagsMarriage.GetText();
  g_szRagsDivorce  = m_edtRagsDivorce.GetText();

  CDialogEx::OnYes();
}