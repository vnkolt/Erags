// FormMarriage.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "..\Common\MDB.h"

#include "Caches.h"
#include "CheckDateDlg.h"
#include "Defaults.h"
#include "Geography.h"
#include "FormMarriage.h"
#include "ElectDlg.h"
#include "EragsDoc.h"
#include "ExtNotice.h"

#include "HelpMan.h"
#include "MainFrm.h"

#include "ABCDlg.h"
#include "Dlg38.h"
#include "Menu.h"
#include "RList.h"
#include "RTFCnv.h"
#include "SVDlg.h"
#include "xMachine.h"

#include "RegDlg.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString g_szSaveMVerdict, g_szSaveWVerdict;

extern COLORREF g_clrLeft;
extern COLORREF g_clrRight;
extern BOOL     g_fUseGradient;
BOOL ConvertForElect(const CString& sTemplate, const CString& sOutName, CPtrArray& array);
BOOL RegDlg(CPPToolTip* pTooltip);
/////////////////////////////////////////////////////////////////////////////
// CFormMarriage

IMPLEMENT_DYNCREATE(CFormMarriage, CEraForm)

CFormMarriage::CFormMarriage()
            	:CEraForm( CFormMarriage::IDD ), m_pRSet((CRSMarriages*&)m_pSet) {
	//{{AFX_DATA_INIT(CFormMarriage)
	//}}AFX_DATA_INIT
  m_MFamily_Status.AddColorState( 0, g_clrMaleForeColor,    _T("У шлюбі не перебував") );
  m_MFamily_Status.AddColorState( 1, g_clrMaleForeColor,    _T("Розлучений, актовий запис про розірвання шлюбу") );
  m_MFamily_Status.AddColorState( 2, g_clrMaleForeColor,    _T("Вдівець, актовий запис про смерть") );
  m_MFamily_Status.AddColorState( 3, g_clrMaleForeColor,    _T("Розлучений за рішенням суду") );

  m_WFamily_Status.AddColorState( 0, g_clrFemaleForeColor,  _T("У шлюбі не перебувала") );
  m_WFamily_Status.AddColorState( 1, g_clrFemaleForeColor,  _T("Розлучена, актовий запис про розірвання шлюбу") );
  m_WFamily_Status.AddColorState( 2, g_clrFemaleForeColor,  _T("Вдова, актовий запис про смерть") );
  m_WFamily_Status.AddColorState( 3, g_clrFemaleForeColor,  _T("Розлучена за рішенням суду") );

  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  m_szFormName = _T("FORM_MARRIAGE");
}

CFormMarriage::~CFormMarriage() {
  if ( m_pSet ) {
    if( m_pSet->IsOpen() )
      m_pSet->Close();
    delete m_pSet;
    m_pSet = NULL;
  }
}

void CFormMarriage::SetFocusToFirstControl() {
  if ( m_DateReg.GetSafeHwnd() ) {
    m_DateReg.SetFocus();
    OnSetfocusDatereg();
  }
}

void CFormMarriage::SetScaleFlags(CWnd* pWnd, WORD& wFlags) {
  switch(pWnd->GetDlgCtrlID()) {
    case IDC_MCITIZEN_LABEL:    case IDC_WCITIZEN_LABEL:
    case IDC_MNACT_LABEL:       case IDC_WNACT_LABEL:
    case IDC_MDATE_LABEL:       case IDC_WDATE_LABEL:
    case IDC_MBY_LABEL:         case IDC_WBY_LABEL:
      wFlags = SCALE_WIDTH;
      break;
    default:
      CDaoRecordViewBG::SetScaleFlags(pWnd, wFlags);
  }
}

