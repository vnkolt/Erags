// RepairDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImpExp.h"
#include "RepairDlg.h"
#include "OldCaches.h"

#include "..\Common\CyrString.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString TypeOfCity(LPCTSTR szCity) {
  CString sCity = Trim(szCity), sRet;
  if (  sCity.Right(3)==_T(" м.") || sCity.Right(2)==_T(" м") || sCity.Right(6)==_T(" місто") )
    sRet = _T("місто");
  else if (  sCity.Right(4)==_T(" слщ") || sCity.Right(5)==_T(" с-ще") || sCity.Right(5)==_T(" смт.") || sCity.Right(4)==_T(" смт") || sCity.Right(7)==_T(" селище") )
    sRet = _T("селище");
  else if ( sCity.Right(2)==_T(" с") || sCity.Right(3)==_T(" с.") || sCity.Right(5)==_T(" село") )
    sRet = _T("село");
  else if ( sCity.Right(2)==_T(" х") || sCity.Right(3)==_T(" х.") || sCity.Right(4)==_T(" х-р") || sCity.Right(6)==_T(" хутір") )
    sRet = _T("хутір");
  else if (  sCity.Right(4)==_T(" ст.") || sCity.Right(7)==_T(" ст-ція") || sCity.Right(5)==_T(" с-ція") || sCity.Right(8)==_T(" станція") )
    sRet = _T("станція");
  else if ( sCity.Right(5)==_T(" с-ця") || sCity.Right(6)==_T(" ст-ця") || sCity.Right(8)==_T(" станиця") )
    sRet = _T("станиця");
  return sRet;
}
CString GetCity(LPCTSTR szCity, bool fTypeCity/*=false*/) {

  CString sCity = Trim(szCity);
  CString sType = TypeOfCity(sCity);
  int trimLen = 0;
  if ( !sType.IsEmpty() ) {
    trimLen = sCity.ReverseFind(' ');
  }
  if ( fTypeCity ) return sCity.Right(sCity.GetLength()-trimLen);
  return sCity.Mid(0, trimLen);
}



/////////////////////////////////////////////////////////////////////////////
// CRepairDlg dialog


CRepairDlg::CRepairDlg(LPCTSTR szFieldName, LPCTSTR szActName,
                       int nAct, COleDateTime DateReg,
                       LPCTSTR szNameOf, CWnd* pParent /*=NULL*/)
	         :CDialog(CRepairDlg::IDD, pParent) {
	//{{AFX_DATA_INIT(CRepairDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_szFieldName = szFieldName;
  m_szActName   = szActName;
  m_nAct        = nAct;
  m_DateReg     = DateReg;
  m_NameOf      = szNameOf;
}


void CRepairDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRepairDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRepairDlg, CDialog)
	//{{AFX_MSG_MAP(CRepairDlg)
	ON_EN_CHANGE(IDC_WHAT, OnChangeWhat)
	ON_BN_CLICKED(IDC_NOMORE, OnNomore)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRepairDlg message handlers

