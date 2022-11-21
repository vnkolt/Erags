//
// CopyMarriage.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#define MARRIAGE_PAZ    0x200
#define MARRIAGE_MBIRTH 0x400
#define MARRIAGE_WBIRTH 0x800

#define szActName _T("����")

void CEra2era3Dlg::CopyMarriage(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM ����_�_�����");

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
        var = rsOld.GetFieldValue(_T("���������"));
        SurnameOldM = V_BSTRT(&var);
        rsOld.GetFieldValue(_T("���������"));
        SurnameOldW = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("�����"));
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
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_PAZ;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("���������") ) {
              rsNew.SetFieldValue(_T("MOLD_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("���������") ) {
              rsNew.SetFieldValue(_T("MNEW_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MNAME"), _T("��'� ����������"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MPATRONYMIC"), _T("�� ������� ����������"), szActName );
            }
            else if ( fi.m_strName==_T("����") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_MBIRTH;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("������") ) {
              rsNew.SetFieldValue(_T("MBIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MBIRTH_CITY"), _T("̳��� ���������� ����������: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MBIRTH_REGION"), _T("̳��� ���������� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MBIRTH_DISTRICT"), _T("̳��� ���������� ����������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MBIRTH_COUNTRY"), _T("̳��� ���������� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_������������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MCITIZENSHIP"), _T("������������ ����������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���������������") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("MNOTICE"), _T("������������� ����������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MRP_CITY"), _T("̳��� ���������� ����������: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MRP_DISTRICT"), _T("̳��� ���������� ����������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MRP_REGION"), _T("̳��� ���������� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MRP_COUNTRY"), _T("̳��� ���������� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MRP_STREET"), _T("̳��� ���������� ����������: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
              try { rsNew.SetFieldValue(_T("MRP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_��������") ) {
              try { rsNew.SetFieldValue(_T("MRP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_���") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("MPASSPORT_BY"), _T("������� ����������: ��� ������"), _T("������"));
            }
            else if ( fi.m_strName==_T("������������") ) {
              try { rsNew.SetFieldValue(_T("MFAMILY_STATUS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����������") ) {
              try { rsNew.SetFieldValue(_T("MACT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("MACT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("MACT_BY"), _T("��� �������� ������� ����� ��� ��������� ����� ��� ������ �� ������ ����������"), szActName);
            }
            else if ( fi.m_strName==_T("���������") ) {
              rsNew.SetFieldValue(_T("WOLD_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("���������") ) {
              rsNew.SetFieldValue(_T("WNEW_SURNAME"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("WNAME"), _T("��'� ��������"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("WPATRONYMIC"), _T("�� ������� ��������"), szActName );
            }
            else if ( fi.m_strName==_T("����") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= MARRIAGE_WBIRTH;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("������") ) {
              rsNew.SetFieldValue(_T("WBIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WBIRTH_CITY"), _T("̳��� ���������� ��������: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WBIRTH_REGION"), _T("̳��� ���������� ��������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WBIRTH_DISTRICT"), _T("̳��� ���������� ��������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WBIRTH_COUNTRY"), _T("̳��� ���������� ��������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_������������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("WCITIZENSHIP"), _T("������������ ��������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���������������") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("WNOTICE"), _T("������������� ��������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WRP_CITY"), _T("̳��� ���������� ��������: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WRP_DISTRICT"), _T("̳��� ���������� ��������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WRP_REGION"), _T("̳��� ���������� ��������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WRP_COUNTRY"), _T("̳��� ���������� ��������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("WRP_STREET"), _T("̳��� ���������� ��������: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
              try { rsNew.SetFieldValue(_T("WRP_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_��������") ) {
              try { rsNew.SetFieldValue(_T("WRP_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_���") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("WPASSPORT_BY"), _T("������� ��������: ��� ������"), szActName);
            }
            else if ( fi.m_strName==_T("������������") ) {
              try { rsNew.SetFieldValue(_T("WFAMILY_STATUS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����������") ) {
              try { rsNew.SetFieldValue(_T("WACT_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("WACT_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("WACT_BY"), _T("��� �������� ������� ����� ��� ��������� ����� ��� ������ �� ������ ��������"), szActName);
            }
            else if ( fi.m_strName==_T("���") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����������") ) {
              SetMemo(rsNew, _T("MNOTICE"), var);
            }
            else if ( fi.m_strName==_T("�����������") ) {
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

