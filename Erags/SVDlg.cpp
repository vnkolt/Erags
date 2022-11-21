// SVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "SVDlg.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "Geography.h"
#include "EraForm.h"
#include "HelpMan.h"
#include "RList.h"
#include "RSBirthes.h"
#include "RNames.h"
#include "RegDlg.h"

#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

LPCTSTR szEOL = _T("\r\n");
extern CString g_sTmpBoss;
extern CString g_szMR_1, g_szMR_2, g_szMR_3;
extern CString g_szOR_1, g_szOR_2, g_szOR_3;
extern COleDateTime g_DateCert;
extern BOOL g_fSecondCert;
extern BOOL g_fStrikeOut;

extern CString g_sMSurname_OV;
extern CString g_sWSurname_OV;
extern CString g_sMName_OV;
extern CString g_sWName_OV;
extern CString g_sMPatronymic_OV;
extern CString g_sWPatronymic_OV;
extern CString g_SurnameTo, g_NameTo, g_PatronymicTo;

/////////////////////////////////////////////////////////////////////////////
// CSVDlg dialog
CSVDlg::CSVDlg(CWnd* pParent, UINT nIDTemplate, BOOL fSex/*=TRUE*/)
       :CDialogEx( nIDTemplate, pParent) {
	//{{AFX_DATA_INIT(CSVDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pParentForm = (CEraForm*)pParent;
  m_nIDTemplate = nIDTemplate;
  if ( g_sTmpBoss.IsEmpty())
    g_sTmpBoss = theIniCache.GetBoss();
  g_fSecondCert = FALSE;
  m_fSexTo = fSex;
  m_pRSBirthes = NULL;
  m_fNeedShowTooltip = FALSE;
}


void CSVDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSVDlg)
	DDX_Control(pDX, IDC_OWNER, m_edtOwner);
	DDX_Control(pDX, IDC_DATEOUT, m_DateCert);
	DDX_Control(pDX, IDC_BOSS, m_edtBoss);
  DDX_Control(pDX, IDC_REPEAT, m_chkRepeat);
  DDX_Control(pDX, IDC_AS_DATEREG, m_chkAsDateReg);
	//}}AFX_DATA_MAP
  DDX_OleDate(pDX, IDC_DATEOUT, m_DateCert, m_DateOut);
  if ( IDD_SVIDADOPTION != m_nIDTemplate ) {
  	DDX_Control(pDX, IDC_RTREE, m_RTree);
//	  DDX_Control(pDX, IDC_CHILDLIST, m_listChilds);
  	DDX_Control(pDX, IDC_REGPLACE, m_edtRegPlace);
  }
  switch(m_nIDTemplate) {
    case IDD_SVIDDIV:
      DDX_Control(pDX, IDC_MSURNAME_1,      m_MSURNAME_1);
      DDX_Control(pDX, IDC_MNAME_1,         m_MNAME_1);
      DDX_Control(pDX, IDC_MPATRONYMIC_1,   m_MPATRONYMIC_1);
      DDX_Control(pDX, IDC_WSURNAME_1,      m_WSURNAME_1);
      DDX_Control(pDX, IDC_WNAME_1,         m_WNAME_1);
      DDX_Control(pDX, IDC_WPATRONYMIC_1,   m_WPATRONYMIC_1);
      DDX_Control(pDX, IDC_SURNAME_TO,      m_SURNAME_TO);
      DDX_Control(pDX, IDC_NAME_TO,         m_NAME_TO);
      DDX_Control(pDX, IDC_PATRONYMIC_TO,   m_PATRONYMIC_TO);
      DDX_Control(pDX, IDC_TOLABEL,         m_ToLabel);
      break;
    case IDD_SVIDADOPTION:
      DDX_Control(pDX, IDC_VERDICT_OF,             m_VerdictOf);
      DDX_OleDate(pDX, IDC_VERDICT_DATE,           m_VerdictDate, m_dtVerdictDate);
      DDX_Control(pDX, IDC_VERDICT_NUMBER,         m_VerdictNumber);
      DDX_Control(pDX, IDC_NEWFATHER_SURNAME,      m_MSURNAME_1);
      DDX_Control(pDX, IDC_NEWFATHER_NAME,         m_MNAME_1);
      DDX_Control(pDX, IDC_NEWFATHER_PATRONYMIC,   m_MPATRONYMIC_1);
      DDX_Control(pDX, IDC_NEWMOTHER_SURNAME,      m_WSURNAME_1);
      DDX_Control(pDX, IDC_NEWMOTHER_NAME,         m_WNAME_1);
      DDX_Control(pDX, IDC_NEWMOTHER_PATRONYMIC,   m_WPATRONYMIC_1);
      DDX_Control(pDX, IDC_NEWSURNAME,             m_NewSurname);
      DDX_Control(pDX, IDC_NEWNAME,                m_NewName);
      DDX_Control(pDX, IDC_NEWPATRONYMIC,          m_NewPatronymic);
      DDX_OleDate(pDX, IDC_NEWBIRTH_DATE,          m_NewBirthDate, m_dtNewBirthDate);
      DDX_Control(pDX, IDC_BIRTH_COUNTRY, m_cmbBirthCountry);
      DDX_Control(pDX, IDC_BIRTH_REGION, m_cmbBirthRegion);
      DDX_Control(pDX, IDC_BIRTH_DISTRICT, m_cmbBirthDistrict);
      DDX_Control(pDX, IDC_BIRTH_CITY, m_cmbBirthCity);
      break;
  }
}

