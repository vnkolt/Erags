//
// CopyBirth.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#include "db.h"
#include "DefBirth.h"


#define BIRTH_G10         0x0001   // Const к_Г10 = 1  ' Графа 10 {Г10: }
#define BIRTH_RENEW       0x0002   // Const к_ПАЗ = 2  ' Поновлений АЗ
#define BIRTH_LONGTERM    0x0004   // Const к_ЗПС = 4  ' З пропуском строку
#define BIRTH_NOINLIST    0x0008   // Const к_МСН = 8  ' Не в списку новонароджених
#define BIRTH_DECL20      0x0010

#define BIRTH_TYPE_ACT            0 // Актовий запис про шлюб
#define BIRTH_TYPE_MOTHER         1 // Заява матері №
#define BIRTH_TYPE_PARENTS        2 // Заява батьків №
#define BIRTH_TYPE_APPL           3 // Заява
#define BIRTH_TYPE_APPLNUM        4 // Заява №
#define BIRTH_TYPE_AFFILIATION1   5 // Заява батька про ВБ №
#define BIRTH_TYPE_AFFILIATION2   6 // Спільна заява про ВБ №

#define szActName _T("НАРОДЖЕННЯ")

CString Trim(LPCTSTR sz);
CString GetFilePath(LPCTSTR szFileName);

CString sCHILD_BP_COUNTRY = _T("Україна");
CString sCHILD_BP_REGION;
CString sCHILD_BP_DISTRICT;
CString sCHILD_BP_CITY;

