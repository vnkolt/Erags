// FormChange.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "FormChange.h"
#include "EragsDoc.h"
#include "MainFrm.h"

#include "Caches.h"
#include "DataManager.h"
#include "Defaults.h"
#include "ElectDlg.h"
#include "ExtNotice.h"

#include "HelpMan.h"
#include "Menu.h"
#include "NoteChange.h"
#include "RNames.h"
#include "SvDlg.h"
#include "RTFCnv.h"
#include "xMachine.h"

#include "ABCDlg.h"
#include "Dlg27.h"
#include "Dlg29.h"

#include "..\Common\DB.h"
#include "..\Common\DaoErr.h"
#include "..\Common\MDB.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL ConvertForElect(const CString& sTemplate, const CString& sOutName, CPtrArray& array);
BOOL RegDlg(CPPToolTip* pTooltip);

/////////////////////////////////////////////////////////////////////////////
// CFormChange

IMPLEMENT_DYNCREATE(CFormChange, CEraForm)

CFormChange::CFormChange()
             :CEraForm(CFormChange::IDD), m_pRSet((CRSChanges*&)m_pSet)  {
	//{{AFX_DATA_INIT(CFormChange)
	//}}AFX_DATA_INIT
  m_szFormName = _T("FORM_CHANGE");
}

CFormChange::~CFormChange() {
  if ( m_pSet ) {
    if( m_pSet->IsOpen() )
      m_pSet->Close();
    delete m_pSet;
    m_pSet = NULL;
  }
}