void CFormMarriage::DoDataExchange(CDataExchange* pDX) {
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
	//{{AFX_DATA_MAP(CFormMarriage)
	DDX_Control(pDX, IDC_NUMBER, m_Number);
//	DDX_Control(pDX, IDC_DATEREG, m_DateReg);
//	DDX_Control(pDX, IDC_MCITIZEN_LABEL, m_MCitizenLabel);
	DDX_Control(pDX, IDC_MCITIZENSHIP, m_MCitizenship);
	DDX_Control(pDX, IDC_WCITIZENSHIP, m_WCitizenship);
//	DDX_Control(pDX, IDC_WCITIZEN_LABEL, m_WCitizenLabel);
	DDX_Control(pDX, IDC_MOLD_SURNAME, m_MOldSurname);
	DDX_Control(pDX, IDC_WOLD_SURNAME, m_WOldSurname);
	DDX_Control(pDX, IDC_MNEW_SURNAME, m_MNewSurname);
	DDX_Control(pDX, IDC_WNEW_SURNAME, m_WNewSurname);
	DDX_Control(pDX, IDC_MNAME, m_MName);
	DDX_Control(pDX, IDC_MPATRONYMIC, m_MPatronymic);
	DDX_Control(pDX, IDC_WNAME, m_WName);
	DDX_Control(pDX, IDC_WPATRONYMIC, m_WPatronymic);
//	DDX_Control(pDX, IDC_MBIRTH_DATE, m_MBirthDate);
//	DDX_Control(pDX, IDC_WBIRTH_DATE, m_WBirthDate);
	DDX_Control(pDX, IDC_MBIRTH_COUNTRY, m_MBirth_Country);
	DDX_Control(pDX, IDC_WBIRTH_COUNTRY, m_WBirth_Country);
	DDX_Control(pDX, IDC_MBIRTH_REGION, m_MBirth_Region);
	DDX_Control(pDX, IDC_WBIRTH_REGION, m_WBirth_Region);
	DDX_Control(pDX, IDC_MBIRTH_DISTRICT, m_MBirth_District);
	DDX_Control(pDX, IDC_WBIRTH_DISTRICT, m_WBirth_District);
	DDX_Control(pDX, IDC_MBIRTH_CITY, m_MBirth_City);
	DDX_Control(pDX, IDC_WBIRTH_CITY, m_WBirth_City);
	DDX_Control(pDX, IDC_MRP_COUNTRY, m_MRP_Country);
	DDX_Control(pDX, IDC_WRP_COUNTRY, m_WRP_Country);
	DDX_Control(pDX, IDC_MRP_REGION, m_MRP_Region);
	DDX_Control(pDX, IDC_WRP_REGION, m_WRP_Region);
	DDX_Control(pDX, IDC_MRP_DISTRICT, m_MRP_District);
	DDX_Control(pDX, IDC_WRP_DISTRICT, m_WRP_District);
	DDX_Control(pDX, IDC_MRP_CITY, m_MRP_City);
	DDX_Control(pDX, IDC_WRP_CITY, m_WRP_City);
	DDX_Control(pDX, IDC_MRP_STREET, m_MRP_Street);
	DDX_Control(pDX, IDC_WRP_STREET, m_WRP_Street);
	DDX_Control(pDX, IDC_MRP_HOUSE, m_MRP_House);
	DDX_Control(pDX, IDC_WRP_HOUSE, m_WRP_House);
	DDX_Control(pDX, IDC_MRP_FLAT, m_MRP_Flat);
	DDX_Control(pDX, IDC_WRP_FLAT, m_WRP_Flat);
	DDX_Control(pDX, IDC_MPASSPORT_TYPE, m_MPassport_Type);
	DDX_Control(pDX, IDC_WPASSPORT_TYPE, m_WPassport_Type);
	DDX_Control(pDX, IDC_MPASSPORT_SERIA, m_MPassport_Seria);
	DDX_Control(pDX, IDC_WPASSPORT_SERIA, m_WPassport_Seria);
	DDX_Control(pDX, IDC_MPASSPORT_NUMBER, m_MPassport_Number);
	DDX_Control(pDX, IDC_WPASSPORT_NUMBER, m_WPassport_Number);
//	DDX_Control(pDX, IDC_MPASSPORT_DATE, m_MPassportDate);
//	DDX_Control(pDX, IDC_WPASSPORT_DATE, m_WPassportDate);
	DDX_Control(pDX, IDC_MPASSPORT_BY, m_MPassport_By);
	DDX_Control(pDX, IDC_WPASSPORT_BY, m_WPassport_By);
	DDX_Control(pDX, IDC_MFAMILY_STATUS, m_MFamily_Status);
	DDX_Control(pDX, IDC_WFAMILY_STATUS, m_WFamily_Status);
	DDX_Control(pDX, IDC_MACT_NUMBER, m_MAct_Number);
	DDX_Control(pDX, IDC_WACT_NUMBER, m_WAct_Number);
//	DDX_Control(pDX, IDC_MACT_DATE, m_MActDate);
//	DDX_Control(pDX, IDC_WACT_DATE, m_WActDate);
	DDX_Control(pDX, IDC_MACT_BY, m_MAct_By);
	DDX_Control(pDX, IDC_WACT_BY, m_WAct_By);
	DDX_Control(pDX, IDC_CERTIFICATE_SERIA, m_Certificate_Seria);
	DDX_Control(pDX, IDC_CERTIFICATE_NUMBER, m_Certificate_Number);
  DDX_Control(pDX, IDC_NOTICE, m_Notice);
	DDX_Control(pDX, IDC_MNOTICE, m_MNotice);
  DDX_Control(pDX, IDC_WNOTICE, m_WNotice);
  DDX_Control(pDX, IDC_MNACT_LABEL, m_MActLabel);
  DDX_Control(pDX, IDC_WNACT_LABEL, m_WActLabel);
  DDX_Control(pDX, IDC_MDATE_LABEL, m_MDateLabel);
  DDX_Control(pDX, IDC_WDATE_LABEL, m_WDateLabel);
  DDX_Control(pDX, IDC_MBY_LABEL, m_MByLabel);
  DDX_Control(pDX, IDC_WBY_LABEL, m_WByLabel);
	//}}AFX_DATA_MAP
  DDX_OleDate(pDX, IDC_DATEREG, m_DateReg, m_pRSet->m_DATEREG);
  DDX_FieldText(pDX, IDC_NUMBER, m_pRSet->m_NUMBER, m_pRSet);
  DDX_MSButton(pDX, IDC_MFAMILY_STATUS, m_MFamily_Status, m_pRSet->m_MFAMILY_STATUS);
  DDX_MSButton(pDX, IDC_WFAMILY_STATUS, m_WFamily_Status, m_pRSet->m_WFAMILY_STATUS);
  DDX_FieldText(pDX, IDC_MCITIZENSHIP, m_pRSet->m_MCITIZENSHIP, m_pRSet);
  DDX_FieldText(pDX, IDC_WCITIZENSHIP, m_pRSet->m_WCITIZENSHIP, m_pRSet);
	DDX_FieldText(pDX, IDC_MOLD_SURNAME, m_pRSet->m_MOLD_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WOLD_SURNAME, m_pRSet->m_WOLD_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MNEW_SURNAME, m_pRSet->m_MNEW_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WNEW_SURNAME, m_pRSet->m_WNEW_SURNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MNAME, m_pRSet->m_MNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_MPATRONYMIC, m_pRSet->m_MPATRONYMIC, m_pRSet);
	DDX_FieldText(pDX, IDC_WNAME, m_pRSet->m_WNAME, m_pRSet);
	DDX_FieldText(pDX, IDC_WPATRONYMIC, m_pRSet->m_WPATRONYMIC, m_pRSet);
	DDX_OleDate(pDX, IDC_MBIRTH_DATE, m_MBirthDate, m_pRSet->m_MBIRTH_DATE);
	DDX_OleDate(pDX, IDC_WBIRTH_DATE, m_WBirthDate, m_pRSet->m_WBIRTH_DATE);
	DDX_FieldText(pDX, IDC_MBIRTH_COUNTRY, m_pRSet->m_MBIRTH_COUNTRY, m_pRSet);
	DDX_FieldText(pDX, IDC_WBIRTH_COUNTRY, m_pRSet->m_WBIRTH_COUNTRY, m_pRSet);
	DDX_FieldText(pDX, IDC_MBIRTH_REGION, m_pRSet->m_MBIRTH_REGION, m_pRSet);
	DDX_FieldText(pDX, IDC_WBIRTH_REGION, m_pRSet->m_WBIRTH_REGION, m_pRSet);
	DDX_FieldText(pDX, IDC_MBIRTH_DISTRICT, m_pRSet->m_MBIRTH_DISTRICT, m_pRSet);
	DDX_FieldText(pDX, IDC_WBIRTH_DISTRICT, m_pRSet->m_WBIRTH_DISTRICT, m_pRSet);
	DDX_FieldText(pDX, IDC_MBIRTH_CITY, m_pRSet->m_MBIRTH_CITY, m_pRSet);
	DDX_FieldText(pDX, IDC_WBIRTH_CITY, m_pRSet->m_WBIRTH_CITY, m_pRSet);
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
  DDX_MSButton(pDX, IDC_MPASSPORT_TYPE, m_MPassport_Type, m_pRSet->m_MPASSPORT_TYPE);
  DDX_MSButton(pDX, IDC_WPASSPORT_TYPE, m_WPassport_Type, m_pRSet->m_WPASSPORT_TYPE);
	DDX_FieldText(pDX, IDC_MPASSPORT_SERIA, m_pRSet->m_MPASSPORT_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_WPASSPORT_SERIA, m_pRSet->m_WPASSPORT_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_MPASSPORT_NUMBER, m_pRSet->m_MPASSPORT_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WPASSPORT_NUMBER, m_pRSet->m_WPASSPORT_NUMBER, m_pRSet);
	DDX_OleDate(pDX, IDC_MPASSPORT_DATE, m_MPassportDate, m_pRSet->m_MPASSPORT_DATE);
	DDX_OleDate(pDX, IDC_WPASSPORT_DATE, m_WPassportDate, m_pRSet->m_WPASSPORT_DATE);
	DDX_FieldText(pDX, IDC_MPASSPORT_BY, m_pRSet->m_MPASSPORT_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_WPASSPORT_BY, m_pRSet->m_WPASSPORT_BY, m_pRSet);
  DDX_MSButton(pDX, IDC_MFAMILY_STATUS, m_MFamily_Status, m_pRSet->m_MFAMILY_STATUS);
  DDX_MSButton(pDX, IDC_WFAMILY_STATUS, m_WFamily_Status, m_pRSet->m_WFAMILY_STATUS);
	DDX_FieldText(pDX, IDC_MACT_NUMBER, m_pRSet->m_MACT_NUMBER, m_pRSet);
	DDX_FieldText(pDX, IDC_WACT_NUMBER, m_pRSet->m_WACT_NUMBER, m_pRSet);
	DDX_OleDate(pDX, IDC_MACT_DATE, m_MActDate, m_pRSet->m_MACT_DATE);
	DDX_OleDate(pDX, IDC_WACT_DATE, m_WActDate, m_pRSet->m_WACT_DATE);
	DDX_FieldText(pDX, IDC_MACT_BY, m_pRSet->m_MACT_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_WACT_BY, m_pRSet->m_WACT_BY, m_pRSet);
	DDX_FieldText(pDX, IDC_CERTIFICATE_SERIA, m_pRSet->m_CERTIFICATE_SERIA, m_pRSet);
	DDX_FieldText(pDX, IDC_CERTIFICATE_NUMBER, m_pRSet->m_CERTIFICATE_NUMBER, m_pRSet);
  DDX_FieldText(pDX, IDC_NOTICE, m_pRSet->m_EXTNOTES, m_pRSet);
	DDX_FieldText(pDX, IDC_MNOTICE, m_pRSet->m_MNOTICE, m_pRSet);
	DDX_FieldText(pDX, IDC_WNOTICE, m_pRSet->m_WNOTICE, m_pRSet);

/************************************** : by VK at 04.12.2004 5:00:29 **\
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
\************************************** : by VK at 04.12.2004 5:00:33 **/
  m_ID = m_pRSet->m_ID;
}


