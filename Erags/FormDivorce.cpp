 // FormDivorce.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "..\Common\MDB.h"

#include "ABCDlg.h"
#include "Caches.h"
#include "CheckDateDlg.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "EragsDoc.h"
#include "ElectDlg.h"
#include "ExtNotice.h"
#include "FormDivorce.h"
#include "Geography.h"
#include "HelpMan.h"
#include "MainFrm.h"
#include "Menu.h"
#include "RNames.h"
#include "RList.h"
#include "RTFCnv.h"
#include "SVDlg.h"
#include "Div18.h"
#include "Div23.h"
#include "xMachine.h"

#include "RegDlg.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString g_sMSurname_OV, g_sWSurname_OV;
extern CString g_sMName_OV, g_sWName_OV;
extern CString g_sMPatronymic_OV, g_sWPatronymic_OV;

BOOL ConvertForElect(const CString& sTemplate, const CString& sOutName, CPtrArray& array);
BOOL RegDlg(CPPToolTip* pTooltip);

CString GetNextNumber(CRSDivorces* pSet, LPCTSTR szFieldName) {
  CString s, sNewNumber;

  try {
    COleVariant bm = pSet->GetBookmark();
    pSet->MoveLast();
    while( !pSet->IsBOF() ) {
      s = GetFieldString(pSet,  szFieldName);
      if ( !s.IsEmpty() ) {
        sNewNumber = GetNumFromStr(s, _T(""), true);
        if ( !sNewNumber.IsEmpty() )
          break;
      }
      pSet->MovePrev();
    }
    pSet->SetBookmark(bm);
  }

  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }
  if ( sNewNumber .IsEmpty() ) {
    sNewNumber  = '1';
  }

  return sNewNumber;
}


/////////////////////////////////////////////////////////////////////////////
// CFormDivorce

IMPLEMENT_DYNCREATE(CFormDivorce, CEraForm)

CFormDivorce::CFormDivorce()
             :CEraForm(CFormDivorce::IDD), m_pRSet((CRSDivorces*&)m_pSet) {
	//{{AFX_DATA_INIT(CFormDivorce)
	//}}AFX_DATA_INIT
  m_MMoneyType.AddState(0,_T("грн.")); m_MMoneyType.AddState(1,_T("крб.")); m_MMoneyType.AddState(2,_T("р."));
  m_WMoneyType.AddState(0,_T("грн.")); m_WMoneyType.AddState(1,_T("крб.")); m_WMoneyType.AddState(2,_T("р."));


/*
  m_GroundType.AddState(0, _T("Спільна заява про РШ"));
  m_GroundType.AddState(1, _T("Рішення суду про ВБВ") );
  m_GroundType.AddState(2, _T("Рішення суду про ВН") );
  m_GroundType.AddState(3, _T("Вирок суду ЗПБ") );
  m_GroundType.AddState(4, _T("Рішення суду") );
*/
/* закоментировано 05.01.2008
  m_GroundType.AddState(0, _T("Постанова про РШ (СЗ)") ); закоментировано 05.01.2008
  m_GroundType.AddState(1, _T("Постанова про РШ (РС про ВБВ)") );
  m_GroundType.AddState(2, _T("Постанова про РШ (РС про ВН)") );
  m_GroundType.AddState(3, _T("Постанова про РШ (ВС про ЗПБ)") );
  m_GroundType.AddState(4, _T("Рішення суду") );
*/

  m_szFormName = _T("FORM_DIVORCE");
}

CFormDivorce::~CFormDivorce() {
  if ( m_pSet ) {
    if( m_pSet->IsOpen() )
      m_pSet->Close();
    delete m_pSet;
    m_pSet = NULL;
  }
}

void CFormDivorce::SetFocusToFirstControl() {
  if ( FALSE==m_bEnabled )
    return;
  if ( m_DateReg.GetSafeHwnd() ) {
    m_DateReg.SetFocus();
    OnSetfocusDatereg();
  }
}
void CFormDivorce::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_LABEL_DATEREG:
    case IDC_LABEL_NUMBER:
    case IDC_LABEL_MARRIAGE_BY:
    case IDC_LABEL_MARRIAGE_NUMBER:
    case IDC_LABEL_MARRIAGE_DATE:
    case IDC_MCITIZEN_LABEL:            case IDC_WCITIZEN_LABEL:
    case IDC_LABEL_MOLD_SURNAME:        case IDC_LABEL_WOLD_SURNAME:  
    case IDC_LABEL_MNEW_SURNAME:        case IDC_LABEL_WNEW_SURNAME:
    case IDC_LABEL_MNAME:               case IDC_LABEL_WNAME:
    case IDC_LABEL_MPATRONYMIC:         case IDC_LABEL_WPATRONYMIC:
    case IDC_LABEL_MBIRTH_DATE:         case IDC_LABEL_WBIRTH_DATE:
    case IDC_LABEL_MPASSPORT_SERIA:     case IDC_LABEL_WPASSPORT_SERIA:
    case IDC_LABEL_MPASSPORT_NUMBER:    case IDC_LABEL_WPASSPORT_NUMBER:
    case IDC_LABEL_MPASSPORT_DATE:      case IDC_LABEL_WPASSPORT_DATE:
    case IDC_LABEL_MPASSPORT_BY:        case IDC_LABEL_WPASSPORT_BY:
    case IDC_LABEL_MRP_COUNTRY:         case IDC_LABEL_WRP_COUNTRY:
    case IDC_LABEL_MRP_REGION:          case IDC_LABEL_WRP_REGION:
    case IDC_LABEL_MRP_DISTRICT:        case IDC_LABEL_WRP_DISTRICT:
    case IDC_LABEL_MRP_CITY:            case IDC_LABEL_WRP_CITY:
    case IDC_LABEL_MRP_STREET:          case IDC_LABEL_WRP_STREET:
    case IDC_LABEL_MRP_HOUSE:           case IDC_LABEL_WRP_HOUSE:
    case IDC_LABEL_MRP_FLAT:            case IDC_LABEL_WRP_FLAT:
    case IDC_LABEL_MDUTY:               case IDC_LABEL_WDUTY:
    case IDC_LABEL_MCHECK_NUMBER:       case IDC_LABEL_WCHECK_NUMBER:
    case IDC_LABEL_MCHECK_DATE:         case IDC_LABEL_WCHECK_DATE:
    case IDC_LABEL_MCHECK_BANK:         case IDC_LABEL_WCHECK_BANK:
    case IDC_LABEL_MCERTIFICATE_SERIA:  case IDC_LABEL_WCERTIFICATE_SERIA:
    case IDC_LABEL_MCERTIFICATE_NUMBER: case IDC_LABEL_WCERTIFICATE_NUMBER:
    case IDC_LABEL_GROUND:              case IDC_LABEL_DATE:
    case IDC_LABEL_NKIDS:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CDaoRecordViewBG::SetScaleFlags(pWnd, wFlags);
  }
}

void CFormDivorce::DoDataExchange(CDataExchange* pDX) {
  if ( FALSE==pDX->m_bSaveAndValidate ) {
    m_MOLD_SURNAME_before_save     = m_pRSet->m_MOLD_SURNAME;
    m_MNEW_SURNAME_before_save     = m_pRSet->m_MNEW_SURNAME;
    m_WOLD_SURNAME_before_save     = m_pRSet->m_WOLD_SURNAME;
    m_WNEW_SURNAME_before_save     = m_pRSet->m_WNEW_SURNAME;
    m_MNAME_before_save            = m_pRSet->m_MNAME;
    m_MPATRONYMIC_before_save      = m_pRSet->m_MPATRONYMIC;
    m_WNAME_before_save            = m_pRSet->m_WNAME;
    m_WPATRONYMIC_before_save      = m_pRSet->m_WPATRONYMIC;
    m_NUMBER_before_save           = m_pRSet->m_NUMBER;
    m_DATEREG_before_save          = m_pRSet->m_DATEREG;
  }  
	CEraForm::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormDivorce)
	DDX_Control(pDX, IDC_NUMBER, m_Number);
	// DDX_Control(pDX, IDC_GROUND_TYPE, m_GroundType);
	DDX_Control(pDX, IDC_GROUND, m_Ground);
	DDX_Control(pDX, IDC_GROUND_NUMBER, m_GroundNumber);
	DDX_Control(pDX, IDC_NKIDS, m_NKids);
	DDX_Control(pDX, IDC_MARRIAGE_BY, m_MarriageBy);
	DDX_Control(pDX, IDC_MARRIAGE_NUMBER, m_MarriageNumber);
//	DDX_Control(pDX, IDC_MARRIAGE_DATE, m_MarriageDate);
	DDX_Control(pDX, IDC_MCITIZENSHIP, m_MCitizenship);
	DDX_Control(pDX, IDC_MMARRIAGE_NUMBER, m_MMarriageNumber);
	DDX_Control(pDX, IDC_MOLD_SURNAME, m_MOldSurname);
	DDX_Control(pDX, IDC_MNEW_SURNAME, m_MNewSurname);
	DDX_Control(pDX, IDC_MNAME, m_MName);
	DDX_Control(pDX, IDC_MPATRONYMIC, m_MPatronymic);