void CFormChange::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() )
    m_fSex.SetFocus();
}
void CFormChange::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LBL_DATE:                case IDC_LBL_NUMBER:
    case IDC_LBL_BEFORE:              case IDC_LBL_AFTER:
    case IDC_LBL_SURNAME:             case IDC_LBL_NAME:        case IDC_LBL_PATRONYMIC:
    case IDC_LBL_BIRTH_DATE:
    case IDC_LBL_BP_COUNTRY:          case IDC_LBL_BP_REGION:
    case IDC_LBL_BP_DISTRICT:         case IDC_LBL_BP_CITY:
    case IDC_LBL_RP_COUNTRY:          case IDC_LBL_RP_REGION:
    case IDC_LBL_RP_DISTRICT:         case IDC_LBL_RP_CITY:
    case IDC_LBL_RP_STREET:           case IDC_LBL_RP_HOUSE:    case IDC_LBL_RP_FLAT:
    case IDC_LBL_BIRTHACT_NUMBER:     case IDC_LBL_BIRTHACT_DATE:
    case IDC_LABEL_MCHECK_NUMBER:     case IDC_LBL_CHECK_DATE:
    case IDC_LABEL_MDUTY:             case IDC_LBL_CHECK_BANK:
    case IDC_LBL_PASSPORT_SERIA:      case IDC_LBL_PASSPORT_NUMBER:
    case IDC_LBL_PASSPORT_DATE:       case IDC_LBL_PASSPORT_BY:
    case IDC_LBL_CERTIFICATE_SERIA:   case IDC_LBL_CERTIFICATE_NUMBER:
    case IDC_LBL_NOTICE:
    case IDC_LBL_LIVEPLACE:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CDaoRecordViewBG::SetScaleFlags(pWnd, wFlags);
  }
}
void CFormChange::DoDataExchange(CDataExchange* pDX) {
  if ( FALSE==pDX->m_bSaveAndValidate ) {
    m_OLDSURNAME_before_save     = m_pRSet->m_OLDSURNAME;
    m_OLDNAME_before_save        = m_pRSet->m_OLDNAME;
    m_OLDPATRONYMIC_before_save  = m_pRSet->m_OLDPATRONYMIC;
    m_NEWSURNAME_before_save     = m_pRSet->m_NEWSURNAME;
    m_NEWNAME_before_save        = m_pRSet->m_NEWNAME;
    m_NEWPATRONYMIC_before_save  = m_pRSet->m_NEWPATRONYMIC;
    m_NUMBER_before_save         = m_pRSet->m_NUMBER;
    m_DATEREG_before_save        = m_pRSet->m_DATEREG;
  }
	CEraForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormChange)
  DDX_Control(pDX, IDC_SEX, m_fSex);
  DDX_Control(pDX, IDC_CITIZENSHIP, m_cmbCitizenship);
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_OLD_SURNAME, m_OldSurname);
  DDX_Control(pDX, IDC_NEW_SURNAME, m_NewSurname);
	DDX_Control(pDX, IDC_BIRTHACT_NUMBER, m_BirthActNumber);
  DDX_Control(pDX, IDC_OLD_NAME, m_OldName);
  DDX_Control(pDX, IDC_NEW_NAME, m_NewName);
  DDX_Control(pDX, IDC_OLD_PATRONYMIC, m_OldPatronymic);
  DDX_Control(pDX, IDC_NEW_PATRONYMIC, m_NewPatronymic);
  DDX_Control(pDX, IDC_BP_COUNTRY, m_cmbBirthCountry);
  DDX_Control(pDX, IDC_BP_REGION, m_cmbBirthRegion);
  DDX_Control(pDX, IDC_BP_DISTRICT, m_cmbBirthDistrict);
  DDX_Control(pDX, IDC_BP_CITY, m_cmbBirthCity);
  DDX_Control(pDX, IDC_RP_COUNTRY, m_cmbRPCountry);
  DDX_Control(pDX, IDC_RP_REGION, m_cmbRPRegion);
  DDX_Control(pDX, IDC_RP_DISTRICT, m_cmbRPDistrict);
  DDX_Control(pDX, IDC_RP_CITY, m_cmbRPCity);
  DDX_Control(pDX, IDC_RP_STREET, m_cmbRPStreet);
  DDX_Control(pDX, IDC_RP_HOUSE, m_RPHouse);
  DDX_Control(pDX, IDC_RP_FLAT, m_RPFlat);
  DDX_Control(pDX, IDC_DUTY, m_Duty);
	DDX_Control(pDX, IDC_CHECK_NUMBER, m_CheckNumber);
	DDX_Control(pDX, IDC_CHECK_BANK, m_CheckBank);
	DDX_Control(pDX, IDC_PASSPORT_TYPE, m_PassportType);
	DDX_Control(pDX, IDC_PASSPORT_SERIA, m_PassportSeria);
	DDX_Control(pDX, IDC_PASSPORT_NUMBER, m_PassportNumber);
	DDX_Control(pDX, IDC_PASSPORT_BY, m_PassportBy);
  DDX_Control(pDX, IDC_CERTIFICATE_SERIA, m_CertificateSeria);
	DDX_Control(pDX, IDC_CERTIFICATE_NUMBER, m_CertificateNumber);
	DDX_Control(pDX, IDC_NOTICE, m_Notice);
	//}}AFX_DATA_MAP
  DDX_FieldCheck(pDX, IDC_SEX, m_pRSet->m_SEX, m_pRSet);
  DDX_FieldText(pDX, IDC_CITIZENSHIP, m_pRSet->m_CITIZENSHIP, m_pRSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, m_pRSet->m_DATEREG);
  //DDX_FieldText(pDX, IDC_DATEREG, m_pRSet->m_DATEREG, m_pRSet);
  DDX_FieldText(pDX, IDC_NUMBER, m_pRSet->m_NUMBER, m_pRSet);
  DDX_FieldText(pDX, IDC_OLD_SURNAME, m_pRSet->m_OLDSURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_NEW_SURNAME, m_pRSet->m_NEWSURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_OLD_NAME, m_pRSet->m_OLDNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_NEW_NAME, m_pRSet->m_NEWNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_OLD_PATRONYMIC, m_pRSet->m_OLDPATRONYMIC, m_pRSet);
  DDX_FieldText(pDX, IDC_NEW_PATRONYMIC, m_pRSet->m_NEWPATRONYMIC, m_pRSet);
  DDX_OleDate(pDX, IDC_BIRTH_DATE, m_BirthDate, m_pRSet->m_BIRTH_DATE);
  DDX_FieldText(pDX, IDC_BP_COUNTRY, m_pRSet->m_BIRTH_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_REGION, m_pRSet->m_BIRTH_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_DISTRICT, m_pRSet->m_BIRTH_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_CITY, m_pRSet->m_BIRTH_CITY, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_COUNTRY, m_pRSet->m_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_REGION, m_pRSet->m_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_DISTRICT, m_pRSet->m_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_CITY, m_pRSet->m_CITY, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_STREET, m_pRSet->m_STREET, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_HOUSE, m_pRSet->m_HOUSE, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_FLAT, m_pRSet->m_FLAT, m_pRSet);
  DDX_FieldText(pDX, IDC_BIRTHACT_NUMBER, m_pRSet->m_BIRTHACT_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_BIRTHACT_DATE, m_BirthActDate, m_pRSet->m_BIRTHACT_DATE);
  DDX_FieldText(pDX, IDC_DUTY, m_pRSet->m_DUTY, m_pRSet);
	DDX_FieldText(pDX, IDC_CHECK_NUMBER, m_pRSet->m_CHECKNUM, m_pRSet);
	DDX_OleDate(pDX, IDC_CHECK_DATE, m_CheckDate, m_pRSet->m_CHECKDATE);
	DDX_FieldText(pDX, IDC_CHECK_BANK, m_pRSet->m_CHECKBANK, m_pRSet);
	DDX_MSButton(pDX, IDC_PASSPORT_TYPE, m_PassportType, m_pRSet->m_PASSPORT_TYPE);
	DDX_FieldText(pDX, IDC_PASSPORT_SERIA, m_pRSet->m_PASSPORT_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_PASSPORT_NUMBER, m_pRSet->m_PASSPORT_NUMBER, m_pRSet);
	DDX_OleDate(pDX, IDC_PASSPORT_DATE, m_PassportDate, m_pRSet->m_PASSPORT_DATE);
	DDX_FieldText(pDX, IDC_PASSPORT_BY, m_pRSet->m_PASSPORT_BY, m_pRSet);
  DDX_FieldText(pDX, IDC_CERTIFICATE_SERIA, m_pRSet->m_CERTIFICATE_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_CERTIFICATE_NUMBER, m_pRSet->m_CERTIFICATE_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_NOTICE, m_pRSet->m_NOTICE, m_pRSet);