BEGIN_MESSAGE_MAP(CSVDlg, CDialogEx)
	//{{AFX_MSG_MAP(CSVDlg)
  ON_BN_CLICKED(IDC_AS_DATEREG, OnAsDateReg)
	ON_EN_UPDATE(IDC_REGPLACE, OnUpdateRegPlace)
	ON_EN_UPDATE(IDC_OWNER, OnUpdateOwner)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_NOTIFY(TVN_SELCHANGED, IDC_RTREE, OnSelchangedRTree)
  ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSVDlg message handlers

BOOL CSVDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();
  m_edtBoss.SetWindowText( g_sTmpBoss );
/*
  m_chkRepeat.SetText( _T("Повторне"), _T("Первинне") );
  m_chkRepeat.SetButtonStyle(BS_OWNERDRAW, TRUE);
*/
  m_DateOut = COleDateTime::GetCurrentTime();

  if ( m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF)) ) {
    m_chkRepeat.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkAsDateReg.SetCheckBoxImageList(&m_CheckBoxIL);
  }

  if ( IDD_SVIDADOPTION != m_nIDTemplate ) {
    HTREEITEM hItem = theRList.FillTreeCtrl(m_RTree, theApp.m_RagsID, NULL);
    if ( hItem ) {
      m_RTree.Expand(hItem, TVE_EXPAND);
      m_RTree.Select(hItem, TVGN_CARET);
    }
/************************************** : by VK at 22.07.2005 22:03:35 **\
    theIniCache.FillChildList(m_listChilds);
    m_listChilds.SetCurSel(0);
\************************************** : by VK at 22.07.2005 22:03:38 **/
  }

  CString s = DecodeRagsName( theIniCache.GetOwner(m_szFormSect) );
  if ( s.IsEmpty() ) {
    s = DecodeRagsName(theIniCache.GetRAGS());
    s = GetStringPart(s, 0);
  }
  if ( !s.IsEmpty() ) {
    m_edtOwner.SetWindowText( s );

    g_szOR_1 = GetTok(s, 0, szEOL );
    g_szOR_2 = GetTok(s, 1, szEOL );
    g_szOR_3 = GetTok(s, 2, szEOL );
  }

  switch( m_nIDTemplate) {
    case IDD_SVIDDIV:
      m_MSURNAME_1.SetWindowText( ManSurname_OV(m_sMSurname) );
      m_WSURNAME_1.SetWindowText( WomanSurname_OV(m_sWSurname) );
      m_MNAME_1.SetWindowText( ManName_OV(m_sMName) );
      m_WNAME_1.SetWindowText( WomanName_OV(m_sWName) );
      m_MPATRONYMIC_1.SetWindowText( ManFather_OV(m_sMPatronymic) );
      m_WPATRONYMIC_1.SetWindowText( WomanFather_OV(m_sWPatronymic) );

      m_ToLabel.SetFontBold( TRUE );

      if ( m_fSexTo) {
        m_ToLabel.SetTextColor( g_clrMaleForeColor );
        m_SURNAME_TO.SetWindowText( ManSurname_DV(m_sNewName) );
        m_NAME_TO.SetWindowText( ManName_DV(m_sMName) );
        m_PATRONYMIC_TO.SetWindowText( ManFather_DV(m_sMPatronymic) );
      }
      else {
        m_ToLabel.SetTextColor( g_clrFemaleForeColor );
        m_SURNAME_TO.SetWindowText( WomanSurname_DV(m_sNewName) );
        m_NAME_TO.SetWindowText( WomanName_DV(m_sWName) );
        m_PATRONYMIC_TO.SetWindowText( WomanFather_DV(m_sWPatronymic) );
      }
      break;
    case IDD_SVIDADOPTION:
      m_dtVerdictDate  = m_pRSBirthes->GetVerdictDate(m_ExtMemo);
      m_dtNewBirthDate = m_pRSBirthes->GetNewBirthDate(m_ExtMemo);

      m_MSURNAME_1.SetWindowText( m_sMSurname );
      m_MNAME_1.SetWindowText( m_sMName );
      m_MPATRONYMIC_1.SetWindowText( m_sMPatronymic );
      m_WSURNAME_1.SetWindowText( m_sWSurname );
      m_WNAME_1.SetWindowText( m_sWName );
      m_WPATRONYMIC_1.SetWindowText( m_sWPatronymic );
      if ( m_pRSBirthes ) {
        s = m_pRSBirthes->GetVerdictOf(m_ExtMemo);
        if ( s.IsEmpty() )
          m_VerdictOf.SetWindowText( theIniCache.GetByCourt() );
        else
          m_VerdictOf.SetWindowText( s );
        m_VerdictNumber.SetWindowText( m_pRSBirthes->GetVerdictNumber(m_ExtMemo) );
        m_NewSurname.SetWindowText( m_pRSBirthes->GetNewSurname(m_ExtMemo) );
        m_NewName.SetWindowText( m_pRSBirthes->GetNewName(m_ExtMemo) );
        m_NewPatronymic.SetWindowText( m_pRSBirthes->GetNewPatronymic(m_ExtMemo) );

        theGeoCache.FillCountryCB( m_cmbBirthCountry, m_pRSBirthes->GetNewBirthCountry(FALSE, m_ExtMemo) );
        theGeoCache.FillRegionCB( m_cmbBirthRegion, m_cmbBirthCountry, m_pRSBirthes->GetNewBirthRegion(FALSE, m_ExtMemo) );
        theGeoCache.FillDistrictCB( m_cmbBirthDistrict, m_cmbBirthRegion, m_pRSBirthes->GetNewBirthDistrict(FALSE, m_ExtMemo) );
        theGeoCache.FillCityCB( m_cmbBirthCity, m_cmbBirthRegion, m_cmbBirthDistrict, m_pRSBirthes->GetNewBirthCity(FALSE, m_ExtMemo) );

        m_cmbBirthCountry.SetDefault(theIniCache.GetBIRTH_BP_COUNTRY());
        m_cmbBirthRegion.SetDefault(theIniCache.GetBIRTH_BP_REGION());
        m_cmbBirthDistrict.SetDefault(theIniCache.GetBIRTH_BP_DISTRICT());
        m_cmbBirthCity.SetDefault(theIniCache.GetBIRTH_BP_CITY());

        /************************************** : by VK at 11.04.2005 7:22:46 **\
        s = m_pRSBirthes->GetNewBirthDate(m_ExtMemo);
        if ( s.IsEmpty() )
          s = GetDateDDMMYYYY(m_pRSBirthes->m_BIRTH_DATE);
        m_NewBirthDate.SetWindowText( s );
        \************************************** : by VK at 11.04.2005 7:22:51 **/
      }
      break;
  }
  UpdateData(FALSE);
  m_tooltip.Create(this);
  SetDefaults(&m_tooltip);
  theToolTipCache.Fill(this, _T("SvDlg"), &m_tooltip);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSVDlg::OnAsDateReg() {
  if ( IsDlgButtonChecked(IDC_AS_DATEREG) ) {
    CEraDateEdit* pEdit = (CEraDateEdit*)m_pParentForm->GetDlgItem(IDC_DATEREG);
    if ( pEdit) {
      m_DateCert.SetDate( pEdit->GetDate() );
    }
  }
  else {
    m_DateCert.SetDate( COleDateTime::GetCurrentTime() );
  }
}
void CSVDlg::OnUpdateRegPlace() {
  CString s;
  m_edtRegPlace.GetWindowText(s);
  if ( !s.IsEmpty() ) {
    HTREEITEM hItem = m_RTree.GetSelectedItem();
    if ( NULL==hItem )
      return;
    CRListRecord* pRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
    if ( NULL==pRecord ) {
      return;
    }
    g_szMR_1 = GetTok(s, 0, szEOL );
    g_szMR_2 = GetTok(s, 1, szEOL );
    g_szMR_3 = GetTok(s, 2, szEOL );
    theIniCache.SetRPChild(pRecord->m_ID, m_szFormSect, s);
  }
}

