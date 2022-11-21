//
// Er3ToEr3.cpp
//
#include "stdafx.h"
#include "ImpExp.h"
#include "Er3ToEr3.h"

#include "..\Common\CyrString.h"
#include "..\Common\DaoErr.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL IsEr3DatabaseValid(CDaoDatabase& db) {
  return ( IsTablePresent(db, _T("BIRTHES"))   && 
           IsTablePresent(db, _T("MARRIAGES")) &&
           IsTablePresent(db, _T("DIVORCES"))  &&
           IsTablePresent(db, _T("CHANGES"))   &&
           IsTablePresent(db, _T("DEATHES"))
         );
}

BOOL OpenNewDB(CDaoDatabase& db, LPCTSTR szFileName) {
  BOOL fRet = true;
  try {
    db.Open(szFileName, false, true);
    if ( false==IsEr3DatabaseValid(db) ) {
      db.Close();
      fRet = false;
    }
  }
  catch(CDaoException* e) {
    e->Delete();
    fRet = false;
  }
  if (fRet==false ) {
    try {
      db.Open(szFileName, false, true, _T(";PWD="));
      if ( false==IsEr3DatabaseValid(db) ) {
        db.Close();
        fRet = false;
      }
    }
    catch(CDaoException* e) {
      #ifdef _DEBUG
        e->ReportError();
      #endif
      e->Delete();
      fRet = false;
    }
  }
  return fRet;
}