/************************************** : by VK at 04.12.2004 5:01:59 **\
  if ( pDX->m_bSaveAndValidate ) {
    if ( m_NUMBER_before_save        != m_pRSet->m_NUMBER         ||
         m_DATEREG_before_save       != m_pRSet->m_DATEREG        ||
         m_OLDSURNAME_before_save    != m_pRSet->m_OLDSURNAME     ||
         m_OLDNAME_before_save       != m_pRSet->m_OLDNAME        ||
         m_OLDPATRONYMIC_before_save != m_pRSet->m_OLDPATRONYMIC  ||
         m_NEWSURNAME_before_save    != m_pRSet->m_NEWSURNAME     ||
         m_NEWNAME_before_save       != m_pRSet->m_NEWNAME        ||
         m_NEWPATRONYMIC_before_save != m_pRSet->m_NEWPATRONYMIC )
  }
\************************************** : by VK at 04.12.2004 5:02:02 **/
  m_ID = m_pRSet->m_ID;
}


BEGIN_MESSAGE_MAP(CFormChange, CEraForm)
	//{{AFX_MSG_MAP(CFormChange)
  ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
  ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_NEW_SURNAME, OnSetfocusNewSurname)
	ON_CBN_SETFOCUS(IDC_NEW_NAME, OnSetfocusNewName)
	ON_CBN_SETFOCUS(IDC_NEW_PATRONYMIC, OnSetfocusNewPatronymic)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_SERIA, OnSetfocusCertificateSeria)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_NUMBER, OnSetfocusCertificateNumber)
  ON_EN_CHANGE(IDC_CERTIFICATE_NUMBER, OnChangeCertificateNumber)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormChange diagnostics

#ifdef _DEBUG
void CFormChange::AssertValid() const {
	CEraForm::AssertValid();
}