//	DDX_Control(pDX, IDC_MBIRTH_DATE, m_MBirthDate);
	DDX_Control(pDX, IDC_MBIRTH_COUNTRY, m_MBirthCountry);
	DDX_Control(pDX, IDC_MBIRTH_REGION, m_MBirthRegion);
	DDX_Control(pDX, IDC_MBIRTH_DISTRICT, m_MBirthDistrict);
	DDX_Control(pDX, IDC_MBIRTH_CITY, m_MBirthCity);
  DDX_Control(pDX, IDC_MPASSPORT_TYPE, m_MPassportType);
	DDX_Control(pDX, IDC_MPASSPORT_SERIA, m_MPassportSeria);
	DDX_Control(pDX, IDC_MPASSPORT_NUMBER, m_MPassportNumber);
//	DDX_Control(pDX, IDC_MPASSPORT_DATE, m_MPassportDate);
	DDX_Control(pDX, IDC_MPASSPORT_BY, m_MPassportBy);
	DDX_Control(pDX, IDC_MRP_COUNTRY, m_MRPCountry);
	DDX_Control(pDX, IDC_MRP_REGION, m_MRPRegion);
	DDX_Control(pDX, IDC_MRP_DISTRICT, m_MRPDistrict);
	DDX_Control(pDX, IDC_MRP_CITY, m_MRPCity);
	DDX_Control(pDX, IDC_MRP_STREET, m_MRPStreet);
	DDX_Control(pDX, IDC_MRP_HOUSE, m_MRPHouse);
	DDX_Control(pDX, IDC_MRP_FLAT, m_MRPFlat);
	DDX_Control(pDX, IDC_MDUTY, m_MDuty);
	DDX_Control(pDX, IDC_MDUTY2, m_MDuty2);
	DDX_Control(pDX, IDC_MMONEY_TYPE, m_MMoneyType);
	DDX_Control(pDX, IDC_MCHECK_NUMBER, m_MCheckNumber);
//	DDX_Control(pDX, IDC_MCHECK_DATE, m_MCheckDate);
	DDX_Control(pDX, IDC_MCHECK_BANK, m_MCheckBank);
	DDX_Control(pDX, IDC_MCERTIFICATE_SERIA, m_MCertificateSeria);
	DDX_Control(pDX, IDC_MCERTIFICATE_NUMBER, m_MCertificateNumber);
	DDX_Control(pDX, IDC_MNOTICE, m_MNotice);
	DDX_Control(pDX, IDC_WCITIZENSHIP, m_WCitizenship);
	DDX_Control(pDX, IDC_WMARRIAGE_NUMBER, m_WMarriageNumber);
	DDX_Control(pDX, IDC_WOLD_SURNAME, m_WOldSurname);
	DDX_Control(pDX, IDC_WNEW_SURNAME, m_WNewSurname);
	DDX_Control(pDX, IDC_WNAME, m_WName);
	DDX_Control(pDX, IDC_WPATRONYMIC, m_WPatronymic);
//	DDX_Control(pDX, IDC_WBIRTH_DATE, m_WBirthDate);
	DDX_Control(pDX, IDC_WBIRTH_COUNTRY, m_WBirthCountry);
	DDX_Control(pDX, IDC_WBIRTH_REGION, m_WBirthRegion);
	DDX_Control(pDX, IDC_WBIRTH_DISTRICT, m_WBirthDistrict);
	DDX_Control(pDX, IDC_WBIRTH_CITY, m_WBirthCity);
	DDX_Control(pDX, IDC_WPASSPORT_TYPE, m_WPassportType);
	DDX_Control(pDX, IDC_WPASSPORT_SERIA, m_WPassportSeria);
	DDX_Control(pDX, IDC_WPASSPORT_NUMBER, m_WPassportNumber);
//	DDX_Control(pDX, IDC_WPASSPORT_DATE, m_WPassportDate);
	DDX_Control(pDX, IDC_WPASSPORT_BY, m_WPassportBy);
	DDX_Control(pDX, IDC_WRP_COUNTRY, m_WRPCountry);
	DDX_Control(pDX, IDC_WRP_REGION, m_WRPRegion);
	DDX_Control(pDX, IDC_WRP_DISTRICT, m_WRPDistrict);
	DDX_Control(pDX, IDC_WRP_CITY, m_WRPCity);
	DDX_Control(pDX, IDC_WRP_STREET, m_WRPStreet);
	DDX_Control(pDX, IDC_WRP_HOUSE, m_WRPHouse);
	DDX_Control(pDX, IDC_WRP_FLAT, m_WRPFlat);
	DDX_Control(pDX, IDC_WDUTY, m_WDuty);
	DDX_Control(pDX, IDC_WDUTY2, m_WDuty2);
	DDX_Control(pDX, IDC_WMONEY_TYPE, m_WMoneyType);
	DDX_Control(pDX, IDC_WCHECK_NUMBER, m_WCheckNumber);
