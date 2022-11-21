//
// DaoErr.cpp
//

#include "stdafx.h"
#include "Erags.h"
#include "..\Common\DaoErr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_DaoErr = 0;
void ResetDaoError() {
  g_DaoErr = 0;
}
BOOL IsDaoError() {
  return (g_DaoErr != 0);
}

CString ExplanationFieldName(CDaoException* e, CDaoFieldInfo& fi, CDaoRecordset* prs=NULL, int nField=-1) {
  CString s;
  if ( NULL==prs || -1==nField)
    return s;
  prs->GetFieldInfo(nField, fi);

/************************************** : by VK at 26.04.2004 6:26:49 **\
  if ( prs->m_strSQL==_T("DEATHES") ) {
  }
\************************************** : by VK at 26.04.2004 6:26:52 **/

  if ( fi.m_strName==_T("DATEREG") )                s = _T("Дата реєстрації");
  else if ( fi.m_strName==_T("BIRTH_DATE") )        s = _T("Дата народження");
  else if ( fi.m_strName==_T("BIRTH_COUNTRY") )     s = _T("Місце народження: Держава");
  else if ( fi.m_strName==_T("BIRTH_REGION") )      s = _T("Місце народження: Область");
  else if ( fi.m_strName==_T("BIRTH_DISTRICT") )    s = _T("Місце народження: Район");
  else if ( fi.m_strName==_T("BIRTH_CITY") )        s = _T("Місце народження: Місто (село, селище)");

  else if ( fi.m_strName==_T("BIRTHACT_NUMBER") )   s = _T("Номер АЗ про народження");
  else if ( fi.m_strName==_T("BIRTHACT_DATE") )     s = _T("Дата АЗ про народження");

  else if ( fi.m_strName==_T("BP_COUNTRY") )        s = _T("Місце народження: Держава");
  else if ( fi.m_strName==_T("BP_REGION") )         s = _T("Місце народження: Область");
  else if ( fi.m_strName==_T("BP_DISTRICT") )       s = _T("Місце народження: Район");
  else if ( fi.m_strName==_T("BP_CITY") )           s = _T("Місце народження: Місто (село, селище)");

  else if ( fi.m_strName==_T("COUNTRY") )           s = _T("Місце проживання: Держава");
  else if ( fi.m_strName==_T("REGION") )            s = _T("Місце проживання: Область");
  else if ( fi.m_strName==_T("DISTRICT") )          s = _T("Місце проживання: Район");
  else if ( fi.m_strName==_T("CITY") )              s = _T("Місце проживання: Місто (селище)");
  else if ( fi.m_strName==_T("STREET") )            s = _T("Місце проживання: Вулиця");
  else if ( fi.m_strName==_T("HOUSE") )             s = _T("Місце проживання: Будинок");
  else if ( fi.m_strName==_T("FLAT") )              s = _T("Місце проживання: Кваритира");

  else if ( fi.m_strName==_T("BYCOUNT") )           s = _T("Яка за рахунком дитина в матері");

  else if ( fi.m_strName==_T("CAUSE_OF_DEATH") )    s = _T("Причина смерті");
  else if ( fi.m_strName==_T("CERTIFICATE_NUMBER")) s = _T("Номер свідоцтва");
  else if ( fi.m_strName==_T("CERTIFICATE_SERIA") ) s = _T("Серія свідоцтва");
  else if ( fi.m_strName==_T("CITIZENSHIP") )       s = _T("Громадянство");

  else if ( fi.m_strName==_T("CHECKNUM") )          s = _T("Номер квитанції про сплату держита");
  else if ( fi.m_strName==_T("CHECKDATE") )         s = _T("Дата квитанції про сплату держита");
  else if ( fi.m_strName==_T("CHECKBANK") )         s = _T("Банк, де сплачено дермито");

  else if ( fi.m_strName==_T("DECLARANT_NAME") )           s = _T("ПІБ заявника");
  else if ( fi.m_strName==_T("DECLARANT_ADDRESS") )        s = _T("Адреса заявника");
  else if ( fi.m_strName==_T("DECLARANT_PASSPORT_TYPE") )  s = _T("Паспорт заявника: Тип");
  else if ( fi.m_strName==_T("DECLARANT_PASSPORT_SERIA"))  s = _T("Паспорт заявника: Серія");
  else if ( fi.m_strName==_T("DECLARANT_PASSPORT_NUMBER")) s = _T("Паспорт заявника: Номер");
  else if ( fi.m_strName==_T("DECLARANT_PASSPORT_DATE"))   s = _T("Паспорт заявника: Дата");
  else if ( fi.m_strName==_T("DECLARANT_PASSPORT_BY"))     s = _T("Паспорт заявника: Ким видано");

  else if ( fi.m_strName==_T("DEATH_DATE") )        s = _T("Дата смерті");

  else if ( fi.m_strName==_T("DP_COUNTRY") )        s = _T("Держава смерті");
  else if ( fi.m_strName==_T("DP_REGION") )         s = _T("Область смерті");
  else if ( fi.m_strName==_T("DP_DISTRICT") )       s = _T("Район смерті");
  else if ( fi.m_strName==_T("DP_CITY") )           s = _T("Місто (село) смерті");

  else if ( fi.m_strName==_T("FATHER_SURNAME") )    s = _T("Прізвище батька");
  else if ( fi.m_strName==_T("FATHER_NAME") )       s = _T("Ім'я батька");
  else if ( fi.m_strName==_T("FATHER_PATRONYMIC") ) s = _T("По батькові батька");

  else if ( fi.m_strName==_T("FATHER_BIRTH_DATE") ) s = _T("Дата народження батька");
  else if ( fi.m_strName==_T("FATHER_CITIZENSHIP")) s = _T("Громадянство батька");
  else if ( fi.m_strName==_T("FATHER_COUNTRY"))     s = _T("Місце проживання батька: Держава");
  else if ( fi.m_strName==_T("FATHER_REGION"))      s = _T("Місце проживання батька: Область");
  else if ( fi.m_strName==_T("FATHER_CITY"))        s = _T("Місце проживання батька: Місто (село, селище)");
  else if ( fi.m_strName==_T("FATHER_DISTRICT"))    s = _T("Місце проживання батька: Район");
  else if ( fi.m_strName==_T("FATHER_STREET"))      s = _T("Місце проживання батька: Вулиця");
  else if ( fi.m_strName==_T("FATHER_HOUSE"))       s = _T("Місце проживання батька: Будинок");
  else if ( fi.m_strName==_T("FATHER_FLAT"))        s = _T("Місце проживання батька: Квартира");

  else if ( fi.m_strName==_T("MEDICAL_CERT_TYPE") )  s = _T("Тип медичного свідоцтва");
  else if ( fi.m_strName==_T("MEDICAL_CERT_NUMBER")) s = _T("Номер медичного свідоцтва");
  else if ( fi.m_strName==_T("MEDICAL_CERT_BY"))     s = _T("Ким видано медичне свідоцтво");
  else if ( fi.m_strName==_T("MEDICAL_CERT_DATE"))   s = _T("Дата видачі медичного свідоцтва");

  else if ( fi.m_strName==_T("MEDICAL_CERTIFICATE_NUMBER")) s = _T("Номер медичного свідоцтва");
  else if ( fi.m_strName==_T("MEDICAL_CERTIFICATE_DATE"))   s = _T("Ким видано медичне свідоцтво");
  else if ( fi.m_strName==_T("MEDICAL_CERTIFICATE_BY"))     s = _T("Дата видачі медичного свідоцтва");

  else if ( fi.m_strName==_T("MOLD_SURNAME") )      s = _T("Прізвище чоловіка ДО реєстрації");
  else if ( fi.m_strName==_T("MNEW_SURNAME") )      s = _T("Прізвище чоловіка ПІСЛЯ реєстрації");
  else if ( fi.m_strName==_T("MNAME") )             s = _T("Ім'я чоловіка");
  else if ( fi.m_strName==_T("MPATRONYMIC") )       s = _T("По батькові чоловіка");

  else if ( fi.m_strName==_T("MBIRTH_DATE") )       s = _T("Дата народження чоловіка");
  else if ( fi.m_strName==_T("MBIRTH_COUNTRY") )    s = _T("Місце народження чоловіка: Держава");
  else if ( fi.m_strName==_T("MBIRTH_REGION") )     s = _T("Місце народження чоловіка: Область");
  else if ( fi.m_strName==_T("MBIRTH_DISTRICT") )   s = _T("Місце народження чоловіка: Район");
  else if ( fi.m_strName==_T("MBIRTH_CITY") )       s = _T("Місце народження чоловіка: Місто (село, селище)");
  else if ( fi.m_strName==_T("MCITIZENSHIP") )      s = _T("Громадянство чоловіка");

  else if ( fi.m_strName==_T("MRP_COUNTRY") )       s = _T("Місце проживання чоловіка: Держава");
  else if ( fi.m_strName==_T("MRP_REGION") )        s = _T("Місце народження чоловіка: Область");
  else if ( fi.m_strName==_T("MRP_DISTRICT") )      s = _T("Місце народження чоловіка: Район");
  else if ( fi.m_strName==_T("MRP_CITY") )          s = _T("Місце народження чоловіка: Місто (село, селище)");
  else if ( fi.m_strName==_T("MRP_STREET") )        s = _T("Місце народження чоловіка: Вулиця");
  else if ( fi.m_strName==_T("MRP_HOUSE") )         s = _T("Місце народження чоловіка: Будинок");
  else if ( fi.m_strName==_T("MRP_FLAT") )          s = _T("Місце народження чоловіка: Квартира");

  else if ( fi.m_strName==_T("MPASSPORT_TYPE") )    s = _T("Паспорт чоловіка: Тип");
  else if ( fi.m_strName==_T("MPASSPORT_SERIA") )   s = _T("Паспорт чоловіка: Серія");
  else if ( fi.m_strName==_T("MPASSPORT_NUMBER") )  s = _T("Паспорт чоловіка: Номер");
  else if ( fi.m_strName==_T("MPASSPORT_DATE") )    s = _T("Паспорт чоловіка: Дата видачі");
  else if ( fi.m_strName==_T("MPASSPORT_BY") )      s = _T("Паспорт чоловіка: Ким видан");

  else if ( fi.m_strName==_T("MDUTY") )             s = _T("Сторона чоловіка: Сплачено держмито");
  else if ( fi.m_strName==_T("MDUTY2") )            s = _T("Сторона чоловіка: Сплачено (старими грошима)");
  else if ( fi.m_strName==_T("MMONEY_TYPE") )       s = _T("Сторона чоловіка: Валюта");
  else if ( fi.m_strName==_T("MCHECK_NUMBER") )     s = _T("Сторона чоловіка: Номер квитанції");
  else if ( fi.m_strName==_T("MCHECK_DATE") )       s = _T("Сторона чоловіка: Дата квитанції");
  else if ( fi.m_strName==_T("MCHECK_BANK") )       s = _T("Сторона чоловіка: Банк, де сплачено держмито");
  else if ( fi.m_strName==_T("MCERTIFICATE_SERIA")) s = _T("Сторона чоловіка: Серія свідоцтва");
  else if ( fi.m_strName==_T("MCERTIFICATE_NUMBER"))s = _T("Сторона чоловіка: Номер свідоцтва");
  else if ( fi.m_strName==_T("MNOTICE"))            s = _T("Сторона чоловіка: Для відміток");

  else if ( fi.m_strName==_T("MFAMILY_STATUS") )    s = _T("Сімейний стан чоловіка");
  else if ( fi.m_strName==_T("MACT_NUMBER") )       s = _T("Сторона чоловіка: Номер АЗ про РШ або про смерть");
  else if ( fi.m_strName==_T("MACT_DATE") )         s = _T("Сторона чоловіка: Дата АЗ про РШ або про смерть");
  else if ( fi.m_strName==_T("MACT_BY") )           s = _T("Сторона чоловіка: Ким складено АЗ про РШ або про смерть");

  else if ( fi.m_strName==_T("MOTHER_SURNAME") )    s = _T("Прізвище матері");
  else if ( fi.m_strName==_T("MOTHER_NAME") )       s = _T("Ім'я матері");
  else if ( fi.m_strName==_T("MOTHER_PATRONYMIC") ) s = _T("По батькові матері");

  else if ( fi.m_strName==_T("MOTHER_BIRTH_DATE") ) { s = _T("Дата народження матері");           }
  else if ( fi.m_strName==_T("MOTHER_CITIZENSHIP")) { s = _T("Громадянство матері");              }
  else if ( fi.m_strName==_T("MOTHER_COUNTRY"))     { s = _T("Місце проживання матері: Держава"); }
  else if ( fi.m_strName==_T("MOTHER_REGION"))      { s = _T("Місце проживання матері: Область"); }
  else if ( fi.m_strName==_T("MOTHER_CITY"))        { s = _T("Місце проживання матері: Місто (село, селище)"); }
  else if ( fi.m_strName==_T("MOTHER_DISTRICT"))    { s = _T("Місце проживання матері: Район");   }
  else if ( fi.m_strName==_T("MOTHER_STREET"))      { s = _T("Місце проживання матері: Вулиця");  }
  else if ( fi.m_strName==_T("MOTHER_HOUSE"))       { s = _T("Місце проживання матері: Будинок"); }
  else if ( fi.m_strName==_T("MOTHER_FLAT"))        { s = _T("Місце проживання матері: Квартира");}


  else if ( fi.m_strName==_T("NATIONALITY") )       s = _T("Національність");
  else if ( fi.m_strName==_T("NKIDS") )             s = _T("Скількі народилося дітей");
  else if ( fi.m_strName==_T("NOTICE") )            s = _T("Для відміток");
  else if ( fi.m_strName==_T("NUMBER") )            s = _T("Номер актового запису");

  else if ( fi.m_strName==_T("NEWSURNAME") )        s = _T("Прізвище після зміни");
  else if ( fi.m_strName==_T("NEWNAME") )           s = _T("Ім'я після зміни");
  else if ( fi.m_strName==_T("NEWPATRONYMIC") )     s = _T("По батькові після зміни");

  else if ( fi.m_strName==_T("OLDSURNAME") )        s = _T("Прізвище до зміни");
  else if ( fi.m_strName==_T("OLDNAME") )           s = _T("Ім'я до зміни");
  else if ( fi.m_strName==_T("OLDPATRONYMIC") )     s = _T("По батькові до зміни");

  else if ( fi.m_strName==_T("PASSPORT_TYPE") )     s = _T("Тип паспорту");
  else if ( fi.m_strName==_T("PASSPORT_SERIA") )    s = _T("Серія паспорту");
  else if ( fi.m_strName==_T("PASSPORT_NUMBER") )   s = _T("Номер паспорту");
  else if ( fi.m_strName==_T("PASSPORT_DATE") )     s = _T("Дата видачі паспорту");
  else if ( fi.m_strName==_T("PASSPORT_BY") )       s = _T("Ким видано паспорт");

  if ( !s.IsEmpty() )
    return s;

  if      ( fi.m_strName==_T("PATRONYMIC") )        s = _T("По бастькові");
  else if ( fi.m_strName==_T("RP_COUNTRY") )        s = _T("Місце проживання: Держава");
  else if ( fi.m_strName==_T("RP_REGION") )         s = _T("Місце проживання: Область");
  else if ( fi.m_strName==_T("RP_DISTRICT") )       s = _T("Місце проживання: Район");
  else if ( fi.m_strName==_T("RP_ZIPCODE") )        s = _T("Місце проживання: Індекс");
  else if ( fi.m_strName==_T("RP_CITY") )           s = _T("Місце проживання: Місто (селище)");
  else if ( fi.m_strName==_T("RP_STREET") )         s = _T("Місце проживання: Вулиця");
  else if ( fi.m_strName==_T("RP_HOUSE") )          s = _T("Місце проживання: Будинок");
  else if ( fi.m_strName==_T("RP_FLAT") )           s = _T("Місце проживання: Кваритира");

  else if ( fi.m_strName==_T("SOURCE_TYPE") )       { s = _T("Підстава: Тип");                    }
  else if ( fi.m_strName==_T("SOURCE_NDOC") )       { s = _T("Підстава: Номер документа");        }
  else if ( fi.m_strName==_T("SOURCE_DATE") )       { s = _T("Підстава: Дата документа");         }
  else if ( fi.m_strName==_T("SOURCE_BY") )         { s = _T("Підстава: Ким зареєстровано шлюб"); }

  else if ( fi.m_strName==_T("SURNAME") )           { s = _T("Прізвище");         }

  else if ( fi.m_strName==_T("TAX_CODE") )          { s = _T("Ідентифікаційний номер");          }


  else if ( fi.m_strName==_T("WOLD_SURNAME") )      s = _T("Прізвище жінки ДО реєстрації");
  else if ( fi.m_strName==_T("WNEW_SURNAME") )      s = _T("Прізвище жінки ПІСЛЯ реєстрації");
  else if ( fi.m_strName==_T("WNAME") )             s = _T("Ім'я жінки");
  else if ( fi.m_strName==_T("WPATRONYMIC") )       s = _T("По батькові жінки");

  else if ( fi.m_strName==_T("WBIRTH_DATE") )       s = _T("Дата народження жінки");
  else if ( fi.m_strName==_T("WBIRTH_COUNTRY") )    s = _T("Місце народження жінки: Держава");
  else if ( fi.m_strName==_T("WBIRTH_REGION") )     s = _T("Місце народження жінки: Область");
  else if ( fi.m_strName==_T("WBIRTH_DISTRICT") )   s = _T("Місце народження жінки: Район");
  else if ( fi.m_strName==_T("WBIRTH_CITY") )       s = _T("Місце народження жінки: Місто (село, селище)");
  else if ( fi.m_strName==_T("WCITIZENSHIP") )      s = _T("Громадянство жінки");

  else if ( fi.m_strName==_T("WRP_COUNTRY") )       s = _T("Місце проживання жінки: Держава");
  else if ( fi.m_strName==_T("WRP_REGION") )        s = _T("Місце народження жінки: Область");
  else if ( fi.m_strName==_T("WRP_DISTRICT") )      s = _T("Місце народження жінки: Район");
  else if ( fi.m_strName==_T("WRP_CITY") )          s = _T("Місце народження жінки: Місто (село, селище)");
  else if ( fi.m_strName==_T("WRP_STREET") )        s = _T("Місце народження жінки: Вулиця");
  else if ( fi.m_strName==_T("WRP_HOUSE") )         s = _T("Місце народження жінки: Будинок");
  else if ( fi.m_strName==_T("WRP_FLAT") )          s = _T("Місце народження жінки: Квартира");

  else if ( fi.m_strName==_T("WPASSPORT_TYPE") )    s = _T("Паспорт жінки: Тип");
  else if ( fi.m_strName==_T("WPASSPORT_SERIA") )   s = _T("Паспорт жінки: Серія");
  else if ( fi.m_strName==_T("WPASSPORT_NUMBER") )  s = _T("Паспорт жінки: Номер");
  else if ( fi.m_strName==_T("WPASSPORT_DATE") )    s = _T("Паспорт жінки: Дата видачі");
  else if ( fi.m_strName==_T("WPASSPORT_BY") )      s = _T("Паспорт жінки: Ким видан");

  else if ( fi.m_strName==_T("WFAMILY_STATUS") )    s = _T("Сімейний стан чоловіка");
  else if ( fi.m_strName==_T("WACT_NUMBER") )       s = _T("Сторона жінки: Номер АЗ про РШ або про смерть");
  else if ( fi.m_strName==_T("WACT_DATE") )         s = _T("Сторона жінки: Дата АЗ про РШ або про смерть");
  else if ( fi.m_strName==_T("WACT_BY") )           s = _T("Сторона жінки: Ким складено АЗ про РШ або про смерть");

  else if ( fi.m_strName==_T("WDUTY") )             s = _T("Сторона жінки: Сплачено держмито");
  else if ( fi.m_strName==_T("WDUTY2") )            s = _T("Сторона жінки: Сплачено (старими грошима)");
  else if ( fi.m_strName==_T("WMONEY_TYPE") )       s = _T("Сторона жінки: Валюта");
  else if ( fi.m_strName==_T("WCHECK_NUMBER") )     s = _T("Сторона жінки: Номер квітанції");
  else if ( fi.m_strName==_T("WCHECK_DATE") )       s = _T("Сторона жінки: Дата кватанції");
  else if ( fi.m_strName==_T("WCHECK_BANK") )       s = _T("Сторона жінки: Банк, де сплачено держмито");
  else if ( fi.m_strName==_T("WCERTIFICATE_SERIA")) s = _T("Сторона жінки: Серія свідоцтва");
  else if ( fi.m_strName==_T("WCERTIFICATE_NUMBER"))s = _T("Сторона жінки: Номер свідоцтва");
  else if ( fi.m_strName==_T("WNOTICE"))            s = _T("Сторона жінки: Для відміток");

  return s;
}

