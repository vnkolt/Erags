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
  CString sql = _T("SELECT * FROM ����_�_������");
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
        var = rsOld.GetFieldValue(_T("�������"));
        Surname = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("�����"));
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
            if ( fi.m_strName==_T("�������") ) {
              DateReg = var;
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
              rsNew.SetFieldValue(_T("RENEW"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("�������") ) {
              rsNew.SetFieldValue(_T("SURNAME"), var);
            }
            else if ( fi.m_strName==_T("����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("NAME"), _T("��'� ������� �����"), _T("������") );
            }
            else if ( fi.m_strName==_T("���������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("PATRONYMIC"), _T("�� ������� ������� �����"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��������������") ) {
              SetNation(rsNew, iNumber, DateReg, bSex, var, _T("NATIONALITY"), _T("�������������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_�����������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("CITIZENSHIP"), _T("������������"), _T("������") );
            }
            else if ( fi.m_strName==_T("���") ) {
              rsNew.SetFieldValue(_T("DOD_FLAG"), var);
            }
            else if ( fi.m_strName==_T("��") ) {
              rsNew.SetFieldValue(_T("DEATH_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_��_���") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("DP_CITY"), _T("̳��� �����: ���� (����)"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("DP_REGION"), _T("̳��� �����: �������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("DP_DISTRICT"), _T("̳��� �����: �����"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("DP_COUNTRY"), _T("̳��� �����: �������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�������������") ) {
              rsNew.SetFieldValue(_T("CAUSE_OF_DEATH"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
              rsNew.SetFieldValue(_T("DOB_FLAG"), var);
            }
            else if ( fi.m_strName==_T("��") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_��_���") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("BP_CITY"), _T("̳��� ����������: ���� (����)"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("BP_REGION"), _T("̳��� ����������: �������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("BP_DISTRICT"), _T("̳��� ����������: �����"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("BP_COUNTRY"), _T("̳��� ����������: �������"), _T("������") );
            }

            else if ( fi.m_strName==_T("��_������") ) {
              rsNew.SetFieldValue(_T("RP_ZIPCODE"), var);
            }
            else if ( fi.m_strName==_T("�_��_���") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("RP_CITY"), _T("̳��� ����������: ���� (����)"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("RP_REGION"), _T("̳��� ����������: �������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("RP_DISTRICT"), _T("̳��� ����������: �����"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("RP_COUNTRY"), _T("̳��� ����������: �������"), _T("������") );
            }
            else if ( fi.m_strName==_T("�_��_��") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("RP_STREET"), _T("̳��� ����������: ������"), _T("������"));
            }
            else if ( fi.m_strName==_T("��_���") ) {
              try { rsNew.SetFieldValue(_T("RP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_��������") ) {
              try { rsNew.SetFieldValue(_T("RP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��-����") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��-����") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_���") ) {
              LPCTSTR szValue = NULL;
              switch( var.bVal ) {
                case 1: szValue = _T("��������� �������� �������� ��� ������ �");   break;
                case 2: szValue = _T("�������� �������� �������� ��� ������ �");   break;
                case 3: szValue = _T("˳������� �������� ��� ������ �");             break;
                case 4: szValue = _T("����������� ��������");                        break;
                case 5: szValue = _T("��������� �������� �������� ��� ������");     break;
                case 6: szValue = _T("�������� �������� �������� ��� ������");     break;
                case 7: szValue = _T("�������� ��� ������������ ������ �");          break;
                case 8: szValue = _T("г����� ����");                                 break;
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
            else if ( fi.m_strName==_T("���_�����") ) {
              try { rsNew.SetFieldValue(_T("MEDICAL_CERT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_���_���") ) {
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
            else if ( fi.m_strName==_T("���_����") ) {
              try { rsNew.SetFieldValue(_T("MEDICAL_CERT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_���������") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_NAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����_���������") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_�����") ) {
              var = rsOld.GetFieldValue(_T("�_�����"));
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
            else if ( fi.m_strName==_T("�_�����") ) {
              try { rsNew.SetFieldValue(_T("PASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_�����") ) {
              try { rsNew.SetFieldValue(_T("PASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�������") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("PASSPORT_BY"), _T("������� ���������: ��� ������"), _T("������"));
            }
            else if ( fi.m_strName==_T("��") ) {
              try { rsNew.SetFieldValue(_T("TAX_CODE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����������") ) {
              try { rsNew.SetFieldValue(_T("NOTICE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_�����") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_�����") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_�����") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_����") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("������� ��������: ��� ������"), _T("������") );
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