//	DDX_Control(pDX, IDC_WCHECK_DATE, m_WCheckDate);
	DDX_Control(pDX, IDC_WCHECK_BANK, m_WCheckBank);
	DDX_Control(pDX, IDC_WCERTIFICATE_SERIA, m_WCertificateSeria);
	DDX_Control(pDX, IDC_WCERTIFICATE_NUMBER, m_WCertificateNumber);
	DDX_Control(pDX, IDC_WNOTICE, m_WNotice);
	//}}AFX_DATA_MAP
  DDX_OleDate(pDX, IDC_DATEREG, m_DateReg, m_pRSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, m_pRSet->m_NUMBER, m_pRSet);
	// DDX_MSButton(pDX, IDC_GROUND_TYPE, m_GroundType, m_pRSet->m_GROUND_TYPE);
	DDX_FieldText(pDX, IDC_GROUND, m_pRSet->m_GROUND, m_pRSet);
	DDX_FieldText(pDX, IDC_GROUND_NUMBER, m_pRSet->m_GROUND_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_GROUND_DATE, m_GroundDate, m_pRSet->m_GROUND_DATE);
	DDX_FieldText(pDX, IDC_NKIDS, m_pRSet->m_NKIDS, m_pRSet);
	DDX_FieldText(pDX, IDC_MARRIAGE_BY, m_pRSet->m_MARRIAGE_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_MARRIAGE_NUMBER, m_pRSet->m_MARRIAGE_NUMBER, m_pRSet);
  DDX_OleDate(pDX, IDC_MARRIAGE_DATE, m_MarriageDate, m_pRSet->m_MARRIAGE_DATE);
	DDX_FieldText(pDX, IDC_MCITIZENSHIP, m_pRSet->m_MCITIZENSHIP, m_pRSet);
	DDX_FieldText(pDX, IDC_WCITIZENSHIP, m_pRSet->m_WCITIZENSHIP, m_pRSet);
	DDX_FieldText(pDX, IDC_MMARRIAGE_NUMBER, m_pRSet->m_MMARRIAGE_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WMARRIAGE_NUMBER, m_pRSet->m_WMARRIAGE_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_MOLD_SURNAME, m_pRSet->m_MOLD_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WOLD_SURNAME, m_pRSet->m_WOLD_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MNEW_SURNAME, m_pRSet->m_MNEW_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WNEW_SURNAME, m_pRSet->m_WNEW_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MNAME, m_pRSet->m_MNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WNAME, m_pRSet->m_WNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MPATRONYMIC, m_pRSet->m_MPATRONYMIC, m_pRSet);
	DDX_FieldText(pDX, IDC_WPATRONYMIC, m_pRSet->m_WPATRONYMIC, m_pRSet);

  DDX_FieldText(pDX, IDC_MBIRTH_COUNTRY , m_pRSet->m_MBIRTH_COUNTRY , m_pRSet);
  DDX_FieldText(pDX, IDC_MBIRTH_REGION  , m_pRSet->m_MBIRTH_REGION  , m_pRSet);
  DDX_FieldText(pDX, IDC_MBIRTH_DISTRICT, m_pRSet->m_MBIRTH_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_MBIRTH_CITY    , m_pRSet->m_MBIRTH_CITY    , m_pRSet);

  DDX_FieldText(pDX, IDC_WBIRTH_COUNTRY , m_pRSet->m_WBIRTH_COUNTRY , m_pRSet);
  DDX_FieldText(pDX, IDC_WBIRTH_REGION  , m_pRSet->m_WBIRTH_REGION  , m_pRSet);
  DDX_FieldText(pDX, IDC_WBIRTH_DISTRICT, m_pRSet->m_WBIRTH_DISTRICT, m_pRSet);
  DDX_FieldText(pDX, IDC_WBIRTH_CITY    , m_pRSet->m_WBIRTH_CITY    , m_pRSet);

  DDX_OleDate(pDX, IDC_MBIRTH_DATE, m_MBirthDate, m_pRSet->m_MBIRTH_DATE);
	DDX_OleDate(pDX, IDC_WBIRTH_DATE, m_WBirthDate, m_pRSet->m_WBIRTH_DATE);
	DDX_MSButton(pDX, IDC_MPASSPORT_TYPE, m_MPassportType, m_pRSet->m_MPASSPORT_TYPE);
	DDX_MSButton(pDX, IDC_WPASSPORT_TYPE, m_WPassportType, m_pRSet->m_WPASSPORT_TYPE);
	DDX_FieldText(pDX, IDC_MPASSPORT_SERIA, m_pRSet->m_MPASSPORT_SERIA, m_pRSet);
  DDX_FieldText(pDX, IDC_WPASSPORT_SERIA, m_pRSet->m_WPASSPORT_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_MPASSPORT_NUMBER, m_pRSet->m_MPASSPORT_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WPASSPORT_NUMBER, m_pRSet->m_WPASSPORT_NUMBER, m_pRSet);
	DDX_OleDate(pDX, IDC_MPASSPORT_DATE, m_MPassportDate, m_pRSet->m_MPASSPORT_DATE);
	DDX_OleDate(pDX, IDC_WPASSPORT_DATE, m_WPassportDate, m_pRSet->m_WPASSPORT_DATE);
	DDX_FieldText(pDX, IDC_MPASSPORT_BY, m_pRSet->m_MPASSPORT_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_WPASSPORT_BY, m_pRSet->m_WPASSPORT_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_COUNTRY, m_pRSet->m_MRP_COUNTRY, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_COUNTRY, m_pRSet->m_WRP_COUNTRY, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_REGION, m_pRSet->m_MRP_REGION, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_REGION, m_pRSet->m_WRP_REGION, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_DISTRICT, m_pRSet->m_MRP_DISTRICT, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_DISTRICT, m_pRSet->m_WRP_DISTRICT, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_CITY, m_pRSet->m_MRP_CITY, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_CITY, m_pRSet->m_WRP_CITY, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_STREET, m_pRSet->m_MRP_STREET, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_STREET, m_pRSet->m_WRP_STREET, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_HOUSE, m_pRSet->m_MRP_HOUSE, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_HOUSE, m_pRSet->m_WRP_HOUSE, m_pRSet);
	DDX_FieldText(pDX, IDC_MRP_FLAT, m_pRSet->m_MRP_FLAT, m_pRSet);
	DDX_FieldText(pDX, IDC_WRP_FLAT, m_pRSet->m_WRP_FLAT, m_pRSet);
	DDX_FieldText(pDX, IDC_MDUTY, m_pRSet->m_MDUTY, m_pRSet);
	DDX_FieldText(pDX, IDC_WDUTY, m_pRSet->m_WDUTY, m_pRSet);
	DDX_FieldText(pDX, IDC_MDUTY2, m_pRSet->m_MDUTY2, m_pRSet);
	DDX_FieldText(pDX, IDC_WDUTY2, m_pRSet->m_WDUTY2, m_pRSet);
	DDX_MSButton(pDX, IDC_MMONEY_TYPE, m_MMoneyType, m_pRSet->m_MMONEY_TYPE);
	DDX_MSButton(pDX, IDC_WMONEY_TYPE, m_WMoneyType, m_pRSet->m_WMONEY_TYPE);
	DDX_FieldText(pDX, IDC_MCHECK_NUMBER, m_pRSet->m_MCHECK_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WCHECK_NUMBER, m_pRSet->m_WCHECK_NUMBER, m_pRSet);
	DDX_OleDate(pDX, IDC_MCHECK_DATE, m_MCheckDate, m_pRSet->m_MCHECK_DATE);
	DDX_OleDate(pDX, IDC_WCHECK_DATE, m_WCheckDate, m_pRSet->m_WCHECK_DATE);
	DDX_FieldText(pDX, IDC_MCHECK_BANK, m_pRSet->m_MCHECK_BANK, m_pRSet);
	DDX_FieldText(pDX, IDC_WCHECK_BANK, m_pRSet->m_WCHECK_BANK, m_pRSet);
	DDX_FieldText(pDX, IDC_MCERTIFICATE_SERIA, m_pRSet->m_MCERTIFICATE_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_WCERTIFICATE_SERIA, m_pRSet->m_WCERTIFICATE_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_MCERTIFICATE_NUMBER, m_pRSet->m_MCERTIFICATE_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WCERTIFICATE_NUMBER, m_pRSet->m_WCERTIFICATE_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_MNOTICE, m_pRSet->m_MNOTICE, m_pRSet);
	DDX_FieldText(pDX, IDC_WNOTICE, m_pRSet->m_WNOTICE, m_pRSet);
/************************************** : by VK at 04.12.2004 5:02:59 **\
  if ( pDX->m_bSaveAndValidate ) {
    if ( m_NUMBER_before_save       != m_pRSet->m_NUMBER       ||
         m_DATEREG_before_save      != m_pRSet->m_DATEREG      ||
         m_MOLD_SURNAME_before_save != m_pRSet->m_MOLD_SURNAME ||
         m_MNEW_SURNAME_before_save != m_pRSet->m_MNEW_SURNAME ||
         m_WOLD_SURNAME_before_save != m_pRSet->m_WOLD_SURNAME ||
         m_WNEW_SURNAME_before_save != m_pRSet->m_WNEW_SURNAME ||
         m_MNAME_before_save        != m_pRSet->m_MNAME        ||
         m_MPATRONYMIC_before_save  != m_pRSet->m_MPATRONYMIC  ||
         m_WNAME_before_save        != m_pRSet->m_WNAME        ||
         m_WPATRONYMIC_before_save  != m_pRSet->m_WPATRONYMIC )
  }
\************************************** : by VK at 04.12.2004 5:03:02 **/
  m_ID = m_pRSet->m_ID;
}

BEGIN_MESSAGE_MAP(CFormDivorce, CEraForm)
	//{{AFX_MSG_MAP(CFormDivorce)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	//ON_BN_CLICKED(IDC_GROUND_TYPE, OnGroundType)
	ON_EN_SETFOCUS(IDC_MNEW_SURNAME, OnSetfocusMNewSurname)
	ON_EN_SETFOCUS(IDC_WOLD_SURNAME, OnSetfocusWOldSurname)
	ON_EN_SETFOCUS(IDC_WNEW_SURNAME, OnSetfocusWNewSurname)
  ON_CBN_SETFOCUS(IDC_GROUND, OnSetfocusGround)
  ON_CBN_SELENDOK(IDC_GROUND, OnSelendokGround)
	ON_EN_SETFOCUS(IDC_GROUND_NUMBER, OnSetfocusGroundNumber)
  ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
  ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce diagnostics

#ifdef _DEBUG
void CFormDivorce::AssertValid() const {
	CDaoRecordView::AssertValid();
}

void CFormDivorce::Dump(CDumpContext& dc) const {
	CDaoRecordView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormDivorce message handlers
CDaoRecordset* CFormDivorce::OnGetRecordset() {
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CRSDivorces(NULL);
	m_pSet->Open();

  m_pRSet->SetCurrentIndex(_T("NUMBER"));
  try {
    if ( FALSE==m_pRSet->IsBOF() && FALSE==m_pRSet->IsEOF() )
      m_pRSet->MoveLast();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }

	return m_pRSet;
}

CRSDivorces* CFormDivorce::GetRecordset() {
	CRSDivorces* pSet = (CRSDivorces*) OnGetRecordset();
	ASSERT(pSet != NULL && pSet->IsKindOf(RUNTIME_CLASS(CRSDivorces)));
	return pSet;
}

#ifndef FREE_LICENCE
BOOL CFormDivorce::IsRDFFieldsDirty() {
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  if ( m_pRSet ) {
    SetChangedBy(m_pRSet, m_pRSet->m_EXTNOTES);
    // MRP_REGION, MRP_DISTRICT, MRP_CITY
    // WRP_REGION, WRP_DISTRICT, WRP_CITY
    if ( m_pRSet->IsFieldDirty(&m_pRSet->m_MRP_REGION)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_MRP_DISTRICT) ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_MRP_CITY) )
      m_GeoFieldsDirtyFlags |= FATHER_GEO_FIELDS_DIRTY;

    if ( m_pRSet->IsFieldDirty(&m_pRSet->m_WRP_REGION)   ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_WRP_DISTRICT) ||
         m_pRSet->IsFieldDirty(&m_pRSet->m_WRP_CITY) )
      m_GeoFieldsDirtyFlags |= MOTHER_GEO_FIELDS_DIRTY;

    return (m_GeoFieldsDirtyFlags != NO_GEO_FIELDS_DIRTY);
  }
  return false;
}
void CFormDivorce::SetRDFFields() {
  if ( m_GeoFieldsDirtyFlags & FATHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_MRP_REGION, m_pRSet->m_MRP_DISTRICT, m_pRSet->m_MRP_CITY, false);
  if ( m_GeoFieldsDirtyFlags & MOTHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_WRP_REGION, m_pRSet->m_WRP_DISTRICT, m_pRSet->m_WRP_CITY, false);
  if ( m_GeoFieldsDirtyFlags )
    SaveGeoValidation();
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
}
#endif // FREE_LICENCE

