// ElectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Erags.h"
#include "DataManager.h"
#include "Defaults.h"
#include "ElectDlg.h"
#include "RNames.h"

#include "..\ImpExp\ImpExpDll.h"

#include "..\Common\CyrString.h"
#include "..\Common\Elections.h"
#include "..\Common\FHelpers.h"
#include "..\Common\MDB.h"
#include "..\Common\Names.h"

#include "..\Controls\ProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SF_BIRTHES    0x01
#define SF_FATHERS    0x02
#define SF_MARRIAGES  0x04
#define SF_DIVORCES   0x08
#define SF_CHANGES    0x10
#define SF_DEATHES    0x20

int     g_Elect_SortOrderID = IDC_SORT_LIVE_PLACE;
int     g_Elect_FilterID    = IDC_DONT_FILTER;
CString g_szFilterRegion, g_szFilterDistrict, g_szFilterCity;

BOOL         g_fManySheets = false;

CDaoDatabase* OpenDB(LPCTSTR szFileName);
void CloseDB(CDaoDatabase* pDB);
CString GetCity(LPCTSTR szCity, bool fTypeCity=false);
BOOL ElectEncoder(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number);

BOOL IsRPDistrictInCity(CElectItem* pItem) {
  return IsDistrictInCity(pItem->m_szRPCountry, pItem->m_szRPRegion, pItem->m_szRPDistrict, pItem->m_szRPCity);
}

int CompareByDomicile(CElectItem *p1, CElectItem *p2) {
  int nCmpRes = CyrCompare(p1->m_szRPCountry, p2->m_szRPCountry);
  if ( nCmpRes ) return nCmpRes;
  nCmpRes = CyrCompare(p1->m_szRPRegion, p2->m_szRPRegion);
  if ( nCmpRes ) return nCmpRes;
  BOOL b1 = IsRPDistrictInCity(p1),
       b2 = IsRPDistrictInCity(p2);
  if ( b1 && b2 ) {
    nCmpRes = CyrCompare(p1->m_szRPCity, p2->m_szRPCity);
    if ( nCmpRes ) return nCmpRes;
    nCmpRes = CyrCompare(p1->m_szRPDistrict, p2->m_szRPDistrict);
    if ( nCmpRes ) return nCmpRes;
    return 0;
  }
  else if ( FALSE==b1 && FALSE==b2 ) {
    nCmpRes = CyrCompare(p1->m_szRPDistrict, p2->m_szRPDistrict);
    if ( nCmpRes ) return nCmpRes;
    nCmpRes = CyrCompare(p1->m_szRPCity, p2->m_szRPCity);
    if ( nCmpRes ) return nCmpRes;
    return 0;
  }
/************************************** : by VK at 17.09.2005 12:04:55 **\
  nCmpRes = CyrCompare(p1->m_szDistrict, p2->m_szDistrict);
  if ( nCmpRes ) return nCmpRes;
  nCmpRes = CyrCompare(p1->m_szCity, p2->m_szCity);
\************************************** : by VK at 17.09.2005 12:04:58 **/
  return (b2 - b1);
}

int ElectItemCompareByAfter(const void *a1, const void *a2) {
  CElectItem *p1 = *(CElectItem**)a1,
             *p2 = *(CElectItem**)a2;
  int ByDomicile = CompareByDomicile(p1, p2);
  if ( ByDomicile )
    return ByDomicile;
  return CyrCompare(p1->m_szNewSNP, p2->m_szNewSNP);
}
int ElectItemCompareByBefore(const void *a1, const void *a2) {
  CElectItem *p1 = *(CElectItem**)a1,
             *p2 = *(CElectItem**)a2;
  int ByDomicile = CompareByDomicile(p1, p2);
  if ( ByDomicile )
    return ByDomicile;
  return CyrCompare(p1->m_szOldSNP, p2->m_szOldSNP);
}
int ElectItemCompareByDate(const void *a1, const void *a2) {
  CElectItem *p1 = *(CElectItem**)a1,
             *p2 = *(CElectItem**)a2;

  int ByDomicile = CompareByDomicile(p1, p2);
  if ( ByDomicile )
    return ByDomicile;

  if ( p1->m_BirtDate.GetStatus()==COleDateTime::valid && 
       p2->m_BirtDate.GetStatus()==COleDateTime::valid ) {
    if ( p1->m_BirtDate < p2->m_BirtDate )
      return -1;
    if ( p1->m_BirtDate > p2->m_BirtDate )
      return 1;
    return 0;
  }
  if ( p1->m_BirtDate.GetStatus()!=COleDateTime::valid )
    return -1;
  return 1;
}
int ElectItemCompareByAddress(const void *a1, const void *a2) {
  CElectItem *p1 = *(CElectItem**)a1,
             *p2 = *(CElectItem**)a2;
  int ByDomicile = CompareByDomicile(p1, p2);
  if ( ByDomicile )
    return ByDomicile;
  return CyrCompare(p1->m_szAddress, p2->m_szAddress);
}

