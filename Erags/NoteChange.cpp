// NoteChange.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"

#include "DataManager.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "FormChange.h"
#include "NoteChange.h"
#include "RNames.h"
#include "RSChanges.h"

#include "..\Common\MDB.h"
#include "..\Common\Names.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CString  g_szSurname_RV, g_szName_RV, g_szPatronymic_RV;
extern CString  g_szSurname_DV, g_szName_DV, g_szPatronymic_DV;
extern CString  g_szChanges, g_szChangeAct, g_szChangeDate, g_szChangeNumber;
extern CString  g_RagsTo, g_RagsWhere;

#define MAX_COLUMNS 5

/////////////////////////////////////////////////////////////////////////////
// CNoteChange dialog


CNoteChange::CNoteChange(CWnd* pParent /*=NULL*/)
          	:CDialogEx(CNoteChange::IDD, pParent) {
	//{{AFX_DATA_INIT(CNoteChange)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_pForm = (CFormChange*)pParent;
}


void CNoteChange::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNoteChange)
	DDX_Control(pDX, IDC_ACTLIST, m_listAct);
	DDX_Control(pDX, IDC_SURNAME_RV, m_Surname_RV);
	DDX_Control(pDX, IDC_NAME_RV, m_Name_RV);
  DDX_Control(pDX, IDC_FATHER_RV, m_Father_RV);
	DDX_Control(pDX, IDC_SURNAME_DV, m_Surname_DV);
	DDX_Control(pDX, IDC_FATHER_DV, m_Father_DV);
	DDX_Control(pDX, IDC_NAME_DV, m_Name_DV);
	DDX_Control(pDX, IDC_CITIZEN_RV, m_Citizen_RV);
	DDX_Control(pDX, IDC_CITIZEN_DV, m_Citizen_DV);
	DDX_Control(pDX, IDC_CHANGE, m_Change);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNoteChange, CDialogEx)
	//{{AFX_MSG_MAP(CNoteChange)
	ON_BN_CLICKED(IDYES, OnYes)
	ON_NOTIFY(NM_CLICK, IDC_ACTLIST, OnClickActlist)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()