void CFormDivorce::AddRecordToNavigateBars(CListCtrl* pNameList, CListCtrl* pNumberList) {
  long lID = m_pRSet->m_ID;
  
  CString sMFIO = MakeSNP(m_pRSet->m_MOLD_SURNAME, m_pRSet->m_MNAME, m_pRSet->m_MPATRONYMIC);
  CString sWFIO = MakeSNP(m_pRSet->m_WOLD_SURNAME, m_pRSet->m_WNAME, m_pRSet->m_WPATRONYMIC);
  CString sDate = GetFieldDate(m_pRSet, _T("DATEREG")); // m_DateReg.GetDDMMYYYY();
  CString sNumber;
  CString sMNewFIO;
  CString sWNewFIO;
  sNumber.Format(_T("%d"), m_pRSet->m_NUMBER);

  if ( !IsEmptyText(m_pRSet->m_MNEW_SURNAME) && (m_pRSet->m_MOLD_SURNAME != m_pRSet->m_MNEW_SURNAME) )
    sMNewFIO = MakeSNP(m_pRSet->m_MNEW_SURNAME, m_pRSet->m_MNAME, m_pRSet->m_MPATRONYMIC);

  if ( !IsEmptyText(m_pRSet->m_WNEW_SURNAME) && (m_pRSet->m_WOLD_SURNAME != m_pRSet->m_WNEW_SURNAME) )
    sWNewFIO = MakeSNP(m_pRSet->m_WNEW_SURNAME, m_pRSet->m_WNAME, m_pRSet->m_WPATRONYMIC);

  int nItem;

  nItem = pNameList->GetItemCount();
  nItem = pNameList->InsertItem(nItem, sMFIO);
  pNameList->SetItemText(nItem, 0, sMFIO  );
  pNameList->SetItemText(nItem, 1, sNumber  );
  pNameList->SetItemText(nItem, 2, sDate );
  pNameList->SetItemData(nItem, (DWORD)lID);

  nItem = pNumberList->GetItemCount();
  pNumberList->InsertItem(nItem, sNumber);
  pNumberList->SetItemText(nItem, 0, sNumber );
  pNumberList->SetItemText(nItem, 1, sMFIO );
  pNumberList->SetItemText(nItem, 2, sDate );
  pNumberList->SetItemData(nItem, (DWORD)lID);

  if ( !sMNewFIO.IsEmpty() ) {
    nItem = pNameList->GetItemCount();
    nItem = pNameList->InsertItem(nItem, sMNewFIO);
    pNameList->SetItemText(nItem, 0, sMNewFIO  );
    pNameList->SetItemText(nItem, 1, sNumber  );
    pNameList->SetItemText(nItem, 2, sDate );
    pNameList->SetItemData(nItem, (DWORD)lID);
  }

  nItem = pNameList->GetItemCount();
  nItem = pNameList->InsertItem(nItem, sWFIO);
  pNameList->SetItemText(nItem, 0, sWFIO  );
  pNameList->SetItemText(nItem, 1, sNumber  );
  pNameList->SetItemText(nItem, 2, sDate );
  pNameList->SetItemData(nItem, (DWORD)lID);

  nItem = pNumberList->GetItemCount();
  pNumberList->InsertItem(nItem, sNumber);
  pNumberList->SetItemText(nItem, 0, sNumber );
  pNumberList->SetItemText(nItem, 1, sWFIO );
  pNumberList->SetItemText(nItem, 2, sDate );
  pNumberList->SetItemData(nItem, (DWORD)lID);


  if ( !sWNewFIO.IsEmpty() ) {
    nItem = pNameList->GetItemCount();
    nItem = pNameList->InsertItem(nItem, sWNewFIO);
    pNameList->SetItemText(nItem, 0, sWNewFIO  );
    pNameList->SetItemText(nItem, 1, sNumber  );
    pNameList->SetItemText(nItem, 2, sDate );
    pNameList->SetItemData(nItem, (DWORD)lID);
  }
}

BOOL CFormDivorce::IsNeedSubclassForStaticBG(CWnd* pWnd) {
  switch( pWnd->GetDlgCtrlID() ) {
    case IDC_ACT_LABEL:                 case IDC_LABEL_DATEREG:
    case IDC_LABEL_NUMBER:              case IDC_LABEL_MARRIAGE_BY:
    case IDC_LABEL_MARRIAGE_NUMBER:     case IDC_LABEL_MARRIAGE_DATE:

//    case IDC_MCITIZEN_LABEL:            case IDC_WCITIZEN_LABEL:
    case IDC_LABEL_MOLD_SURNAME:        case IDC_LABEL_WOLD_SURNAME:  
    case IDC_LABEL_MNEW_SURNAME:        case IDC_LABEL_WNEW_SURNAME:
    case IDC_LABEL_MNAME:               case IDC_LABEL_WNAME:
    case IDC_LABEL_MPATRONYMIC:         case IDC_LABEL_WPATRONYMIC:
    case IDC_LABEL_MBIRTH_DATE:         case IDC_LABEL_WBIRTH_DATE:
    case IDC_LABEL_MPASSPORT_SERIA:     case IDC_LABEL_WPASSPORT_SERIA:
    case IDC_LABEL_MPASSPORT_NUMBER:    case IDC_LABEL_WPASSPORT_NUMBER:
    case IDC_LABEL_MPASSPORT_DATE:      case IDC_LABEL_WPASSPORT_DATE:
    case IDC_LABEL_MPASSPORT_BY:        case IDC_LABEL_WPASSPORT_BY:
    case IDC_LABEL_MRP_COUNTRY:         case IDC_LABEL_WRP_COUNTRY:
    case IDC_LABEL_MRP_REGION:          case IDC_LABEL_WRP_REGION:
    case IDC_LABEL_MRP_DISTRICT:        case IDC_LABEL_WRP_DISTRICT:
    case IDC_LABEL_MRP_CITY:            case IDC_LABEL_WRP_CITY:
    case IDC_LABEL_MRP_STREET:          case IDC_LABEL_WRP_STREET:
    case IDC_LABEL_MRP_HOUSE:           case IDC_LABEL_WRP_HOUSE:
    case IDC_LABEL_MRP_FLAT:            case IDC_LABEL_WRP_FLAT:
    case IDC_LABEL_MDUTY:               case IDC_LABEL_WDUTY:
    case IDC_LABEL_MCHECK_NUMBER:       case IDC_LABEL_WCHECK_NUMBER:
    case IDC_LABEL_MCHECK_DATE:         case IDC_LABEL_WCHECK_DATE:
    case IDC_LABEL_MCHECK_BANK:         case IDC_LABEL_WCHECK_BANK:
    case IDC_LABEL_MCERTIFICATE_SERIA:  case IDC_LABEL_WCERTIFICATE_SERIA:
    case IDC_LABEL_MCERTIFICATE_NUMBER: case IDC_LABEL_WCERTIFICATE_NUMBER:
    case IDC_LABEL_GROUND:              case IDC_LABEL_DATE:
    case IDC_LABEL_NKIDS:
    case IDC_STATIC:
    case 0xFFFF:
      return TRUE;
  }
  return FALSE;
}

