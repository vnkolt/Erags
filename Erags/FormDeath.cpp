// FormDeath.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "FormDeath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "..\Common\DB.h"
#include "..\Common\MDB.h"

#include "ABCDlg.h"
#include "AddRsnDlg.h"
#include "BlanksDlg.h"
#include "Caches.h"
#include "CheckDateDlg.h"
#include "DateFunc.h"
#include "DataManager.h"
#include "Defaults.h"
#include "Dlg43.h"
#include "DownloadChecker.h"
#include "ElectDlg.h"
#include "EragsDoc.h"
#include "ExtNotice.h"

#include "HelpMan.h"
#include "MainFrm.h"
#include "Menu.h"
#include "MonthList.h"
#include "RNames.h"
#include "RegDlg.h"
#include "RTFCnv.h"
#include "SecReg.h"
#include "SVDlg.h"
#include "xMachine.h"



#include "..\Common\Names.h"
#include "..\Common\FHelpers.h"
#include "..\Controls\MyFileDialog.h"

extern CString  g_sChoosenDistrict;
extern CString  g_sOverString;
extern CString  g_szDBFile;
extern BOOL     g_fMakeXLS;
extern BOOL     g_fMakeDBF;

BOOL RegDlg(CPPToolTip* pTooltip);

CString GetSpecialPath(WORD CSIDL) {
  CString s;
  SHGetSpecialFolderPath(0, s.GetBuffer(MAX_PATH), CSIDL, false);
  s.ReleaseBuffer();
  return s;
}

BOOL ConvertForElect(const CString& sTemplate, const CString& sOutName, CPtrArray& array);
BOOL CheckDeathDate(CEraDateEdit* pDateReg, CEraDateEdit* pDeathDate) {

  if ( theApp.m_fExitApp || -1==theDataManager.m_Year )
    return TRUE;

  COleDateTime DateReg   = pDateReg->GetDate();
  COleDateTime DeathDate = pDeathDate->GetDate();

  if ( DateReg.GetStatus()!=COleDateTime::valid || DeathDate.GetStatus()!=COleDateTime::valid )
    return TRUE;

  CEraForm* pParent = (CEraForm*)pDateReg->GetParent();
  CWnd* pFocus = CWnd::GetFocus();
  if ( pFocus && pFocus->GetParent()!=pParent )
    return TRUE;

  if ( DeathDate > DateReg ) {
    MessageBox(AfxGetMainWnd()->m_hWnd, _T("Увага, Ви намагаєтесь визначити дату смерті, яка більш за дату реєстрації."), _T("ЕРАГС"), MB_OK|MB_ICONSTOP);
    return FALSE;
  }

  return TRUE;
}


BOOL CheckBirthDate(CEraDateEdit* pDateReg, CEraDateEdit* pBirthDate, CEraDateEdit* pDeathDate) {

  if ( theApp.m_fExitApp || -1==theDataManager.m_Year )
    return TRUE;

  COleDateTime DateReg   = pDateReg->GetDate();
  COleDateTime BirthDate = pBirthDate->GetDate();

  if ( DateReg.GetStatus()!=COleDateTime::valid || BirthDate.GetStatus()!=COleDateTime::valid )
    return TRUE;

  CEraForm* pParent = (CEraForm*)pDateReg->GetParent();
  CWnd* pFocus = CWnd::GetFocus();
  if ( pFocus && pFocus->GetParent()!=pParent )
    return TRUE;

  if ( BirthDate > DateReg ) {
    MessageBox(AfxGetMainWnd()->m_hWnd, _T("Увага, Ви намагаєтесь визначити дату народження, яка більш за дату реєстрації."), _T("ЕРАГС"), MB_OK|MB_ICONWARNING);
    return FALSE;
  }

  COleDateTime DeathDate = pDeathDate->GetDate();

  if ( DeathDate.GetStatus()!=COleDateTime::valid ) {
    return TRUE;
  }

  if ( BirthDate > DeathDate ) {
    MessageBox(AfxGetMainWnd()->m_hWnd, _T("Увага, Ви намагаєтесь визначити дату народження, яка більш за дату смерті."), _T("ЕРАГС"), MB_OK|MB_ICONWARNING);
    return FALSE;
  }

  return TRUE;
}

int FilterFuncForTax(CRSDeathes* pSet) {
  if ( COleDateTime::valid != pSet->m_DATEREG.GetStatus() ) {
    return 0;
  }
  if ( g_fNoPrintUnknowns && IsEmptyText(pSet->m_NAME) ) { // Пустое имя, значит "Невідомий"
    return 0;
  }
  if ( FALSE==g_sChoosenDistrict.IsEmpty() && pSet->m_RP_DISTRICT!=g_sChoosenDistrict)
    return 0;
  if ( g_fPeriod && g_odtFrom <= pSet->m_DATEREG && pSet->m_DATEREG <= g_odtTill ) {
    return 1;
  }
  else if ( false==g_fPeriod && pSet->m_DATEREG.GetMonth() == g_iMonth ) {
    return 1;
  }
  return 0;
}

int FilterFuncPassports(CRSDeathes* pSet) {
  int nScan(0);

/*
  int drM = pSet->m_DATEREG.GetMonth();
  int drD = pSet->m_DATEREG.GetDay();
*/
  int fM = g_odtFrom.GetMonth(), tM = g_odtTill.GetMonth();
  int fD = g_odtFrom.GetDay(), tD = g_odtTill.GetDay();

  if ( COleDateTime::valid != pSet->m_DATEREG.GetStatus() )
    return 0;
  if ( FALSE==g_sChoosenDistrict.IsEmpty() && pSet->m_RP_DISTRICT!=g_sChoosenDistrict)
    return 0;
  if ( g_fPeriod && g_odtFrom <= pSet->m_DATEREG && pSet->m_DATEREG <= g_odtTill) {
    nScan++;
  }
  else if ( false==g_fPeriod && pSet->m_DATEREG.GetMonth() == g_iMonth ) {
    nScan++;
  }
  else
    return 0;
  if ( g_fNoPrintUnknowns && IsEmptyText(pSet->m_NAME) ) { // Пустое имя, значит "Невідомий"
    return 0;
  }
  bool fPassport;
  bool fMilitDoc;
  fPassport = (false==IsEmptyText(pSet->m_PASSPORT_SERIA) && false==IsEmptyText(pSet->m_PASSPORT_NUMBER) );
  fMilitDoc = (false==IsEmptyText(pSet->GetMilitaryCardSeria()) && false==IsEmptyText(pSet->GetMilitaryCardNumber()) );

  switch(CMonthList::m_PrintWhat) {
    case PRINT_ALLDOCS:
      if ( fPassport && fMilitDoc )
        nScan = 2;
      else if ( fPassport || fMilitDoc )
        nScan = 1;
      else
        nScan = 0;
      break;
    case PRINT_PASPORTS:
      nScan = fPassport ? 1 : 0;
      break;
    case PRINT_MILCARS:
      nScan = fMilitDoc  ? 2 : 0;
      break;
  }
  return nScan;
}

