#if !defined(ERADATE_H_INCLUDED)
#define ERADATE_H_INCLUDED

#pragma warning(disable : 4995)

//
// EraDate.h
//
class CEraDate  : public COleDateTime {
public:
  BOOL ParseDate(const CString& szDate);
public:
  operator COleDateTime*()   { return (COleDateTime*)this;  }
  operator COleDateTime&()   { return (COleDateTime&)*this; }

};

COleDateTime ParseDate(const CString& szDate);


void AFXAPI DDX_Text(CDataExchange* pDX, int nIDC, CEraDate& value);
void AFXAPI DDX_FieldText(CDataExchange* pDX, int nIDC, CEraDate& value, CDaoRecordset* pRecordset);

#endif // ERADATE_H_INCLUDED