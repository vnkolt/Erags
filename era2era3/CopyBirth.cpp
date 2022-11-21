//
// CopyBirth.cpp
//
#include "stdafx.h"
#include "era2era3.h"
#include "era2era3Dlg.h"

#include "db.h"
#include "DefBirth.h"


#define BIRTH_G10         0x0001   // Const �_�10 = 1  ' ����� 10 {�10: }
#define BIRTH_RENEW       0x0002   // Const �_��� = 2  ' ���������� ��
#define BIRTH_LONGTERM    0x0004   // Const �_��� = 4  ' � ��������� ������
#define BIRTH_NOINLIST    0x0008   // Const �_��� = 8  ' �� � ������ ��������������
#define BIRTH_DECL20      0x0010

#define BIRTH_TYPE_ACT            0 // ������� ����� ��� ����
#define BIRTH_TYPE_MOTHER         1 // ����� ����� �
#define BIRTH_TYPE_PARENTS        2 // ����� ������ �
#define BIRTH_TYPE_APPL           3 // �����
#define BIRTH_TYPE_APPLNUM        4 // ����� �
#define BIRTH_TYPE_AFFILIATION1   5 // ����� ������ ��� �� �
#define BIRTH_TYPE_AFFILIATION2   6 // ������ ����� ��� �� �

#define szActName _T("����������")

CString Trim(LPCTSTR sz);
CString GetFilePath(LPCTSTR szFileName);

CString sCHILD_BP_COUNTRY = _T("������");
CString sCHILD_BP_REGION;
CString sCHILD_BP_DISTRICT;
CString sCHILD_BP_CITY;