void CFormChange::Dump(CDumpContext& dc) const {
	CEraForm::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormChange message handlers
CDaoRecordset* CFormChange::OnGetRecordset() {
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CRSChanges(&theDataManager.m_dbYear);
	m_pSet->Open();

  m_pRSet->SetCurrentIndex(_T("NUMBER"));
  try {
    if ( FALSE==m_pRSet->IsBOF() && FALSE==m_pRSet->IsEOF() )
      m_pRSet->MoveLast();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
  }

	return m_pRSet;
}

void CFormChange::SelectIfNotEmpty(CEraNameComboBox& cb, const CString& sValue) {
  if ( !sValue.IsEmpty() ) {
    int nItem = cb.FindString(-1, sValue);
    if ( CB_ERR == nItem ) 
      nItem = cb.AddString(sValue);
    cb.SelectString(-1, sValue);
  }
}

void CFormChange::OnSexDependences() {
  CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
  if ( NULL==pDoc )
    return;

  CString sOldName       = m_pRSet->m_OLDNAME;
  CString sOldPatronymic = m_pRSet->m_OLDPATRONYMIC;
  CString sNewName       = m_pRSet->m_NEWNAME;
  CString sNewPatronymic = m_pRSet->m_NEWPATRONYMIC;

  if ( m_fSex.IsOn() ) { // Male
    theMNames.FillCombo( m_OldName, m_pRSet->m_OLDNAME, FALSE==m_OldName.IsMale() );
    theMNames.FillCombo( m_NewName, m_pRSet->m_NEWNAME, FALSE==m_NewName.IsMale() );
    theMPatronymics.FillCombo( m_OldPatronymic, m_pRSet->m_OLDPATRONYMIC, FALSE==m_OldPatronymic.IsMale() );
    theMPatronymics.FillCombo( m_NewPatronymic, m_pRSet->m_NEWPATRONYMIC, FALSE==m_NewPatronymic.IsMale() );

    m_OldName.SetMale();
    m_NewName.SetMale();
    m_OldPatronymic.SetMale();
    m_NewPatronymic.SetMale();
  }
  else {                // Female
    theWNames.FillCombo( m_OldName, m_pRSet->m_OLDNAME, FALSE==m_OldName.IsFemale() );
    theWNames.FillCombo( m_NewName, m_pRSet->m_NEWNAME, FALSE==m_NewName.IsFemale() );
    theWPatronymics.FillCombo( m_OldPatronymic, m_pRSet->m_OLDPATRONYMIC, FALSE==m_OldPatronymic.IsFemale() );
    theWPatronymics.FillCombo( m_NewPatronymic, m_pRSet->m_NEWPATRONYMIC, FALSE==m_NewPatronymic.IsFemale() );
    m_OldName.SetFemale();
    m_NewName.SetFemale();
    m_OldPatronymic.SetFemale();
    m_NewPatronymic.SetFemale();
  }
  SelectIfNotEmpty(m_OldName, sOldName);
  SelectIfNotEmpty(m_NewName, sNewName);
  SelectIfNotEmpty(m_OldPatronymic, sOldPatronymic);
  SelectIfNotEmpty(m_NewPatronymic, sNewPatronymic);

}

CRSChanges* CFormChange::GetRecordset() {
	CRSChanges* pSet = (CRSChanges*) OnGetRecordset();
	ASSERT(pSet != NULL && pSet->IsKindOf(RUNTIME_CLASS(CRSChanges)));
	return pSet;
}
#ifndef FREE_LICENCE
BOOL CFormChange::IsRDFFieldsDirty() {
  if ( m_pRSet ) {
    SetChangedBy(m_pRSet, m_pRSet->m_EXTNOTES);
    // 	REGION, DISTRICT, CITY
    if ( m_pRSet->IsFieldDirty(&m_pRSet->m_REGION)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_DISTRICT) ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_CITY) )
      return true;
  }
  return false;
}
void CFormChange::SetRDFFields() {
  SaveGeoValidation(m_pRSet->m_REGION, m_pRSet->m_DISTRICT, m_pRSet->m_CITY, true);
}
#endif // #ifndef FREE_LICENCE

