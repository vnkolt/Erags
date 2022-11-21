// MonthList.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "Defaults.h"
#include "MonthList.h"
#include "Geography.h"

#include "..\Common\CyrString.h"
#include "..\Common\FHelpers.h"

#include "..\Controls\ShellType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

SHORT         g_iMonth = 0;
BOOL          g_fPeriod = false;
BOOL          g_fNoPrintUnknowns = true;
COleDateTime  g_odtFrom;
COleDateTime  g_odtTill;
COleDateTime  g_RegDate;

CString g_sChoosenDistrict;
CString g_sOverString;

extern BOOL     g_fMakeDBF;
extern CString  g_szVBScript;

int CMonthList::m_PrintWhat = PRINT_ALLDOCS;

/////////////////////////////////////////////////////////////////////////////
// CMonthList dialog


CMonthList::CMonthList(UINT idPrintID, BOOL bCheckPeriod, const COleDateTime& odt, CWnd* pParent /*=NULL*/)
	         :CDialogEx(CMonthList::IDD, pParent) {
	//{{AFX_DATA_INIT(CMonthList)
	//}}AFX_DATA_INIT

  m_PrintID = idPrintID;

  if ( (DATE)0==g_RegDate.m_dt)
    g_RegDate = COleDateTime::GetCurrentTime();

  if ( COleDateTime::valid==odt.GetStatus() )
    m_odt = odt;
  else
    m_odt = COleDateTime::GetCurrentTime();
  m_bCheckPeriod = bCheckPeriod;
}

CMonthList::~CMonthList() {
  m_cache.RemoveAll();
}

void CMonthList::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMonthList)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
  DDX_Control(pDX, IDC_FRAME4, m_Frame4);
	DDX_Control(pDX, IDC_PAGE2, m_Page2);
	DDX_Control(pDX, IDC_PAGE1, m_Page1);
	DDX_Control(pDX, IDC_TILL, m_Till);
	DDX_Control(pDX, IDC_FROM, m_From);
	DDX_Control(pDX, IDC_PERIOD, m_chkPeriod);
	DDX_Control(pDX, IDC_COMBORAGS, m_cmbDistrict);
	DDX_Control(pDX, IDC_MONLIST, m_MonList);
  DDX_Control(pDX, IDC_COMMONLIST, m_btnCommonList);
  DDX_Control(pDX, IDC_PASSPORTS, m_btnPasports);
  DDX_Control(pDX, IDC_MILCARS, m_btnMilCards);
  DDX_Control(pDX, IDC_NOPRINT_UNKNOWNS, m_chkNoUnknowns);
  DDX_Control(pDX, IDC_MAKE_DBF, m_chkMakeDBF);
  DDX_Control(pDX, IDC_SCRIPT_COMBO, m_cmbVBScript);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMonthList, CDialogEx)
	//{{AFX_MSG_MAP(CMonthList)
	ON_LBN_SELCHANGE(IDC_MONLIST, OnSelchangeMonlist)
	ON_CBN_EDITCHANGE(IDC_COMBORAGS, OnEditChangeComboDistricts)
	ON_CBN_SELCHANGE(IDC_COMBORAGS, OnSelchangeComboDistricts)
	ON_EN_CHANGE(IDC_PAGE1, OnChangePage1)
	ON_EN_CHANGE(IDC_PAGE2, OnChangePage2)
	ON_BN_CLICKED(IDC_PERIOD, OnPeriod)
  ON_BN_CLICKED(IDC_NOPRINT_UNKNOWNS, OnNoPrintUnknowns)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_BN_CLICKED(IDC_COMMONLIST, OnCommonlist)
	ON_BN_CLICKED(IDC_PASSPORTS, OnPassports)
	ON_BN_CLICKED(IDC_MILCARS, OnMilcars)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

