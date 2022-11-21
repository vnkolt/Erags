// FormBirth.cpp : implementation file
//

#include "stdafx.h"
#include "EraABC.h"
#include "FormBirth.h"

#include "ABCList.h"
#include "EraABCDoc.h"
#include "rsBirthes.h"

#include "SetDefDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormBirth

IMPLEMENT_DYNCREATE(CFormBirth, CFormABC)

CFormBirth::CFormBirth(): CFormABC(CFormBirth::IDD) {
	//{{AFX_DATA_INIT(CFormBirth)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_szFormName = _T("FORM_BIRTH");
  m_bmBoy.LoadBitmap(IDB_BOY);
  m_bmGirl.LoadBitmap(IDB_GIRL);
  m_bmStillbornBoy.LoadBitmap(IDB_STILLBORN_BOY);
  m_bmStillbornGirl.LoadBitmap(IDB_STILLBORN_GIRL);
}

CFormBirth::~CFormBirth() {
}

CDaoRecordset* CFormBirth::OnGetRecordset() {
  if ( FALSE==theApp.m_dbYear.IsOpen() )
    return NULL;
  if (m_pSet != NULL)
    return m_pSet;
  m_fSexSaved = FALSE;
  m_pSet = new CRSBirthes(&theApp.m_dbYear);
  m_pSet->Open();

  m_pSet->SetCurrentIndex(_T("PrimaryKey"));
  EnableControls(MoveLast(m_pSet));
  return m_pSet;
}
void CFormBirth::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() ) {
    SetActiveWindow();
    m_fSex.SetFocus();
  }
}
void CFormBirth::DoDataExchange(CDataExchange* pDX) {
	//{{AFX_DATA_MAP(CFormBirth)
  DDX_Control(pDX, IDC_CHILDFACE, m_Face);
	DDX_Control(pDX, IDC_SEX, m_fSex);
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_DATEREG, m_DateReg);
  DDX_Control(pDX, IDC_SURNAME, m_Surname);
  DDX_Control(pDX, IDC_NAME, m_Name);
  DDX_Control(pDX, IDC_PATRONYMIC, m_Patronymic);
  DDX_Control(pDX, IDC_ALIVE_FLAG, m_Alive_Flag);
	//}}AFX_DATA_MAP
/************************************** : by VK at 25.04.2005 7:57:41 **\
  if ( m_DateReg.GetSafeHwnd()==NULL ) {
    DDX_OleDate(pDX, IDC_DATEREG, m_DateReg);
    if ( g_Shell < WinXP )
      m_DateReg.SetButtonImageID(IDB_CALENDAR);
  }
\************************************** : by VK at 25.04.2005 7:57:45 **/
  if ( FALSE==m_fFilled )
    return;
  CABCList* pABCList = GetListCtrl();
  if ( NULL==pABCList || pABCList->GetItemCount() <= 0 )
    return;

  CRSBirthes* pSet = (CRSBirthes*)m_pSet;
	CFormABC::DoDataExchange(pDX, pSet->m_ID);

  DDX_FieldCheck(pDX, IDC_SEX, pSet->m_SEX, pSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, pSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, pSet->m_NUMBER, pSet);
  DDX_FieldText(pDX, IDC_SURNAME, pSet->m_SURNAME, pSet);
  DDX_FieldText(pDX, IDC_NAME, pSet->m_NAME, pSet);
  DDX_FieldText(pDX, IDC_PATRONYMIC, pSet->m_PATRONYMIC, pSet);
  DDX_MSButton(pDX,  IDC_ALIVE_FLAG, m_Alive_Flag, pSet->m_ALIVE_FLAG);
  if ( pDX->m_bSaveAndValidate ) {
    m_fSexSaved = pSet->m_SEX;
    pABCList->UpdateData(pSet->m_ID);
  }
  else {
    if ( pSet->m_ALIVE_FLAG )
      m_Face.SetBitmap( pSet->m_SEX ? m_bmBoy : m_bmGirl);
    else
      m_Face.SetBitmap( pSet->m_SEX ? m_bmStillbornBoy : m_bmStillbornGirl);
    OnSexDependences(m_fSexSaved!=pSet->m_SEX);
  }
}