BOOL CFormChange::OnMove(UINT nIDMoveCommand) {
  if ( NULL==m_pRSet )
    return FALSE;
  if ( m_pRSet->IsBOF() && m_pRSet->IsEOF() )
    return FALSE;
  BOOL bRet = CEraForm::OnMove(nIDMoveCommand);
  if ( bRet ) {
    OnSexDependences();

    theCitizenships.FillCombo( m_cmbCitizenship, m_pRSet->m_CITIZENSHIP );

    theGeoCache.FillCountryCB(m_cmbBirthCountry, m_pRSet->m_BIRTH_COUNTRY);
    theGeoCache.FillRegionCB(m_cmbBirthRegion, m_cmbBirthCountry, m_pRSet->m_BIRTH_REGION);
    theGeoCache.FillDistrictCB(m_cmbBirthDistrict, m_cmbBirthRegion, m_pRSet->m_BIRTH_DISTRICT);

    theGeoCache.FillCountryCB(m_cmbRPCountry, m_pRSet->m_COUNTRY);
    theGeoCache.FillRegionCB(m_cmbRPRegion, m_cmbRPCountry, m_pRSet->m_REGION);
    theGeoCache.FillDistrictCB(m_cmbRPDistrict, m_cmbRPRegion, m_pRSet->m_DISTRICT);
    theStreets.Add( m_cmbRPStreet, m_pRSet->m_STREET );

  }
  return bRet;
}

BOOL CFormChange::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LBL_DATE:                case IDC_LBL_NUMBER:
    case IDC_LBL_BEFORE:              case IDC_LBL_AFTER:
    case IDC_LBL_SURNAME:             case IDC_LBL_NAME:        case IDC_LBL_PATRONYMIC:
    case IDC_LBL_BIRTH_DATE:
    case IDC_LBL_BP_COUNTRY:          case IDC_LBL_BP_REGION:
    case IDC_LBL_BP_DISTRICT:         case IDC_LBL_BP_CITY:
    case IDC_LBL_RP_COUNTRY:          case IDC_LBL_RP_REGION:
    case IDC_LBL_RP_DISTRICT:         case IDC_LBL_RP_CITY:
    case IDC_LBL_RP_STREET:           case IDC_LBL_RP_HOUSE:    case IDC_LBL_RP_FLAT:
    case IDC_LBL_BIRTHACT_NUMBER:     case IDC_LBL_BIRTHACT_DATE:
    case IDC_LABEL_MCHECK_NUMBER:     case IDC_LBL_CHECK_DATE:
    case IDC_LABEL_MDUTY:             case IDC_LBL_CHECK_BANK:
    case IDC_LBL_PASSPORT_SERIA:      case IDC_LBL_PASSPORT_NUMBER:
    case IDC_LBL_PASSPORT_DATE:       case IDC_LBL_PASSPORT_BY:
    case IDC_LBL_CERTIFICATE_SERIA:   case IDC_LBL_CERTIFICATE_NUMBER:
    case IDC_LBL_NOTICE:
    case IDC_LBL_LIVEPLACE:
    case IDC_STATIC:
    case 0xFFFF:
      return TRUE;
  }
  return FALSE;
}
void CFormChange::OnInitialUpdate() {
	BeginWaitCursor();
	GetRecordset();
/************************************** : by VK at 04.12.2004 5:02:10 **\
  ClearNavigateBars();
\************************************** : by VK at 04.12.2004 5:02:12 **/
  ((CMainFrame*)AfxGetMainWnd())->m_pChangeFrame = GetParentFrame();
  m_nPrinPos = CONTEXT_CHANGE; // Зміна

	CEraForm::OnInitialUpdate();


	if (m_pRSet->IsOpen()) {

		CString strTitle = m_pRSet->m_pDatabase->GetName();
    strTitle += _T(" - Зміни");
    CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
    pDoc->SetTitle(strTitle);

    m_fSex.SetText( _T("Актовий запис про зміну імені громадянина"), _T("Актовий запис про зміну імені громадянки") );
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);

    m_cmbBirthCountry.SetDefault( theIniCache.GetCOUNTRY() );
    m_cmbRPCountry.SetDefault( theIniCache.GetCOUNTRY() );

    m_cmbCitizenship.SetDefault( g_szDefCitizenship );
    m_PassportBy.SetDefault( theIniCache.GetByROVD() );
    theStreets.FillCombo( m_cmbRPStreet, m_pRSet->m_STREET );

    theIniCache.FillBanks();
    for( int i(0); i < theBanks.GetSize(); i++ ) {    
      CString s = theBanks.GetAt(i);
      m_CheckBank.AddString(s);
    }

    OnMove(ID_RECORD_LAST);
    m_fSex.SetFocus();
    if ( m_pRSet->IsEOF() && m_pRSet->IsBOF() )
      EnableForm(FALSE);
	}

	EndWaitCursor();
