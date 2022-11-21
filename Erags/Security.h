#if !defined(SECURITY_H_INCLUDED)
#define SECURITY_H_INCLUDED

#include "..\Common\Crypto.h"
#include "..\Common\Sections.h"

#define ISREGION_OK 0x2020

extern short g_IsRegion[];

class CSecurity {
public:
// error values
	enum OpenFlags {
    errNoErrors,     // No errors, all right
		errCannotOpen,   // File does not exist
    errCannotRead,
    errBadFormat,    // Bad .rdf file format, or wrong size
    errBadCheckSum,
    errDateExpired
  };
  
// member variables
protected:
  CString     m_sFileName;   // .rdf filename
  SRDFHeader  m_rdflHeader;  // Header of .rdf file
  bool        m_bLoaded;    // true if .rdf was loaded
  bool        m_bArrayBuilt;// true if CIniContainer object was built
  int         m_error;      // error value

  bool        m_fRegion;
  bool        m_fValidOwner;
  CString     m_sRegionKey;
  CString     m_sExpiration;

  CIniContainer m_IniArray; // CIniContainer object
                             // will be created in BuildIniContainer() function
public:
  CSecurity();
  ~CSecurity();
  bool  Load();

  bool  IsRegion()  { return m_fRegion; }
  bool  IsLoaded()  { return m_bLoaded; }

  CIniContainer* GetContainer() { return &m_IniArray; }

  void SetFileName(LPCTSTR pFileName=NULL);


  bool IsValid(int& retCode);

  // Helpers
  CSection*  GetSection(LPCTSTR szSectionName) {
    return m_IniArray.GetSection(szSectionName);
  }

  CString    GetExpiration();
  bool       IsDisabled(COleDateTime& odt);
  void       CheckRegion(LPCTSTR szRegion, LPCTSTR szCity);
  bool       CheckForKeys(const CString& sRegion, LPCTSTR szRagsName);


  bool    IniArrayWasBuilt()  { return m_bArrayBuilt; }

  CString GetFileName()       { return m_sFileName;   }
  CString GetKeyValue(LPCTSTR szSection, LPCTSTR szKeyName);


  bool    IsExpiration(); // return true, if Expiration date <= system date

protected:
  int   IsBadSignature(LPCTSTR pSignature); // != 0 if signature Ok
  bool  Decrypt();
  bool  BuildIniContainer();
};

extern CSecurity theSecurity;


#endif SECURITY_H_INCLUDED