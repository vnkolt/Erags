// FormBirth.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "..\Common\MDB.h"

#include "ABCDlg.h"
#include "FormBirth.h"
#include "EragsDoc.h"
#include "Caches.h"
#include "CheckDateDlg.h"
#include "DataManager.h"
#include "Defaults.h"
#include "Dlg43.h"
#include "BirthDlgs.h"
#include "HelpMan.h"
#include "MainFrm.h"
#include "Menu.h"
#include "MonthList.h"

#include "BirthSurnamesDlg.h"
#include "DownloadChecker.h"
#include "PassportsDlg.h"
#include "RegDlg.h"
#include "RList.h"
#include "RNames.h"
#include "RTFCnv.h"
#include "ExtBirthDlg.h"
#include "ExtNotice.h"

#include "BlanksDlg.h"
#include "SetDefDlg.h"
#include "SVDlg.h"

#include "xMachine.h"

#include "..\Common\FHelpers.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GetBirthDoc(CRSBirthes* pSet);
CString MedSv(CRSBirthes* pSet);
CString PassportName(BYTE bType, BOOL bShortName);
BOOL RegDlg(CPPToolTip* pTooltip);

extern COLORREF  g_clrLeft, g_clrRight;
extern BOOL      g_fAdoption;
extern CString   g_sChoosenDistrict;

//
// CDisableCommands
CDisableCommands::CDisableCommands(void* pUnusedPointer) {
  m_pUnusedPointer = pUnusedPointer;
}

void CDisableCommands::Do() {
  theApp.m_bGeoLoaded = FALSE;
  theDataManager.Init();
}

int FilterFuncForBirtList(CRSBirthes* pSet) {
  if ( COleDateTime::valid != pSet->m_DATEREG.GetStatus() )
    return 0;

  if ( FALSE==g_sChoosenDistrict.IsEmpty() && pSet->m_BP_DISTRICT!=g_sChoosenDistrict)
    return 0;

  if ( g_odtFrom <= pSet->m_DATEREG && pSet->m_DATEREG <= g_odtTill ) {
    return 1;
  }
/************************************** : by VK at 27.01.2008 11:11:53 **\
  if ( g_fPeriod && g_odtFrom <= pSet->m_DATEREG && pSet->m_DATEREG <= g_odtTill ) {
    return 1;
  }
  else if ( pSet->m_DATEREG.GetMonth() == g_iMonth )
    return 1;
\************************************** : by VK at 27.01.2008 11:11:56 **/

  return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CFormBirth

IMPLEMENT_DYNCREATE(CFormBirth, CEraForm)

CFormBirth::CFormBirth()
           :CEraForm( CFormBirth::IDD ), m_pRSet((CRSBirthes*&)m_pSet) {
  //{{AFX_DATA_INIT(CFormBirth)
  //}}AFX_DATA_INIT

  m_SourceType.AddState( BIRTH_TYPE_ACT,          _T("Актовий запис про шлюб") );// 0
  m_SourceType.AddState( BIRTH_TYPE_MOTHER,       _T("Заява матері №") );        // 1
  m_SourceType.AddState( BIRTH_TYPE_PARENTS,      _T("Заява батьків №") );       // 2
  m_SourceType.AddState( BIRTH_TYPE_APPL,         _T("Заява") );                 // 3
  m_SourceType.AddState( BIRTH_TYPE_APPLNUM,      _T("Заява №") );               // 4
  m_SourceType.AddState( BIRTH_TYPE_AFFILIATION1, _T("Заява батька про ВБ №") ); // 5
  m_SourceType.AddState( BIRTH_TYPE_AFFILIATION2, _T("Спільна заява про ВБ №") );// 6

  m_DeclarantType.AddColorState( 0, RGB(0x00, 0x00, 0xFF), _T("Заявник") );
  m_DeclarantType.AddColorState( 1, RGB(0xFF, 0x00, 0x00), _T("Заявниця") );
  m_DeclarantType.AddColorState( 2, RGB(0xFF, 0x00, 0xFF), _T("Заявники") );

  m_szFormName = _T("FORM_BIRTH");

#ifndef FREE_LICENCE
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
#endif // FREE_LICENCE
}

CFormBirth::~CFormBirth() {
  if ( m_pSet ) {
    if( m_pSet->IsOpen() )
      m_pSet->Close();
    delete m_pSet;
    m_pSet = NULL;
  }
}

void CFormBirth::SetFocusToFirstControl() {
  if ( m_fSex.GetSafeHwnd() )
    m_fSex.SetFocus();
}

void CFormBirth::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    //case IDC_BC_LABEL:
    //case IDC_BD_LABEL:
    //case IDC_BR_LABEL:
    //case IDC_BV_LABEL:
    case IDC_LBL_DECLARANT_PSERIA:
    case IDC_LBL_DECLARANT_PNUMBER:
    case IDC_LBL_DECLARANT_PDATE:
    case IDC_LBL_DECLARANT_PBY:
    case IDC_BIRTH_PLACE:
    case IDC_ALIVE_FLAG:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CDaoRecordViewBG::SetScaleFlags(pWnd, wFlags);
  }
}
void CFormBirth::OnKillfocusSurname() {
  static BOOL inbody = false;
  if ( inbody )
    return;
  CWnd* pFocusWnd = GetFocus();
  if ( NULL==pFocusWnd )
    return;
  if ( pFocusWnd->GetParent() != this )
    return;

  inbody = true;
  CString szSurname = Trim(m_Surname.GetText());
  if ( !szSurname.IsEmpty() ) { 
    CString szOldSurname = GetTokSpace(szSurname, 0);
    CString szNewSurname = GetTokSpace(szSurname, 1);
    if ( !szNewSurname.IsEmpty() ) { // Типа того: "Іванов Петров"
      m_tooltip.HideTooltip();
      CBirthSurnamesDlg dlg(this);
      dlg.m_szSurname = szSurname;
      if ( IDYES==dlg.DoModal() ) {
        CString szMemo = m_ExtNotices.GetText();
        if ( dlg.m_fTwoSurnames ) {
          szMemo = m_ExtNotices.GetText();
          m_Surname.SetWindowText(dlg.m_szOldSurname);
          m_pRSet->SetNewSurname(dlg.m_szNewSurname, szMemo);
        }
        else {
          m_Surname.SetWindowText(dlg.m_szSurname);
          m_pRSet->SetNewSurname(_T(""), szMemo);
        }
        m_ExtNotices.SetWindowText(szMemo);
      }
    }
  }
  pFocusWnd->SetFocus();
  inbody = false;
}
void CFormBirth::BeforeLeavePatronymic() {
  if ( FALSE==IsAlive() ) {
    return;
  }
  if ( IsFocusChild(this) ) {
    CString sName = Trim(m_Name.GetCurText());
    CString szPattronymic = Trim(m_Patronymic.GetCurText());
    if ( m_Name.IsEmpty() && szPattronymic.IsEmpty() ) {
      CWnd* pFocus = GetFocus();
      LPCTSTR szMsg = _T("Ім'я та по батькові залишени незаповненими. Чи вважати, що це мертвонароджена дитина?");
      int nDlgRes = CallSetDefDlg(this, _T("Settings"), _T("ShowAliveRequest"), _T("AliveResponse"), szMsg);
      if ( IDYES==nDlgRes ) {
        OnAliveFlag();
      }
      if ( pFocus )
        pFocus->SetFocus();
    }
  }
}
void CFormBirth::DoDataExchange(CDataExchange* pDX) {
  if ( FALSE==pDX->m_bSaveAndValidate ) {
    m_SURNAME_before_save        = m_pRSet->m_SURNAME;
    m_NAME_before_save           = m_pRSet->m_NAME;
    m_PATRONYMIC_before_save     = m_pRSet->m_PATRONYMIC;
    m_NUMBER_before_save         = m_pRSet->m_NUMBER;
    m_DATEREG_before_save        = m_pRSet->m_DATEREG;
    m_NEW_SURNAME_before_save    = m_pRSet->GetNewSurname();
    m_NEW_NAME_before_save       = m_pRSet->GetNewName();
    m_NEW_PATRONYMIC_before_save = m_pRSet->GetNewPatronymic();
  }  
	CEraForm::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFormBirth)
  DDX_Control(pDX, IDC_BIRTH_PLACE, m_BirthPlace);
  DDX_Control(pDX, IDC_SEX, m_fSex);
  DDX_Control(pDX, IDC_NUMBER, m_Number);
  DDX_Control(pDX, IDC_SURNAME, m_Surname);
  DDX_Control(pDX, IDC_NAME, m_Name);
  DDX_Control(pDX, IDC_PATRONYMIC, m_Patronymic);
  DDX_Control(pDX, IDC_BIRTH_COUNTRY, m_cmbBirthCountry);
  DDX_Control(pDX, IDC_BIRTH_REGION, m_cmbBirthRegion);
  DDX_Control(pDX, IDC_BIRTH_DISTRICT, m_cmbBirthDistrict);
  DDX_Control(pDX, IDC_BIRTH_CITY, m_cmbBirthCity);
  DDX_Control(pDX, IDC_NKIDS, m_nKids);
  DDX_Control(pDX, IDC_BYCOUNT, m_nByCount);
  DDX_Control(pDX, IDC_ALIVE_FLAG, m_Alive_Flag);
  DDX_Control(pDX, IDC_ALIVE_FLAG_EDIT, m_AliveFlag);
  DDX_Control(pDX, IDC_MEDICAL_CERTIFICATE_NUMBER, m_MedCertNumber);
//  DDX_Control(pDX, IDC_MEDICAL_CERTIFICATE_DATE, m_MedCertDate);
  DDX_Control(pDX, IDC_MEDICAL_CERTIFICATE_PSEUDUNYM, m_MedCertPseudo);
  DDX_Control(pDX, IDC_MEDICAL_CERTIFICATE_BY, m_MedCertBy);
  DDX_Control(pDX, IDC_SOURCE_TYPE, m_SourceType);
  DDX_Control(pDX, IDC_SOURCE_NDOC, m_SourceNDoc);