int FilterFuncForChildren(CRSDeathes* pSet) {
  if ( 0==FilterFuncForTax(pSet) )
    return 0;
  Duration d = duration(pSet->m_BIRTH_DATE, pSet->m_DEATH_DATE);
  return (d.years < 16) ? 1 : 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFormDeath

IMPLEMENT_DYNCREATE(CFormDeath, CEraForm)

CFormDeath::CFormDeath()
           :CEraForm(CFormDeath::IDD), m_pRSet((CRSDeathes*&)m_pSet) {
  //{{AFX_DATA_INIT(CFormDeath)
  //}}AFX_DATA_INIT
  m_szFormName = _T("FORM_DEATH");
}

CFormDeath::~CFormDeath() {
}

void CFormDeath::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() )
    m_fSex.SetFocus();
}

void CFormDeath::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LBL_AGE:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CDaoRecordViewBG::SetScaleFlags(pWnd, wFlags);
  }
}

void CFormDeath::DoDataExchange(CDataExchange* pDX) {
  if ( FALSE==pDX->m_bSaveAndValidate ) {
    m_SURNAME_before_save     = m_pRSet->m_SURNAME;
    m_NAME_before_save        = m_pRSet->m_NAME;
    m_PATRONYMIC_before_save  = m_pRSet->m_PATRONYMIC;
    m_NUMBER_before_save      = m_pRSet->m_NUMBER;
    m_DATEREG_before_save     = m_pRSet->m_DATEREG;
  }
	CEraForm::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFormDeath)
  DDX_Control(pDX, IDC_SEX, m_fSex);
  DDX_Control(pDX, IDC_CITIZENSHIP, m_cmbCitizenship);
//  DDX_Control(pDX, IDC_DATEREG, m_DateReg);
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_SURNAME, m_Surname);
  DDX_Control(pDX, IDC_NAME, m_Name);
  DDX_Control(pDX, IDC_PATRONYMIC, m_Patronymic);
  DDX_Control(pDX, IDC_LBL_AGE, m_lblAge);
//  DDX_Control(pDX, IDC_DEATH_DATE, m_DeathDate);
  DDX_Control(pDX, IDC_DP_COUNTRY, m_cmbDeathCountry);
  DDX_Control(pDX, IDC_DP_REGION, m_cmbDeathRegion);
  DDX_Control(pDX, IDC_DP_DISTRICT, m_cmbDeathDistrict);
  DDX_Control(pDX, IDC_DP_CITY, m_cmbDeathCity);
  DDX_Control(pDX, IDC_REASON_PSEUDO, m_cmbReasonPseudo);
  DDX_Control(pDX, IDC_REASON, m_Reason);
  DDX_Control(pDX, IDC_MEDICAL_CERT_TYPE, m_cmbMidicalCertType);
  DDX_Control(pDX, IDC_MEDICAL_CERT_NUMBER, m_MedicalCertNumber);
//  DDX_Control(pDX, IDC_MEDICAL_CERT_DATE, m_MedicalCertDate);
  DDX_Control(pDX, IDC_MEDICAL_CERT_BY_PSEUDO, m_cmbMedicalCertByPseudo);
  DDX_Control(pDX, IDC_MEDICAL_CERT_BY, m_cmbMedicalCertBy);
//  DDX_Control(pDX, IDC_BIRTH_DATE, m_BirthDate);
  DDX_Control(pDX, IDC_BP_COUNTRY, m_cmbBirthCountry);
  DDX_Control(pDX, IDC_BP_REGION, m_cmbBirthRegion);
  DDX_Control(pDX, IDC_BP_DISTRICT, m_cmbBirthDistrict);
  DDX_Control(pDX, IDC_BP_CITY, m_cmbBirthCity);
  DDX_Control(pDX, IDC_RP_ZIPCODE, m_RPIndex);
  DDX_Control(pDX, IDC_RP_COUNTRY, m_cmbRPCountry);
  DDX_Control(pDX, IDC_RP_REGION, m_cmbRPRegion);
  DDX_Control(pDX, IDC_RP_DISTRICT, m_cmbRPDistrict);
  DDX_Control(pDX, IDC_RP_CITY, m_cmbRPCity);
  DDX_Control(pDX, IDC_RP_STREET, m_cmbRPStreet);
  DDX_Control(pDX, IDC_RP_HOUSE, m_RPHouse);
  DDX_Control(pDX, IDC_RP_FLAT, m_RPFlat);
  DDX_Control(pDX, IDC_IN, m_IN);
  DDX_Control(pDX, IDC_PASSPORT_TYPE, m_PassportType);
  DDX_Control(pDX, IDC_PASSPORT_SERIA, m_PassportSeria);
  DDX_Control(pDX, IDC_PASSPORT_NUMBER, m_PassportNumber);
//  DDX_Control(pDX, IDC_PASSPORT_DATE, m_PassportDate);
  DDX_Control(pDX, IDC_PASSPORT_BY, m_cmbPassportBy);
  DDX_Control(pDX, IDC_DECLARANT_NAME, m_DeclarantName);
  DDX_Control(pDX, IDC_DECLARANT_ADDRESS, m_DeclarantAddress);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_TYPE, m_DeclarantPassportType);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_SERIA, m_DeclarantPassportSeria);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_NUMBER, m_DeclarantPassportNumber);
