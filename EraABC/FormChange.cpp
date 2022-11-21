// FormChange.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FormChange.h"

#include "ABCList.h"
#include "EraABCDoc.h"
#include "rsChanges.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormChange
IMPLEMENT_DYNCREATE(CFormChange, CFormABC)
BEGIN_MESSAGE_MAP(CFormChange, CFormABC)
	//{{AFX_MSG_MAP(CFormChange)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormChange::CFormChange():CFormABC(CFormChange::IDD) {
  m_szFormName = _T("FORM_CHANGE");
}
CDaoRecordset* CFormChange::OnGetRecordset() {
  if (m_pSet != NULL)
    return m_pSet;
  m_fSexSaved = FALSE;
  m_pSet = new CRSChanges(&theApp.m_dbYear);
  m_pSet->Open();

  m_pSet->SetCurrentIndex(_T("PrimaryKey"));
  EnableControls(MoveLast(m_pSet));
  return m_pSet;
}
void CFormChange::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() )
    m_fSex.SetFocus();
}
void CFormChange::DoDataExchange(CDataExchange* pDX) {
  //{{AFX_DATA_MAP(CFormChange)
	DDX_Control(pDX, IDC_SEX, m_fSex);
  DDX_Control(pDX, IDC_DATEREG, m_DateReg);
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_OLD_SURNAME, m_OldSurname);
  DDX_Control(pDX, IDC_NEW_SURNAME, m_NewSurname);
  DDX_Control(pDX, IDC_OLD_NAME,    m_OldName);
  DDX_Control(pDX, IDC_NEW_NAME,    m_NewName);
  DDX_Control(pDX, IDC_OLD_PATRONYMIC, m_OldPatronymic);
  DDX_Control(pDX, IDC_NEW_PATRONYMIC, m_NewPatronymic);
	//}}AFX_DATA_MAP
/************************************** : by VK at 25.04.2005 7:59:46 **\
  if ( m_DateReg.GetSafeHwnd()==NULL ) {
    DDX_OleDate(pDX, IDC_DATEREG, m_DateReg);
    if ( g_Shell < WinXP )
      m_DateReg.SetButtonImageID(IDB_CALENDAR);
  }
\************************************** : by VK at 25.04.2005 7:59:50 **/
  CABCList* pABCList = GetListCtrl();
  if ( NULL==pABCList ||pABCList->GetItemCount() <= 0 )
    return;
  CRSChanges* pSet = (CRSChanges*)m_pSet;
  DDX_FieldCheck(pDX, IDC_SEX, pSet->m_SEX, pSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, pSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, pSet->m_NUMBER, pSet);
  DDX_FieldText(pDX, IDC_OLD_SURNAME, pSet->m_OLDSURNAME, pSet);
  DDX_FieldText(pDX, IDC_NEW_SURNAME, pSet->m_NEWSURNAME, pSet);
  DDX_FieldText(pDX, IDC_OLD_NAME, pSet->m_OLDNAME, pSet);
  DDX_FieldText(pDX, IDC_NEW_NAME, pSet->m_NEWNAME, pSet);
  DDX_FieldText(pDX, IDC_OLD_PATRONYMIC, pSet->m_OLDPATRONYMIC, pSet);
  DDX_FieldText(pDX, IDC_NEW_PATRONYMIC, pSet->m_NEWPATRONYMIC, pSet);
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
void CFormChange::OnClickSex() {
  BOOL fMale = m_fSex.IsOn();
  CRSChanges* pSet = (CRSChanges*)m_pSet;
  theNames.FillCombo(m_OldName, pSet->m_OLDNAME, fMale, TRUE);
  theNames.FillCombo(m_NewName, pSet->m_NEWNAME, fMale, TRUE);
  thePatronymics.FillCombo(m_OldPatronymic, pSet->m_OLDPATRONYMIC, fMale, TRUE);
  thePatronymics.FillCombo(m_NewPatronymic, pSet->m_NEWPATRONYMIC, fMale, TRUE);
}
void CFormChange::OnSexDependences(BOOL fRefill) {
  //m_Face.SetBitmap( fMale ? m_bmBoy : m_bmGirl);
  CRSChanges* pSet = (CRSChanges*)m_pSet;
  BOOL fMale = pSet->m_SEX;

  theNames.FillCombo(m_OldName, pSet->m_OLDNAME, fMale, fRefill);
  theNames.FillCombo(m_NewName, pSet->m_NEWNAME, fMale, fRefill);
  thePatronymics.FillCombo(m_OldPatronymic, pSet->m_OLDPATRONYMIC, fMale, fRefill);
  thePatronymics.FillCombo(m_NewPatronymic, pSet->m_NEWPATRONYMIC, fMale, fRefill);
}
void CFormChange::OnInitialUpdate() {
	OnGetRecordset();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
	  CFormABC::OnInitialUpdate();
    m_fSex.SetText(_T("ÀÇ ïðî ÇÌ²ÍÓ ²ìåí³"), _T("ÀÇ ïðî ÇÌ²ÍÓ ²ìåí³") );
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);
    if ( MoveLast(m_pSet) )
      OnMove(ID_RECORD_LAST);
  }
}

void CFormChange::OnSetfocusNumber() {
	// TODO: Add your control notification handler code here
  CRSChanges* pSet = (CRSChanges*)m_pSet;
  if ( (0==pSet->m_NUMBER || pSet->IsFieldNull(&pSet->m_NUMBER)) ) {
    SetDefaultNumber();
    SaveData();
    pSet->SetBookmark(pSet->GetLastModifiedBookmark());
  }
}

void CFormChange::OnSetfocusDatereg() {
	// TODO: Add your control notification handler code here
  CString s;
  GetDlgItem(IDC_DATEREG)->GetWindowText(s);
	if ( s.IsEmpty() ) {
    SetDefaultDateReg();
  }
}