void CMonthList::Resize() {
  CRect r;
  m_cmbDistrict.GetWindowRect(&r);
  int cy = r.bottom;
  GetDlgItem(IDC_DISTRICT_LABEL)->GetWindowRect(&r);
  cy -= r.top;
  CWnd* pWnd = m_cmbDistrict.GetWindow(GW_HWNDNEXT);
  int i(0);
  while ( pWnd ) {
    pWnd->GetWindowRect(&r);
    ScreenToClient(&r);
    r.OffsetRect(0, -cy);
    pWnd->MoveWindow(&r);
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
  GetWindowRect(&r);
  SetWindowPos(NULL, 0, 0, r.Width(), r.Height()-cy, SWP_NOMOVE|SWP_NOZORDER);
}

void CMonthList::FillVBScriptCombo(LPCTSTR pszKey) {
  CString szKey = CString(pszKey).Right(3);
  szKey.MakeLower();
  CString szMask, szKeyFile;
  szMask.Format(_T("%s\\*.vbs"), GetModulePath());

  CFileFind finder;
  BOOL bWorking = finder.FindFile(szMask);
  while (bWorking) {
    bWorking = finder.FindNextFile();
    if (finder.IsDots() || finder.IsDirectory() ) {
      continue;
    }
    CString szFile = finder.GetFileName();
    m_cmbVBScript.AddString( szFile );
    szFile.MakeLower();
    if ( szFile.Find(szKey) >= 0 ) {
      szKeyFile = finder.GetFileName();
    }
  }
  CString szSel = theApp.GetProfileString(_T("Settings"), pszKey);
  if ( false==szSel.IsEmpty() ) {
    int nSel = m_cmbVBScript.SelectString(-1, szSel);
    if ( nSel==CB_ERR ) {
      m_cmbVBScript.SetCurSel(0);
    }
  }
  else if ( false==szKeyFile.IsEmpty() ) {
    m_cmbVBScript.SelectString(-1, szKeyFile);
  }
}
/////////////////////////////////////////////////////////////////////////////
// CMonthList message handlers
BOOL CMonthList::OnInitDialog() {
	CDialogEx::OnInitDialog();

  m_sCaption.Replace(_T("&"), _T(""));
  SetWindowText(m_sCaption);

  // Создаём иммидж-лист для радиокнопок
  if ( m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF)) ) {
    m_btnCommonList.SetRadioImageList(&m_RadioIL);
    m_btnCommonList.SetRadio(IDC_COMMONLIST, IDC_MILCARS);

    m_btnPasports.SetRadioImageList(&m_RadioIL);
    m_btnPasports.SetRadio(IDC_COMMONLIST, IDC_MILCARS);

    m_btnMilCards.SetRadioImageList(&m_RadioIL);
    m_btnMilCards.SetRadio(IDC_COMMONLIST, IDC_MILCARS);
  }
  // Создаём иммидж-лист для чек-боксов
  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkPeriod.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkNoUnknowns.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkMakeDBF.SetCheckBoxImageList(&m_CheckBoxIL);
  }
  int chkMakeDBF = 0;
  switch( m_PrintID ) {
    case ID_PRINT_DEATH_FORTAX    :
    case ID_PRINT_DEATH_FORTAX_13 :
      chkMakeDBF = theApp.GetProfileInt(_T("Settings"), _T("DBFForTax"), 0);
      FillVBScriptCombo(_T("VBSForTax"));
      break;
    case ID_PRINT_DEATH_FORSOCPROT:
      chkMakeDBF = theApp.GetProfileInt(_T("Settings"), _T("DBFForSoc"), 0);
      m_Frame4.SetWindowText(_T("DBF-файл для органу соцзахисту"));
      FillVBScriptCombo(_T("VBSForSoc"));
      break;
    default                       :
      m_Frame4.ShowWindow(SW_HIDE);
      m_chkMakeDBF.ShowWindow(SW_HIDE);
      m_cmbVBScript.ShowWindow(SW_HIDE);
      GetDlgItem(IDC_LBL_VBSCRIPT)->ShowWindow(SW_HIDE);
      break;
  }

  if ( chkMakeDBF ) {
    m_chkMakeDBF.SetCheck(chkMakeDBF);
  }

  CString s;
  g_sChoosenDistrict.Empty();

  for (int i(0); i < 12; i++) {
    s.LoadString(i+IDS_UM01);
    m_MonList.AddString(s);
  }

  BOOL bFillDistrictCombo = false;

  CGeoRecord* pRecord = theGeoCache.GetCountry( theIniCache.GetCOUNTRY());
  if ( pRecord ) {
    pRecord = theGeoCache.GetRegion(&pRecord->m_array, theIniCache.GetREGION());
  }
  if ( pRecord ) {
    pRecord = theGeoCache.GetCity(&pRecord->m_array, theIniCache.GetCITY());
  }
  if ( pRecord && pRecord->GetCount() ) { // Город имеет районы?
    CString sDistrict = Trim(theIniCache.GetDISTRICT());
    if ( sDistrict.IsEmpty() ) { // Район по умолчанию не не указан
      for( int i(0); i < pRecord->GetCount(); i++ ) {
        CGeoRecord* pDistrict = (CGeoRecord*)pRecord->m_array.GetAt(i);
        if ( pDistrict ) {
          m_cmbDistrict.AddString(pDistrict->GetName());
        }
      }
      bFillDistrictCombo = true;
    }
  }
  if ( false==bFillDistrictCombo ) {
    GetDlgItem(IDC_DISTRICT_LABEL)->ShowWindow(SW_HIDE);
    m_cmbDistrict.ShowWindow(SW_HIDE);
    Resize();
  }

