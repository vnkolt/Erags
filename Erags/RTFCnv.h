#if !defined(RTFCNV_H_INCLUDED)
#define RTFCNV_H_INCLUDED

#define BIRTH_TYPE_ACT          0 // Акт про одруження
#define BIRTH_TYPE_MOTHER       1 // Заява матері
#define BIRTH_TYPE_PARENTS      2 // Заява батьків
#define BIRTH_TYPE_APPL         3 // Заява
#define BIRTH_TYPE_APPLNUM      4 // Заява №
#define BIRTH_TYPE_AFFILIATION1 5 // Заява про визнання батьківства
#define BIRTH_TYPE_AFFILIATION2 6 // Спільна заява про визнання батьківства

enum PRINTDOCTYPE { DOCTYPE_UNKNOWN = 0, 
                    DOCTYPE_ACT = 1,
                    DOCTYPE_CERT = 2,
                    DOCTYPE_OTHER = 4 };

struct RegBlankItem {
  BYTE    bType;        // Народження, Одруження, Розірвання, Зміна, Смерть
  CString szCertSeria;  // Серія свідоцтва
  CString szCertNumber; // Номер свідоцтва
  CString szPIB;        // Прізвище, ім'я, по батькові особи, на яку складено актовий запис
  short   Number;       // Номер актового запису
  COleDateTime DataReg; // Дата складення актового запису
};

class CRSBirthes;
class CRSMarriages;
class CRSDivorces;
class CRSDeathes;
class CRSChanges;

CString GetCity(LPCTSTR szCity, bool fTypeCity=false);

typedef int (*pDeathFilterFunc)(CRSDeathes* pSet);
typedef int (*pBirthFilterFunc)(CRSBirthes* pSet);

CString GetPassport(BYTE bType, const CString& sSeria, const CString& sNumber, const COleDateTime& odtDate, const CString& sBy);

void  MakeInOutExt(CString& sTemplate, CString& sOutName);

BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet);
BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet);
BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet);
BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet);
BOOL UConvert(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet);

BOOL ConvertTable(LPCTSTR szReportName, const CString& sTemplate, const CString& sOutName, LPCTSTR szDBFScript, CRSDeathes* pSet, int nPage1, int nPage2, int (*pDeathFilterFunc)(CRSDeathes* pSet), int scanFrom=0);
BOOL ConvertTable(LPCTSTR szReportName, const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet, int nPage1, int nPage2, int (*pBirthFilterFunc)(CRSBirthes* pSet));

BOOL RTF_ABCDeath(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet);
BOOL RTF_DeathBlank(const CString& sTemplate, const CString& sOutName, CRSDeathes* pSet);

BOOL RTF_ABCBirth(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet);
BOOL RTF_BirthBlank(const CString& sTemplate, const CString& sOutName, CRSBirthes* pSet);

BOOL RTF_ABCMarriage(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet);
BOOL RTF_MarriageBlank(const CString& sTemplate, const CString& sOutName, CRSMarriages* pSet);

BOOL RTF_ABCDivorce(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet);
BOOL RTF_DivorceBlank(const CString& sTemplate, const CString& sOutName, CRSDivorces* pSet);

BOOL RTF_ABCChange(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet);
BOOL RTF_ChangeBlank(const CString& sTemplate, const CString& sOutName, CRSChanges* pSet);

BOOL ConvertEnvelope(const CString& sTemplate, const CString& sOutName);
BOOL ConvertForBlankRegister(const CString& sTemplate, const CString& sOutName);

extern PRINTDOCTYPE g_nDocType;

#endif // RTFCNV_H_INCLUDED