BOOL IsEr3RecordPresent(CDaoRecordset& rs, const SHORT& Number, const COleDateTime& DateReg, const CString& Surname, LPCTSTR szSurnameFieldName) {
  BOOL fRet = false;
  try {
    if ( false==rs.IsBOF() && false==rs.IsEOF() ) {
      COleVariant bm = rs.GetBookmark();  // ��������� ������� ������� � ����������
      if ( rs.Seek(_T("="), &COleVariant(Number, VT_I2)) ) {
        while ( !rs.IsEOF()) {
          try {
            if (Number  == GetFieldShort(&rs, _T("NUMBER"))        &&
                DateReg == GetFieldOleDateTime(&rs, _T("DATEREG")) &&
                Surname == Trim(GetFieldString(&rs, szSurnameFieldName)) ) { // �� ���������?
              fRet = true;
              break;  // ������ �� ���������
            }
          }
          catch(CDaoException* e) {
            #ifdef _DEBUG
              e->ReportError();
            #endif
            OnMessage(MT_ERROR, FormatDaoError(e));
            e->Delete();
          }
          rs.MoveNext();
        }
      }
      rs.SetBookmark(bm); // ��������������� ������� � ����������
    }
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return fRet;
}

long ImportFromEr3Table(MesssageType mt, LPCTSTR szTypeName, LPCTSTR szTableName, LPCTSTR szCheckField1, LPCTSTR szCheckField2/*=NULL*/) {
  long nImportedRecords = 0;
  CString s;
  CDaoRecordset rsDst(&g_TargetDB);
  CDaoRecordset rsSrc(&g_SourceDB);
  try {
    rsSrc.Open(dbOpenTable, szTableName, dbReadOnly);
    rsDst.Open(dbOpenTable, szTableName, 0);
    rsDst.SetCurrentIndex(_T("NUMBER"));
    while ( !rsSrc.IsEOF() ) {
      g_pProgress->OffsetPos(1);
      try {
        int nImage           = mt;
        SHORT Number         = GetFieldShort(&rsSrc, _T("NUMBER"));
        COleDateTime DateReg = GetFieldOleDateTime(&rsSrc, _T("DATEREG"));
        CString Surname1     = Trim(GetFieldString(&rsSrc, szCheckField1));
        CString Surname2;
        if ( szCheckField2 ) {
          Surname2 = Trim(GetFieldString(&rsSrc, szCheckField2));
        }
        else { // � ������ ������ ���� ���� SEX (BIRTHES or DEATHES)
          if ( GetFieldBool(&rsSrc, _T("SEX")) ) // ���� ������� ���,
            nImage++;                            // ������ ����� ����� ��������� ������ � ������-�����
        }

        if ( g_fNoEmpty && Surname1.IsEmpty() && Surname2.IsEmpty() ) {    // ������� �����?
          goto _Next;
        }
        if( g_Year && g_Year != DateReg.GetYear() ) { // ��� ����������� �� ���������?
          goto _Next;
        }
        if ( g_fNoExist ) { // ��������� ������ �������������� ������?
          if ( IsEr3RecordPresent(rsDst, Number, DateReg, Surname1, szCheckField1) ) {
            if ( szCheckField2 ) {  // ���� �������� ������ �������, ��������� � �� ���.
              if ( IsEr3RecordPresent(rsDst, Number, DateReg, Surname2, szCheckField2) ) {
                goto _Next;
              }
            }
            else {
              goto _Next;
            }
          }
        }

        try {
          rsDst.AddNew(); // ��������� ����� ������.
          for( int i(0); i < rsSrc.GetFieldCount(); i++ ) {
            CDaoFieldInfo fi;
            rsSrc.GetFieldInfo(i, fi);
            if ( fi.m_strName==_T("ID") ) {
              continue; // ������������� ������ ����������� �������������
            }
            if ( IsFieldPresent(rsDst, fi.m_strName) ) { // ���� �� � ����� ���������� ����� �� ����?
              COleVariant var = rsSrc.GetFieldValue(i);
              try {
                rsDst.SetFieldValue(fi.m_strName, var);
              }
              catch(CDaoException* e) {
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          rsDst.Update();
          nImportedRecords++;
          switch( nImage ) {
            case MT_GIRL   :  case MT_BOY     :
            case MT_WDEATH :  case MT_MDEATH  :
              s.Format(_T("���������� �� ��� %s: %s, �� � %d �� %02d.%02d.%04d."),
                       szTypeName, Surname1, Number,
                       DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
              break;
            case MT_MARRIAGE: case MT_DIVORCE :
              s.Format(_T("���������� �� ��� %s: %s �� %s �� � %d �� %02d.%02d.%04d."),
                       szTypeName, Surname1, Surname2, Number,
                       DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
              break;
          }
          OnMessage(nImage, s);
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

long ImportChangesFromEr3() {
  long nImportedRecords = 0;
  CString s;
  CDaoRecordset rsDst(&g_TargetDB);
  CDaoRecordset rsDstDep(&g_TargetDB);
  CDaoRecordset rsSrc(&g_SourceDB);
  CDaoRecordset rsSrcDep(&g_SourceDB);

  try {
    rsSrc.Open(dbOpenTable, _T("CHANGES"), dbReadOnly);
    rsSrcDep.Open(dbOpenTable, _T("CHANGESDEP"), dbReadOnly);
    rsDst.Open(dbOpenTable, _T("CHANGES"), 0);
    rsDstDep.Open(dbOpenTable, _T("CHANGESDEP"), 0);
    rsDst.SetCurrentIndex(_T("NUMBER"));

    while ( !rsSrc.IsEOF() ) {
      g_pProgress->OffsetPos(1);

      try {
        SHORT Number         = GetFieldShort(&rsSrc, _T("NUMBER"));
        COleDateTime DateReg = GetFieldOleDateTime(&rsSrc, _T("DATEREG"));
        CString Surname      = Trim(GetFieldString(&rsSrc, _T("OLDSURNAME")));
        int nImage           = MT_WCHANGE;
        if ( GetFieldBool(&rsSrc, _T("SEX")) ) // ���� ������� ���,
          nImage++;                            // ������ ����� ����� ��������� ������ � ������-�����

        if ( g_fNoEmpty && Surname.IsEmpty() ) {    // ������� �����?
          goto _Next;
        }
        if( g_Year && g_Year != DateReg.GetYear() ) { // ��� ����������� �� ���������?
          goto _Next;
        }
        if ( g_fNoExist && IsEr3RecordPresent(rsDst, Number, DateReg, Surname, _T("OLDSURNAME")) ) { // ��������� ������ �������������� ������?
          goto _Next;
        }

        try {
          long lSrcID = 0; // �������� ���� ��� ����� ����� CHANGES � CHANGESDEP � �����-���������
          rsDst.AddNew();  // ��������� ����� ������.
          for( int i(0); i < rsSrc.GetFieldCount(); i++ ) {
            CDaoFieldInfo fi;
            rsSrc.GetFieldInfo(i, fi);
            if ( fi.m_strName==_T("ID") ) {
              lSrcID = rsSrc.GetFieldValue(_T("ID")).lVal;
              continue; // ������������� ������ ����������� �������������
            }
            if ( IsFieldPresent(rsDst, fi.m_strName) ) { // ���� �� � ����� ���������� ����� �� ����?
              COleVariant var = rsSrc.GetFieldValue(i);
              try {
                rsDst.SetFieldValue(fi.m_strName, var);
              }
              catch(CDaoException* e) {
                #ifdef _DEBUG
                  e->ReportError();
                #endif
                OnMessage(MT_ERROR, FormatDaoError(e));
                e->Delete();
              }
            }
          }
          rsDst.Update();
          s.Format(_T("���������� �� ��� ����: %s �� � %d �� %02d.%02d.%04d."),
                   Surname, Number,
                   DateReg.GetDay(), DateReg.GetMonth(), DateReg.GetYear());
          OnMessage(nImage, s);
          nImportedRecords++;
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
          long lDstID = rsDst.GetFieldValue(_T("ID")).lVal; // �������� ���� ��� ����� ����� CHANGES � CHANGESDEP � �����-��������
          // �������� ������� ������, ���� ��� ����
          rsSrcDep.SetCurrentIndex(_T("ID"));
          try {
            if ( rsSrcDep.Seek(_T("="), &COleVariant(lSrcID, VT_I4)) ) {
              while( !rsSrcDep.IsEOF() ) {
                if ( lSrcID != GetFieldLong(&rsSrcDep, _T("ID")) ) {
                  break;
                }
                rsDstDep.AddNew();  // ��������� ����� ������.
                try {
                  for( int i(0); i < rsSrcDep.GetFieldCount(); i++ ) {
                    CDaoFieldInfo fi;
                    rsSrcDep.GetFieldInfo(i, fi);
                    COleVariant var = rsSrcDep.GetFieldValue(i);
                    if ( fi.m_strName==_T("ID") ) {
                      var.lVal = lDstID; // ������ �������� �������� ����
                    }
                    rsDstDep.SetFieldValue(fi.m_strName, var);
                  }
                  rsDstDep.Update();   // ����������
                }
                catch(CDaoException* e) { // �� ���������� �������� �����-�� ����?
                 #ifdef _DEBUG
                   e->ReportError();
                  #endif
                  OnMessage(MT_ERROR, FormatDaoError(e));
                  e->Delete();
                }
                rsSrcDep.MoveNext(); // ��������� �� ��������� ������
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
        }
        catch(CDaoException* e) {
         #ifdef _DEBUG
           e->ReportError();
         #endif
         OnMessage(MT_ERROR, FormatDaoError(e));
         e->Delete();
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
    rsDst.Close();
    rsSrc.Close();
  }
  catch(CDaoException* e) {
    #ifdef _DEBUG
      e->ReportError();
    #endif
    OnMessage(MT_ERROR, FormatDaoError(e));
    e->Delete();
  }
  return nImportedRecords;
}

long ImportFromEr3() {
  long lRecsInBir = 0;
  long lRecsInMar = 0;
  long lRecsInDiv = 0;
  long lRecsInCha = 0;
  long lRecsInDea = 0;

  if ( g_fBirth ) {
    lRecsInBir  = GetRecordCount(g_SourceDB, _T("BIRTHES"));   // ���������� ������� � ��������
  }
  if ( g_fMarriage ) {
    lRecsInMar  = GetRecordCount(g_SourceDB, _T("MARRIAGES")); // ���������� ������� � �����
  }
  if ( g_fDivorce ) {
    lRecsInDiv  = GetRecordCount(g_SourceDB, _T("DIVORCES"));  // ���������� ������� � ����������� �����
  }
  if ( g_fChange ) {
    lRecsInCha  = GetRecordCount(g_SourceDB, _T("CHANGES"));   // ���������� ������� � ��������
  }
  if ( g_fDeath ) {
    lRecsInDea  = GetRecordCount(g_SourceDB, _T("DEATHES"));   // ���������� ������� � ������
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

  g_pProgress->SetRange32(0, lTotalSrcRecs);
  g_pProgress->SetPos(0);


  if ( lRecsInBir ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ����������..."));
    lImported = ImportFromEr3Table(MT_GIRL, _T("����������"), _T("BIRTHES"),   _T("SURNAME"), NULL);
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ����������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInMar ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ���������..."));
    lImported = ImportFromEr3Table(MT_MARRIAGE, _T("���������"), _T("MARRIAGES"), _T("MOLD_SURNAME"), _T("WOLD_SURNAME"));
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ���������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDiv ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ��������� �����..."));
    lImported = ImportFromEr3Table(MT_DIVORCE, _T("��������� �����"), _T("DIVORCES"),  _T("MOLD_SURNAME"), _T("WOLD_SURNAME"));
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ��������� �����."), lImported);
      OnMessage(MT_INFO, s);
    }
  }
  if ( lRecsInDea ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ������..."));
    lImported = ImportFromEr3Table(MT_WDEATH, _T("������"), _T("DEATHES"),   _T("SURNAME"), NULL);
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ������."), lImported);
      OnMessage(MT_INFO, s);
    }
  }

  if ( lRecsInCha ) {
    g_pInfoBox->SetWindowText(_T("������������ �� ��� ����..."));
    lImported = ImportChangesFromEr3();
    lTotalImported += lImported;
    if ( lImported ) {
      s.Format(_T("����������� %lu ������ ��� ����."), lImported);
      OnMessage(MT_INFO, s);
    }
  }

  g_pInfoBox->SetWindowText(_T("������ ��������."));
  return lTotalImported;
}
