//
// CopyDivorce.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#include "db.h"

#define DIVORCE_NATM     0x0001
#define DIVORCE_CITM     0x0002
#define DIVORCE_FM       0x0004

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

#define szActName _T("РОЗІРВАННЯ ШЛЮБУ")


void CEra2era3Dlg::CopyDivorce(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM Акты_о_разводе");

  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[DIVORCES]"));
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

      if ( iNumber != -1 ) {
        if ( fOverwrite && rsNew.Seek(_T("="), &var) ) {
          rsNew.Edit();
        }
        else
          rsNew.AddNew();

        int nFields = rsOld.GetFieldCount();
        CString sKey, s;
        CSexRecord* pSexRecord = NULL;

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
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("Флаги") ) {
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ПАЗ") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= DIVORCE_PAZ;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("сРагсБ") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("MARRIAGE_BY"), _T("Ким складено шлюб"), szActName );
            }
            else if ( fi.m_strName==_T("НомерАБ") ) {
              try { rsNew.SetFieldValue(_T("MARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДатаАБ") ) {
              try { rsNew.SetFieldValue(_T("MARRIAGE_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Основание") ) {
              try { rsNew.SetFieldValue(_T("GROUND"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }

            else if ( fi.m_strName==_T("НомерБМ") ) {
              try { rsNew.SetFieldValue(_T("MMARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ФамилияМС") ) {
              try { rsNew.SetFieldValue(_T("MOLD_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ФамилияМН") ) {
              try { rsNew.SetFieldValue(_T("MNEW_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сИмяМ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MNAME"), _T("Ім'я чоловіка"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоМ") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MPATRONYMIC"), _T("По батькові чоловіка"), szActName );
            }
            else if ( fi.m_strName==_T("фДРМ") ) {
              try {
                rsNew.GetFieldValue(_T("FLAGS"), var);
                var.lVal |= DIVORCE_MBIRTH;
                rsNew.SetFieldValue(_T("FLAGS"), var);
              }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДРМ") ) {
              try { rsNew.SetFieldValue(_T("MBIRTH_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("с_ГражданствоМ") && var.bVal!=0 ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MCITIZENSHIP"), _T("Громадянство чоловіка"), szActName );
            }
            else if ( fi.m_strName==_T("с_НациональностьМ") && var.lVal!=0 ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("MNOTICE"), _T("Національність чоловіка"), szActName );
            }

            else if ( fi.m_strName==_T("с_МПМ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MRP_CITY"), _T("Місце проживання чоловіка: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MRP_DISTRICT"), _T("Місце проживання чоловіка: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MRP_REGION"), _T("Місце проживання чоловіка: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MRP_COUNTRY"), _T("Місце проживання чоловіка: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПМ_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MRP_STREET"), _T("Місце проживання чоловіка: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПМ_Дом") ) {
              CString s = GetFieldString(&rsNew, _T("MRP_HOUSE"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MRP_HOUSE"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("МПМ_Квартира") ) {
              CString s = GetFieldString(&rsNew, _T("MRP_FLAT"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MRP_FLAT"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_С") ) {
              CString s = GetFieldString(&rsNew, _T("MPASSPORT_SERIA"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Н") ) {
              CString s = GetFieldString(&rsNew, _T("MPASSPORT_NUMBER"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Д") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортМ_Код") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("MPASSPORT_BY"), _T("Ким видано паспорт чоловіка"), szActName);
            }
            else if ( fi.m_strName==_T("СуммаМ") ) {
              try { rsNew.SetFieldValue(_T("MDUTY"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("СуммаМС") ) {
              try { rsNew.SetFieldValue(_T("MDUTY2"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("КвитанцияМ") || fi.m_strName==_T("КвМ") ) {
              CString sVal = GetFieldString(&rsOld, fi.m_strName );
              if ( !sVal.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MCHECK_NUMBER"), (LPCTSTR)sVal); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ДатаКМ") ) {
              try { rsNew.SetFieldValue(_T("MCHECK_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сБанкМ") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("MCHECK_BANK"), _T("Назва фінансової установи на стороні чоловіка"), szActName);
            }
            else if ( fi.m_strName==_T("СвСМ") ) {
              try { rsNew.SetFieldValue(_T("MCERTIFICATE_SERIA"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("СвНМ") ) {
              try { rsNew.SetFieldValue(_T("MCERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПримечанияМ") ) {
              SetMemo(rsNew, _T("MNOTICE"), var);
            }

            else if ( fi.m_strName==_T("НомерБЖ") ) {
              try { rsNew.SetFieldValue(_T("WMARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ФамилияЖС") ) {
              try { rsNew.SetFieldValue(_T("WOLD_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ФамилияЖН") ) {
              try { rsNew.SetFieldValue(_T("WNEW_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сИмяЖ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("WNAME"), _T("Ім'я жінки"), szActName );
            }
            else if ( fi.m_strName==_T("сОтчествоЖ") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("WPATRONYMIC"), _T("По батькові жінки"), szActName );
            }
            else if ( fi.m_strName==_T("фДРЖ") ) {
              try {
                rsNew.GetFieldValue(_T("FLAGS"), var);
                var.lVal |= DIVORCE_WBIRTH;
                rsNew.SetFieldValue(_T("FLAGS"), var);
              }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ДРЖ") ) {
              try { rsNew.SetFieldValue(_T("WBIRTH_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("с_ГражданствоЖ") && var.bVal!=0 ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("WCITIZENSHIP"), _T("Громадянство жінки"), szActName );
            }
            else if ( fi.m_strName==_T("с_НациональностьЖ") && var.lVal!=0) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, FALSE, var, _T("WNOTICE"), _T("Національність жінки"), szActName );
            }

            else if ( fi.m_strName==_T("с_МПЖ_Г") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WRP_CITY"), _T("Місце проживання жінки: Місто (село)"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_Р") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WRP_DISTRICT"), _T("Місце проживання жінки: Район"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_О") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WRP_REGION"), _T("Місце проживання жінки: Область"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_С") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WRP_COUNTRY"), _T("Місце проживання жінки: Держава"), szActName );
            }
            else if ( fi.m_strName==_T("с_МПЖ_У") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("WRP_STREET"), _T("Місце проживання жінки: Вулиця"), szActName );
            }
            else if ( fi.m_strName==_T("МПЖ_Дом") ) {
              CString s = GetFieldString(&rsNew, _T("WRP_HOUSE"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("WRP_HOUSE"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("МПЖ_Квартира") ) {
              CString s = GetFieldString(&rsNew, _T("WRP_FLAT"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("WRP_FLAT"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_С") ) {
              CString s = GetFieldString(&rsNew, _T("WPASSPORT_SERIA"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Н") ) {
              CString s = GetFieldString(&rsNew, _T("WPASSPORT_NUMBER"));
              if ( s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Д") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ПаспортЖ_Код") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("WPASSPORT_BY"), _T("Ким видано паспорт жінки"), szActName);
            }
            else if ( fi.m_strName==_T("СуммаЖ") ) {
              try { rsNew.SetFieldValue(_T("WDUTY"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("СуммаЖС") ) {
              try { rsNew.SetFieldValue(_T("WDUTY2"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("КвитанцияЖ") || fi.m_strName==_T("КвЖ") ) {
              CString sVal = GetFieldString(&rsOld, fi.m_strName );
              if ( !sVal.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("WCHECK_NUMBER"), (LPCTSTR)sVal); }
                catch(CDaoException* e) {
                  #ifdef _DEBUG
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ДатаКЖ") ) {
              try { rsNew.SetFieldValue(_T("WCHECK_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("сБанкЖ") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("WCHECK_BANK"), _T("Назва фінансової установи на стороні жінки"), szActName);
            }
            else if ( fi.m_strName==_T("СвСЖ") ) {
              try { rsNew.SetFieldValue(_T("WCERTIFICATE_SERIA"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("СвНЖ") ) {
              try { rsNew.SetFieldValue(_T("WCERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
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