/************************************** : by VK at 24.12.2006 8:34:23 **\
  if ( false==theIniCache.FillForLists(m_cmbDistrict) ) {
    m_cmbDistrict.EnableWindow(FALSE);
  }
\************************************** : by VK at 24.12.2006 8:34:28 **/
  CString sDefPage1, sDefPage2;
  sDefPage1.Format(_T("%d"), m_MaxPage1);
  sDefPage2.Format(_T("%d"), m_MaxPage2);

  s = theIniCache.GetSVal(m_SectName, _T("Page1"), sDefPage1 );
  GetDlgItem(IDC_PAGE1)->SetWindowText(s);

  s = theIniCache.GetSVal(m_SectName, _T("Page2"), sDefPage2 );
  GetDlgItem(IDC_PAGE2)->SetWindowText(s);

  COleDateTime dt;
  dt = COleDateTime::GetCurrentTime();
  g_iMonth = (SHORT)dt.GetMonth();
  if(dt.GetDay()<28 && g_iMonth>1)
    g_iMonth--;
  m_MonList.SetCurSel(g_iMonth-1);

  dt = m_odt;
  while ( dt.GetDayOfWeek() != 2 ) { // Monday
    dt -= COleDateTimeSpan(1, 0, 0, 0);
  }
  m_From.SetDate(dt);

  dt = m_odt;
  while ( dt.GetDayOfWeek() != 1 ) { // Sunday
    dt += COleDateTimeSpan(1, 0, 0, 0);
  }
  m_Till.SetDate(dt);

  if ( m_bCheckPeriod )
    m_chkPeriod.SetCheck(1);
  else
    m_chkPeriod.SetCheck(0);
  OnPeriod();

  m_chkNoUnknowns.SetCheck(1);
  g_fNoPrintUnknowns = true;

  m_PrintWhat = PRINT_ALLDOCS;
  if ( m_SectName==_T("DEATH_PASSPORTS") ) {
    GetDlgItem(IDC_FRAME2)->ShowWindow(SW_NORMAL);
    GetDlgItem(IDC_COMMONLIST)->ShowWindow(SW_NORMAL);
    GetDlgItem(IDC_PASSPORTS)->ShowWindow(SW_NORMAL);
    GetDlgItem(IDC_MILCARS)->ShowWindow(SW_NORMAL);
    CheckDlgButton(IDC_COMMONLIST, 1);
  }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CMonthList::OnSelchangeMonlist() {
	// TODO: Add your control notification handler code here
  g_iMonth = (SHORT)(m_MonList.GetCurSel() + 1);

  COleDateTime odt = m_From.GetDate();
  odt.SetDate(odt.GetYear(), g_iMonth, 1);
  m_From.SetDate(odt);
  odt.SetDate(odt.GetYear(), g_iMonth, 28);
  while ( odt.GetMonth()==g_iMonth ) {
    odt += COleDateTimeSpan(1, 0, 0, 0);
  }
  odt -= COleDateTimeSpan(1, 0, 0, 0); // last day of  g_iMonth
  m_Till.SetDate(odt);
}

void CMonthList::OnEditChangeComboDistricts() {
	// TODO: Add your control notification handler code here
	if ( !m_cmbDistrict.GetDroppedState() )
      m_cmbDistrict.ShowDropDown(TRUE);
}
void CMonthList::OnSelchangeComboDistricts() {
	// TODO: Add your control notification handler code here
  int nIndex = m_cmbDistrict.GetCurSel();
  if( nIndex != CB_ERR){
    m_cmbDistrict.GetLBText(nIndex, g_sChoosenDistrict);
    g_sOverString = theIniCache.GetOverByDistrict(g_sChoosenDistrict);
  }
}