BOOL CRepairDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
  CString s;
  s.Format(_T("  В поле \"%s\" було введене значення, яке потім видалили зі списку.\r\n")
           _T("Підніміть актовий запис про %s № %d від %02d.%02d.%04d ")
           _T("та введіть %s в актовому записі.\r\n")
           _T("  У цільовому файлі БД буде внесене це значення.\r\n\r\n")
           _T("  Натисніть \"Скасувати\" щоб залишити це поле пустим."),
           m_szFieldName, m_szActName, m_nAct, m_DateReg.GetDay(), m_DateReg.GetMonth(), m_DateReg.GetYear(),
           m_NameOf);
  GetDlgItem(IDC_RAPAIR)->SetWindowText(s);
  GetDlgItem(IDC_LBL_WHAT)->SetWindowText(m_szFieldName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRepairDlg::OnChangeWhat() {
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
  GetDlgItem(IDC_WHAT)->GetWindowText(m_szFieldValue);
	GetDlgItem(IDOK)->EnableWindow(!m_szFieldValue.IsEmpty());
}

void CRepairDlg::OnNomore() 
{
	// TODO: Add your control notification handler code here
  g_fNoAskMore = IsDlgButtonChecked(IDC_NOMORE);
}


//
//
//
void AddToMemo(CDaoRecordset& rsNew, LPCTSTR szMemoFld, LPCTSTR szWhat, const CString& sValue) {
  CString sMemo = GetFieldString(&rsNew, szMemoFld);
  CString s;
  if ( sMemo.Find(sValue)==-1 ) {
    s.Format(_T(" {%s: %s}"), szWhat, sValue);
    sMemo += s;
    sMemo = Trim(sMemo);
    try {
      rsNew.SetFieldValue(szMemoFld, (LPCTSTR)sMemo);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetName(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
             LPCTSTR szWhat/*=NULL*/) {

  if ( 0==var.lVal )
    return;
  CString s = theNames.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("Ім'я, яке вказане"));
    if (IDOK==dlg.DoModal() ) {
      s = dlg.m_szFieldValue;
      theNames.Add(var.lVal, s);
    }
  }
  if ( false==s.IsEmpty() ) {
    if ( szWhat ) {
      AddToMemo(rsNew, szFieldName, szWhat, s);
    }
    else {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void SetPatronymic(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                   LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
                   LPCTSTR szWhat/*=NULL*/) {

  if ( 0==var.lVal )
    return;
  CString s = thePatronymics.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("по батькові, яке вказане"));
    if (IDOK==dlg.DoModal() ) {
      s = dlg.m_szFieldValue;
      thePatronymics.Add(var.lVal, s);
    }
  }
  if ( false==s.IsEmpty() ) {
    if ( szWhat ) {
      AddToMemo(rsNew, szFieldName, szWhat, s);
    }
    else {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void SetCountry(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.bVal )
    return;
  C2FieldRecord* pRecord = theCountries.Lookup((long)var.bVal);
  if ( (NULL==pRecord || pRecord->m_Value1.IsEmpty()) && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву держави, яка вказана"));
    if (IDOK==dlg.DoModal() ) {
      if ( NULL==pRecord ) {
        pRecord = new C2FieldRecord(dlg.m_szFieldValue, _T(""));
        theCountries.Add( (long)var.bVal, pRecord );
      }
      else {
        pRecord->m_Value1 = dlg.m_szFieldValue;
      }
    }
  }
  if ( pRecord && !pRecord->m_Value1.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Value1);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetRegion(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theRegions.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву області, яка вказана"));
    if (IDOK==dlg.DoModal() ) {
      s = dlg.m_szFieldValue;
      theRegions.Add(var.lVal, s);
    }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetCity(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  C2FieldRecord* pRecord = theCities.Lookup(var.lVal);

  if ( (NULL==pRecord || pRecord->m_Value1.IsEmpty()) && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву населенного пункту, який вказан"));
    if (IDOK==dlg.DoModal() ) {
      CString szCity = GetCity(dlg.m_szFieldValue, false),
              szType = TypeOfCity(dlg.m_szFieldValue);
      if ( NULL==pRecord ) {
        pRecord = new C2FieldRecord(szCity, szType);
        theCities.Add( (long)var.bVal, pRecord );
      }
      else {
        pRecord->m_Value1 = GetCity(dlg.m_szFieldValue, false);
        if ( pRecord->m_Value1.IsEmpty() ) {
          pRecord->m_Value2 = TypeOfCity(dlg.m_szFieldValue);
        }
      }
    }
  }
  if ( pRecord && false==pRecord->m_Value1.IsEmpty() ) {
    CString s;
    s.Format(_T("%s %s"), pRecord->m_Value1, pRecord->m_Value2);
    s.TrimRight();
    try {
      CDaoFieldInfo fi;
      rsNew.GetFieldInfo(szFieldName, fi);
      if ( fi.m_lSize < s.GetLength() )
        s = s.Left(fi.m_lSize);
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetDistrict(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                 LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theDistricts.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву району, який вказан"));
    if (IDOK==dlg.DoModal() ) {
      s = Trim(dlg.m_szFieldValue);
      theDistricts.Add(var.lVal, s);
    }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}
void SetStreet(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theStreets.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву вулиці, яка вказана"));
    if (IDOK==dlg.DoModal() ) {
      s = dlg.m_szFieldValue;
      theStreets.Add(var.lVal, s);
    }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetCitizen(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
                LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName ) {

  if ( 0==var.bVal )
    return;
  C2FieldRecord* pRecord = theCountries.Lookup((long)var.bVal);
  if ( (NULL==pRecord || pRecord->m_Value2.IsEmpty()) && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("громадянство, яке вказане"));
    if (IDOK==dlg.DoModal() ) {
      if ( NULL==pRecord ) {
        pRecord = new C2FieldRecord(_T(""), dlg.m_szFieldValue);
        theCountries.Add( (long)var.bVal, pRecord );
      }
      else {
        pRecord->m_Value2 = dlg.m_szFieldValue;
      }
    }
  }

  if ( pRecord ) {
    pRecord->m_Value2.Replace(_T("громадянин "), _T(""));
    pRecord->m_Value2.Replace(_T("громадянка "), _T(""));
    pRecord->m_Value2.Replace(_T("Громадянин "), _T(""));
    pRecord->m_Value2.Replace(_T("Громадянка "), _T(""));

    if ( !pRecord->m_Value2.IsEmpty() ) {
      try {
        rsNew.SetFieldValue(szFieldName, (LPCTSTR)pRecord->m_Value2);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void SetNation(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, BOOL fSex, COleVariant var,
               LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName,
               BOOL fToMemo/*=FALSE*/) {

  if ( 0==var.lVal )
    return;
  C2FieldRecord* pRecord = theNations.Lookup(var.lVal);

  if ( pRecord ) {
    CString s = fSex ? pRecord->m_Value1 : pRecord->m_Value2;

    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву національності, яка вказана"));
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        if ( fSex ) pRecord->m_Value1 = s;
        else        pRecord->m_Value2 = s;
      }
    }
    if ( !s.IsEmpty() ) {
      if ( fToMemo ) {
        AddToMemo(rsNew, szFieldName, szFieldDesc, s);
      }
      else {
        try {
          rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
            e->ReportError();
          #endif
          e->Delete();
        }
      }
    }
  }
}

void SetNationToMemo(CDaoRecordset& rsNew, CDaoRecordset& rsOld,
                     int NAZ, COleDateTime& DateReg, BOOL fSex,
                     COleVariant var, LPCTSTR szMemoFld, LPCTSTR szFieldDesc,
                     LPCTSTR szActName) {
  
  if ( 0==var.lVal )
    return;
  C2FieldRecord* pRecord = theNations.Lookup(var.lVal);
  if ( pRecord ) {
    CString s = fSex ? pRecord->m_Value1 : pRecord->m_Value2;

    if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву національності, яка вказана"));
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        if ( fSex ) pRecord->m_Value1 = s;
        else        pRecord->m_Value2 = s;
      }
    }
    if ( !s.IsEmpty() ) {
      COleVariant varMemo;
      rsNew.GetFieldValue(szMemoFld, varMemo);
      CString sMemo = V_BSTRT(&varMemo);
      CString sNat;
      sNat.Format(_T("{Національність: %s}"), s);
      if ( sMemo.Find(sNat)==-1 )
        sMemo += sNat;
      try {
        rsNew.SetFieldValue(szMemoFld, (LPCTSTR)sMemo);
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
          e->ReportError();
        #endif
        e->Delete();
      }
    }
  }
}

void SetRAGS(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theRAGSes.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("СКОРОЧЕНУ назву органу реєстрації в ОРУДНОМУ ВІДМІНКУ, який вказан"));
    if (IDOK==dlg.DoModal() ) {
      s = Trim(dlg.m_szFieldValue);
      if ( false==s.IsEmpty() ) {
        theRAGSes.Add(var.lVal, s);
      }
    }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}
void SetROVD(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theROVDs.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
    CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву органу внутрішніх справ в ОРУДНОМУ ВІДМІНКУ, який вказан"));
    if (IDOK==dlg.DoModal() ) {
      s = dlg.m_szFieldValue;
      theROVDs.Add(var.lVal, s);
    }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}

void SetBank(CDaoRecordset& rsNew, int NAZ, COleDateTime& DateReg, COleVariant var,
             LPCTSTR szFieldName, LPCTSTR szFieldDesc, LPCTSTR szActName) {

  if ( 0==var.lVal )
    return;
  CString s = theBanks.Lookup(var.lVal);
  if ( s.IsEmpty() && FALSE==g_fNoAskMore) {
      CRepairDlg dlg(szFieldDesc, szActName, NAZ, DateReg, _T("назву фінансової установи, яка вказана"));
      if (IDOK==dlg.DoModal() ) {
        s = dlg.m_szFieldValue;
        theBanks.Add(var.lVal, s);
      }
  }
  if ( !s.IsEmpty() ) {
    try {
      rsNew.SetFieldValue(szFieldName, (LPCTSTR)s);
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
    }
  }
}