//  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_DATE, m_DeclarantPassportDate);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_BY, m_cmbDeclarantPassportBy);
  DDX_Control(pDX, IDC_CERTIFICATE_SERIA, m_CertificateSeria);
  DDX_Control(pDX, IDC_CERTIFICATE_NUMBER, m_CertificateNumber);
  DDX_Control(pDX, IDC_NOTICE, m_Notice);
	//}}AFX_DATA_MAP
  DDX_FieldCheck(pDX, IDC_SEX, m_pRSet->m_SEX, m_pRSet);
  DDX_FieldText(pDX, IDC_CITIZENSHIP, m_pRSet->m_CITIZENSHIP, m_pRSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, m_pRSet->m_DATEREG);
  //DDX_FieldText(pDX, IDC_DATEREG, m_pRSet->m_DATEREG, m_pRSet);
  DDX_FieldText(pDX, IDC_NUMBER, m_pRSet->m_NUMBER, m_pRSet);
  DDX_FieldText(pDX, IDC_SURNAME, m_pRSet->m_SURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_NAME, m_pRSet->m_NAME, m_pRSet);
  DDX_FieldText(pDX, IDC_PATRONYMIC, m_pRSet->m_PATRONYMIC, m_pRSet);
  DDX_OleDate(pDX, IDC_DEATH_DATE, m_DeathDate, m_pRSet->m_DEATH_DATE);
  DDX_FieldText(pDX, IDC_DP_COUNTRY, m_pRSet->m_DP_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_DP_REGION, m_pRSet->m_DP_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_DP_DISTRICT, m_pRSet->m_DP_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_DP_CITY, m_pRSet->m_DP_CITY, m_pRSet);

  DDX_FieldText(pDX, IDC_REASON, m_pRSet->m_CAUSE_OF_DEATH, m_pRSet);
  DDX_FieldText(pDX, IDC_MEDICAL_CERT_TYPE, m_pRSet->m_MEDICAL_CERT_TYPE, m_pRSet);
  DDX_FieldText(pDX, IDC_MEDICAL_CERT_NUMBER, m_pRSet->m_MEDICAL_CERT_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_MEDICAL_CERT_DATE, m_MedicalCertDate, m_pRSet->m_MEDICAL_CERT_DATE);
  DDX_FieldText(pDX, IDC_MEDICAL_CERT_BY, m_pRSet->m_MEDICAL_CERT_BY, m_pRSet);

  DDX_OleDate(pDX, IDC_BIRTH_DATE, m_BirthDate, m_pRSet->m_BIRTH_DATE);
  DDX_FieldText(pDX, IDC_BP_COUNTRY, m_pRSet->m_BP_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_REGION, m_pRSet->m_BP_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_DISTRICT, m_pRSet->m_BP_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_BP_CITY, m_pRSet->m_BP_CITY, m_pRSet);

  DDX_FieldText(pDX, IDC_RP_ZIPCODE, m_pRSet->m_RP_ZIPCODE, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_COUNTRY, m_pRSet->m_RP_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_REGION, m_pRSet->m_RP_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_DISTRICT, m_pRSet->m_RP_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_CITY, m_pRSet->m_RP_CITY, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_STREET, m_pRSet->m_RP_STREET, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_HOUSE, m_pRSet->m_RP_HOUSE, m_pRSet);
  DDX_FieldText(pDX, IDC_RP_FLAT, m_pRSet->m_RP_FLAT, m_pRSet);

  DDX_FieldText(pDX, IDC_IN, m_pRSet->m_TAX_CODE, m_pRSet);
  DDX_MSButton(pDX, IDC_PASSPORT_TYPE, m_PassportType, m_pRSet->m_PASSPORT_TYPE);
  DDX_FieldText(pDX, IDC_PASSPORT_SERIA, m_pRSet->m_PASSPORT_SERIA, m_pRSet);
  DDX_FieldText(pDX, IDC_PASSPORT_NUMBER, m_pRSet->m_PASSPORT_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_PASSPORT_DATE, m_PassportDate, m_pRSet->m_PASSPORT_DATE);
  DDX_FieldText(pDX, IDC_PASSPORT_BY, m_pRSet->m_PASSPORT_BY, m_pRSet);
  
  DDX_FieldText(pDX, IDC_DECLARANT_NAME, m_pRSet->m_DECLARANT_NAME, m_pRSet);
  DDX_FieldText(pDX, IDC_DECLARANT_ADDRESS, m_pRSet->m_DECLARANT_ADDRESS, m_pRSet);
  DDX_MSButton(pDX, IDC_DECLARANT_PASSPORT_TYPE, m_DeclarantPassportType, m_pRSet->m_DECLARANT_PASSPORT_TYPE);
  DDX_FieldText(pDX, IDC_DECLARANT_PASSPORT_SERIA, m_pRSet->m_DECLARANT_PASSPORT_SERIA, m_pRSet);
  DDX_FieldText(pDX, IDC_DECLARANT_PASSPORT_NUMBER, m_pRSet->m_DECLARANT_PASSPORT_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_DECLARANT_PASSPORT_DATE, m_DeclarantPassportDate, m_pRSet->m_DECLARANT_PASSPORT_DATE);
  DDX_FieldText(pDX, IDC_DECLARANT_PASSPORT_BY, m_pRSet->m_DECLARANT_PASSPORT_BY, m_pRSet);

  DDX_FieldText(pDX, IDC_CERTIFICATE_SERIA, m_pRSet->m_CERTIFICATE_SERIA, m_pRSet);
  DDX_FieldText(pDX, IDC_CERTIFICATE_NUMBER, m_pRSet->m_CERTIFICATE_NUMBER, m_pRSet);
  DDX_FieldText(pDX, IDC_NOTICE, m_pRSet->m_NOTICE, m_pRSet);

/************************************** : by VK at 04.12.2004 5:02:23 **\
  if ( pDX->m_bSaveAndValidate ) {
    if ( m_DATEREG_before_save    != m_pRSet->m_DATEREG   ||
         m_NUMBER_before_save     != m_pRSet->m_NUMBER    ||
         m_SURNAME_before_save    != m_pRSet->m_SURNAME   ||
         m_NAME_before_save       != m_pRSet->m_NAME      ||
         m_PATRONYMIC_before_save != m_pRSet->m_PATRONYMIC )
  }
  else
    OnUpdateBirthDate();
\************************************** : by VK at 04.12.2004 5:02:31 **/
  if ( FALSE==pDX->m_bSaveAndValidate ) {
    OnUpdateBirthDate();
  }
  m_ID = m_pRSet->m_ID;
}

BEGIN_MESSAGE_MAP(CFormDeath, CEraForm)
  //{{AFX_MSG_MAP(CFormDeath)
  ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
  ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
  ON_EN_SETFOCUS(IDC_DEATH_DATE, OnSetfocusDeathDate)
  ON_EN_UPDATE(IDC_BIRTH_DATE, OnUpdateBirthDate)
  ON_CBN_SETFOCUS(IDC_REASON_PSEUDO, OnSetfocusReasonPseudo)
  ON_CBN_SELENDOK(IDC_REASON_PSEUDO, OnSelendokReasonPseudo)
  ON_EN_SETFOCUS(IDC_MEDICAL_CERT_DATE, OnSetfocusMedicalCertDate)
	ON_CBN_SELENDOK(IDC_MEDICAL_CERT_BY_PSEUDO, OnSelendokMedicalCertByPseudo)
	ON_CBN_SELCHANGE(IDC_MEDICAL_CERT_BY_PSEUDO, OnSelchangeMedicalCertByPseudo)
	ON_EN_SETFOCUS(IDC_DECLARANT_NAME, OnSetfocusDeclarantName)
	ON_EN_KILLFOCUS(IDC_DECLARANT_NAME, OnKillfocusDeclarantName)
	ON_EN_SETFOCUS(IDC_DECLARANT_ADDRESS, OnSetfocusDeclarantAddress)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_SERIA, OnSetfocusCertificateSeria)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_NUMBER, OnSetfocusCertificateNumber)
	ON_EN_CHANGE(IDC_CERTIFICATE_NUMBER, OnChangeCertificateNumber)
	ON_EN_SETFOCUS(IDC_NOTICE, OnSetfocusNotice)
	ON_EN_SETFOCUS(IDC_REASON, OnSetfocusReason)
	ON_EN_KILLFOCUS(IDC_REASON, OnKillfocusReason)
  ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
	ON_CBN_SELCHANGE(IDC_REASON_PSEUDO, OnSelendokReasonPseudo)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDeath diagnostics

#ifdef _DEBUG
void CFormDeath::AssertValid() const {
  CDaoRecordView::AssertValid();
}

