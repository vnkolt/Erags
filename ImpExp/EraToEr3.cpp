//
// EraToEr3.cpp
//
#include "stdafx.h"
#include "ImpExp.h"
#include "EraToEr3.h"
#include "OldCaches.h"

#include "RepairDlg.h"
#include "DefBirth.h"

#include "..\Common\CyrString.h"
//#include "..\Common\DaoErr.h"
#include "..\Common\DaoErr.h"
#include "..\Common\DB.h"
#include "..\Common\MDB.h"
#include "..\Common\FHelpers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL IsEr3RecordPresent(CDaoRecordset& rs, const SHORT& Number, const COleDateTime& DateReg, const CString& Surname, LPCTSTR szSurnameFieldName);

#define MP_CLEAR  0x3FFFFFFF  // 00111111111111111111111111111111b
#define WP_CLEAR  0xCFFFFFFF  // 11001111111111111111111111111111b

#define MARRIAGE_PAZ    0x200
#define MARRIAGE_MBIRTH 0x400
#define MARRIAGE_WBIRTH 0x800

#define DIVORCE_NATW     0x0008
#define DIVORCE_CITW     0x0020
#define DIVORCE_FW       0x0040
#define DIVORCE_VMK      0x0400
#define DIVORCE_VMR      0x0800
#define DIVORCE_VWK      0x1000
#define DIVORCE_VWR      0x2000
#define DIVORCE_MBIRTH   0x4000
#define DIVORCE_WBIRTH   0x8000
#define DIVORCE_PAZ     0x10000


WORD GetDocType(DWORD dwFlags, BOOL bSex) {
  WORD wShift;
  if(bSex){
    wShift = 30;
    dwFlags &= ~MP_CLEAR;
  }
  else{
    wShift = 28;
    dwFlags &= ~WP_CLEAR;
  }
  return (WORD)(dwFlags >> wShift);
}

WORD PASCAL EXPORT GetOldPassportType(DWORD dwFlags, BOOL bSex){
  return GetDocType(dwFlags, bSex);
}


BOOL IsEraDatabaseValid(CDaoDatabase& db) {
  return ( IsTablePresent(db, _T("Акты_о_рождении")) && 
           IsTablePresent(db, _T("Акты_о_браке"))    &&
           IsTablePresent(db, _T("Акты_о_разводе"))  &&
           // IsTablePresent(db, _T("Акты_о_перемене")) && В некоторых старых БД этой таблицы может не быть
           IsTablePresent(db, _T("Акты_о_смерти"))
         );
}

BOOL OpenOldDB(CDaoDatabase& db, LPCTSTR szFileName) {
  BOOL fRet = true;
  try {
    db.Open(szFileName, false, true);
    if ( false==IsEraDatabaseValid(db) ) {
      db.Close();
      fRet = false;
    }
  }
  catch(CDaoException* e) {
    e->Delete();
    fRet = false;
  }
  if ( false==fRet ) { // Не получилось открыть без пароля?
    CString sPWD;
    sPWD.Format(_T(";PWD=%s"), _T("августдекабрь"));
    try {
      db.Open(szFileName, false, true, sPWD);
      if ( false==IsEraDatabaseValid(db) ) {
        db.Close();
        fRet = false;
      }
    }
    catch(CDaoException* e) {
      e->Delete();
      fRet = false;
    }
  }
  return fRet;
}