void CSVDlg::OnUpdateOwner() {
  CString s;
  m_edtOwner.GetWindowText(s);
  if ( !s.IsEmpty() ) {
    g_szOR_1 = GetTok(s, 0, szEOL );
    g_szOR_2 = GetTok(s, 1, szEOL );
    g_szOR_3 = GetTok(s, 2, szEOL );

    theIniCache.SetOwner(m_szFormSect, s);
    if ( s.Find(_T(" ради"))>=0 || s.Find(_T(" рада"))>=0 ) {
#ifndef FREE_LICENCE
      g_ValidOwner.dwVyconcom++;
      SaveGeoValidation();
#endif
    }
  }
}

BOOL CSVDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);

  switch( wCtrlId ) {
    case IDC_BIRTH_COUNTRY:   if ( CBN_SETFOCUS==wNotifyCode )  CEraForm::OnSetfocusCountry(m_cmbBirthCountry);
      break;
    case IDC_BIRTH_REGION:    if ( CBN_SETFOCUS==wNotifyCode )  CEraForm::OnSetfocusRegion(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthCity);
      break;
    case IDC_BIRTH_DISTRICT:  if ( CBN_SETFOCUS==wNotifyCode )  CEraForm::OnSetfocusDistrict(m_cmbBirthRegion, m_cmbBirthDistrict);
      break;
    case IDC_BIRTH_CITY:      if ( CBN_SETFOCUS==wNotifyCode )  CEraForm::OnSetfocusCity(m_cmbBirthCountry, m_cmbBirthRegion, m_cmbBirthDistrict, m_cmbBirthCity);
      break;
  }


  switch(wNotifyCode) {
    case BN_SETFOCUS:
    case EN_SETFOCUS:
    case CBN_SETFOCUS:
      m_tooltip.HideTooltip();
      break;
  }