void  DaoError(CDaoException* e, LPCTSTR szFieldName/*=NULL*/, CDaoRecordset* prs/*=NULL*/, int nField/*=-1*/) {
  CString sErr;
  g_DaoErr = e->m_pErrorInfo->m_lErrorCode;
  switch(e->m_pErrorInfo->m_lErrorCode) {
    case 2420:  //	Syntax error in number.
      break;
    case 2421:  //	Syntax error in date.
      break;
    case 2422:  //	Syntax error in string.
      break;
    case 2423:  //	Invalid use of '.', '!', or '()'.
      break;
    case 2424:  //	Unknown name.
      break;
    case 2425:  //	Unknown function name.
      break;
    case 2426:  //	Function isn't available in expressions.
      break;
    case 2427:  //	Object has no value.
      break;
    case 2428:  //	Invalid arguments used with domain function.
      break;
    case 2429:  //	In operator without ().
      break;

    case 2430:  //	Between operator without And.
      break;
    case 2431:  //	Syntax error (missing operator).
      break;
    case 2432:  //	Syntax error (comma).
      break;
    case 2433:  //	Syntax error.
      break;
    case 2434:  //	Syntax error (missing operator).
      break;
    case 2435:  //	Extra ).
      break;
    case 2436:  //	Missing ), ], or Item.
      break;
    case 2437:  //	Invalid use of vertical bars.
      break;
    case 2438:  //	Syntax error.
      break;
    case 2439:  //	Wrong number of arguments used with function.
      break;

    case 2440:  //	IIF function without ().
      break;
    case 2442:  //	Invalid use of parentheses.
      break;
    case 2443:  //	Invalid use of Is operator.
      break;
    case 2445:  //	Expression too complex.
      break;
    case 2446:  //	Out of memory during calculation.
      break;
    case 2447:  //	Invalid use of '.', '!', or '()'.
      break;
    case 2448:  //	Can't set value.
      break;
    case 3000:  //	Reserved error <Item>; there is no message for this error.
      break;
    case 3001:  //	Invalid argument.
      break;
    case 3002:  //	Couldn't start session.
      break;

    case 3003:  //	Couldn't start transaction; too many transactions already nested.
      break;
    case 3005:  //	<Database name> isn't a valid database name.
      break;
    case 3006:  //	Database <name> is exclusively locked.
      break;
    case 3007:  //	Can’t open library database <name>.
      break;
    case 3008:  //	The table <name> is already opened exclusively by another user, or it is already open through the user interface and cannot be manipulated programmatically.
      break;
    case 3009:  //	You tried to lock a table while opening it, but the table can't be locked because it is currently in use. Wait a moment, and then try the operation again.
      break;

    case 3010:  //	Table <name> already exists.
      break;
    case 3011:  //	The Microsoft Jet database engine could not find the object <name>. Make sure the object exists and that you spell its name and the path name correctly.
      break;
    case 3012:  //	Object <name> already exists.
      break;
    case 3013:  //	Couldn't rename installable ISAM file.
      break;
    case 3014:  //	Can't open any more tables.
      break;
    case 3015:  //	<Index name> isn't an index in this table. Look in the Indexes collection of the TableDef object to determine the valid index names.
      break;

    case 3016:  //	Field won't fit in record.
      break;
    case 3017:  //	The size of a field is too long.
      break;
    case 3018:  //	Couldn't find field <name>.
      break;
    case 3019:  //	Operation invalid without a current index.
      break;
    case 3020:  //	Update or CancelUpdate without AddNew or Edit.
      break;
    case 3021:  //	No current record.
      break;
    case 3022:  //	The changes you requested to the table were not successful because they would create duplicate values in the index, primary key, or relationship. Change the data in the field or fields that contain duplicate data, remove the index, or redefine the index to permit duplicate entries and try again.
      break;

    case 3023:  //	AddNew or Edit already used.
      break;
    case 3024:  //	Couldn't find file <name>.
      break;
    case 3025:  //	Can't open any more files.
      break;
    case 3026:  //	Not enough space on disk.
      break;
    case 3027:  //	Can't update. Database or object is read-only.
      break;
    case 3028:  //	Can't start your application. The workgroup information file is missing or opened exclusively by another user.
      break;
    case 3029:  //	Not a valid account name or password.
      break;
    case 3030:  //	<Account name> isn't a valid account name.
      break;

    case 3031:  //	Not a valid password.
      break;
    case 3032:  //	Can't perform this operation.
      break;
    case 3033:  //	You don't have the necessary permissions to use the <name> object. Have your system administrator or the person who created this object establish the appropriate permissions for you.
      break;
    case 3034:  //	You tried to commit or roll back a transaction without first using BeginTrans.
      break;
    case 3036:  //	Database has reached maximum size.
      break;
    case 3037:  //	Can't open any more tables or queries.
      break;

    case 3039:  //	Couldn't create index; too many indexes already defined.
      break;
    case 3040:  //	Disk I/O error during read.
      break;
    case 3041:  //	Can't open a database created with a previous version of your application.
      break;
    case 3042:  //	Out of MS-DOS file handles.
      break;
    case 3043:  //	Disk or network error.
      break;
    case 3044:  //	<Path> isn't a valid path. Make sure that the path name is spelled correctly and that you are connected to the server on which the file resides.
      break;

    case 3045:  //	Couldn't use <name>; file already in use.
      break;
    case 3046:  //	Couldn't save; currently locked by another user.
      break;
    case 3047:  //	Record is too large.
      break;
    case 3048:  //	Can't open any more databases.
      break;
    case 3049:  //	Can't open database <name>. It may not be a database that your application recognizes, or the file may be corrupt.
      break;
    case 3051:  //	The Microsoft Jet database engine cannot open the file <name>. It is already opened exclusively by another user, or you need permission to view its data.
      break;

    case 3052:  //	MS-DOS file sharing lock count exceeded. You need to increase the number of locks installed with Share.exe.
      break;
    case 3053:  //	Too many client tasks.
      break;
    case 3054:  //	Too many Memo or OLE Object fields.
      break;
    case 3055:  //	Not a valid file name.
      break;
    case 3056:  //	Couldn't repair this database.
      break;
    case 3057:  //	Operation not supported on linked tables.
      break;
    case 3058:  //	Index or primary key can't contain a Null value.
      break;
    case 3059:  //	Operation canceled by user.
      break;

    case 3060:  //	Wrong data type for parameter <parameter>.
      break;
    case 3061:  //	Too few parameters. Expected <number>.
      break;
    case 3062:  //	Duplicate output alias <name>.
      break;
    case 3063:  //	Duplicate output destination <name>.
      break;
    case 3064:  //	Can't open action query <name>.
      break;
    case 3065:  //	Can't execute a select query.
      break;
    case 3066:  //	Query must have at least one destination field.
      break;
    case 3067:  //	Query input must contain at least one table or query.
      break;

    case 3068:  //	Not a valid alias name.
      break;
    case 3069:  //	The action query <name> cannot be used as a row source.
      break;
    case 3070:  //	The Microsoft Jet database engine does not recognize <name> as a valid field name or expression.
      break;
    case 3071:  //	This expression is typed incorrectly, or it is too complex to be evaluated. For example, a numeric expression may contain too many complicated elements. Try simplifying the expression by assigning parts of the expression to variables.
      break;

    case 3073:  //	Operation must use an updatable query.
      break;
    case 3074:  //	Can't repeat table name <name> in FROM clause.
      break;
    case 3075:  //	<Message> in query expression <expression>.
      break;
    case 3076:  //	<Name> in criteria expression.
      break;
    case 3077:  //	<Message> in expression.
      break;
    case 3078:  //	The Microsoft Jet database engine cannot find the input table or query <name>. Make sure it exists and that its name is spelled correctly.
      break;
    case 3079:  //	The specified field reference could refer to more than one table listed in the FROM clause of your SQL statement.
      break;

    case 3080:  //	Joined table <name> not listed in FROM clause.
      break;
    case 3081:  //	Can't join more than one table with the same name <name>.
      break;
    case 3082:  //	JOIN operation <operation> refers to a field that isn't in one of the joined tables.
      break;
    case 3083:  //	Can't use internal report query.
      break;
    case 3084:  //	Can't insert data with action query.
      break;
    case 3085:  //	Undefined function <name> in expression.
      break;
    case 3086:  //	Couldn't delete from specified tables.
      break;

    case 3087:  //	Too many expressions in GROUP BY clause.
      break;
    case 3088:  //	Too many expressions in ORDER BY clause.
      break;
    case 3089:  //	Too many expressions in DISTINCT output.
      break;
    case 3090:  //	Resultant table not allowed to have more than one AutoNumber field.
      break;
    case 3092:  //	Can't use HAVING clause in TRANSFORM statement.
      break;
    case 3093:  //	ORDER BY clause <clause> conflicts with DISTINCT.
      break;
    case 3094:  //	ORDER BY clause <clause> conflicts with GROUP BY clause.
      break;

    case 3095:  //	Can't have aggregate function in expression <expression>.
      break;
    case 3096:  //	Can't have aggregate function in WHERE clause <clause>.
      break;
    case 3097:  //	Can't have aggregate function in ORDER BY clause <clause>.
      break;
    case 3098:  //	Can't have aggregate function in GROUP BY clause <clause>.
      break;
    case 3099:  //	Can't have aggregate function in JOIN operation <operation>.
      break;
    case 3100:  //	Can't set field <name> in join key to Null.
      break;
    case 3101:  //	The Microsoft Jet database engine can't find a record in the table <name> with key matching field(s) <name>.
      break;

    case 3102:  //	Circular reference caused by <query reference>.
      break;
    case 3103:  //	Circular reference caused by alias <name> in query definition's SELECT list.
      break;
    case 3104:  //	Can't specify fixed column heading <value> in a crosstab query more than once.
      break;
    case 3105:  //	Missing destination field name in SELECT INTO statement <statement>.
      break;
    case 3106:  //	Missing destination field name in UPDATE statement <statement>.
      break;
    case 3107:  //	Record(s) can't be added; no insert permission on <name>.
      break;

    case 3108:  //	Record(s) can't be edited; no update permission on <name>.
      break;
    case 3109:  //	Record(s) can't be deleted; no delete permission on <name>.
      break;
    case 3110:  //	Couldn't read definitions; no read definitions permission for table or query <name>.
      break;
    case 3111:  //	Couldn't create; no modify design permission for table or query <name>.
      break;
    case 3112:  //	Record(s) can't be read; no read permission on <name>.
      break;
    case 3113:  //	Can't update <field name>; field not updatable.
      break;

    case 3114:  //	Can't include Memo or OLE Object when you select unique values <statement>.
      break;
    case 3115:  //	Can't have Memo or OLE Object fields in aggregate argument <statement>.
      break;
    case 3116:  //	Can't have Memo or OLE Object fields in criteria <criteria> for aggregate function.
      break;
    case 3117:  //	Can't sort on Memo or OLE Object <clause>.
      break;
    case 3118:  //	Can't join on Memo or OLE Object <name>.
      break;
    case 3119:  //	Can't group on Memo or OLE Object <clause>.
      break;

    case 3120:  //	Can't group on fields selected with '*' <table name>.
      break;
    case 3121:  //	Can't group on fields selected with '*'.
      break;
    case 3122:  //	You tried to execute a query that doesn't include the specified expression <name> as part of an aggregate function.
      break;
    case 3123:  //	Can't use '*' in crosstab query.
      break;
    case 3124:  //	Can't input from internal report query <name>.
      break;
    case 3125:  //	The database engine can't find <name>. Make sure it is a valid parameter or alias name, that it doesn't include invalid characters or punctuation, and that the name isn't too long.
      break;

    case 3126:  //	Invalid bracketing of name <name>.
      break;
    case 3127:  //	The INSERT INTO statement contains the following unknown field name: <field name>. Make sure you've typed the name correctly, and try the operation again.
      break;
    case 3128:  //	Specify the table containing the records you want to delete.
      break;
    case 3129:  //	Invalid SQL statement; expected 'DELETE', 'INSERT', 'PROCEDURE', 'SELECT', or 'UPDATE'.
      break;
    case 3130:  //	Syntax error in DELETE statement.
      break;

    case 3131:  //	Syntax error in FROM clause.
      break;
    case 3132:  //	Syntax error in GROUP BY clause.
      break;
    case 3133:  //	Syntax error in HAVING clause.
      break;
    case 3134:  //	Syntax error in INSERT INTO statement.
      break;
    case 3135:  //	Syntax error in JOIN operation.
      break;
    case 3136:  //	The LEVEL clause includes a reserved word or argument that is misspelled or missing, or the punctuation is incorrect.
      break;
    case 3138:  //	Syntax error in ORDER BY clause.
      break;
    case 3139:  //	Syntax error in PARAMETER clause.
      break;

    case 3140:  //	Syntax error in PROCEDURE clause.
      break;
    case 3141:  //	The SELECT statement includes a reserved word or an argument name that is misspelled or missing, or the punctuation is incorrect.
      break;
    case 3143:  //	Syntax error in TRANSFORM statement.
      break;
    case 3144:  //	Syntax error in UPDATE statement.
      break;
    case 3145:  //	Syntax error in WHERE clause.
      break;
    case 3146:  //	ODBC —call failed.
      break;
    case 3151:  //	ODBC —connection to <name> failed.
      break;

    case 3154:  //	ODBC —couldn't find DLL <name>.
      break;
    case 3155:  //	ODBC —insert on a linked table failed.
      break;
    case 3156:  //	ODBC —delete on a linked table failed.
      break;
    case 3157:  //	ODBC —update on a linked table failed.
      break;
    case 3158:  //	Couldn't save record; currently locked by another user.
      break;
    case 3159:  //	Not a valid bookmark.
      break;
    case 3160:  //	Table isn't open.
      break;
    case 3161:  //	Couldn't decrypt file.
      break;
    case 3162:  //	You tried to assign the Null value to a variable that isn't a Variant data type.
      break;

    case 3163:  //	The field is too small to accept the amount of data you attempted to add. Try inserting or pasting less data.
      if ( szFieldName ) {
        sErr.Format(_T("Поле \"%s\" не вміщує таку кілкість даних"), szFieldName);
      }
      else if ( prs != NULL && nField != -1 ) {
        long lSize = 0;
        CDaoFieldInfo fi;
        CString s = ExplanationFieldName(e, fi, prs, nField);
        sErr.Format(_T("Поле \"%s\" не вміщує таку кілкість даних."), s);
        if ( FALSE==s.IsEmpty() ) {
          if ( dbText==fi.m_nType ) {
            s.Format(_T("\nЦе поле вміщує тільки %d символів."), fi.m_lSize);
            sErr += s;
          }
        }
      }
      break;
    case 3164:  //	The field can't be updated because another user or process has locked the corresponding record or table.
      break;
    case 3165:  //	Couldn't open .inf file.
      break;
    case 3166:  //	Cannot locate the requested Xbase memo file.
      break;
    case 3167:  //	Record is deleted.
      break;
    case 3168:  //	Invalid .inf file.
      break;
    case 3169:  //	The Microsoft Jet database engine could not execute the SQL statement because it contains a field that has an invalid data type.
      break;

    case 3170:  //	Couldn't find installable ISAM.
      break;
    case 3171:  //	Couldn't find network path or user name.
      break;
    case 3172:  //	Couldn't open Paradox.net.
      break;
    case 3173:  //	Couldn't open table 'MSysAccounts' in the workgroup information file.
      break;
    case 3174:  //	Couldn't open table 'MSysGroups' in the workgroup information file.
      break;
    case 3175:  //	Date is out of range or is in an invalid format.
      break;
    case 3176:  //	Couldn't open file <name>.
      break;
    case 3177:  //	Not a valid table name.
      break;

    case 3179:  //	Encountered unexpected end of file.
      break;
    case 3180:  //	Couldn't write to file <name>.
      break;
    case 3181:  //	Invalid range.
      break;
    case 3182:  //	Invalid file format.
      break;
    case 3183:  //	Not enough space on temporary disk.
      break;
    case 3184:  //	Couldn't execute query; couldn't find linked table.
      break;
    case 3185:  //	SELECT INTO on a remote database tried to produce too many fields.
      break;
    case 3186:  //	Couldn't save; currently locked by user <name> on machine <name>.
      break;

    case 3187:  //	Couldn't read; currently locked by user <name> on machine <name>.
      break;
    case 3188:  //	Couldn't update; currently locked by another session on this machine.
      break;
    case 3189:  //	Table <name> is exclusively locked by user <name> on machine <name>.
      break;
    case 3190:  //	Too many fields defined.
      break;
    case 3191:  //	Can't define field more than once.
      break;
    case 3192:  //	Couldn't find output table <name>.
      break;
    case 3196:  //	The database <database name> is already in use by another person or process. When the database is available, try the operation again.
      break;

    case 3197:  //	The Microsoft Jet database engine stopped the process because you and another user are attempting to change the same data at the same time.
      break;
    case 3198:  //	Couldn't start session.  Too many sessions already active.
      break;
    case 3199:  //	Couldn't find reference.
      break;
    case 3200:  //	The record cannot be deleted or changed because table <name> includes related records.
      break;
    case 3201:  //	You can't add or change a record because a related record is required in table <name>.
      break;

    case 3202:  //	Couldn't save; currently locked by another user.
      break;
    case 3203:  //	Subqueries cannot be used in the expression <expression>.
      break;
    case 3204:  //	Database already exists.
      break;
    case 3205:  //	Too many crosstab column headers <value>.
      break;
    case 3206:  //	Can't create a relationship between a field and itself.
      break;
    case 3207:  //	Operation not supported on a Paradox table with no primary key.
      break;
    case 3208:  //	Invalid Deleted setting in the Xbase key of the Windows Registry.
      break;

    case 3210:  //	The connection string is too long.
      break;
    case 3211:  //	The database engine couldn't lock table <name> because it's already in use by another person or process.
      break;
    case 3212:  //	Couldn't lock table <name>; currently in use by user <name> on machine <name>.
      break;
    case 3213:  //	Invalid Date setting in the Xbase key of the Windows Registry.
      break;
    case 3214:  //	Invalid Mark setting in the Xbase key of the Windows Registry.
      break;
    case 3215:  //	Too many Btrieve tasks.
      break;

    case 3216:  //	Parameter <name> specified where a table name is required.
      break;
    case 3217:  //	Parameter <name> specified where a database name is required.
      break;
    case 3218:  //	Couldn't update; currently locked.
      break;
    case 3219:  //	Invalid operation.
      break;
    case 3220:  //	Incorrect collating sequence.
      break;
    case 3221:  //	Invalid settings in the Btrieve key of the Windows Registry.
      break;
    case 3222:  //	Query can't contain a Database parameter.
      break;
    case 3223:  //	<Parameter name> is invalid because it's longer than 64 characters or contains invalid characters.
      break;

    case 3224:  //	Can't read Btrieve data dictionary.
      break;
    case 3225:  //	Encountered a record locking deadlock while performing a Btrieve operation.
      break;
    case 3226:  //	Errors encountered while using the Btrieve DLL.
      break;
    case 3227:  //	Invalid Century setting in the Xbase key of the Windows Registry.
      break;
    case 3228:  //	Invalid CollatingSequence setting in the Paradox key of the Windows Registry.
      break;
    case 3229:  //	Btrieve —can't change field.
      break;
    case 3230:  //	Out-of-date Paradox lock file.
      break;

    case 3231:  //	ODBC —field would be too long; data truncated.
      break;
    case 3232:  //	ODBC —couldn't create table.
      break;
    case 3234:  //	ODBC —remote query timeout expired.
      break;
    case 3235:  //	ODBC —data type not supported on server.
      break;
    case 3238:  //	ODBC —data out of range.
      break;
    case 3239:  //	Too many active users.
      break;
    case 3240:  //	Btrieve —missing Btrieve engine.
      break;
    case 3241:  //	Btrieve —out of resources.
      break;
    case 3242:  //	Invalid reference in SELECT statement.
      break;

    case 3243:  //	None of the import field names match fields in the appended table.
      break;
    case 3244:  //	Can't import password-protected spreadsheet.
      break;
    case 3245:  //	Couldn't parse field names from the first row of the import table.
      break;
    case 3246:  //	Operation not supported in transactions.
      break;
    case 3247:  //	ODBC —linked table definition has changed.
      break;
    case 3248:  //	Invalid NetworkAccess setting in the Windows Registry.
      break;
    case 3249:  //	Invalid PageTimeout setting in the Windows Registry.
      break;

    case 3250:  //	Couldn't build key.
      break;
    case 3251:  //	Operation is not supported for this type of object.
      break;
    case 3252:  //	Can't open a form whose underlying query contains a user-defined function that attempts to set or get the form's RecordsetClone property.
      break;
    case 3254:  //	ODBC —Can't lock all records.
      break;
    case 3256:  //	Index file not found.
      break;
    case 3257:  //	Syntax error in WITH OWNERACCESS OPTION declaration.
      break;
    case 3258:  //	The SQL statement couldn't be executed because it contains ambiguous outer joins. To force one of the joins to be performed first, create a separate query that performs the first join and then include that query in your SQL statement.
      break;

    case 3259:  //	Invalid field data type.
      break;
    case 3260:  //	Couldn't update; currently locked by user <name> on machine <name>.
      break;
    case 3261:  //	Table <name> is exclusively locked by user <name> on machine <name>.
      break;
    case 3262:  //	Couldn't lock table <name>; currently in use by user <name> on machine <name>.
      break;
    case 3263:  //	Invalid Database object.
      break;
    case 3264:  //	No field defined —cannot append TableDef or Index.
      break;
    case 3265:  //	Item not found in this collection.
      break;

    case 3266:  //	Can't append a Field that is already a part of a Fields collection.
      break;
    case 3267:  //	Property can be set only when the Field is part of a Recordset object's Fields collection.
      break;
    case 3268:  //	Can't set this property once the object is part of a collection.
      break;
    case 3269:  //	Can't append an Index that is already a part of an Indexes collection.
      break;
    case 3270:  //	Property not found.
      break;
    case 3271:  //	Invalid property value.
      break;

    case 3272:  //	Object isn't a collection.
      break;
    case 3273:  //	Method not applicable for this object.
      break;
    case 3274:  //	External table isn't in the expected format.
      break;
    case 3275:  //	Unexpected error from external database driver <error number>.
      break;
    case 3276:  //	Invalid database object reference.
      break;
    case 3277:  //	Can't have more than 10 fields in an index.
      break;
    case 3278:  //	The Microsoft Jet database engine has not been initialized.
      break;
    case 3279:  //	The Microsoft Jet database engine has already been initialized.
      break;

    case 3280:  //	Can't delete a field that is part of an index or is needed by the system.
      break;
    case 3281:  //	Can't delete this index or table.  It is either the current index or is used in a relationship.
      break;
    case 3282:  //	Operation not supported on a table that contains data.
      break;
    case 3283:  //	Primary key already exists.
      break;
    case 3284:  //	Index already exists.
      break;
    case 3285:  //	Invalid index definition.
      break;
    case 3286:  //	Format of memo file doesn't match specified external database format.
      break;

    case 3287:  //	Can't create index on the given field.
      break;
    case 3288:  //	Paradox index is not primary.
      break;
    case 3289:  //	Syntax error in CONSTRAINT clause.
      break;
    case 3290:  //	Syntax error in CREATE TABLE statement.
      break;
    case 3291:  //	Syntax error in CREATE INDEX statement.
      break;
    case 3292:  //	Syntax error in field definition.
      break;
    case 3293:  //	Syntax error in ALTER TABLE statement.
      break;
    case 3294:  //	Syntax error in DROP INDEX statement.
      break;

    case 3295:  //	Syntax error in DROP TABLE or DROP INDEX.
      break;
    case 3296:  //	Join expression not supported.
      break;
    case 3297:  //	Couldn't import table or query. No records found, or all records contain errors.
      break;
    case 3298:  //	There are several tables with that name. Please specify owner in the format 'owner.table'.
      break;
    case 3299:  //	ODBC Specification Conformance Error <message>. Report this error to the developer of your application.
      break;
    case 3300:  //	Can't create a relationship.
      break;

    case 3301:  //	Can't perform this operation; features in this version are not available in databases with older formats.
      break;
    case 3302:  //	Can't change a rule while the rules for this table are in use.
      break;
    case 3303:  //	Can't delete this field. It's part of one or more relationships.
      break;
    case 3304:  //	You must enter a personal identifier (PID) consisting of at least 4 and no more than 20 characters and digits.
      break;
    case 3305:  //	Invalid connection string in pass-through query.
      break;

    case 3306:  //	You've written a subquery that can return more than one field without using the EXISTS reserved word in the main query's FROM clause. Revise the SELECT statement of the subquery to request only one field.
      break;
    case 3307:  //	The number of columns in the two selected tables or queries of a union query don't match.
      break;
    case 3308:  //	Invalid TOP argument in select query.
      break;
    case 3309:  //	Property setting can't be larger than 2K.
      break;
    case 3310:  //	This property isn't supported for external data sources or for databases created with a previous version of Microsoft Jet.
      break;

    case 3311:  //	Property specified already exists.
      break;
    case 3312:  //	Validation rules and default values can't be placed on system or linked tables.
      break;
    case 3313:  //	Can't place this validation expression on this field.
      break;
    case 3314:  //	The field <name> can't contain a Null value because the Required property for this field is set to True. Enter a value in this field.
      break;
    case 3315:  //	Field <name> can't be a zero-length string.
      break;
    case 3316:  //	<Table-level validation text>.
      break;

    case 3317:  //	One or more values are prohibited by the validation rule <rule> set for <name>. Enter a value that the expression for this field can accept.
      break;
    case 3318:  //	Values specified in a TOP clause are not allowed in delete queries or reports.
      break;
    case 3319:  //	Syntax error in union query.
      break;
    case 3320:  //	<Error> in table-level validation expression.
      break;
    case 3321:  //	No database specified in connection string or IN clause.
      break;
    case 3322:  //	Crosstab query contains one or more invalid fixed column headings.
      break;

    case 3323:  //	The query cannot be used as a row source.
      break;
    case 3324:  //	The query is a DDL query and cannot be used as a row source.
      break;
    case 3325:  //	Pass-through query with ReturnsRecords property set to True did not return any records.
      break;
    case 3326:  //	This Recordset is not updatable.
      break;
    case 3334:  //	Can be present only in version 1.0 format.
      break;
    case 3336:  //	Btrieve: Invalid IndexDDF option in initialization setting.
      break;
    case 3337:  //	Invalid DataCodePage option in initialization setting.
      break;

    case 3338:  //	Btrieve: Xtrieve options aren't correct in initialization setting.
      break;
    case 3339:  //	Btrieve: Invalid IndexDeleteRenumber option in initialization setting.
      break;
    case 3340:  //	Query <name> is corrupt.
      break;
    case 3341:  //	The current field must match the join key <name> in the table that serves as the 'one' side of one-to-many relationship. Enter a record in the 'one' side table with the desired key value, and then make the entry with the desired join key in the 'many-only' table.
      break;

    case 3342:  //	Invalid Memo or OLE Object in subquery <name>.
      break;
    case 3343:  //	Unrecognized database format <filename>.
      break;
    case 3344:  //	The database engine does not recognize either the field <name> in a validation expression, or the default value in the table <name>.
      break;
    case 3345:  //	Unknown or invalid field reference <name>.
      break;
    case 3346:  //	Number of query values and destination fields aren't the same.
      break;
    case 3349:  //	Numeric field overflow.
      break;

    case 3350:  //	Object is invalid for operation.
      break;
    case 3351:  //	The ORDER BY expression <expression> includes fields that aren't selected by the query. Only those fields requested in the first query can be included in an ORDER BY expression.
      break;
    case 3352:  //	No destination field name in INSERT INTO statement <statement>.
      break;
    case 3353:  //	Btrieve: Can't find file Field.ddf.
      break;
    case 3354:  //	At most one record can be returned by this subquery.
      break;

    case 3355:  //	Syntax error in default value.
      break;
    case 3356:  //	You attempted to open a database that is already opened exclusively by user <name> on machine <name>. Try again when the database is available.
      break;
    case 3357:  //	This query is not a properly formed data-definition query.
      break;
    case 3358:  //	Can't open the Microsoft Jet engine workgroup information file.
      break;
    case 3359:  //	Pass-through query must contain at least one character.
      break;
    case 3360:  //	Query is too complex.
      break;

    case 3361:  //	Unions not allowed in a subquery.
      break;
    case 3362:  //	Single-row update/delete affected more than one row of a linked table. Unique index contains duplicate values.
      break;
    case 3364:  //	Can't use Memo or OLE Object field <name> in the SELECT clause of a union query.
      break;
    case 3365:  //	Can't set this property for remote objects.
      break;
    case 3366:  //	Can't append a relation with no fields defined.
      break;
    case 3367:  //	Can't append. An object with that name already exists in the collection.
      break;

    case 3368:  //	Relationship must be on the same number of fields with the same data types.
      break;
    case 3370:  //	Can't modify the design of table <name>. It's in a read-only database.
      break;
    case 3371:  //	Can't find table or constraint.
      break;
    case 3372:  //	No such index <name> on table <name>.
      break;
    case 3373:  //	Can't create relationship. Referenced table <name> doesn't have a primary key.
      break;
    case 3374:  //	The specified fields are not uniquely indexed in table <name>.
      break;

    case 3375:  //	Table <name> already has an index named <name>.
      break;
    case 3376:  //	Table <name> doesn't exist.
      break;
    case 3377:  //	No such relationship <name> on table <name>.
      break;
    case 3378:  //	There is already a relationship named <name> in the current database.
      break;
    case 3379:  //	Can't create relationships to enforce referential integrity. Existing data in table <name> violates referential integrity rules in table <name>.
      break;
    case 3380:  //	Field <name> already exists in table <name>.
      break;

    case 3381:  //	There is no field named <name> in table <name>.
      break;
    case 3382:  //	Size of field <name> is too long.
      break;
    case 3383:  //	Can't delete field <name>. It's part of one or more relationships.
      break;
    case 3384:  //	Can't delete a built-in property.
      break;
    case 3385:  //	User-defined properties don't support a Null value.
      break;
    case 3386:  //	Property <name> must be set before using this method.
      break;
    case 3388:  //	Unknown function <name> in validation expression or default value on <name>.
      break;

    case 3389:  //	Query support unavailable.
      break;
    case 3390:  //	Account name already exists.
      break;
    case 3393:  //	Can't perform join, group, sort, or indexed restriction. A value being searched or sorted on is too long.
      break;
    case 3394:  //	Can't save property; property is a schema property.
      break;
    case 3396:  //	Can't perform cascading operation. Since related records exist in table <name>, referential integrity rules would be violated.
      break;
    case 3397:  //	Can't perform cascading operation. There must be a related record in table <name>.
      break;

    case 3398:  //	Can't perform cascading operation. It would result in a null key in table <name>.
      break;
    case 3399:  //	Can't perform cascading operation. It would result in a duplicate key in table <name>.
      break;
    case 3400:  //	Can't perform cascading operation. It would result in two updates to field <name> in table <name>.
      break;
    case 3401:  //	Can't perform cascading operation. It would cause field <name> to become Null, which is not allowed.
      break;
    case 3402:  //	Can't perform cascading operation. It would cause field <name> to become a zero-length string, which is not allowed.
      break;

    case 3403:  //	Can't perform cascading operation: <validation text>.
      break;
    case 3404:  //	Can't perform cascading operation. The value entered is prohibited by the validation rule <rule> set for <name>.
      break;
    case 3405:  //	Error <error text> in validation rule.
      break;
    case 3406:  //	The expression you're trying to use for the DefaultValue property is invalid because <error text>. Use a valid expression to set this property.
      break;
    case 3407:  //	The server's MSysConf table exists, but is in an incorrect format. Contact your system administrator.
      break;

    case 3409:  //	Invalid field name <name> in definition of index or relationship.
      break;
    case 3411:  //	Invalid entry. Can't perform cascading operation in table <name> because the value entered is too large for field <name>.
      break;
    case 3412:  //	Can't perform cascading update on table <name> because it is currently in use by user <name> on machine <name>.
      break;
    case 3414:  //	Can't perform cascading operation on table <name> because it is currently in use.
      break;
    case 3415:  //	Zero-length string is valid only in a Text or Memo field.
      break;

    case 3416:  //	<reserved error alert> 
      break;
    case 3417:  //	An action query cannot be used as a row source.
      break;
    case 3418:  //	Can't open <tablename>. Another user has the table open using a different network control file or locking style.
      break;
    case 3419:  //	Can't open this Paradox 4.x or 5.x table because ParadoxNetStyle is set to 3.x in the Windows Registry.
      break;
    case 3420:  //	Object reference is invalid or the object library isn't registered.
      break;
    case 3421:  //	Data type conversion error.
      break;

    case 3422:  //	Can't modify table structure. Another user has the table open.
      break;
    case 3423:  //	You cannot use ODBC to import from, export to, or link an external Microsoft Jet or ISAM database table to your database.
      break;
    case 3424:  //	Can't create database because the locale is invalid.
      break;
    case 3428:  //	A problem occurred in your database. Correct the problem by repairing and compacting the database.
      break;
    case 3429:  //	Incompatible version of an installable ISAM.
      break;

    case 3430:  //	While loading the Microsoft Excel installable ISAM, OLE was unable to initialize.
      break;
    case 3431:  //	This is not a Microsoft Excel 5.0 file.
      break;
    case 3432:  //	Error opening a Microsoft Excel 5.0 file.
      break;
    case 3433:  //	Invalid setting in Excel key of Engines section of the Windows Registry.
      break;
    case 3434:  //	Can't expand named range.
      break;
    case 3435:  //	Cannot delete spreadsheet cells.
      break;
    case 3436:  //	Failure creating file.
      break;

    case 3437:  //	Spreadsheet is full.
      break;
    case 3438:  //	The data being exported does not match the format described in the Schema.ini file.
      break;
    case 3439:  //	You attempted to link or import a Microsoft Word mail merge file. Although you can export such files, you cannot link or import them.
      break;
    case 3440:  //	An attempt was made to import or link an empty text file. To import or link a text file, the file must contain data.
      break;
    case 3441:  //	Text file specification field separator matches decimal separator or text delimiter.
      break;

    case 3442:  //	In the text file specification <name>, the <name> option is invalid.
      break;
    case 3443:  //	In the fixed-width specification <name>, the <name> does not specify a width.
      break;
    case 3444:  //	In the fixed width specification <name>, column <column> does not specify a width.
      break;
    case 3445:  //	Incorrect version of the DLL file <name> was found.
      break;
    case 3446:  //	Jet VBA file (VBAJET.dll for 16-bit versions, or VBAJET32.dll for 32-bit versions) is missing. Try reinstalling the application that returned the error.
      break;

    case 3447:  //	The Jet VBA file (VBAJET.dll for 16-bit versions, or VBAJET32.dll for 32-bit versions) failed to initialize when called. Try reinstalling the application that returned the error.
      break;
    case 3448:  //	A call to an OLE system function was not successful. Try reinstalling the application that returned the error.
      break;
    case 3449:  //	No country code found in connection string for a linked table.
      break;

    case 3452:  //	You can't make changes to the design of the database at this replica.
      break;
    case 3453:  //	You can't establish or maintain an enforced relationship between a replicated table and a local table.
      break;
    case 3455:  //	Can't make the database replicable.
      break;
    case 3456:  //	Can't make the <name> object in <name> container replicable.
      break;
    case 3457:  //	You can't set the KeepLocal property for an object that is already replicated.
      break;
    case 3458:  //	The KeepLocal property cannot be set on a database; it can be set only on the objects in a database.
      break;

    case 3459:  //	After a database has been replicated, you cannot remove the replication features from the database.
      break;
    case 3460:  //	The operation you attempted conflicts with an existing operation involving this member of the replica set.
      break;
    case 3461:  //	The replication property you are attempting to set or delete is read-only and can't be changed.
      break;
    case 3462:  //	Failure to load a DLL.
      break;
    case 3463:  //	Can't find the .dll <name>.
      break;
    case 3464:  //	Data type mismatch in criteria expression.
      break;

    case 3465:  //	The disk drive you are attempting to access is unreadable.
      break;
    case 3468:  //	Access was denied while accessing dropbox folder <name>.
      break;
    case 3469:  //	The disk for dropbox folder <name> is full.
      break;
    case 3470:  //	Disk failure accessing dropbox folder <name>.
      break;
    case 3471:  //	Failure to write to the Synchronizer log file.
      break;
    case 3472:  //	Disk full for path <name>.
      break;
    case 3473:  //	Disk failure while accessing log file <name>.
      break;

    case 3474:  //	Can't open the log file <name> for writing.
      break;
    case 3475:  //	Sharing violation while attempting to open log file <name> in Deny Write mode.
      break;
    case 3476:  //	Invalid dropbox path <name>.
      break;
    case 3477:  //	Dropbox address <name> is syntactically invalid.
      break;
    case 3478:  //	The replica is not a partial replica.
      break;
    case 3479:  //	Can't designate a partial replica as the Design Master for the replica set.
      break;
    case 3480:  //	The relationship <name> in the partial filter expression is invalid.
      break;

    case 3481:  //	The table name <name> in the partial filter expression is invalid.
      break;
    case 3482:  //	The filter expression for the partial replica is invalid.
      break;
    case 3483:  //	The password supplied for the dropbox folder <name> is invalid.
      break;
    case 3484:  //	The password used by the Synchronizer to write to a destination dropbox folder is invalid.
      break;
    case 3485:  //	The object can't be replicated because the database is not replicated.
      break;
    case 3486:  //	You can't add a second Replication ID AutoNumber field to a table.
      break;

    case 3487:  //	The database you are attempting to replicate can't be converted.
      break;
    case 3488:  //	The value specified is not a ReplicaID for any member in the replica set.
      break;
    case 3489:  //	The object specified can't be replicated because it is missing a necessary resource.
      break;
    case 3490:  //	Can't create a new replica because the <name> object in <name> container could not be replicated.
      break;
    case 3491:  //	The database must be opened in exclusive mode before it can be replicated.
      break;

    case 3492:  //	The synchronization failed because a design change could not be applied to one of the replicas.
      break;
    case 3493:  //	Can't set the specified Registry parameter for the Synchronizer.
      break;
    case 3494:  //	Unable to retrieve the specified Registry parameter for the Synchronizer.
      break;
    case 3495:  //	There are no scheduled synchronizations between the two Synchronizers.
      break;
    case 3496:  //	Replication Manager cannot find the ExchangeID in the MSysExchangeLog table.
      break;

    case 3497:  //	Unable to set a schedule for the Synchronizer.
      break;
    case 3499:  //	Can't retrieve the full path information for a member of the replica set.
      break;
    case 3500:  //	Setting an exchange with the same Synchronizer is not allowed.
      break;
    case 3502:  //	The Design Master or replica is not being managed by a Synchronizer.
      break;
    case 3503:  //	The Synchronizer's Registry has no value set for the key you queried.
      break;
    case 3504:  //	The Synchronizer ID does not match an existing ID in the MSysTranspAddress table.
      break;

    case 3506:  //	The Synchronizer is unable to open the Synchronizer log.
      break;
    case 3507:  //	Failure writing to the Synchronizer log.
      break;
    case 3508:  //	There is no active transport for the Synchronizer.
      break;
    case 3509:  //	Could not find a valid transport for this Synchronizer.
      break;
    case 3510:  //	The member of the replica set you are attempting to synchronize is currently being used in another synchronization.
      break;
    case 3512:  //	Failed to read the dropbox folder.
      break;

    case 3513:  //	Failed to write to the dropbox folder.
      break;
    case 3514:  //	Synchronizer could not find any scheduled or on-demand synchronizations to process.
      break;
    case 3515:  //	The Microsoft Jet database engine could not read the system clock on your computer.
      break;
    case 3516:  //	Could not find transport address.
      break;
    case 3517:  //	Synchronizer could not find any messages to process.
      break;
    case 3518:  //	Could not find Synchronizer in the MSysTranspAddress table.
      break;

    case 3519:  //	Failed to send a message.
      break;
    case 3520:  //	The replica name or ID does not match a currently managed member of the replica set.
      break;
    case 3521:  //	Two members of the replica set cannot be synchronized because there is no common point to start the synchronization.
      break;
    case 3522:  //	Synchronizer cannot find the record of a specific synchronization in the MSysExchangeLog table.
      break;
    case 3523:  //	Synchronizer cannot find a specific version number in the MSysSchChange table.
      break;

    case 3524:  //	The history of design changes in the replica does not match the history in the Design Master.
      break;
    case 3525:  //	Synchronizer could not access the message database.
      break;
    case 3526:  //	The name selected for the system object is already in use.
      break;
    case 3527:  //	The Synchronizer or Replication Manager could not find the system object.
      break;
    case 3528:  //	There is no new data in shared memory for the Synchronizer or Replication Manager to read.
      break;

    case 3529:  //	The Synchronizer or Replication Manager found unread data in the shared memory. The existing data will be overwritten.
      break;
    case 3530:  //	The Synchronizer is already serving a client.
      break;
    case 3531:  //	The wait period for an event has timed out.
      break;
    case 3532:  //	Synchronizer could not be initialized.
      break;
    case 3533:  //	The system object used by a process still exists after the process has stopped.
      break;
    case 3534:  //	Synchronizer looked for a system event but did not find one to report to the client.
      break;

    case 3535:  //	Client has asked the Synchronizer to terminate operation.
      break;
    case 3536:  //	Synchronizer received an invalid message for a member of the replica set that it manages.
      break;
    case 3538:  //	Cannot initialize Synchronizer because there are too many applications running.
      break;
    case 3539:  //	A system error has occurred or your swap file has reached its limit.
      break;
    case 3540:  //	Your swap file has reached its limit or is corrupted.
      break;
    case 3541:  //	Synchronizer could not be shut down properly and is still active.
      break;

    case 3542:  //	Process stopped when attempting to terminate Synchronizer client.
      break;
    case 3543:  //	Synchronizer has not been set up.
      break;
    case 3544:  //	Synchronizer is already running.
      break;
    case 3545:  //	The two replicas you are attempting to synchronize are from different replica sets.
      break;
    case 3546:  //	The type of synchronization you are attempting is not valid.
      break;
    case 3547:  //	Synchronizer could not find a replica from the correct set to complete the synchronization.
      break;

    case 3548:  //	GUIDs do not match or the requested GUID could not be found.
      break;
    case 3549:  //	The file name you provided is too long.
      break;
    case 3550:  //	There is no index on the GUID column.
      break;
    case 3551:  //	Unable to delete the specified Registry parameter for the Synchronizer.
      break;
    case 3552:  //	The size of the Registry parameter exceeds the maximum allowed.
      break;
    case 3553:  //	The GUID could not be created.
      break;
    case 3555:  //	All valid nicknames for replicas are already in use.
      break;

    case 3556:  //	Invalid path for destination dropbox folder.
      break;
    case 3557:  //	Invalid address for destination dropbox folder.
      break;
    case 3558:  //	Disk I/O error at destination dropbox folder.
      break;
    case 3559:  //	Failure to write because destination disk is full.
      break;
    case 3560:  //	The two members of the replica set you are attempting to synchronize have the same ReplicaID.
      break;
    case 3561:  //	The two members of the replica set you are attempting to synchronize are both Design Masters.
      break;

    case 3562:  //	Access denied at destination dropbox folder.
      break;
    case 3563:  //	Fatal error accessing a local dropbox folder.
      break;
    case 3564:  //	Synchronizer can't find the source file for messages.
      break;
    case 3565:  //	There is a sharing violation in the source dropbox folder because the message database is open in another application.
      break;
    case 3566:  //	Network I/O error.
      break;
    case 3567:  //	Message in dropbox folder belongs to the wrong Synchronizer.
      break;

    case 3568:  //	Synchronizer could not delete a file.
      break;
    case 3569:  //	This member of the replica set has been logically removed from the set and is no longer available.
      break;
    case 3571:  //	The attempt to set a column in a partial replica violated a rule governing partial replicas.
      break;
    case 3572:  //	A disk I/O error occurred while reading or writing to the TEMP directory.
      break;
    case 3574:  //	The ReplicaID for this member of the replica set was reassigned during a move or copy procedure.
      break;

    case 3575:  //	The disk drive you are attempting to write to is full.
      sErr = _T("Не вистачає дискового простіру для збереження даних.");
      break;
    case 3576:  //	The database you are attempting to open is already in use by another application.
      break;
    case 3577:  //	Can't update replication system column.
      break;
    case 3578:  //	Failure to replicate database; can't determine whether database is open in exclusive mode.
      break;
    case 3581:  //	Can't open replication system table <name> because the table is already in use.
      break;
    case 3584:  //	Insufficient memory to complete operation.
      break;

    case 3586:  //	Syntax error in partial filter expression.
      break;
    case 3587:  //	Invalid expression in the ReplicaFilter property.
      break;
    case 3588:  //	Error when evaluating the partial filter expression.
      break;
    case 3589:  //	The partial filter expression contains an unknown function.
      break;
    case 3592:  //	You can't replicate a password-protected database or set password protection on a replicated database.
      break;
    case 3593:  //	Can't change a replicated database from allowing data changes at the Design Master and replicas to allowing data changes only at the Design Master.
      break;

    case 3594:  //	Can't change a replicated database from allowing data changes only at the Design Master to allowing data changes at the Design Master and other replicas.
      break;
    case 3595:  //	The system tables in your replica are no longer reliable and the replica should not be used.
      break;
    case 3605:  //	Synchronizing with a non-replicated database is not allowed. The <name> database is not a Design Master or replica.
      break;
    case 3607:  //	The replication property you are attempting to delete is read-only and cannot be removed.
      break;

    case 3608:  //	Record length is too long for an indexed Paradox table.
      break;
    case 3609:  //	No unique index found for the referenced field of the primary table.
      break;
    case 3610:  //	Same table referenced as both the source and destination in a make-table query.
      break;
    case 3611:  //	Can’t execute data definition statements on linked data sources.
      break;
    case 3612:  //	Multi-level GROUP BY clause is not allowed in a subquery.
      break;
    case 3613:  //	Can’t create a relationship on linked ODBC tables.
      break;

    case 3614:  //	GUID not allowed in Find method criteria expression.
      break;
    case 3615:  //	Type mismatch in JOIN expression.
      break;
    case 3616:  //	Updating data in a linked table is not supported by this ISAM.
      break;
    case 3617:  //	Deleting data in a linked table is not supported by this ISAM.
      break;
    case 3618:  //	Exceptions table could not be created on import/export.
      break;
    case 3619:  //	Records could not be added to exceptions table.
      break;
    case 3620:  //	The connection for viewing your linked Microsoft Excel worksheet was lost.
      break;

    case 3621:  //	Can’t change password on a shared open database.
      break;
    case 3622:  //	You must use the dbSeeChanges option with OpenRecordset when accessing a SQL Server table that has an IDENTITY column.
      break;
    case 3623:  //	Cannot access the FoxPro 3.0 bound DBF file <filename>.
      break;
    case 3624:  //	Couldn’t read the record; currently locked by another user.
      break;
    case 3625:  //	The text file specification <name> does not exist. You can’t import, export, or link using the specification.
      break;

    case 3626:  //	The operation failed. There are too many indexes on table <name>. Delete some of the indexes on the table and try the operation again.
      break;
  
  }
  if ( sErr.IsEmpty() ) {
    e->ReportError();
  }
  else {
    MessageBox(AfxGetMainWnd()->m_hWnd, sErr, _T("ЕРАГС"), MB_OK|MB_ICONSTOP);
  }
}

