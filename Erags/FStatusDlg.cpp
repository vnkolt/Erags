// FStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "Caches.h"
#include "FStatusDlg.h"

#include "Defaults.h"
#include "RNames.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFStatusDlg dialog

COleDateTime  CFStatusDlg::m_odt;
CString       CFStatusDlg::m_szNumber;
CString       CFStatusDlg::m_szRags;
COleDateTime  CFStatusDlg::m_odtFrom;
COleDateTime  CFStatusDlg::m_odtTill;
BOOL          CFStatusDlg::m_fSex = FALSE;
CString       CFStatusDlg::m_szFullName1;
BOOL          CFStatusDlg::m_fCitizen;
CString       CFStatusDlg::m_szFullName2;
BOOL          CFStatusDlg::m_fUnmarried = TRUE;
COleDateTime  CFStatusDlg::m_odtBirth;
CString       CFStatusDlg::m_szBPlace;
BYTE          CFStatusDlg::m_bPassportType = 0;
CString       CFStatusDlg::m_szPassportSeria;
CString       CFStatusDlg::m_szPassportNumber;
COleDateTime  CFStatusDlg::m_odtPassportDate;
CString       CFStatusDlg::m_szPassportBy;


CFStatusDlg::CFStatusDlg(CWnd* pParent /*=NULL*/)
          	:CDialogEx(CFStatusDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CFStatusDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CFStatusDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFStatusDlg)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
  DDX_Control(pDX, IDC_FRAME4, m_Frame4);
  DDX_Control(pDX, IDC_FRAME5, m_Frame5);
	DDX_Control(pDX, IDC_UNMARRIED, m_Unmarried);
	DDX_Control(pDX, IDC_DATEV, m_DateV);
	DDX_Control(pDX, IDC_NDOV, m_NDov);
	DDX_Control(pDX, IDC_RAGS, m_Rags);
	DDX_Control(pDX, IDC_DFROM, m_DFrom);
	DDX_Control(pDX, IDC_DTILL, m_DTill);
	DDX_Control(pDX, IDC_SEX, m_Sex);
	DDX_Control(pDX, IDC_FULLNAME1, m_FullName1);
	DDX_Control(pDX, IDC_CITIZEN, m_Citizen);
	DDX_Control(pDX, IDC_FULLNAME2, m_FullName2);
	DDX_Control(pDX, IDC_DBIRTH, m_DBirth);
	DDX_Control(pDX, IDC_BPLACE, m_BPlace);
	DDX_Control(pDX, IDC_PASSPORT, m_PassportType);
	DDX_Control(pDX, IDC_PASSPORT_SERIA, m_PassportSeria);
	DDX_Control(pDX, IDC_PASSPORT_NUMBER, m_PassportNumber);
	DDX_Control(pDX, IDC_PASSPORT_DATE, m_PassportDate);
	DDX_Control(pDX, IDC_PASSPORT_BY, m_PassportBy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFStatusDlg, CDialogEx)
	//{{AFX_MSG_MAP(CFStatusDlg)
	ON_BN_CLICKED(IDC_SEX, OnSex)
	ON_EN_CHANGE(IDC_FULLNAME1, OnChangeFullname1)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFStatusDlg message handlers
BOOL CFStatusDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here
  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_Sex.SetCheckBoxImageList(&m_CheckBoxIL);
    m_Citizen.SetCheckBoxImageList(&m_CheckBoxIL);
    m_Unmarried.SetCheckBoxImageList(&m_CheckBoxIL);
  }

  COleDateTime odt = COleDateTime::GetCurrentTime();
  m_DTill.SetDate( odt );
  m_DateV.SetDate( odt );
  odt -= COleDateTimeSpan(365*5+1, 0, 0, 0);
  m_DFrom.SetDate( odt );

  m_Rags.SetWindowText( SVRagsC(theIniCache.GetRAGS(), RC_MV) );

  m_Sex.SetText(_T("ПІБ Заявника"), _T("ПІБ Заявниці") );
  m_Sex.SetForeColor(g_clrMaleForeColor, g_clrFemaleForeColor);
  m_Sex.SetButtonStyle(BS_OWNERDRAW, TRUE);
  m_Citizen.SetButtonStyle(BS_OWNERDRAW, TRUE);
  m_Unmarried.SetButtonStyle(BS_OWNERDRAW, TRUE);

  m_Sex.SetCheck(BST_UNCHECKED);
  m_Citizen.SetCheck(BST_CHECKED);
  m_Unmarried.SetCheck(BST_CHECKED);

  OnSex();
  m_Citizen.SetText(_T("громадянки України"), _T("особи без громадянтсва"));

  theMIAs.FillCombo( m_PassportBy, _T("")/*theIniCache.GetByROVD()*/ );
  m_PassportBy.SetDefault( theIniCache.GetByROVD() );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFStatusDlg::OnSex() {
	// TODO: Add your control notification handler code here
	if ( m_Sex.IsOn() ) {
/************************************** : by VK at 12.11.2005 12:59:07 **\
    m_Frame3.SetWindowText(_T("Заявник"));
\************************************** : by VK at 12.11.2005 12:59:09 **/
    m_Citizen.SetForeColor(g_clrMaleForeColor, g_clrMaleForeColor);
    m_Unmarried.SetForeColor(g_clrMaleForeColor, g_clrMaleForeColor);
    m_Citizen.SetText(_T("Громадянина України"),  _T("Особи без громадянства"));
    m_Unmarried.SetText(_T("У шлюбі НЕ перебував"), _T("Раніше ПЕРЕБУВАВ у шлюбі") );
  }
  else {
/************************************** : by VK at 12.11.2005 12:59:13 **\
    m_Frame3.SetWindowText(_T("Заявниця"));
\************************************** : by VK at 12.11.2005 12:59:15 **/
    m_Citizen.SetForeColor(g_clrFemaleForeColor, g_clrFemaleForeColor);
    m_Unmarried.SetForeColor(g_clrFemaleForeColor, g_clrFemaleForeColor);
    m_Citizen.SetText(_T("Громадянки України"), _T("Особи без громадянства"));
    m_Unmarried.SetText(_T("У шлюбі НЕ перебувала"), _T("Раніше ПЕРЕБУВАЛА у шлюбі") );
  }
/************************************** : by VK at 12.11.2005 12:59:19 **\
  CRect r;
  m_Frame3.GetWindowRect(&r);
  ScreenToClient(&r);
  InvalidateRect(&r);
\************************************** : by VK at 12.11.2005 12:59:22 **/
  m_Citizen.InvalidateRect(NULL);
  m_Unmarried.InvalidateRect(NULL);
}