void CFormDeath::Dump(CDumpContext& dc) const {
  CDaoRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormDeath message handlers
CDaoRecordset* CFormDeath::OnGetRecordset() {
  if (m_pSet != NULL)
    return m_pSet;

  m_pSet = new CRSDeathes(&theDataManager.m_dbYear);
  m_pSet->Open();

  m_pRSet->SetCurrentIndex(_T("NUMBER"));
  try {
    if ( FALSE==m_pRSet->IsBOF() && FALSE==m_pRSet->IsEOF() )
      m_pRSet->MoveLast();
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }
  return m_pRSet;
}

BOOL CFormDeath::IsMilitary() {
  if ( NULL==m_pRSet )
    return FALSE;
  if ( m_pRSet->GetMilitaryCardSeria().IsEmpty() )
    return FALSE;
  if ( m_pRSet->GetMilitaryCardNumber().IsEmpty() )
    return FALSE;
  return TRUE;
}
CString CFormDeath::GetMilitaryInfo() {
  CString s;
  s.Format(_T("ВК %s № %s від %s"), 
           m_pRSet->GetMilitaryCardSeria(),
           m_pRSet->GetMilitaryCardNumber(),
           m_pRSet->GetMilitaryCardDate() );
  return s;
}
BOOL CFormDeath::OnMove(UINT nIDMoveCommand) {
  if ( NULL==m_pRSet )
    return FALSE;

  if ( m_pRSet->IsBOF() && m_pRSet->IsEOF() )
    return FALSE;
  BOOL bRet = CEraForm::OnMove(nIDMoveCommand);
  if ( bRet ) {
    OnSexDependences();

    if ( IsMilitary() ) {
      GetDlgItem(IDC_LBL_MILITARY)->SetWindowText( GetMilitaryInfo() );
      GetDlgItem(IDC_LBL_MILITARY)->ShowWindow( SW_SHOW );
    }
    else {
      GetDlgItem(IDC_LBL_MILITARY)->ShowWindow( SW_HIDE );
    }

    theCitizenships.FillCombo( m_cmbCitizenship, m_pRSet->m_CITIZENSHIP );

    theGeoCache.FillCountryCB(m_cmbDeathCountry, m_pRSet->m_DP_COUNTRY);
    theGeoCache.FillRegionCB(m_cmbDeathRegion, m_cmbDeathCountry, m_pRSet->m_DP_REGION);
    theGeoCache.FillDistrictCB(m_cmbDeathDistrict, m_cmbDeathRegion, m_pRSet->m_DP_DISTRICT);

    theGeoCache.FillCountryCB(m_cmbBirthCountry, m_pRSet->m_BP_COUNTRY);
    theGeoCache.FillRegionCB(m_cmbBirthRegion, m_cmbBirthCountry, m_pRSet->m_BP_REGION);
    theGeoCache.FillDistrictCB(m_cmbBirthDistrict, m_cmbBirthRegion, m_pRSet->m_BP_DISTRICT);

    theGeoCache.FillCountryCB(m_cmbRPCountry, m_pRSet->m_RP_COUNTRY);
    theGeoCache.FillRegionCB(m_cmbRPRegion, m_cmbRPCountry, m_pRSet->m_RP_REGION);
    theGeoCache.FillDistrictCB(m_cmbRPDistrict, m_cmbRPRegion, m_pRSet->m_RP_DISTRICT);

    theGeoCache.FillCityCB(m_cmbDeathCity, m_cmbDeathRegion, m_cmbDeathDistrict, m_pRSet->m_DP_CITY);
    theGeoCache.FillCityCB(m_cmbBirthCity, m_cmbBirthRegion, m_cmbBirthDistrict, m_pRSet->m_BP_CITY);
    theGeoCache.FillCityCB(m_cmbRPCity,    m_cmbRPRegion,    m_cmbRPDistrict,    m_pRSet->m_RP_CITY);

    theMIAs.Add( m_cmbPassportBy, m_pRSet->m_PASSPORT_BY );
    theMIAs.Add( m_cmbDeclarantPassportBy, m_pRSet->m_DECLARANT_PASSPORT_BY );
    theStreets.Add( m_cmbRPStreet, m_pRSet->m_RP_STREET );

    theHospitals.FillCombo(m_cmbMedicalCertByPseudo, m_cmbMedicalCertBy, m_pRSet->m_MEDICAL_CERT_BY);

    m_sReasonSaved = m_pRSet->m_CAUSE_OF_DEATH;

    OnUpdateBirthDate();
  }
  return bRet;
}


CRSDeathes* CFormDeath::GetRecordset() {
  CRSDeathes* pSet = (CRSDeathes*) OnGetRecordset();
  ASSERT(pSet != NULL && pSet->IsKindOf(RUNTIME_CLASS(CRSDeathes)));
  return pSet;
}
#ifndef FREE_LICENCE
BOOL CFormDeath::IsRDFFieldsDirty() {
  if ( m_pRSet ) {
    SetChangedBy(m_pRSet, m_pRSet->m_EXTNOTES);
    // 	m_RP_REGION, m_RP_DISTRICT, m_RP_CITY;
    if ( m_pRSet->IsFieldDirty(&m_pRSet->m_RP_REGION)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_RP_DISTRICT) ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_RP_CITY) )
      return true;
  }
  return false;
}
void CFormDeath::SetRDFFields() {
  if ( IsEmptyText(m_pRSet->m_SURNAME) || IsEmptyText(m_pRSet->m_NAME) )
    return;
  SaveGeoValidation(m_pRSet->m_RP_REGION, m_pRSet->m_RP_DISTRICT, m_pRSet->m_RP_CITY, true);
  SaveDateValidation(&m_pRSet->m_DATEREG, &m_pRSet->m_DEATH_DATE, &m_pRSet->m_MEDICAL_CERT_DATE);
}
#endif // #FREE_LICENCE

bool CFormDeath::LoadCauses() {
  m_CausesCache.RemoveAll();

  CString sql = _T("SELECT PSEUDONYM, CAUSE FROM CAUSESOFDEATH");
  CDaoQueryDef qd(&theDataManager.m_dbLists);
  CDaoRecordset rs(&theDataManager.m_dbLists);
  try {
    qd.Create(NULL,sql);
    rs.Open(&qd);
    while ( !rs.IsEOF() ) {
      CString sPseudo = Trim(iDBStringField(rs, 0));
      CString sCause  = Trim(iDBStringField(rs, 1));
      if ( FALSE==sPseudo.IsEmpty() && FALSE==sCause.IsEmpty() )
        m_CausesCache.SetAt(sPseudo, sCause);
      rs.MoveNext();
    }
  }
  catch (CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError(); // to do logstring
    #endif
    e->Delete();
    return false;
  }
  return true;
}
void CFormDeath::FillCauseCmb() {
  m_cmbReasonPseudo.ResetContent();
  POSITION pos = m_CausesCache.GetStartPosition();
  int nItem(0);
  while ( pos ) {
    CString sPseudo, sReason;
    m_CausesCache.GetNextAssoc(pos, sPseudo, sReason);
    m_cmbReasonPseudo.AddRow(sPseudo, sReason);
    nItem++;
  }
}

void CFormDeath::OnBlank(const CString& szTemplate, const CString& szOut) {
  if ( RTF_DeathBlank(szTemplate, szOut, m_pRSet) ) {
    OnRTFShell(szOut);
  }
}