BEGIN_MESSAGE_MAP(CFormBirth, CFormABC)
	//{{AFX_MSG_MAP(CFormBirth)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormBirth diagnostics
#ifdef _DEBUG
void CFormBirth::AssertValid() const {
	CFormABC::AssertValid();
}
void CFormBirth::Dump(CDumpContext& dc) const {
	CFormABC::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormBirth message handlers
void CFormBirth::OnClickSex() {
  BOOL fMale = m_fSex.IsOn();
  m_Face.SetBitmap( fMale ? m_bmBoy : m_bmGirl);
  CRSBirthes* pSet = (CRSBirthes*)m_pSet;
  theNames.FillCombo(m_Name, pSet->m_NAME, fMale, TRUE);
  thePatronymics.FillCombo(m_Patronymic, pSet->m_PATRONYMIC, fMale, TRUE);
}
void CFormBirth::OnSexDependences(BOOL fRefill) {
  //m_Face.SetBitmap( fMale ? m_bmBoy : m_bmGirl);
  CRSBirthes* pSet = (CRSBirthes*)m_pSet;
  BOOL fMale = pSet->m_SEX;//m_fSex.IsOn();

  theNames.FillCombo(m_Name, pSet->m_NAME, fMale, fRefill);
  thePatronymics.FillCombo(m_Patronymic, pSet->m_PATRONYMIC, fMale, fRefill);
}

void CFormBirth::OnInitialUpdate() {
  OnGetRecordset();
  if ( FALSE==m_fInitialized ) {
    m_fInitialized = TRUE;
    CFormABC::OnInitialUpdate();

    m_fSex.SetText(_T("АЗ про народження хлопчика"), _T("АЗ про народження дівчинки") );
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);

    m_Alive_Flag.AddColorState( 0, RGB(0x00, 0x00, 0x00), _T("мертвонароджена") );
    m_Alive_Flag.AddColorState( 1, RGB(0xFF, 0x20, 0x20), _T("живонароджена") );    

    if ( NULL==m_pSet ) {
      EnableControls(FALSE);
      return;
    }
    if ( MoveLast(m_pSet) ) {
      CFormABC::OnMove(ID_RECORD_LAST);
    }
    else {
      m_Face.SetBitmap(NULL); // Потому что нет записей
    }
  }
}

void CFormBirth::OnSetfocusNumber() {
	// TODO: Add your control notification handler code here
  CRSBirthes* pSet = (CRSBirthes*)m_pSet;
  if ( (0==pSet->m_NUMBER || pSet->IsFieldNull(&pSet->m_NUMBER)) ) {
    SetDefaultNumber();
    SaveData();
    pSet->SetBookmark( pSet->GetLastModifiedBookmark() );
  }
}

void CFormBirth::OnSetfocusDatereg() {
	// TODO: Add your control notification handler code here
  CString s;
  GetDlgItem(IDC_DATEREG)->GetWindowText(s);
	if ( s.IsEmpty() ) {
    SetDefaultDateReg();
  }
}
void CFormBirth::BeforeGoToNextRecord() {
  CString sName = Trim(m_Name.GetCurText());
  CString szPattronymic = Trim(m_Patronymic.GetCurText());
  if ( m_Name.IsEmpty() && szPattronymic.IsEmpty() ) {
    LPCTSTR szMsg = _T("Ім'я та по батькові залишени незаповненими. Чи вважати, що це мертвонароджена дитина?");
    int nDlgRes = CallSetDefDlg(this, _T("Settings"), _T("ShowAliveRequest"), _T("AliveResponse"), szMsg);
    if ( IDYES==nDlgRes ) {
      m_Alive_Flag.SetIndex(0);
    }
  }
}

