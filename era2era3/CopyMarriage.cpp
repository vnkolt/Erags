//
// CopyMarriage.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#define MARRIAGE_PAZ    0x200
#define MARRIAGE_MBIRTH 0x400
#define MARRIAGE_WBIRTH 0x800

#define szActName _T("ШЛЮБ")

void CEra2era3Dlg::CopyMarriage(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM Акты_о_браке");

  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[MARRIAGES]"));
    rsNew.SetCurrentIndex(_T("NUMBER"));

    while ( !rsOld.IsEOF() ) {
      short   iNumber = -1;
      CString SurnameOldM, SurnameOldW;
      COleVariant var;
      COleDateTime DateReg;

      m_ProgressFile.SetPos(++m_FilePos);
      m_ProgressTotal.SetPos(++m_TotalPos);

      try {
        var = rsOld.GetFieldValue(_T("ФамилияМС"));
        SurnameOldM = V_BSTRT(&var);
        rsOld.GetFieldValue(_T("ФамилияЖС"));
        SurnameOldW = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("Номер"));
        iNumber = var.iVal;
      } 
      catch(CDaoException* e) {
        #ifdef _DEBUG 
          e->ReportError();
        #endif
        e->Delete();
      }

      if ( SurnameOldM.IsEmpty() ) {
        rsOld.MoveNext();
        continue;
      }

      if ( iNumber != -1 ) {
        if ( fOverwrite && rsNew.Seek(_T("="), &var) )
          rsNew.Edit();
        else
          rsNew.AddNew();

        int nFields = rsOld.GetFieldCount();
        CString s;

        try {
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
            else if ( fi.m_strName==_T("Флаги") ) {
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ПАЗ") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_PAZ;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ФамилияМС") ) {
              rsNew.SetFieldValue(_T("MOLD_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("ФамилияМН") ) {
              rsNew.SetFieldValue(_T("MNEW_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("сИмяМ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MNAME"), _T("Ім'я нареченого"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоМ") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MPATRONYMIC"), _T("По батькові нареченого"), szActName );
            }
            else if ( fi.m_strName==_T("фДРМ") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_MBIRTH;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ДатаРМ") ) {
              rsNew.SetFieldValue(_T("MBIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("с_МРМ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MBIRTH_CITY"), _T("Місце народження нареченого: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРМ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MBIRTH_REGION"), _T("Місце народження нареченого: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРМ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MBIRTH_DISTRICT"), _T("Місце народження нареченого: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРМ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MBIRTH_COUNTRY"), _T("Місце народження нареченого: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_ГражданствоМ") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MCITIZENSHIP"), _T("Громадянство нареченого"), szActName );
            }
            else if ( fi.m_strName==_T("с_НациональностьМ") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("MNOTICE"), _T("Національність нареченого"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MRP_CITY"), _T("Місце проживання нареченого: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MRP_DISTRICT"), _T("Місце проживання нареченого: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MRP_REGION"), _T("Місце проживання нареченого: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MRP_COUNTRY"), _T("Місце проживання нареченого: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MRP_STREET"), _T("Місце проживання нареченого: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПМ_Дом") ) {
              try { rsNew.SetFieldValue(_T("MRP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("МПМ_Квартира") ) {
              try { rsNew.SetFieldValue(_T("MRP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_С") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("MPASSPORT_BY"), _T("Паспорт нареченого: ким видано"), _T("СМЕРТЬ"));
            }
            else if ( fi.m_strName==_T("фСПоложениеМ") ) {
              try { rsNew.SetFieldValue(_T("MFAMILY_STATUS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("НомерАктаМ") ) {
              try { rsNew.SetFieldValue(_T("MACT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДатаАктаМ") ) {
              try { rsNew.SetFieldValue(_T("MACT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сРагсМ") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("MACT_BY"), _T("Ким складено актовий запис про розірвання шлюбу або смерть на стороні нареченого"), szActName);
            }
            else if ( fi.m_strName==_T("ФамилияЖС") ) {
              rsNew.SetFieldValue(_T("WOLD_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("ФамилияЖН") ) {
              rsNew.SetFieldValue(_T("WNEW_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("сИмяЖ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("WNAME"), _T("Ім'я нареченої"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоЖ") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("WPATRONYMIC"), _T("По батькові нареченої"), szActName );
            }
            else if ( fi.m_strName==_T("фДРЖ") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_WBIRTH;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ДатаРЖ") ) {
              rsNew.SetFieldValue(_T("WBIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("с_МРЖ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WBIRTH_CITY"), _T("Місце народження нареченої: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРЖ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WBIRTH_REGION"), _T("Місце народження нареченої: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРЖ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WBIRTH_DISTRICT"), _T("Місце народження нареченої: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МРЖ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WBIRTH_COUNTRY"), _T("Місце народження нареченої: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_ГражданствоЖ") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("WCITIZENSHIP"), _T("Громадянство нареченої"), szActName );
            }
            else if ( fi.m_strName==_T("с_НациональностьЖ") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("WNOTICE"), _T("Національність нареченої"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WRP_CITY"), _T("Місце проживання нареченої: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WRP_DISTRICT"), _T("Місце проживання нареченої: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WRP_REGION"), _T("Місце проживання нареченої: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WRP_COUNTRY"), _T("Місце проживання нареченої: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("WRP_STREET"), _T("Місце проживання нареченої: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПЖ_Дом") ) {
              try { rsNew.SetFieldValue(_T("WRP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("МПЖ_Квартира") ) {
              try { rsNew.SetFieldValue(_T("WRP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_С") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Н") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Д") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Код") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("WPASSPORT_BY"), _T("Паспорт нареченої: ким видано"), szActName);
            }
            else if ( fi.m_strName==_T("фСПоложениеЖ") ) {
              try { rsNew.SetFieldValue(_T("WFAMILY_STATUS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("НомерАктаЖ") ) {
              try { rsNew.SetFieldValue(_T("WACT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДатаАктаЖ") ) {
              try { rsNew.SetFieldValue(_T("WACT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сРагсЖ") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("WACT_BY"), _T("Ким складено актовий запис про розірвання шлюбу або смерть на стороні нареченої"), szActName);
            }
            else if ( fi.m_strName==_T("СвС") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("СвН") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПримечанияМ") ) {
              SetMemo(rsNew, _T("MNOTICE"), var);
            }
            else if ( fi.m_strName==_T("ПримечанияЖ") ) {
              SetMemo(rsNew, _T("WNOTICE"), var);
            }
          }// for( int i(0); i < nFields; i++ )


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
        catch(CDaoException* e) {
          #ifdef _DEBUG 
            e->ReportError();
          #endif
          e->Delete();
        }
     }      
     rsOld.MoveNext();
    } // while ( !rsOld.IsEOF() )
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
    e->ReportError();
    #endif
    e->Delete();
  }
}