void CFormDeath::OnPrint(UINT nPrintID) {
  CString szDBFScript;
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

  if ( FALSE==CEraForm::OnMove(0) )  // Save data
    return;

#ifndef FREE_LICENCE
    theRegTimer.Next();
#endif

  g_nDocType = DOCTYPE_OTHER;
  BOOL    fDbf  = false;
  LPCTSTR szDBFFor = NULL;

  CString sTemplate, sOut;
  int nPage1(0), nPage2(0);
  switch ( nPrintID ) {
    case ID_PRINT_DEATH_ACT:
      g_nDocType = DOCTYPE_ACT;
      sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("Act") );
      sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("Act"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_DEATH_CERIFICATE: {
        g_nDocType = DOCTYPE_CERT;
        CSVDlg dlg(this, IDD_SVID);
        dlg.m_szFormSect = _T("DEATH_FORM");
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("Certificate") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("Certificate"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DEATH_DOV:
      sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("11") );
      sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("11"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_DEATH_DOV43: {
        CDlg43 dlg(43, this);
        dlg.m_sTo = m_DeclarantName.GetText();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("43") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("43"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DEATH_PASSPORTS: {
        CString s;
        s.LoadString(ID_PRINT_DEATH_PASSPORTS);
        CMonthList dlg(nPrintID, TRUE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("/n") );
        dlg.m_SectName = _T("DEATH_PASSPORTS");
        dlg.m_MaxPage1 = 13;
        dlg.m_MaxPage2 = 20;
        if ( dlg.DoModal()==IDYES ) {
          LPCTSTR szWhat;
          switch(CMonthList::m_PrintWhat) {
            case PRINT_PASPORTS:  szWhat = _T("Passports"); break;
            case PRINT_MILCARS:   szWhat = _T("MilCards");  break;
            default:              szWhat = _T("AllDocs");   break;
          }
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, szWhat );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, szWhat, g_iMonth);
          MakeInOutExt(sTemplate, sOut);
        }
        nPage1 = dlg.m_MaxPage1;
        nPage2 = dlg.m_MaxPage2;
      }
      break;
    case ID_PRINT_DEATH_FORTAX: {
        szDBFFor = _T("податкової служби");
        fDbf  = true;
        CString s;
        s.LoadString(ID_PRINT_DEATH_FORTAX);
        CMonthList dlg(nPrintID, FALSE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("/n") );
        dlg.m_SectName = _T("DEATH_FORTAX");
        dlg.m_MaxPage1 = 15;
        dlg.m_MaxPage2 = 18;
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("ToTax") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("ToTax"), g_iMonth);
          MakeInOutExt(sTemplate, sOut);
        }
        nPage1 = dlg.m_MaxPage1;
        nPage2 = dlg.m_MaxPage2;
      }
      break;
    case ID_PRINT_DEATH_FORTAX_13: {
        szDBFFor = _T("податкової служби");
        fDbf  = true;
        CString s;
        s.LoadString(ID_PRINT_DEATH_FORTAX_13);
        CMonthList dlg(nPrintID, FALSE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("/n") );
        dlg.m_SectName = _T("DEATH_FORTAX_13");
        dlg.m_MaxPage1 = 46;
        dlg.m_MaxPage2 = 61;
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("ToTax_13") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("ToTax_13"), g_iMonth);
          MakeInOutExt(sTemplate, sOut);
        }
        nPage1 = dlg.m_MaxPage1;
        nPage2 = dlg.m_MaxPage2;
      }
      break;
    case ID_PRINT_DEATH_FORSOCPROT: {
        szDBFFor = _T("органу соцзахисту");
        fDbf  = true;
        CString s;
        s.LoadString(ID_PRINT_DEATH_FORSOCPROT);
        CMonthList dlg(nPrintID, FALSE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("/n") );
        dlg.m_SectName = _T("DEATH_SOCPROT");
        dlg.m_MaxPage1 = 39;
        dlg.m_MaxPage2 = 55;
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("ToSocProt") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("ToSocProt"), g_iMonth);
          MakeInOutExt(sTemplate, sOut);
        }
        nPage1 = dlg.m_MaxPage1;
        nPage2 = dlg.m_MaxPage2;
      }
      break;
    case ID_PRINT_DEATH_CHILDREN: {
        CString s;
        s.LoadString(ID_PRINT_DEATH_CHILDREN);
        CMonthList dlg(nPrintID, TRUE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("/n") );
        dlg.m_SectName = _T("DEATH_CHILDREN");
        dlg.m_MaxPage1 = 44;
        dlg.m_MaxPage2 = 55;
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("Children") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("Children"), g_iMonth);
          MakeInOutExt(sTemplate, sOut);
        }
        nPage1 = dlg.m_MaxPage1;
        nPage2 = dlg.m_MaxPage2;
      }
      break;
    case ID_PRINT_DEATH_ABC: {
        CABCDlg dlg(true, this);
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DEATH_IN, theApp.m_sTemplatePath, _T("ABC") );
          sOut.Format(IDS_DEATH_OUT, theApp.m_sOutPath, _T("ABC"), m_DateReg.GetDate().GetYear());
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DEATH_ELECTIONS: {
        CElectDlg dlg(IDD_ELECTION_DEATH, this);
        sTemplate.Format(IDS_ELECTION_LIST, theApp.m_sTemplatePath, _T("Deceases") );
        sOut.Format(IDS_ELECTION_LIST, theApp.m_sOutPath, _T("Deceases") );
        if ( dlg.DoModal()==IDYES ) {
          MakeInOutExt(sTemplate, sOut);
          if ( FALSE==ConvertForElect(sTemplate, sOut, dlg.m_ElectItems) )
            return;
          if ( g_fMakeXLS ) {
            ElectionsToXLS(&theElections, true);
          }
        }
        else
          return;
      }
      break;
    case ID_PRINT_DEATH_10_3_11 : case ID_PRINT_DEATH_11_3_12 : case ID_PRINT_DEATH_12_3_13 :
    case ID_PRINT_DEATH_13_3_13 : case ID_PRINT_DEATH_32_7_1  : case ID_PRINT_DEATH_39_7_8  :
    case ID_PRINT_DEATH_40_7_8  : case ID_PRINT_DEATH_43_7_8  : case ID_PRINT_DEATH_54_7_8  :
      OnBlankItem();
      return;
    case ID_PRINT_BLANK_REGISTER: {
        CBlanksDlg dlg(m_pRSet->m_DATEREG, this);
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_PATH_NAME_EXT, theApp.m_sTemplatePath, _T("Register.11.4.4"), _T("rtf") );
          sOut.Format(IDS_PATH_NAME_EXT, theApp.m_sOutPath,           _T("Register.11.4.4"), _T("rtf") );
          MakeInOutExt(sTemplate, sOut);
        }
      }
      break;
  }

  if ( sTemplate.IsEmpty() )
    return;

  int scanFrom = 0;

  switch( nPrintID ) {
    case ID_PRINT_DEATH_PASSPORTS:
      if ( PRINT_MILCARS==CMonthList::m_PrintWhat)
        scanFrom++;
      if ( FALSE==ConvertTable(_T("список паспортів"), sTemplate, sOut, NULL, m_pRSet, nPage1, nPage2, FilterFuncPassports, scanFrom) )
        return;
      break;
    case ID_PRINT_DEATH_FORTAX:
      if ( FALSE==ConvertTable(_T("список до податкової"), sTemplate, sOut, szDBFScript, m_pRSet, nPage1, nPage2, FilterFuncForTax) )
        return;
      break;
    case ID_PRINT_DEATH_FORTAX_13:
    case ID_PRINT_DEATH_FORSOCPROT:
      if ( FALSE==ConvertTable(_T("список до органу соцзахисту"), sTemplate, sOut, szDBFScript, m_pRSet, nPage1, nPage2, FilterFuncForTax) )
        return;
      break;
    case ID_PRINT_DEATH_CHILDREN:
      if ( FALSE==ConvertTable(_T("список померлих дітей"), sTemplate, sOut, NULL, m_pRSet, nPage1, nPage2, FilterFuncForChildren) )
        return;
      break;
    case ID_PRINT_DEATH_ABC:
      if ( FALSE==RTF_ABCDeath(sTemplate, sOut, m_pRSet) )
        return;
      break;
    case ID_PRINT_DEATH_ELECTIONS:
      break;
    case ID_PRINT_BLANK_REGISTER :
      if ( false==ConvertForBlankRegister(sTemplate, sOut) ) {
        return;
      }
      break;
    default:
      if ( FALSE==UConvert(sTemplate, sOut, m_pRSet) )
        return;
      break;
  }

  if ( fDbf && g_fMakeDBF && FileExists(g_szDBFile) ) {
    TCHAR szFile[MAX_PATH+2];
    CString szTitle, szDir;
    sprintf(szFile, "%s", GetFileName(g_szDBFile));
    szDir = GetSpecialPath(CSIDL_DESKTOP);
    szTitle.Format(_T("Вкажіть ім'я DBF-файлу для %s"), szDBFFor);
    CMyFileDialog ofd(false, "*.dbf", NULL, OFN_HIDEREADONLY|OFN_LONGNAMES, _T("DBF файли (*.dbf)|*.dbf|"), AfxGetMainWnd());
    ofd.m_fEnableTemplate = false;
    ofd.SetTitle(0, szTitle);
    ofd.m_ofn.lpstrInitialDir = szDir;
    ofd.m_ofn.lpstrFile       = szFile;
    ofd.m_ofn.nMaxFile        = MAX_PATH;
    if ( IDOK==ofd.DoModal() ) {
      CopyFile(g_szDBFile, ofd.GetPathName(), false);
    }
  }

  OnRTFShell(sOut);
}