long ImportFromOldBirth() {
  static LPCTSTR szActName = _T("НАРОДЖЕННЯ");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM Акты_о_рождении");

  long nImportedRecords = 0;

  CString s;

  s.Format(_T("%s\\Defaults.ini"), GetFilePath(g_SourceDB.GetName()));
  ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_REGION"), _T(""), sCHILD_BP_REGION.GetBuffer(64), 64, s);
  sCHILD_BP_REGION.ReleaseBuffer();
  ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_DISTRICT"), _T(""), sCHILD_BP_DISTRICT.GetBuffer(64), 64, s);
  sCHILD_BP_DISTRICT.ReleaseBuffer();
  ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_CITY"), _T(""), sCHILD_BP_CITY.GetBuffer(64), 64, s);
  sCHILD_BP_CITY.ReleaseBuffer();

  if ( sCHILD_BP_COUNTRY.IsEmpty() ) {
    sCHILD_BP_COUNTRY = g_szCountry;
  }
  if ( sCHILD_BP_REGION.IsEmpty() ) {
    sCHILD_BP_REGION = g_szRegion;
  }
  if ( sCHILD_BP_CITY.IsEmpty() ) {
    sCHILD_BP_CITY = g_szCity;
  }
  if ( sCHILD_BP_DISTRICT.IsEmpty() ) {
    sCHILD_BP_DISTRICT = g_szDistrict;
  }

  CDefBirth dlg(NULL);
  dlg.DoModal();

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[BIRTHES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));
    int nFields = rsSrc.GetFieldCount();

    while ( !rsSrc.IsEOF() ) {
      short   Number = -1;
      CString Surname;
      COleVariant var;
      COleDateTime DateReg;
      DWORD dwFlags = 0;
      VARIANT_BOOL bSex = FALSE;

      CString szMPassportSeria, szMPassportNumber, szMPassportBy;
      CString szWPassportSeria, szWPassportNumber, szWPassportBy;
      COleDateTime MPassportDate, WPassportDate;
      CString szExtMemo;
      BOOL fDeclarantPassport = false;

      int nImage = MT_GIRL;

      g_pProgress->OffsetPos(1);

      try {
        var = rsSrc.GetFieldValue(_T("ФамилияС"));
        Surname = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("Номер"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("ДатаРег"));
        if ( GetFieldBool(&rsSrc, _T("Пол")) ) {
          nImage++;
        }
      } 
      catch(CDaoException* e) {
        e->Delete();
        OnMessage(MT_ERROR, FormatDaoError(e));
      }
      if ( g_fNoEmpty && Surname.IsEmpty() ) {     // Фамилия пуста?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// Год регистрации не совпадает?
        goto _Next;
      }
      if ( g_fNoExist ) { // Добавлять только несуществующие записи?
        if ( IsEr3RecordPresent(rsDst, Number, DateReg, Surname, _T("SURNAME")) ) {
          goto _Next;
        }
      }

      rsDst.AddNew();

      try {
        BOOL fMR = FALSE;
        long lOldName = 0, lOldPatronymic = 0;
        for( int i(0); i < nFields; i++ ) {
          CDaoFieldInfo fi;
          rsSrc.GetFieldInfo(i, fi);
          var = rsSrc.GetFieldValue(i);
          if ( fi.m_strName==_T("ДатаРег") ) {
            DateReg = var;
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("Номер") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("НомерАУО") ) {
          }
          else if ( fi.m_strName==_T("Флаги") ) {
            dwFlags = (DWORD)var.lVal;
            rsDst.SetFieldValue(_T("RENEW"), var);
          }
          else if ( fi.m_strName==_T("ПАЗ") ) {
          }
          else if ( fi.m_strName==_T("ДатаРег") ) {
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("ДатаРегАУО") ) {
          }
          else if ( fi.m_strName==_T("Пол") ) {
            bSex = var.boolVal;
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("Отцовство") ) {
          }
          else if ( fi.m_strName==_T("НомерДок") ) {
            s = GetFieldString(&rsSrc, fi.m_strName);
            if ( !s.IsEmpty() )
              rsDst.SetFieldValue(_T("SOURCE_NDOC"), (LPCTSTR)s);
          }
          else if ( fi.m_strName==_T("ДатаДок") ) {
            rsDst.SetFieldValue(_T("SOURCE_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_РАГС") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("SOURCE_BY"), _T("Ким складено АЗ про шлюб"), szActName);
          }
          else if ( fi.m_strName==_T("НомерСЗР") ) {
          }
          else if ( fi.m_strName==_T("ДатаСЗР") ) {
          }
          else if ( fi.m_strName==_T("ФамилияС") ) {
            rsDst.SetFieldValue(_T("SURNAME"), var);
          }
          else if ( fi.m_strName==_T("ФамилияН") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              s.Format(_T("{Нове прізвище: %s} "), Trim(V_BSTRT(&var)));
              szExtMemo += s;
            }
          }
          else if ( fi.m_strName==_T("сИмя") ) {
            lOldName = var.lVal;
            SetName(rsDst, Number, DateReg, var, _T("NAME"), _T("Ім'я новонародженого"), szActName);
          }
          else if ( fi.m_strName==_T("сИмяН") && var.lVal!=lOldName) {
            SetName(rsDst, Number, DateReg, var, _T("EXTNOTES"), _T("Нове ім'я новонародженого"), szActName, _T("Нове Ім'я"));
          }
          else if ( fi.m_strName==_T("сОтчество") ) {
            lOldPatronymic = var.lVal;
            SetPatronymic(rsDst, Number, DateReg, var, _T("PATRONYMIC"), _T("По батькові новонародженого"), szActName);
          }
          else if ( fi.m_strName==_T("сОтчествоН") && var.lVal != lOldPatronymic) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("EXTNOTES"), _T("Нове по батькові новонародженого"), szActName, _T("Нове по батькові"));
          }
          else if ( fi.m_strName==_T("ДРождения") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("фМР") ) {
            fMR = var.boolVal;
          }
          else if ( fi.m_strName==_T("с_МР_Г") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_CITY.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_CITY"), (LPCTSTR)sCHILD_BP_CITY);
            }
            else
              SetCity(rsDst, Number, DateReg, var, _T("BP_CITY"), _T("Місце народження: місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_О") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_REGION.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_REGION"), (LPCTSTR)sCHILD_BP_REGION);
            }
            else
              SetRegion(rsDst, Number, DateReg, var, _T("BP_REGION"), _T("Місце народження: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_Р") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_DISTRICT.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_DISTRICT"), (LPCTSTR)sCHILD_BP_DISTRICT);
            }
            else
              SetDistrict(rsDst, Number, DateReg, var, _T("BP_DISTRICT"), _T("Місце народження: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_С") ) {
            if ( (var.vt==NULL || var.bVal==0) ) {
              if ( FALSE==sCHILD_BP_COUNTRY.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_COUNTRY"), (LPCTSTR)sCHILD_BP_COUNTRY);
            }
            else
              SetCountry(rsDst, Number, DateReg, var, _T("BP_COUNTRY"), _T("Місце народження: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("кДетей") ) {
            rsDst.SetFieldValue(_T("NKIDS"), var);
          }
          else if ( fi.m_strName==_T("ПоСчёту") ) {
            rsDst.SetFieldValue(_T("BYCOUNT"), var);
          }
          else if ( fi.m_strName==_T("фЖиворождённый") ) {
            rsDst.SetFieldValue(_T("ALIVE_FLAG"), var);
          }
          else if ( fi.m_strName==_T("ТипГрафы18") ) {
            BYTE b = var.bVal & 0x0F;
            switch(b) {
              case 1: b = 0;  break;  // к_18_АР_Брак = 1 -> BIRTH_TYPE_ACT=0
              case 2: b = 1;  break;  // к_18_АР_ЗМ = 2   -> BIRTH_TYPE_MOTHER=1
              case 3: b = 2;  break;  // к_18_АР_ЗР = 3   -> BIRTH_TYPE_PARENTS=2
              case 4: b = 3;  break;  // к_18_АР_З = 4    -> BIRTH_TYPE_APPL=3
              case 5:         break;  // к_18_АР_АУО = 5  -> BIRTH_TYPE_AFFILIATION1=5
            }
            rsDst.SetFieldValue(_T("SOURCE_TYPE"), &COleVariant(b) );
          }
          else if ( fi.m_strName==_T("НСР") ) {
            s = GetFieldString(&rsSrc, fi.m_strName);
            if ( !s.IsEmpty() )
              rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_NUMBER"), (LPCTSTR)s);
          }
          else if ( fi.m_strName==_T("ДСР") ) {
            rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_СР_Код") ) {
            s = theMHospitals.Lookup(var.lVal);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_BY"), (LPCTSTR)s); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("Фамилия_О") ) {
            try { rsDst.SetFieldValue(_T("FATHER_SURNAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ИмяО") ) {
            SetName(rsDst, Number, DateReg, var, _T("FATHER_NAME"), _T("Ім'я батька"), szActName);
          }
          else if ( fi.m_strName==_T("с_ОтчествоО") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("FATHER_PATRONYMIC"), _T("По батькові батька"), szActName);
          }
          else if ( fi.m_strName==_T("фДРО") ) {
            try { rsDst.SetFieldValue(_T("FATHER_DOB_FLAG"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДатаРО") ) {
            try { rsDst.SetFieldValue(_T("FATHER_BIRTH_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ГражданствоО") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("FATHER_CITIZENSHIP"), _T("Громадянство батька"), szActName);
          }
          else if ( fi.m_strName==_T("с_НациональностьО") ) {
            SetNation(rsDst, Number, DateReg, TRUE, var, _T("EXTNOTES"), _T("Національність батька"), szActName, TRUE);
          }
          else if ( fi.m_strName==_T("с_МПО_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("FATHER_COUNTRY"), _T("Місце проживання батька: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПО_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("FATHER_REGION"), _T("Місце проживання батька: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПО_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("FATHER_CITY"), _T("Місце проживання батька: місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПО_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("FATHER_DISTRICT"), _T("Місце проживання батька: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПО_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("FATHER_STREET"), _T("Місце проживання батька: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПО_Дом") ) {
            try { rsDst.SetFieldValue(_T("FATHER_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МПО_Квартира") ) {
            try { rsDst.SetFieldValue(_T("FATHER_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортО_С") ) {
            szMPassportSeria = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортО_Н") ) {
            szMPassportNumber = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортО_Д") ) {
            MPassportDate = GetFieldOleDateTime(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортО_Код") ) {
            szMPassportBy = theROVDs.Lookup( GetFieldLong(&rsSrc, fi.m_strName) );
          }
          else if ( fi.m_strName==_T("Фамилия_М") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_SURNAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Фамилия_МН") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              s.Format(_T("{Нове прізвище матері: %s} "), Trim(V_BSTRT(&var)));
              szExtMemo += s;
            }
          }
          else if ( fi.m_strName==_T("фИспользуетсяНФМ") ) {
          }
          else if ( fi.m_strName==_T("с_ИмяМ") ) {
            SetName(rsDst, Number, DateReg, var, _T("MOTHER_NAME"), _T("Ім'я матері"), szActName);
          }
          else if ( fi.m_strName==_T("с_ОтчествоМ") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MOTHER_PATRONYMIC"), _T("По батькові матері"), szActName);
          }
          else if ( fi.m_strName==_T("фДРМ") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_DOB_FLAG"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДатаРМ") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_BIRTH_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ГражданствоМ") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MOTHER_CITIZENSHIP"), _T("Громадянство матері"), szActName);
          }
          else if ( fi.m_strName==_T("с_НациональностьМ") ) {
            SetNation(rsDst, Number, DateReg, FALSE, var, _T("EXTNOTES"), _T("Національність матері"), szActName, TRUE);
          }
          else if ( fi.m_strName==_T("с_МПМ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MOTHER_COUNTRY"), _T("Місце проживання матері: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MOTHER_REGION"), _T("Місце проживання матері: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MOTHER_CITY"), _T("Місце проживання матері: місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MOTHER_DISTRICT"), _T("Місце проживання матері: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MOTHER_STREET"), _T("Місце проживання матері: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПМ_Дом") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МПМ_Квартира") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_С") ) {
            szWPassportSeria = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
            szWPassportNumber = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
            WPassportDate = GetFieldOleDateTime(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
            szWPassportBy = theROVDs.Lookup( GetFieldLong(&rsSrc, fi.m_strName) );
          }
          else if ( fi.m_strName==_T("Св-твоСАРР") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Св-твоНАРР") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Св-твоСАУО") ) {
          }
          else if ( fi.m_strName==_T("Св-твоНАУО") ) {
          }
          else if ( fi.m_strName==_T("ФИО_ЗаявителяАРР") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_NAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Адрес_ЗаявителяАРР") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФИО_ЗаявителяАУО") ) {
          }
          else if ( fi.m_strName==_T("Адрес_ЗаявителяАУО") ) {
          }
          else if ( fi.m_strName==_T("Примечания") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("NOTICE"), var); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Серия") && false==Trim(V_BSTRT(&var)).IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); fDeclarantPassport = true; }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Номер") && false==Trim(V_BSTRT(&var)).IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); fDeclarantPassport = true; }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Выдан") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_РОВД") && var.lVal != 0 ) {
            SetROVD(rsDst, Number, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("Ким видано паспорт заявника"), szActName);
            fDeclarantPassport = true;
          }
        } // for by record fields
        if ( false==szWPassportSeria.IsEmpty() ) {
          // {П2: 3} {Серія П2: ДН} {Номер П2: 3583} {Дата видачі П2: 19.02.1999} {Ким видано П2: УПРІМР УмВС України в Донецьій області}
          s.Format(_T("{П2: %d} {Серія П2: %s} "),
                   GetOldPassportType(dwFlags, false), szWPassportSeria);
          szExtMemo += s;
        }
        if ( false==szWPassportNumber.IsEmpty() ) {
          s.Format(_T("{Номер П2: %s} "), szWPassportNumber);
          szExtMemo += s;
        }
        if ( WPassportDate.m_dt != (DATE)0 ) {
          s.Format(_T("{Дата видачі П2: %02d.%d.%04d} "), WPassportDate.GetDay(), WPassportDate.GetMonth(), WPassportDate.GetYear());
          szExtMemo += s;
        }
        if ( false==szWPassportBy.IsEmpty() ) {
          s.Format(_T("{Ким видано П2: %s}"), szWPassportBy);
          szExtMemo += s;
        }
        if ( false==fDeclarantPassport ) {
          if ( MPassportDate.m_dt != (DATE)0 && WPassportDate.m_dt != (DATE)0) {
            rsDst.SetFieldValue(_T("DECLARANT_TYPE"), COleVariant((BYTE)2) ); // Два заявителя
          }
          rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_TYPE"),
                                COleVariant((BYTE)GetOldPassportType(dwFlags, true)) );
          
          if ( false==szMPassportSeria.IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), (LPCTSTR)szMPassportSeria); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          if ( false==szMPassportNumber.IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), (LPCTSTR)szMPassportNumber); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          if ( false==szMPassportBy.IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_BY"), (LPCTSTR)szMPassportBy); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          if ( MPassportDate.m_dt != (DATE)0 ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), MPassportDate); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
        }
        szExtMemo.TrimRight();
        if ( false==szExtMemo.IsEmpty() ) {
          try { rsDst.SetFieldValue(_T("EXTNOTES"), (LPCTSTR)szExtMemo); }
          catch(CDaoException* e) {
            OnMessage(MT_ERROR, FormatDaoError(e));
            e->Delete();
          }
        }
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      try {
        rsDst.Update();
        nImportedRecords++;
        s.Format(_T("Імпортовано АЗ про народження: %s, АЗ № %d від %02d.%02d.%04d."),
                     Surname, Number, DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());

        OnMessage(nImage, s);
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
_Next:
      rsSrc.MoveNext();
    } // while ( !rsSrc.IsEOF() )
    rsDst.Close();
    rsSrc.Close();
  }
  catch(CDaoException* e) {
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return nImportedRecords;
}

long ImportFromOldMarriage() {
  static LPCTSTR szActName = _T("ОДРУЖЕННЯ");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM Акты_о_браке"), s;

  long nImportedRecords = 0;
  int nFields = 0;

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[MARRIAGES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));

    nFields = rsSrc.GetFieldCount();

    while ( !rsSrc.IsEOF() ) {
      short   Number = -1;
      CString SurnameOldM, SurnameOldW;
      COleVariant var;
      COleDateTime DateReg;
      DWORD dwFlags = 0;

      g_pProgress->OffsetPos(1);

      try {
        var = rsSrc.GetFieldValue(_T("ФамилияМС"));
        SurnameOldM = Trim(V_BSTRT(&var));
        rsSrc.GetFieldValue(_T("ФамилияЖС"));
        SurnameOldW = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("Номер"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("ДатаРег"));
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && SurnameOldM.IsEmpty() && SurnameOldW.IsEmpty() ) { // Фимилии пусты?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// Год регистрации не совпадает?
        goto _Next;
      }
      if ( g_fNoExist ) { // Добавлять только несуществующие записи?
        if ( IsEr3RecordPresent(rsDst, Number, DateReg, SurnameOldM, _T("MOLD_SURNAME")) &&
             IsEr3RecordPresent(rsDst, Number, DateReg, SurnameOldW, _T("WOLD_SURNAME")) ) {
          goto _Next;
        }
      }

      rsDst.AddNew();

      try {
        for( int i(0); i < nFields; i++ ) {
          CDaoFieldInfo fi;
          rsSrc.GetFieldInfo(i, fi);
          var = rsSrc.GetFieldValue(i);

          if ( fi.m_strName==_T("ДатаРег") ) {
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("Номер") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("Флаги") ) {
            dwFlags = (DWORD)var.lVal;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ПАЗ") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_PAZ;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ФамилияМС") ) {
            rsDst.SetFieldValue(_T("MOLD_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("ФамилияМН") ) {
            rsDst.SetFieldValue(_T("MNEW_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("сИмяМ") ) {
            SetName(rsDst, Number, DateReg, var, _T("MNAME"), _T("Ім'я нареченого"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоМ") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MPATRONYMIC"), _T("По батькові нареченого"), szActName );
          }
          else if ( fi.m_strName==_T("фДРМ") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_MBIRTH;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ДатаРМ") ) {
            rsDst.SetFieldValue(_T("MBIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_МРМ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MBIRTH_CITY"), _T("Місце народження нареченого: М_сто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРМ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MBIRTH_REGION"), _T("Місце народження нареченого: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРМ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MBIRTH_DISTRICT"), _T("Місце народження нареченого: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРМ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MBIRTH_COUNTRY"), _T("Місце народження нареченого: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_ГражданствоМ") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MCITIZENSHIP"), _T("Громадянство нареченого"), szActName );
          }
          else if ( fi.m_strName==_T("с_НациональностьМ") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("MNOTICE"), _T("Національність нареченого"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MRP_CITY"), _T("Місце проживання нареченого: Місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MRP_DISTRICT"), _T("Місце проживання нареченого: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MRP_REGION"), _T("Місце проживання нареченого: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MRP_COUNTRY"), _T("Місце проживання нареченого: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MRP_STREET"), _T("Місце проживання нареченого: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПМ_Дом") ) {
            try { rsDst.SetFieldValue(_T("MRP_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МПМ_Квартира") ) {
            try { rsDst.SetFieldValue(_T("MRP_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_С") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("MPASSPORT_BY"), _T("Паспорт нареченого: ким видано"), _T("СМЕРТЬ"));
          }
          else if ( fi.m_strName==_T("фСПоложениеМ") ) {
            try { rsDst.SetFieldValue(_T("MFAMILY_STATUS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("НомерАктаМ") ) {
            try { rsDst.SetFieldValue(_T("MACT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДатаАктаМ") ) {
            try { rsDst.SetFieldValue(_T("MACT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сРагсМ") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("MACT_BY"), _T("Ким складено актовий запис про роз_рвання шлюбу або смерть на стороні нареченого"), szActName);
          }
          else if ( fi.m_strName==_T("ФамилияЖС") ) {
            rsDst.SetFieldValue(_T("WOLD_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("ФамилияЖН") ) {
            rsDst.SetFieldValue(_T("WNEW_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("сИмяЖ") ) {
            SetName(rsDst, Number, DateReg, var, _T("WNAME"), _T("Ім'я нареченої"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоЖ") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("WPATRONYMIC"), _T("По батькові нареченої"), szActName );
          }
          else if ( fi.m_strName==_T("фДРЖ") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_WBIRTH;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ДатаРЖ") ) {
            rsDst.SetFieldValue(_T("WBIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_МРЖ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WBIRTH_CITY"), _T("Місце народження нареченої: М_сто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРЖ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WBIRTH_REGION"), _T("Місце народження нареченої: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРЖ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WBIRTH_DISTRICT"), _T("Місце народження нареченої: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МРЖ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WBIRTH_COUNTRY"), _T("Місце народження нареченої: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_ГражданствоЖ") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("WCITIZENSHIP"), _T("Громадянство нареченої"), szActName );
          }
          else if ( fi.m_strName==_T("с_НациональностьЖ") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("WNOTICE"), _T("Нац_ональн_сть нареченої"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WRP_CITY"), _T("Місце проживання нареченої: М_сто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WRP_DISTRICT"), _T("Місце проживання нареченої: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WRP_REGION"), _T("Місце проживання нареченої: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WRP_COUNTRY"), _T("Місце проживання нареченої: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("WRP_STREET"), _T("Місце проживання нареченої: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПЖ_Дом") ) {
            try { rsDst.SetFieldValue(_T("WRP_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МПЖ_Квартира") ) {
            try { rsDst.SetFieldValue(_T("WRP_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_С") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Н") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Д") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Код") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("WPASSPORT_BY"), _T("Паспорт нареченої: ким видано"), szActName);
          }
          else if ( fi.m_strName==_T("фСПоложениеЖ") ) {
            try { rsDst.SetFieldValue(_T("WFAMILY_STATUS"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("НомерАктаЖ") ) {
            try { rsDst.SetFieldValue(_T("WACT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДатаАктаЖ") ) {
            try { rsDst.SetFieldValue(_T("WACT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сРагсЖ") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("WACT_BY"), _T("Ким складено актовий запис про роз_рвання шлюбу або смерть на стороні нареченої"), szActName);
          }
          else if ( fi.m_strName==_T("СвС") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("СвН") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПримечанияМ") ) {
            try { rsDst.SetFieldValue(_T("MNOTICE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПримечанияЖ") ) {
            try { rsDst.SetFieldValue(_T("WNOTICE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
        }// for( int i(0); i < nFields; i++ )


        try {
          rsDst.Update();
          nImportedRecords++;
          s.Format(_T("Імпортован АЗ про %s: %s та %s, АЗ № %d від %02d.%02d.%04d."),
                   szActName, SurnameOldM, SurnameOldW, Number,
                   DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
          OnMessage(MT_MARRIAGE, s);
        }
        catch(CDaoException* e) {
          OnMessage(MT_ERROR, FormatDaoError(e));
          e->Delete();
        }
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
_Next:
     rsSrc.MoveNext();
    } // while ( !rsSrc.IsEOF() )
  }
  catch(CDaoException* e) {
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return nImportedRecords;
}

long ImportFromOldDivorce() {
  static LPCTSTR szActName = _T("РОЗІРВАННЯ ШЛЮБУ");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM Акты_о_разводе"), s;

  long nImportedRecords = 0;

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[DIVORCES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));

    int nFields = rsSrc.GetFieldCount();
    while ( !rsSrc.IsEOF() ) {
      short   Number = -1;
      CString SurnameOldM, SurnameOldW;
      COleVariant var;
      COleDateTime DateReg;

      g_pProgress->OffsetPos(1);

      try {
        var = rsSrc.GetFieldValue(_T("ФамилияМС"));
        SurnameOldM = Trim(V_BSTRT(&var));
        rsSrc.GetFieldValue(_T("ФамилияЖС"));
        SurnameOldW = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("Номер"));
        Number = var.iVal;
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && SurnameOldM.IsEmpty() && SurnameOldW.IsEmpty() ) { // Фимилии пусты?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// Год регистрации не совпадает?
        goto _Next;
      }
      if ( g_fNoExist ) { // Добавлять только несуществующие записи?
        if ( IsEr3RecordPresent(rsDst, Number, DateReg, SurnameOldM, _T("MOLD_SURNAME")) &&
             IsEr3RecordPresent(rsDst, Number, DateReg, SurnameOldW, _T("WOLD_SURNAME")) ) {
          goto _Next;
        }
      }

      rsDst.AddNew();

      try {
        for( int i(0); i < nFields; i++ ) {
          CDaoFieldInfo fi;
          rsSrc.GetFieldInfo(i, fi);
          var = rsSrc.GetFieldValue(i);

          if ( fi.m_strName==_T("ДатаРег") ) {
            DateReg = var;
            try { rsDst.SetFieldValue(_T("DATEREG"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Номер") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("Флаги") ) {
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ПАЗ") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= DIVORCE_PAZ;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("сРагсБ") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("MARRIAGE_BY"), _T("Ким складено шлюб"), szActName );
          }
          else if ( fi.m_strName==_T("НомерАБ") ) {
            try { rsDst.SetFieldValue(_T("MARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДатаАБ") ) {
            try { rsDst.SetFieldValue(_T("MARRIAGE_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Основание") ) {
            try { rsDst.SetFieldValue(_T("GROUND"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }

          else if ( fi.m_strName==_T("НомерБМ") ) {
            try { rsDst.SetFieldValue(_T("MMARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФамилияМС") ) {
            try { rsDst.SetFieldValue(_T("MOLD_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФамилияМН") ) {
            try { rsDst.SetFieldValue(_T("MNEW_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сИмяМ") ) {
            SetName(rsDst, Number, DateReg, var, _T("MNAME"), _T("Ім'я чолов_ка"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоМ") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MPATRONYMIC"), _T("По батькові чолов_ка"), szActName );
          }
          else if ( fi.m_strName==_T("фДРМ") ) {
            try {
              rsDst.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= DIVORCE_MBIRTH;
              rsDst.SetFieldValue(_T("FLAGS"), var);
            }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДРМ") ) {
            try { rsDst.SetFieldValue(_T("MBIRTH_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ГражданствоМ") && var.bVal!=0 ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MCITIZENSHIP"), _T("Громадянство чолов_ка"), szActName );
          }
          else if ( fi.m_strName==_T("с_НациональностьМ") && var.lVal!=0 ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("MNOTICE"), _T("Нац_ональн_сть чолов_ка"), szActName );
          }

          else if ( fi.m_strName==_T("с_МПМ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MRP_CITY"), _T("Місце проживання чолов_ка: М_сто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MRP_DISTRICT"), _T("Місце проживання чолов_ка: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MRP_REGION"), _T("Місце проживання чолов_ка: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MRP_COUNTRY"), _T("Місце проживання чолов_ка: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПМ_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MRP_STREET"), _T("Місце проживання чолов_ка: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПМ_Дом") ) {
            CString s = GetFieldString(&rsDst, _T("MRP_HOUSE"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MRP_HOUSE"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("МПМ_Квартира") ) {
            CString s = GetFieldString(&rsDst, _T("MRP_FLAT"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MRP_FLAT"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_С") ) {
            CString s = GetFieldString(&rsDst, _T("MPASSPORT_SERIA"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
            CString s = GetFieldString(&rsDst, _T("MPASSPORT_NUMBER"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("MPASSPORT_BY"), _T("Ким видано паспорт чолов_ка"), szActName);
          }
          else if ( fi.m_strName==_T("СуммаМ") ) {
            try { rsDst.SetFieldValue(_T("MDUTY"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("СуммаМС") ) {
            try { rsDst.SetFieldValue(_T("MDUTY2"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("КвитанцияМ") || fi.m_strName==_T("КвМ") ) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MCHECK_NUMBER"), (LPCTSTR)sVal); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ДатаКМ") ) {
            try { rsDst.SetFieldValue(_T("MCHECK_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сБанкМ") ) {
            SetBank(rsDst, Number, DateReg, var, _T("MCHECK_BANK"), _T("Назва фінансової установи на стороні чолов_ка"), szActName);
          }
          else if ( fi.m_strName==_T("СвСМ") ) {
            try { rsDst.SetFieldValue(_T("MCERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("СвНМ") ) {
            try { rsDst.SetFieldValue(_T("MCERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПримечанияМ") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MNOTICE"), var); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }

          else if ( fi.m_strName==_T("НомерБЖ") ) {
            try { rsDst.SetFieldValue(_T("WMARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФамилияЖС") ) {
            try { rsDst.SetFieldValue(_T("WOLD_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФамилияЖН") ) {
            try { rsDst.SetFieldValue(_T("WNEW_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сИмяЖ") ) {
            SetName(rsDst, Number, DateReg, var, _T("WNAME"), _T("Ім'я жінки"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоЖ") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("WPATRONYMIC"), _T("По батькові жінки"), szActName );
          }
          else if ( fi.m_strName==_T("фДРЖ") ) {
            try {
              rsDst.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= DIVORCE_WBIRTH;
              rsDst.SetFieldValue(_T("FLAGS"), var);
            }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ДРЖ") ) {
            try { rsDst.SetFieldValue(_T("WBIRTH_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ГражданствоЖ") && var.bVal!=0 ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("WCITIZENSHIP"), _T("Громадянство жінки"), szActName );
          }
          else if ( fi.m_strName==_T("с_НациональностьЖ") && var.lVal!=0) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, FALSE, var, _T("WNOTICE"), _T("Нац_ональн_сть жінки"), szActName );
          }

          else if ( fi.m_strName==_T("с_МПЖ_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WRP_CITY"), _T("Місце проживання жінки: М_сто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WRP_DISTRICT"), _T("Місце проживання жінки: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WRP_REGION"), _T("Місце проживання жінки: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WRP_COUNTRY"), _T("Місце проживання жінки: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МПЖ_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("WRP_STREET"), _T("Місце проживання жінки: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МПЖ_Дом") ) {
            CString s = GetFieldString(&rsDst, _T("WRP_HOUSE"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WRP_HOUSE"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("МПЖ_Квартира") ) {
            CString s = GetFieldString(&rsDst, _T("WRP_FLAT"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WRP_FLAT"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_С") ) {
            CString s = GetFieldString(&rsDst, _T("WPASSPORT_SERIA"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Н") ) {
            CString s = GetFieldString(&rsDst, _T("WPASSPORT_NUMBER"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Д") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПаспортЖ_Код") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("WPASSPORT_BY"), _T("Ким видано паспорт жінки"), szActName);
          }
          else if ( fi.m_strName==_T("СуммаЖ") ) {
            try { rsDst.SetFieldValue(_T("WDUTY"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("СуммаЖС") ) {
            try { rsDst.SetFieldValue(_T("WDUTY2"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("КвитанцияЖ") || fi.m_strName==_T("КвЖ") ) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WCHECK_NUMBER"), (LPCTSTR)sVal); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ДатаКЖ") ) {
            try { rsDst.SetFieldValue(_T("WCHECK_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("сБанкЖ") ) {
            SetBank(rsDst, Number, DateReg, var, _T("WCHECK_BANK"), _T("Назва фінансової установи на стороні жінки"), szActName);
          }
          else if ( fi.m_strName==_T("СвСЖ") ) {
            try { rsDst.SetFieldValue(_T("WCERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("СвНЖ") ) {
            try { rsDst.SetFieldValue(_T("WCERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПримечанияЖ") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WNOTICE"), var); } 
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
        }// for( int i(0); i < nFields; i++ )
        try {
          rsDst.Update();
          nImportedRecords++;
          s.Format(_T("Імпортован АЗ про %s: %s та %s, АЗ № %d від %02d.%02d.%04d."),
                   szActName, SurnameOldM, SurnameOldW, Number,
                   DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
          OnMessage(MT_DIVORCE, s);
        }
        catch(CDaoException* e) {
          OnMessage(MT_ERROR, FormatDaoError(e));
          e->Delete();
        }
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
_Next:
     rsSrc.MoveNext();
    } // while ( !rsSrc.IsEOF() )
  }
  catch(CDaoException* e) {
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return nImportedRecords;
}

long ImportFromOldChange() {
  static LPCTSTR szActName = _T("ЗМІНА");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CDaoRecordset rsSubOld(&g_SourceDB), rsSubNew(&g_TargetDB);
  CString sql = _T("SELECT * FROM Акты_о_перемене");

  long nImportedRecords = 0;
  CString s;

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[CHANGES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));

    rsSubOld.Open(dbOpenTable, _T("[АктыП]"));
    rsSubOld.SetCurrentIndex(_T("ID"));
    rsSubNew.Open(dbOpenTable, _T("[CHANGESDEP]"));
    rsSubNew.SetCurrentIndex(_T("ID"));

    int nFields = rsSrc.GetFieldCount();

    while ( !rsSrc.IsEOF() ) {
      CDWordArray array;
      short   Number = -1;
      long    lSrcID = 0; // Значение поля для связи между Акты_о_перемене и АктыП в файле-источнике
      long    lDstID = 0; // Значение поля для связи между CHANGES и CHANGESDEP в файле-приёмнике
      COleVariant var;
      COleDateTime DateReg;
      CString SurnameOld;
      int nImage = MT_WCHANGE;
      VARIANT_BOOL bSex = FALSE;


      g_pProgress->OffsetPos(1);

      try {
        var = rsSrc.GetFieldValue(_T("ID"));
        lSrcID = var.lVal;
        var = rsSrc.GetFieldValue(_T("Номер"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("ДатаРег"));
        var = rsSrc.GetFieldValue(_T("ФамилияС"));
        SurnameOld = Trim(V_BSTRT(&var));
/*
        rsSubOld.Seek( _T("="), &COleVariant(lID,VT_I4) );
        while( !rsSubOld.IsEOF() ) {
          COleVariant v;
          rsSubOld.GetFieldValue(_T("ID"), v);
          //if ( v.lVal==lID )
          //  array.Add(
          rsSubOld.MoveNext();
        }
*/
      } 
      catch(CDaoException* e) {
        e->Delete();
      }

      if ( g_fNoEmpty && SurnameOld.IsEmpty() ) {  // Фамилия пуста?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// Год регистрации не совпадает?
        goto _Next;
      }
      if ( g_fNoExist ) { // Добавлять только несуществующие записи?
        if ( IsEr3RecordPresent(rsDst, Number, DateReg, SurnameOld, _T("OLDSURNAME")) ) {
          goto _Next;
        }
      }

      rsDst.AddNew();

      try {
        for( int i(0); i < nFields; i++ ) {
          CDaoFieldInfo fi;
          rsSrc.GetFieldInfo(i, fi);
          var = rsSrc.GetFieldValue(i);
          if ( fi.m_strName==_T("ДатаРег") ) {
            DateReg = var;
            try { rsDst.SetFieldValue(_T("DATEREG"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Номер") ) {
            try { rsDst.SetFieldValue(_T("NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Флаги") ) {
            try { rsDst.SetFieldValue(_T("FLAGS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Пол") ) {
            bSex = var.boolVal;
            if ( bSex ) {
              nImage++;
            }
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("ФамилияС") ) {
            rsDst.SetFieldValue(_T("OLDSURNAME"), var);
          }
          else if ( fi.m_strName==_T("ФамилияН") ) {
            rsDst.SetFieldValue(_T("NEWSURNAME"), var);
          }
          else if ( fi.m_strName==_T("сИмяС") ) {
            SetName(rsDst, Number, DateReg, var, _T("OLDNAME"), _T("Ім'я ДО реєстрації"), szActName );
          }
          else if ( fi.m_strName==_T("сИмяН") ) {
            SetName(rsDst, Number, DateReg, var, _T("NEWNAME"), _T("Ім'я ПІСЛЯ реєстрації"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоС") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("OLDPATRONYMIC"), _T("По батькові ДО реєстрації"), szActName );
          }
          else if ( fi.m_strName==_T("сОтчествоН") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("NEWPATRONYMIC"), _T("По батькові ПІСЛЯ реєстрації"), szActName );
          }
          else if ( fi.m_strName==_T("фДР") ) {
          }
          else if ( fi.m_strName==_T("ДР") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_МР_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("BIRTH_CITY"), _T("Місце народження: місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("BIRTH_DISTRICT"), _T("Місце народження: район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("BIRTH_REGION"), _T("Місце народження: область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МР_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("BIRTH_COUNTRY"), _T("Місце народження: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("НомерАОР") ) {
            rsDst.SetFieldValue(_T("BIRTHACT_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("ДатаАОР") ) {
            rsDst.SetFieldValue(_T("BIRTHACT_DATE"), var);
          }
          else if ( fi.m_strName==_T("РагсАОР") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("BIRTHACT_BY"), _T("Ким складено АЗ про народження"), szActName );
          }
          else if ( fi.m_strName==_T("с_Гражданство") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("CITIZENSHIP"), _T("Громадянство"), szActName );
          }
          else if ( fi.m_strName==_T("с_Национальность") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("NOTICE"), _T("Нац_ональн_сть"), szActName);
          }
          else if ( fi.m_strName==_T("с_МП_Г") ) {
            SetCity(rsDst, Number, DateReg, var, _T("CITY"), _T("Місце проживання: місто (село)"), szActName );
          }
          else if ( fi.m_strName==_T("с_МП_Р") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("DISTRICT"), _T("Місце проживання: Район"), szActName );
          }
          else if ( fi.m_strName==_T("с_МП_С") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("COUNTRY"), _T("Місце проживання: Держава"), szActName );
          }
          else if ( fi.m_strName==_T("с_МП_О") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("REGION"), _T("Місце проживання: Область"), szActName );
          }
          else if ( fi.m_strName==_T("с_МП_У") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("STREET"), _T("Місце проживання: Вулиця"), szActName );
          }
          else if ( fi.m_strName==_T("МП_Дом") ) {
            try { rsDst.SetFieldValue(_T("HOUSE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МП_Квартира") ) {
            try { rsDst.SetFieldValue(_T("FLAT"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Квитанция") || fi.m_strName==_T("НКв")) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              rsDst.SetFieldValue(_T("CHECKNUM"), (LPCTSTR)sVal);
            }
          }
          else if ( fi.m_strName==_T("ДатаК") ) {
            rsDst.SetFieldValue(_T("CHECKDATE"), var);
          }
          else if ( fi.m_strName==_T("сБанк") ) {
            SetBank(rsDst, Number, DateReg, var, _T("CHECKBANK"), _T("Назва фінансової установи"), szActName);
          }
          else if ( fi.m_strName==_T("Паспорт_С") ) {
            rsDst.SetFieldValue(_T("PASSPORT_SERIA"), var);
          }
          else if ( fi.m_strName==_T("Паспорт_Н") ) {
            rsDst.SetFieldValue(_T("PASSPORT_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("Паспорт_Д") ) {
            rsDst.SetFieldValue(_T("PASSPORT_DATE"), var);
          }
          else if ( fi.m_strName==_T("Паспорт_Код") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("PASSPORT_BY"), _T("Ким видано паспорт"), szActName);
          }
          else if ( fi.m_strName==_T("СерияС") ) {
            rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var);
          }
          else if ( fi.m_strName==_T("НомерС") ) {
            rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("Примечания") ) {
            rsDst.SetFieldValue(_T("NOTICE"), var);
          }
        }
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      try {
        rsDst.Update();
        nImportedRecords++;
        s.Format(_T("Імпортован АЗ про %s: %s, АЗ № %d від %02d.%02d.%04d."),
                 szActName, SurnameOld, Number,
                 DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
        OnMessage(nImage, s);
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      try {
         rsDst.SetBookmark( rsDst.GetLastModifiedBookmark() ); // Необходимо для последующего чтения из rsDst
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
           e->ReportError();
        #endif
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      lDstID = rsDst.GetFieldValue(_T("ID")).lVal; // Значение поля для связи между CHANGES и CHANGESDEP в файле-приёмнике
      // Копируем связные записи, если они есть
      rsSubOld.SetCurrentIndex(_T("ID"));
      try {
        if ( rsSubOld.Seek(_T("="), &COleVariant(lSrcID, VT_I4)) ) {
          while( !rsSubOld.IsEOF() ) {
            if ( lSrcID != GetFieldLong(&rsSubOld, _T("ID")) ) {
              break;
            }
            try { rsSubNew.AddNew();  // Добавляем новую запись для зависимого акта.
              for( int i(0); i < rsSubOld.GetFieldCount(); i++ ) {
                LPCTSTR szActType = _T("");
                CDaoFieldInfo fi;
                rsSubOld.GetFieldInfo(i, fi);
                var = rsSubOld.GetFieldValue(i);
                if ( fi.m_strName==_T("ID") ) {
                  var.lVal = lDstID; // Меняем значение связного поля
                  rsSubNew.SetFieldValue(fi.m_strName, var);
                }
                else if ( fi.m_strName==_T("Тип") )     { // Тип зависимого акта
                  switch( var.bVal ) {
                    case 1: // Народження
                      var.bVal = UCHAR('н'); szActType = _T("Народження");
                      break;
                    case 2: // Встановлення батьківства
                      var.bVal = UCHAR('в'); szActType = _T("Встановлення батьківства");
                      break;
                    case 3: // Шлюб
                      var.bVal = UCHAR('ш'); szActType = _T("Шлюб");
                      break;
                    case 4: // Розірвання шлюбу
                      var.bVal = UCHAR('р'); szActType = _T("Розірвання шлюбу");
                      break;
                    case 5: // Зміна
                      var.bVal = UCHAR('з'); szActType = _T("Зміну");
                      break;
                  }
                  rsSubNew.SetFieldValue(_T("TYPE"), var);
                }
                else if ( fi.m_strName==_T("НАЗ") )     { // Номер зависимого акта
                  rsSubNew.SetFieldValue(_T("NUMBER"), var);
                }
                else if ( fi.m_strName==_T("ДатаРег") ) { // Дата регистрации зависимого акта
                  rsSubNew.SetFieldValue(_T("DATEREG"), var);
                }
                else if ( fi.m_strName==_T("Рагс") )    { // Кем зарегистрирован зависимый акт
                  s.Format(_T("Ким складено АЗ про %s"), szActType);
                  SetRAGS(rsSubNew, Number, DateReg, var, _T("REGISTRAR"), s, szActName);
                }
              } // for( int i(0); i < rsSubOld.GetFieldCount(); i++ )
              rsSubNew.Update();
            } // try rsSubNew.AddNew();
            catch(CDaoException* e) { // Не получилось записать какое-то поле?
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
            rsSubOld.MoveNext(); // Переходим на следующую запись
          }
        }
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
           e->ReportError();
        #endif
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
_Next:
      rsSrc.MoveNext();
    }

    rsSubNew.Close();
    rsSubOld.Close();
  }
  catch(CDaoException* e) {
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }

  return nImportedRecords;
}

long ImportFromOldDeath() {
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM Акты_о_смерти"), s;
  long nImportedRecords = 0;

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[DEATHES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));

    int nFields = rsSrc.GetFieldCount();

    while ( !rsSrc.IsEOF() ) {
      short   Number = -1;
      CString Surname;
      COleVariant var;
      COleDateTime DateReg;
      VARIANT_BOOL bSex = FALSE;
      g_pProgress->OffsetPos(1);
      try {
        var = rsSrc.GetFieldValue(_T("Фамилия"));
        Surname = V_BSTRT(&var);
        var = rsSrc.GetFieldValue(_T("Номер"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("ДатаРег"));
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && Surname.IsEmpty() ) {     // Фамилия пуста?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// Год регистрации не совпадает?
        goto _Next;
      }
      if ( g_fNoExist ) { // Добавлять только несуществующие записи?
        if ( IsEr3RecordPresent(rsDst, Number, DateReg, Surname, _T("SURNAME")) ) {
          goto _Next;
        }
      }

      rsDst.AddNew();

      try {
        for( int i(0); i < nFields; i++ ) {
          CDaoFieldInfo fi;
          rsSrc.GetFieldInfo(i, fi);
          var = rsSrc.GetFieldValue(i);
          if ( fi.m_strName==_T("ДатаРег") ) {
            DateReg = var;
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("Номер") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("Флаги") ) {
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("ПАЗ") ) {
            rsDst.SetFieldValue(_T("RENEW"), var);
          }
          else if ( fi.m_strName==_T("Пол") ) {
            bSex = var.boolVal;
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("Фамилия") ) {
            rsDst.SetFieldValue(_T("SURNAME"), var);
          }
          else if ( fi.m_strName==_T("сИмя") ) {
            SetName(rsDst, Number, DateReg, var, _T("NAME"), _T("Ім'я померлої особи"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("сОтчество") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("PATRONYMIC"), _T("По батькові померлої особи"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_Национальность") ) {
            // SetNation(rsDst, Number, DateReg, bSex, var, _T("NATIONALITY"), _T("Національність"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_Гражданство") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("CITIZENSHIP"), _T("Громадянство"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("фДС") ) {
            rsDst.SetFieldValue(_T("DOD_FLAG"), var);
          }
          else if ( fi.m_strName==_T("ДС") ) {
            rsDst.SetFieldValue(_T("DEATH_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_МС_КНП") ) {
            SetCity(rsDst, Number, DateReg, var, _T("DP_CITY"), _T("Місце смерті: місто (село)"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МС_КО") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("DP_REGION"), _T("Місце смерті: область"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МС_КР") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("DP_DISTRICT"), _T("Місце смерті: район"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МС_КС") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("DP_COUNTRY"), _T("Місце смерті: Держава"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("ПричинаСмерти") ) {
            rsDst.SetFieldValue(_T("CAUSE_OF_DEATH"), var);
          }
          else if ( fi.m_strName==_T("фДР") ) {
            rsDst.SetFieldValue(_T("DOB_FLAG"), var);
          }
          else if ( fi.m_strName==_T("ДР") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("с_МР_КНП") ) {
            SetCity(rsDst, Number, DateReg, var, _T("BP_CITY"), _T("Місце народження: місто (село)"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МР_КО") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("BP_REGION"), _T("Місце народження: область"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МР_КР") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("BP_DISTRICT"), _T("Місце народження: район"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МР_КС") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("BP_COUNTRY"), _T("Місце народження: Держава"), _T("СМЕРТЬ") );
          }

          else if ( fi.m_strName==_T("МП_Индекс") ) {
            rsDst.SetFieldValue(_T("RP_ZIPCODE"), var);
          }
          else if ( fi.m_strName==_T("с_МП_КНП") ) {
            SetCity(rsDst, Number, DateReg, var, _T("RP_CITY"), _T("Місце проживання: місто (село)"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МП_КО") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("RP_REGION"), _T("Місце проживання: область"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МП_КР") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("RP_DISTRICT"), _T("Місце проживання: район"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МП_КС") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("RP_COUNTRY"), _T("Місце проживання: Держава"), _T("СМЕРТЬ") );
          }
          else if ( fi.m_strName==_T("с_МП_КУ") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("RP_STREET"), _T("Місце проживання: вулиця"), _T("СМЕРТЬ"));
          }
          else if ( fi.m_strName==_T("МП_Дом") ) {
            try { rsDst.SetFieldValue(_T("RP_HOUSE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("МП_Квартира") ) {
            try { rsDst.SetFieldValue(_T("RP_FLAT"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Св-твоС") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Св-твоН") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ВСС_Тип") ) {
            LPCTSTR szValue = NULL;
            switch( var.bVal ) {
              case 1: szValue = _T("Остаточне лікарське свідоцтво про смерть №");   break;
              case 2: szValue = _T("Попереднє лікарське свідоцтво про смерть №");   break;
              case 3: szValue = _T("Лікарське свідоцтво про смерть №");             break;
              case 4: szValue = _T("Повідомлення установи");                        break;
              case 5: szValue = _T("Остаточне лікарське свідоцтво про смерть");     break;
              case 6: szValue = _T("Попереднє лікарське свідоцтво про смерть");     break;
              case 7: szValue = _T("Свідоцтво про перинатальну смерть №");          break;
              case 8: szValue = _T("Рішення суду");                                 break;
            }
            if ( szValue ) {
              try { rsDst.SetFieldValue(_T("MEDICAL_CERT_TYPE"), szValue ); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ВСС_Номер") ) {
            try { rsDst.SetFieldValue(_T("MEDICAL_CERT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("с_ВСС_Код") ) {
            s = theHospitals.Lookup(var.lVal);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MEDICAL_CERT_BY"), (LPCTSTR)s); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("ВСС_Дата") ) {
            try { rsDst.SetFieldValue(_T("MEDICAL_CERT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ФИО_Заявителя") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_NAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Адрес_Заявителя") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("П_Серия") ) {
            var = rsSrc.GetFieldValue(_T("П_Серия"));
            s = V_BSTRT(&var);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("PASSPORT_SERIA"), (LPCTSTR)s); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("П_Номер") ) {
            try { rsDst.SetFieldValue(_T("PASSPORT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("П_Выдан") ) {
            try { rsDst.SetFieldValue(_T("PASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("КодРОВД") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("PASSPORT_BY"), _T("Паспорт померлого: ким видано"), _T("СМЕРТЬ"));
          }
          else if ( fi.m_strName==_T("ИН") ) {
            try { rsDst.SetFieldValue(_T("TAX_CODE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("Примечания") ) {
            try { rsDst.SetFieldValue(_T("NOTICE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Серия") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Номер") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_Выдан") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("ПЗ_РОВД") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("Паспорт заявника: ким видано"), _T("СМЕРТЬ") );
          }
        }
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      try {
        rsDst.Update();
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
_Next:
      rsSrc.MoveNext();
    }
    rsDst.Close();
    rsSrc.Close();
  }
  catch(CDaoException* e) {
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return nImportedRecords;
}

long ImportFromEra() {
  long lRecsInBir = 0;
  long lRecsInMar = 0;
  long lRecsInDiv = 0;
  long lRecsInCha = 0;
  long lRecsInDea = 0;

  if ( g_fBirth ) {
    lRecsInBir  = GetRecordCount(g_SourceDB, _T("Акты_о_рождении")); // Количество записей о рождении
  }
  if ( g_fMarriage ) {
    lRecsInMar  = GetRecordCount(g_SourceDB, _T("Акты_о_браке"));    // Количество записей о браке
  }
  if ( g_fDivorce ) {
    lRecsInDiv  = GetRecordCount(g_SourceDB, _T("Акты_о_разводе"));  // Количество записей о расторжении брака
  }
  if ( g_fChange && IsTablePresent(g_SourceDB, _T("Акты_о_перемене")) ) {
    lRecsInCha  = GetRecordCount(g_SourceDB, _T("Акты_о_перемене")); // Количество записей о перемене
  }
  if ( g_fDeath ) {
    lRecsInDea  = GetRecordCount(g_SourceDB, _T("Акты_о_смерти"));   // Количество записей о смерти
  }
  long lTotalSrcRecs = lRecsInBir + lRecsInMar + lRecsInDiv + lRecsInCha + lRecsInDea;

  CString s;

  s.Format(_T("Імпорт із БД \"%s\"."), g_szSourceFile);
  OnMessage(MT_INFO, s);

  if ( 0 == lTotalSrcRecs ) {
    g_pProgress->ShowWindow(SW_HIDE); // А зачем тогда прогрессбар?
    s.Format(_T("Не існує даних для імпорту у файлі БД \"%s\"."), g_szSourceFile);
    OnMessage(MT_WARNING, s);
    return 0;  // Nothing to do because src database is empty.
  }
  long lTotalImported(0), lImported(0);

  // Заполняем кэши
  theNames      .Fill(g_SourceDB, _T("Имена"),          _T("КодИмени"),    _T("Имя")      );
  thePatronymics.Fill(g_SourceDB, _T("Отчества"),       _T("КодОтчества"), _T("Отчество") );
  theBanks      .Fill(g_SourceDB, _T("Банки"),          _T("Код"),         _T("Банк")     );
  theCountries  .Fill(g_SourceDB, _T("геоСтраны"),      _T("Код_Страны"),  _T("Страна"),      _T("Гражданство") );
  theRegions    .Fill(g_SourceDB, _T("геоОбласти"),     _T("КодО"),        _T("Область")  );
  theCities     .Fill(g_SourceDB, _T("геоНП"),          _T("Код НП"),      _T("Название"),  _T("НП") );
  theDistricts  .Fill(g_SourceDB, _T("геоРайоны"),      _T("Код Района"),  _T("Район")    );
  theStreets    .Fill(g_SourceDB, _T("геоУлицы"),       _T("Код"),         _T("Улица")    );
  theNations    .Fill(g_SourceDB, _T("Национальности"), _T("Код"),         _T("Чоловік"),     _T("Жінка") );
  theRAGSes     .Fill(g_SourceDB, _T("РАГСы"),          _T("Код"),         _T("РАГС")     );
  theROVDs      .Fill(g_SourceDB, _T("РОВД"),           _T("Код"),         _T("Паспорт_выдан")     );
  theMHospitals .Fill(g_SourceDB, _T("РодДома"),        _T("Код"),         _T("Больница") );
  theHospitals  .Fill(g_SourceDB, _T("СвВыдано"),       _T("Код"),         _T("Больница") );
 
  if ( lRecsInBir ) {
    g_pInfoBox->SetWindowText(_T("Імпортуються АЗ про народження..."));
    lImported = ImportFromOldBirth();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("Імпортовано %lu записів про народження."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInMar ) {
    g_pInfoBox->SetWindowText(_T("Імпортуються АЗ про одруження..."));
    lImported = ImportFromOldMarriage();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("Імпортовано %lu записів про одруження."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDiv ) {
    g_pInfoBox->SetWindowText(_T("Імпортуються АЗ про розірвання шлюбу..."));
    lImported = ImportFromOldDivorce();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("Імпортовано %lu записів про розірвання шлюбу."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDea ) {
    g_pInfoBox->SetWindowText(_T("Імпортуються АЗ про смерть..."));
    lImported = ImportFromOldDeath();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("Імпортовано %lu записів про смерть."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInCha ) {
    g_pInfoBox->SetWindowText(_T("Імпортуються АЗ про зміну..."));
    lImported = ImportFromOldChange();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("Імпортовано %lu записів про зміну."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  g_pInfoBox->SetWindowText(_T("Імпорт закінчено."));

  return lTotalImported;
}