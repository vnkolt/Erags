#if !defined(DBF_H__INCLUDED_)
#define DBF_H__INCLUDED_

#pragma pack(push, r1, 1)

class CDBFField{
public:
  BYTE  fieldname[11];
  BYTE  ty;       // field type in ASCII
  BYTE  Res_1[4]; // reserved
  BYTE  fl;       // fields length in bytes
  BYTE  nd;       // number of decimals
  BYTE  Res_2;    // reserved
  BYTE  wa;       // work area
  BYTE  Res_3[12];// reserved
  CDBFField(){}
  void Create(LPCTSTR szFName, UCHAR ucFType, BYTE bFLen, BYTE bFDec);
};

class CDBFHeader{
public:
  BYTE  id;       // identification
  BYTE  yy;       //
  BYTE  mm;
  BYTE  dd;
  LONG  nRecs;    // number of records in file
  SHORT hl;       // number of bytes in header
  SHORT rl;       // number of bytes per record
  SHORT Res_1;    // reserved
  BYTE  in;       // incomplete tranzaction = 1
  BYTE  en;       // encrypted file = 1
  BYTE  Res_2[12];// reserved
  BYTE  md;       // .MDX file exists = 1
  BYTE  Res_3[3]; // reserved

  CDBFHeader(){}
};


class CDBF {
private:
  CFile       cFile;
  CDBFHeader  dbfHeader;
public:
  CDBF();
  ~CDBF();
  void Close();
  BOOL Create(LPCTSTR lpszFileName, int nFields, CDBFField* dbfFields);
  BOOL Create(LPCTSTR lpszFileName, LPCTSTR szFieldsInfo, char* pErrBuf);
  BOOL AddRec(CDBFField* pDBFFields, CString* psFields, int nFields);
  BOOL AddRec(LPCSTR szRecord);

  static CString MakeDBFDate(COleDateTime& odt);
  static CString MakeDBFCDate();
};

#pragma pack(pop, r1)

#endif