void CFormDeath::OnSexDependences() {
  CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
  if ( NULL==pDoc )
    return;
  CString sName = m_pRSet->m_NAME;
  CString sPatronymic = m_pRSet->m_PATRONYMIC;
  if ( m_fSex.IsOn() ) { // Male
    theMNames.FillCombo( m_Name, m_pRSet->m_NAME, FALSE==m_Name.IsMale() );
    theMPatronymics.FillCombo( m_Patronymic, m_pRSet->m_PATRONYMIC, FALSE==m_Patronymic.IsMale() );
    m_Name.SetMale();
    m_Patronymic.SetMale();
  }
  else {                // Female
    theWNames.FillCombo( m_Name, m_pRSet->m_NAME, FALSE==m_Name.IsFemale() );
    theWPatronymics.FillCombo( m_Patronymic, m_pRSet->m_PATRONYMIC, FALSE==m_Patronymic.IsFemale() );
    m_Name.SetFemale();
    m_Patronymic.SetFemale();
  }
  if ( !sName.IsEmpty() ) {
    int nItem = m_Name.FindString(-1, sName);
    if ( CB_ERR == nItem ) 
      nItem = m_Name.AddString(sName);
    m_Name.SelectString(-1, sName);
  }
  if ( !sPatronymic.IsEmpty() ) {
    int nItem = m_Patronymic.FindString(-1, sPatronymic);
    if ( CB_ERR == nItem )
      nItem = m_Patronymic.AddString(sPatronymic);
    m_Patronymic.SelectString(-1, sPatronymic);
  }
}

void CFormDeath::OnInitialUpdate() {
  BeginWaitCursor();
  GetRecordset();

/************************************** : by VK at 04.12.2004 5:02:44 **\
  ClearNavigateBars();
\************************************** : by VK at 04.12.2004 5:02:46 **/
//  srand( (unsigned)time( NULL ) );

/************************************** : by VK at 06.11.2005 4:36:44 **\
  if ( m_lblAge.GetSafeHwnd()==0 )
    m_lblAge.SubclassDlgItem(IDC_LBL_AGE, this);
\************************************** : by VK at 06.11.2005 4:36:47 **/

  ((CMainFrame*)AfxGetMainWnd())->m_pDeathFrame = GetParentFrame();

  m_nPrinPos = CONTEXT_DEATH; // Смерть

//  m_cmbReasonPseudo.Create(_T("MultiColumnComboBox"), _T(""), WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, NULL);
  CEraForm::OnInitialUpdate();
  //CDaoRecordView::OnInitialUpdate();

  m_cmbReasonPseudo.FormatComboBox(2, 0);
  m_cmbReasonPseudo.SetColumnWidth(64, 512);

  LoadCauses();
  FillCauseCmb();

  if (m_pRSet->IsOpen()) {
/************************************** : by VK at 26.05.2006 22:59:37 **\
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
\************************************** : by VK at 26.05.2006 22:59:41 **/

    CString strTitle = m_pRSet->m_pDatabase->GetName();
    strTitle += _T(" - Смерті");
    CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
    pDoc->SetTitle(strTitle);

    m_fSex.SetText( _T("Актовий запис про смерть громадянина"), _T("Актовий запис про смерть громадянки") );
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetIcons(IDI_CROSSM, IDI_CROSSW);

    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);

    m_cmbCitizenship.SetDefault( g_szDefCitizenship );

    m_cmbDeathCountry.SetDefault( theIniCache.GetCOUNTRY() );
    m_cmbBirthCountry.SetDefault( theIniCache.GetCOUNTRY() );
    m_cmbRPCountry.SetDefault( theIniCache.GetCOUNTRY() );

    m_Reason.m_fSelectAll = false;
    m_DeclarantName.m_fSelectAll = false;

/************************************** : by VK at 26.01.2004 11:03:11 **\
    m_cmbDeathRegion.SetDefault( theIniCache.GetREGION() );
    m_cmbBirthRegion.SetDefault( theIniCache.GetREGION() );
    m_cmbRPRegion.SetDefault( theIniCache.GetREGION() );

    m_cmbDeathDistrict.SetDefault(theIniCache.GetDISTRICT());
    m_cmbBirthDistrict.SetDefault(theIniCache.GetDISTRICT());
    m_cmbRPDistrict.SetDefault(theIniCache.GetDISTRICT());

    m_cmbDeathCity.SetDefault(theIniCache.GetCITY());
    m_cmbBirthCity.SetDefault(theIniCache.GetCITY());
    m_cmbRPCity.SetDefault(theIniCache.GetCITY());
\************************************** : by VK at 26.01.2004 11:03:16 **/
    m_cmbPassportBy.SetDefault( theIniCache.GetByROVD() );
    m_cmbDeclarantPassportBy.SetDefault( theIniCache.GetByROVD() );

//    m_cmbMidicalCertType.SetDroppedWidth(320);

    theHospitals.FillCombo(m_cmbMedicalCertByPseudo, m_cmbMedicalCertBy, m_pRSet->m_MEDICAL_CERT_BY);
    theStreets.FillCombo( m_cmbRPStreet, m_pRSet->m_RP_STREET );
    theMIAs.FillCombo( m_cmbPassportBy, m_pRSet->m_PASSPORT_BY );
    theMIAs.FillCombo( m_cmbDeclarantPassportBy, m_pRSet->m_DECLARANT_PASSPORT_BY );

    m_IN.SetMask(_T("9999999999"));

    OnMove(ID_RECORD_LAST);
    m_fSex.SetFocus();
    if ( m_pRSet->IsEOF() && m_pRSet->IsBOF() )
      EnableForm(FALSE);

    m_fSetfocusDeclarantName = false;

  }
  EndWaitCursor();

  BOOL fQuit = false;

#ifndef FREE_LICENCE
  if ( FALSE==RegDlg(&m_tooltip) ) {
    fQuit = true;
    AfxGetMainWnd()->PostMessage(WM_QUIT);
  }
#endif // FREE_LICENCE
  EmptyTable();
  if ( false==fQuit ) {
    RunDownloadUpdates();
  }
}

void CFormDeath::OnSetfocusDatereg() {
  SetDefaultDateReg(IDD_FORM_BIRTH);
}