BOOL CFStatusDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
  BOOL bResult = CDialogEx::OnCommand(wParam, lParam);
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);

  switch( wCtrlId ) {
    case IDC_SEX:
      if ( BN_CLICKED==wNotifyCode )
        OnSex();
      break;
    case IDC_BPLACE:
      if ( m_BPlace.IsEmpty() ) {
        CString s = GetAddress(theIniCache.GetCOUNTRY(),
                               theIniCache.GetREGION(),
                               theIniCache.GetCITY(),
                               theIniCache.GetDISTRICT(),
                               "", "", "", TRUE);
        m_BPlace.SetWindowText(s);
      }
      break;
    case IDC_PASSPORT_BY:
      if ( CBN_SETFOCUS==wNotifyCode ) {
        if ( m_PassportBy.IsEmpty() ) {
          if ( false==m_PassportSeria.IsEmpty() || false==m_PassportNumber.IsEmpty() ) {
            m_PassportBy.UpdateByDefault();
          }
        }
      }
      break;
  }
	
	return bResult;
}

void CFStatusDlg::OnChangeFullname1() {
  CString sFullName;
  GetDlgItem(IDC_FULLNAME1)->GetWindowText(sFullName);
  if ( !sFullName.IsEmpty() ) {
    sFullName = Trim(sFullName);
    sFullName = MakeCanonicalName(sFullName);

    if ( sFullName.GetLength() > 4 ) {
      CString sSurName, sName, sFather;

      sSurName = GetTok(sFullName, 0, " ");
      sName    = GetTok(sFullName, 1, " ");
      sFather  = GetTok(sFullName, 2, " ");

      if ( m_Sex.IsOn() ) {
        sFullName.Format(_T("%s %s %s"),
                         ManSurname_RV(sSurName),
                         ManName_RV(sName),
                         ManFather_RV(sFather) );
      }
      else {
        sFullName.Format(_T("%s %s %s"),
                         WomanSurname_RV(sSurName),
                         WomanName_RV(sName),
                         WomanFather_RV(sFather) );
      }
      GetDlgItem(IDC_FULLNAME2)->SetWindowText(sFullName);
    }
  }
}

void CFStatusDlg::OnYes() {
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
  m_odt              = m_DateV.GetDate();
  m_szNumber         = m_NDov.GetText();
  m_szRags           = m_Rags.GetText();
  m_odtFrom          = m_DFrom.GetDate();
  m_odtTill          = m_DTill.GetDate();
  m_fSex             = m_Sex.IsOn();
  m_szFullName1      = m_FullName1.GetText();
  m_fCitizen         = m_Citizen.IsOn();
  m_szFullName2      = m_FullName2.GetText();
  m_fUnmarried       = m_Unmarried.IsOn();
  m_odtBirth         = m_DBirth.GetDate();
  m_szBPlace         = m_BPlace.GetText();
  m_bPassportType    = (BYTE)m_PassportType.GetIndex();
  m_szPassportSeria  = m_PassportSeria.GetText();
  m_szPassportNumber = m_PassportNumber.GetText();
  m_odtPassportDate  = m_PassportDate.GetDate();
  m_szPassportBy     = m_PassportBy.GetCurText();

  EndDialog(IDYES);
}

BOOL CFStatusDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#PrintRefs"));
  return true;
}