void FillSearchList(LPCTSTR szPath, CStringArray &sa, int fromYear, int tillYear){
  HANDLE hFindFile;
  BOOL bFind;
  WIN32_FIND_DATA findData;
  CString sPath = szPath; sPath += _T("\\");
  CString sMask = sPath + _T("*.*");
  CString sFileName, sFromY, sTillY;

  sFromY.Format(_T("%d"), fromYear);
  sTillY.Format(_T("%d"), tillYear);

  if((hFindFile = FindFirstFile(sMask, &findData)) != INVALID_HANDLE_VALUE){
    bFind = TRUE;
    while(bFind){
      if(findData.cFileName[0] != '.'){
        if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
          CString sNewPath = sPath + findData.cFileName;
          FillSearchList(sNewPath, sa, fromYear, tillYear);
        }
        sFileName = sPath + findData.cFileName;
        if(sFileName.Right(3).CompareNoCase(_T("er3")) == 0) {
          if ( sFileName.Find(sFromY)>=0 ||sFileName.Find(sTillY)>=0 )
            sa.Add( sFileName );
        }
      }
      bFind = FindNextFile(hFindFile, &findData);
    }
    FindClose(hFindFile);
  }
}


void CElectItemEx::SetNew(LPCTSTR szNewSurname, LPCTSTR szNewName, LPCTSTR szNewPatronymic) {
  m_szNewSurname    = szNewSurname;
  m_szNewName       = szNewName;
  m_szNewPatronymic = szNewPatronymic;
  m_szNewSNP = MakeFIO(szNewSurname, szNewName, szNewPatronymic);
}
void CElectItemEx::SetOld(LPCTSTR szOldSurname, LPCTSTR szOldName, LPCTSTR szOldPatronymic) {
  m_szOldSurname    = szOldSurname;
  m_szOldName       = szOldName;
  m_szOldPatronymic = szOldPatronymic;
  m_szOldSNP = MakeFIO(szOldSurname, szOldName, szOldPatronymic);
}
void CElectItemEx::SetBP(CDaoRecordset* pRS, LPCTSTR szFldCountry, LPCTSTR szFldRegion,
                         LPCTSTR szFldDistrict, LPCTSTR szFldCity) {
  m_szBPCountry  = GetFieldString(pRS, szFldCountry);
  m_szBPRegion   = GetFieldString(pRS, szFldRegion);
  m_szBPDistrict = GetFieldString(pRS, szFldDistrict);
  m_szBPCity     = GetFieldString(pRS, szFldCity);
  m_szBirthPlace = GetPlace(m_szBPCountry, m_szBPRegion, m_szBPDistrict, m_szBPCity);
}
void CElectItemEx::SetRP(CDaoRecordset* pRS, LPCTSTR szFldCountry, LPCTSTR szFldRegion,
                         LPCTSTR szFldDistrict, LPCTSTR szFldCity) {
  m_szRPCountry  = GetFieldString(pRS, szFldCountry);
  m_szRPRegion   = GetFieldString(pRS, szFldRegion);
  m_szRPDistrict = GetFieldString(pRS, szFldDistrict);
  m_szRPCity     = GetFieldString(pRS, szFldCity);
}
void CElectItemEx::SetAddress(CDaoRecordset* pRS, LPCTSTR szFldStreet, LPCTSTR szFldHouse, LPCTSTR szFldFlat) {
  m_szRPStreet = GetFieldString(pRS, szFldStreet);
  m_szRPHouse  = GetFieldString(pRS, szFldHouse);
  m_szRPFlat   = GetFieldString(pRS, szFldFlat);
  m_szAddress  = GetAddress(m_szRPCountry, m_szRPRegion, m_szRPCity, m_szRPDistrict, m_szRPStreet, m_szRPHouse, m_szRPFlat, true);
}

/*
CString GetAddress(CElectItem* pItem) {
  return ::GetAddress(pItem->m_szRPCountry, pItem->m_szRPRegion, pItem->m_szRPCity, pItem->m_szRPDistrict,
                      pItem->m_szRPStreet, pItem->m_szRPHouse, pItem->m_szRPFlat, true);

}

CString GetBirthPlace(CElectItem* pItem) {
  return GetPlace(pItem->m_szBPCountry, pItem->m_szBPRegion, pItem->m_szBPDistrict, pItem->m_szBPCity);
}
*/

BOOL IsInFilter(CElectItem* pItem) {
  switch(g_Elect_FilterID) {
    case  IDC_DONT_FILTER:  return TRUE;
    case  IDC_FILTER_YES:
      if ( g_szFilterRegion   != pItem->m_szRPRegion  ||
           g_szFilterDistrict != pItem->m_szRPDistrict ||
           g_szFilterCity     != GetCity(pItem->m_szRPCity) )
        return FALSE;
      return TRUE;
    case  IDC_FILTER_NO:
      if ( g_szFilterRegion   == pItem->m_szRPRegion   &&
           g_szFilterDistrict == pItem->m_szRPDistrict &&
           g_szFilterCity     == GetCity(pItem->m_szRPCity) )
        return FALSE;
      return TRUE;
  }
  return FALSE;
}

BOOL IsNeedAdd(const CString& sNew, const CString& sOld, LPCTSTR szCitizenship = NULL) {
  if ( sNew.IsEmpty() || sOld.IsEmpty() )
    return FALSE;
  if ( sNew==sOld )
    return FALSE;

  if ( szCitizenship ) {
    return (DBCompare(szCitizenship, _T("України"))==0);
  }
  return TRUE;
}