void CFormDeath::OnSetfocusNumber() {
  if ( 0==m_pRSet->m_NUMBER && SetDefaultNumber(m_pRSet->m_NUMBER) ) {
    m_pRSet->Edit();
    m_pRSet->Update();
    UpdateData(TRUE);
    m_pRSet->SetBookmark( m_pRSet->GetLastModifiedBookmark() );
    SetBookMarks();
  }
}

void CFormDeath::OnSetfocusDeathDate() {
  CString s;
  m_DeathDate.GetWindowText(s);
  if ( s.IsEmpty() ) {
    COleDateTime odt = m_DateReg.GetDate();
    if ( COleDateTime::valid==odt.GetStatus() ) {
      odt -= COleDateTimeSpan(1, 0, 0, 0);
      s.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear());
      m_DeathDate.SetWindowText(s);
    }
  }
}

LRESULT CFormDeath::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam) {
  LPCTSTR szMessage = (LPCTSTR)wParam;
  if ( stricmp(szMessage, "close")==0 ) {
    m_fEnableRelayEvent = true;
  }
  else if ( stricmp(szMessage, "medlist")==0 ) {
    m_fEnableRelayEvent = true;
    //m_tooltip.HideTooltip();
    //theApp.OnMedics();
    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    pMainFrame->PostMessage(WM_COMMAND,  MAKEWPARAM(ID_MEDICS, 0), LPARAM(pMainFrame->m_wndDlgBar.m_hWnd) );
    //GetDlgItem(IDC_MEDICAL_CERT_BY_PSEUDO)->SetFocus();
  }
  m_tooltip.HideTooltip();

  return TRUE;
}

BOOL CFormDeath::OnCommand(WPARAM wParam, LPARAM lParam) {
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
    case IDC_CITIZENSHIP:   if ( CBN_SETFOCUS==wNotifyCode )    m_cmbCitizenship.UpdateByDefault();
      break;

    case IDC_DP_COUNTRY:    if ( CBN_SETFOCUS==wNotifyCode )    m_cmbDeathCountry.UpdateByDefault();
      break;
    case IDC_DP_REGION:     if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusRegion(m_cmbDeathCountry, m_cmbDeathRegion, m_cmbDeathCity);
      break;
    case IDC_DP_DISTRICT:   if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusDistrict(m_cmbDeathRegion, m_cmbDeathDistrict);
      break;
    case IDC_DP_CITY:       if ( CBN_SETFOCUS==wNotifyCode )    OnSetfocusCity(m_cmbDeathCountry, m_cmbDeathRegion, m_cmbDeathDistrict, m_cmbDeathCity);
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

    case IDC_DEATH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DeathDate, _T("смерті"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;

    case IDC_BIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_BirthDate, _T("народження"), &m_DeathDate, _T("смерті"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;

    case IDC_REASON_PSEUDO:
      if ( CBN_SETFOCUS==wNotifyCode )
        OnSetfocusReasonPseudo();
      else if ( CBN_SELENDOK==wNotifyCode )
        OnSelendokReasonPseudo();
      break;
    case IDC_MEDICAL_CERT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DeathDate, _T("смерті"), &m_MedicalCertDate, _T("медичного свідоцтва"), FALSE) ) {
          return FALSE;
        }
        return bResult;
      }
      if ( CBN_SETFOCUS==wNotifyCode )
          OnSetfocusMedicalCertDate();
      break;

    case IDC_PASSPORT_BY:           if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_PassportSeria, m_PassportNumber, m_cmbPassportBy);
      break;
    case IDC_DECLARANT_PASSPORT_BY: if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_DeclarantPassportSeria, m_DeclarantPassportNumber, m_cmbDeclarantPassportBy);
      break;
    case IDC_PASSPORT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_PassportDate, _T("видачі паспорту"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_DECLARANT_PASSPORT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DeclarantPassportDate, _T("видачі паспорту"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
  }
  m_LastCtrlId = wCtrlId;
  bResult = CEraForm::OnCommand(wParam, lParam);
  return bResult;
}

void CFormDeath::OnUpdateBirthDate() {
/************************************** : by VK at 27.10.2004 21:38:18 **\
  CString sBirthDate = m_BirthDate.GetText();
  CString sDeathDate = m_DeathDate.GetText();
\************************************** : by VK at 27.10.2004 21:38:21 **/
  m_lblAge.SetRedraw(FALSE);
  CString s = GetAge(m_BirthDate.GetDate(), m_DeathDate.GetDate(), true);
  GetDlgItem(IDC_LBL_AGE)->SetWindowText(s);
  m_lblAge.SetRedraw(TRUE);
  m_lblAge.InvalidateRect(NULL);
}

void CFormDeath::OnSetfocusReasonPseudo() {
  CString s;
  GetDlgItem(IDC_REASON)->GetWindowText(s);
  if ( s.IsEmpty() )
    m_cmbReasonPseudo.ShowDropDown();
/************************************** : by VK at 18.04.2006 6:03:09 **\
  else {
    int nextKey = GetKeyState(VK_TAB);
    if( nextKey < 0 )
      GetDlgItem(IDC_MEDICAL_CERT_TYPE)->SetFocus();
  }
\************************************** : by VK at 18.04.2006 6:03:11 **/
}

void CFormDeath::OnSelendokReasonPseudo() {
  int nItem = m_cmbReasonPseudo.GetCurSel();
  if ( CB_ERR != nItem ) {
    CString s = m_cmbReasonPseudo.GetColumnText(nItem, 1);
    if ( !s.IsEmpty() ) {
      m_sReasonSaved = s;
      GetDlgItem(IDC_REASON)->SetWindowText(s);
    }
  }
}

void CFormDeath::OnSetfocusMedicalCertDate() {
  CString s;
  m_MedicalCertDate.GetWindowText(s);
  if ( s.IsEmpty() && COleDateTime::valid==m_DateReg.GetDate().GetStatus() ) {
    COleDateTime odt = m_DateReg.GetDate();    
    s.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear());
    m_MedicalCertDate.SetWindowText(s);
  }
}

void CFormDeath::OnSelendokMedicalCertByPseudo() {
  int nIndex = m_cmbMedicalCertByPseudo.GetCurSel();
  if ( CB_ERR != nIndex ) {
    CString s, sHospital;
    m_cmbMedicalCertByPseudo.GetLBText(nIndex, s);

    if ( theHospitals.Lookup(s, sHospital) ) {
      m_cmbMedicalCertBy.SetWindowText(sHospital);
    }
  }
}

void CFormDeath::OnSelchangeMedicalCertByPseudo() {
	CString s = m_cmbMedicalCertByPseudo.GetCurText();
  if ( !s.IsEmpty() ) {
    CString sHospital;
    if ( theHospitals.Lookup(s, sHospital) ) {
      m_cmbMedicalCertBy.SetWindowText(sHospital);
    }
  }
}

void CFormDeath::OnSetfocusDeclarantName() {
  CString s;
  m_DeclarantName.GetWindowText(s);
  m_fSetfocusDeclarantName = false;
  if ( s.IsEmpty() ) {
    m_Surname.GetWindowText(s);
    m_DeclarantName.SetWindowText(s);
    m_DeclarantName.SendMessage(WM_KEYDOWN, (WPARAM)VK_END, MAKELONG(1, 0) );
    m_fSetfocusDeclarantName = true;
  }
}