void CMonthList::OnChangePage1() {
  CString s;
  GetDlgItem(IDC_PAGE1)->GetWindowText(s);
  if ( false==IsEmptyText(s) ) {
    m_MaxPage1 = atoi(s);
    theIniCache.SetSVal(m_SectName, _T("Page1"), s);
  }
}

void CMonthList::OnChangePage2() {
  CString s;
  GetDlgItem(IDC_PAGE2)->GetWindowText(s);
  if ( false==IsEmptyText(s) ) {
    m_MaxPage2 = atoi(s);
    theIniCache.SetSVal(m_SectName, _T("Page2"), s);
  }
}

HBRUSH CMonthList::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO: Change any attributes of the DC here
  CWnd* pFocus = GetFocus();
  int iID = pFocus->GetDlgCtrlID();
  if ( /*iID==IDC_COMBORAGS || */iID==IDC_MONLIST ) {
    if ( pWnd==pFocus ) {
      pDC->SetBkColor(g_clrFocusBackColor);
      pDC->SetTextColor(g_clrFocusForeColor);
      return g_hFocusEditBrush;
    }
    else {
      pDC->SetBkColor(g_clrBackColor);
      pDC->SetTextColor(g_clrForeColor);
      return g_hEditBrush;
    }
  }
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CMonthList::OnPeriod() {
	// TODO: Add your control notification handler code here
  BOOL bEnable = m_chkPeriod.GetCheck() ? true : false;
  m_Till.EnableWindow(bEnable);
  m_From.EnableWindow(bEnable);
}

void CMonthList::OnNoPrintUnknowns() {
  g_fNoPrintUnknowns = m_chkNoUnknowns.GetCheck() ? true : false;
}

void CMonthList::OnYes() {
  if ( UpdateData(TRUE) ) {
    int cbSel = CB_ERR;
    g_fMakeDBF = false;
    g_szVBScript.Empty();
    switch( m_PrintID ) {
      case ID_PRINT_DEATH_FORTAX    :
      case ID_PRINT_DEATH_FORTAX_13 :
        g_fMakeDBF = m_chkMakeDBF.GetCheck();
        theApp.WriteProfileInt(_T("Settings"), _T("DBFForTax"),  g_fMakeDBF);
        cbSel = m_cmbVBScript.GetCurSel();
        if ( cbSel != CB_ERR ) {
          m_cmbVBScript.GetLBText(cbSel, g_szVBScript);
          theApp.WriteProfileString(_T("Settings"), _T("VBSForTax"), g_szVBScript);
        }
        break;
      case ID_PRINT_DEATH_FORSOCPROT:
        g_fMakeDBF = m_chkMakeDBF.GetCheck();
        theApp.WriteProfileInt(_T("Settings"), _T("DBFForSoc"),  g_fMakeDBF);
        cbSel = m_cmbVBScript.GetCurSel();
        if ( cbSel != CB_ERR ) {
          m_cmbVBScript.GetLBText(cbSel, g_szVBScript);
          theApp.WriteProfileString(_T("Settings"), _T("VBSForSoc"), g_szVBScript);
        }
        break;
    }

    
    g_fPeriod = m_chkPeriod.GetCheck() ? TRUE : FALSE;
    g_odtFrom = m_From.GetDate();
    g_odtTill = m_Till.GetDate();
    if ( g_odtFrom.GetStatus() != COleDateTime::valid || g_odtTill.GetStatus() != COleDateTime::valid ) {
      AfxMessageBox(_T("Вказана неправільна дата."));
      return;
    }
    if ( false==g_fPeriod ) {
      OnSelchangeMonlist();
      g_odtFrom = m_From.GetDate();
      g_odtTill = m_Till.GetDate();
    }
    EndDialog(IDYES);
  }
}

void CMonthList::OnCommonlist() {
	m_PrintWhat = PRINT_ALLDOCS;
}

void CMonthList::OnPassports() {
	m_PrintWhat = PRINT_PASPORTS;
}

void CMonthList::OnMilcars() {
	m_PrintWhat = PRINT_MILCARS;
}

BOOL CMonthList::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintLists"));
  return true;
}