/*
  if ( IDC_REPEAT==wCtrlId && BN_CLICKED==wNotifyCode) {
    BOOL bRet = CDialogEx::OnCommand(wParam, lParam);
    OnRepeat();
    return bRet;
  }
  if ( (IDYES==wCtrlId || IDOK==wCtrlId)&& BN_CLICKED==wNotifyCode) {
    UpdateData(TRUE);

    m_edtBoss.GetWindowText(g_sTmpBoss);

  	if ( m_fDivorce ) {
  	  m_MSURNAME_1.GetWindowText(g_sMSurname_OV);
      m_WSURNAME_1.GetWindowText(g_sWSurname_OV);
      m_MNAME_1.GetWindowText(g_sMName_OV);
      m_WNAME_1.GetWindowText(g_sWName_OV);
      m_MPATRONYMIC_1.GetWindowText(g_sMPatronymic_OV);
      m_WPATRONYMIC_1.GetWindowText(g_sWPatronymic_OV);
      m_SURNAME_TO.GetWindowText(g_SurnameTo);
      m_NAME_TO.GetWindowText(g_NameTo);
      m_PATRONYMIC_TO.GetWindowText(g_PatronymicTo);
	  }
  }
*/
	return CDialogEx::OnCommand(wParam, lParam);
}