void CFormDeath::OnKillfocusDeclarantName() {
	// TODO: Add your control notification handler code here
	if ( m_fSetfocusDeclarantName ) {
    CString s;
    m_DeclarantName.GetWindowText(s);
    if ( !s.IsEmpty() ) {
      s = MakeCanonicalName(s);
      m_DeclarantName.SetWindowText(s);
      m_fSetfocusDeclarantName = false;
    }
  }
}

void CFormDeath::OnSetfocusDeclarantAddress() {
  CString s;
  m_DeclarantAddress.GetWindowText(s);
  if ( s.IsEmpty() ) {
    CString s, sAddress;
    m_RPIndex.GetWindowText(s);
    if ( !s.IsEmpty() ) {
      s += _T(", ");
    }
    sAddress = s;
    s = MakeAddress(&m_cmbRPCountry, &m_cmbRPRegion, &m_cmbRPCity, &m_cmbRPDistrict, &m_cmbRPStreet, &m_RPHouse, &m_RPFlat);
    sAddress += s;
    m_DeclarantAddress.SetWindowText(sAddress);
  }
}

void CFormDeath::OnSetfocusCertificateSeria() {
	CString s;
  m_CertificateSeria.GetWindowText(s);
  if ( s.IsEmpty() ) {
    m_CertificateSeria.SetWindowText( theIniCache.GetDEATH_Seria() );
    m_CertificateSeria.SetSel(0, -1);
  }
}

void CFormDeath::OnSetfocusCertificateNumber() {
	CString s;
	m_CertificateNumber.GetWindowText(s);
  bool fSeriaIsEmpty = m_CertificateSeria.IsEmpty();
  if ( s.IsEmpty() && !fSeriaIsEmpty ) {
    s = theIniCache.GetDEATH_CNum();
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

void CFormDeath::OnChangeCertificateNumber() {
  theIniCache.SetDEATH_CNum( &m_CertificateNumber );
}

/*
  Dim s As String, lFlags As Long
  With Me
    lFlags = .Флаги
    s = DeaN(.RecordsetClone, Nz(.Номер), _
             Nz(.ДатаРег, Now()), Nz(.Примечания, ""), lFlags, _
             IIf(Nz(.Гражданство, 0) = 0, True, False), _
             IsEmptyText(.П_Серия), IsEmptyText(.СерияСв), _
             String(512, 0), 512)
    .Примечания = IIf(IsEmptyText(s), Null, s)
  End With

*/
void CFormDeath::OnSetfocusNotice() {
  CString s, sNewNumber, sMemo;
  m_Notice.GetWindowText(s);
  if ( !s.IsEmpty() )
    return;

  try {
    COleVariant bm = m_pRSet->GetBookmark();
    m_pRSet->MoveLast();
    while( !m_pRSet->IsBOF() ) {
      s = m_pRSet->m_NOTICE;
      if ( !s.IsEmpty() ) {
        sNewNumber = GetNumFromStr(s, _T("№"));
        if ( !sNewNumber.IsEmpty() )
          break;
      }
      m_pRSet->MovePrev();
    }
    m_pRSet->SetBookmark(bm);
  }

  catch(CDaoException* e) {
    e->Delete();
  }

  if ( sNewNumber.IsEmpty() )
    sNewNumber = _T("1");

  if ( m_CertificateSeria.IsEmpty() || m_CertificateNumber.IsEmpty() ) {
    s = theIniCache.GetNoCert();
    //lFlags |= DEA_FLAG_CERTIFICATE;
  }
  else {
    COleDateTime odt(m_DateReg.GetDate() );
    CString szDate;
    szDate.Format(_T("%02d.%02d.%04d р."), odt.GetDay(), odt.GetMonth(), odt.GetYear());
    /************************************** : by VK at 17.08.2008 5:20:02 **\
    s.Format(IDS_DEA_DOVIDKA, sNewNumber, odt.GetDay(), odt.GetMonth(), odt.GetYear());
    IDS_DEA_DOVIDKA         "Видана довідка № %s від %02d.%02d.%04d р. для отримання допомоги на поховання."
    \************************************** : by VK at 17.08.2008 5:20:05 **/
    s = theIniCache.GetDEATH_DefNotice();
    ReplaceIgnoreCase(s, _T("!№!"), sNewNumber);
    ReplaceIgnoreCase(s, _T("!дата!"), szDate);
    ReplaceIgnoreCase(s, _T(".."), _T("."));
  }
  sMemo += s;

  if ( m_cmbCitizenship.IsEmpty() ) {
    s.LoadString(IDS_CITIZENSHIP);
    sMemo = Trim(sMemo);  sMemo += s;
    // lFlags |= DEA_FLAG_CITIZENSHIP;
  }

  if ( m_PassportSeria.IsEmpty() ||  m_PassportNumber.IsEmpty() ) {
    s.LoadString(IDS_NODEADPASSPORT);
    sMemo += s; sMemo = Trim(sMemo);
    // lFlags |= DEA_FLAG_PASSPORT;
  }
/************************************** : by VK at 01.11.2003 10:47:13 **\
  else
    lFlags &= ~DEA_FLAG_PASSPORT;
\************************************** : by VK at 01.11.2003 10:47:16 **/

/************************************** : by VK at 01.11.2003 10:54:57 **\
  else
    lFlags &= ~DEA_FLAG_CITIZENSHIP;
\************************************** : by VK at 01.11.2003 10:54:59 **/

  if ( m_DeclarantPassportNumber.IsEmpty() ) {
    s.LoadString(IDS_DECPASSPORT);
    sMemo += s; sMemo = Trim(sMemo);
  }
  sMemo = Trim(sMemo);
  m_Notice.SetWindowText(sMemo);
}

void CFormDeath::OnSetfocusReason() {
//  OnSelendokReasonPseudo();
}

void CFormDeath::OnKillfocusReason() {
  m_tooltip.HideTooltip();
  CWnd* pFocusWnd = GetFocus();
  if ( NULL==pFocusWnd )
    return;
  if ( pFocusWnd->GetParent() != this )
    return;

  CString s;
  GetDlgItem(IDC_REASON)->GetWindowText(s);
  if ( !s.IsEmpty() && s != m_sReasonSaved ) {
    m_tooltip.HideTooltip();
    CAddRsnDlg dlg(this);
    dlg.m_sReason = s;
    if ( dlg.DoModal()==IDYES ) {
      LoadCauses();
    }
//    else
      m_sReasonSaved = s;
  }
  pFocusWnd->SetFocus();
}


void CFormDeath::OnDestroy() {
//  CEraForm::OnMove(0);
//  CEraForm::OnDestroy();
  m_CausesCache.RemoveAll();
  if ( m_pRSet ) {
    m_pRSet->Close();
    delete m_pRSet;
    m_pRSet = NULL;
  }
}

void CFormDeath::OnContextMenu(CWnd* pWnd, CPoint point) {
	// TODO: Add your message handler code here
  m_tooltip.HideTooltip();
  UINT nPos = CONTEXT_DEATH;
  CString s, sMemo;
  m_Notice.GetWindowText(sMemo);
  s = ContextMenu(m_Notice.m_hWnd, nPos, m_fSex.IsOn(), m_DateReg.GetDate(), sMemo, false, &m_BirthDate.GetDate(), &m_DeathDate.GetDate());
  if ( s != sMemo )
    m_Notice.SetWindowText(s);
}