BEGIN_MESSAGE_MAP(CFormMarriage, CEraForm)
	//{{AFX_MSG_MAP(CFormMarriage)
	ON_EN_SETFOCUS(IDC_DATEREG, OnSetfocusDatereg)
	ON_EN_SETFOCUS(IDC_NUMBER, OnSetfocusNumber)
	ON_EN_SETFOCUS(IDC_MNEW_SURNAME, OnSetfocusMNewSurname)
	ON_EN_SETFOCUS(IDC_WNEW_SURNAME, OnSetfocusWNewSurname)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_SERIA, OnSetfocusCertificateSeria)
	ON_EN_SETFOCUS(IDC_CERTIFICATE_NUMBER, OnSetfocusCertificateNumber)
	ON_EN_CHANGE(IDC_CERTIFICATE_NUMBER, OnChangeCertificateNumber)
  ON_EN_SETFOCUS(IDC_NOTICE, OnSetfocusNotice)
  ON_COMMAND(ID_RECORD_DELETE, OnRecordDelete)
  ON_COMMAND(ID_RECORD_NEW, OnRecordNew)
	ON_WM_CONTEXTMENU()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
	ON_MESSAGE(UNM_HYPERLINK_CLICKED, NotifyHyperlinkClicked)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormMarriage diagnostics