//  DDX_Control(pDX, IDC_SOURCE_DATE, m_SourceDate);
  DDX_Control(pDX, IDC_SOURCE_BY, m_SourceBy);
  DDX_Control(pDX, IDC_FATHER_CITIZENSHIP, m_FatherCitizenship);
  DDX_Control(pDX, IDC_FATHER_SURNAME, m_FatherSurname);
  DDX_Control(pDX, IDC_FATHER_NAME, m_FatherName);
  DDX_Control(pDX, IDC_FATHER_PATRONYMIC, m_FatherPatronymic);
//  DDX_Control(pDX, IDC_FATHER_BIRTH_DATE, m_FatherDate);
  DDX_Control(pDX, IDC_FATHER_COUNTRY, m_FatherCountry);
  DDX_Control(pDX, IDC_FATHER_REGION, m_FatherRegion);
  DDX_Control(pDX, IDC_FATHER_CITY, m_FatherCity);
  DDX_Control(pDX, IDC_FATHER_DISTRICT, m_FatherDistrict);
  DDX_Control(pDX, IDC_FATHER_STREET, m_FatherStreet);
  DDX_Control(pDX, IDC_FATHER_HOUSE, m_FatherHouse);
  DDX_Control(pDX, IDC_FATHER_FLAT, m_FatherFlat);
  DDX_Control(pDX, IDC_MOTHER_CITIZENSHIP, m_MotherCitizenship);
  DDX_Control(pDX, IDC_MOTHER_SURNAME, m_MotherSurname);
  DDX_Control(pDX, IDC_MOTHER_NAME, m_MotherName);
  DDX_Control(pDX, IDC_MOTHER_PATRONYMIC, m_MotherPatronymic);
//  DDX_Control(pDX, IDC_MOTHER_BIRTH_DATE, m_MotherDate);
  DDX_Control(pDX, IDC_MOTHER_COUNTRY, m_MotherCountry);
  DDX_Control(pDX, IDC_MOTHER_REGION, m_MotherRegion);
  DDX_Control(pDX, IDC_MOTHER_CITY, m_MotherCity);
  DDX_Control(pDX, IDC_MOTHER_DISTRICT, m_MotherDistrict);
  DDX_Control(pDX, IDC_MOTHER_STREET, m_MotherStreet);
  DDX_Control(pDX, IDC_MOTHER_HOUSE, m_MotherHouse);
  DDX_Control(pDX, IDC_MOTHER_FLAT, m_MotherFlat);
  DDX_Control(pDX, IDC_DECLARANT_TYPE, m_DeclarantType);
	DDX_Control(pDX, IDC_DECLARANT_20, m_Decl20);
  DDX_Control(pDX, IDC_DECLARANT_NAME, m_DeclarantName);
  DDX_Control(pDX, IDC_DECLARANT_ADDRESS, m_DeclarantAddress);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_TYPE, m_DeclarantPassportType);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_SERIA, m_DeclarantPassportSeria);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_NUMBER, m_DeclarantPassportNumber);
//  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_DATE, m_DeclarantPassportDate);
  DDX_Control(pDX, IDC_DECLARANT_PASSPORT_BY, m_DeclarantPassportBy);
  DDX_Control(pDX, IDC_DECLARANT_DLG, m_btnDeclarantPassports);
  DDX_Control(pDX, IDC_CERTIFICATE_SERIA, m_CertificateSeria);
  DDX_Control(pDX, IDC_CERTIFICATE_NUMBER, m_CertificateNumber);
  DDX_Control(pDX, IDC_NOTICE, m_Notice);
  DDX_Control(pDX, IDC_EXTNOTICES, m_ExtNotices);
  DDX_Control(pDX, IDC_RENEW, m_Flags);
	//}}AFX_DATA_MAP
  DDX_FieldCheck(pDX, IDC_SEX, m_pRSet->m_SEX, m_pRSet);
  DDX_OleDate(pDX, IDC_DATEREG,     m_DateReg, m_pRSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, m_pRSet->m_NUMBER, m_pRSet);
  DDX_FieldText(pDX, IDC_SURNAME, m_pRSet->m_SURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_NAME, m_pRSet->m_NAME, m_pRSet);
  DDX_FieldText(pDX, IDC_PATRONYMIC, m_pRSet->m_PATRONYMIC, m_pRSet);
  DDX_FieldText(pDX, IDC_BIRTH_COUNTRY, m_pRSet->m_BP_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_BIRTH_REGION, m_pRSet->m_BP_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_BIRTH_DISTRICT, m_pRSet->m_BP_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_BIRTH_CITY, m_pRSet->m_BP_CITY, m_pRSet);
  DDX_OleDate(pDX, IDC_DATEOFBIRTH, m_DateBirth, m_pRSet->m_BIRTH_DATE);
  DDX_FieldText(pDX, IDC_NKIDS, m_pRSet->m_NKIDS, m_pRSet);
  DDX_FieldText(pDX, IDC_BYCOUNT, m_pRSet->m_BYCOUNT, m_pRSet);
  DDX_FieldText(pDX, IDC_ALIVE_FLAG_EDIT, m_pRSet->m_ALIVE_FLAG, m_pRSet);
  DDX_FieldText(pDX, IDC_MEDICAL_CERTIFICATE_NUMBER, m_pRSet->m_MEDICAL_CERTIFICATE_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_MEDICAL_CERTIFICATE_DATE, m_MedCertDate, m_pRSet->m_MEDICAL_CERTIFICATE_DATE);
  //DDX_FieldTextEraDate(pDX, IDC_MEDICAL_CERTIFICATE_DATE, m_pRSet->m_MEDICAL_CERTIFICATE_DATE, m_pRSet);
  DDX_FieldText(pDX, IDC_MEDICAL_CERTIFICATE_BY, m_pRSet->m_MEDICAL_CERTIFICATE_BY, m_pRSet);
  DDX_OleDate(pDX, IDC_FATHER_BIRTH_DATE, m_FatherDate, m_pRSet->m_FATHER_BIRTH_DATE);
  DDX_OleDate(pDX, IDC_MOTHER_BIRTH_DATE, m_MotherDate, m_pRSet->m_MOTHER_BIRTH_DATE);
  DDX_MSButton(pDX, IDC_SOURCE_TYPE, m_SourceType, m_pRSet->m_SOURCE_TYPE);
  DDX_OleDate(pDX, IDC_SOURCE_DATE, m_SourceDate, m_pRSet->m_SOURCE_DATE);
  //DDX_FieldText(pDX, IDC_DATEREG, m_pRSet->m_DATEREG, m_pRSet);
  //DDX_FieldText(pDX, IDC_DATEOFBIRTH, m_pRSet->m_BIRTH_DATE, m_pRSet);
  DDX_FieldText(pDX, IDC_SOURCE_NDOC, m_pRSet->m_SOURCE_NDOC, m_pRSet);
  //DDX_FieldTextEraDate(pDX, IDC_SOURCE_DATE, m_pRSet->m_SOURCE_DATE, m_pRSet);
  DDX_FieldText(pDX, IDC_SOURCE_BY, m_pRSet->m_SOURCE_BY, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_CITIZENSHIP, m_pRSet->m_FATHER_CITIZENSHIP, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_SURNAME, m_pRSet->m_FATHER_SURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_NAME, m_pRSet->m_FATHER_NAME, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_PATRONYMIC, m_pRSet->m_FATHER_PATRONYMIC, m_pRSet);
  //DDX_FieldTextEraDate(pDX, IDC_FATHER_BIRTH_DATE, m_pRSet->m_FATHER_BIRTH_DATE, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_COUNTRY, m_pRSet->m_FATHER_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_REGION, m_pRSet->m_FATHER_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_CITY, m_pRSet->m_FATHER_CITY, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_DISTRICT, m_pRSet->m_FATHER_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_STREET, m_pRSet->m_FATHER_STREET, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_HOUSE, m_pRSet->m_FATHER_HOUSE, m_pRSet);
  DDX_FieldText(pDX, IDC_FATHER_FLAT, m_pRSet->m_FATHER_FLAT, m_pRSet);

  DDX_FieldText(pDX, IDC_MOTHER_CITIZENSHIP, m_pRSet->m_MOTHER_CITIZENSHIP, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_SURNAME, m_pRSet->m_MOTHER_SURNAME, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_NAME, m_pRSet->m_MOTHER_NAME, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_PATRONYMIC, m_pRSet->m_MOTHER_PATRONYMIC, m_pRSet);
  //DDX_FieldTextEraDate(pDX, IDC_MOTHER_BIRTH_DATE, m_pRSet->m_MOTHER_BIRTH_DATE, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_COUNTRY, m_pRSet->m_MOTHER_COUNTRY, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_REGION, m_pRSet->m_MOTHER_REGION, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_CITY, m_pRSet->m_MOTHER_CITY, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_DISTRICT, m_pRSet->m_MOTHER_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_STREET, m_pRSet->m_MOTHER_STREET, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_HOUSE, m_pRSet->m_MOTHER_HOUSE, m_pRSet);
  DDX_FieldText(pDX, IDC_MOTHER_FLAT, m_pRSet->m_MOTHER_FLAT, m_pRSet);

  DDX_MSButton(pDX, IDC_DECLARANT_TYPE, m_DeclarantType, m_pRSet->m_DECLARANT_TYPE);
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
  DDX_FieldText(pDX, IDC_EXTNOTICES, m_pRSet->m_EXTNOTES, m_pRSet);
  DDX_FieldText(pDX, IDC_RENEW, m_pRSet->m_RENEW, m_pRSet);