void FillByMarriages(CDaoDatabase* pDB, CPtrArray& array, CProgressCtrl* pProgress) {
  CDaoRecordset rs(pDB);
  try {
    rs.Open(dbOpenTable, _T("MARRIAGES"), dbReadOnly);
    if ( rs.IsOpen() ) {
      while(rs.IsEOF()==FALSE) {
        pProgress->SetPos( (int)rs.GetPercentPosition() );
        CString      sName, sPatronymic;
        COleDateTime odtDateReg = GetFieldOleDateTime(&rs, _T("DATEREG"));
        if ( odtDateReg.GetStatus()==COleDateTime::valid && g_odtFrom <= odtDateReg && odtDateReg <= g_odtTill ) {
          short Number        = GetFieldShort( &rs, _T("NUMBER") );
          // Man
          CString sCitizenship = GetFieldString(&rs, _T("MCITIZENSHIP"));
          CString sOldSurname  = GetFieldString(&rs, _T("MOLD_SURNAME"));
          CString sNewSurname  = GetFieldString(&rs, _T("MNEW_SURNAME"));
          if ( IsNeedAdd(sOldSurname, sNewSurname, sCitizenship) ) {
            sName       = GetFieldString(&rs, _T("MNAME") );
            sPatronymic = GetFieldString(&rs, _T("MPATRONYMIC") );
            CElectItemEx* pItem = new CElectItemEx();
            pItem->m_DateReg  = odtDateReg;
            pItem->m_Number   = Number;
            pItem->SetNew(sNewSurname, sName, sPatronymic);
            pItem->SetOld(sOldSurname, sName, sPatronymic);
            pItem->m_BirtDate = GetFieldOleDateTime(&rs, _T("MBIRTH_DATE"));
            pItem->SetBP(&rs, _T("MBIRTH_COUNTRY"), _T("MBIRTH_REGION"), _T("MBIRTH_DISTRICT"), _T("MBIRTH_CITY") );
            pItem->SetRP(&rs, _T("MRP_COUNTRY"), _T("MRP_REGION"), _T("MRP_DISTRICT"), _T("MRP_CITY") );
            if ( IsInFilter(pItem) ) {
              pItem->SetAddress(&rs, _T("MRP_STREET"), _T("MRP_HOUSE"), _T("MRP_FLAT"));
              pItem->m_szType = _T("Ш");
              array.Add( pItem );
            }
            else
              delete pItem;
          }
          // Woman
          sCitizenship = GetFieldString(&rs, _T("WCITIZENSHIP"));
          sOldSurname  = GetFieldString(&rs, _T("WOLD_SURNAME"));
          sNewSurname  = GetFieldString(&rs, _T("WNEW_SURNAME"));
          if ( IsNeedAdd(sOldSurname, sNewSurname, sCitizenship) ) {
            sName       = GetFieldString(&rs, _T("WNAME") );
            sPatronymic = GetFieldString(&rs, _T("WPATRONYMIC") );
            CElectItemEx* pItem = new CElectItemEx();
            pItem->m_DateReg  = odtDateReg;
            pItem->m_Number   = Number;
            pItem->SetNew(sNewSurname, sName, sPatronymic);
            pItem->SetOld(sOldSurname, sName, sPatronymic);
            pItem->m_BirtDate = GetFieldOleDateTime(&rs, _T("WBIRTH_DATE"));
            pItem->SetBP(&rs, _T("WBIRTH_COUNTRY"), _T("WBIRTH_REGION"), _T("WBIRTH_DISTRICT"), _T("WBIRTH_CITY"));
            pItem->SetRP(&rs, _T("WRP_COUNTRY"),    _T("WRP_REGION"),    _T("WRP_DISTRICT"),    _T("WRP_CITY"));
            if ( IsInFilter(pItem) ) {
              pItem->SetAddress(&rs, _T("WRP_STREET"), _T("WRP_HOUSE"), _T("WRP_FLAT"));
              pItem->m_szType = _T("Ш");
              array.Add( pItem );
            }
            else
              delete pItem;
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
  }
  catch(CDaoException* e){
    e->Delete();
  }
}
void FillByDivorces(CDaoDatabase* pDB, CPtrArray& array, CProgressCtrl* pProgress) {
  CDaoRecordset rs(pDB);
  try {
    rs.Open(dbOpenTable, _T("DIVORCES"), dbReadOnly);
    if ( rs.IsOpen() ) {
      while(rs.IsEOF()==FALSE) {
        pProgress->SetPos( (int)rs.GetPercentPosition() );
        CString      sName, sPatronymic;
        COleDateTime odtDateReg = GetFieldOleDateTime(&rs, _T("DATEREG"));
        if ( odtDateReg.GetStatus()==COleDateTime::valid && g_odtFrom <= odtDateReg && odtDateReg <= g_odtTill ) {
          short Number        = GetFieldShort( &rs, _T("NUMBER") );
          // Man
          CString sCitizenship = GetFieldString(&rs, _T("MCITIZENSHIP"));
          CString sOldSurname = GetFieldString(&rs, _T("MOLD_SURNAME") );
          CString sNewSurname = GetFieldString(&rs, _T("MNEW_SURNAME") );
          if ( IsNeedAdd(sOldSurname, sNewSurname, sCitizenship) ) {
            sName       = GetFieldString(&rs, _T("MNAME") );
            sPatronymic = GetFieldString(&rs, _T("MPATRONYMIC") );
            CElectItemEx* pItem = new CElectItemEx();
            pItem->m_DateReg  = odtDateReg;
            pItem->m_Number   = Number;
            pItem->SetNew(sNewSurname, sName, sPatronymic);
            pItem->SetOld(sOldSurname, sName, sPatronymic);
            pItem->m_BirtDate = GetFieldOleDateTime(&rs, _T("MBIRTH_DATE"));
            pItem->SetBP(&rs, _T("MBIRTH_COUNTRY"), _T("MBIRTH_REGION"), _T("MBIRTH_DISTRICT"), _T("MBIRTH_CITY"));
            pItem->SetRP(&rs, _T("MRP_COUNTRY"), _T("MRP_REGION"), _T("MRP_DISTRICT"), _T("MRP_CITY"));
            if ( IsInFilter(pItem) ) {
              pItem->SetAddress(&rs, _T("MRP_STREET"), _T("MRP_HOUSE"), _T("MRP_FLAT"));
              pItem->m_szType = _T("Р");
              array.Add( pItem );
            }
            else
              delete pItem;
          }
          // Woman
          sCitizenship = GetFieldString(&rs, _T("WCITIZENSHIP"));
          sOldSurname  = GetFieldString(&rs, _T("WOLD_SURNAME") );
          sNewSurname  = GetFieldString(&rs, _T("WNEW_SURNAME") );
          if ( IsNeedAdd(sOldSurname, sNewSurname, sCitizenship) ) {
            sName       = GetFieldString(&rs, _T("WNAME") );
            sPatronymic = GetFieldString(&rs, _T("WPATRONYMIC") );
            CElectItemEx* pItem = new CElectItemEx();
            pItem->m_DateReg  = odtDateReg;
            pItem->m_Number   = Number;
            pItem->SetNew(sNewSurname, sName, sPatronymic);
            pItem->SetOld(sOldSurname, sName, sPatronymic);
            pItem->m_BirtDate = GetFieldOleDateTime(&rs, _T("WBIRTH_DATE"));
            pItem->SetBP(&rs, _T("WBIRTH_COUNTRY"), _T("WBIRTH_REGION"), _T("WBIRTH_DISTRICT"), _T("WBIRTH_CITY"));
            pItem->SetRP(&rs, _T("WRP_COUNTRY"), _T("WRP_REGION"), _T("WRP_DISTRICT"), _T("WRP_CITY"));
            if ( IsInFilter(pItem) ) {
              pItem->SetAddress(&rs, _T("WRP_STREET"), _T("WRP_HOUSE"), _T("WRP_FLAT"));
              pItem->m_szType = _T("Р");
              array.Add( pItem );
            }
            else
              delete pItem;
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
  }
  catch(CDaoException* e){
    e->Delete();
  }
}
void FillByChanges(CDaoDatabase* pDB, CPtrArray& array, CProgressCtrl* pProgress) {
  CDaoRecordset rs(pDB);
  try {
    rs.Open(dbOpenTable, _T("CHANGES"), dbReadOnly);
    if ( rs.IsOpen() ) {
      while(rs.IsEOF()==FALSE) {
        pProgress->SetPos( (int)rs.GetPercentPosition() );
        CString      sName, sPatronymic;
        COleDateTime odtDateReg = GetFieldOleDateTime(&rs, _T("DATEREG"));
        if ( odtDateReg.GetStatus()==COleDateTime::valid && g_odtFrom <= odtDateReg && odtDateReg <= g_odtTill ) {
          short Number        = GetFieldShort( &rs, _T("NUMBER"));
          CString sOldSurname = GetFieldString(&rs, _T("OLDSURNAME"));
          CString sNewSurname = GetFieldString(&rs, _T("NEWSURNAME"));
          CString sOldName    = GetFieldString(&rs, _T("OLDNAME"));
          CString sNewName    = GetFieldString(&rs, _T("NEWNAME"));
          CString sOldPatronymic = GetFieldString(&rs, _T("OLDPATRONYMIC"));
          CString sNewPatronymic = GetFieldString(&rs, _T("NEWPATRONYMIC"));
          if ( IsNeedAdd(sOldSurname, sNewSurname) || IsNeedAdd(sOldName, sNewName) || IsNeedAdd(sOldPatronymic, sNewPatronymic) ) {
            CElectItemEx* pItem = new CElectItemEx();
            pItem->m_DateReg  = odtDateReg;
            pItem->m_Number   = Number;
            pItem->SetNew(sNewSurname, sNewName, sNewPatronymic);
            pItem->SetOld(sOldSurname, sOldName, sOldPatronymic);
            pItem->m_BirtDate = GetFieldOleDateTime(&rs, _T("BIRTH_DATE"));
            pItem->SetBP(&rs, _T("BIRTH_COUNTRY"), _T("BIRTH_REGION"), _T("BIRTH_DISTRICT"), _T("BIRTH_CITY"));
            pItem->SetRP(&rs, _T("COUNTRY"), _T("REGION"), _T("DISTRICT"), _T("CITY"));
            if ( IsInFilter(pItem) ) {
              pItem->SetAddress(&rs, _T("STREET"), _T("HOUSE"), _T("FLAT"));
              pItem->m_szType = _T("З");
              array.Add( pItem );
            }
            else
              delete pItem;
          }
        }
        rs.MoveNext();
      }
      rs.Close();
    }
  }
  catch(CDaoException* e){
    e->Delete();
  }
}
void FillByDeathes(CDaoDatabase* pDB, CPtrArray& array, CProgressCtrl* pProgress) {
  CDaoRecordset rs(pDB);
  try {
    rs.Open(dbOpenTable, _T("DEATHES"), dbReadOnly);
    if ( rs.IsOpen() ) {
      while(rs.IsEOF()==FALSE) {
        pProgress->SetPos( (int)rs.GetPercentPosition() );
        CString      sName, sPatronymic;
        COleDateTime odtDateReg = GetFieldOleDateTime(&rs, _T("DATEREG"));
        CString sCitizenship = GetFieldString(&rs, _T("CITIZENSHIP"));
        if ( odtDateReg.GetStatus()==COleDateTime::valid &&
             g_odtFrom <= odtDateReg && odtDateReg <= g_odtTill &&
             DBCompare(sCitizenship, _T("України"))==0 ) {
          short Number        = GetFieldShort( &rs, _T("NUMBER") );
          CString sSurname    = GetFieldString(&rs, _T("SURNAME") );
          CString sName       = GetFieldString(&rs, _T("NAME") );
          CString sPatronymic = GetFieldString(&rs, _T("PATRONYMIC") );
          CElectItemEx* pItem = new CElectItemEx();
          pItem->m_DateReg  = odtDateReg;
          pItem->m_Number   = Number;
          pItem->SetOld(sSurname, sName, sPatronymic);
          pItem->m_BirtDate   = GetFieldOleDateTime(&rs, _T("BIRTH_DATE"));
          pItem->m_DeathDate  = GetFieldOleDateTime(&rs, _T("DEATH_DATE"));
          pItem->SetBP(&rs, _T("BP_COUNTRY"), _T("BP_REGION"), _T("BP_DISTRICT"), _T("BP_CITY"));
          pItem->SetRP(&rs, _T("RP_COUNTRY"), _T("RP_REGION"), _T("RP_DISTRICT"), _T("RP_CITY"));
          if ( IsInFilter(pItem) ) {
            pItem->SetAddress(&rs, _T("RP_STREET"), _T("RP_HOUSE"), _T("RP_FLAT"));
            pItem->m_szType = _T("С");
            array.Add( pItem );
          }
          else
            delete pItem;
        }
        rs.MoveNext();
      }
      rs.Close();
    }
  }
  catch(CDaoException* e){
    e->Delete();
  }
}

/////////////////////////////////////////////////////////////////////////////
// CElectDlg dialog
CElectDlg::CElectDlg(UINT idDialog, CWnd* pParent /*=NULL*/)
	         :CDialogEx(idDialog, pParent) {
	//{{AFX_DATA_INIT(CElectDlg)
	//}}AFX_DATA_INIT
  m_IDD = idDialog;
}

CElectDlg::~CElectDlg() {
  for( int i(0); i < m_ElectItems.GetSize(); i++ ) {
    CElectItem* pItem = (CElectItem*)m_ElectItems.GetAt(i);
    delete pItem;
  }
  m_ElectItems.RemoveAll();
}

void CElectDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CElectDlg)
  DDX_Control(pDX, IDC_FRAME1, m_Frame1);
  DDX_Control(pDX, IDC_FRAME2, m_Frame2);
  DDX_Control(pDX, IDC_FRAME3, m_Frame3);
  DDX_Control(pDX, IDC_FRAME4, m_Frame4);
	DDX_Control(pDX, IDC_TILL, m_Till);
	DDX_Control(pDX, IDC_FROM, m_From);
  DDX_Control(pDX, IDC_DONT_FILTER, m_rbDontFilter);
  DDX_Control(pDX, IDC_FILTER_YES, m_rbFilterYes);
  DDX_Control(pDX, IDC_FILTER_NO, m_rbFilterNo);
  DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
  if ( IDD_ELECTION_CHANGES==m_IDD ) {
    DDX_Control(pDX, IDC_FRAME5, m_Frame5);
    DDX_Control(pDX, IDC_CHECK_MARRIAGES, m_chkMarriages);
    DDX_Control(pDX, IDC_CHECK_DIVORCES, m_chkDicorces);
    DDX_Control(pDX, IDC_CHECK_CHANGES, m_chkChanges);
    DDX_Control(pDX, IDC_SORT_PIB_AFTER,  m_rbSortPibAfter);
    DDX_Control(pDX, IDC_SORT_PIB_BEFORE, m_rbSortPibBefore);
    DDX_Control(pDX, IDC_SORT_BIRTH_DATE, m_rbSortBirthDate);
    DDX_Control(pDX, IDC_SORT_LIVE_PLACE, m_rbSortLivePlace);
  }
  else {
    DDX_Control(pDX, IDC_SORT_PIB,        m_rbSortPib);
    DDX_Control(pDX, IDC_SORT_BIRTH_DATE, m_rbSortBirthDate);
    DDX_Control(pDX, IDC_SORT_LIVE_PLACE, m_rbSortLivePlace);
  }
  DDX_Control(pDX, IDC_MAKE_XLS,    m_chkXLS);
  DDX_Control(pDX, IDC_TVK_EMPTY,   m_chkTVKDash);
  DDX_Control(pDX, IDC_ONE_SHEET,   m_rbOneSheet);
  DDX_Control(pDX, IDC_MANY_SHEETS, m_rbManySheets);
}

BEGIN_MESSAGE_MAP(CElectDlg, CDialogEx)
	//{{AFX_MSG_MAP(CElectDlg)
	ON_BN_CLICKED(IDYES, OnYes)
	//}}AFX_MSG_MAP
	ON_WM_HELPINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CElectDlg message handlers
BOOL CElectDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

  COleDateTime dt = COleDateTime::GetCurrentTime();
  COleDateTime dtFrom = dt, dtTill = dt;
  COleDateTimeSpan odsDay(1, 0, 0, 0);

  switch( dt.GetMonth() ) {
    case 1:
      dtFrom.SetDate(dt.GetYear()-1,  9,  1);
      dtTill.SetDate(dt.GetYear()-1, 11, 30);
      break;
    case 2: case 3: case 4:
      dtFrom.SetDate( dt.GetYear()-1, 12,  1);
      dtTill.SetDate( dt.GetYear()  ,  2, 28);
      dtTill += odsDay;
      if ( dtTill.GetDay() != 29 ) {
        dtTill -= odsDay;
      }
      break;
    case 5: case 6: case 7:
      dtFrom.SetDate( dt.GetYear(),  3,  1);
      dtTill.SetDate( dt.GetYear(),  5, 31);
      break;
    case 8: case 9: case 10:
      dtFrom.SetDate( dt.GetYear(),  6,  1);
      dtTill.SetDate( dt.GetYear(),  8, 31);
      break;
    case 11: case 12:
      dtFrom.SetDate( dt.GetYear(),  9,  1);
      dtTill.SetDate( dt.GetYear(), 11, 30);
      break;
  }

  m_From.SetDate(dtFrom);
  m_Till.SetDate(dtTill);

/*
  while (dt.GetDay() != 1 ) { dt -= odsDay;  }  dt -= odsDay;
  m_Till.SetDate(dt);
  while (dt.GetDay() != 1 ) { dt -= odsDay;  }
  m_From.SetDate(dt);

  #ifdef _DEBUG
    m_From.SetDate( COleDateTime(2007, 12,  1, 0, 0, 0) );
    m_Till.SetDate( COleDateTime(2008,  2, 29, 0, 0, 0) );
  #endif
*/
  BOOL fRadioOK = m_RadioIL.CreateTC(IDIL_RADIOXP, RGB(0xFF,0x00,0xFF));
  BOOL fCheckOK = m_CheckBoxIL.CreateTC(IDIL_CHECKBOXXP, RGB(0xFF,0x00,0xFF));

  //if ( fCheckOK ) {
  //  m_chkXLS.SetCheckBoxImageList(&m_CheckBoxIL);
  //}

  if ( IDD_ELECTION_CHANGES==m_IDD ) {
    CheckDlgButton(IDC_CHECK_MARRIAGES, 1);
    CheckDlgButton(IDC_CHECK_DIVORCES,  1);
    CheckDlgButton(IDC_CHECK_CHANGES,   1);
    CheckRadioButton(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE, IDC_SORT_PIB_BEFORE);
    if ( fCheckOK ) {
      m_chkMarriages.SetCheckBoxImageList(&m_CheckBoxIL);
      m_chkDicorces.SetCheckBoxImageList(&m_CheckBoxIL);
      m_chkChanges.SetCheckBoxImageList(&m_CheckBoxIL);
    }
    if ( fRadioOK ) {
      m_rbSortPibAfter.SetRadioImageList(&m_RadioIL);   m_rbSortPibAfter.SetRadio(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
      m_rbSortPibBefore.SetRadioImageList(&m_RadioIL);  m_rbSortPibBefore.SetRadio(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
      m_rbSortBirthDate.SetRadioImageList(&m_RadioIL);  m_rbSortBirthDate.SetRadio(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
      m_rbSortLivePlace.SetRadioImageList(&m_RadioIL);  m_rbSortLivePlace.SetRadio(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
    }
  }
  else {
    if ( fRadioOK ) {
      m_rbSortPib.SetRadioImageList(&m_RadioIL);        m_rbSortPib.SetRadio(IDC_SORT_PIB, IDC_SORT_LIVE_PLACE);
      m_rbSortBirthDate.SetRadioImageList(&m_RadioIL);  m_rbSortBirthDate.SetRadio(IDC_SORT_PIB, IDC_SORT_LIVE_PLACE);
      m_rbSortLivePlace.SetRadioImageList(&m_RadioIL);  m_rbSortLivePlace.SetRadio(IDC_SORT_PIB, IDC_SORT_LIVE_PLACE);
    }
    CheckRadioButton(IDC_SORT_PIB, IDC_SORT_LIVE_PLACE, IDC_SORT_PIB);
  }

  if ( fRadioOK ) {
    m_rbDontFilter.SetRadioImageList(&m_RadioIL); m_rbDontFilter.SetRadio(IDC_DONT_FILTER, IDC_FILTER_NO);
    m_rbFilterYes .SetRadioImageList(&m_RadioIL); m_rbFilterYes .SetRadio(IDC_DONT_FILTER, IDC_FILTER_NO);
    m_rbFilterNo  .SetRadioImageList(&m_RadioIL); m_rbFilterNo  .SetRadio(IDC_DONT_FILTER, IDC_FILTER_NO);
    m_rbOneSheet  .SetRadioImageList(&m_RadioIL); m_rbOneSheet  .SetRadio(IDC_ONE_SHEET, IDC_MANY_SHEETS);
    m_rbManySheets.SetRadioImageList(&m_RadioIL); m_rbManySheets.SetRadio(IDC_ONE_SHEET, IDC_MANY_SHEETS);
  }
  if ( fCheckOK ) {
    m_chkXLS.SetCheckBoxImageList(&m_CheckBoxIL);
    m_chkTVKDash.SetCheckBoxImageList(&m_CheckBoxIL);
  }

  CheckDlgButton(IDC_DONT_FILTER, 1);
  GetDlgItem(IDC_REGION)->SetWindowText( theIniCache.GetREGION() );
  GetDlgItem(IDC_DISTRICT)->SetWindowText( theIniCache.GetDISTRICT() );
  GetDlgItem(IDC_CITY)->SetWindowText( theIniCache.GetCITY() );

  m_SortID = IDC_SORT_LIVE_PLACE;

  CheckDlgButton(IDC_MAKE_XLS, g_fMakeXLS);
  CheckDlgButton(IDC_TVK_EMPTY, theIniCache.GetTVKDash());
  CheckRadioButton(IDC_ONE_SHEET, IDC_MANY_SHEETS, g_fManySheets ? IDC_MANY_SHEETS : IDC_ONE_SHEET);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CElectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
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

void CElectDlg::Sort() {
  if ( m_ElectItems.GetSize() ) {
    switch ( m_SortID ) {
      case IDC_SORT_PIB_AFTER:
        qsort( m_ElectItems.GetData(), m_ElectItems.GetSize(), sizeof(CElectItem*), ElectItemCompareByAfter);
        break;
      case IDC_SORT_PIB_BEFORE:
      case IDC_SORT_PIB:
        qsort( m_ElectItems.GetData(), m_ElectItems.GetSize(), sizeof(CElectItem*), ElectItemCompareByBefore);
        break;
      case IDC_SORT_BIRTH_DATE:
        qsort( m_ElectItems.GetData(), m_ElectItems.GetSize(), sizeof(CElectItem*), ElectItemCompareByDate);
        break;
      case IDC_SORT_LIVE_PLACE:
        qsort( m_ElectItems.GetData(), m_ElectItems.GetSize(), sizeof(CElectItem*), ElectItemCompareByAddress);
        break;
    }
  }
}

void CElectDlg::OnYes() {
  if ( UpdateData(TRUE) ) {
    g_odtFrom = m_From.GetDate();
    g_odtTill = m_Till.GetDate();
    if ( g_odtFrom.GetStatus() != COleDateTime::valid || g_odtTill.GetStatus() != COleDateTime::valid ) {
      AfxMessageBox(_T("Вказана неправільна дата."));
      return;
    }

    CWaitCursor wc;
    GetDlgItem(IDYES)->ShowWindow(SW_HIDE);
    GetDlgItem(IDNO)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_FILENAME)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_TABLE_NAME)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_PROGRESS)->ShowWindow(SW_SHOW);
    m_SortID = GetCheckedRadioButton(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
    g_Elect_FilterID = GetCheckedRadioButton(IDC_DONT_FILTER, IDC_FILTER_NO);

    g_fMakeXLS    = IsDlgButtonChecked(IDC_MAKE_XLS);
    theIniCache.SetTVKDash(IsDlgButtonChecked(IDC_TVK_EMPTY));
    g_fManySheets = (IDC_MANY_SHEETS==GetCheckedRadioButton(IDC_ONE_SHEET, IDC_MANY_SHEETS));

    GetDlgItem(IDC_REGION)->GetWindowText(g_szFilterRegion);
    g_szFilterRegion = Trim(g_szFilterRegion);

    GetDlgItem(IDC_DISTRICT)->GetWindowText(g_szFilterDistrict);
    g_szFilterDistrict = Trim(g_szFilterDistrict);

    GetDlgItem(IDC_CITY)->GetWindowText(g_szFilterCity);
    g_szFilterCity = GetCity(g_szFilterCity);

    int SeekFor = 0;
    if ( IDD_ELECTION_CHANGES==m_IDD ) {
      m_SortID = GetCheckedRadioButton(IDC_SORT_PIB_AFTER, IDC_SORT_LIVE_PLACE);
      if ( IsDlgButtonChecked(IDC_CHECK_MARRIAGES) )
        SeekFor |= SF_MARRIAGES;
      if ( IsDlgButtonChecked(IDC_CHECK_DIVORCES) )
        SeekFor |= SF_DIVORCES;
      if ( IsDlgButtonChecked(IDC_CHECK_CHANGES) )
        SeekFor |= SF_CHANGES;
    }
    else {
      m_SortID = GetCheckedRadioButton(IDC_SORT_PIB, IDC_SORT_LIVE_PLACE);
      SeekFor = SF_DEATHES;
    }
    if ( SeekFor ) {
      CStringArray sa;
      CString sPath = GetFilePath(theDataManager.GetYearDBName());
      FillSearchList(sPath, sa, g_odtFrom.GetYear(), g_odtTill.GetYear());

      m_Progress.SetRange32(0, 100);

      for( int i(0); i < sa.GetSize(); i++ ) {
        m_Progress.SetPos(0);
        CString szDBFile = sa.GetAt(i);
        CDaoDatabase* pDB = OpenDB(szDBFile);
        if(pDB && pDB->IsOpen()) {
          CString sMsg;
          sMsg.Format(_T("Оброблюється файл %s."), pDB->GetName() );
          GetDlgItem(IDC_FILENAME)->SetWindowText(sMsg);
          if ( SF_MARRIAGES & SeekFor ) {
            GetDlgItem(IDC_TABLE_NAME)->SetWindowText(_T("Оброблюються АЗ про ШЛЮБ"));
            FillByMarriages(pDB, m_ElectItems, &m_Progress);
          }
          if ( SF_DIVORCES & SeekFor ) {
            GetDlgItem(IDC_TABLE_NAME)->SetWindowText(_T("Оброблюються АЗ про РОЗІРВАННЯ ШЛЮБУ"));
            FillByDivorces(pDB, m_ElectItems, &m_Progress);
          }
          if ( SF_CHANGES & SeekFor ) {
            GetDlgItem(IDC_TABLE_NAME)->SetWindowText(_T("Оброблюються АЗ про ЗМІНУ ІМЕНІ"));
            FillByChanges(pDB, m_ElectItems, &m_Progress);
          }
          if ( SF_DEATHES & SeekFor ) {
            GetDlgItem(IDC_TABLE_NAME)->SetWindowText(_T("Оброблюються АЗ про СМЕРТЬ"));
            FillByDeathes(pDB, m_ElectItems, &m_Progress);
          }
          pDB->Close();
        }
      }
      m_Progress.SetPos(0);
      GetDlgItem(IDC_TABLE_NAME)->SetWindowText(_T("Сортируються знайдені записи"));
      Sort();

      EndDialog(IDYES);
      return;
    }
    EndDialog(IDNO);
  }
}

BOOL CElectDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
  theApp.OnHelp(_T("PrintDocs"), _T("#ElectLists"));
  return true;
}

void ElectionsToXLS(CElections* pElections, BOOL fDeath) {
  LPCTSTR pXLSTemplate = fDeath ? _T("p0578_2007_d6") : _T("p0578_2007_d7");
  CString szSource, szDest;
  szSource.Format(_T("%s\\%s.xls"), theApp.m_sTemplatePath, pXLSTemplate);
  szDest.Format(_T("%s\\%s за перiод з %02d.%02d.%04d по %02d.%02d.%04d.xls"),
                theApp.m_sOutPath, pXLSTemplate,
                g_odtFrom.GetDay(), g_odtFrom.GetMonth(), g_odtFrom.GetDay(),
                g_odtTill.GetDay(), g_odtTill.GetMonth(), g_odtTill.GetDay()
                );

  pElections->m_From = g_odtFrom;
  pElections->m_Till = g_odtTill;
  if ( false==CopyFile(szSource, szDest, false) ) {
    if ( false==FileExists(szSource) ) {
      CString szErr;
      szErr.Format(_T("Не можна створити XLS-файл: відсутній файл шаблону\n%s\n"), szSource);
      AfxMessageBox(szErr);
    }
    else { // probably szDest already opened
      CString szErr;
      szErr.Format(_T("Помилка при спробі створити файл %s.\nМожливо він вже відкритий якоюсь програмою."), szDest);
      AfxMessageBox(szErr);
    }
    return;
  }

  CWaitCursor wc;
  CProgressBar bar(_T("Генерується XLS-документ для ТВК"), 80, 100, true, 2);

  if ( MS_OFFICE==theApp.GetOffice() ) {
    E2Excel(&theElections, szDest, g_fManySheets, ElectEncoder, ProgressRoutine, &bar);
  }
  else {
    E2OCalc(&theElections, szDest, g_fManySheets, ElectEncoder, ProgressRoutine, &bar);
  }

/*
  typedef BOOL (WINAPI* pElectXLS)(CElections*, LPCTSTR szXLS, BOOL fMultiSheet, BOOL (* pElectEncoder)(TCHAR* pDestBuf, int BufSize, LPCTSTR szKey, CElectItem* pItem, int Number), void (* pProgressRoutine)(int nCount, int nProcessed, void* lpData), void* lpData);
  HINSTANCE hImpExp = LoadLibrary("ImpExp.dll");
  if( hImpExp ) {
    pElectXLS fElectXLS = (pElectXLS)GetProcAddress(hImpExp, _T("Elections"));
    if ( fElectXLS ) {
      fElectXLS(&theElections, szDest, g_fManySheets, ElectEncoder, ProgressRoutine, &bar);
    }
    FreeLibrary(hImpExp);
  }
*/
}