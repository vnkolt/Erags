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

#define szActName _T("��ǲ������ �����")


void CEra2era3Dlg::CopyDivorce(int nIndex, CDaoDatabase& dbIn, CDaoDatabase& dbOut) {
  BOOL fOverwrite = m_newFileList.GetCheck(nIndex);
  CDaoRecordset rsOld(&dbIn), rsNew(&dbOut);
  CString sql = _T("SELECT * FROM ����_�_�������");

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
              rsNew.SetFieldValue(_T("NUMBER"), var);
            }
            else if ( fi.m_strName==_T("�����") ) {
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("���") ) {
              rsNew.GetFieldValue(_T("FLAGS"), var);
              var.lVal |= DIVORCE_PAZ;
              rsNew.SetFieldValue(_T("FLAGS"), var);
            }
            else if ( fi.m_strName==_T("������") ) {
              SetRAGS(rsNew, iNumber, DateReg, var, _T("MARRIAGE_BY"), _T("��� �������� ����"), szActName );
            }
            else if ( fi.m_strName==_T("�������") ) {
              try { rsNew.SetFieldValue(_T("MARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("MARRIAGE_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("GROUND"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }

            else if ( fi.m_strName==_T("�������") ) {
              try { rsNew.SetFieldValue(_T("MMARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("MOLD_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("MNEW_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("MNAME"), _T("��'� �������"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("MPATRONYMIC"), _T("�� ������� �������"), szActName );
            }
            else if ( fi.m_strName==_T("����") ) {
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
            else if ( fi.m_strName==_T("���") ) {
              try { rsNew.SetFieldValue(_T("MBIRTH_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_������������") && var.bVal!=0 ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("MCITIZENSHIP"), _T("������������ �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���������������") && var.lVal!=0 ) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, TRUE, var, _T("MNOTICE"), _T("������������� �������"), szActName );
            }

            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("MRP_CITY"), _T("̳��� ���������� �������: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("MRP_DISTRICT"), _T("̳��� ���������� �������: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("MRP_REGION"), _T("̳��� ���������� �������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("MRP_COUNTRY"), _T("̳��� ���������� �������: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("MRP_STREET"), _T("̳��� ���������� �������: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
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
            else if ( fi.m_strName==_T("���_��������") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("MPASSPORT_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_���") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("MPASSPORT_BY"), _T("��� ������ ������� �������"), szActName);
            }
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("MDUTY"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�������") ) {
              try { rsNew.SetFieldValue(_T("MDUTY2"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����������") || fi.m_strName==_T("���") ) {
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
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("MCHECK_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("MCHECK_BANK"), _T("����� ��������� �������� �� ������ �������"), szActName);
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("MCERTIFICATE_SERIA"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("MCERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����������") ) {
              SetMemo(rsNew, _T("MNOTICE"), var);
            }

            else if ( fi.m_strName==_T("�������") ) {
              try { rsNew.SetFieldValue(_T("WMARRIAGE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("WOLD_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("���������") ) {
              try { rsNew.SetFieldValue(_T("WNEW_SURNAME"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�����") ) {
              SetName(rsNew, iNumber, DateReg, var, _T("WNAME"), _T("��'� ����"), szActName );
            }
            else if ( fi.m_strName==_T("����������") ) {
              SetPatronymic(rsNew, iNumber, DateReg, var, _T("WPATRONYMIC"), _T("�� ������� ����"), szActName );
            }
            else if ( fi.m_strName==_T("����") ) {
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
            else if ( fi.m_strName==_T("���") ) {
              try { rsNew.SetFieldValue(_T("WBIRTH_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�_������������") && var.bVal!=0 ) {
              SetCitizen(rsNew, iNumber, DateReg, var, _T("WCITIZENSHIP"), _T("������������ ����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���������������") && var.lVal!=0) {
              SetNationToMemo(rsNew, rsOld, iNumber, DateReg, FALSE, var, _T("WNOTICE"), _T("������������� ����"), szActName );
            }

            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCity(rsNew, iNumber, DateReg, var, _T("WRP_CITY"), _T("̳��� ���������� ����: ̳��� (����)"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetDistrict(rsNew, iNumber, DateReg, var, _T("WRP_DISTRICT"), _T("̳��� ���������� ����: �����"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetRegion(rsNew, iNumber, DateReg, var, _T("WRP_REGION"), _T("̳��� ���������� ����: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetCountry(rsNew, iNumber, DateReg, var, _T("WRP_COUNTRY"), _T("̳��� ���������� ����: �������"), szActName );
            }
            else if ( fi.m_strName==_T("�_���_�") ) {
              SetStreet(rsNew, iNumber, DateReg, var, _T("WRP_STREET"), _T("̳��� ���������� ����: ������"), szActName );
            }
            else if ( fi.m_strName==_T("���_���") ) {
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
            else if ( fi.m_strName==_T("���_��������") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
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
            else if ( fi.m_strName==_T("��������_�") ) {
              try { rsNew.SetFieldValue(_T("WPASSPORT_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("��������_���") ) {
              SetROVD(rsNew, iNumber, DateReg, var, _T("WPASSPORT_BY"), _T("��� ������ ������� ����"), szActName);
            }
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("WDUTY"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("�������") ) {
              try { rsNew.SetFieldValue(_T("WDUTY2"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����������") || fi.m_strName==_T("���") ) {
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
            else if ( fi.m_strName==_T("������") ) {
              try { rsNew.SetFieldValue(_T("WCHECK_DATE"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("������") ) {
              SetBank(rsNew, iNumber, DateReg, var, _T("WCHECK_BANK"), _T("����� ��������� �������� �� ������ ����"), szActName);
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("WCERTIFICATE_SERIA"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
            }
            else if ( fi.m_strName==_T("����") ) {
              try { rsNew.SetFieldValue(_T("WCERTIFICATE_NUMBER"), var); }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                e->Delete();
              }
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