/************************************** : by VK at 04.12.2004 4:48:49 **\

  if ( pDX->m_bSaveAndValidate ) {
    if ( m_NUMBER_before_save         != m_pRSet->m_NUMBER           ||
         m_DATEREG_before_save        != m_pRSet->m_DATEREG          ||
         m_SURNAME_before_save        != m_pRSet->m_SURNAME          ||
         m_NAME_before_save           != m_pRSet->m_NAME             ||
         m_PATRONYMIC_before_save     != m_pRSet->m_PATRONYMIC       ||
         m_NEW_SURNAME_before_save    != m_pRSet->GetNewSurname()    ||
         m_NEW_NAME_before_save       != m_pRSet->GetNewName()       ||
         m_NEW_PATRONYMIC_before_save != m_pRSet->GetNewPatronymic() )
      UpdateNavigateBars();
  }
\************************************** : by VK at 04.12.2004 4:48:52 **/
  m_ID = m_pRSet->m_ID;
}


BEGIN_MESSAGE_MAP(CFormBirth, CEraForm)
  //{{AFX_MSG_MAP(CFormBirth)
  ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
  ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
  ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
  ON_EN_SETFOCUS(IDC_MEDICAL_CERTIFICATE_DATE, OnSetfocusMedicalCertificateDate)
  ON_EN_SETFOCUS(IDC_MEDICAL_CERTIFICATE_BY, OnSetfocusMedicalCertificateBy)
  ON_EN_SETFOCUS(IDC_SOURCE_DATE, OnSetfocusSourceDate)
  ON_EN_SETFOCUS(IDC_FATHER_SURNAME, OnSetfocusFatherSurname)
  ON_CBN_SETFOCUS(IDC_FATHER_NAME, OnSetfocusFatherName)
  ON_EN_SETFOCUS(IDC_DATEOFBIRTH, OnSetfocusDateofBirth)
  ON_EN_SETFOCUS(IDC_MOTHER_SURNAME, OnSetfocusMotherSurname)
  ON_BN_SETFOCUS(IDC_DECLARANT_TYPE, OnSetfocusDeclaranType)
  ON_EN_SETFOCUS(IDC_CERTIFICATE_SERIA, OnSetfocusCertificateSeria)
  ON_EN_SETFOCUS(IDC_CERTIFICATE_NUMBER, OnSetfocusCertificateNumber)
  ON_EN_CHANGE(IDC_CERTIFICATE_NUMBER, OnChangeCertificateNumber)
  ON_EN_SETFOCUS(IDC_NOTICE, OnSetfocusNotice)
  ON_EN_KILLFOCUS(IDC_SURNAME, OnKillfocusSurname)
  ON_BN_CLICKED(IDC_DECLARANT_TYPE, OnDeclarantType)
  ON_UPDATE_COMMAND_UI(ID_EXTNOTES, OnUpdateExtnotes)
  ON_COMMAND(ID_EXTNOTES, OnExtnotes)
  ON_EN_SETFOCUS(IDC_MOTHER_HOUSE, OnSetfocusMotherHouse)
  ON_EN_SETFOCUS(IDC_MOTHER_FLAT, OnSetfocusMotherFlat)
	ON_BN_CLICKED(IDC_DECLARANT_20, OnDeclarant20)
  ON_BN_CLICKED(IDC_DECLARANT_DLG, OnDeclarantDlg)
  ON_WM_CONTEXTMENU()
	ON_CBN_SELENDOK(IDC_MEDICAL_CERTIFICATE_PSEUDUNYM, OnSelendokMedicalCertificatePseudunym)
  ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_WM_DRAWITEM()
  ON_WM_SIZE()
  //ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormBirth diagnostics

#ifdef _DEBUG
void CFormBirth::AssertValid() const {
  CEraForm::AssertValid();
}

