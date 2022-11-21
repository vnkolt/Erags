// DepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "erags.h"
#include "DepDlg.h"


#include "DataManager.h"
#include "DateFunc.h"
#include "FormChange.h"
#include "Defaults.h"
#include "RList.h"
#include "RNames.h"
#include "RSChanges.h"

#include "..\Common\MDB.h"
#include "..\Common\Names.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/************************************** : by VK at 13.09.2004 16:09:32 **\
CString RemoveToSentence(LPCTSTR szNotice) {
  CString s = szNotice;
  int nBegin = 0;
  while ( nBegin != - 1) {
    nBegin = s.Find(_T("В актовий запис про"), 0);
    if ( nBegin==-1 )
      nBegin = s.Find(_T("в актовий запис про"), 0);
    if ( nBegin >= 0 ) {
      int nEnd = s.Find(_T("на ім'я"), nBegin+1);
      if ( nEnd >= 0 ) {
        nEnd = s.Find(_T("."), nEnd+7);
        if ( nEnd >= 0 ) {
          CString szSentence = s.Mid(nBegin, nEnd-nBegin+1);
          s.Replace(szSentence, _T(""));
        }
      }
    }
  }

  return s;
}
\************************************** : by VK at 13.09.2004 16:09:36 **/

WORD uTypes[MAX_DEPROWS]   = { IDC_TYPE1,  IDC_TYPE2,  IDC_TYPE3,  IDC_TYPE4,  IDC_TYPE5,  IDC_TYPE6,  IDC_TYPE7,  IDC_TYPE8,  IDC_TYPE9,   IDC_TYPE10,  IDC_TYPE11,  IDC_TYPE12   };
WORD uNumbers[MAX_DEPROWS] = { IDC_NUMBER1,IDC_NUMBER2,IDC_NUMBER3,IDC_NUMBER4,IDC_NUMBER5,IDC_NUMBER6,IDC_NUMBER7,IDC_NUMBER8,IDC_NUMBER9, IDC_NUMBER10,IDC_NUMBER11,IDC_NUMBER12 };
WORD uDates[MAX_DEPROWS]   = { IDC_DATE1,  IDC_DATE2,  IDC_DATE3,  IDC_DATE4,  IDC_DATE5,  IDC_DATE6,  IDC_DATE7,  IDC_DATE8,  IDC_DATE9,   IDC_DATE10,  IDC_DATE11,  IDC_DATE12   };
WORD uRagses[MAX_DEPROWS]  = { IDC_RAGS1,  IDC_RAGS2,  IDC_RAGS3,  IDC_RAGS4,  IDC_RAGS5,  IDC_RAGS6,  IDC_RAGS7,  IDC_RAGS8,  IDC_RAGS9,   IDC_RAGS10,  IDC_RAGS11,  IDC_RAGS12   };
WORD uWho[MAX_DEPROWS]     = { IDC_WHO1,   IDC_WHO2,   IDC_WHO3,   IDC_WHO4,   IDC_WHO5,   IDC_WHO6,   IDC_WHO7,   IDC_WHO8,   IDC_WHO9,    IDC_WHO10,   IDC_WHO11,   IDC_WHO12    };

/////////////////////////////////////////////////////////////////////////////
// CDepDlg dialog


CDepDlg::CDepDlg(CWnd* pParent /*=NULL*/)
      	:CDialogEx(CDepDlg::IDD, pParent) {
  m_pForm = (CFormChange*)theApp.GetGetActiveForm();
	//{{AFX_DATA_INIT(CDepDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDepDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDepDlg)
	//}}AFX_DATA_MAP
  for( int i(0); i < MAX_DEPROWS; i++ ) {
	  DDX_Control(pDX, uTypes[i], m_Type[i]);
	  DDX_Control(pDX, uNumbers[i], m_Number[i]);
	  DDX_Control(pDX, uDates[i], m_Date[i]);
	  DDX_Control(pDX, uRagses[i], m_Rags[i]);
	  DDX_Control(pDX, uWho[i], m_Who[i]);
  }
}


