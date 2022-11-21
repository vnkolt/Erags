#if !defined(NAVIGATE_H_INCLUDED)
#define NAVIGATE_H_INCLUDED

// Navigate.h

#include "xMachine.h"

#pragma warning(disable : 4995)

class CFindItem : public CObject {
public:
  long          m_ID;
  short         m_Number;
  COleDateTime  m_DateReg;
public:
  CFindItem(long lID, short Number, COleDateTime& DateReg) {
    m_ID = lID;
    m_Number = Number;
    m_DateReg = DateReg;
  }
};

class CFindDeathItem : public CFindItem {
public:
  CFindDeathItem(long lID, short Number, COleDateTime& DateReg);
};

class CDeathFillerFirst : public CXCommand {
public:
  void Do();
};
class CDeathFillerNext : public CXCommand {
private:
  CDaoRecordset* m_pRS;
public:
  CDeathFillerNext(CDaoRecordset* pRS) {
    m_pRS = pRS;
  }
  void Do();
};
class CDeathFillerLast : public CXCommand {
private:
  CDaoRecordset* m_pRS;
public:
  CDeathFillerLast(CDaoRecordset* pRS) {
    m_pRS = pRS;
  }
  void Do();
};

#endif // NAVIGATE_H_INCLUDED