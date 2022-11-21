//
// Navigate.cpp
//
#include "stdafx.h"
#include "erags.h"
#include "Navigate.h"

#include "DataManager.h"
#include "..\Common\MDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// Death Fillers
//
CFindDeathItem::CFindDeathItem(long lID, short Number, COleDateTime& DateReg)
               :CFindItem(lID, Number, DateReg) {
}

void CDeathFillerFirst::Do() {
  try {
    CDaoRecordset* pRS = new CDaoRecordset(&theDataManager.m_dbYear);
    pRS->Open(dbOpenDynaset, _T("SELECT ID, SEX, DATEREG, NUMBER, SURNAME, NAME, PATRONYMIC FROM DEATHES"), dbReadOnly);
    g_pMachine->AddCommand( new CDeathFillerNext(pRS) );
  }
  catch(CDaoException* e) {
    e->Delete();
  }
}
void CDeathFillerNext::Do() {
  try {
    if ( !m_pRS->IsEOF() ) {
      if ( FALSE==m_pRS->IsDeleted() ) {
        long lID = GetIDField(m_pRS);
      }
      m_pRS->MoveNext();
    }
    else
      g_pMachine->AddCommand( new CDeathFillerLast(m_pRS) );
  }
  catch(CDaoException* e) {
    delete m_pRS;
    e->Delete();
  }
}
void CDeathFillerLast::Do() {
  try {
    m_pRS->Close();
    delete m_pRS;
  }
  catch(CDaoException* e) {
    e->Delete();
  }
}