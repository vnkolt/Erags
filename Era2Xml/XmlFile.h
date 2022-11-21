
#pragma once

class CXmlFile : public CStdioFile {
public:
  void  WriteFormat(LPCTSTR szFormat, ...);
};