void CSVDlg::OnYes() {
	// TODO: Add your control notification handler code here
  UpdateData(TRUE);

  g_fSecondCert = IsDlgButtonChecked(IDC_REPEAT);
  g_DateCert    = m_DateCert.GetDate();
  m_edtBoss.GetWindowText(g_sTmpBoss);

  switch( m_nIDTemplate) {
    case IDD_SVIDDIV:
      m_MSURNAME_1.GetWindowText(g_sMSurname_OV);
      m_WSURNAME_1.GetWindowText(g_sWSurname_OV);
      m_MNAME_1.GetWindowText(g_sMName_OV);
      m_WNAME_1.GetWindowText(g_sWName_OV);
      m_MPATRONYMIC_1.GetWindowText(g_sMPatronymic_OV);
      m_WPATRONYMIC_1.GetWindowText(g_sWPatronymic_OV);
      m_SURNAME_TO.GetWindowText(g_SurnameTo);
      m_NAME_TO.GetWindowText(g_NameTo);
      m_PATRONYMIC_TO.GetWindowText(g_PatronymicTo);
      break;
    case IDD_SVIDADOPTION:
      if ( m_pRSBirthes ) {
        m_pRSBirthes->SetNewSurname( m_NewSurname.GetText(), m_ExtMemo );
        m_pRSBirthes->SetNewName( m_NewName.GetText(), m_ExtMemo );
        m_pRSBirthes->SetNewPatronymic( m_NewPatronymic.GetText(), m_ExtMemo );

        m_pRSBirthes->SetVerdictOf( m_VerdictOf.GetText(), m_ExtMemo );
        m_pRSBirthes->SetVerdictDate( m_VerdictDate.GetDate(), m_ExtMemo );
        m_pRSBirthes->SetVerdictNumber( m_VerdictNumber.GetText(), m_ExtMemo );

        m_pRSBirthes->SetNewBirthDate( m_NewBirthDate.GetDate(), m_ExtMemo );
        m_pRSBirthes->SetNewBirthCountry( m_cmbBirthCountry.GetCurText(), m_ExtMemo );
        m_pRSBirthes->SetNewBirthRegion( m_cmbBirthRegion.GetCurText(), m_ExtMemo );
        m_pRSBirthes->SetNewBirthDistrict( m_cmbBirthDistrict.GetCurText(), m_ExtMemo );
        m_pRSBirthes->SetNewBirthCity( m_cmbBirthCity.GetCurText(), m_ExtMemo );

        m_NewSurname.SetWindowText( m_pRSBirthes->GetNewSurname(m_ExtMemo) );
        m_NewName.SetWindowText( m_pRSBirthes->GetNewName(m_ExtMemo) );
        m_NewPatronymic.SetWindowText( m_pRSBirthes->GetNewPatronymic(m_ExtMemo) );

        g_fStrikeOut = IsDlgButtonChecked(IDC_STRIKE_OUT);

      }
      break;
  }

  EndDialog(IDYES);	
}

void CSVDlg::OnSelchangedRTree(NMHDR* pNMHDR, LRESULT* pResult) {
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
  HTREEITEM hItem = m_RTree.GetSelectedItem();
  if ( NULL==hItem )
    return;

  CString sItemText = m_RTree.GetItemText(hItem);
  CRListRecord* pRecord = (CRListRecord*)m_RTree.GetItemData(hItem);
  if ( NULL==pRecord ) {
    return;
  }
  CString s = DecodeRagsName(theIniCache.GetRPChild(pRecord->m_ID, m_szFormSect));
  if ( !s.IsEmpty() ) {
    m_edtRegPlace.SetWindowText(s);
    g_szMR_1 = GetTok(s, 0, szEOL );
    g_szMR_2 = GetTok(s, 1, szEOL );
    g_szMR_3 = GetTok(s, 2, szEOL );
    if ( m_edtOwner.IsEmpty() ) {
      m_edtOwner.SetWindowText(s);
      g_szOR_1 = g_szMR_1;
      g_szOR_2 = g_szMR_2;
      g_szOR_3 = g_szMR_3;
    }
  }
  else {
    s = GetStringPart(DecodeRagsName(sItemText), 0);
    m_edtRegPlace.SetWindowText(s);
    OnUpdateRegPlace();
  }
	*pResult = 0;
}

BOOL CSVDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  m_tooltip.HideTooltip();
  if ( HELPINFO_WINDOW==pHelpInfo->iContextType ) {
    if ( GetKeyState(VK_F1) < 0 ) {
      theApp.OnHelp(_T("PrintDocs"), _T("#PrintCert"));
    }
    else {
      CWnd* pWnd = CWnd::FromHandle((HWND)pHelpInfo->hItemHandle);
      if ( pWnd ) {
        m_fNeedShowTooltip = TRUE;
        ShowHelpTooltipSetFocus(&m_tooltip, pWnd->GetParent(), _T("SvDlg"), pWnd, pHelpInfo->iCtrlId);
      }
    }
  }
/************************************** : by VK at 24.09.2004 22:14:15 **\
  int nButtons  = GetToolBarCtrl().GetButtonCount();
  ScreenToClient(&p);
  for( int i(0); i < nButtons; i++ ) {
    CRect rect;
    GetItemRect(i, &rect);
    if ( rect.PtInRect(p) )
      break;
  }
  if ( i < nButtons ) {
    ShowHelpTooltip(&m_tooltip, this, m_szName, GetItemID(i));
  }
\************************************** : by VK at 24.09.2004 22:14:21 **/
  return TRUE;
//  return CToolBar::OnHelpInfo(pHelpInfo);
}

BOOL CSVDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
  switch(message) {
    case WM_PARENTNOTIFY:
      m_tooltip.HideTooltip();
      break;
    case WM_NCPAINT:
      if ( FALSE==m_fNeedShowTooltip )
        m_tooltip.HideTooltip();
      m_fNeedShowTooltip = FALSE;
      break;
  }
  return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}