#ifdef _DEBUG
void CFormMarriage::AssertValid() const
{
	CEraForm::AssertValid();
}

void CFormMarriage::Dump(CDumpContext& dc) const
{
	CEraForm::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormMarriage message handlers
CDaoRecordset* CFormMarriage::OnGetRecordset() {
	if (m_pSet != NULL)
		return m_pSet;

	m_pSet = new CRSMarriages(NULL);
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

CRSMarriages* CFormMarriage::GetRecordset() {
	CRSMarriages* pSet = (CRSMarriages*) OnGetRecordset();
	ASSERT(pSet != NULL && pSet->IsKindOf(RUNTIME_CLASS(CRSMarriages)));
	return pSet;
}

#ifndef FREE_LICENCE
BOOL CFormMarriage::IsRDFFieldsDirty() {
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  if ( m_pRSet ) {
    // SetChangedBy(m_pRSet, m_pRSet->m_EXTNOTES);
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
void CFormMarriage::SetRDFFields() {
  if ( m_GeoFieldsDirtyFlags & FATHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_MRP_REGION, m_pRSet->m_MRP_DISTRICT, m_pRSet->m_MRP_CITY, false);
  if ( m_GeoFieldsDirtyFlags & MOTHER_GEO_FIELDS_DIRTY )
    SaveGeoValidation(m_pRSet->m_WRP_REGION, m_pRSet->m_WRP_DISTRICT, m_pRSet->m_WRP_CITY, false);
  if ( m_GeoFieldsDirtyFlags )
    SaveGeoValidation();
  m_GeoFieldsDirtyFlags = NO_GEO_FIELDS_DIRTY;
  SaveDateValidation(&m_pRSet->m_DATEREG, &m_pRSet->m_MACT_DATE, &m_pRSet->m_WACT_DATE);
}
#endif // FREE_LICENCE
void CFormMarriage::AddRecordToNavigateBars(CListCtrl* pNameList, CListCtrl* pNumberList) {
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

void CFormMarriage::OnInitialUpdate() {
	BeginWaitCursor();

  ((CMainFrame*)AfxGetMainWnd())->m_pMarriageFrame = GetParentFrame();
  m_nPrinPos = CONTEXT_MARRIAGE; // Шлюб

	GetRecordset();
	CEraForm::OnInitialUpdate();

	if (m_pRSet->IsOpen()) {
/************************************** : by VK at 26.05.2006 23:18:11 **\
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
\************************************** : by VK at 26.05.2006 23:18:14 **/
    CString strTitle = m_pRSet->m_pDatabase->GetName();
    strTitle += _T(" - Шлюби");
    CEragsDoc* pDoc = (CEragsDoc*)GetDocument();
    pDoc->SetTitle(strTitle);

    GetDlgItem(IDC_MCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);
    GetDlgItem(IDC_WCITIZEN_LABEL)->ModifyStyle(0, WS_BORDER|SS_OWNERDRAW, 0);

    m_MCitizenship.SetDefault( g_szDefCitizenship );
    m_WCitizenship.SetDefault( g_szDefCitizenship );

    m_MBirth_Country.SetDefault(theIniCache.GetCOUNTRY());
    m_WBirth_Country.SetDefault(theIniCache.GetCOUNTRY());

    m_MRP_Country.SetDefault(theIniCache.GetCOUNTRY());
    m_WRP_Country.SetDefault(theIniCache.GetCOUNTRY());

    OnMove(ID_RECORD_LAST);
    if ( m_pRSet->IsEOF() && m_pRSet->IsBOF() ) {
      EnableForm(FALSE);
    }
    else {
      SetFocusToFirstControl();
    }

	}
	EndWaitCursor();

#ifndef FREE_LICENCE
  if ( FALSE==RegDlg(&m_tooltip) ) {
    AfxGetMainWnd()->PostMessage(WM_QUIT);
  }
#endif // #FREE_LICENCE
  EmptyTable();
}

BOOL CFormMarriage::OnMove(UINT nIDMoveCommand) {
  if ( NULL==m_pRSet )
    return FALSE;
  if ( m_pRSet->IsBOF() && m_pRSet->IsEOF() )
    return FALSE;
  BOOL bNewRecord = m_fNewRecord;
  BOOL bRet = CEraForm::OnMove(nIDMoveCommand);
  if ( bRet ) {
    g_szSaveMVerdict.Empty();
    g_szSaveWVerdict.Empty();
    if ( bNewRecord ) {
      SetFocusToFirstControl();
    }
    theCitizenships.FillCombo( m_MCitizenship, m_pRSet->m_MCITIZENSHIP );
    theCitizenships.FillCombo( m_WCitizenship, m_pRSet->m_WCITIZENSHIP );
    theMNames.FillCombo( m_MName, m_pRSet->m_MNAME, false );
    theWNames.FillCombo( m_WName, m_pRSet->m_WNAME, false );
    theMPatronymics.FillCombo( m_MPatronymic, m_pRSet->m_MPATRONYMIC, false );
    theWPatronymics.FillCombo( m_WPatronymic, m_pRSet->m_WPATRONYMIC, false );

    theGeoCache.FillCountryCB(m_MBirth_Country, m_pRSet->m_MBIRTH_COUNTRY);
    theGeoCache.FillCountryCB(m_WBirth_Country, m_pRSet->m_WBIRTH_COUNTRY);
    theGeoCache.FillRegionCB(m_MBirth_Region, m_MBirth_Country, m_pRSet->m_MBIRTH_REGION );
    theGeoCache.FillRegionCB(m_WBirth_Region, m_WBirth_Country, m_pRSet->m_WBIRTH_REGION );
    theGeoCache.FillDistrictCB(m_MBirth_District, m_MBirth_Region, m_pRSet->m_MBIRTH_DISTRICT);
    theGeoCache.FillDistrictCB(m_WBirth_District, m_WBirth_Region, m_pRSet->m_WBIRTH_DISTRICT);
    theGeoCache.FillCityCB(m_MBirth_City, m_MBirth_Region, m_MBirth_District, m_pRSet->m_MBIRTH_CITY);
    theGeoCache.FillCityCB(m_WBirth_City, m_WBirth_Region, m_WBirth_District, m_pRSet->m_WBIRTH_CITY);

    theGeoCache.FillCountryCB(m_MRP_Country, m_pRSet->m_MRP_COUNTRY);
    theGeoCache.FillCountryCB(m_WRP_Country, m_pRSet->m_WRP_COUNTRY);
    theGeoCache.FillRegionCB(m_MRP_Region, m_MRP_Country, m_pRSet->m_MRP_REGION );
    theGeoCache.FillRegionCB(m_WRP_Region, m_WRP_Country, m_pRSet->m_WRP_REGION );
    theGeoCache.FillDistrictCB(m_MRP_District, m_MRP_Region, m_pRSet->m_MRP_DISTRICT);
    theGeoCache.FillDistrictCB(m_WRP_District, m_WRP_Region, m_pRSet->m_WRP_DISTRICT);
    theGeoCache.FillCityCB(m_MRP_City, m_MRP_Region, m_MRP_District, m_pRSet->m_MRP_CITY);
    theGeoCache.FillCityCB(m_WRP_City, m_WRP_Region, m_WRP_District, m_pRSet->m_WRP_CITY);

    theStreets.FillCombo( m_MRP_Street, m_pRSet->m_MRP_STREET );
    theStreets.FillCombo( m_WRP_Street, m_pRSet->m_WRP_STREET );

    OnFamilyStatusDependences(m_MFamily_Status, IDC_MNACT_LABEL, IDC_MACT_NUMBER, IDC_MDATE_LABEL, IDC_MACT_DATE, IDC_MBY_LABEL, IDC_MACT_BY, m_MNotice);
    OnFamilyStatusDependences(m_WFamily_Status, IDC_WNACT_LABEL, IDC_WACT_NUMBER, IDC_WDATE_LABEL, IDC_WACT_DATE, IDC_WBY_LABEL, IDC_WACT_BY, m_WNotice);

    theMIAs.FillCombo( m_MPassport_By, m_pRSet->m_MPASSPORT_BY );
    theMIAs.FillCombo( m_WPassport_By, m_pRSet->m_WPASSPORT_BY );
    m_MPassport_By.SetDefault( theIniCache.GetByROVD() );
    m_WPassport_By.SetDefault( theIniCache.GetByROVD() );


    m_MAct_By.SetDefault(theIniCache.GetRAGS());
    m_WAct_By.SetDefault(theIniCache.GetRAGS());

    theRList.FillRegCB(m_MAct_By, m_pRSet->m_MACT_BY);
    theRList.FillRegCB(m_WAct_By, m_pRSet->m_WACT_BY);

  }
 	return bRet;
}

void CFormMarriage::OnSetfocusDatereg() {
	if ( m_DateReg.IsEmpty() ) {
    COleDateTime odt = COleDateTime::GetCurrentTime();
    while ( odt.GetDayOfWeek() != 7 ) {
      odt += COleDateTimeSpan( 1, 0, 0, 0 );
    }
    //CString s;
    //s.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
    m_DateReg.SetDate( odt );
  }
}

void CFormMarriage::OnSetfocusNumber() {
  if ( 0==m_pRSet->m_NUMBER && SetDefaultNumber(m_pRSet->m_NUMBER) ) {
    m_pRSet->Edit();
    m_pRSet->Update();
    UpdateData(TRUE);
    m_pRSet->SetBookmark( m_pRSet->GetLastModifiedBookmark() );
    SetBookMarks();
  }
}

void CFormMarriage::OnSetfocusMNewSurname() {
	if ( m_MNewSurname.IsEmpty() && !m_MOldSurname.IsEmpty() ) {
    m_MNewSurname.SetWindowText(m_MOldSurname.GetText());
    m_MNewSurname.SetSel(0, -1);
  }
}

void CFormMarriage::OnSetfocusWNewSurname() {
	if ( m_WNewSurname.IsEmpty() &&  !m_MNewSurname.IsEmpty() ) {
    m_WNewSurname.SetWindowText( OfferSurname( m_MNewSurname.GetText(), TRUE, FALSE) );
    m_WNewSurname.SetSel(0, -1);
  }
}

void CFormMarriage::OnSetfocusCertificateSeria() {
  if ( m_Certificate_Seria.IsEmpty() ) {
    m_Certificate_Seria.SetWindowText( theIniCache.GetMARRIAGE_Seria() );
    m_Certificate_Seria.SetSel(0, -1);
  }
}

void CFormMarriage::OnSetfocusCertificateNumber() {
  bool fSeriaIsEmpty = m_Certificate_Seria.IsEmpty();
  if ( m_Certificate_Number.IsEmpty() && !fSeriaIsEmpty ) {
    CString s = theIniCache.GetMARRIAGE_CNum();
    int nLen = s.GetLength();
    m_Certificate_Number.SetWindowText( s );
    m_Certificate_Number.SetSel(nLen, nLen);
  }
/************************************** : by VK at 23.01.2004 22:07:55 **\
  else if ( fSeriaIsEmpty ) {
    if ( IDC_MNOTICE==m_LastCtrlId )
      m_Certificate_Seria.SetFocus();
    else
      m_Notice.SetFocus();
  }
\************************************** : by VK at 23.01.2004 22:07:57 **/
}

void CFormMarriage::OnChangeCertificateNumber() {
  theIniCache.SetMARRIAGE_CNum( &m_Certificate_Number );	
}

CString GetVerdictSentence(const CString& sMemo) {
  CString sz;
  if ( sMemo.Find(_T("Рішення")) >= 0 && sMemo.Find(_T(" розірвання")) > 0 ) {
    sz = GetSentence(sMemo, _T("Рішення "), _T("р."));
    if ( sz.IsEmpty() ) {
      sz = GetSentence(sMemo, _T("Рішення "), _T("року."));
    }
  }
  return sz;
}


void CFormMarriage::OnFamilyStatusDependences(CEraMultiStateButton& msFamily_Status,
                                              UINT id_NACT_LABEL, UINT id_ACT_NUMBER,
                                              UINT id_DATE_LABEL, UINT id_ACT_DATE,
                                              UINT id_BY_LABEL,  UINT id_ACT_BY,
                                              CEraNoticeEdit& NoticeWnd,
                                              BOOL fSet/*=false*/
                                              ) {
  // modify database, set default value = 0 for MFamily_Status and WFamily_Status
  int nIndex = msFamily_Status.GetIndex();
  int nShowWindow = SW_SHOW;
  switch ( nIndex ) {
    case 0: // У шлюбі не перебував(ла)
    case 3: // Розлучений(на) за рішенням суду
      nShowWindow = SW_HIDE;
      break;
  }

  GetDlgItem(id_NACT_LABEL)->ShowWindow(nShowWindow);
  GetDlgItem(id_ACT_NUMBER)->ShowWindow(nShowWindow);
  GetDlgItem(id_DATE_LABEL)->ShowWindow(nShowWindow);
  GetDlgItem(id_ACT_DATE)->ShowWindow(nShowWindow);
  GetDlgItem(id_BY_LABEL)->ShowWindow(nShowWindow);
  GetDlgItem(id_ACT_BY)->ShowWindow(nShowWindow);
  msFamily_Status.InvalidateRect(NULL);


  if ( fSet ) {
    CString sMemo, sz;
    NoticeWnd.GetWindowText(sMemo);

    sz = GetVerdictSentence(sMemo);

    if ( sz.IsEmpty() && 3==nIndex) { // to add
      CString& szSave = NoticeWnd.m_hWnd==m_MNotice.m_hWnd ? g_szSaveMVerdict : g_szSaveWVerdict;
      if ( szSave.IsEmpty() ) {
        COleDateTime odt = COleDateTime::GetCurrentTime();
        odt -= COleDateTimeSpan(30, 0, 0, 0);

        sz.Format(_T("Рішення %s про розірвання шлюбу № 1 від %02d.%02d.%04d р."), theIniCache.GetByCourt(), odt.GetDay(), odt.GetMonth(), odt.GetYear());
      }
      else {
        sz = szSave;
      }
      sMemo = Trim(sMemo);
      sMemo += ' ';
      sMemo += sz;
      sMemo = Trim(sMemo);
    }
    else if ( false==sz.IsEmpty() && 0==nIndex) {  // to remove
      CString& szSave = NoticeWnd.m_hWnd==m_MNotice.m_hWnd ? g_szSaveMVerdict : g_szSaveWVerdict;
      szSave = sz;
      sMemo = FindAndReplace(sMemo, sz, _T(""), true);
    }
    NoticeWnd.SetWindowText(sMemo);
  }

}


void CFormMarriage::OnBlank(const CString& szTemplate, const CString& szOut) {
  if ( RTF_MarriageBlank(szTemplate, szOut, m_pRSet) ) {
    OnRTFShell(szOut);
  }
}

void CFormMarriage::OnPrint(UINT nPrintID) {
  CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();

  if ( FALSE==CEraForm::OnMove(0) ) // Save data
    return;

#ifndef FREE_LICENCE
    theRegTimer.Next();
#endif

  CString sTemplate, sOut;

  g_nDocType = DOCTYPE_OTHER;

  switch ( nPrintID ) {
    case ID_PRINT_MARRIAGE_ACT:
      g_nDocType = DOCTYPE_ACT;
      sTemplate.Format(IDS_MARRIAGE_IN, theApp.m_sTemplatePath, _T("Act") );
      sOut.Format(IDS_MARRIAGE_OUT, theApp.m_sOutPath, _T("Act"), m_pRSet->m_NUMBER);
      MakeInOutExt(sTemplate, sOut);
      break;
    case ID_PRINT_MARRIAGE_CERIFICATE: {
        g_nDocType = DOCTYPE_CERT;
        CSVDlg dlg(this, IDD_SVID);
        dlg.m_szFormSect = _T("MARRIAGE_FORM");
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_MARRIAGE_IN, theApp.m_sTemplatePath, _T("Certificate") );
          sOut.Format(IDS_MARRIAGE_OUT, theApp.m_sOutPath, _T("Certificate"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
        else
          return;
      }
      break;
    case ID_PRINT_ANTENUPTIAL: {
        CDlg38 dlg(this);
        if ( IDYES==dlg.DoModal() ) {
          sTemplate.Format(IDS_MARRIAGE_IN, theApp.m_sTemplatePath, _T("38.7.7") );
          sOut.Format(IDS_MARRIAGE_OUT, theApp.m_sOutPath, _T("38.7.7"), m_pRSet->m_NUMBER);
          MakeInOutExt(sTemplate, sOut);
        }
      }
      break;
    case ID_PRINT_MARRIAGE_ABC: {
        CABCDlg dlg(false, this);
        if ( dlg.DoModal()==IDYES ) {
          sTemplate.Format(IDS_MARRIAGE_IN, theApp.m_sTemplatePath, _T("ABC") );
          sOut.Format(IDS_MARRIAGE_OUT, theApp.m_sOutPath, _T("ABC") );
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
        MakeInOutExt(sTemplate, sOut);
        if ( dlg.DoModal()==IDYES ) {
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
    case ID_PRINT_MARRIAGE_14_4_1 :  case ID_PRINT_MARRIAGE_15_4_28 :
    case ID_PRINT_MARRIAGE_33_7_1 :  case ID_PRINT_MARRIAGE_37_7_7  :
    case ID_PRINT_MARRIAGE_38_7_7 :  case ID_PRINT_MARRIAGE_39_7_8  :
    case ID_PRINT_MARRIAGE_40_7_8 :  case ID_PRINT_MARRIAGE_44_7_8  :
    case ID_PRINT_MARRIAGE_45_7_8 :  case ID_PRINT_MARRIAGE_46_7_8  :
    case ID_PRINT_MARRIAGE_51_7_8 :  case ID_PRINT_MARRIAGE_52_7_8  :
    case ID_PRINT_MARRIAGE_53_7_8 :  case ID_PRINT_MARRIAGE_54_7_8  :
      OnBlankItem();
      break;
  }

  if ( sTemplate.IsEmpty() )
    return;

  switch(nPrintID) {
    case ID_PRINT_MARRIAGE_ABC:
      if (FALSE==RTF_ABCMarriage(sTemplate, sOut, m_pRSet) )
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

LRESULT CFormMarriage::NotifyHyperlinkClicked(WPARAM wParam, LPARAM lParam) {
  LPCTSTR szMessage = (LPCTSTR)wParam;
  if ( stricmp(szMessage, "close")==0 ) {
    m_fEnableRelayEvent = true;
  }
  m_tooltip.HideTooltip();

  return TRUE;
}

BOOL CFormMarriage::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  BOOL bResult;
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
      if ( pControl->IsKindOf(RUNTIME_CLASS(CEraDateEdit)) && ((CEraDateEdit*)pControl)->IsCalendarActive()) {
        m_tooltip.HideTooltip();
      }
      m_fEnableRelayEvent = true;
      break;
  }

  switch (wCtrlId) {
    case IDC_DATEREG:
      if ( EN_KILLFOCUS==wNotifyCode ) {
        if ( IsFocusChild(this) ) {
          m_tooltip.HideTooltip();
          bResult = CEraForm::OnCommand(wParam, lParam);
          if ( FALSE==CheckDateReg(this, &m_DateReg, m_fNewRecord) ) {
            m_DateReg.SetFocus();
            return FALSE;
          }
        }
        return bResult;
      }
      break;
    case IDC_MBIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MBirthDate, _T("народження"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_WBIRTH_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_WBirthDate, _T("народження"), &m_DateReg, _T("реєстрації"), TRUE) ) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_MBIRTH_COUNTRY:  if ( CBN_SETFOCUS==wNotifyCode ) m_MBirth_Country.UpdateByDefault();
      break;
    case IDC_WBIRTH_COUNTRY:  if ( CBN_SETFOCUS==wNotifyCode ) m_WBirth_Country.UpdateByDefault();
      break;
    case IDC_MBIRTH_REGION:   if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_MBirth_Country, m_MBirth_Region, m_MBirth_City);
      break;
    case IDC_WBIRTH_REGION:   if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_WBirth_Country, m_WBirth_Region, m_WBirth_City);
      break;
    case IDC_MBIRTH_DISTRICT: if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_MBirth_Region, m_MBirth_District);
      break;
    case IDC_WBIRTH_DISTRICT: if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_WBirth_Region, m_WBirth_District);
      break;
    case IDC_MBIRTH_CITY:     if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_MBirth_Country, m_MBirth_Region, m_MBirth_District, m_MBirth_City);
      break;
    case IDC_WBIRTH_CITY:     if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_WBirth_Country, m_WBirth_Region, m_WBirth_District, m_WBirth_City);
      break;

    case IDC_MRP_COUNTRY:     if ( CBN_SETFOCUS==wNotifyCode ) m_MRP_Country.UpdateByDefault();
      break;
    case IDC_WRP_COUNTRY:     if ( CBN_SETFOCUS==wNotifyCode ) m_WRP_Country.UpdateByDefault();
      break;
    case IDC_MRP_REGION:      if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_MRP_Country, m_MRP_Region, m_MRP_City);
      break;
    case IDC_WRP_REGION:      if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusRegion(m_WRP_Country, m_WRP_Region, m_WRP_City);
      break;
    case IDC_MRP_DISTRICT:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_MRP_Region, m_MRP_District);
      break;
    case IDC_WRP_DISTRICT:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusDistrict(m_WRP_Region, m_WRP_District);
      break;
    case IDC_MRP_CITY:        if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_MRP_Country, m_MRP_Region, m_MRP_District, m_MRP_City);
      break;
    case IDC_WRP_CITY:        if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusCity(m_WRP_Country, m_WRP_Region, m_WRP_District, m_WRP_City);
      break;

    case IDC_MCITIZENSHIP:    if ( CBN_SETFOCUS==wNotifyCode ) m_MCitizenship.UpdateByDefault();
      break;
    case IDC_WCITIZENSHIP:    if ( CBN_SETFOCUS==wNotifyCode ) m_WCitizenship.UpdateByDefault();
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

    case IDC_MPASSPORT_BY:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_MPassport_Seria,  m_MPassport_Number, m_MPassport_By);
      break;
    case IDC_WPASSPORT_BY:    if ( CBN_SETFOCUS==wNotifyCode ) OnSetfocusPassportBy(m_WPassport_Seria,  m_WPassport_Number, m_WPassport_By);
      break;

    case IDC_MACT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_MActDate, _T("розлучення/смерті"), &m_DateReg, _T("реєстрації"),  TRUE)) {
          return FALSE;
        }
        return bResult;
      }
      break;
    case IDC_WACT_DATE:
      if ( EN_KILLFOCUS==wNotifyCode && IsFocusChild(this) ) {
        m_tooltip.HideTooltip();
        bResult = CEraForm::OnCommand(wParam, lParam);
        if ( FALSE==CheckDates(&m_WActDate, _T("розлучення/смерті"), &m_DateReg, _T("реєстрації"),  TRUE)) {
          return FALSE;
        }
        return bResult;
      }
      break;

    case IDC_MACT_BY:
      if ( CBN_SETFOCUS==wNotifyCode ) {
        switch( m_MFamily_Status.GetIndex() ) {
          case 1  : // Розлучена
            m_MAct_By.SetDefault( theIniCache.GetParent() );
            break;
          default :
            m_MAct_By.SetDefault( theIniCache.GetRAGS() );
            break;
        }
        m_MAct_By.UpdateByDefault();
      }
      break;
    case IDC_WACT_BY:
      if ( CBN_SETFOCUS==wNotifyCode ) {
        switch( m_WFamily_Status.GetIndex() ) {
          case 1  : // Розлучена
            m_WAct_By.SetDefault( theIniCache.GetParent() );
            break;
          default :
            m_WAct_By.SetDefault( theIniCache.GetRAGS() );
            break;
        }
        m_WAct_By.UpdateByDefault();
      }
      break;

    case IDC_MFAMILY_STATUS:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnFamilyStatusDependences(m_MFamily_Status, IDC_MNACT_LABEL, IDC_MACT_NUMBER,
                                  IDC_MDATE_LABEL, IDC_MACT_DATE,
                                  IDC_MBY_LABEL, IDC_MACT_BY, m_MNotice, true);
        return bResult;
      }
      break;
    case IDC_WFAMILY_STATUS:
      if ( BN_CLICKED==wNotifyCode ) {
        bResult = CEraForm::OnCommand(wParam, lParam);
        OnFamilyStatusDependences(m_WFamily_Status, IDC_WNACT_LABEL, IDC_WACT_NUMBER,
                                  IDC_WDATE_LABEL, IDC_WACT_DATE,
                                  IDC_WBY_LABEL, IDC_WACT_BY, m_WNotice, true);
        return bResult;
      }
      break;
  }
  bResult = CEraForm::OnCommand(wParam, lParam);
  m_LastCtrlId = wCtrlId;
	return bResult;
}

