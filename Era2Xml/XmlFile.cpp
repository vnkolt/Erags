//
// XmlFile.cpp
//
#include "stdafx.h"
#include "XmlFile.h"


void CXmlFile::WriteFormat(LPCTSTR szFormat, ...) {
  CString sz;
  va_list va;
  va_start(va, szFormat);
  sz.FormatV(szFormat, va);
  va_end(va);

  WriteString(sz);

}