#ifndef FREE_LICENCE
  if ( FALSE==RegDlg(&m_tooltip) ) {
    AfxGetMainWnd()->PostMessage(WM_QUIT);
  }
#endif // FREE_LICENCE
  EmptyTable();
}

void CFormChange::OnSetfocusDatereg() {
  SetDefaultDateReg(IDD_FORM_CHANGE);
}

void CFormChange::OnSetfocusNumber() {
  if ( 0==m_pRSet->m_NUMBER && SetDefaultNumber(m_pRSet->m_NUMBER) ) {
    m_pRSet->Edit();
    m_pRSet->Update();
    UpdateData(TRUE);
    m_pRSet->SetBookmark( m_pRSet->GetLastModifiedBookmark() );
    SetBookMarks();
  }
}

void CFormChange::OnSetfocusNewSurname() {
  CString s = Trim(m_NewSurname.GetText());
  if ( s.IsEmpty() ) {
    m_NewSurname.SetWindowText( m_OldSurname.GetText() );
    m_NewSurname.SetSel(0, -1);
  }
}

void CFormChange::OnSetfocusNewName() {
	CString s = Trim(m_NewName.GetCurText());
  if ( s.IsEmpty() ) {
    m_NewName.SetCurText(m_OldName.GetCurText());
  }
}

void CFormChange::OnSetfocusNewPatronymic() {
	CString s = Trim(m_NewPatronymic.GetCurText());
  if ( s.IsEmpty() ) {
    m_NewPatronymic.SetCurText(m_OldPatronymic.GetCurText());
  }
}

void CFormChange::OnSetfocusCertificateSeria() {
	CString s;
  m_CertificateSeria.GetWindowText(s);
  if ( s.IsEmpty() ) {
    m_CertificateSeria.SetWindowText( theIniCache.GetCHANGE_Seria() );
    m_CertificateSeria.SetSel(0, -1);
  }
}

void CFormChange::OnSetfocusCertificateNumber() {
	CString s;
	m_CertificateNumber.GetWindowText(s);
  bool fSeriaIsEmpty = m_CertificateSeria.IsEmpty();
  if ( s.IsEmpty() && !fSeriaIsEmpty ) {
    s = theIniCache.GetCHANGE_CNum();
    int nLen = s.GetLength();
    m_CertificateNumber.SetWindowText( s );
    m_CertificateNumber.SetSel(nLen, nLen);
  }
  else if ( fSeriaIsEmpty ) {
    if ( IDC_NOTICE==m_LastCtrlId )
      m_CertificateSeria.SetFocus();
    else
      m_Notice.SetFocus();
  }
}

void CFormChange::OnChangeCertificateNumber() {
  theIniCache.SetCHANGE_CNum( &m_CertificateNumber );  
}

void CFormChange::OnContextMenu(CWnd* pWnd, CPoint point) {
  m_tooltip.HideTooltip();
  UINT nPos = CONTEXT_CHANGE;
  CString s, sMemo;
  m_Notice.GetWindowText(sMemo);
  s = ContextMenu(m_Notice.m_hWnd, nPos, m_fSex.IsOn(), m_DateReg.GetDate(), sMemo, false, NULL, NULL);
  if ( s != sMemo )
    m_Notice.SetWindowText(s);
}

