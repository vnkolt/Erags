//
// CopyChange.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#include "db.h"

#define szActName _T("ЗМІНА")


void CEra2era3Dlg::CopyChange(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CDaoRecordset rsSubOld(&dbIn), rsSubNew(&dbOut);
  CString sql = _T("SELECT * FROM Акты_о_перемене");

  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[CHANGES]"));
    rsNew.SetCurrentIndex(_T("NUMBER"));

    rsSubOld.Open(dbOpenTable, _T("[АктыП]"));
    rsSubOld.SetCurrentIndex(_T("ID"));
    rsSubNew.Open(dbOpenTable, _T("[CHANGESDEP]"));
    rsSubNew.SetCurrentIndex(_T("ID"));

    while ( !rsOld.IsEOF() ) {
      CDWordArray array;
      short   iNumber = -1;
      long    lID;
      COleVariant var;
      COleDateTime DateReg;
      CString SurnameOld;

      m_ProgressFile.SetPos(++m_FilePos);
      m_ProgressTotal.SetPos(++m_TotalPos);

      try {
        var = rsOld.GetFieldValue(_T("ФамилияС"));
        SurnameOld = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("Номер"));
        iNumber = var.iVal;
        var = rsOld.GetFieldValue(_T("ID"));
        lID = var.lVal;

        rsSubOld.Seek( _T("="), &COleVariant(lID,VT_I4) );
        while( !rsSubOld.IsEOF() ) {
          COleVariant v;
          rsSubOld.GetFieldValue(_T("ID"), v);
          //if ( v.lVal==lID )
          //  array.Add(
          rsSubOld.MoveNext();
        }
      } 
      catch(CDaoException* e) {
        e->Delete();
      }
      if ( iNumber != -1 && FALSE==SurnameOld.IsEmpty()) {
        if ( fOverwrite && rsNew.Seek(_T("="), &var) )
          rsNew.Edit();
        else
          rsNew.AddNew();

        int nFields = rsOld.GetFieldCount();
        CString sKey, s;
        VARIANT_BOOL bSex = FALSE;
        try {
          for( int i(0); i < nFields; i++ ) {
            CDaoFieldInfo fi;
            rsOld.GetFieldInfo(i, fi);
            var = rsOld.GetFieldValue(i);
            if ( fi.m_strName==_T("ДатаРег") ) {
              DateReg = var;
              try { rsNew.SetFieldValue(_T("DATEREG"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Номер") ) {
              try { rsNew.SetFieldValue(_T("NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Флаги") ) {
              try { rsNew.SetFieldValue(_T("FLAGS"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Пол") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("ФамилияС") ) {
              rsNew.SetFieldValue(_T("OLDSURNAME"), var);
            }
            else if ( fi.m_strName==_T("ФамилияН") ) {
              rsNew.SetFieldValue(_T("NEWSURNAME"), var);
            }
            else if ( fi.m_strName==_T("сИмяС") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("OLDNAME"), _T("Ім'я ДО реєстрації"), szActName );
            }
            else if ( fi.m_strName==_T("сИмяН") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("NEWNAME"), _T("Ім'я ПІСЛЯ реєстрації"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоС") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("OLDPATRONYMIC"), _T("По батькові ДО реєстрації"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоН") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("NEWPATRONYMIC"), _T("По батькові ПІСЛЯ реєстрації"), szActName );
            }
            else if ( fi.m_strName==_T("фДР") ) {
            }
            else if ( fi.m_strName==_T("ДР") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("с_МР_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("BIRTH_CITY"), _T("Місце народження: місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("BIRTH_DISTRICT"), _T("Місце народження: район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("BIRTH_REGION"), _T("Місце народження: область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МР_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("BIRTH_COUNTRY"), _T("Місце народження: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("НомерАОР") ) {
              rsNew.SetFieldValue(_T("BIRTHACT_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("ДатаАОР") ) {
              rsNew.SetFieldValue(_T("BIRTHACT_DATE"), var);
            }
            else if ( fi.m_strName==_T("РагсАОР") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("BIRTHACT_BY"), _T("Ким складено АЗ про народження"), szActName );
            }
            else if ( fi.m_strName==_T("с_Гражданство") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("CITIZENSHIP"), _T("Громадянство"), szActName );
            }
            else if ( fi.m_strName==_T("с_Национальность") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("NOTICE"), _T("Національність"), szActName);
            }
            else if ( fi.m_strName==_T("с_МП_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("CITY"), _T("Місце проживання: місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МП_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("DISTRICT"), _T("Місце проживання: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МП_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("COUNTRY"), _T("Місце проживання: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МП_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("REGION"), _T("Місце проживання: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МП_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("STREET"), _T("Місце проживання: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МП_Дом") ) {
              try { rsNew.SetFieldValue(_T("HOUSE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("МП_Квартира") ) {
              try { rsNew.SetFieldValue(_T("FLAT"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Квитанция") || fi.m_strName==_T("НКв")) {
              CString sVal = GetFieldString(&rsOld, fi.m_strName );
              if ( !sVal.IsEmpty() ) {
                rsNew.SetFieldValue(_T("CHECKNUM"), (LPCTSTR)sVal);
              }
            }
            else if ( fi.m_strName==_T("ДатаК") ) {
              rsNew.SetFieldValue(_T("CHECKDATE"), var);
            }
            else if ( fi.m_strName==_T("сБанк") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("CHECKBANK"), _T("Назва фінансової установи"), szActName);
            }
            else if ( fi.m_strName==_T("Паспорт_С") ) {
              rsNew.SetFieldValue(_T("PASSPORT_SERIA"), var);
            }
            else if ( fi.m_strName==_T("Паспорт_Н") ) {
              rsNew.SetFieldValue(_T("PASSPORT_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("Паспорт_Д") ) {
              rsNew.SetFieldValue(_T("PASSPORT_DATE"), var);
            }
            else if ( fi.m_strName==_T("Паспорт_Код") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("PASSPORT_BY"), _T("Ким видано паспорт"), szActName);
            }
            else if ( fi.m_strName==_T("СерияС") ) {
              rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var);
            }
            else if ( fi.m_strName==_T("НомерС") ) {
              rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("Примечания") ) {
              rsNew.SetFieldValue(_T("NOTICE"), var);
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

    rsSubNew.Close();
    rsSubOld.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
  }

}