void CNoteChange::AddToChange(int nGraph, LPCTSTR sOld, LPCTSTR sNew) {
  if( lstrcmp(sOld, sNew) != 0 ) {
    CString s, sChanges;
    sChanges = m_Change.GetText();
    if( !sChanges.IsEmpty() )
      sChanges += _T(", ");
    s.Format( _T("гр. %u виправити з \"%s\" на \"%s\""), nGraph, sOld, sNew );
    sChanges += s;
    m_Change.SetWindowText(sChanges);
  }
}
/////////////////////////////////////////////////////////////////////////////
// CNoteChange message handlers
BOOL CNoteChange::OnInitDialog() {
	CDialogEx::OnInitDialog();

  m_pForm->UpdateData(TRUE);
  GetDlgItem(IDYES)->EnableWindow(FALSE);
	
	// TODO: Add extra initialization here
  for ( int i(0); i < MAX_COLUMNS; i++ ) {
    LPCTSTR szColumns[MAX_COLUMNS] = {_T("Акт про..."), _T(" № "), _T("від"), _T("складений"), _T("на ім'я")};
    int aColWidth[MAX_COLUMNS] = {120, 40, 85, 360, 140};
    m_listAct.InsertColumn(i, szColumns[i], LVCFMT_LEFT, aColWidth[i]);
  }
  m_listAct.SetExtendedStyle(m_listAct.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

  CString sql;
  sql.Format(_T("SELECT TYPE, NUMBER, DATEREG, REGISTRAR, PERSON FROM CHANGESDEP WHERE ID=%ld"), m_pForm->m_pRSet->m_ID);
  CDaoRecordset rs(&theDataManager.m_dbYear);

  try {
    rs.Open(dbOpenDynaset, sql);
    int nItem = 0;
    while( !rs.IsEOF() ) {
      BYTE bType   = GetFieldByte(&rs, _T("TYPE") );
      m_listAct.InsertItem(nItem, CRSChanges::GetTypeName(bType) );
      m_listAct.SetItemText(nItem, 1, GetFieldString(&rs, _T("NUMBER")) );
      m_listAct.SetItemText(nItem, 2, GetFieldDate(&rs, _T("DATEREG"), false) );
      m_listAct.SetItemText(nItem, 3, GetFieldString(&rs, _T("REGISTRAR")) );
      m_listAct.SetItemText(nItem, 4, GetFieldString(&rs, _T("PERSON")) );
      rs.MoveNext();
    }
  }
  catch(CDaoException* e) {
    e->ReportError();
    e->Delete();
  }

  if ( m_pForm->m_fSex.IsOn() ) {
    m_Surname_DV. SetWindowText( ManSurname_DV(m_pForm->m_pRSet->m_OLDSURNAME) );
    m_Name_DV.    SetWindowText( ManName_DV(m_pForm->m_pRSet->m_OLDNAME) );
    m_Father_DV.  SetWindowText( ManFather_DV(m_pForm->m_pRSet->m_OLDPATRONYMIC) );
    m_Surname_RV. SetWindowText( ManSurname_RV(m_pForm->m_pRSet->m_OLDSURNAME) );
    m_Name_RV.    SetWindowText( ManName_RV(m_pForm->m_pRSet->m_OLDNAME) );
    m_Father_RV.  SetWindowText( ManFather_RV(m_pForm->m_pRSet->m_OLDPATRONYMIC) );

	  m_Citizen_DV.SetWindowText(_T(" Громадянину"));
	  m_Citizen_RV.SetWindowText(_T(" Громадянина"));
  }
  else {
    m_Surname_DV. SetWindowText( WomanSurname_DV(m_pForm->m_pRSet->m_OLDSURNAME) );
    m_Name_DV.    SetWindowText( WomanName_DV(m_pForm->m_pRSet->m_OLDNAME) );
    m_Father_DV.  SetWindowText( WomanFather_DV(m_pForm->m_pRSet->m_OLDPATRONYMIC) );
    m_Surname_RV. SetWindowText( WomanSurname_RV(m_pForm->m_pRSet->m_OLDSURNAME) );
    m_Name_RV.    SetWindowText( WomanName_RV(m_pForm->m_pRSet->m_OLDNAME) );
    m_Father_RV.  SetWindowText( WomanFather_RV(m_pForm->m_pRSet->m_OLDPATRONYMIC) );

	  m_Citizen_DV.SetWindowText(_T(" Громадянці"));
	  m_Citizen_RV.SetWindowText(_T(" Громадянки"));
  }

  AddToChange(1, m_pForm->m_pRSet->m_OLDSURNAME,     m_pForm->m_pRSet->m_NEWSURNAME);
  AddToChange(2, m_pForm->m_pRSet->m_OLDNAME,        m_pForm->m_pRSet->m_NEWNAME);
  AddToChange(3, m_pForm->m_pRSet->m_OLDPATRONYMIC,  m_pForm->m_pRSet->m_NEWPATRONYMIC);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNoteChange::OnClickActlist(NMHDR* pNMHDR, LRESULT* pResult) {
  POSITION pos = m_listAct.GetFirstSelectedItemPosition();
  if ( pos ) {
    int nItem = m_listAct.GetNextSelectedItem(pos);
    if ( nItem != -1 ) {
      g_szChangeAct    = m_listAct.GetItemText(nItem, 0);
      if ( g_szChangeAct==_T("шлюб") ) 
        g_szChangeAct = _T("шлюбу");
      else if ( g_szChangeAct==_T("смерть") ) 
        g_szChangeAct = _T("смерті");
      else {
        g_szChangeAct.Replace(_T("зміну"), _T("зміни "));
        g_szChangeAct.Replace(_T("переміну "), _T("переміни "));
      }

      g_szChangeNumber = m_listAct.GetItemText(nItem, 1);
      g_szChangeDate   = GetDateDDMMMYYYYr(m_listAct.GetItemText(nItem, 2));

      g_RagsTo = g_RagsWhere = m_listAct.GetItemText(nItem, 3);
      if ( theIniCache.IsChildRags( g_RagsTo ) ) {
        g_RagsTo = theIniCache.GetParent();
      }
      else if ( theIniCache.IsVyconcom(g_RagsTo) ) {
        g_RagsTo = theIniCache.GetVyconcomParent(g_RagsTo);
      }

      g_RagsTo = SVRagsC(g_RagsTo, RC_RV);
      g_RagsWhere = SVRagsC(g_RagsWhere, RC_MV);

      CString s = m_listAct.GetItemText(nItem, 4);
      if ( m_listAct.GetItemCount() > 1 && FALSE==s.IsEmpty() ) {
        BOOL fMale = GetMaleOrFemale(s);
        CString szSurname, szName, szPatronymic;

        GetCanonicalPIB(s, szSurname, szName, szPatronymic, fMale);
        if ( fMale ) {
          m_Surname_DV.SetWindowText( ManSurname_DV(szSurname) );
          m_Name_DV.   SetWindowText( ManName_DV(szName) );
          m_Father_DV. SetWindowText( ManFather_DV(szPatronymic) );
          m_Surname_RV.SetWindowText( ManSurname_RV(szSurname) );
          m_Name_RV.   SetWindowText( ManName_RV(szName) );
          m_Father_RV. SetWindowText( ManFather_RV(szPatronymic) );

      	  m_Citizen_DV.SetWindowText(_T(" Громадянину"));
	        m_Citizen_RV.SetWindowText(_T(" Громадянина"));

        }
        else {
          m_Surname_DV.SetWindowText( WomanSurname_DV(szSurname) );
          m_Name_DV.   SetWindowText( WomanName_DV(szName) );
          m_Father_DV. SetWindowText( WomanFather_DV(szPatronymic) );
          m_Surname_RV.SetWindowText( WomanSurname_RV(szSurname) );
          m_Name_RV.   SetWindowText( WomanName_RV(szName) );
          m_Father_RV. SetWindowText( WomanFather_RV(szPatronymic) );

          m_Citizen_DV.SetWindowText(_T(" Громадянці"));
	        m_Citizen_RV.SetWindowText(_T(" Громадянки"));

        }
/************************************** : by VK at 27.09.2005 23:27:00 **\
        m_Change.SetWindowText(_T(""));
        AddToChange(1, szSurname,     m_pForm->m_pSet->m_NEWSURNAME);
        AddToChange(2, szName,        m_pForm->m_pSet->m_NEWNAME);
        AddToChange(3, szPatronymic,  m_pForm->m_pSet->m_NEWPATRONYMIC);
\************************************** : by VK at 27.09.2005 23:27:04 **/
      }
      GetDlgItem(IDYES)->EnableWindow(TRUE);
    }
  }
	*pResult = 0;
}

void CNoteChange::OnYes() {
  UpdateData(TRUE);


  g_szSurname_RV      = m_Surname_RV.GetText();
  g_szName_RV         = m_Name_RV.GetText();
  g_szPatronymic_RV   = m_Father_RV.GetText();
  g_szSurname_DV      = m_Surname_DV.GetText();
  g_szName_DV         = m_Name_DV.GetText();
  g_szPatronymic_DV   = m_Father_DV.GetText();
  g_szChanges         = m_Change.GetText();

  CDialogEx::OnYes();
}

BOOL CNoteChange::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("RegChange2"));
  return true;
}