void CEra2era3Dlg::CopyBirth(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM Акты_о_рождении");

  if ( sCHILD_BP_REGION.IsEmpty() && sCHILD_BP_DISTRICT.IsEmpty() && sCHILD_BP_CITY.IsEmpty() ) {
    CString sDefIni;
    sDefIni.Format(_T("%s\\Defaults.ini"), GetFilePath(dbOut.GetName()));
    ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_REGION"), _T(""), sCHILD_BP_REGION.GetBuffer(64), 64, sDefIni);
    sCHILD_BP_REGION.ReleaseBuffer();
    ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_DISTRICT"), _T(""), sCHILD_BP_DISTRICT.GetBuffer(64), 64, sDefIni);
    sCHILD_BP_DISTRICT.ReleaseBuffer();
    ::GetPrivateProfileString(_T("BIRTH_FORM"), _T("CHILD_BP_CITY"), _T(""), sCHILD_BP_CITY.GetBuffer(64), 64, sDefIni);
    sCHILD_BP_CITY.ReleaseBuffer();
    CDefBirth dlg;
    dlg.DoModal();
  }

  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[BIRTHES]"));
    rsNew.SetCurrentIndex(_T("NUMBER"));

    while ( !rsOld.IsEOF() ) {
      short   iNumber = -1;
      CString Surname;
      COleVariant var;
      COleDateTime DateReg;

      m_ProgressFile.SetPos(++m_FilePos);
      m_ProgressTotal.SetPos(++m_TotalPos);

      try {
        var = rsOld.GetFieldValue(_T("ФамилияС"));
        Surname = Trim(V_BSTRT(&var));
        var = rsOld.GetFieldValue(_T("Номер"));
        iNumber = var.iVal;
      } 
      catch(CDaoException* e) {
        e->Delete();
      }
      if ( Surname.IsEmpty() ) {
        rsOld.MoveNext();
        continue;
      }
      if ( iNumber != -1 ) {
        if ( fOverwrite && rsNew.Seek(_T("="), &var) && rsOld.GetFieldValue(_T("ФамилияС"))==rsNew.GetFieldValue(_T("SURNAME")) )
          rsNew.Edit();
        else
          rsNew.AddNew();

        int nFields = rsOld.GetFieldCount();
        CString sKey, s;
        VARIANT_BOOL bSex = FALSE;
        try {
          BOOL fMR = FALSE;
          long lOldName = 0, lOldPatronymic = 0;
          for( int i(0); i < nFields; i++ ) {
            CDaoFieldInfo fi;
            rsOld.GetFieldInfo(i, fi);
            var = rsOld.GetFieldValue(i);
            if ( fi.m_strName==_T("ДатаРег") ) {
              DateReg = var;
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("Номер") ) {
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("НомерАУО") ) {
            }
            else if ( fi.m_strName==_T("Флаги") ) {
              rsNew.SetFieldValue(_T("RENEW"), var);
            }
            else if ( fi.m_strName==_T("ПАЗ") ) {
            }
            else if ( fi.m_strName==_T("ДатаРег") ) {
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("ДатаРегАУО") ) {
            }
            else if ( fi.m_strName==_T("Пол") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("Отцовство") ) {
            }
            else if ( fi.m_strName==_T("НомерДок") ) {
              s = GetFieldString(&rsOld, fi.m_strName);
              if ( !s.IsEmpty() )
                rsNew.SetFieldValue(_T("SOURCE_NDOC"), (LPCTSTR)s);
            }
            else if ( fi.m_strName==_T("ДатаДок") ) {
              rsNew.SetFieldValue(_T("SOURCE_DATE"), var);
            }
            else if ( fi.m_strName==_T("с_РАГС") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("SOURCE_BY"), _T("Ким складено АЗ про шлюб"), szActName);
            }
            else if ( fi.m_strName==_T("НомерСЗР") ) {
            }
            else if ( fi.m_strName==_T("ДатаСЗР") ) {
            }
            else if ( fi.m_strName==_T("ФамилияС") ) {
              rsNew.SetFieldValue(_T("SURNAME"), var);
            }
            else if ( fi.m_strName==_T("ФамилияН") ) {
              AddToMemo(rsNew, _T("EXTNOTES"), _T("Нове прізвище"), Trim(V_BSTRT(&var)));
            }
            else if ( fi.m_strName==_T("сИмя") ) {
              lOldName = var.lVal;              
              SetName(rsNew, iNumber, DateReg, var, _T("NAME"), _T("Ім'я новонародженого"), szActName);
            }
            else if ( fi.m_strName==_T("сИмяН") && var.lVal!=lOldName) {
              SetName(rsNew, iNumber, DateReg, var, _T("EXTNOTES"), _T("Нове ім'я новонародженого"), szActName, _T("Нове ім'я"));
            }
            else if ( fi.m_strName==_T("сОтчество") ) {
              lOldPatronymic = var.lVal;
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("PATRONYMIC"), _T("По батькові новонародженого"), szActName);
            }
            else if ( fi.m_strName==_T("сОтчествоН") && var.lVal != lOldPatronymic) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("EXTNOTES"), _T("Нове по батькові новонародженого"), szActName, _T("Нове по батькові"));
            }
            else if ( fi.m_strName==_T("ДРождения") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("фМР") ) {
              fMR = var.boolVal;
            }
            else if ( fi.m_strName==_T("с_МР_Г") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_CITY.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_CITY"), (LPCTSTR)sCHILD_BP_CITY);
              }
              else
                SetCity(rsNew, iNumber, DateReg, var, _T("BP_CITY"), _T("Місце народження: місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_О") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_REGION.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_REGION"), (LPCTSTR)sCHILD_BP_REGION);
              }
              else
                SetRegion(rsNew, iNumber, DateReg, var, _T("BP_REGION"), _T("Місце народження: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_Р") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_DISTRICT.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_DISTRICT"), (LPCTSTR)sCHILD_BP_DISTRICT);
              }
              else
                SetDistrict(rsNew, iNumber, DateReg, var, _T("BP_DISTRICT"), _T("Місце народження: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_С") ) {
              if ( (var.vt==NULL || var.bVal==0) ) {
                if ( FALSE==sCHILD_BP_COUNTRY.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_COUNTRY"), (LPCTSTR)sCHILD_BP_COUNTRY);
              }
              else
                SetCountry(rsNew, iNumber, DateReg, var, _T("BP_COUNTRY"), _T("Місце народження: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("кДетей") ) {
              rsNew.SetFieldValue(_T("NKIDS"), var);
            }
            else if ( fi.m_strName==_T("ПоСчёту") ) {
              rsNew.SetFieldValue(_T("BYCOUNT"), var);
            }
            else if ( fi.m_strName==_T("фЖиворождённый") ) {
              rsNew.SetFieldValue(_T("ALIVE_FLAG"), var);
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
              rsNew.SetFieldValue(_T("SOURCE_TYPE"), &COleVariant(b) );
            }
            else if ( fi.m_strName==_T("НСР") ) {
              s = GetFieldString(&rsOld, fi.m_strName);
              if ( !s.IsEmpty() )
                rsNew.SetFieldValue(_T("MEDICAL_CERTIFICATE_NUMBER"), (LPCTSTR)s);
            }
            else if ( fi.m_strName==_T("ДСР") ) {
              rsNew.SetFieldValue(_T("MEDICAL_CERTIFICATE_DATE"), var);
            }
            else if ( fi.m_strName==_T("с_СР_Код") ) {
              CString sKey;
              sKey.Format(_T("%d"), var.lVal);
              if ( m_MHospitals.Lookup(sKey, s) && !s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MEDICAL_CERTIFICATE_BY"), (LPCTSTR)s); }
                catch(CDaoException* e){
                  #ifdef _DEBUG 
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("Фамилия_О") ) {
              try { rsNew.SetFieldValue(_T("FATHER_SURNAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("с_ИмяО") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("FATHER_NAME"), _T("Ім'я батька"), szActName);
            }
            else if ( fi.m_strName==_T("с_ОтчествоО") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("FATHER_PATRONYMIC"), _T("По батькові батька"), szActName);
            }
            else if ( fi.m_strName==_T("фДРО") ) {
              try { rsNew.SetFieldValue(_T("FATHER_DOB_FLAG"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДатаРО") ) {
              try { rsNew.SetFieldValue(_T("FATHER_BIRTH_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("с_ГражданствоО") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("FATHER_CITIZENSHIP"), _T("Громадянство батька"), szActName);
            }
            else if ( fi.m_strName==_T("с_НациональностьО") ) {
              SetNation(rsNew, iNumber, DateReg, TRUE, var, _T("EXTNOTES"), _T("Національність батька"), szActName, TRUE);
            }
            else if ( fi.m_strName==_T("с_МПО_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("FATHER_COUNTRY"), _T("Місце проживання батька: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПО_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("FATHER_REGION"), _T("Місце проживання батька: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПО_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("FATHER_CITY"), _T("Місце проживання батька: місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПО_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("FATHER_DISTRICT"), _T("Місце проживання батька: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПО_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("FATHER_STREET"), _T("Місце проживання батька: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПО_Дом") ) {
              try { rsNew.SetFieldValue(_T("FATHER_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("МПО_Квартира") ) {
              try { rsNew.SetFieldValue(_T("FATHER_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортО_С") ) {
            }
            else if ( fi.m_strName==_T("ПаспортО_Н") ) {
            }
            else if ( fi.m_strName==_T("ПаспортО_Д") ) {
            }
            else if ( fi.m_strName==_T("ПаспортО_Код") ) {
            }
            else if ( fi.m_strName==_T("Фамилия_М") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_SURNAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Фамилия_МН") ) {
              AddToMemo(rsNew, _T("EXTNOTES"), _T("Нове прізвище матері"), Trim(V_BSTRT(&var)));
            }
            else if ( fi.m_strName==_T("фИспользуетсяНФМ") ) {
            }
            else if ( fi.m_strName==_T("с_ИмяМ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MOTHER_NAME"), _T("Ім'я матері"), szActName);
            }
            else if ( fi.m_strName==_T("с_ОтчествоМ") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MOTHER_PATRONYMIC"), _T("По батькові матері"), szActName);
            }
            else if ( fi.m_strName==_T("фДРМ") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_DOB_FLAG"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДатаРМ") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_BIRTH_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("с_ГражданствоМ") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MOTHER_CITIZENSHIP"), _T("Громадянство матері"), szActName);
            }
            else if ( fi.m_strName==_T("с_НациональностьМ") ) {
              SetNation(rsNew, iNumber, DateReg, FALSE, var, _T("EXTNOTES"), _T("Національність матері"), szActName, TRUE);
            }
            else if ( fi.m_strName==_T("с_МПМ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MOTHER_COUNTRY"), _T("Місце проживання матері: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MOTHER_REGION"), _T("Місце проживання матері: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MOTHER_CITY"), _T("Місце проживання матері: місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MOTHER_DISTRICT"), _T("Місце проживання матері: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MOTHER_STREET"), _T("Місце проживання матері: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПМ_Дом") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("МПМ_Квартира") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_С") ) {
            }
            else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
            }
            else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
            }
            else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
            }
            else if ( fi.m_strName==_T("Св-твоСАРР") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Св-твоНАРР") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Св-твоСАУО") ) {
            }
            else if ( fi.m_strName==_T("Св-твоНАУО") ) {
            }
            else if ( fi.m_strName==_T("ФИО_ЗаявителяАРР") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_NAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Адрес_ЗаявителяАРР") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ФИО_ЗаявителяАУО") ) {
            }
            else if ( fi.m_strName==_T("Адрес_ЗаявителяАУО") ) {
            }
            else if ( fi.m_strName==_T("Примечания") ) {
              try { rsNew.SetFieldValue(_T("NOTICE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПЗ_Серия") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПЗ_Номер") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПЗ_Выдан") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПЗ_РОВД") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("Ким видано паспорт заявника"), szActName);
            }
          }
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
          e->ReportError();
          #endif
          e->Delete();
        }
        try {
          rsNew.Update();
        }
        catch(CDaoException* e) {
          #ifdef _DEBUG
          e->ReportError();
          #endif
          e->Delete();
        }
      }

      rsOld.MoveNext();
    }
    rsNew.Close();
    rsOld.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
  }

}