void CFormBirth::Dump(CDumpContext& dc) const {
  CEraForm::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormBirth message handlers
CDaoRecordset* CFormBirth::OnGetRecordset() {
  if (m_pSet != NULL)
    return m_pSet;

  m_pSet = new CRSBirthes(&theDataManager.m_dbYear);
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

CRSBirthes* CFormBirth::GetRecordset() {
  CRSBirthes* pSet = (CRSBirthes*) OnGetRecordset();
  ASSERT(pSet != NULL && pSet->IsKindOf(RUNTIME_CLASS(CRSBirthes)));
  return pSet;
}

#ifndef FREE_LICENCE
BOOL CFormBirth::IsRDFFieldsDirty() {
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  if ( m_pRSet ) {
    SetChangedBy(m_pRSet, m_pRSet->m_EXTNOTES);
    //  FATHER_REGION, FATHER_CITY, FATHER_DISTRICT,
    if ( m_pRSet->IsFieldDirty(&m_pRSet->m_FATHER_REGION) ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_FATHER_CITY)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_FATHER_DISTRICT) )
      m_GeoFieldsDirtyFlags |= FATHER_GEO_FIELDS_DIRTY;

    //  MOTHER_REGION, MOTHER_CITY, MOTHER_DISTRICT
    if (  m_pRSet->IsFieldDirty(&m_pRSet->m_MOTHER_REGION)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_MOTHER_CITY)     ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_MOTHER_DISTRICT) )
      m_GeoFieldsDirtyFlags |= MOTHER_GEO_FIELDS_DIRTY;
    return (m_GeoFieldsDirtyFlags != NO_GEO_FIELDS_DIRTY);
  }
  return false;
}
void CFormBirth::SetRDFFields() {
  if ( IsEmptyText(m_pRSet->m_SURNAME) || IsEmptyText(m_pRSet->m_NAME) )
    return;
  if ( m_GeoFieldsDirtyFlags & FATHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_FATHER_REGION, m_pRSet->m_FATHER_DISTRICT, m_pRSet->m_FATHER_CITY, false);
  if ( m_GeoFieldsDirtyFlags & MOTHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_MOTHER_REGION, m_pRSet->m_MOTHER_DISTRICT, m_pRSet->m_MOTHER_CITY, false);
  if ( m_GeoFieldsDirtyFlags ) {
    SaveGeoValidation();
  }
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  SaveDateValidation(&m_pRSet->m_DATEREG, &m_pRSet->m_BIRTH_DATE, &m_pRSet->m_MEDICAL_CERTIFICATE_DATE);

}
#endif // FREE_LICENCE
void CFormBirth::OnSexDependences() {
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
    theWPatronymics.FillCombo( m_Patronymic, m_pRSet->m_NAME, FALSE==m_Patronymic.IsFemale() );
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

void CFormBirth::OnBirthPlaceDependences() {
  CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
  if ( NULL==pDoc )
    return;
  int id[] = {/*IDC_BC_LABEL, */IDC_BIRTH_COUNTRY,
              /*IDC_BR_LABEL, */IDC_BIRTH_REGION,
              /*IDC_BD_LABEL, */IDC_BIRTH_DISTRICT,
              /*IDC_BV_LABEL, */IDC_BIRTH_CITY };
  for( int i(0); i < sizeof(id)/sizeof(int); i++ ) {
    CWnd* pWnd = GetDlgItem(id[i]);
    pWnd->EnableWindow(m_BirthPlace.m_bOn);
    pWnd = pWnd->GetWindow(GW_CHILD);
    if ( pWnd )
      pWnd->EnableWindow(m_BirthPlace.m_bOn);
  }
}
void CFormBirth::OnSourceTypeDependences() {
    m_SourceType.InvalidateRect(NULL);
    int swSourceNDoc(SW_SHOW),
        swSourceDate(SW_SHOW),
        swSourceBy(SW_SHOW);
    switch( m_SourceType.GetIndex() ) {
      case BIRTH_TYPE_ACT       : // show all
        break;
      case BIRTH_TYPE_MOTHER    :
      case BIRTH_TYPE_PARENTS   :
      case BIRTH_TYPE_APPLNUM   :
        swSourceBy = SW_HIDE;
        break;
      case BIRTH_TYPE_AFFILIATION1:
      case BIRTH_TYPE_AFFILIATION2:
        swSourceBy = SW_HIDE;
        break;
      case BIRTH_TYPE_APPL      :
      default                   :
        swSourceNDoc = swSourceDate = swSourceBy = SW_HIDE;
        break;
    }
    m_SourceNDoc.ShowWindow(swSourceNDoc);
    GetDlgItem(IDC_SOURCE_OF_LABEL)->ShowWindow(swSourceDate);
    m_SourceDate.ShowWindow(swSourceDate);
    GetDlgItem(IDC_SOURCE_BY_LABEL)->ShowWindow(swSourceBy);
    m_SourceBy.ShowWindow(swSourceBy);
}

void CFormBirth::SetBPDefaults() {
  m_cmbBirthCountry.UpdateByDefault();
  m_cmbBirthRegion.UpdateByDefault();
  m_cmbBirthDistrict.UpdateByDefault();
  m_cmbBirthCity.UpdateByDefault();
}

void CFormBirth::OnBlank(const CString& szTemplate, const CString& szOut) {
  if ( RTF_BirthBlank(szTemplate, szOut, m_pRSet) ) {
    OnRTFShell(szOut);
  }
}
void CFormBirth::OnPrint(UINT nPrintID) {
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

  if ( FALSE==CEraForm::OnMove(0) )  // Save data
    return;

#ifndef FREE_LICENCE
    theRegTimer.Next();
#endif

  g_fAdoption = FALSE;
  CString sTemplate, sOut;

  int nPage1(0), nPage2(0);

  g_nDocType = DOCTYPE_OTHER;

  switch ( nPrintID ) {
    case ID_PRINT_BIRTH_ACT:
      g_nDocType = DOCTYPE_ACT;
      sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("Act") );
      sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("Act"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_BIRTH_CERTIFICATE: {
        g_nDocType = DOCTYPE_CERT;
        CSVDlg dlg(this, IDD_SVID);
        dlg.m_szFormSect    = _T("BIRTH_FORM");

        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("Certificate") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("Certificate"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_ADOPTION_CERTIFICATE: {
        g_nDocType = DOCTYPE_CERT;
        g_fAdoption = TRUE;
        CSVDlg dlg(this, IDD_SVIDADOPTION);
        dlg.m_pRSBirthes = m_pRSet;
        dlg.m_szFormSect = _T("BIRTH_FORM");
        dlg.m_sMSurname     = m_FatherSurname.GetText();
        dlg.m_sMName        = m_FatherName.GetCurText();
        dlg.m_sMPatronymic  = m_FatherPatronymic.GetCurText();
        dlg.m_sWSurname     = m_MotherSurname.GetText();
        dlg.m_sWName        = m_MotherName.GetCurText();
        dlg.m_sWPatronymic  = m_MotherPatronymic.GetCurText();
        dlg.m_ExtMemo       = m_ExtNotices.GetText();
        if ( IDYES==dlg.DoModal() ) {
          m_ExtNotices.SetWindowText( dlg.m_ExtMemo );
          CEraForm::OnMove(0);
          sTemplate.Format(_T("%s\\Adoption_Certificate."), theApp.m_sTemplatePath );
          sOut.Format(_T("%s\\Adoption_Certificate_%04d."),theApp.m_sOutPath, m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_8: {
        if ( BirthDlg08(8, this, m_pRSet->m_NUMBER, m_pRSet->m_SEX, m_Notice.GetText(), m_Surname.GetText(), m_Name.GetCurText(), m_Patronymic.GetCurText() ) ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("08") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("08"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_9:
      sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("09") );
      sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("09"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_BIRTH_AFFILIATION_09: {
        if ( BirthDlg09(this, m_pRSet->m_SEX,
                        m_Surname.GetText(),       m_Name.GetCurText(),       m_Patronymic.GetCurText(),
                        m_FatherSurname.GetText(), m_FatherName.GetCurText(), m_FatherPatronymic.GetCurText()
                       )
           ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("09.2.18") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("09.2.18"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_AFFILIATION_11: {
        if ( BirthDlg11(this, m_pRSet->m_SEX,
                        m_Surname.GetText(),       m_Name.GetCurText(),       m_Patronymic.GetCurText(),
                        m_FatherSurname.GetText(), m_FatherName.GetCurText(), m_FatherPatronymic.GetCurText(),
                        m_MotherSurname.GetText(), m_MotherName.GetCurText(), m_MotherPatronymic.GetCurText()
                       )
           ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("11.2.21") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("11.2.21"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_41: {
        CDlg43 dlg(41, this);
        dlg.m_sTo = m_DeclarantName.GetText();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("41") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("41"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_42: {
        CDlg43 dlg(42, this);
        g_sFullBabyNameRV = MakeFIO(&m_Surname, &m_Name, &m_Patronymic);
        dlg.m_sTo = m_DeclarantName.GetText();
        dlg.m_fSex = m_fSex.IsOn();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("42") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("42"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_FORTAX: {
        sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("ToTax") );
        sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("ToTax"), m_pRSet->m_NUMBER);
        MakeInOutExt(sTemplate, sOut);
        CString s;
        s.LoadString(ID_PRINT_BIRTH_FORTAX);
        CMonthList dlg(nPrintID, FALSE, m_pRSet->m_DATEREG, this);
        g_RegDate = m_pRSet->m_DATEREG;
        dlg.m_sCaption = GetTok(s, 0, _T("\n") );
        dlg.m_SectName = _T("BIRTH_FORTAX");
        dlg.m_MaxPage1 = 53;
        dlg.m_MaxPage2 = 57;
        if ( dlg.DoModal()==IDYES ) {
          nPage1 = dlg.m_MaxPage1;
          nPage2 = dlg.m_MaxPage2;
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_ABC: {
        CABCDlg dlg(false, this);
        dlg.m_AfterTitle = _T("Додавати до списку нові прізвищами, імена, по батькові");
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_BIRTH_IN, theApp.m_sTemplatePath, _T("ABC") );
          sOut.Format(IDS_BIRTH_OUT, theApp.m_sOutPath, _T("ABC"), m_DateReg.GetDate().GetYear());
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_BIRTH_01_2_3  :    case ID_PRINT_BIRTH_02_2_15 :
    case ID_PRINT_BIRTH_04_2_16 :    case ID_PRINT_BIRTH_05_2_17 :
    case ID_PRINT_BIRTH_06_2_19 :    case ID_PRINT_BIRTH_07_2_20 :
    case ID_PRINT_BIRTH_08_2_29 :    case ID_PRINT_BIRTH_09_2_30 :
    case ID_PRINT_BIRTH_31_7_1  :    case ID_PRINT_BIRTH_35_7_1  :
    case ID_PRINT_BIRTH_39_7_8  :    case ID_PRINT_BIRTH_40_7_8  :
    case ID_PRINT_BIRTH_41_7_8  :    case ID_PRINT_BIRTH_42_7_8  :
    case ID_PRINT_BIRTH_49_7_8  :    case ID_PRINT_BIRTH_50_7_8  :
    case ID_PRINT_BIRTH_51_7_8  :    case ID_PRINT_BIRTH_54_7_8  :
      OnBlankItem();
      return;
    case ID_PRINT_BLANK_REGISTER: {
        CBlanksDlg dlg(m_pRSet->m_DATEREG, this);
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_PATH_NAME_EXT, theApp.m_sTemplatePath, _T("Register.11.4.4"));
          sOut.Format(IDS_PATH_NAME_EXT, theApp.m_sOutPath,           _T("Register.11.4.4"));
          MakeInOutExt(sTemplate, sOut);
        }
      }
      break;
  }

  if ( sTemplate.IsEmpty() )
    return;

  switch( nPrintID ) {
    case ID_PRINT_BIRTH_FORTAX:
      if ( FALSE==ConvertTable(_T("список до податкової"), sTemplate, sOut, m_pRSet, nPage1, nPage2, FilterFuncForBirtList))
        return;
      break;
    case ID_PRINT_BIRTH_ABC:
      //if ( FALSE==RTF_ABCBirth(sTemplate, sOut, m_pRSet, nPage1, nPage2, FilterFuncForAbcBirt))
      //  return;
      if ( FALSE==RTF_ABCBirth(sTemplate, sOut, m_pRSet))
        return;
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

  OnRTFShell(sOut);

}

void CFormBirth::GetDecalantPassports() {
  CString sSeria   = m_DeclarantPassportSeria.GetText(),
          sNumber  = m_DeclarantPassportNumber.GetText();

  CString s = _T("Натисніть на цю кнопку, щоб задати паспортні дані для обох заявників");
  if ( FALSE==sSeria.IsEmpty() && FALSE==sSeria.IsEmpty() ) {
    s = GetPassport( (BYTE)m_DeclarantPassportType.GetIndex(), 
                     m_DeclarantPassportSeria.GetText(),
                     m_DeclarantPassportNumber.GetText(),
                     m_DeclarantPassportDate.GetDate(),
                     m_DeclarantPassportBy.GetCurText() );
  }
  m_btnDeclarantPassports.SetWindowText(s);
}

BOOL CFormBirth::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  switch( pWnd->GetDlgCtrlID() ) {
    case IDC_LBL_DECLARANT_PSERIA:
    case IDC_LBL_DECLARANT_PNUMBER:
    case IDC_LBL_DECLARANT_PDATE:
    case IDC_LBL_DECLARANT_PBY:
    case IDC_STATIC:
    case 0xFFFF:
      return TRUE;
  }
  return FALSE;
}
void CFormBirth::OnInitialUpdate() {
  #ifdef _DEBUG
    SYSTEMTIME st1;
    GetLocalTime(&st1);
  #endif
  BeginWaitCursor();
  GetRecordset();

  ((CMainFrame*)AfxGetMainWnd())->m_pBirthFrame = GetParentFrame();
  m_nPrinPos = CONTEXT_BIRTH; // Народження

  CEraForm::OnInitialUpdate();

/*
  if ( m_lblBirthCountry.GetSafeHwnd()==NULL )
    m_lblBirthCountry.SubclassDlgItem(IDC_BC_LABEL, this);
*/
  if ( m_lblSourceOf.GetSafeHwnd()==NULL )
    m_lblSourceOf.SubclassDlgItem(IDC_SOURCE_OF_LABEL, this);
  if ( m_lblSourceBy.GetSafeHwnd()==NULL )
    m_lblSourceBy.SubclassDlgItem(IDC_SOURCE_BY_LABEL, this);
/*
  if ( m_lblDeclarantSeria.GetSafeHwnd()==NULL )
    m_lblDeclarantSeria.SubclassDlgItem(IDC_LBL_DECLARANT_PSERIA, this);
  if ( m_lblDeclarantNumber.GetSafeHwnd()==NULL )
    m_lblDeclarantNumber.SubclassDlgItem(IDC_LBL_DECLARANT_PNUMBER, this);
  if ( m_lblDeclarantPDate.GetSafeHwnd()==NULL )
    m_lblDeclarantPDate.SubclassDlgItem(IDC_LBL_DECLARANT_PDATE, this);
*/
  //m_DateReg.SetBeforeKillFocusHandler((pBeforeKillFocus)CheckDateReg);

  CRect r, r1, r2;
  m_DeclarantPassportType.GetWindowRect(&r1); ScreenToClient(&r1);
  m_DeclarantPassportBy.GetWindowRect(&r2); ScreenToClient(&r2);
  r.SetRect( r1.left, r1.top, r2.right, r2.bottom);
  GetDlgItem(IDC_DECLARANT_DLG)->SetWindowPos(NULL, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER);
  SetRect(GetDlgItem(IDC_DECLARANT_DLG), &r);

  m_fMedCertPseudoChanged = false;
  if ( m_pRSet->IsOpen() ) {
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

    CString strTitle = m_pRSet->m_pDatabase->GetName();
    strTitle += _T(" - Народження");
    CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
    pDoc->SetTitle(strTitle);

    m_fSex.SetText(_T("Актовий запис про народження хлопчика"),
                   _T("Актовий запис про народження дівчинки")
                  );
    m_fSex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
    m_fSex.SetButtonStyle(BS_OWNERDRAW, TRUE);
    m_fSex.SetIcons(IDI_SIGNMALE, IDI_SIGNFEMALE);


//    m_lblMotherSurname.SetText(_T("Прізвище"), _T("Нове прізвище") );
//    m_lblMotherSurname.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);

    m_cmbBirthCountry.SetDefault(theIniCache.GetBIRTH_BP_COUNTRY());
    m_cmbBirthRegion.SetDefault(theIniCache.GetBIRTH_BP_REGION());
    m_cmbBirthDistrict.SetDefault(theIniCache.GetBIRTH_BP_DISTRICT());
    m_cmbBirthCity.SetDefault(theIniCache.GetBIRTH_BP_CITY());

    m_FatherCountry.SetDefault(theIniCache.GetCOUNTRY());
    m_MotherCountry.SetDefault(theIniCache.GetCOUNTRY());

    m_FatherRegion.SetDefault(theIniCache.GetREGION());
    m_MotherRegion.SetDefault(theIniCache.GetREGION());
    m_FatherDistrict.SetDefault(theIniCache.GetDISTRICT());
    m_MotherDistrict.SetDefault(theIniCache.GetDISTRICT());
    m_FatherCity.SetDefault(theIniCache.GetCITY());
    m_MotherCity.SetDefault(theIniCache.GetCITY());

    m_SourceBy.SetDefault(theIniCache.GetRAGS());

    GetDlgItem(IDC_MCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
    GetDlgItem(IDC_WCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);

    m_Alive_Flag.SetText(_T("живонароджена"), _T("мертвонароджена"));
    //m_Alive_Flag.SetForeColor(RGB(0xFF, 0x20, 0x20), RGB(0x00, 0x00, 0x00));
    GetDlgItem(IDC_ALIVE_FLAG)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);

    theHospitals.FillCombo(m_MedCertPseudo, m_MedCertBy, m_pRSet->m_MEDICAL_CERTIFICATE_BY);

    m_BirthPlace.SetText( _T("Місце народження:"), _T("Місце народження:") );
    m_BirthPlace.SetButtonStyle(BS_OWNERDRAW, TRUE);

    m_Decl20.SetText(_T("-> Гр20"), _T("-> Гр18"));

    theCitizenships.FillCombo( m_FatherCitizenship, m_pRSet->m_FATHER_CITIZENSHIP );
    theCitizenships.FillCombo( m_MotherCitizenship, m_pRSet->m_MOTHER_CITIZENSHIP );
/************************************** : by VK at 23.01.2004 10:35:12 **\
    theMNames.FillCombo( m_FatherName, m_pRSet->m_FATHER_NAME );
    theWNames.FillCombo( m_MotherName, m_pRSet->m_MOTHER_NAME );
    theMPatronymics.FillCombo( m_FatherPatronymic, m_pRSet->m_FATHER_PATRONYMIC );
    theWPatronymics.FillCombo( m_MotherPatronymic, m_pRSet->m_MOTHER_PATRONYMIC );
\************************************** : by VK at 23.01.2004 10:35:16 **/
    m_FatherCitizenship.SetDefault( g_szDefCitizenship );
    m_MotherCitizenship.SetDefault( g_szDefCitizenship );
    theMIAs.FillCombo( m_DeclarantPassportBy, m_pRSet->m_DECLARANT_PASSPORT_BY );
    m_DeclarantPassportBy.SetDefault( theIniCache.GetByROVD() );

    theStreets.FillCombo( m_FatherStreet, m_pRSet->m_FATHER_STREET );
    theStreets.FillCombo( m_MotherStreet, m_pRSet->m_MOTHER_STREET );

    OnMove(ID_RECORD_LAST);
//    m_fSex.SetFocus();

  }

  EndWaitCursor();

//  SetFocusToFirstControl();
  #ifdef _DEBUG
    SYSTEMTIME st2;
    GetLocalTime(&st2);
    int Milliseconds = ((int)st2.wHour)*60*60*1000 - ((int)st1.wHour)*60*60*1000
                     + ((int)st2.wMinute)*60*1000 - ((int)st1.wMinute)*60*1000
                     + ((int)st2.wSecond)*1000 - ((int)st1.wSecond)*1000
                     + ((int)st2.wMilliseconds) - ((int)st1.wMilliseconds);
    TRACE1("\nCFormBirth::OnInitialUpdate() worked %d milliseconds.\n", Milliseconds); // 594 ms before optimization, 203 - after first optimization
  #endif

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

void CFormBirth::SetNewNames() {
  CString s, szAltText;
  s = m_pRSet->GetNewSurname();
  if ( s.IsEmpty() ) {
    m_Surname.SetAltText(_T(""), 0);
  }
  else {
    szAltText.Format(_T("(%s)"), s);
    m_Surname.SetAltText(szAltText, RGB(0,0,255));
  }
  s = m_pRSet->GetNewName();
  if ( s.IsEmpty() ) {
    m_Name.SetAltText(_T(""), 0);
  }
  else {
    szAltText.Format(_T("(%s)"), s);
    m_Name.SetAltText(szAltText, RGB(0,0,255));
  }
  s = m_pRSet->GetNewPatronymic();
  if ( s.IsEmpty() ) {
    m_Patronymic.SetAltText(_T(""), 0);
  }
  else {
    szAltText.Format(_T("(%s)"), s);
    m_Patronymic.SetAltText(szAltText, RGB(0,0,255));
  }

}
BOOL CFormBirth::OnMove(UINT nIDMoveCommand) {
  if ( NULL==m_pRSet )
    return FALSE;
  if ( m_pRSet->IsBOF() && m_pRSet->IsEOF() )
    return FALSE;

  BOOL bRet = CEraForm::OnMove(nIDMoveCommand);
  if ( bRet ) {
    m_fMedCertPseudoChanged = false;
    OnSexDependences();
    OnBirthPlaceDependences();
    OnSourceTypeDependences();

    m_Alive_Flag.SetOn( IsAlive() );
    m_Alive_Flag.Reset();

    GetDlgItem(IDC_LBL_RENEW)   ->ShowWindow( IsRenew()    ? SW_SHOW : SW_HIDE );
    GetDlgItem(IDC_LBL_LONGTERM)->ShowWindow( IsLongTerm() ? SW_SHOW : SW_HIDE );

    m_Decl20.SetOn( m_pRSet->IsDeclarantIn20() );
    m_Decl20.Reset();


    theGeoCache.FillCountryCB(m_cmbBirthCountry, m_pRSet->m_BP_COUNTRY);
    theGeoCache.FillCountryCB(m_FatherCountry, m_pRSet->m_FATHER_COUNTRY);
    theGeoCache.FillCountryCB(m_MotherCountry, m_pRSet->m_MOTHER_COUNTRY);

    theGeoCache.FillRegionCB(m_cmbBirthRegion, m_cmbBirthCountry, m_pRSet->m_BP_REGION);
    theGeoCache.FillRegionCB(m_FatherRegion, m_FatherCountry, m_pRSet->m_FATHER_REGION);
    theGeoCache.FillRegionCB(m_MotherRegion, m_MotherCountry, m_pRSet->m_MOTHER_REGION);

    theGeoCache.FillDistrictCB(m_cmbBirthDistrict, m_cmbBirthRegion, m_pRSet->m_BP_DISTRICT);
    theGeoCache.FillDistrictCB(m_FatherDistrict, m_FatherRegion, m_pRSet->m_FATHER_DISTRICT);
    theGeoCache.FillDistrictCB(m_MotherDistrict, m_MotherRegion, m_pRSet->m_MOTHER_DISTRICT);

    theGeoCache.FillCityCB(m_cmbBirthCity, m_cmbBirthRegion, m_cmbBirthDistrict, m_pRSet->m_BP_CITY);
    theGeoCache.FillCityCB(m_FatherCity, m_FatherRegion, m_FatherDistrict, m_pRSet->m_FATHER_CITY);
    theGeoCache.FillCityCB(m_MotherCity, m_MotherRegion, m_MotherDistrict, m_pRSet->m_MOTHER_CITY);

    theMNames.FillCombo( m_FatherName, m_pRSet->m_FATHER_NAME, false);
    theMPatronymics.FillCombo( m_FatherPatronymic, m_pRSet->m_FATHER_PATRONYMIC, false );
    theWNames.FillCombo( m_MotherName, m_pRSet->m_MOTHER_NAME, false);
    theWPatronymics.FillCombo( m_MotherPatronymic, m_pRSet->m_MOTHER_PATRONYMIC, false );

    theRList.FillRegCB(m_SourceBy, m_pRSet->m_SOURCE_BY);

    theMIAs.Add( m_DeclarantPassportBy, m_pRSet->m_DECLARANT_PASSPORT_BY );
    ShowPassportButton(m_DeclarantType.GetIndex()==2);

    theStreets.Add( m_FatherStreet, m_pRSet->m_FATHER_STREET );
    theStreets.Add( m_MotherStreet, m_pRSet->m_MOTHER_STREET );

    SetNewNames();

  }
  return bRet;
}

void CFormBirth::OnSetFocusMotherStreet() {
  if ( m_MotherStreet.IsEmpty() ) {
    if (    m_FatherCountry.GetCurText()==m_MotherCountry.GetCurText()
         && m_FatherRegion.GetCurText()==m_MotherRegion.GetCurText()
         && m_FatherDistrict.GetCurText()==m_MotherDistrict.GetCurText()
         && m_FatherCity.GetCurText()==m_MotherCity.GetCurText() )
      m_MotherStreet.SetCurText( m_FatherStreet.GetCurText() );
  }
}

BOOL CFormBirth::IsRenew() {
  long lFlags = atol(m_Flags.GetText());
  return (lFlags & BIRTH_RENEW);
}

BOOL CFormBirth::IsLongTerm() {
  long lFlags = atol(m_Flags.GetText());
  return (lFlags & BIRTH_LONGTERM);
}
BOOL CFormBirth::IsAlive() {
  return atol(m_AliveFlag.GetText());
}
BOOL CFormBirth::IsDeclarantIn20() {
  long lFlags = atol(m_Flags.GetText());
  return (lFlags & BIRTH_DECL20);
}

void CFormBirth::OnRenew() {
  long lFlags = atol(m_Flags.GetText());
  if ( lFlags & BIRTH_RENEW )
    lFlags &= ~(BIRTH_RENEW);
  else
    lFlags |= BIRTH_RENEW;
  CString s;
  s.Format(_T("%d"), lFlags);
  GetDlgItem(IDC_RENEW)->SetWindowText(s);
  GetDlgItem(IDC_LBL_RENEW)->ShowWindow( lFlags & BIRTH_RENEW ? SW_SHOW : SW_HIDE );
}

void CFormBirth::OnLongTerm() {
  long lFlags = atol(m_Flags.GetText());
  if ( lFlags & BIRTH_LONGTERM )
    lFlags &= ~(BIRTH_LONGTERM);
  else
    lFlags |= BIRTH_LONGTERM;
  CString s;
  s.Format(_T("%d"), lFlags);
  GetDlgItem(IDC_RENEW)->SetWindowText(s);
  GetDlgItem(IDC_LBL_LONGTERM)->ShowWindow( lFlags & BIRTH_LONGTERM ? SW_SHOW : SW_HIDE );
}

void CFormBirth::OnAliveFlag() {
  CString s;
  BOOL fAlive = IsAlive() ^ 1;
  s.Format(_T("%d"), fAlive);
  m_AliveFlag.SetWindowText(s);
  m_Alive_Flag.SetOn( fAlive );
}

void CFormBirth::OnDecl20() {
  m_Decl20.SetOn( !m_Decl20.m_bOn );
  OnDeclarant20();
}

void CFormBirth::OnDeclarant20() {
  long lFlags = atol(m_Flags.GetText());
  if ( m_Decl20.m_bOn )
    lFlags |= BIRTH_DECL20;
  else
    lFlags &= ~(BIRTH_DECL20);
  CCyrString s, s1, s2;
  CString sNotice;
  s.Format(_T("%d"), lFlags);
  GetDlgItem(IDC_RENEW)->SetWindowText(s);
  sNotice = m_Notice.GetText();
  if ( (lFlags & BIRTH_DECL20)==0 ) {
    s1.Format(_T("%s з"), PassportName(m_DeclarantPassportType.GetIndex(), false));
    s1.MakeUpperFirstChar();
    s2 = CCyrString(m_DeclarantPassportBy.GetCurText());
    s2.TrimRight(" .");
    //if ( !s2.IsEmpty() ) {
      s2 += '.';
    //}
    s = CCyrString(GetSentence(sNotice, s1, s2));
    if ( !s.IsEmpty() ) {
      sNotice.Replace(s, _T(""));
      sNotice = Trim(sNotice);
    }
  }
  else {
    s1 = s2 = CCyrString(PassportName(m_DeclarantPassportType.GetIndex(), false));
    s2.MakeUpperFirstChar();
    if ( m_DeclarantType.GetIndex()==0 )
      s2 += _T(" заявника ");
    else
      s2 += _T(" заявниці ");
    s = CCyrString(GetPassport(m_DeclarantPassportType.GetIndex(), m_DeclarantPassportSeria.GetText(), m_DeclarantPassportNumber.GetText(), m_DeclarantPassportDate.GetDate(), m_DeclarantPassportBy.GetCurText()));
    s.Replace(s1, s2);
    sNotice += _T(" ");
    sNotice += s;
    sNotice.TrimRight(" .");
    sNotice += '.';
  }
  m_Notice.SetWindowText(sNotice);
}

void CFormBirth::OnSetfocusMotherHouse() {
  if ( m_MotherHouse.IsEmpty() ) {
    if ( m_FatherStreet.GetCurText()==m_MotherStreet.GetCurText() ) {
      m_MotherHouse.SetWindowText( m_FatherHouse.GetText() );
      m_MotherHouse.SetSel(0, -1);
    }
  }
}

void CFormBirth::OnSetfocusMotherFlat() {
  if ( m_MotherFlat.IsEmpty() ) {
    if ( m_MotherHouse.GetText()==m_MotherHouse.GetText() ) {
      m_MotherFlat.SetWindowText( m_FatherFlat.GetText() );
      m_MotherFlat.SetSel(0, -1);
    }
  }
}

LRESULT CFormBirth::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam) {
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
  else if ( stricmp(szMessage, "newnames")==0 ) {
    m_fEnableRelayEvent = true;
    CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
    pMainFrame->PostMessage(WM_COMMAND,  MAKEWPARAM(ID_EXTNOTES, 0), LPARAM(pMainFrame->m_wndDlgBar.m_hWnd) );
  }
  m_tooltip.HideTooltip();

  return TRUE;
}

void CFormBirth::OnSelendokMedicalCertificatePseudunym() {
	// TODO: Add your control notification handler code here
  m_fMedCertPseudoChanged = true;
  OnSetfocusMedicalCertificateBy();
}

void CFormBirth::OnRecordDelete() {
  CEraForm::OnRecordDelete();
}
void CFormBirth::OnRecordNew() {
  CEraForm::OnRecordNew();
}
BOOL CFormBirth::OnCommand(WPARAM wParam, LPARAM lParam) {
  // TODO: Add your specialized code here and/or call the base class
  BOOL bResult(FALSE);
  //bResult = CEraForm::OnCommand(wParam, lParam);
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
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
      //m_tooltip.HideTooltip();
      //m_fEnableRelayEvent = true;
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
    case IDC_SURNAME:
      if ( EN_KILLFOCUS==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnKillfocusSurname();
        return bResult;
      }
      break;
    case IDC_PATRONYMIC:
      if ( CBN_KILLFOCUS==wNotifyCode ) {
        static bool incall = false;
        if ( incall )
          break;
        bResult = CEraForm::OnCommand(wParam, lParam);
        incall = true;
        BeforeLeavePatronymic();
        incall = false;
        return bResult;
      }
      break;
    case IDC_BIRTH_PLACE:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnBirthPlaceDependences();
        return bResult;
      }
      else if ( BN_SETFOCUS==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        SetBPDefaults();
        return bResult;
      }
      break;
    case IDC_BIRTH_COUNTRY:         if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCountry(m_cmbBirthCountry);
      break;
    case IDC_BIRTH_REGION:          if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusRegion(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthCity);
      break;
    case IDC_BIRTH_DISTRICT:        if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusDistrict(m_cmbBirthRegion, m_cmbBirthDistrict);
      break;
    case IDC_BIRTH_CITY:            if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCity(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthDistrict, m_cmbBirthCity);
      break;

    case IDC_FATHER_CITIZENSHIP:    if ( CBN_SETFOCUS==wNotifyCode )  m_FatherCitizenship.UpdateByDefault();
      break;    
    case IDC_MOTHER_CITIZENSHIP:    if ( CBN_SETFOCUS==wNotifyCode )  m_MotherCitizenship.UpdateByDefault();
      break;    

    case IDC_FATHER_COUNTRY:        if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCountry(m_FatherCountry);
      break;
    case IDC_FATHER_REGION:         if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusRegion(m_FatherCountry, m_FatherRegion, m_FatherCity);
      break;
    case IDC_FATHER_DISTRICT:       if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusDistrict(m_FatherRegion, m_FatherDistrict);
      break;
    case IDC_FATHER_CITY:           if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCity(m_FatherCountry, m_FatherRegion, m_FatherDistrict, m_FatherCity);
      break;
    case IDC_MOTHER_COUNTRY:        if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCountry(m_MotherCountry);
      break;
    case IDC_MOTHER_REGION:         if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusRegion(m_MotherCountry, m_MotherRegion, m_MotherCity);
      break;
    case IDC_MOTHER_DISTRICT:       if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusDistrict(m_MotherRegion, m_MotherDistrict);
      break;
    case IDC_MOTHER_CITY:           if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusCity(m_MotherCountry, m_MotherRegion, m_MotherDistrict, m_MotherCity);
      break;
    case IDC_MOTHER_STREET:         if ( CBN_SETFOCUS==wNotifyCode )  OnSetFocusMotherStreet();
      break;
    case IDC_NKIDS: case IDC_BYCOUNT:
      if ( EN_SETFOCUS==wNotifyCode ) {
        CString s;
        GetDlgItem(wCtrlId)->GetWindowText(s);
        if ( s.IsEmpty() )
          GetDlgItem(wCtrlId)->SetWindowText(_T("1"));
      }
      break;
    case IDC_MEDICAL_CERTIFICATE_PSEUDUNYM:
      if ( CBN_EDITCHANGE==wNotifyCode )
        m_fMedCertPseudoChanged = true;
      break;
    case IDC_MEDICAL_CERTIFICATE_BY: if ( CBN_SETFOCUS==wNotifyCode )  OnSetfocusMedicalCertificateBy();
      break;
    case IDC_SOURCE_TYPE:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnSourceTypeDependences();
        return bResult;
      }
      break;
    case IDC_FATHER_NAME:
      if ( CBN_SETFOCUS==wNotifyCode ) {
        OnSetfocusFatherName();
      }
      break;
    case IDC_DECLARANT_TYPE:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnDeclarantType();
        return bResult;
      }
      break;
    case IDC_ALIVE_FLAG:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnAliveFlag();
        return bResult;
      }
      break;
    case IDC_DECLARANT_20:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnDeclarant20();
        return bResult;
      }
      break;
    case IDC_DECLARANT_PASSPORT_BY:   if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_DeclarantPassportSeria, m_DeclarantPassportNumber, m_DeclarantPassportBy);
      break;
    case IDC_SOURCE_BY:               if ( CBN_SETFOCUS==wNotifyCode ) m_SourceBy.UpdateByDefault();
      break;

    case IDC_DATEREG:
      if ( EN_KILLFOCUS==wNotifyCode ) {
        if ( IsFocusChild(this) ) {
          m_tooltip.HideTooltip();
          if ( FALSE==CheckDateReg(this, &m_DateReg, m_fNewRecord) ) {
            m_DateReg.SetFocus();
            return FALSE;
          }
        }
      }
      break;
    case IDC_DATEOFBIRTH:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DateBirth, _T("народження"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_MEDICAL_CERTIFICATE_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DateBirth, _T("народження"), &m_MedCertDate, _T("медичного свідоцтва"), FALSE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_SOURCE_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_SourceDate, _T("підстави відомостей про батька"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_FATHER_BIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_FatherDate, _T("народження батька"), &m_DateBirth, _T("народження дитини"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_MOTHER_BIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MotherDate, _T("народження матері"), &m_DateBirth, _T("народження дитини"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_DECLARANT_PASSPORT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_DeclarantPassportDate, _T("видачі паспарту"), &m_DateReg, _T("реєстрації"), TRUE) ) {
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

void CFormBirth::OnUpdateRecordDelete(CCmdUI* pCmdUI) {
  pCmdUI->Enable(( m_pRSet!=NULL) & !m_pRSet->IsDeleted());
}

void CFormBirth::OnSetfocusDatereg() {
  SetDefaultDateReg(IDD_FORM_BIRTH);
}

void CFormBirth::OnSetfocusNumber() {
  if ( 0==m_pRSet->m_NUMBER && SetDefaultNumber(m_pRSet->m_NUMBER) ) {
    m_pRSet->Edit();
    m_pRSet->Update();
    UpdateData(TRUE);
//    m_pRSet->Move(0);
    m_pRSet->SetBookmark( m_pRSet->GetLastModifiedBookmark() );
    SetBookMarks();
  }
}

void CFormBirth::OnSetfocusMedicalCertificateDate() {
  CString s;
  m_MedCertDate.GetWindowText(s);
  if ( s.IsEmpty() ) {
    m_DateBirth.GetWindowText(s);
    m_MedCertDate.SetWindowText(s);
  }
}

void CFormBirth::OnSetfocusMedicalCertificateBy() {
  if ( false==m_fMedCertPseudoChanged )
    return;
  int nItem = m_MedCertPseudo.GetCurSel();
  if ( CB_ERR != nItem ) {
    CString sKey;
    m_MedCertPseudo.GetLBText(nItem, sKey);
    if ( !sKey.IsEmpty() ) {
      CString sName;
      CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
      theHospitals.Lookup(sKey, sName);
      if ( !sName.IsEmpty() ) {
        nItem = m_MedCertBy.FindString(-1, sName);
        if ( CB_ERR==nItem )
          nItem = m_MedCertBy.AddString(sName);
        m_MedCertBy.SetCurSel(nItem);
        m_fMedCertPseudoChanged = false;
      }
    }
  }
}
void CFormBirth::OnSetfocusSourceDate() {
  if ( m_SourceType.GetIndex()!=BIRTH_TYPE_ACT ) {
    CString s;
    m_SourceDate.GetWindowText(s);
    if ( s.IsEmpty() ) {
      m_DateReg.GetWindowText(s);
      m_SourceDate.SetWindowText(s);
    }
  }
}

void CFormBirth::OnSetfocusFatherSurname() {
  CString s;
  m_FatherSurname.GetWindowText(s);
  if ( s.IsEmpty() ) {
    s = OfferSurname(&m_Surname, m_fSex.IsOn(), TRUE);
    m_FatherSurname.SetWindowText(s);
    m_FatherSurname.SetSel(0, -1);
  }
}

void CFormBirth::OnSetfocusFatherName() {
  // TODO: Add your control notification handler code here
  CString sName = m_FatherName.GetCurText();
  int nItem = m_FatherName.GetCurSel();
  if ( CB_ERR != nItem )
    return;
  if ( !sName.IsEmpty() ) {
    m_FatherName.SetCurText(sName);
    return;
  }
  nItem = m_Patronymic.GetCurSel();
  if ( CB_ERR != nItem ) {
    CString sPatro;
    m_Patronymic.GetLBText(nItem, sPatro);
    if ( !sPatro.IsEmpty() ) {
      CString s;
      CFByP* p = theDataManager.m_FByPArray.Offer(sPatro);
      if ( p )
        s = p->m_sName;
      else
        s = theDataManager.m_FByPArray.OfferDefault(sPatro);
      if ( !s.IsEmpty() ) {
        nItem = m_FatherName.FindString(-1, s);
        if ( CB_ERR==nItem )
          nItem = m_FatherName.AddString(s);
        m_FatherName.SetCurSel( nItem );
      }
    }
  }
}

void CFormBirth::OnSetfocusDateofBirth() {
  CString s;
  m_DateBirth.GetWindowText(s);
  if ( s.IsEmpty() ) {
    COleDateTime odt = m_DateReg.GetDate();
    if ( COleDateTime::valid==odt.m_status ) {
      odt -= COleDateTimeSpan(7, 0, 0, 0);
      s.Format( _T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
      m_DateBirth.SetWindowText(s);
    }
  }
}

void CFormBirth::OnSetfocusMotherSurname() {
  CString s;
  m_MotherSurname.GetWindowText(s);
  if ( s.IsEmpty() ) {
    m_FatherSurname.GetWindowText(s);
    if( !s.IsEmpty() ) {
      s = OfferSurname(&m_FatherSurname, TRUE, FALSE);
      m_MotherSurname.SetWindowText(s);
      int nLen = s.GetLength();
      m_MotherSurname.SetSel(nLen, nLen);
    }
  }
}

void CFormBirth::OnSetfocusDeclaranType() {
  CString sName, sAddress;
//  m_DeclarantName.GetWindowText(sName);
//  m_DeclarantAddress.GetWindowText(sAddress);
//  if ( sName.IsEmpty() && sAddress.IsEmpty() ) {
    OnDeclarantType();
//  }
}

void CFormBirth::OnSetfocusCertificateSeria() {
  if ( m_CertificateSeria.IsEmpty() ) {
    m_CertificateSeria.SetWindowText( theIniCache.GetBIRTH_Seria() );
    m_CertificateSeria.SetSel(0, -1);
  }
}

void CFormBirth::OnSetfocusCertificateNumber() {
  CString s;
  m_CertificateNumber.GetWindowText(s);
  bool fSeriaIsEmpty = m_CertificateSeria.IsEmpty();
  if ( s.IsEmpty() && !fSeriaIsEmpty ) {
    s = theIniCache.GetBIRTH_CNum();
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

void CFormBirth::OnChangeCertificateNumber() {
  theIniCache.SetBIRTH_CNum( &m_CertificateNumber );  
}

void CFormBirth::OnSetfocusNotice() {
  CString s, sNewNumber, sNewNumber2, sMemo;
  m_Notice.GetWindowText(s);
  if ( !s.IsEmpty() )
    return;

  bool fOne = true;
  switch ( m_SourceType.GetIndex() ) {
    case BIRTH_TYPE_ACT:           // 0 Актовий запис про шлюб
      break;
    case BIRTH_TYPE_MOTHER:        // 1 Заява матері №
      fOne = false;
      break;
    case BIRTH_TYPE_PARENTS:       // 2 Заява батьків №
      break;
    case BIRTH_TYPE_APPL:          // 3 Заява
    case BIRTH_TYPE_APPLNUM:       // 4 Заява №
      if ( COleDateTime::valid ==m_FatherDate.GetDate().GetStatus() )
        fOne = false;
      break;
    case BIRTH_TYPE_AFFILIATION1:  // 5 Заява про ВБ №
    case BIRTH_TYPE_AFFILIATION2:  // 6 Спілька заява батьквів про ВБ №
      break;
  }

  try {
    COleVariant bm = m_pRSet->GetBookmark();
    m_pRSet->MoveLast();
    while( !m_pRSet->IsBOF() ) {
      s = m_pRSet->m_NOTICE;
      if ( !s.IsEmpty() ) {
        if ( sNewNumber.IsEmpty() )
          sNewNumber = GetNumFromStr(s, _T("довідка №"));
        else if ( false==fOne && sNewNumber2.IsEmpty() ) {
          int nFound = s.Find(_T("захисту населення"), 0);
          if ( nFound >= 0 ) {
            bool bFound = false;
            while ( nFound >= 0 ) {
              if ( s[nFound]=='№' ) {
                bFound = true;
                break;
              }
              nFound--;
            }
            if ( bFound ) {
              CString sFound = s.Mid(nFound);
              sNewNumber2 = GetNumFromStr(sFound, _T("№"));
            }
          }
        }

        if ( fOne && !sNewNumber.IsEmpty() )
          break;
        if ( false==fOne && !sNewNumber2.IsEmpty() )
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

  // Свідоцтво, довідки
  if ( m_CertificateSeria.IsEmpty() ) {
    sMemo = theIniCache.GetNoCert();
    //lFlags |= BIR_FLAG_CERTIFICATE;
  }
  else {
    //lFlags &= ~BIR_FLAG_CERTIFICATE;
    COleDateTime odt(m_DateReg.GetDate());
    CString szDate;
    szDate.Format(_T("%02d.%02d.%04d р."), odt.GetDay(), odt.GetMonth(), odt.GetYear());
    if ( fOne ) {
      /*
      sMemo.Format(IDS_BIR_DOVIDKA_1, sNewNumber, odt.GetDay(), odt.GetMonth(), odt.GetYear());
      IDS_BIR_DOVIDKA_1       "Видана довідка № %s від %02d.%02d.%02d р. на отримання допомоги у зв'язку з народженням дитини."
      */
      sMemo = theIniCache.GetBIRTH_DefNotice();
      ReplaceIgnoreCase(sMemo, _T("!№!"), sNewNumber);
      ReplaceIgnoreCase(sMemo, _T("!дата!"), szDate);
      ReplaceIgnoreCase(sMemo, _T(".."), _T("."));
    }
    else {
      if ( sNewNumber2.IsEmpty() )
        sNewNumber2 = _T("1");

      sMemo.Empty();
      /*
      s.Format(IDS_BIR_DOVIDKA_1, sNewNumber, odt.GetDay(), odt.GetMonth(), odt.GetYear() );
      IDS_BIR_DOVIDKA_1       "Видана довідка № %s від %02d.%02d.%02d р. на отримання допомоги у зв'язку з народженням дитини."
      */
      s = theIniCache.GetBIRTH_DefNotice();
      ReplaceIgnoreCase(s, _T("!№!"), sNewNumber);
      ReplaceIgnoreCase(s, _T("!дата!"), szDate);
      ReplaceIgnoreCase(s, _T(".."), _T("."));
      
      sMemo += s;
      /*
      s.Format(IDS_BIR_DOVIDKA_2, sNewNumber2, odt.GetDay(), odt.GetMonth(), odt.GetYear() );
      IDS_BIR_DOVIDKA_2       " Видана довідка № %s від %02d.%02d.%04d р. в управління праці та соціального захисту населення."
      */
      s += _T(" ");
      s = theIniCache.GetBIRTH_DefNotice2();
      ReplaceIgnoreCase(s, _T("!№!"), sNewNumber);
      ReplaceIgnoreCase(s, _T("!дата!"), szDate);
      ReplaceIgnoreCase(s, _T(".."), _T("."));
      sMemo += s;
    }
  }

  if ( m_DeclarantPassportNumber.IsEmpty() ) {
    s.LoadString(IDS_DECPASSPORT);
    sMemo += s; sMemo = Trim(sMemo);
  }

  m_Notice.SetWindowText( sMemo );
}

void CFormBirth::ShowPassportButton(BOOL bShowTwoPassportButton) {
  if ( bShowTwoPassportButton ) {
    GetDecalantPassports();
    m_DeclarantPassportType.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LBL_DECLARANT_PSERIA)->ShowWindow(SW_HIDE);
    m_DeclarantPassportSeria.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LBL_DECLARANT_PNUMBER)->ShowWindow(SW_HIDE);
    m_DeclarantPassportNumber.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LBL_DECLARANT_PDATE)->ShowWindow(SW_HIDE);
    m_DeclarantPassportDate.ShowWindow(SW_HIDE);
    GetDlgItem(IDC_LBL_DECLARANT_PBY)->ShowWindow(SW_HIDE);
    m_DeclarantPassportBy.ShowWindow(SW_HIDE);

    CRect r;
    m_DeclarantPassportType.GetWindowRect(&r);
    int Left = r.left;
    int Height = r.Height();
    m_DeclarantPassportBy.GetWindowRect(&r);
    r.left = Left;
    ScreenToClient(&r);
    m_btnDeclarantPassports.MoveWindow(&r);
    m_btnDeclarantPassports.ShowWindow(SW_SHOW);
  }
  else {
    m_btnDeclarantPassports.ShowWindow(SW_HIDE);
    m_DeclarantPassportType.ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LBL_DECLARANT_PSERIA)->ShowWindow(SW_SHOW);
    m_DeclarantPassportSeria.ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LBL_DECLARANT_PNUMBER)->ShowWindow(SW_SHOW);
    m_DeclarantPassportNumber.ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LBL_DECLARANT_PDATE)->ShowWindow(SW_SHOW);
    m_DeclarantPassportDate.ShowWindow(SW_SHOW);
    GetDlgItem(IDC_LBL_DECLARANT_PBY)->ShowWindow(SW_SHOW);
    m_DeclarantPassportBy.ShowWindow(SW_SHOW);
  }
}

void CFormBirth::OnDeclarantType() {
  CString sName, sAddress;
  BOOL bShowTwoPassportButton = FALSE;
  switch ( m_DeclarantType.GetIndex() ) {
    case 0: if ( false==m_FatherSurname.IsEmpty() ) {
              sName = MakeFIO(&m_FatherSurname, &m_FatherName, &m_FatherPatronymic);
              sAddress = MakeAddress(&m_FatherCountry, &m_FatherRegion, &m_FatherCity, &m_FatherDistrict, &m_FatherStreet, &m_FatherHouse, &m_FatherFlat);
            }
      break;
    case 1: if ( false==m_MotherSurname.IsEmpty() ) {
              sName = MakeFIO(&m_MotherSurname, &m_MotherName, &m_MotherPatronymic);
              sAddress = MakeAddress(&m_MotherCountry, &m_MotherRegion, &m_MotherCity, &m_MotherDistrict, &m_MotherStreet, &m_MotherHouse, &m_MotherFlat);
            }
      break;
    case 2: if ( false==m_FatherSurname.IsEmpty() ) {
              sName = MakeFIO(&m_FatherSurname, &m_FatherName, &m_FatherPatronymic)
                    + _T(", ")
                    + MakeAddress(&m_FatherCountry, &m_FatherRegion, &m_FatherCity, &m_FatherDistrict, &m_FatherStreet, &m_FatherHouse, &m_FatherFlat);
            }
            if ( false==m_MotherSurname.IsEmpty() ) {
              sAddress = MakeFIO(&m_MotherSurname, &m_MotherName, &m_MotherPatronymic)
                       + _T(", ")
                       + MakeAddress(&m_MotherCountry, &m_MotherRegion, &m_MotherCity, &m_MotherDistrict, &m_MotherStreet, &m_MotherHouse, &m_MotherFlat);
            }
            bShowTwoPassportButton = TRUE;
      break;
  }

  m_DeclarantName.SetWindowText(sName);
  m_DeclarantAddress.SetWindowText(sAddress);

  ShowPassportButton(bShowTwoPassportButton);

}

void CFormBirth::OnUpdateExtnotes(CCmdUI* pCmdUI) {
  pCmdUI->Enable();
}

void CFormBirth::OnExtnotes() {
  m_tooltip.HideTooltip();
  CExtBirthDlg dlg(this);
  dlg.m_pSet = m_pRSet;
  dlg.m_fSex = m_fSex.IsOn() ? true : false;
  GetDlgItem(IDC_SURNAME)->GetWindowText(dlg.m_Surname);
  dlg.m_Name = m_Name.GetCurText();
  dlg.m_Patronymic = m_Patronymic.GetCurText();
  GetDlgItem(IDC_FATHER_SURNAME)->GetWindowText(dlg.m_FatherSurname);
  dlg.m_FatherName = m_FatherName.GetCurText();
  dlg.m_FatherDate = m_FatherDate.GetDate();
  GetDlgItem(IDC_MOTHER_SURNAME)->GetWindowText(dlg.m_MotherSurname);
  dlg.m_MotherDate = m_MotherDate.GetDate();
  dlg.m_sGr10     = MedSv(m_pRSet);
  dlg.m_sNewGr10  = m_pRSet->GetGr10(m_ExtNotices.GetText());

  dlg.m_sMemo = m_ExtNotices.GetText();

  if ( IDYES==dlg.DoModal() ) {
    m_ExtNotices.SetWindowText( dlg.m_sMemo );
  }
}

void CFormBirth::OnDeclarantDlg() {
  // TODO: Add your control notification handler code here
  m_tooltip.HideTooltip();
  CPassportsDlg dlg( m_pRSet,
                     &m_ExtNotices,
                     &m_DeclarantPassportType,
                     &m_DeclarantPassportSeria,
                     &m_DeclarantPassportNumber,
                     &m_DeclarantPassportDate,
                     &m_DeclarantPassportBy,
                     this);
  if ( IDYES==dlg.DoModal() ) {
    m_ExtNotices.SetWindowText( dlg.m_sMemo );
    GetDecalantPassports();
  }
}

void CFormBirth::OnContextMenu(CWnd* pWnd, CPoint point) {
  m_tooltip.HideTooltip();
  UINT nPos = CONTEXT_BIRTH;
  CString s, sMemo;
  m_Notice.GetWindowText(sMemo);
  s = ContextMenu(m_Notice.m_hWnd, nPos, m_fSex.IsOn(), m_DateReg.GetDate(), sMemo, false);
  if ( s != sMemo ) {
    m_Notice.SetFocus();
    m_Notice.SetWindowText(s);
    switch ( nPos ) {
      case ID_PMMD1:
      case ID_PMMD2:
      case ID_NPM:
      case ID_MOTHERIS:
      case ID_FOUNDLING:
      case ID_OTHER_MARRIAGE:
        m_Notice.SetSel( s.GetLength()-1, s.GetLength()-1 );
        break;
    }
  }
}

void CFormBirth::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
	// TODO: Add your message handler code here and/or call default
/************************************** : by VK at 18.11.2005 23:20:45 **\
  CWnd* pWnd = GetDlgItem(nIDCtl);
  CString sText;
  pWnd->GetWindowText(sText);
\************************************** : by VK at 18.11.2005 23:20:48 **/
  switch( nIDCtl ) {
    case IDC_MCITIZEN_LABEL:
      DrawLabel(this, nIDCtl, lpDIS, 0xFFFFFF, g_clrMaleForeColor, TRUE, FALSE);
      return;
    case IDC_WCITIZEN_LABEL:
      DrawLabel(this, nIDCtl, lpDIS, 0xFFFFFF, g_clrFemaleForeColor, TRUE, FALSE);
      return;
    case IDC_ALIVE_FLAG: {
      COLORREF clrText = IsAlive() ? RGB(0xFF, 0x20, 0x20) : RGB(0x00, 0x00, 0x00);
      COLORREF clrBk = g_clrRight;//(g_clrLeft + g_clrRight)/2;
      DrawLabel(this, nIDCtl, lpDIS, clrText, clrBk, TRUE, TRUE);
      return;
      }
  }
	CEraForm::OnDrawItem(nIDCtl, lpDIS);
}
void CFormBirth::OnSize(UINT nType, int cx, int cy) {
  CEraForm::OnSize(nType, cx, cy);
  if ( m_DeclarantType.GetSafeHwnd() ) {
    ShowPassportButton(m_DeclarantType.GetIndex()==2);
  }
}

void CFormBirth::OnHelp() {
  CView* pView = GetParentFrame()->GetActiveView();
  theApp.OnHelp(_T("RegBirth"));
}