void CFormDivorce::OnInitialUpdate() {
	BeginWaitCursor();

  ((CMainFrame*)AfxGetMainWnd())->m_pDivorceFrame = GetParentFrame();
  m_nPrinPos = CONTEXT_DIVORCE; // Розірвання шлюбу

	GetRecordset();
	CEraForm::OnInitialUpdate();

	if (m_pRSet->IsOpen()) {
/************************************** : by VK at 26.05.2006 23:17:36 **\
    try {
      if ( FALSE==m_pRSet->IsBOF() && FALSE==m_pRSet->IsEOF() )
        m_pRSet->MoveLast();
      else {
        EnableForm(FALSE);
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError(); // to do logstring
      #endif
      e->Delete();
    }
\************************************** : by VK at 26.05.2006 23:17:40 **/

    CString strTitle = m_pRSet->m_pDatabase->GetName();
    strTitle += _T(" - Розірвання шлюбів");
    CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
    pDoc->SetTitle(strTitle);

    GetDlgItem(IDC_MCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
    GetDlgItem(IDC_WCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);

    m_MCitizenship.SetDefault( g_szDefCitizenship );
    m_WCitizenship.SetDefault( g_szDefCitizenship );

    m_MRPCountry.SetDefault(theIniCache.GetCOUNTRY());
    m_WRPCountry.SetDefault(theIniCache.GetCOUNTRY());
    m_MBirthCountry.SetDefault(theIniCache.GetCOUNTRY());
    m_WBirthCountry.SetDefault(theIniCache.GetCOUNTRY());
    theIniCache.FillBanks();
    for( int i(0); i < theBanks.GetSize(); i++ ) {    
      CString s =theBanks.GetAt(i);
      m_MCheckBank.AddString(s);
      m_WCheckBank.AddString(s);
    }
    OnMove(ID_RECORD_LAST);
    if ( m_pRSet->IsEOF() && m_pRSet->IsBOF() ) {
      EnableForm(FALSE);
    }

	}

	EndWaitCursor();
#ifndef FREE_LICENCE
  if ( FALSE==RegDlg(&m_tooltip) ) {
    AfxGetMainWnd()->PostMessage(WM_QUIT);
  }
#endif // FREE_LICENCE
  EmptyTable();
}

BOOL CFormDivorce::OnMove(UINT nIDMoveCommand) {
  if ( NULL==m_pRSet )
    return FALSE;
  if ( m_pRSet->IsBOF() && m_pRSet->IsEOF() )
    return FALSE;
  BOOL bNewRecord = m_fNewRecord;
  BOOL bRet = CEraForm::OnMove(nIDMoveCommand);

  if ( bRet ) {
    if ( bNewRecord ) {
      SetFocusToFirstControl();
      // m_GroundType.SetIndex(4); !!!
    }

    m_MarriageBy.SetDefault(theIniCache.GetRAGS());
    theRList.FillRegCB(m_MarriageBy, m_pRSet->m_MARRIAGE_BY);

    theCitizenships.FillCombo( m_MCitizenship, m_pRSet->m_MCITIZENSHIP );
    theCitizenships.FillCombo( m_WCitizenship, m_pRSet->m_WCITIZENSHIP );

    theMNames.FillCombo( m_MName, m_pRSet->m_MNAME, false );
    theWNames.FillCombo( m_WName, m_pRSet->m_WNAME, false );
    theMPatronymics.FillCombo( m_MPatronymic, m_pRSet->m_MPATRONYMIC, false );
    theWPatronymics.FillCombo( m_WPatronymic, m_pRSet->m_WPATRONYMIC, false );

    theMIAs.FillCombo( m_MPassportBy, m_pRSet->m_MPASSPORT_BY );
    theMIAs.FillCombo( m_WPassportBy, m_pRSet->m_WPASSPORT_BY );
    m_MPassportBy.SetDefault( theIniCache.GetByROVD() );
    m_WPassportBy.SetDefault( theIniCache.GetByROVD() );

    theGeoCache.FillCountryCB(m_MRPCountry, m_pRSet->m_MRP_COUNTRY);
    theGeoCache.FillCountryCB(m_WRPCountry, m_pRSet->m_WRP_COUNTRY);
    theGeoCache.FillRegionCB(m_MRPRegion, m_MRPCountry, m_pRSet->m_MRP_REGION );
    theGeoCache.FillRegionCB(m_WRPRegion, m_WRPCountry, m_pRSet->m_WRP_REGION );
    theGeoCache.FillDistrictCB(m_MRPDistrict, m_MRPRegion, m_pRSet->m_MRP_DISTRICT);
    theGeoCache.FillDistrictCB(m_WRPDistrict, m_WRPRegion, m_pRSet->m_WRP_DISTRICT);
    theGeoCache.FillCityCB(m_MRPCity, m_MRPRegion, m_MRPDistrict, m_pRSet->m_MRP_CITY);
    theGeoCache.FillCityCB(m_WRPCity, m_WRPRegion, m_WRPDistrict, m_pRSet->m_WRP_CITY);
    theStreets.FillCombo( m_MRPStreet, m_pRSet->m_MRP_STREET );
    theStreets.FillCombo( m_WRPStreet, m_pRSet->m_WRP_STREET );

    theGeoCache.FillCountryCB(m_MBirthCountry, m_pRSet->m_MBIRTH_COUNTRY);
    theGeoCache.FillCountryCB(m_WBirthCountry, m_pRSet->m_WBIRTH_COUNTRY);
    theGeoCache.FillRegionCB(m_MBirthRegion, m_MBirthCountry, m_pRSet->m_MBIRTH_REGION);
    theGeoCache.FillRegionCB(m_WBirthRegion, m_WBirthCountry, m_pRSet->m_WBIRTH_REGION);
    theGeoCache.FillDistrictCB(m_MBirthDistrict, m_MBirthRegion, m_pRSet->m_MBIRTH_DISTRICT);
    theGeoCache.FillDistrictCB(m_WBirthDistrict, m_WBirthRegion, m_pRSet->m_WBIRTH_DISTRICT);
    theGeoCache.FillCityCB(m_MBirthCity, m_MBirthRegion, m_MBirthDistrict, m_pRSet->m_MBIRTH_CITY);
    theGeoCache.FillCityCB(m_WBirthCity, m_WBirthRegion, m_WBirthDistrict, m_pRSet->m_WBIRTH_CITY);

    OnShowHideGroundNumber();
    RefillGroundCombo();

  }
  return bRet;
}

void CFormDivorce::OnSetfocusDatereg() {
	// TODO: Add your control notification handler code here
	SetDefaultDateReg(IDD_FORM_DIVORCE);
}

void CFormDivorce::OnSetfocusNumber() {
  if ( 0==m_pRSet->m_NUMBER && SetDefaultNumber(m_pRSet->m_NUMBER) ) {
    m_pRSet->Edit();
    m_pRSet->Update();
    UpdateData(TRUE);
    m_pRSet->SetBookmark( m_pRSet->GetLastModifiedBookmark() );
    SetBookMarks();
  }
}

CString CFormDivorce::DivReason(int nReason) {
  CString sReason, sWho;
  bool bReplace = false;
  if ( m_MNewSurname.IsEmpty() )
    sWho = MakeFromFullName(MakeFIO(&m_MOldSurname, &m_MName, &m_MPatronymic), true);
  else if ( m_WNewSurname.IsEmpty() )
    sWho = MakeFromFullName(MakeFIO(&m_WOldSurname, &m_WName, &m_WPatronymic), false);
  else
    sWho = MakeFromFullName(MakeFIO(&m_MOldSurname, &m_MName, &m_MPatronymic), true);

  switch(nReason) {
    case 0: // Спільна заява про РШ
      /* закоментировано 05.01.2008
       sReason.Format(_T("Постанова про розірвання шлюбу %s"), SVRagsC(theIniCache.GetRAGS(), RC_RV) );
      */
      sReason = _T("Спільна заява про розірвання шлюбу");
      break;
    case 1:
      sReason.Format(_T("Рішення суду %s про визнання гр. %s безвісно відсутнім."),
                     theIniCache.GetByCourt(), sWho);
      bReplace = true;
      break;
    case 2:
      break;
    case 3:
      sReason.Format(_T("Постанова про розірвання шлюбу %s"), SVRagsC(theIniCache.GetRAGS(), RC_RV) );
      break;
    case 4:
      sReason.Format(_T("Рішення суду %s"), theIniCache.GetByCourt() );
      if ( sReason.Find(_T(" суду"), 12) > 0 ) {
        sReason.Replace(_T("Рішення суду "), _T("Рішення "));
      }
      break;
  }
  if ( bReplace && sReason.Find(_T(" суду "), 12) > 0 ) {
    sReason.Replace(_T("Рішення суду "), _T("Рішення "));
    sReason.Replace(_T("Вирок суду "), _T("Вирок "));
  }

  return sReason;
}

CString CFormDivorce::DecisionCase(int nReason) {
  if ( nReason != 0 ) {
    return _T("");
  }
  COleDateTime odt = m_DateReg.GetDate();
  CString s, sWho;
  bool bReplace = false;

  if ( m_MNewSurname.IsEmpty() )
    sWho = MakeFromFullName(MakeFIO(&m_MOldSurname, &m_MName, &m_MPatronymic), true);
  else if ( m_WNewSurname.IsEmpty() )
    sWho = MakeFromFullName(MakeFIO(&m_WOldSurname, &m_WName, &m_WPatronymic), false);
  else
    sWho = MakeFromFullName(MakeFIO(&m_MOldSurname, &m_MName, &m_MPatronymic), true);

  switch(nReason) {
    case 0:
      odt -= COleDateTimeSpan(30, 0, 0, 0);
      s.Format(_T("Постанова про розірвання шлюбу № %s від %s"),
               GetNumFromStr(m_pRSet, _T("MNOTICE"), _T("про розірвання шлюбу №"), true),
               GetPrevWorkDay(odt) ); 
/* закоментировано 05.01.2008
          s.Format(_T("Спільна заява подружжя № %s від %s"),
                     GetNumFromStr(m_pRSet, _T("MNOTICE"), _T("заява подружжя №"), true),
                     GetPrevWorkDay(odt) ); 
*/
      break;
    case 1:
      odt -= COleDateTimeSpan(30, 0, 0, 0);
      s.Format(_T("Рішення суду %s від %s про визнання гр. %s безвісно відсутнім."),
               theIniCache.GetByCourt(), GetPrevWorkDay(odt), sWho );
      bReplace = true;
      break;
    case 2:
      odt -= COleDateTimeSpan(30, 0, 0, 0);
      s.Format(_T("Рішення суду %s від %s про визнання гр. %s недієздатним у наслідок душевної хвороби чи недоумства."),
               theIniCache.GetByCourt(), GetPrevWorkDay(odt), sWho );
      bReplace = true;
      break;
    case 3:
      odt -= COleDateTimeSpan(30, 0, 0, 0);
      s.Format(_T("Вирок суду %s від %s про засудження гр. %s  до позбавлення волі на строк 3 роки."),
               theIniCache.GetByCourt(), GetPrevWorkDay(odt), sWho );
      break;
  }

  if ( bReplace && s.Find(_T(" суду "), 12) > 0 ) {
    s.Replace(_T("Рішення суду "), _T("Рішення "));
    s.Replace(_T("Вирок суду "), _T("Вирок "));
  }

  return s;
}

void CFormDivorce::OnShowHideGroundNumber() {
  return;
/*
  CRect r, rNew;
  int nShow = SW_HIDE;
  switch( m_GroundType.GetIndex() ) {
    case 0: case 4: // Рішення суду
      nShow = SW_SHOW;
      break;

  }
  GetDlgItem(IDC_LABEL_GROUND)->ShowWindow(nShow);
  GetDlgItem(IDC_GROUND_NUMBER)->ShowWindow(nShow);
  GetDlgItem(IDC_LABEL_DATE)->ShowWindow(nShow);
  GetDlgItem(IDC_GROUND_DATE)->ShowWindow(nShow);
  m_GroundType.GetWindowRect(&r);
  ScreenToClient(&r);
  rNew = r;
  rNew.left = r.right + 4;
  rNew.top  = r.top;
  if ( nShow ) {
    GetDlgItem(IDC_LABEL_GROUND)->GetWindowRect(&r);
    ScreenToClient(&r);
    rNew.right = r.left - 4;
  }
  else {
    GetDlgItem(IDC_GROUND_DATE)->GetWindowRect(&r);
    ScreenToClient(&r);
    rNew.right = r.right;
  }
  m_Ground.MoveWindow(&rNew);
*/
}

void CFormDivorce::OnBeforeGroundType() {
/*
  int nGroundIndex = m_GroundType.GetIndex();
  CString s = DecisionCase(nGroundIndex);
  CString sNotice;
  m_MNotice.GetWindowText(sNotice);
  sNotice.Replace(s, _T(""));
  m_MNotice.SetWindowText(sNotice);
*/
}
/************************************** : by VK 1/9/2008 at 3:20:14 PM **\
void CFormDivorce::OnGroundType() {
	// TODO: Add your control notification handler code here
  int nGroundIndex = m_GroundType.GetIndex();
	m_Ground.SetWindowText( DivReason(nGroundIndex) );
  CString sMemo;
  m_MNotice.GetWindowText(sMemo);
  sMemo = Trim(sMemo);
  sMemo += _T(" ");
  sMemo += DecisionCase(nGroundIndex);
  sMemo = Trim(sMemo);
  m_MNotice.SetWindowText(sMemo);
  OnShowHideGroundNumber();
}
\************************************** : by VK 1/9/2008 at 3:20:18 PM **/

void CFormDivorce::OnSetfocusMNewSurname() {
	if ( m_MNewSurname.IsEmpty() ) {
    m_MNewSurname.SetWindowText( m_MOldSurname.GetText() );
    m_MNewSurname.SetSel(0, -1);
	}
}

void CFormDivorce::OnSetfocusWOldSurname() {
	if ( m_WOldSurname.IsEmpty() ) {
    m_WOldSurname.SetWindowText( OfferSurname(m_MOldSurname.GetText(), TRUE, FALSE) );
    m_WOldSurname.SetSel(0, -1);
  }
}

void CFormDivorce::OnSetfocusWNewSurname() {
	if ( m_WNewSurname.IsEmpty() ) {
    m_WNewSurname.SetWindowText( m_WOldSurname.GetText() );
    m_WNewSurname.SetSel(0, -1);
  }
}

void CFormDivorce::OnBlank(const CString& szTemplate, const CString& szOut) {
  if ( RTF_DivorceBlank(szTemplate, szOut, m_pRSet) ) {
    OnRTFShell(szOut);
  }
}

void CFormDivorce::OnPrint(UINT nPrintID) {
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

  if ( FALSE==CEraForm::OnMove(0) )  // Save data
    return;
  CString sTemplate, sOut;

  g_nDocType = DOCTYPE_OTHER;

  switch ( nPrintID ) {
    case ID_PRINT_DIVORCE_ACT:
      g_nDocType = DOCTYPE_ACT;
      sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("Act") );
      sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("Act"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_DIVORCE_CERIFICATE1:
    case ID_PRINT_DIVORCE_CERIFICATE2: {
        g_nDocType = DOCTYPE_CERT;
        BOOL fSex = (ID_PRINT_DIVORCE_CERIFICATE1==nPrintID);
        CSVDlg dlg(this, IDD_SVIDDIV, fSex );
        dlg.m_szFormSect = _T("DIVORCE_FORM");
        dlg.m_sMSurname = m_MOldSurname.GetText();
        dlg.m_sWSurname = m_WOldSurname.GetText();
        dlg.m_sMName = m_MName.GetCurText();
        dlg.m_sWName = m_WName.GetCurText();
        dlg.m_sMPatronymic = m_MPatronymic.GetCurText();
        dlg.m_sWPatronymic = m_WPatronymic.GetCurText();
        dlg.m_sNewName = fSex ? m_MNewSurname.GetText() : m_WNewSurname.GetText();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("Certificate") );
          sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("Certificate"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DIVORCE_16:
      g_sMSurname_OV    = ManSurname_OV(m_MOldSurname.GetText());
      g_sMName_OV       = ManName_OV(m_MName.GetCurText());
      g_sMPatronymic_OV = ManFather_OV(m_MPatronymic.GetCurText());
      g_sWSurname_OV    = WomanSurname_OV(m_WOldSurname.GetText());
      g_sWName_OV       = WomanName_OV(m_WName.GetCurText());
      g_sWPatronymic_OV = WomanFather_OV(m_WPatronymic.GetCurText());
      sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("16") );
      sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("16"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_DIVORCE_21:
      g_sMSurname_OV    = ManSurname_OV(m_MOldSurname.GetText());
      g_sMName_OV       = ManName_OV(m_MName.GetCurText());
      g_sMPatronymic_OV = ManFather_OV(m_MPatronymic.GetCurText());
      g_sWSurname_OV    = WomanSurname_OV(m_WOldSurname.GetText());
      g_sWName_OV       = WomanName_OV(m_WName.GetCurText());
      g_sWPatronymic_OV = WomanFather_OV(m_WPatronymic.GetCurText());
      sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("21") );
      sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("21"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_DIVORCE_18_1:
    case ID_PRINT_DIVORCE_18_2: {
        BOOL fSex = (ID_PRINT_DIVORCE_18_1==nPrintID);
        CDiv18 dlg(this, fSex);
        dlg.m_sToRags     = m_MarriageBy.GetCurText();
        dlg.m_sSurname    = fSex ? m_MOldSurname.GetText()    : m_WOldSurname.GetText();
        dlg.m_sName       = fSex ? m_MName.GetCurText()       : m_WName.GetCurText();
        dlg.m_sPatronymic = fSex ? m_MPatronymic.GetCurText() : m_WPatronymic.GetCurText();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("18") );
          sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("18"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DIVORCE_23: {
        CDiv23 dlg(this);
        dlg.m_sToRags      = m_MarriageBy.GetCurText();
        dlg.m_sMSurname    = m_MOldSurname.GetText();
        dlg.m_sMName       = m_MName.GetCurText();
        dlg.m_sWSurname    = m_WOldSurname.GetText();
        dlg.m_sWName       = m_WName.GetCurText();
        dlg.m_sMPatronymic = m_MPatronymic.GetCurText();
        dlg.m_sWPatronymic = m_WPatronymic.GetCurText();
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("23") );
          sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("23"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_DIVORCE_ABC: {
        CABCDlg dlg(false, this);
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_DIVORCE_IN, theApp.m_sTemplatePath, _T("ABC") );
          sOut.Format(IDS_DIVORCE_OUT, theApp.m_sOutPath, _T("ABC") );
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
    case ID_PRINT_DIVORCE_15_5_25 :  case ID_PRINT_DIVORCE_16_5_2  :
    case ID_PRINT_DIVORCE_17_5_4  :  case ID_PRINT_DIVORCE_19_5_12 :
    case ID_PRINT_DIVORCE_20_5_19 :  case ID_PRINT_DIVORCE_21_5_19 :
    case ID_PRINT_DIVORCE_22_5_20 :  case ID_PRINT_DIVORCE_23_5_22 :
    case ID_PRINT_DIVORCE_24_5_22 :  case ID_PRINT_DIVORCE_34_7_1  :
    case ID_PRINT_DIVORCE_39_7_8  :  case ID_PRINT_DIVORCE_40_7_8  :
    case ID_PRINT_DIVORCE_47_7_8  :  case ID_PRINT_DIVORCE_51_7_8  :
    case ID_PRINT_DIVORCE_52_7_8  :  case ID_PRINT_DIVORCE_53_7_8  :
    case ID_PRINT_DIVORCE_54_7_8  :
      OnBlankItem();
      break;
  }

  if ( sTemplate.IsEmpty() )
    return;

  switch ( nPrintID ) {
    case ID_PRINT_DIVORCE_ABC:
      if ( FALSE==RTF_ABCDivorce(sTemplate, sOut, m_pRSet) )
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

CString CFormDivorce::GetForUnknown(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale) {
  CString sRet;
  if ( newSN.IsEmpty() ) {
    CString sWho;
    sWho = MakeFromFullName(MakeFIO(&oldSN, &Name, &Patronymic), fMale);
    sRet.Format(_T("Рішення суду %s про визнання гр. %s безвісно відсутн%s."),
                theIniCache.GetByCourt(), sWho, fMale ? _T("ім") : _T("ьою"));
    if ( sRet.Find(_T(" суду "), 12) > 0 ) {
      sRet.Replace(_T("Рішення суду "), _T("Рішення "));
    }
  }
  return sRet;
}
CString CFormDivorce::GetForIncapable(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale) {
  CString sRet;
  if ( newSN.IsEmpty() ) {
    CString sWho;
    sWho = MakeFromFullName(MakeFIO(&oldSN, &Name, &Patronymic), fMale);
    sRet.Format(_T("Рішення суду %s про визнання гр. %s недієздатн%s у наслідок душевної хвороби чи недоумства."),
                theIniCache.GetByCourt(), sWho, fMale ? _T("им") : _T("ьою"));
    if ( sRet.Find(_T(" суду "), 12) > 0 ) {
      sRet.Replace(_T("Рішення суду "), _T("Рішення "));
    }
  }
  return sRet;
}
CString CFormDivorce::GetForDeprivationOfLiberty(CEraNameEdit& newSN, CEraNameEdit& oldSN, CEraNameComboBox& Name, CEraNameComboBox& Patronymic, bool fMale) {
  CString sRet;
  if ( newSN.IsEmpty() ) {
    CString sWho;
    sWho = MakeFromFullName(MakeFIO(&oldSN, &Name, &Patronymic), fMale);
    sRet.Format(_T("Вирок суду %s про засудження гр. %s до позбавлення волі на строк 3 роки."),
                theIniCache.GetByCourt(), sWho);
    if ( sRet.Find(_T(" суду "), 12) > 0 ) {
      sRet.Replace(_T("Вирок суду "), _T("Вирок "));
    }
  }
  return sRet;
}
void CFormDivorce::RefillGroundCombo() {
  CString sz;
  CStringArray szArray;

  sz.Format(_T("Рішення суду %s"), theIniCache.GetByCourt());
  if ( sz.Find(_T(" суду "), 12) > 0 ) {
    sz.Replace(_T("Рішення суду "), _T("Рішення "));
  }
  szArray.Add(sz);

  szArray.Add(_T("Спільна заява подружжя про розірвання шлюбу"));
  szArray.Add(_T("Спільна заява про розірвання шлюбу"));

  sz = GetForUnknown(m_MNewSurname, m_MOldSurname, m_MName, m_MPatronymic, true);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }
  sz = GetForUnknown(m_WNewSurname, m_WOldSurname, m_WName, m_WPatronymic, false);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }

  sz = GetForIncapable(m_MNewSurname, m_MOldSurname, m_MName, m_MPatronymic, true);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }
  sz = GetForIncapable(m_WNewSurname, m_WOldSurname, m_WName, m_WPatronymic, false);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }

  sz = GetForDeprivationOfLiberty(m_MNewSurname, m_MOldSurname, m_MName, m_MPatronymic, true);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }
  sz = GetForDeprivationOfLiberty(m_WNewSurname, m_WOldSurname, m_WName, m_WPatronymic, false);
  if ( false==sz.IsEmpty() ) { szArray.Add(sz); }

  sz = Trim(m_pRSet->m_GROUND);
  int nDefIndex = -1;
  if ( false==sz.IsEmpty() ) {
    nDefIndex = szArray.Add(sz);
  }
  m_Ground.ResetContent();
  for( int i(0); i < szArray.GetSize(); i++ ) {
    m_Ground.AddString( szArray.GetAt(i) );
  }
  if ( nDefIndex != -1 ) {
    m_Ground.SetCurSel(nDefIndex);
  }

}
void CFormDivorce::OnKillFocusPatronymic(CEraNameEdit& wndNewSurname, CEraMoneyEdit& wndDuty) {
  RefillGroundCombo();
  if ( wndNewSurname.IsEmpty() )
    wndDuty.SetFocus();
}

void CFormDivorce::OnKillfocusDuty(CEraNameEdit& wndNewSurname, CWnd& where) {
  if ( wndNewSurname.IsEmpty() ) {
    where.SetFocus();
  }
}


void CFormDivorce::OnSetfocusCertificateSeria(CEraSeriaEdit& wndCertificateSeria) {
	if ( wndCertificateSeria.IsEmpty() ) {
    wndCertificateSeria.SetWindowText( theIniCache.GetDIVORCE_Seria() );
    wndCertificateSeria.SetSel(0, -1);
  }
}

void CFormDivorce::OnSetfocusCertificateNumber(CEraSeriaEdit& wndCertificateSeria, CEraEdit& wndCertificateNumber) {
  if ( wndCertificateNumber.IsEmpty() && !wndCertificateSeria.IsEmpty() ) {
    CString s = theIniCache.GetDIVORCE_CNum();
    int nLen = s.GetLength();
    wndCertificateNumber.SetWindowText( s );
    wndCertificateNumber.SetSel(nLen, nLen);
  }
}

void CFormDivorce::OnChangeCertificateNumber(CEraEdit& wndCertificateNumber) {
  theIniCache.SetDIVORCE_CNum( &wndCertificateNumber );	
}

void CFormDivorce::OnSetfocusGround() {
  CString s = Trim(m_Ground.GetCurText());
  if ( s.IsEmpty() && m_Ground.GetCount()>0 ) {
    m_Ground.SetCurSel(0);
  }
}
void CFormDivorce::OnSelendokGround() {
  CString s, sNotice, sOld;
  int nIndex = m_Ground.GetCurSel();
  if ( CB_ERR != nIndex ) {
    m_MNotice.GetWindowText(sNotice);
    sOld = GetSentence(sNotice, _T("Постанова про розірвання шлюбу"), _T("р."));
    m_Ground.GetLBText(nIndex, s);
    if ( s.Find(_T("Спільна заява")) >= 0 ) {
      COleDateTime odt = m_DateReg.GetDate();
      odt -= COleDateTimeSpan(30, 0, 0, 0);
      if ( sOld.IsEmpty() ) {
        CString sMem;
        sMem.Format(_T("Постанова про розірвання шлюбу № %s від %s"),
                    GetNumFromStr(m_pRSet, _T("MNOTICE"), _T("про розірвання шлюбу №"), true),
                    GetPrevWorkDay(odt) ); 
        sNotice.Insert(0, sMem);
        m_MNotice.SetWindowText(sNotice);
      }
    }
    else {
      if ( false==sOld.IsEmpty() ) {
        sNotice = FindAndReplace(sNotice, sOld, _T(""), true);
        m_MNotice.SetWindowText(sNotice);
      }
    }
  }
}
void CFormDivorce::OnSetfocusGroundNumber() {
	if ( m_GroundNumber.IsEmpty() ) {
  	CString s = GetNumFromStr(m_pRSet, _T("GROUND_NUMBER"), NULL, true );
    m_GroundNumber.SetWindowText(s);
  }
}

LRESULT CFormDivorce::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam) {
  LPCTSTR szMessage = (LPCTSTR)wParam;
  if ( stricmp(szMessage, "close")==0 ) {
    m_fEnableRelayEvent = true;
  }
  m_tooltip.HideTooltip();

  return TRUE;
}

