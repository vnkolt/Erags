// FormDeath.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FormDeath.h"

#include "ABCList.h"
#include "EraABCDoc.h"
#include "rsDeathes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDeath
/////////////////////////////////////////////////////////////////////////////
// CFormDeath
IMPLEMENT_DYNCREATE(CFormDeath, CFormABC)
BEGIN_MESSAGE_MAP(CFormDeath, CFormABC)
	//{{AFX_MSG_MAP(CFormDeath)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormDeath::CFormDeath():CFormABC(CFormDeath::IDD) {
  m_szFormName = _T("FORM_DEATH");
}
CDaoRecordset* CFormDeath::OnGetRecordset() {
  if (m_pSet != NULL)
    return m_pSet;
  m_pSet = new CRSDeathes(&theApp.m_dbYear);
  m_pSet->Open();

  m_pSet->SetCurrentIndex(_T("PrimaryKey"));
  if ( FALSE==MoveLast(m_pSet) ) {
    EnableControls(FALSE);
  }
  return m_pSet;
}
void CFormDeath::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() )
    m_fSex.SetFocus();
}
void CFormDeath::DoDataExchange(CDataExchange* pDX) {
	//{{AFX_DATA_MAP(CFormDeath)
		DDX_Control(pDX, IDC_SEX, m_fSex);
    DDX_Control(pDX, IDC_NUMBER, m_Number);
    DDX_Control(pDX, IDC_DATEREG, m_DateReg);
    DDX_Control(pDX, IDC_SURNAME, m_Surname);
    DDX_Control(pDX, IDC_NAME, m_Name);
    DDX_Control(pDX, IDC_PATRONYMIC, m_Patronymic);
	//}}AFX_DATA_MAP
  if ( FALSE==m_fFilled )
    return;
  CABCList* pABCList = GetListCtrl();
  if ( NULL==pABCList || pABCList->GetItemCount() <= 0 )
    return;
  CRSDeathes* pSet = (CRSDeathes*)m_pSet;
  DDX_FieldCheck(pDX, IDC_SEX, pSet->m_SEX, pSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, pSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, pSet->m_NUMBER, pSet);
  DDX_FieldText(pDX, IDC_SURNAME, pSet->m_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_NAME, pSet->m_NAME, pSet);
  DDX_FieldText(pDX, IDC_PATRONYMIC, pSet->m_PATRONYMIC, pSet);
  CFormABC::DoDataExchange(pDX, pSet->m_ID);
  if ( pDX->m_bSaveAndValidate ) {
    m_fSexSaved = pSet->m_SEX;
    pABCList->UpdateData(pSet->m_ID);
  }
  else {
    //m_Face.SetBitmap( pSet->m_SEX ? m_bmBoy : m_bmGirl);
    OnSexDependences(m_fSexSaved!=pSet->m_SEX);
  }
}
void CFormDeath::OnClickSex() {
  BOOL fMale = m_fSex.IsOn();
  CRSDeathes* pSet = (CRSDeathes*)m_pSet;
  theNames.FillCombo(m_Name, pSet->m_NAME, fMale, TRUE);
  thePatronymics.FillCombo(m_Patronymic, pSet->m_PATRONYMIC, fMale, TRUE);
}
void CFormDeath::OnSexDependences(BOOL fRefill) {
  CRSDeathes* pSet = (CRSDeathes*)m_pSet;
  BOOL fMale = pSet->m_SEX;
  theNames.FillCombo(m_Name, pSet->m_NAME, fMale, fRefill);
  thePatronymics.FillCombo(m_Patronymic, pSet->m_PATRONYMIC, fMale, fRefill);
}

void CFormDeath::OnInitialUpdate() {
  OnGetRecordset();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
	  CFormABC::OnInitialUpdate();
    m_fSex.SetText(_T("АЗ про смерть громадянина"), _T("АЗ про смерть громадянки"));
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);
    UpdateData(FALSE);
    if ( MoveLast(m_pSet) )
      OnMove(ID_RECORD_LAST);
  }
}

void CFormDeath::OnSetfocusNumber() {
	// TODO: Add your control notification handler code here
  CRSDeathes* pSet = (CRSDeathes*)m_pSet;
  if ( (0==pSet->m_NUMBER || pSet->IsFieldNull(&pSet->m_NUMBER)) ) {
    SetDefaultNumber();
    SaveData();
    pSet->SetBookmark( pSet->GetLastModifiedBookmark() );
  }
}

void CFormDeath::OnSetfocusDatereg() {
	// TODO: Add your control notification handler code here
  CString s;
  GetDlgItem(IDC_DATEREG)->GetWindowText(s);
	if ( s.IsEmpty() ) {
    SetDefaultDateReg();
  }
}