void CEra2era3Dlg::CopyBirth(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM ����_�_��������");

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
        var = rsOld.GetFieldValue(_T("��������"));
        Surname = Trim(V_BSTRT(&var));
        var = rsOld.GetFieldValue(_T("�����"));
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
        if ( fOverwrite && rsNew.Seek(_T("="), &var) && rsOld.GetFieldValue(_T("��������"))==rsNew.GetFieldValue(_T("SURNAME")) )
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
            if ( fi.m_strName==_T("�������") ) {
              DateReg = var;
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("��������") ) {
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("RENEW"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
            }
            else if ( fi.m_strName==_T("�������") ) {
              rsNew.SetFieldValue(_T("DATEREG"), var);
            }
            else if ( fi.m_strName==_T("����������") ) {
            }
            else if ( fi.m_strName==_T("���") ) {
              bSex = var.boolVal;
              rsNew.SetFieldValue(_T("SEX"), var);
            }
            else if ( fi.m_strName==_T("���������") ) {
            }
            else if ( fi.m_strName==_T("��������") ) {
              s = GetFieldString(&rsOld, fi.m_strName);
              if ( !s.IsEmpty() )
                rsNew.SetFieldValue(_T("SOURCE_NDOC"), (LPCTSTR)s);
            }
            else if ( fi.m_strName==_T("�������") ) {
              rsNew.SetFieldValue(_T("SOURCE_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_����") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("SOURCE_BY"), _T("��� �������� �� ��� ����"), szActName);
            }
            else if ( fi.m_strName==_T("��������") ) {
            }
            else if ( fi.m_strName==_T("�������") ) {
            }
            else if ( fi.m_strName==_T("��������") ) {
              rsNew.SetFieldValue(_T("SURNAME"), var);
            }
            else if ( fi.m_strName==_T("��������") ) {
              AddToMemo(rsNew, _T("EXTNOTES"), _T("���� �������"), Trim(V_BSTRT(&var)));
            }
            else if ( fi.m_strName==_T("����") ) {
              lOldName = var.lVal;              
              SetName(rsNew, iNumber, DateReg, var, _T("NAME"), _T("��'� ���������������"), szActName);
            }
            else if ( fi.m_strName==_T("�����") && var.lVal!=lOldName) {
              SetName(rsNew, iNumber, DateReg, var, _T("EXTNOTES"), _T("���� ��'� ���������������"), szActName, _T("���� ��'�"));
            }
            else if ( fi.m_strName==_T("���������") ) {
              lOldPatronymic = var.lVal;
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("PATRONYMIC"), _T("�� ������� ���������������"), szActName);
            }
            else if ( fi.m_strName==_T("����������") && var.lVal != lOldPatronymic) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("EXTNOTES"), _T("���� �� ������� ���������������"), szActName, _T("���� �� �������"));
            }
            else if ( fi.m_strName==_T("���������") ) {
              rsNew.SetFieldValue(_T("BIRTH_DATE"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
              fMR = var.boolVal;
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_CITY.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_CITY"), (LPCTSTR)sCHILD_BP_CITY);
              }
              else
                SetCity(rsNew, iNumber, DateReg, var, _T("BP_CITY"), _T("̳��� ����������: ���� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_REGION.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_REGION"), (LPCTSTR)sCHILD_BP_REGION);
              }
              else
                SetRegion(rsNew, iNumber, DateReg, var, _T("BP_REGION"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              if ( (var.vt==NULL || var.lVal==0) ) {
                if ( FALSE==sCHILD_BP_DISTRICT.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_DISTRICT"), (LPCTSTR)sCHILD_BP_DISTRICT);
              }
              else
                SetDistrict(rsNew, iNumber, DateReg, var, _T("BP_DISTRICT"), _T("̳��� ����������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_��_�") ) {
              if ( (var.vt==NULL || var.bVal==0) ) {
                if ( FALSE==sCHILD_BP_COUNTRY.IsEmpty() )
                  rsNew.SetFieldValue(_T("BP_COUNTRY"), (LPCTSTR)sCHILD_BP_COUNTRY);
              }
              else
                SetCountry(rsNew, iNumber, DateReg, var, _T("BP_COUNTRY"), _T("̳��� ����������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("������") ) {
              rsNew.SetFieldValue(_T("NKIDS"), var);
            }
            else if ( fi.m_strName==_T("�������") ) {
              rsNew.SetFieldValue(_T("BYCOUNT"), var);
            }
            else if ( fi.m_strName==_T("�������������") ) {
              rsNew.SetFieldValue(_T("ALIVE_FLAG"), var);
            }
            else if ( fi.m_strName==_T("��������18") ) {
              BYTE b = var.bVal & 0x0F;
              switch(b) {
                case 1: b = 0;  break;  // �_18_��_���� = 1 -> BIRTH_TYPE_ACT=0
                case 2: b = 1;  break;  // �_18_��_�� = 2   -> BIRTH_TYPE_MOTHER=1
                case 3: b = 2;  break;  // �_18_��_�� = 3   -> BIRTH_TYPE_PARENTS=2
                case 4: b = 3;  break;  // �_18_��_� = 4    -> BIRTH_TYPE_APPL=3
                case 5:         break;  // �_18_��_��� = 5  -> BIRTH_TYPE_AFFILIATION1=5
              }
              rsNew.SetFieldValue(_T("SOURCE_TYPE"), &COleVariant(b) );
            }
            else if ( fi.m_strName==_T("���") ) {
              s = GetFieldString(&rsOld, fi.m_strName);
              if ( !s.IsEmpty() )
                rsNew.SetFieldValue(_T("MEDICAL_CERTIFICATE_NUMBER"), (LPCTSTR)s);
            }
            else if ( fi.m_strName==_T("���") ) {
              rsNew.SetFieldValue(_T("MEDICAL_CERTIFICATE_DATE"), var);
            }
            else if ( fi.m_strName==_T("�_��_���") ) {
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
            else if ( fi.m_strName==_T("�������_�") ) {
              try { rsNew.SetFieldValue(_T("FATHER_SURNAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("FATHER_NAME"), _T("��'� ������"), szActName);
            }
            else if ( fi.m_strName==_T("�_���������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("FATHER_PATRONYMIC"), _T("�� ������� ������"), szActName);
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("FATHER_DOB_FLAG"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("FATHER_BIRTH_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_������������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("FATHER_CITIZENSHIP"), _T("������������ ������"), szActName);
            }
            else if ( fi.m_strName==_T("�_���������������") ) {
              SetNation(rsNew, iNumber, DateReg, TRUE, var, _T("EXTNOTES"), _T("������������� ������"), szActName, TRUE);
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("FATHER_COUNTRY"), _T("̳��� ���������� ������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("FATHER_REGION"), _T("̳��� ���������� ������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("FATHER_CITY"), _T("̳��� ���������� ������: ���� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("FATHER_DISTRICT"), _T("̳��� ���������� ������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("FATHER_STREET"), _T("̳��� ���������� ������: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
              try { rsNew.SetFieldValue(_T("FATHER_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_��������") ) {
              try { rsNew.SetFieldValue(_T("FATHER_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_���") ) {
            }
            else if ( fi.m_strName==_T("�������_�") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_SURNAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�������_��") ) {
              AddToMemo(rsNew, _T("EXTNOTES"), _T("���� ������� �����"), Trim(V_BSTRT(&var)));
            }
            else if ( fi.m_strName==_T("����������������") ) {
            }
            else if ( fi.m_strName==_T("�_����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MOTHER_NAME"), _T("��'� �����"), szActName);
            }
            else if ( fi.m_strName==_T("�_���������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MOTHER_PATRONYMIC"), _T("�� ������� �����"), szActName);
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_DOB_FLAG"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_BIRTH_DATE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_������������") ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MOTHER_CITIZENSHIP"), _T("������������ �����"), szActName);
            }
            else if ( fi.m_strName==_T("�_���������������") ) {
              SetNation(rsNew, iNumber, DateReg, FALSE, var, _T("EXTNOTES"), _T("������������� �����"), szActName, TRUE);
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MOTHER_COUNTRY"), _T("̳��� ���������� �����: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MOTHER_REGION"), _T("̳��� ���������� �����: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MOTHER_CITY"), _T("̳��� ���������� �����: ���� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MOTHER_DISTRICT"), _T("̳��� ���������� �����: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MOTHER_STREET"), _T("̳��� ���������� �����: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_HOUSE"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_��������") ) {
              try { rsNew.SetFieldValue(_T("MOTHER_FLAT"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_�") ) {
            }
            else if ( fi.m_strName==_T("��������_���") ) {
            }
            else if ( fi.m_strName==_T("��-�������") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��-�������") ) {
              try { rsNew.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��-�������") ) {
            }
            else if ( fi.m_strName==_T("��-�������") ) {
            }
            else if ( fi.m_strName==_T("���_������������") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_NAME"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����_������������") ) {
              try { rsNew.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
              catch(CDaoException* e){
                #ifdef _DEBUG 
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���_������������") ) {
            }
            else if ( fi.m_strName==_T("�����_������������") ) {
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
              SetROVD(rsNew, iNumber, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("��� ������ ������� ��������"), szActName);
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