BOOL CFormDivorce::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  BOOL bResult(FALSE);
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
  CWnd* pControl = CWnd::FromHandle((HWND)lParam);

  switch(wNotifyCode) {
    case BN_SETFOCUS:
    case EN_SETFOCUS:
    case CBN_SETFOCUS:
      ScrollToControl(pControl);
      m_pFocused = pControl;
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

  switch (wCtrlId) {
    case IDC_DATEREG:
      if ( EN_KILLFOCUS==wNotifyCode ){
        if ( IsFocusChild(this) ) {
          m_tooltip.HideTooltip();
          if ( FALSE==CheckDateReg(this, &m_DateReg, m_fNewRecord) ) {
            m_DateReg.SetFocus();
            return FALSE;
          }
        }
      }
      break;
/************************************** : by VK 1/9/2008 at 3:20:41 PM **\
    case IDC_GROUND_TYPE:
      if ( BN_CLICKED==wNotifyCode ) {
        OnBeforeGroundType();
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnGroundType();
        return bResult;
      }
      else if ( BN_SETFOCUS==wNotifyCode && m_Ground.IsEmpty() )
        OnGroundType();
      break;
\************************************** : by VK 1/9/2008 at 3:20:44 PM **/
    case IDC_GROUND:
      //if ( CBN_SETFOCUS==wNotifyCode ) {
      //  OnSetfocusGround();
      //}
      //else if ( CBN_SELENDOK==wNotifyCode ) {
      //  OnSelendokGround();
      //}
      break;
    case IDC_MARRIAGE_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MarriageDate, _T("реєстрації шлюбу"), &m_DateReg, _T("реєстрації розірвання шлюбу"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_MBIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MBirthDate, _T("народження"), &m_MarriageDate, _T("реєстрації шлюбу"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_MPASSPORT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MBirthDate, _T("народження"), &m_MPassportDate, _T("видачі паспорту"), FALSE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_WBIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_WBirthDate, _T("народження"), &m_MarriageDate, _T("реєстрації шлюбу"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_WPASSPORT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_WBirthDate, _T("народження"), &m_WPassportDate, _T("видачі паспорту"), FALSE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_GROUND_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_GroundDate, _T("заяви, постанови або рішення суду"), &m_DateReg, _T("реєстрації розірвання шлюбу"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;

    case IDC_MARRIAGE_BY:   if ( CBN_SETFOCUS==wNotifyCode ) m_MarriageBy.UpdateByDefault();
      break;
    case IDC_MPATRONYMIC:   if ( CBN_KILLFOCUS==wNotifyCode ) OnKillFocusPatronymic(m_MNewSurname, m_MDuty);
      break;
    case IDC_WPATRONYMIC:   if ( CBN_KILLFOCUS==wNotifyCode ) OnKillFocusPatronymic(m_WNewSurname, m_WDuty);
      break;
    case IDC_MDUTY:         if ( EN_KILLFOCUS==wNotifyCode ) OnKillfocusDuty(m_MNewSurname, m_WOldSurname);
      break;
    //case IDC_WDUTY:         if ( EN_KILLFOCUS==wNotifyCode ) OnKillfocusDuty(m_WNewSurname, m_GroundType);
      break;
    case IDC_MRP_COUNTRY:   if ( CBN_SETFOCUS==wNotifyCode ) m_MRPCountry.UpdateByDefault();
      break;
    case IDC_WRP_COUNTRY:   if ( CBN_SETFOCUS==wNotifyCode ) m_WRPCountry.UpdateByDefault();
      break;
    case IDC_MRP_REGION:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_MRPCountry, m_MRPRegion, m_MRPCity);
      break;
    case IDC_WRP_REGION:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_WRPCountry, m_WRPRegion, m_WRPCity);
      break;
    case IDC_MRP_DISTRICT:  if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_MRPRegion, m_MRPDistrict);
      break;
    case IDC_WRP_DISTRICT:  if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_WRPRegion, m_WRPDistrict);
      break;
    case IDC_MRP_CITY:      if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_MRPCountry, m_MRPRegion, m_MRPDistrict, m_MRPCity);
      break;
    case IDC_WRP_CITY:      if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_WRPCountry, m_WRPRegion, m_WRPDistrict, m_WRPCity);
      break;
    case IDC_MBIRTH_COUNTRY: if ( CBN_SETFOCUS==wNotifyCode ) m_MBirthCountry.UpdateByDefault();
      break;
    case IDC_WBIRTH_COUNTRY: if ( CBN_SETFOCUS==wNotifyCode ) m_WBirthCountry.UpdateByDefault();
      break;
    case IDC_MBIRTH_REGION:  if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_MBirthCountry, m_MBirthRegion, m_MBirthCity);
      break;
    case IDC_WBIRTH_REGION:  if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_WBirthCountry, m_WBirthRegion, m_WBirthCity);
      break;
    case IDC_MBIRTH_DISTRICT:if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_MBirthRegion, m_MBirthDistrict);
      break;
    case IDC_WBIRTH_DISTRICT:if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_WBirthRegion, m_WBirthDistrict);
      break;
    case IDC_MBIRTH_CITY:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_MBirthCountry, m_MBirthRegion, m_MBirthDistrict, m_MBirthCity);
      break;
    case IDC_WBIRTH_CITY:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_WBirthCountry, m_WBirthRegion, m_WBirthDistrict, m_WBirthCity);
      break;
    case IDC_MCITIZENSHIP:  if ( CBN_SETFOCUS==wNotifyCode ) m_MCitizenship.UpdateByDefault();
      break;
    case IDC_WCITIZENSHIP:  if ( CBN_SETFOCUS==wNotifyCode ) m_WCitizenship.UpdateByDefault();
      break;

    case IDC_MPASSPORT_BY:  if ( CBN_SETFOCUS==wNotifyCode ) m_MPassportBy.UpdateByDefault();
      break;
    case IDC_WPASSPORT_BY:  if ( CBN_SETFOCUS==wNotifyCode ) m_WPassportBy.UpdateByDefault();
      break;

    case IDC_MCERTIFICATE_SERIA:  if ( EN_SETFOCUS==wNotifyCode ) OnSetfocusCertificateSeria(m_MCertificateSeria);
      break;
    case IDC_WCERTIFICATE_SERIA:  if ( EN_SETFOCUS==wNotifyCode ) OnSetfocusCertificateSeria(m_WCertificateSeria);
      break;
    case IDC_MCERTIFICATE_NUMBER:
      if ( EN_SETFOCUS==wNotifyCode )     OnSetfocusCertificateNumber(m_MCertificateSeria, m_MCertificateNumber);
      else if  ( EN_CHANGE==wNotifyCode ) OnChangeCertificateNumber(m_MCertificateNumber);
      break;
    case IDC_WCERTIFICATE_NUMBER:
      if ( EN_SETFOCUS==wNotifyCode )     OnSetfocusCertificateNumber(m_WCertificateSeria, m_WCertificateNumber);
      else if  ( EN_CHANGE==wNotifyCode ) OnChangeCertificateNumber(m_WCertificateNumber);
      break;
  }
  bResult = CEraForm::OnCommand(wParam, lParam);
  m_LastCtrlId = wCtrlId;
	return bResult;
}