BEGIN_MESSAGE_MAP(CDepDlg, CDialogEx)
	//{{AFX_MSG_MAP(CDepDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
  ON_WM_HELPINFO()
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CDepDlg message handlers
BOOL CDepDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  TCHAR* szTypes[7] = { _T("народження"),
                        _T("встановлення батьківства"),
                        _T("одруження"),
                        _T("шлюб"),
                        _T("розірвання шлюбу"),
                        _T("зміну імені"),
                        _T("переміну прізвища, імені, по батькові")
                      }; 
  int i;

  m_pForm->OnMove(0);  // Save form data
  //m_pForm->UpdateData(TRUE);  // Save form data
  for( i = 0; i < MAX_DEPROWS; i++ ) {
    for( int j(0); j < 7; j++ ) {
      m_Type[i].AddString( szTypes[j] );
    }
    m_Rags[i].SetDefault( theIniCache.GetRAGS() );
    theRList.FillRegCB( m_Rags[i], "");
  }


  CString sql;
  sql.Format(_T("SELECT TYPE, NUMBER, DATEREG, REGISTRAR, PERSON FROM CHANGESDEP WHERE ID=%ld"), m_pForm->m_pRSet->m_ID);
  CDaoRecordset rs(&theDataManager.m_dbYear);
  i = 0;
  try {
    rs.Open(dbOpenDynaset, sql);
    while( !rs.IsEOF() ) {
      if ( MAX_DEPROWS==i )
        break;
      COleVariant ovar;
      BYTE         bType   = GetFieldByte(&rs, _T("TYPE") );
      m_Type[i].SelectString(-1, CRSChanges::GetTypeName(bType) );
      CString      sNumber = GetFieldString(&rs, _T("NUMBER") );
      m_Number[i].SetWindowText(sNumber);
      COleDateTime odt     = rs.GetFieldValue(_T("DATEREG"));
      m_Date[i].SetDate( odt );

      CString      sBy     = GetFieldString(&rs, _T("REGISTRAR") );
      m_Rags[i].SetCurText( sBy );

      CString     sWho     = GetFieldString(&rs, _T("PERSON") );
      m_Who[i].SetWindowText( sWho );

      rs.MoveNext();
      i++;
    }
    rs.Close();
  }
  catch(CDaoException* e) {
    e->ReportError();
    e->Delete();
  }


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDepDlg::UpdateWho( int nIndex ) {
  if ( m_Who[nIndex].IsEmpty() ) {
    CString sSurName    = m_pForm->m_pRSet->m_OLDSURNAME;
    CString sName       = m_pForm->m_pRSet->m_OLDNAME;
    CString sPatronymic = m_pForm->m_pRSet->m_OLDPATRONYMIC;
    CString sWho = MakeFullName(sSurName, sName, sPatronymic, m_pForm->m_pRSet->m_SEX, RC_RV);
    m_Who[nIndex].SetWindowText(sWho);
  }
}

BOOL CDepDlg::OnCommand(WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  WORD wNotifyCode = HIWORD(wParam);
  WORD wCtrlId = LOWORD(wParam);
  if ( CBN_SETFOCUS==wNotifyCode ) {
    for( int i(0); i < MAX_DEPROWS; i++ ) {
      if ( uRagses[i]==wCtrlId ) {
        m_Rags[i].UpdateByDefault();
        break;
      }
    }
  }
  else if ( EN_SETFOCUS==wNotifyCode ) {
    for( int i(0); i < MAX_DEPROWS; i++ ) {
      if ( uWho[i]==wCtrlId ) {
        UpdateWho(i);
        break;
      }
    }
  }
	
	return CDialogEx::OnCommand(wParam, lParam);
}

void CDepDlg::OnYes() {
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

  CString sql;
  sql.Format(_T("DELETE FROM CHANGESDEP WHERE ID=%ld"), m_pForm->m_pRSet->m_ID);
  try {
    theDataManager.m_dbYear.Execute(sql);
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    e->Delete();
  }

  CDaoRecordset rs(&theDataManager.m_dbYear);
  try {
    rs.Open(dbOpenDynaset, _T("SELECT * FROM CHANGESDEP"));

    CString sTo;
    for( int i(0); i < MAX_DEPROWS; i++ ) {
      long ID = m_pForm->m_pRSet->m_ID;
      CString sAct = m_Type[i].GetCurText();
      if ( sAct.IsEmpty() )
        break;

      BYTE bType = (BYTE)sAct.GetAt(0);
      SHORT uNumber = (SHORT)atoi(m_Number[i].GetText());
      COleDateTime odt = m_Date[i].GetDate();
      CString sRags = m_Rags[i].GetCurText();
      if ( sRags.IsEmpty() )
        break;

      CString sWho = m_Who[i].GetText();

      CString s;
      s.Format(_T("в актовий запис про %s № %d від %s складений %s на ім'я %s; "),
                  sAct, uNumber, GetDateDDMMMYYYYr(odt), SVRagsC(sRags, RC_OV), sWho );
      sTo += s;

      if ( rs.CanAppend() ) {
        rs.AddNew();
        rs.SetFieldValue(_T("ID"), COleVariant(ID, VT_I4) );
        rs.SetFieldValue(_T("TYPE"), COleVariant(bType) );
        rs.SetFieldValue(_T("NUMBER"), COleVariant(uNumber, VT_I2) );
        rs.SetFieldValue(_T("DATEREG"), odt );
        rs.SetFieldValue(_T("REGISTRAR"), (LPCTSTR)sRags );
        rs.SetFieldValue(_T("PERSON"), (LPCTSTR)sWho );
        rs.Update();
      }
    }
    rs.Close();
    sTo.Replace(_T("  "), _T(" "));
    sTo = Trim(sTo);
    sTo.TrimRight(';');
    CString sNewNotice;
    sNewNotice.Format(_T("Виправлення внесені:\r\n%s."), sTo);
    m_pForm->m_Notice.SetWindowText( sNewNotice );
  }
  catch(CDaoException* e) {
    e->Delete();
  }

  m_pForm->OnMove(0);  // Save form data
  CDialogEx::OnYes();
}

BOOL CDepDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("RegChange2"));
  return true;
}
