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
  return ( IsTablePresent(db, _T("����_�_��������")) && 
           IsTablePresent(db, _T("����_�_�����"))    &&
           IsTablePresent(db, _T("����_�_�������"))  &&
           // IsTablePresent(db, _T("����_�_��������")) && � ��������� ������ �� ���� ������� ����� �� ����
           IsTablePresent(db, _T("����_�_������"))
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
  if ( false==fRet ) { // �� ���������� ������� ��� ������?
    CString sPWD;
    sPWD.Format(_T(";PWD=%s"), _T("�������������"));
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
  static LPCTSTR szActName = _T("����������");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM ����_�_��������");

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
        var = rsSrc.GetFieldValue(_T("��������"));
        Surname = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("�����"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("�������"));
        if ( GetFieldBool(&rsSrc, _T("���")) ) {
          nImage++;
        }
      } 
      catch(CDaoException* e) {
        e->Delete();
        OnMessage(MT_ERROR, FormatDaoError(e));
      }
      if ( g_fNoEmpty && Surname.IsEmpty() ) {     // ������� �����?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// ��� ����������� �� ���������?
        goto _Next;
      }
      if ( g_fNoExist ) { // ��������� ������ �������������� ������?
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
          if ( fi.m_strName==_T("�������") ) {
            DateReg = var;
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("��������") ) {
          }
          else if ( fi.m_strName==_T("�����") ) {
            dwFlags = (DWORD)var.lVal;
            rsDst.SetFieldValue(_T("RENEW"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
          }
          else if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("����������") ) {
          }
          else if ( fi.m_strName==_T("���") ) {
            bSex = var.boolVal;
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("���������") ) {
          }
          else if ( fi.m_strName==_T("��������") ) {
            s = GetFieldString(&rsSrc, fi.m_strName);
            if ( !s.IsEmpty() )
              rsDst.SetFieldValue(_T("SOURCE_NDOC"), (LPCTSTR)s);
          }
          else if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("SOURCE_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_����") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("SOURCE_BY"), _T("��� �������� �� ��� ����"), szActName);
          }
          else if ( fi.m_strName==_T("��������") ) {
          }
          else if ( fi.m_strName==_T("�������") ) {
          }
          else if ( fi.m_strName==_T("��������") ) {
            rsDst.SetFieldValue(_T("SURNAME"), var);
          }
          else if ( fi.m_strName==_T("��������") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              s.Format(_T("{���� �������: %s} "), Trim(V_BSTRT(&var)));
              szExtMemo += s;
            }
          }
          else if ( fi.m_strName==_T("����") ) {
            lOldName = var.lVal;
            SetName(rsDst, Number, DateReg, var, _T("NAME"), _T("��'� ���������������"), szActName);
          }
          else if ( fi.m_strName==_T("�����") && var.lVal!=lOldName) {
            SetName(rsDst, Number, DateReg, var, _T("EXTNOTES"), _T("���� ��'� ���������������"), szActName, _T("���� ��'�"));
          }
          else if ( fi.m_strName==_T("���������") ) {
            lOldPatronymic = var.lVal;
            SetPatronymic(rsDst, Number, DateReg, var, _T("PATRONYMIC"), _T("�� ������� ���������������"), szActName);
          }
          else if ( fi.m_strName==_T("����������") && var.lVal != lOldPatronymic) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("EXTNOTES"), _T("���� �� ������� ���������������"), szActName, _T("���� �� �������"));
          }
          else if ( fi.m_strName==_T("���������") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            fMR = var.boolVal;
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_CITY.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_CITY"), (LPCTSTR)sCHILD_BP_CITY);
            }
            else
              SetCity(rsDst, Number, DateReg, var, _T("BP_CITY"), _T("̳��� ����������: ���� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_REGION.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_REGION"), (LPCTSTR)sCHILD_BP_REGION);
            }
            else
              SetRegion(rsDst, Number, DateReg, var, _T("BP_REGION"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            if ( (var.vt==NULL || var.lVal==0) ) {
              if ( FALSE==sCHILD_BP_DISTRICT.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_DISTRICT"), (LPCTSTR)sCHILD_BP_DISTRICT);
            }
            else
              SetDistrict(rsDst, Number, DateReg, var, _T("BP_DISTRICT"), _T("̳��� ����������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            if ( (var.vt==NULL || var.bVal==0) ) {
              if ( FALSE==sCHILD_BP_COUNTRY.IsEmpty() )
                rsDst.SetFieldValue(_T("BP_COUNTRY"), (LPCTSTR)sCHILD_BP_COUNTRY);
            }
            else
              SetCountry(rsDst, Number, DateReg, var, _T("BP_COUNTRY"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("������") ) {
            rsDst.SetFieldValue(_T("NKIDS"), var);
          }
          else if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("BYCOUNT"), var);
          }
          else if ( fi.m_strName==_T("�������������") ) {
            rsDst.SetFieldValue(_T("ALIVE_FLAG"), var);
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
            rsDst.SetFieldValue(_T("SOURCE_TYPE"), &COleVariant(b) );
          }
          else if ( fi.m_strName==_T("���") ) {
            s = GetFieldString(&rsSrc, fi.m_strName);
            if ( !s.IsEmpty() )
              rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_NUMBER"), (LPCTSTR)s);
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_��_���") ) {
            s = theMHospitals.Lookup(var.lVal);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MEDICAL_CERTIFICATE_BY"), (LPCTSTR)s); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("�������_�") ) {
            try { rsDst.SetFieldValue(_T("FATHER_SURNAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_����") ) {
            SetName(rsDst, Number, DateReg, var, _T("FATHER_NAME"), _T("��'� ������"), szActName);
          }
          else if ( fi.m_strName==_T("�_���������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("FATHER_PATRONYMIC"), _T("�� ������� ������"), szActName);
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("FATHER_DOB_FLAG"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("FATHER_BIRTH_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_������������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("FATHER_CITIZENSHIP"), _T("������������ ������"), szActName);
          }
          else if ( fi.m_strName==_T("�_���������������") ) {
            SetNation(rsDst, Number, DateReg, TRUE, var, _T("EXTNOTES"), _T("������������� ������"), szActName, TRUE);
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("FATHER_COUNTRY"), _T("̳��� ���������� ������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("FATHER_REGION"), _T("̳��� ���������� ������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("FATHER_CITY"), _T("̳��� ���������� ������: ���� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("FATHER_DISTRICT"), _T("̳��� ���������� ������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("FATHER_STREET"), _T("̳��� ���������� ������: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            try { rsDst.SetFieldValue(_T("FATHER_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            try { rsDst.SetFieldValue(_T("FATHER_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            szMPassportSeria = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            szMPassportNumber = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            MPassportDate = GetFieldOleDateTime(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            szMPassportBy = theROVDs.Lookup( GetFieldLong(&rsSrc, fi.m_strName) );
          }
          else if ( fi.m_strName==_T("�������_�") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_SURNAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�������_��") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              s.Format(_T("{���� ������� �����: %s} "), Trim(V_BSTRT(&var)));
              szExtMemo += s;
            }
          }
          else if ( fi.m_strName==_T("����������������") ) {
          }
          else if ( fi.m_strName==_T("�_����") ) {
            SetName(rsDst, Number, DateReg, var, _T("MOTHER_NAME"), _T("��'� �����"), szActName);
          }
          else if ( fi.m_strName==_T("�_���������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MOTHER_PATRONYMIC"), _T("�� ������� �����"), szActName);
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_DOB_FLAG"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_BIRTH_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_������������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MOTHER_CITIZENSHIP"), _T("������������ �����"), szActName);
          }
          else if ( fi.m_strName==_T("�_���������������") ) {
            SetNation(rsDst, Number, DateReg, FALSE, var, _T("EXTNOTES"), _T("������������� �����"), szActName, TRUE);
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MOTHER_COUNTRY"), _T("̳��� ���������� �����: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MOTHER_REGION"), _T("̳��� ���������� �����: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MOTHER_CITY"), _T("̳��� ���������� �����: ���� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MOTHER_DISTRICT"), _T("̳��� ���������� �����: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MOTHER_STREET"), _T("̳��� ���������� �����: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            try { rsDst.SetFieldValue(_T("MOTHER_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            szWPassportSeria = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            szWPassportNumber = GetFieldString(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            WPassportDate = GetFieldOleDateTime(&rsSrc, fi.m_strName);
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            szWPassportBy = theROVDs.Lookup( GetFieldLong(&rsSrc, fi.m_strName) );
          }
          else if ( fi.m_strName==_T("��-�������") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��-�������") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��-�������") ) {
          }
          else if ( fi.m_strName==_T("��-�������") ) {
          }
          else if ( fi.m_strName==_T("���_������������") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_NAME"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����_������������") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_������������") ) {
          }
          else if ( fi.m_strName==_T("�����_������������") ) {
          }
          else if ( fi.m_strName==_T("����������") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("NOTICE"), var); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��_�����") && false==Trim(V_BSTRT(&var)).IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); fDeclarantPassport = true; }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_�����") && false==Trim(V_BSTRT(&var)).IsEmpty() ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); fDeclarantPassport = true; }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_�����") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_����") && var.lVal != 0 ) {
            SetROVD(rsDst, Number, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("��� ������ ������� ��������"), szActName);
            fDeclarantPassport = true;
          }
        } // for by record fields
        if ( false==szWPassportSeria.IsEmpty() ) {
          // {�2: 3} {���� �2: ��} {����� �2: 3583} {���� ������ �2: 19.02.1999} {��� ������ �2: ��в�� ���� ������ � �������� ������}
          s.Format(_T("{�2: %d} {���� �2: %s} "),
                   GetOldPassportType(dwFlags, false), szWPassportSeria);
          szExtMemo += s;
        }
        if ( false==szWPassportNumber.IsEmpty() ) {
          s.Format(_T("{����� �2: %s} "), szWPassportNumber);
          szExtMemo += s;
        }
        if ( WPassportDate.m_dt != (DATE)0 ) {
          s.Format(_T("{���� ������ �2: %02d.%d.%04d} "), WPassportDate.GetDay(), WPassportDate.GetMonth(), WPassportDate.GetYear());
          szExtMemo += s;
        }
        if ( false==szWPassportBy.IsEmpty() ) {
          s.Format(_T("{��� ������ �2: %s}"), szWPassportBy);
          szExtMemo += s;
        }
        if ( false==fDeclarantPassport ) {
          if ( MPassportDate.m_dt != (DATE)0 && WPassportDate.m_dt != (DATE)0) {
            rsDst.SetFieldValue(_T("DECLARANT_TYPE"), COleVariant((BYTE)2) ); // ��� ���������
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
        s.Format(_T("����������� �� ��� ����������: %s, �� � %d �� %02d.%02d.%04d."),
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
  static LPCTSTR szActName = _T("���������");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM ����_�_�����"), s;

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
        var = rsSrc.GetFieldValue(_T("���������"));
        SurnameOldM = Trim(V_BSTRT(&var));
        rsSrc.GetFieldValue(_T("���������"));
        SurnameOldW = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("�����"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("�������"));
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && SurnameOldM.IsEmpty() && SurnameOldW.IsEmpty() ) { // ������� �����?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// ��� ����������� �� ���������?
        goto _Next;
      }
      if ( g_fNoExist ) { // ��������� ������ �������������� ������?
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

          if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            dwFlags = (DWORD)var.lVal;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_PAZ;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("���������") ) {
            rsDst.SetFieldValue(_T("MOLD_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("���������") ) {
            rsDst.SetFieldValue(_T("MNEW_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("MNAME"), _T("��'� ����������"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MPATRONYMIC"), _T("�� ������� ����������"), szActName );
          }
          else if ( fi.m_strName==_T("����") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_MBIRTH;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("������") ) {
            rsDst.SetFieldValue(_T("MBIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MBIRTH_CITY"), _T("̳��� ���������� ����������: �_��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MBIRTH_REGION"), _T("̳��� ���������� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MBIRTH_DISTRICT"), _T("̳��� ���������� ����������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MBIRTH_COUNTRY"), _T("̳��� ���������� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_������������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MCITIZENSHIP"), _T("������������ ����������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���������������") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("MNOTICE"), _T("������������� ����������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MRP_CITY"), _T("̳��� ���������� ����������: ̳��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MRP_DISTRICT"), _T("̳��� ���������� ����������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MRP_REGION"), _T("̳��� ���������� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MRP_COUNTRY"), _T("̳��� ���������� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MRP_STREET"), _T("̳��� ���������� ����������: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            try { rsDst.SetFieldValue(_T("MRP_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            try { rsDst.SetFieldValue(_T("MRP_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("MPASSPORT_BY"), _T("������� ����������: ��� ������"), _T("������"));
          }
          else if ( fi.m_strName==_T("������������") ) {
            try { rsDst.SetFieldValue(_T("MFAMILY_STATUS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����������") ) {
            try { rsDst.SetFieldValue(_T("MACT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("MACT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("MACT_BY"), _T("��� �������� ������� ����� ��� ���_������ ����� ��� ������ �� ������ ����������"), szActName);
          }
          else if ( fi.m_strName==_T("���������") ) {
            rsDst.SetFieldValue(_T("WOLD_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("���������") ) {
            rsDst.SetFieldValue(_T("WNEW_SURNAME"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("WNAME"), _T("��'� ��������"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("WPATRONYMIC"), _T("�� ������� ��������"), szActName );
          }
          else if ( fi.m_strName==_T("����") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= MARRIAGE_WBIRTH;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("������") ) {
            rsDst.SetFieldValue(_T("WBIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WBIRTH_CITY"), _T("̳��� ���������� ��������: �_��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WBIRTH_REGION"), _T("̳��� ���������� ��������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WBIRTH_DISTRICT"), _T("̳��� ���������� ��������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WBIRTH_COUNTRY"), _T("̳��� ���������� ��������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_������������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("WCITIZENSHIP"), _T("������������ ��������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���������������") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("WNOTICE"), _T("���_������_��� ��������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WRP_CITY"), _T("̳��� ���������� ��������: �_��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WRP_DISTRICT"), _T("̳��� ���������� ��������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WRP_REGION"), _T("̳��� ���������� ��������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WRP_COUNTRY"), _T("̳��� ���������� ��������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("WRP_STREET"), _T("̳��� ���������� ��������: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            try { rsDst.SetFieldValue(_T("WRP_HOUSE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            try { rsDst.SetFieldValue(_T("WRP_FLAT"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("WPASSPORT_BY"), _T("������� ��������: ��� ������"), szActName);
          }
          else if ( fi.m_strName==_T("������������") ) {
            try { rsDst.SetFieldValue(_T("WFAMILY_STATUS"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����������") ) {
            try { rsDst.SetFieldValue(_T("WACT_NUMBER"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("WACT_DATE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("WACT_BY"), _T("��� �������� ������� ����� ��� ���_������ ����� ��� ������ �� ������ ��������"), szActName);
          }
          else if ( fi.m_strName==_T("���") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����������") ) {
            try { rsDst.SetFieldValue(_T("MNOTICE"), var); }
            catch(CDaoException* e){
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����������") ) {
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
          s.Format(_T("���������� �� ��� %s: %s �� %s, �� � %d �� %02d.%02d.%04d."),
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
  static LPCTSTR szActName = _T("��ǲ������ �����");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CString sql = _T("SELECT * FROM ����_�_�������"), s;

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
        var = rsSrc.GetFieldValue(_T("���������"));
        SurnameOldM = Trim(V_BSTRT(&var));
        rsSrc.GetFieldValue(_T("���������"));
        SurnameOldW = Trim(V_BSTRT(&var));
        var = rsSrc.GetFieldValue(_T("�����"));
        Number = var.iVal;
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && SurnameOldM.IsEmpty() && SurnameOldW.IsEmpty() ) { // ������� �����?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// ��� ����������� �� ���������?
        goto _Next;
      }
      if ( g_fNoExist ) { // ��������� ������ �������������� ������?
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

          if ( fi.m_strName==_T("�������") ) {
            DateReg = var;
            try { rsDst.SetFieldValue(_T("DATEREG"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.GetFieldValue(_T("FLAGS"), var);
            var.lVal |= DIVORCE_PAZ;
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("������") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("MARRIAGE_BY"), _T("��� �������� ����"), szActName );
          }
          else if ( fi.m_strName==_T("�������") ) {
            try { rsDst.SetFieldValue(_T("MARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("MARRIAGE_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("GROUND"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }

          else if ( fi.m_strName==_T("�������") ) {
            try { rsDst.SetFieldValue(_T("MMARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("MOLD_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("MNEW_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("MNAME"), _T("��'� �����_��"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("MPATRONYMIC"), _T("�� ������� �����_��"), szActName );
          }
          else if ( fi.m_strName==_T("����") ) {
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
          else if ( fi.m_strName==_T("���") ) {
            try { rsDst.SetFieldValue(_T("MBIRTH_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_������������") && var.bVal!=0 ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("MCITIZENSHIP"), _T("������������ �����_��"), szActName );
          }
          else if ( fi.m_strName==_T("�_���������������") && var.lVal!=0 ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("MNOTICE"), _T("���_������_��� �����_��"), szActName );
          }

          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("MRP_CITY"), _T("̳��� ���������� �����_��: �_��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("MRP_DISTRICT"), _T("̳��� ���������� �����_��: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("MRP_REGION"), _T("̳��� ���������� �����_��: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("MRP_COUNTRY"), _T("̳��� ���������� �����_��: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("MRP_STREET"), _T("̳��� ���������� �����_��: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            CString s = GetFieldString(&rsDst, _T("MRP_HOUSE"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MRP_HOUSE"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            CString s = GetFieldString(&rsDst, _T("MRP_FLAT"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MRP_FLAT"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            CString s = GetFieldString(&rsDst, _T("MPASSPORT_SERIA"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MPASSPORT_SERIA"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            CString s = GetFieldString(&rsDst, _T("MPASSPORT_NUMBER"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MPASSPORT_NUMBER"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("MPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("MPASSPORT_BY"), _T("��� ������ ������� �����_��"), szActName);
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("MDUTY"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�������") ) {
            try { rsDst.SetFieldValue(_T("MDUTY2"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����������") || fi.m_strName==_T("���") ) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MCHECK_NUMBER"), (LPCTSTR)sVal); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("MCHECK_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            SetBank(rsDst, Number, DateReg, var, _T("MCHECK_BANK"), _T("����� ��������� �������� �� ������ �����_��"), szActName);
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("MCERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("MCERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����������") ) {
            s = Trim(V_BSTRT(&var));
            if ( false==s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MNOTICE"), var); }
              catch(CDaoException* e){
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }

          else if ( fi.m_strName==_T("�������") ) {
            try { rsDst.SetFieldValue(_T("WMARRIAGE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("WOLD_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") ) {
            try { rsDst.SetFieldValue(_T("WNEW_SURNAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("WNAME"), _T("��'� ����"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("WPATRONYMIC"), _T("�� ������� ����"), szActName );
          }
          else if ( fi.m_strName==_T("����") ) {
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
          else if ( fi.m_strName==_T("���") ) {
            try { rsDst.SetFieldValue(_T("WBIRTH_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_������������") && var.bVal!=0 ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("WCITIZENSHIP"), _T("������������ ����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���������������") && var.lVal!=0) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, FALSE, var, _T("WNOTICE"), _T("���_������_��� ����"), szActName );
          }

          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("WRP_CITY"), _T("̳��� ���������� ����: �_��� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("WRP_DISTRICT"), _T("̳��� ���������� ����: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("WRP_REGION"), _T("̳��� ���������� ����: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("WRP_COUNTRY"), _T("̳��� ���������� ����: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_���_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("WRP_STREET"), _T("̳��� ���������� ����: ������"), szActName );
          }
          else if ( fi.m_strName==_T("���_���") ) {
            CString s = GetFieldString(&rsDst, _T("WRP_HOUSE"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WRP_HOUSE"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("���_��������") ) {
            CString s = GetFieldString(&rsDst, _T("WRP_FLAT"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WRP_FLAT"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            CString s = GetFieldString(&rsDst, _T("WPASSPORT_SERIA"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WPASSPORT_SERIA"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            CString s = GetFieldString(&rsDst, _T("WPASSPORT_NUMBER"));
            if ( s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WPASSPORT_NUMBER"), var); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("��������_�") ) {
            try { rsDst.SetFieldValue(_T("WPASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��������_���") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("WPASSPORT_BY"), _T("��� ������ ������� ����"), szActName);
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("WDUTY"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�������") ) {
            try { rsDst.SetFieldValue(_T("WDUTY2"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����������") || fi.m_strName==_T("���") ) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("WCHECK_NUMBER"), (LPCTSTR)sVal); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            try { rsDst.SetFieldValue(_T("WCHECK_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("������") ) {
            SetBank(rsDst, Number, DateReg, var, _T("WCHECK_BANK"), _T("����� ��������� �������� �� ������ ����"), szActName);
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("WCERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����") ) {
            try { rsDst.SetFieldValue(_T("WCERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����������") ) {
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
          s.Format(_T("���������� �� ��� %s: %s �� %s, �� � %d �� %02d.%02d.%04d."),
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
  static LPCTSTR szActName = _T("�̲��");
  CDaoRecordset rsSrc(&g_SourceDB), rsDst(&g_TargetDB);
  CDaoRecordset rsSubOld(&g_SourceDB), rsSubNew(&g_TargetDB);
  CString sql = _T("SELECT * FROM ����_�_��������");

  long nImportedRecords = 0;
  CString s;

  try {
    rsSrc.Open(dbOpenDynaset, sql);
    rsDst.Open(dbOpenTable, _T("[CHANGES]"));
    rsDst.SetCurrentIndex(_T("NUMBER"));

    rsSubOld.Open(dbOpenTable, _T("[�����]"));
    rsSubOld.SetCurrentIndex(_T("ID"));
    rsSubNew.Open(dbOpenTable, _T("[CHANGESDEP]"));
    rsSubNew.SetCurrentIndex(_T("ID"));

    int nFields = rsSrc.GetFieldCount();

    while ( !rsSrc.IsEOF() ) {
      CDWordArray array;
      short   Number = -1;
      long    lSrcID = 0; // �������� ���� ��� ����� ����� ����_�_�������� � ����� � �����-���������
      long    lDstID = 0; // �������� ���� ��� ����� ����� CHANGES � CHANGESDEP � �����-��������
      COleVariant var;
      COleDateTime DateReg;
      CString SurnameOld;
      int nImage = MT_WCHANGE;
      VARIANT_BOOL bSex = FALSE;


      g_pProgress->OffsetPos(1);

      try {
        var = rsSrc.GetFieldValue(_T("ID"));
        lSrcID = var.lVal;
        var = rsSrc.GetFieldValue(_T("�����"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("�������"));
        var = rsSrc.GetFieldValue(_T("��������"));
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

      if ( g_fNoEmpty && SurnameOld.IsEmpty() ) {  // ������� �����?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// ��� ����������� �� ���������?
        goto _Next;
      }
      if ( g_fNoExist ) { // ��������� ������ �������������� ������?
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
          if ( fi.m_strName==_T("�������") ) {
            DateReg = var;
            try { rsDst.SetFieldValue(_T("DATEREG"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            try { rsDst.SetFieldValue(_T("NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            try { rsDst.SetFieldValue(_T("FLAGS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���") ) {
            bSex = var.boolVal;
            if ( bSex ) {
              nImage++;
            }
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("��������") ) {
            rsDst.SetFieldValue(_T("OLDSURNAME"), var);
          }
          else if ( fi.m_strName==_T("��������") ) {
            rsDst.SetFieldValue(_T("NEWSURNAME"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("OLDNAME"), _T("��'� �� ���������"), szActName );
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetName(rsDst, Number, DateReg, var, _T("NEWNAME"), _T("��'� ϲ��� ���������"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("OLDPATRONYMIC"), _T("�� ������� �� ���������"), szActName );
          }
          else if ( fi.m_strName==_T("����������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("NEWPATRONYMIC"), _T("�� ������� ϲ��� ���������"), szActName );
          }
          else if ( fi.m_strName==_T("���") ) {
          }
          else if ( fi.m_strName==_T("��") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("BIRTH_CITY"), _T("̳��� ����������: ���� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("BIRTH_DISTRICT"), _T("̳��� ����������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("BIRTH_REGION"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("BIRTH_COUNTRY"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("��������") ) {
            rsDst.SetFieldValue(_T("BIRTHACT_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("BIRTHACT_DATE"), var);
          }
          else if ( fi.m_strName==_T("�������") ) {
            SetRAGS(rsDst, Number, DateReg, var, _T("BIRTHACT_BY"), _T("��� �������� �� ��� ����������"), szActName );
          }
          else if ( fi.m_strName==_T("�_�����������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("CITIZENSHIP"), _T("������������"), szActName );
          }
          else if ( fi.m_strName==_T("�_��������������") ) {
            SetNationToMemo(rsDst, rsSrc, Number, DateReg, TRUE, var, _T("NOTICE"), _T("���_������_���"), szActName);
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetCity(rsDst, Number, DateReg, var, _T("CITY"), _T("̳��� ����������: ���� (����)"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("DISTRICT"), _T("̳��� ����������: �����"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("COUNTRY"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("REGION"), _T("̳��� ����������: �������"), szActName );
          }
          else if ( fi.m_strName==_T("�_��_�") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("STREET"), _T("̳��� ����������: ������"), szActName );
          }
          else if ( fi.m_strName==_T("��_���") ) {
            try { rsDst.SetFieldValue(_T("HOUSE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_��������") ) {
            try { rsDst.SetFieldValue(_T("FLAT"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���������") || fi.m_strName==_T("���")) {
            CString sVal = GetFieldString(&rsSrc, fi.m_strName );
            if ( !sVal.IsEmpty() ) {
              rsDst.SetFieldValue(_T("CHECKNUM"), (LPCTSTR)sVal);
            }
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("CHECKDATE"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            SetBank(rsDst, Number, DateReg, var, _T("CHECKBANK"), _T("����� ��������� ��������"), szActName);
          }
          else if ( fi.m_strName==_T("�������_�") ) {
            rsDst.SetFieldValue(_T("PASSPORT_SERIA"), var);
          }
          else if ( fi.m_strName==_T("�������_�") ) {
            rsDst.SetFieldValue(_T("PASSPORT_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("�������_�") ) {
            rsDst.SetFieldValue(_T("PASSPORT_DATE"), var);
          }
          else if ( fi.m_strName==_T("�������_���") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("PASSPORT_BY"), _T("��� ������ �������"), szActName);
          }
          else if ( fi.m_strName==_T("������") ) {
            rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var);
          }
          else if ( fi.m_strName==_T("������") ) {
            rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var);
          }
          else if ( fi.m_strName==_T("����������") ) {
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
        s.Format(_T("���������� �� ��� %s: %s, �� � %d �� %02d.%02d.%04d."),
                 szActName, SurnameOld, Number,
                 DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
        OnMessage(nImage, s);
      }
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      try {
         rsDst.SetBookmark( rsDst.GetLastModifiedBookmark() ); // ���������� ��� ������������ ������ �� rsDst
      }
      catch(CDaoException* e) {
        #ifdef _DEBUG
           e->ReportError();
        #endif
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }
      lDstID = rsDst.GetFieldValue(_T("ID")).lVal; // �������� ���� ��� ����� ����� CHANGES � CHANGESDEP � �����-��������
      // �������� ������� ������, ���� ��� ����
      rsSubOld.SetCurrentIndex(_T("ID"));
      try {
        if ( rsSubOld.Seek(_T("="), &COleVariant(lSrcID, VT_I4)) ) {
          while( !rsSubOld.IsEOF() ) {
            if ( lSrcID != GetFieldLong(&rsSubOld, _T("ID")) ) {
              break;
            }
            try { rsSubNew.AddNew();  // ��������� ����� ������ ��� ���������� ����.
              for( int i(0); i < rsSubOld.GetFieldCount(); i++ ) {
                LPCTSTR szActType = _T("");
                CDaoFieldInfo fi;
                rsSubOld.GetFieldInfo(i, fi);
                var = rsSubOld.GetFieldValue(i);
                if ( fi.m_strName==_T("ID") ) {
                  var.lVal = lDstID; // ������ �������� �������� ����
                  rsSubNew.SetFieldValue(fi.m_strName, var);
                }
                else if ( fi.m_strName==_T("���") )     { // ��� ���������� ����
                  switch( var.bVal ) {
                    case 1: // ����������
                      var.bVal = UCHAR('�'); szActType = _T("����������");
                      break;
                    case 2: // ������������ ����������
                      var.bVal = UCHAR('�'); szActType = _T("������������ ����������");
                      break;
                    case 3: // ����
                      var.bVal = UCHAR('�'); szActType = _T("����");
                      break;
                    case 4: // ��������� �����
                      var.bVal = UCHAR('�'); szActType = _T("��������� �����");
                      break;
                    case 5: // ����
                      var.bVal = UCHAR('�'); szActType = _T("����");
                      break;
                  }
                  rsSubNew.SetFieldValue(_T("TYPE"), var);
                }
                else if ( fi.m_strName==_T("���") )     { // ����� ���������� ����
                  rsSubNew.SetFieldValue(_T("NUMBER"), var);
                }
                else if ( fi.m_strName==_T("�������") ) { // ���� ����������� ���������� ����
                  rsSubNew.SetFieldValue(_T("DATEREG"), var);
                }
                else if ( fi.m_strName==_T("����") )    { // ��� ��������������� ��������� ���
                  s.Format(_T("��� �������� �� ��� %s"), szActType);
                  SetRAGS(rsSubNew, Number, DateReg, var, _T("REGISTRAR"), s, szActName);
                }
              } // for( int i(0); i < rsSubOld.GetFieldCount(); i++ )
              rsSubNew.Update();
            } // try rsSubNew.AddNew();
            catch(CDaoException* e) { // �� ���������� �������� �����-�� ����?
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
            rsSubOld.MoveNext(); // ��������� �� ��������� ������
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
  CString sql = _T("SELECT * FROM ����_�_������"), s;
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
        var = rsSrc.GetFieldValue(_T("�������"));
        Surname = V_BSTRT(&var);
        var = rsSrc.GetFieldValue(_T("�����"));
        Number = var.iVal;
        DateReg = GetFieldOleDateTime(&rsSrc, _T("�������"));
      } 
      catch(CDaoException* e) {
        OnMessage(MT_ERROR, FormatDaoError(e));
        e->Delete();
      }

      if ( g_fNoEmpty && Surname.IsEmpty() ) {     // ������� �����?
        goto _Next;
      }
      if( g_Year && g_Year != DateReg.GetYear() ) {// ��� ����������� �� ���������?
        goto _Next;
      }
      if ( g_fNoExist ) { // ��������� ������ �������������� ������?
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
          if ( fi.m_strName==_T("�������") ) {
            DateReg = var;
            rsDst.SetFieldValue(_T("DATEREG"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("NUMBER"), var);
          }
          else if ( fi.m_strName==_T("�����") ) {
            rsDst.SetFieldValue(_T("FLAGS"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.SetFieldValue(_T("RENEW"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            bSex = var.boolVal;
            rsDst.SetFieldValue(_T("SEX"), var);
          }
          else if ( fi.m_strName==_T("�������") ) {
            rsDst.SetFieldValue(_T("SURNAME"), var);
          }
          else if ( fi.m_strName==_T("����") ) {
            SetName(rsDst, Number, DateReg, var, _T("NAME"), _T("��'� ������� �����"), _T("������") );
          }
          else if ( fi.m_strName==_T("���������") ) {
            SetPatronymic(rsDst, Number, DateReg, var, _T("PATRONYMIC"), _T("�� ������� ������� �����"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��������������") ) {
            // SetNation(rsDst, Number, DateReg, bSex, var, _T("NATIONALITY"), _T("�������������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_�����������") ) {
            SetCitizen(rsDst, Number, DateReg, var, _T("CITIZENSHIP"), _T("������������"), _T("������") );
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.SetFieldValue(_T("DOD_FLAG"), var);
          }
          else if ( fi.m_strName==_T("��") ) {
            rsDst.SetFieldValue(_T("DEATH_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_��_���") ) {
            SetCity(rsDst, Number, DateReg, var, _T("DP_CITY"), _T("̳��� �����: ���� (����)"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("DP_REGION"), _T("̳��� �����: �������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("DP_DISTRICT"), _T("̳��� �����: �����"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("DP_COUNTRY"), _T("̳��� �����: �������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�������������") ) {
            rsDst.SetFieldValue(_T("CAUSE_OF_DEATH"), var);
          }
          else if ( fi.m_strName==_T("���") ) {
            rsDst.SetFieldValue(_T("DOB_FLAG"), var);
          }
          else if ( fi.m_strName==_T("��") ) {
            rsDst.SetFieldValue(_T("BIRTH_DATE"), var);
          }
          else if ( fi.m_strName==_T("�_��_���") ) {
            SetCity(rsDst, Number, DateReg, var, _T("BP_CITY"), _T("̳��� ����������: ���� (����)"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("BP_REGION"), _T("̳��� ����������: �������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("BP_DISTRICT"), _T("̳��� ����������: �����"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("BP_COUNTRY"), _T("̳��� ����������: �������"), _T("������") );
          }

          else if ( fi.m_strName==_T("��_������") ) {
            rsDst.SetFieldValue(_T("RP_ZIPCODE"), var);
          }
          else if ( fi.m_strName==_T("�_��_���") ) {
            SetCity(rsDst, Number, DateReg, var, _T("RP_CITY"), _T("̳��� ����������: ���� (����)"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetRegion(rsDst, Number, DateReg, var, _T("RP_REGION"), _T("̳��� ����������: �������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetDistrict(rsDst, Number, DateReg, var, _T("RP_DISTRICT"), _T("̳��� ����������: �����"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetCountry(rsDst, Number, DateReg, var, _T("RP_COUNTRY"), _T("̳��� ����������: �������"), _T("������") );
          }
          else if ( fi.m_strName==_T("�_��_��") ) {
            SetStreet(rsDst, Number, DateReg, var, _T("RP_STREET"), _T("̳��� ����������: ������"), _T("������"));
          }
          else if ( fi.m_strName==_T("��_���") ) {
            try { rsDst.SetFieldValue(_T("RP_HOUSE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_��������") ) {
            try { rsDst.SetFieldValue(_T("RP_FLAT"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��-����") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��-����") ) {
            try { rsDst.SetFieldValue(_T("CERTIFICATE_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
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
              try { rsDst.SetFieldValue(_T("MEDICAL_CERT_TYPE"), szValue ); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("���_�����") ) {
            try { rsDst.SetFieldValue(_T("MEDICAL_CERT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_���_���") ) {
            s = theHospitals.Lookup(var.lVal);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("MEDICAL_CERT_BY"), (LPCTSTR)s); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("���_����") ) {
            try { rsDst.SetFieldValue(_T("MEDICAL_CERT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("���_���������") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_NAME"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�����_���������") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_ADDRESS"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_�����") ) {
            var = rsSrc.GetFieldValue(_T("�_�����"));
            s = V_BSTRT(&var);
            if ( !s.IsEmpty() ) {
              try { rsDst.SetFieldValue(_T("PASSPORT_SERIA"), (LPCTSTR)s); }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          else if ( fi.m_strName==_T("�_�����") ) {
            try { rsDst.SetFieldValue(_T("PASSPORT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�_�����") ) {
            try { rsDst.SetFieldValue(_T("PASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("�������") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("PASSPORT_BY"), _T("������� ���������: ��� ������"), _T("������"));
          }
          else if ( fi.m_strName==_T("��") ) {
            try { rsDst.SetFieldValue(_T("TAX_CODE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("����������") ) {
            try { rsDst.SetFieldValue(_T("NOTICE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_�����") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_SERIA"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_�����") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_NUMBER"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_�����") ) {
            try { rsDst.SetFieldValue(_T("DECLARANT_PASSPORT_DATE"), var); }
            catch(CDaoException* e) {
              OnMessage(MT_ERROR, FormatDaoError(e));
              e->Delete();
            }
          }
          else if ( fi.m_strName==_T("��_����") ) {
            SetROVD(rsDst, Number, DateReg, var, _T("DECLARANT_PASSPORT_BY"), _T("������� ��������: ��� ������"), _T("������") );
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
    lRecsInBir  = GetRecordCount(g_SourceDB, _T("����_�_��������")); // ���������� ������� � ��������
  }
  if ( g_fMarriage ) {
    lRecsInMar  = GetRecordCount(g_SourceDB, _T("����_�_�����"));    // ���������� ������� � �����
  }
  if ( g_fDivorce ) {
    lRecsInDiv  = GetRecordCount(g_SourceDB, _T("����_�_�������"));  // ���������� ������� � ����������� �����
  }
  if ( g_fChange && IsTablePresent(g_SourceDB, _T("����_�_��������")) ) {
    lRecsInCha  = GetRecordCount(g_SourceDB, _T("����_�_��������")); // ���������� ������� � ��������
  }
  if ( g_fDeath ) {
    lRecsInDea  = GetRecordCount(g_SourceDB, _T("����_�_������"));   // ���������� ������� � ������
  }
  long lTotalSrcRecs = lRecsInBir + lRecsInMar + lRecsInDiv + lRecsInCha + lRecsInDea;

  CString s;

  s.Format(_T("������ �� �� \"%s\"."), g_szSourceFile);
  OnMessage(MT_INFO, s);

  if ( 0 == lTotalSrcRecs ) {
    g_pProgress->ShowWindow(SW_HIDE); // � ����� ����� �����������?
    s.Format(_T("�� ���� ����� ��� ������� � ���� �� \"%s\"."), g_szSourceFile);
    OnMessage(MT_WARNING, s);
    return 0;  // Nothing to do because src database is empty.
  }
  long lTotalImported(0), lImported(0);

  // ��������� ����
  theNames      .Fill(g_SourceDB, _T("�����"),          _T("��������"),    _T("���")      );
  thePatronymics.Fill(g_SourceDB, _T("��������"),       _T("�����������"), _T("��������") );
  theBanks      .Fill(g_SourceDB, _T("�����"),          _T("���"),         _T("����")     );
  theCountries  .Fill(g_SourceDB, _T("���������"),      _T("���_������"),  _T("������"),      _T("�����������") );
  theRegions    .Fill(g_SourceDB, _T("����������"),     _T("����"),        _T("�������")  );
  theCities     .Fill(g_SourceDB, _T("�����"),          _T("��� ��"),      _T("��������"),  _T("��") );
  theDistricts  .Fill(g_SourceDB, _T("���������"),      _T("��� ������"),  _T("�����")    );
  theStreets    .Fill(g_SourceDB, _T("��������"),       _T("���"),         _T("�����")    );
  theNations    .Fill(g_SourceDB, _T("��������������"), _T("���"),         _T("������"),     _T("Ƴ���") );
  theRAGSes     .Fill(g_SourceDB, _T("�����"),          _T("���"),         _T("����")     );
  theROVDs      .Fill(g_SourceDB, _T("����"),           _T("���"),         _T("�������_�����")     );
  theMHospitals .Fill(g_SourceDB, _T("�������"),        _T("���"),         _T("��������") );
  theHospitals  .Fill(g_SourceDB, _T("��������"),       _T("���"),         _T("��������") );
 
  if ( lRecsInBir ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ����������..."));
    lImported = ImportFromOldBirth();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ����������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInMar ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ���������..."));
    lImported = ImportFromOldMarriage();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ���������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDiv ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ��������� �����..."));
    lImported = ImportFromOldDivorce();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ��������� �����."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDea ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ������..."));
    lImported = ImportFromOldDeath();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInCha ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ����..."));
    lImported = ImportFromOldChange();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ����."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  g_pInfoBox->SetWindowText(_T("������ ��������."));

  return lTotalImported;
}