void CFormDivorce::OnRecordNew() {
  CEraForm::OnRecordNew();
}
void CFormDivorce::OnRecordDelete() {
  CEraForm::OnRecordDelete();
}

void CFormDivorce::OnContextMenu(CWnd* pWnd, CPoint point) {
  UINT nPos = CONTEXT_DIVORCE;
  CString s, sMemo;
  CEraNoticeEdit* pNotice = (CEraNoticeEdit*)pWnd;
  if ( pNotice==&m_MNotice ) {
    m_MNotice.GetWindowText(sMemo);
    s = ContextMenu(m_MNotice.m_hWnd, nPos, true, m_DateReg.GetDate(), sMemo, false, &m_MBirthDate.GetDate(), NULL);
    if ( s != sMemo )
      m_MNotice.SetWindowText(s);
  }
  else if ( pNotice==&m_WNotice ) {
    m_WNotice.GetWindowText(sMemo);
    s = ContextMenu(m_WNotice.m_hWnd, nPos, false, m_DateReg.GetDate(), sMemo, false, &m_WBirthDate.GetDate(), NULL);
    if ( s != sMemo )
      m_WNotice.SetWindowText(s);
  }
}

void CFormDivorce::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
	// TODO: Add your message handler code here and/or call default
  switch( nIDCtl ) {
    case IDC_MCITIZEN_LABEL:
      DrawLabel(this, nIDCtl, lpDIS, 0xFFFFFF, g_clrMaleForeColor, TRUE, FALSE);
      return;
    case IDC_WCITIZEN_LABEL:
      DrawLabel(this, nIDCtl, lpDIS, 0xFFFFFF, g_clrFemaleForeColor, TRUE, FALSE);
      return;
  }
	CEraForm::OnDrawItem(nIDCtl, lpDIS);
}