void CFormMarriage::OnSetfocusNotice() {
  CString s;
  m_Notice.GetWindowText(s);
  if ( false==s.IsEmpty() )
    return;

  s = theIniCache.GetMARRIAGE_DefNotice();

  m_Notice.SetWindowText(s);
}


void CFormMarriage::OnRecordDelete() {
  CEraForm::OnRecordDelete();
//  m_MCitizenLabel.InvalidateRect(NULL);
//  m_WCitizenLabel.InvalidateRect(NULL);
}

void CFormMarriage::OnRecordNew() {
  CEraForm::OnRecordNew();
//  m_MCitizenLabel.InvalidateRect(NULL);
//  m_WCitizenLabel.InvalidateRect(NULL);
}

void CFormMarriage::OnContextMenu(CWnd* pWnd, CPoint point) {
	// TODO: Add your message handler code here
  m_tooltip.HideTooltip();

  UINT nPos = CONTEXT_MARRIAGE;
  CString s, sMemo;
  CEraNoticeEdit* pNotice = (CEraNoticeEdit*)pWnd;
  if ( pNotice==&m_Notice ) {
    m_Notice.GetWindowText(sMemo);
    s = ContextMenu(m_Notice.m_hWnd, nPos, true, m_DateReg.GetDate(), sMemo, false, NULL, NULL);
    if ( s != sMemo )
      m_Notice.SetWindowText(s);
  }
  else if ( pNotice==&m_MNotice ) {
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

void CFormMarriage::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDIS) {
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
