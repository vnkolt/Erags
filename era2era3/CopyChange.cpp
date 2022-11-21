//
// CopyChange.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#include "db.h"

#define szActName _T("�̲��")


void CEra2era3Dlg::CopyChange(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CDaoRecordset rsSubOld(&dbIn), rsSubNew(&dbOut);
  CString sql = _T("SELECT * FROM ����_�_��������");

  try {
    rsOld.Open(dbOpenDynaset, sql);
    rsNew.Open(dbOpenTable, _T("[CHANGES]"));
    rsNew.SetCurrentIndex(_T("NUMBER"));

    rsSubOld.Open(dbOpenTable, _T("[�����]"));
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
        var = rsOld.GetFieldValue(_T("��������"));
        SurnameOld = V_BSTRT(&var);
        var = rsOld.GetFieldValue(_T("�����"));
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
            if ( fi.m_strName==_T("�������") ) {
              DateReg = var;
              try { rsNew.SetFieldValue(_T("DATEREG"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����") ) {
              try { rsNew.SetFieldValue(_T("NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����") ) {
              try { rsNew.SetFieldValue(_T("FLAGS"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("��������") ) {
              rsNew.SetFieldValue(_T("OLDSURNAME"), var);
            }
            else if ( fi.m_strName==_T("��������") ) {
              rsNew.SetFieldValue(_T("NEWSURNAME"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("OLDNAME"), _T("��'� �� ���������"), szActName );
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("NEWNAME"), _T("��'� ϲ��� ���������"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("OLDPATRONYMIC"), _T("�� ������� �� ���������"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("NEWPATRONYMIC"), _T("�� ������� ϲ��� ���������"), szActName );
            }
            else if ( fi.m_strName==_T("���") ) {
            }
            else if ( fi.m_strName==_T("��") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("BIRTH_CITY"), _T("̳��� ����������: ���� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("BIRTH_DISTRICT"), _T("̳��� ����������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("BIRTH_REGION"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("BIRTH_COUNTRY"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("��������") ) {
              rsNew.SetFieldValue(_T("BIRTHACT_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("�������") ) {
              rsNew.SetFieldValue(_T("BIRTHACT_DATE"), var);
            }
            else if ( fi.m_strName==_T("�������") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("BIRTHACT_BY"), _T("��� �������� �� ��� ����������"), szActName );
            }
            else if ( fi.m_strName==_T("�_�����������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("CITIZENSHIP"), _T("������������"), szActName );
            }
            else if ( fi.m_strName==_T("�_��������������") ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("NOTICE"), _T("�������������"), szActName);
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("CITY"), _T("̳��� ����������: ���� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("DISTRICT"), _T("̳��� ����������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("COUNTRY"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("REGION"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("STREET"), _T("̳��� ����������: ������"), szActName );
            }
            else if ( fi.m_strName==_T("��_���") ) {
              try { rsNew.SetFieldValue(_T("HOUSE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��_��������") ) {
              try { rsNew.SetFieldValue(_T("FLAT"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") || fi.m_strName==_T("���")) {
              CString sVal = GetFieldString(&rsOld, fi.m_strName );
              if ( !sVal.IsEmpty() ) {
                rsNew.SetFieldValue(_T("CHECKNUM"), (LPCTSTR)sVal);
              }
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("CHECKDATE"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("CHECKBANK"), _T("����� ��������� ��������"), szActName);
            }
            else if ( fi.m_strName==_T("�������_�") ) {
              rsNew.SetFieldValue(_T("PASSPORT_SERIA"), var);
            }
            else if ( fi.m_strName==_T("�������_�") ) {
              rsNew.SetFieldValue(_T("PASSPORT_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("�������_�") ) {
              rsNew.SetFieldValue(_T("PASSPORT_DATE"), var);
            }
            else if ( fi.m_strName==_T("�������_���") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("PASSPORT_BY"), _T("��� ������ �������"), szActName);
            }
            else if ( fi.m_strName==_T("������") ) {
              rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var);
            }
            else if ( fi.m_strName==_T("������") ) {
              rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var);
            }
            else if ( fi.m_strName==_T("����������") ) {
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
