// FormDivorce.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FormDivorce.h"

#include "ABCList.h"
#include "EraABCDoc.h"
#include "rsDivorces.h"

#include "Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce
/////////////////////////////////////////////////////////////////////////////
// CFormDivorce
IMPLEMENT_DYNCREATE(CFormDivorce, CFormABC)
BEGIN_MESSAGE_MAP(CFormDivorce, CFormABC)
	//{{AFX_MSG_MAP(CFormDivorce)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	ON_EN_SETFOCUS(IDC_MNEW_SURNAME, OnSetfocusMnewSurname)
  ON_EN_SETFOCUS(IDC_WOLD_SURNAME, OnSetfocusWoldSurname)
	ON_EN_SETFOCUS(IDC_WNEW_SURNAME, OnSetfocusWnewSurname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFormDivorce::CFormDivorce():CFormABC(CFormDivorce::IDD) {
	//{{AFX_DATA_INIT(CFormDivorce)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_szFormName = _T("FORM_DIVORCE");
}
CDaoRecordset* CFormDivorce::OnGetRecordset() {
  if (m_pSet != NULL)
    return m_pSet;
  m_pSet = new CRSDivorces(&theApp.m_dbYear);
  m_pSet->Open();

  m_pSet->SetCurrentIndex(_T("PrimaryKey"));
  EnableControls(MoveLast(m_pSet));
  return m_pSet;
}
void CFormDivorce::SetFocusToFirstControl() {
  if ( m_Number.GetSafeHwnd() ) {
    m_Number.SetFocus();
  }
}
void CFormDivorce::DoDataExchange(CDataExchange* pDX) {
	//{{AFX_DATA_MAP(CFormDivorce)
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_DATEREG, m_DateReg);
  DDX_Control(pDX, IDC_MOLD_SURNAME, m_MOldSurname);
  DDX_Control(pDX, IDC_MNEW_SURNAME, m_MNewSurname);
  DDX_Control(pDX, IDC_MNAME, m_MName);
  DDX_Control(pDX, IDC_MPATRONYMIC, m_MPatronymic);
  DDX_Control(pDX, IDC_WOLD_SURNAME, m_WOldSurname);
  DDX_Control(pDX, IDC_WNEW_SURNAME, m_WNewSurname);
  DDX_Control(pDX, IDC_WNAME, m_WName);
  DDX_Control(pDX, IDC_WPATRONYMIC, m_WPatronymic);
	//}}AFX_DATA_MAP
/************************************** : by VK at 25.04.2005 8:00:36 **\
  if ( m_DateReg.GetSafeHwnd()==NULL ) {
    DDX_OleDate(pDX, IDC_DATEREG, m_DateReg);
    if ( g_Shell < WinXP )
      m_DateReg.SetButtonImageID(IDB_CALENDAR);
  }
\************************************** : by VK at 25.04.2005 8:00:39 **/
  CABCList* pABCList = GetListCtrl();
  if ( NULL==pABCList || pABCList->GetItemCount() <= 0 )
    return;
  CRSDivorces* pSet = (CRSDivorces*)m_pSet;
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, pSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, pSet->m_NUMBER, pSet);
  DDX_FieldText(pDX, IDC_MOLD_SURNAME, pSet->m_MOLD_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_MNEW_SURNAME, pSet->m_MNEW_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_MNAME, pSet->m_MNAME, pSet);
  DDX_FieldText(pDX, IDC_MPATRONYMIC, pSet->m_MPATRONYMIC, pSet);
  DDX_FieldText(pDX, IDC_WOLD_SURNAME, pSet->m_WOLD_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_WNEW_SURNAME, pSet->m_WNEW_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_WNAME, pSet->m_WNAME, pSet);
  DDX_FieldText(pDX, IDC_WPATRONYMIC, pSet->m_WPATRONYMIC, pSet);
  CFormABC::DoDataExchange(pDX, pSet->m_ID);
  if ( pDX->m_bSaveAndValidate ) {
    pABCList->UpdateData(pSet->m_ID);
  }
}
void CFormDivorce::OnInitialUpdate() {
  OnGetRecordset();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
	  CFormABC::OnInitialUpdate();

    if ( NULL==m_pSet ) {
      EnableControls(FALSE);
      return;
    }

    if ( MoveLast(m_pSet) )
      OnMove(ID_RECORD_LAST);
    CRSDivorces* pSet = (CRSDivorces*)m_pSet;
    theNames.FillCombo(m_MName, pSet->m_MNAME, TRUE, TRUE);
    theNames.FillCombo(m_WName, pSet->m_WNAME, FALSE, TRUE);
    thePatronymics.FillCombo(m_MPatronymic, pSet->m_MPATRONYMIC, TRUE,  TRUE);
    thePatronymics.FillCombo(m_WPatronymic, pSet->m_WPATRONYMIC, FALSE, TRUE);
  }
}

void CFormDivorce::OnSetfocusNumber()  {
  CRSDivorces* pSet = (CRSDivorces*)m_pSet;
  if ( (0==pSet->m_NUMBER || pSet->IsFieldNull(&pSet->m_NUMBER)) ) {
    SetDefaultNumber();
    SaveData();
    pSet->SetBookmark( pSet->GetLastModifiedBookmark() );
  }
}

void CFormDivorce::OnSetfocusDatereg() {
	// TODO: Add your control notification handler code here
  CString s;
  GetDlgItem(IDC_DATEREG)->GetWindowText(s);
	if ( s.IsEmpty() ) {
    SetDefaultDateReg();
  }
}

void CFormDivorce::OnSetfocusMnewSurname() {
	// TODO: Add your control notification handler code here
	if ( m_MNewSurname.IsEmpty() && !m_MOldSurname.IsEmpty() ) {
    m_MNewSurname.SetWindowText(m_MOldSurname.GetText());
    m_MNewSurname.SetSel(0, -1);
  }
}

void CFormDivorce::OnSetfocusWoldSurname() {
  if ( m_WOldSurname.IsEmpty() && !m_MOldSurname.IsEmpty() ) {
    m_WOldSurname.SetWindowText( OfferSurname( m_MNewSurname.GetText(), TRUE, FALSE) );
  }
}

void CFormDivorce::OnSetfocusWnewSurname() {
	// TODO: Add your control notification handler code here
	if ( m_WNewSurname.IsEmpty() && !m_MNewSurname.IsEmpty() ) {
    m_WNewSurname.SetWindowText( OfferSurname( m_MNewSurname.GetText(), TRUE, FALSE) );
    m_WNewSurname.SetSel(0, -1);
  }
}


