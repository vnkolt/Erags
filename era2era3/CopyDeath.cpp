//
// CopyDeath.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

CString Trim(LPCTSTR sz);

void CEra2era3Dlg::CopyDeath(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM Àêòû_î_ñìåðòè");
  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[DEATHES]"));
    rsNew.SetCurrentIndex(_T("NUMBER"));
    while ( !rsOld.IsEOF() ) {
      short   iNumber = -1;
      CString Surname;
      COleVariant var;
      COleDateTime DateReg;
      m_ProgressFile.SetPos(++m_FilePos);
      m_ProgressTotal.SetPos(++m_TotalPos);
      try {
        var = rsOld.GetFieldValue(_T("Ôàìèëèÿ"));
        Surname = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("Íîìåð"));
        iNumber = var.iVal;
      } 
      catch(CDaoException* e) {
        e->Delete();
      }
      if ( iNumber != -1 ) {
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
            if ( fi.m_strName==_T("ÄàòàÐåã") ) {
              DateReg = var;
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("Íîìåð") ) {
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("Ôëàãè") ) {
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("ÏÀÇ") ) {
              rsNew.SetFieldValue(_T("RENEW"), var);
            }
            else if ( fi.m_strName==_T("Ïîë") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("Ôàìèëèÿ") ) {
              rsNew.SetFieldValue(_T("SURNAME"), var);
            }
            else if ( fi.m_strName==_T("ñÈìÿ") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("NAME"), _T("²ì'ÿ ïîìåðëî¿ îñîáè"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñÎò÷åñòâî") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("PATRONYMIC"), _T("Ïî áàòüêîâ³ ïîìåðëî¿ îñîáè"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_Íàöèîíàëüíîñòü") ) {
              SetNation(rsNew, iNumber, DateReg, bSex, var, _T("NATIONALITY"), _T("Íàö³îíàëüí³ñòü"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_Ãðàæäàíñòâî") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("CITIZENSHIP"), _T("Ãðîìàäÿíñòâî"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ôÄÑ") ) {
              rsNew.SetFieldValue(_T("DOD_FLAG"), var);
            }
            else if ( fi.m_strName==_T("ÄÑ") ) {
              rsNew.SetFieldValue(_T("DEATH_DATE"), var);
            }
            else if ( fi.m_strName==_T("ñ_ÌÑ_ÊÍÏ") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("DP_CITY"), _T("Ì³ñöå ñìåðò³: ì³ñòî (ñåëî)"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÑ_ÊÎ") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("DP_REGION"), _T("Ì³ñöå ñìåðò³: îáëàñòü"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÑ_ÊÐ") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("DP_DISTRICT"), _T("Ì³ñöå ñìåðò³: ðàéîí"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÑ_ÊÑ") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("DP_COUNTRY"), _T("Ì³ñöå ñìåðò³: Äåðæàâà"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("Ïðè÷èíàÑìåðòè") ) {
              rsNew.SetFieldValue(_T("CAUSE_OF_DEATH"), var);
            }
            else if ( fi.m_strName==_T("ôÄÐ") ) {
              rsNew.SetFieldValue(_T("DOB_FLAG"), var);
            }
            else if ( fi.m_strName==_T("ÄÐ") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("ñ_ÌÐ_ÊÍÏ") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("BP_CITY"), _T("Ì³ñöå íàðîäæåííÿ: ì³ñòî (ñåëî)"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÐ_ÊÎ") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("BP_REGION"), _T("Ì³ñöå íàðîäæåííÿ: îáëàñòü"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÐ_ÊÐ") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("BP_DISTRICT"), _T("Ì³ñöå íàðîäæåííÿ: ðàéîí"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÐ_ÊÑ") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("BP_COUNTRY"), _T("Ì³ñöå íàðîäæåííÿ: Äåðæàâà"), _T("ÑÌÅÐÒÜ") );
            }

            else if ( fi.m_strName==_T("ÌÏ_Èíäåêñ") ) {
              rsNew.SetFieldValue(_T("RP_ZIPCODE"), var);
            }
            else if ( fi.m_strName==_T("ñ_ÌÏ_ÊÍÏ") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("RP_CITY"), _T("Ì³ñöå ïðîæèâàííÿ: ì³ñòî (ñåëî)"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÏ_ÊÎ") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("RP_REGION"), _T("Ì³ñöå ïðîæèâàííÿ: îáëàñòü"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÏ_ÊÐ") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("RP_DISTRICT"), _T("Ì³ñöå ïðîæèâàííÿ: ðàéîí"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÏ_ÊÑ") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("RP_COUNTRY"), _T("Ì³ñöå ïðîæèâàííÿ: Äåðæàâà"), _T("ÑÌÅÐÒÜ") );
            }
            else if ( fi.m_strName==_T("ñ_ÌÏ_ÊÓ") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("RP_STREET"), _T("Ì³ñöå ïðîæèâàííÿ: âóëèöÿ"), _T("ÑÌÅÐÒÜ"));
            }
            else if ( fi.m_strName==_T("ÌÏ_Äîì") ) {
              try { rsNew.SetFieldValue(_T("RP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÌÏ_Êâàðòèðà") ) {
              try { rsNew.SetFieldValue(_T("RP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Ñâ-òâîÑ") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Ñâ-òâîÍ") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÂÑÑ_Òèï") ) {
              LPCTSTR szValue = NULL;
              switch( var.bVal ) {
                case 1: szValue = _T("Îñòàòî÷íå ë³êàðñüêå ñâ³äîöòâî ïðî ñìåðòü ¹");   break;
                case 2: szValue = _T("Ïîïåðåäíº ë³êàðñüêå ñâ³äîöòâî ïðî ñìåðòü ¹");   break;
                case 3: szValue = _T("Ë³êàðñüêå ñâ³äîöòâî ïðî ñìåðòü ¹");             break;
                case 4: szValue = _T("Ïîâ³äîìëåííÿ óñòàíîâè");                        break;
                case 5: szValue = _T("Îñòàòî÷íå ë³êàðñüêå ñâ³äîöòâî ïðî ñìåðòü");     break;
                case 6: szValue = _T("Ïîïåðåäíº ë³êàðñüêå ñâ³äîöòâî ïðî ñìåðòü");     break;
                case 7: szValue = _T("Ñâ³äîöòâî ïðî ïåðèíàòàëüíó ñìåðòü ¹");          break;
                case 8: szValue = _T("Ð³øåííÿ ñóäó");                                 break;
              }
              if ( szValue ) {
                try { rsNew.SetFieldValue(_T("MEDICAL_CERT_TYPE"), szValue ); }
                catch(CDaoException* e){
                  #ifdef _DEBUG 
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ÂÑÑ_Íîìåð") ) {
              try { rsNew.SetFieldValue(_T("MEDICAL_CERT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ñ_ÂÑÑ_Êîä") ) {
              CString sKey;
              sKey.Format(_T("%d"), var.lVal);
              if ( m_Hospitals.Lookup(sKey, s) && !s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("MEDICAL_CERT_BY"), (LPCTSTR)s); }
                catch(CDaoException* e){
                  #ifdef _DEBUG 
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("ÂÑÑ_Äàòà") ) {
              try { rsNew.SetFieldValue(_T("MEDICAL_CERT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÔÈÎ_Çàÿâèòåëÿ") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_NAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Àäðåñ_Çàÿâèòåëÿ") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Ï_Ñåðèÿ") ) {
              var = rsOld.GetFieldValue(_T("Ï_Ñåðèÿ"));
              s = V_BSTRT(&var);
              if ( !s.IsEmpty() ) {
                try { rsNew.SetFieldValue(_T("PASSPORT_SERIA"), (LPCTSTR)s); }
                catch(CDaoException* e){
                  #ifdef _DEBUG 
                    e->ReportError();
                  #endif
                  e->Delete();
                }
              }
            }
            else if ( fi.m_strName==_T("Ï_Íîìåð") ) {
              try { rsNew.SetFieldValue(_T("PASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Ï_Âûäàí") ) {
              try { rsNew.SetFieldValue(_T("PASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÊîäÐÎÂÄ") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("PASSPORT_BY"), _T("Ïàñïîðò ïîìåðëîãî: êèì âèäàíî"), _T("ÑÌÅÐÒÜ"));
            }
            else if ( fi.m_strName==_T("ÈÍ") ) {
              try { rsNew.SetFieldValue(_T("TAX_CODE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("Ïðèìå÷àíèÿ") ) {
              try { rsNew.SetFieldValue(_T("NOTICE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÏÇ_Ñåðèÿ") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÏÇ_Íîìåð") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÏÇ_Âûäàí") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("ÏÇ_ÐÎÂÄ") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("Ïàñïîðò çàÿâíèêà: êèì âèäàíî"), _T("ÑÌÅÐÒÜ") );
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