void CFormChange::OnBlank(const CString& szTemplate, const CString& szOut) {
  if ( RTF_ChangeBlank(szTemplate, szOut, m_pRSet) ) {
    OnRTFShell(szOut);
  }
}
void CFormChange::OnPrint(UINT nPrintID) {
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

  if ( FALSE==CEraForm::OnMove(0) )  // Save data
    return;

  CString sTemplate, sOut;

  int nPage1(0), nPage2(0);

  g_nDocType = DOCTYPE_OTHER;

  switch ( nPrintID ) {
    case ID_PRINT_CHANGE_ACT:
      g_nDocType = DOCTYPE_ACT;
      sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, _T("Act") );
      sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, _T("Act"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_CHANGE_CERIFICATE: {
        g_nDocType = DOCTYPE_CERT;
        CSVDlg dlg(this, IDD_SVID);
        dlg.m_szFormSect = _T("CHANGE_FORM");
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, _T("Certificate") );
          sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, _T("Certificate"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_27: {
        CDlg27 dlg(this);
        dlg.m_fSex            = m_fSex.IsOn();
        dlg.m_sOldSurname     = m_OldSurname.GetText();
        dlg.m_sOldName        = m_OldName.GetCurText();
        dlg.m_sOldPatronymic  = m_OldPatronymic.GetCurText();
        dlg.m_sNewSurname     = m_NewSurname.GetText();
        dlg.m_sNewName        = m_NewName.GetCurText();
        dlg.m_sNewPatronymic  = m_NewPatronymic.GetCurText();
        dlg.m_sAddress        = MakeAddress(&m_cmbRPCountry, &m_cmbRPRegion, &m_cmbRPCity, &m_cmbRPDistrict, &m_cmbRPStreet, &m_RPHouse, &m_RPFlat);
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, _T("27") );
          sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, _T("27"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_28: {
        CNoteChange dlg(this);
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, _T("28") );
          sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, _T("28"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_29:
    case ID_PRINT_CHANGE_30: {
        CDlg29 dlg(nPrintID, this);
        if ( IDYES==dlg.DoModal() ) {
          LPCSTR szDocNum = (nPrintID==ID_PRINT_CHANGE_29) ? _T("29") : _T("30");
          sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, szDocNum );
          sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, szDocNum, m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_ABC: {
        CABCDlg dlg(false, this);
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_CHANGE_IN, theApp.m_sTemplatePath, _T("ABC") );
          sOut.Format(IDS_CHANGE_OUT, theApp.m_sOutPath, _T("ABC"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_ELECTIONS: {
        CElectDlg dlg(IDD_ELECTION_CHANGES, this);
        sTemplate.Format(IDS_ELECTION_LIST, theApp.m_sTemplatePath, _T("Changes") );
        sOut.Format(IDS_ELECTION_LIST, theApp.m_sOutPath, _T("Changes") );
        if ( dlg.DoModal()==IDYES ) {
          MakeInOutExt(sTemplate, sOut);
          if ( FALSE==ConvertForElect(sTemplate, sOut, dlg.m_ElectItems) )
            return;
          if ( g_fMakeXLS ) {
            ElectionsToXLS(&theElections, false);
          }
        }
        else
          return;
      }
      break;
    case ID_PRINT_CHANGE_15_6_13 : case ID_PRINT_CHANGE_25_6_1  :
    case ID_PRINT_CHANGE_26_6_9  : case ID_PRINT_CHANGE_27_6_10 :
    case ID_PRINT_CHANGE_28_6_12 : case ID_PRINT_CHANGE_29_6_13 :
    case ID_PRINT_CHANGE_30_6_13 : case ID_PRINT_CHANGE_36_7_1  :
    case ID_PRINT_CHANGE_39_7_8  : case ID_PRINT_CHANGE_40_7_8  :
    case ID_PRINT_CHANGE_51_7_8  : case ID_PRINT_CHANGE_54_7_8  :
      OnBlankItem();
      return;
  }

  if ( sTemplate.IsEmpty() )
    return;

  switch( nPrintID ) {
    case ID_PRINT_CHANGE_ABC:
      if ( FALSE==RTF_ABCChange(sTemplate, sOut, m_pRSet) )
        return;
      break;
    case ID_PRINT_CHANGE_ELECTIONS:
      break;
    default:
      if ( FALSE==UConvert(sTemplate, sOut, m_pRSet) )
        return;
  }

  OnRTFShell(sOut);
}

LRESULT CFormChange::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam) {
  LPCTSTR szMessage = (LPCTSTR)wParam;
  if ( stricmp(szMessage, "close")==0 ) {
    m_fEnableRelayEvent = true;
  }
  m_tooltip.HideTooltip();

  return TRUE;
}

BOOL CFormChange::OnCommand(WPARAM wParam, LPARAM lParam) {
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
  BOOL bResult(FALSE);
  CWnd* pControl = CWnd::FromHandle((HWND)lParam);

  switch(wNotifyCode) {
    case BN_SETFOCUS:
    case EN_SETFOCUS:
    case CBN_SETFOCUS:
      m_pFocused = pControl;
      ScrollToControl(pControl);
      if ( theApp.m_fUseHelper && m_ShownCtrlId != wCtrlId ) {
        m_tooltip.HideTooltip();
        m_ShownCtrlId = wCtrlId;
        ShowHelpTooltipSetFocus(&m_tooltip, this, m_szFormName, pControl, wCtrlId);
        m_fEnableRelayEvent = false;
      }
      break;
    case BN_KILLFOCUS:
    case EN_KILLFOCUS:
    case CBN_KILLFOCUS:
      m_tooltip.HideTooltip();
      m_fEnableRelayEvent = true;
      break;
  }

  switch( wCtrlId ) {
    case IDC_SEX:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnSexDependences();
        return bResult;
      }
      break;
    case IDC_NEW_NAME:      if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusNewName();
      break;
    case IDC_NEW_PATRONYMIC: if ( CBN_SETFOCUS==wNotifyCode )   OnSetfocusNewPatronymic();
      break;
    case IDC_CITIZENSHIP:   if ( CBN_SETFOCUS==wNotifyCode )    m_cmbCitizenship.UpdateByDefault();
      break;

    case IDC_BP_COUNTRY:    if ( CBN_SETFOCUS==wNotifyCode )    m_cmbBirthCountry.UpdateByDefault();
      break;
    case IDC_BP_REGION:     if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusRegion(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthCity);
      break;
    case IDC_BP_DISTRICT:   if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusDistrict(m_cmbBirthRegion, m_cmbBirthDistrict);
      break;
    case IDC_BP_CITY:       if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusCity(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthDistrict, m_cmbBirthCity);
      break;

    case IDC_RP_COUNTRY:    if ( CBN_SETFOCUS==wNotifyCode )    m_cmbRPCountry.UpdateByDefault();
      break;
    case IDC_RP_REGION:     if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusRegion(m_cmbRPCountry, m_cmbRPRegion, m_cmbRPCity);
      break;
    case IDC_RP_DISTRICT:   if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusDistrict(m_cmbRPRegion, m_cmbRPDistrict);
      break;
    case IDC_RP_CITY:       if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusCity(m_cmbRPCountry, m_cmbRPRegion, m_cmbRPDistrict, m_cmbRPCity);
      break;

    case IDC_DATEREG:
      if ( EN_KILLFOCUS==wNotifyCode ) {
        if ( IsFocusChild(this) ) {
          m_tooltip.HideTooltip();
          if ( FALSE==CheckDateReg(this, &m_DateReg, m_fNewRecord) )
            m_DateReg.SetFocus();
          return FALSE;
        }
      }
      break;

    case IDC_PASSPORT_BY:           if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_PassportSeria, m_PassportNumber, m_PassportBy);
      break;

  }
  m_LastCtrlId = wCtrlId;
  bResult = CEraForm::OnCommand(wParam, lParam);
  return bResult;
}

