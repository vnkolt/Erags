//
// HelpMan.cpp
//
#include "stdafx.h"
#include "Erags.h"

#include "HelpMan.h"

#include "..\Common\FHelpers.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolTipCache theToolTipCache;

typedef struct tagSCONTROL { UINT  id; LPCTSTR name; DWORD direction; } SCONTROL;
BOOL Is_IDC_STATIC(int id);

#define ID_FOUND_LIST (AFX_IDW_PANE_FIRST + 1)


SCONTROL BirthFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_SURNAME,                _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_LBL_RENEW,              _T("Renew")           ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_LBL_LONGTERM,           _T("LongTerm")        ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NAME,                   _T("Name")            ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_PATRONYMIC,             _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_BIRTH_PLACE,            _T("Birth_Place")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_COUNTRY,          _T("BP_Country")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_REGION,           _T("BP_Region")       ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_BIRTH_DISTRICT,         _T("BP_District")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_CITY,             _T("BP_City")         ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_DATEOFBIRTH,            _T("Birth_date")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NKIDS,                  _T("NKids")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BYCOUNT,                _T("ByCount")         ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_ALIVE_FLAG,             _T("Alive")           ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_MEDICAL_CERTIFICATE_NUMBER,_T("MedCertNumber"),PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MEDICAL_CERTIFICATE_DATE,_T("MedCertDate")    ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MEDICAL_CERTIFICATE_PSEUDUNYM,_T("MedCertPsuedo"),PPTOOLTIP_TOPEDGE_CENTER  },
   {IDC_MEDICAL_CERTIFICATE_BY, _T("MedCertBy")       ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_SOURCE_TYPE,            _T("SourceType")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_SOURCE_NDOC,            _T("SourceNum")       ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_SOURCE_DATE,            _T("SourceDate")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_SOURCE_BY,              _T("SourceBy")        ,PPTOOLTIP_TOPEDGE_RIGHT      },

   {IDC_FATHER_CITIZENSHIP,     _T("FCitizenship")    ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_SURNAME,         _T("FSurname")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_NAME,            _T("FName")           ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_PATRONYMIC,      _T("FPatronymic")     ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_FATHER_BIRTH_DATE,      _T("FBirt_date")      ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_FATHER_COUNTRY,         _T("FCountry")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_REGION,          _T("FRegion")         ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_DISTRICT,        _T("FDistrict")       ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_FATHER_CITY,            _T("FCity")           ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_FATHER_STREET,          _T("FStreet")         ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_FATHER_HOUSE,           _T("FHouse")          ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_FATHER_FLAT,            _T("FFlat")           ,PPTOOLTIP_BOTTOMEDGE_CENTER  },

   {IDC_MOTHER_CITIZENSHIP,     _T("MCitizenship")    ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MOTHER_SURNAME,         _T("MSurname")        ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MOTHER_NAME,            _T("MName")           ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_PATRONYMIC,      _T("MPatronymic")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_BIRTH_DATE,      _T("MBirt_date")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_COUNTRY,         _T("MCountry")        ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_REGION,          _T("MRegion")         ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_DISTRICT,        _T("MDistrict")       ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_CITY,            _T("MCity")           ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_STREET,          _T("MStreet")         ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_HOUSE,           _T("MHouse")          ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_MOTHER_FLAT,            _T("MFlat")           ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_DECLARANT_TYPE,         _T("Declarant")       ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_DECLARANT_NAME,         _T("DeclarantName")   ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_DECLARANT_ADDRESS,      _T("DeclarantAddress"),PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_DECLARANT_PASSPORT_TYPE,_T("PassportType")     ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_PASSPORT_SERIA,_T("PassportSeria")   ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_PASSPORT_NUMBER,_T("PassportNumber") ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_PASSPORT_DATE,_T("PassportDate")     ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_DECLARANT_PASSPORT_BY,  _T("PassportBy")       ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_DLG,          _T("TwoDeclarants")    ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_DECLARANT_20,           _T("Gr18Gr20")         ,PPTOOLTIP_TOPEDGE_RIGHT     },

   {IDC_CERTIFICATE_SERIA,      _T("CertificateSeria") ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_CERTIFICATE_NUMBER,     _T("CertificateNumber"),PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_NOTICE,                 _T("Notice")          ,PPTOOLTIP_BOTTOMEDGE_CENTER  },

   {0,                          NULL                  ,0                            }
};

SCONTROL MarriageFormControls[] = {
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT      },

   {IDC_MCITIZENSHIP,           _T("MCitizenship")    ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MOLD_SURNAME,           _T("MOldSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNEW_SURNAME,           _T("MNewSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MNAME,                  _T("MName")           ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPATRONYMIC,            _T("MPatronymic")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MBIRTH_DATE,            _T("MBirth_date")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_COUNTRY,         _T("MBirth_Country")  ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_REGION,          _T("MBirth_Region")   ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_DISTRICT,        _T("MBirth_District") ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MBIRTH_CITY,            _T("MBirth_City")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MRP_COUNTRY,            _T("MRP_Country")     ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MRP_REGION,             _T("MRP_Region")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MRP_DISTRICT,           _T("MRP_District")    ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MRP_CITY,               _T("MRP_City")        ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MRP_STREET,             _T("MRP_Street")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MRP_HOUSE,              _T("MRP_House")       ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MRP_FLAT,               _T("MRP_Flat")        ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MPASSPORT_TYPE,         _T("MPassportType")   ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MPASSPORT_SERIA,        _T("MPassportSeria")  ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MPASSPORT_NUMBER,       _T("MPassportNumber") ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MPASSPORT_DATE,         _T("MPassportDate")   ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MPASSPORT_BY,           _T("MPassportBy")     ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MFAMILY_STATUS,         _T("MStatus")         ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MACT_NUMBER,            _T("MActNumber")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MACT_DATE,              _T("MActDate")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MACT_BY,                _T("MActBy")          ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MNOTICE,                _T("MNotice")         ,PPTOOLTIP_BOTTOMEDGE_LEFT    },

   {IDC_WCITIZENSHIP,           _T("WCitizenship")    ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WOLD_SURNAME,           _T("WOldSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNEW_SURNAME,           _T("WNewSurname")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WNAME,                  _T("WName")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WPATRONYMIC,            _T("WPatronymic")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_DATE,            _T("WBirth_date")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WBIRTH_COUNTRY,         _T("WBirth_Country")  ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_REGION,          _T("WBirth_Region")   ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_DISTRICT,        _T("WBirth_District") ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_CITY,            _T("WBirth_City")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_COUNTRY,            _T("WRP_Country")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_REGION,             _T("WRP_Region")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_DISTRICT,           _T("WRP_District")    ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_CITY,               _T("WRP_City")        ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_STREET,             _T("WRP_Street")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_HOUSE,              _T("WRP_House")       ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WRP_FLAT,               _T("WRP_Flat")        ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WPASSPORT_TYPE,         _T("WPassportType")   ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_WPASSPORT_SERIA,        _T("WPassportSeria")  ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WPASSPORT_NUMBER,       _T("WPassportNumber") ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_WPASSPORT_DATE,         _T("WPassportDate")   ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WPASSPORT_BY,           _T("WPassportBy")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WFAMILY_STATUS,         _T("WStatus")         ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WACT_NUMBER,            _T("WActNumber")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WACT_DATE,              _T("WActDate")        ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WACT_BY,                _T("WActBy")          ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WNOTICE,                _T("WNotice")         ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_CERTIFICATE_SERIA,      _T("CertificateSeria") ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_CERTIFICATE_NUMBER,     _T("CertificateNumber"),PPTOOLTIP_BOTTOMEDGE_CENTER },

   {0,                          NULL                  ,0                            }
};

SCONTROL DivorceFormControls[] = {
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_MARRIAGE_BY,            _T("MarActBy")        ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_MARRIAGE_NUMBER,        _T("MarActNumber")    ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_MARRIAGE_DATE,          _T("MarActDate")      ,PPTOOLTIP_TOPEDGE_RIGHT      },

   {IDC_MMARRIAGE_NUMBER,       _T("MMarriageNum")    ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MOLD_SURNAME,           _T("MOldSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNEW_SURNAME,           _T("MNewSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MNAME,                  _T("MName")           ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPATRONYMIC,            _T("MPatronymic")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MBIRTH_DATE,            _T("MBirth_date")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_COUNTRY,         _T("MBirth_Country")  ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_REGION,          _T("MBirth_Region")   ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MBIRTH_DISTRICT,        _T("MBirth_District") ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MBIRTH_CITY,            _T("MBirth_City")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MPASSPORT_TYPE,         _T("MPassportType")   ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPASSPORT_SERIA,        _T("MPassportSeria")  ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPASSPORT_NUMBER,       _T("MPassportNumber") ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPASSPORT_DATE,         _T("MPassportDate")   ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MPASSPORT_BY,           _T("MPassportBy")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MCITIZENSHIP,           _T("MCitizenship")    ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MRP_COUNTRY,            _T("MRP_Country")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MRP_REGION,             _T("MRP_Region")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MRP_DISTRICT,           _T("MRP_District")    ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MRP_CITY,               _T("MRP_City")        ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MRP_STREET,             _T("MRP_Street")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MRP_HOUSE,              _T("MRP_House")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MRP_FLAT,               _T("MRP_Flat")        ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_MDUTY,                  _T("MDuty")           ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MDUTY2,                 _T("MDuty2")          ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MMONEY_TYPE,            _T("MMoneyType")      ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MCHECK_NUMBER,          _T("MCheckNum")       ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MCHECK_DATE,            _T("MCheckDate")      ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MCHECK_BANK,            _T("MCheckBank")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MCERTIFICATE_SERIA,     _T("MCertSeria")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MCERTIFICATE_NUMBER,    _T("MCertNumber")     ,PPTOOLTIP_BOTTOMEDGE_CENTER  },

   {IDC_WMARRIAGE_NUMBER,       _T("WMarriageNum")    ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WMARRIAGE_NUMBER,       _T("WarriageNum")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WOLD_SURNAME,           _T("WOldSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNEW_SURNAME,           _T("WNewSurname")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WNAME,                  _T("WName")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WPATRONYMIC,            _T("WPatronymic")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_DATE,            _T("WBirth_date")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_COUNTRY,         _T("WBirth_Country")  ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_REGION,          _T("WBirth_Region")   ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_DISTRICT,        _T("WBirth_District") ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WBIRTH_CITY,            _T("WBirth_City")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WPASSPORT_TYPE,         _T("WPassportType")   ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WPASSPORT_SERIA,        _T("WPassportSeria")  ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WPASSPORT_NUMBER,       _T("WPassportNumber") ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WPASSPORT_DATE,         _T("WPassportDate")   ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WPASSPORT_BY,           _T("WPassportBy")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WCITIZENSHIP,           _T("WCitizenship")    ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_COUNTRY,            _T("WRP_Country")     ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_REGION,             _T("WRP_Region")      ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_DISTRICT,           _T("WRP_District")    ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_CITY,               _T("WRP_City")        ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_STREET,             _T("WRP_Street")      ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_HOUSE,              _T("WRP_House")       ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WRP_FLAT,               _T("WRP_Flat")        ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_WDUTY,                  _T("WDuty")           ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WDUTY2,                 _T("WDuty2")          ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WMONEY_TYPE,            _T("WMoneyType")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WCHECK_NUMBER,          _T("WCheckNum")       ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WCHECK_DATE,            _T("WCheckDate")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WCHECK_BANK,            _T("WCheckBank")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WCERTIFICATE_SERIA,     _T("WCertSeria")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WCERTIFICATE_NUMBER,    _T("WCertNumber")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

//   {IDC_GROUND_TYPE,            _T("GroundType")      ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_GROUND,                 _T("Ground")          ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_GROUND_NUMBER,          _T("GroundNumber")    ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_GROUND_DATE,            _T("GroundDate")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_NKIDS,                  _T("NKids")           ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_MNOTICE,                _T("MNotice")         ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_WNOTICE,                _T("WNotice")         ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {0,                          NULL                  ,0                            }
};

SCONTROL ChangeFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_CITIZENSHIP,            _T("Citizenship")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_OLD_SURNAME,            _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_SURNAME,            _T("NewSurname")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_OLD_NAME,               _T("Name")            ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_NAME,               _T("NewName")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_OLD_PATRONYMIC,         _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_PATRONYMIC,         _T("NewPatronymic")   ,PPTOOLTIP_TOPEDGE_CENTER     },

   {IDC_BIRTH_DATE,             _T("Birth_date")      ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_BP_COUNTRY,             _T("BP_Country")      ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_BP_REGION,              _T("BP_Region")       ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_BP_DISTRICT,            _T("BP_District")     ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_BP_CITY,                _T("BP_City")         ,PPTOOLTIP_TOPEDGE_CENTER    },

   {IDC_RP_COUNTRY,             _T("RP_Country")      ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_REGION,              _T("RP_Region")       ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_DISTRICT,            _T("RP_District")     ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_CITY,                _T("RP_City")         ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_STREET,              _T("RP_Street")       ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_HOUSE,               _T("RP_House")        ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_RP_FLAT,                _T("RP_Flat")         ,PPTOOLTIP_TOPEDGE_RIGHT     },

   {IDC_BIRTHACT_NUMBER,        _T("BirthActNum")     ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_BIRTHACT_DATE,          _T("BirthActDate")    ,PPTOOLTIP_TOPEDGE_CENTER    },

   {IDC_CHECK_NUMBER,           _T("CheckNum")        ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_CHECK_DATE,             _T("CheckDate")       ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DUTY,                   _T("CheckDuty")       ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_CHECK_BANK,             _T("CheckBank")       ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },

   {IDC_PASSPORT_TYPE,          _T("PassportType")    ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_PASSPORT_SERIA,         _T("PassportSeria")   ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_PASSPORT_NUMBER,        _T("PassportNumber")  ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_PASSPORT_DATE,          _T("PassportDate")    ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_PASSPORT_BY,            _T("PassportBy")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },

   {IDC_CERTIFICATE_SERIA,      _T("CertificateSeria") ,PPTOOLTIP_BOTTOMEDGE_LEFT  },
   {IDC_CERTIFICATE_NUMBER,     _T("CertificateNumber"),PPTOOLTIP_BOTTOMEDGE_CENTER},
   {IDC_NOTICE,                 _T("Notice")           ,PPTOOLTIP_BOTTOMEDGE_CENTER},

   {0,                          NULL                  ,0                           }
};

SCONTROL DeathFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_CITIZENSHIP,            _T("Citizenship")     ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_SURNAME,                _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_NAME,                   _T("Name")            ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_PATRONYMIC,             _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_DEATH_DATE,             _T("Death_date")      ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_DP_COUNTRY,             _T("DP_Country")      ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_DP_REGION,              _T("DP_Region")       ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_DP_DISTRICT,            _T("DP_District")     ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_DP_CITY,                _T("DP_City")         ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_REASON_PSEUDO,          _T("Reason_Pseudo")   ,PPTOOLTIP_RIGHTEDGE_TOP     },
   {IDC_REASON,                 _T("Reason")          ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_MEDICAL_CERT_TYPE,      _T("MedCertType")     ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_MEDICAL_CERT_NUMBER,    _T("MedCertNumber")   ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_MEDICAL_CERT_DATE,      _T("MedCertDate")     ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_MEDICAL_CERT_BY_PSEUDO, _T("MedCertPsuedo")   ,PPTOOLTIP_TOPEDGE_RIGHT     },
   {IDC_MEDICAL_CERT_BY,        _T("MedCertBy")       ,PPTOOLTIP_TOPEDGE_RIGHT     },

   {IDC_BIRTH_DATE,             _T("Birth_date")      ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_BP_COUNTRY,             _T("BP_Country")      ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_BP_REGION,              _T("BP_Region")       ,PPTOOLTIP_TOPEDGE_LEFT      },
   {IDC_BP_DISTRICT,            _T("BP_District")     ,PPTOOLTIP_TOPEDGE_CENTER    },
   {IDC_BP_CITY,                _T("BP_City")         ,PPTOOLTIP_TOPEDGE_CENTER    },

   {IDC_RP_COUNTRY,             _T("RP_Country")      ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_RP_REGION,              _T("RP_Region")       ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_RP_DISTRICT,            _T("RP_District")     ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_RP_CITY,                _T("RP_City")         ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_RP_STREET,              _T("RP_Street")       ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_RP_HOUSE,               _T("RP_House")        ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_RP_FLAT,                _T("RP_Flat")         ,PPTOOLTIP_BOTTOMEDGE_CENTER },

   {IDC_IN,                     _T("IN")              ,PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_MILITARY,               _T("Military")        ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_PASSPORT_TYPE,          _T("PassportType")    ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_PASSPORT_SERIA,         _T("PassportSeria")   ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_PASSPORT_NUMBER,        _T("PassportNumber")  ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_PASSPORT_DATE,          _T("PassportDate")    ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_PASSPORT_BY,            _T("PassportBy")      ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },

   {IDC_DECLARANT_NAME,         _T("DeclarantName")        ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_ADDRESS,      _T("DeclarantAddress")     ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_DECLARANT_PASSPORT_TYPE,_T("DeclarantPassportType"),PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_DECLARANT_PASSPORT_SERIA,_T("DeclarantPassportSeria"),PPTOOLTIP_BOTTOMEDGE_RIGHT},
   {IDC_DECLARANT_PASSPORT_NUMBER,_T("DeclarantPassportNumber"),PPTOOLTIP_BOTTOMEDGE_RIGHT},
   {IDC_DECLARANT_PASSPORT_DATE,_T("DeclarantPassportDate"),PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_DECLARANT_PASSPORT_BY,  _T("DeclarantPassportBy")  ,PPTOOLTIP_BOTTOMEDGE_RIGHT  },
   {IDC_CERTIFICATE_SERIA,      _T("CertificateSeria") ,PPTOOLTIP_BOTTOMEDGE_LEFT   },
   {IDC_CERTIFICATE_NUMBER,     _T("CertificateNumber"),PPTOOLTIP_BOTTOMEDGE_CENTER },
   {IDC_NOTICE,                 _T("Notice")          ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {0,                          NULL                  ,0                            }
};

SCONTROL MainBarControls[] = {
   {ID_FILE_OPEN,               _T("FileOpen")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {ID_BIRTH,                   _T("BirthReg")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {0,                          NULL                  ,0                            }
};

SCONTROL SearchWndControls[] = {
   {ID_NEW_SEARCH,              _T("NewSearch")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_FILE_SAVE,               _T("SaveSearch")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_FINDPATH,                _T("SearchPath")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_FIND,                    _T("BeginSearch")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_FIND_EQU,                _T("EquMatching")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_PARTIAL_MATCHING,        _T("PartialMatching") ,PPTOOLTIP_TOPEDGE_CENTER     },

   {ID_ENABLE_BIRTHES,          _T("Birthes")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_ENABLE_MARRIAGES,        _T("Marriages")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_ENABLE_DIVORCES,         _T("Divorces")        ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_ENABLE_CHANGES,          _T("Changes")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_ENABLE_DEATHES,          _T("Deathes")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {ID_GOTO_FOUNDREC,           _T("GotoFoundRec")    ,PPTOOLTIP_TOPEDGE_CENTER     },

   {ID_SEARCH_LIST,             _T("SearchList")      ,PPTOOLTIP_TOPEDGE_CENTER   },
   {ID_FOUND_LIST,              _T("FoundList")       ,PPTOOLTIP_TOPEDGE_CENTER   },

   {0,                          NULL                  ,0                            }
};

SCONTROL SVDlgControls[] = {
   {IDC_REPEAT,                 _T("Repeat")          ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_DATEOUT,                _T("DateOut")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_AS_DATEREG,             _T("AsDateReg")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_RTREE,                  _T("RTree")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_REGPLACE,               _T("RegPlace")        ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_OWNER,                  _T("Owner")           ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_BOSS,                   _T("Boss")            ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDYES,                      _T("Yes")             ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDNO,                       _T("No")              ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_MSURNAME_1,             _T("MSurname")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_MNAME_1,                _T("MName")           ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_MPATRONYMIC_1,          _T("MPatronymic")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_WSURNAME_1,             _T("WSurname")        ,PPTOOLTIP_BOTTOMEDGE_LEFT    },
   {IDC_WNAME_1,                _T("WName")           ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_WPATRONYMIC_1,          _T("WPatronymic")     ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },
   {IDC_SURNAME_TO,             _T("SurnameTo")       ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_NAME_TO,                _T("NameTo")          ,PPTOOLTIP_BOTTOMEDGE_CENTER  },
   {IDC_PATRONYMIC_TO,          _T("PatronymicTo")    ,PPTOOLTIP_BOTTOMEDGE_RIGHT   },

   {IDC_VERDICT_OF,             _T("VerdictOf")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_VERDICT_DATE,           _T("VerdictDate")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_VERDICT_NUMBER,         _T("VerdictNumber")   ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWFATHER_SURNAME,      _T("NFSurname")       ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NEWFATHER_NAME,         _T("NFName")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWFATHER_PATRONYMIC,   _T("NFPatronymic")    ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWMOTHER_SURNAME,      _T("NMSurname")       ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NEWMOTHER_NAME,         _T("NMName")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWMOTHER_PATRONYMIC,   _T("NMPatronymic")    ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWSURNAME,             _T("NSurname")        ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NEWNAME,                _T("NName")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWPATRONYMIC,          _T("NPatronymic")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NEWBIRTH_DATE,          _T("NBirthDate")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_COUNTRY,          _T("NBirthCountry")   ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_REGION,           _T("NBirthRegion")    ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_DISTRICT,         _T("NBirthDistrict")  ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_BIRTH_CITY,             _T("NBirthCity")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_STRIKE_OUT,             _T("StrikeOut")       ,PPTOOLTIP_TOPEDGE_CENTER     },
   {0,                          NULL                  ,0                            }
};

SCONTROL* GetControl(LPCTSTR szName, UINT id) {
  if ( NULL==szName )
    return NULL;
  SCONTROL* pKnownControls = NULL;
  if      ( stricmp(szName, _T("FORM_BIRTH"))==0 )
    pKnownControls = BirthFormControls;
  else if ( stricmp(szName, _T("FORM_DEATH"))==0 )
    pKnownControls = DeathFormControls;
  else if ( stricmp(szName, _T("FORM_MARRIAGE"))==0 )
    pKnownControls = MarriageFormControls;
  else if ( stricmp(szName, _T("FORM_DIVORCE"))==0 )
    pKnownControls = DivorceFormControls;
  else if ( stricmp(szName, _T("FORM_CHANGE"))==0 )
    pKnownControls = ChangeFormControls;
  else if ( stricmp(szName, _T("MainBar"))==0 )
    pKnownControls = MainBarControls;
  else if ( stricmp(szName, _T("SearchWindow"))==0 )
    pKnownControls = SearchWndControls;
  else if ( stricmp(szName, _T("SvDlg"))==0 )
    pKnownControls = SVDlgControls;
  else
    return NULL;

  if ( pKnownControls ) {
    for( int i(0); pKnownControls[i].id; i++ ) {
      if ( id==pKnownControls[i].id )
        return &pKnownControls[i];
    }
  }
  return NULL;
}

CString GetControlContext(LPCTSTR szBuffer, LPCTSTR szControlName) {
  CString s, sBegin, sEnd;
  sBegin.Format(_T("<%s>"), szControlName);
  sEnd.Format(_T("</%s>"), szControlName);
  const char* p1 = strstr(szBuffer, sBegin);
  const char* p2 = strstr(szBuffer, sEnd);
  if ( p1 && p2 ) {
    int iLen = p2 - p1 - sEnd.GetLength()+1;
    s = CString(p1+sBegin.GetLength(), iLen);
    s.TrimLeft();
    s.TrimRight();
  }
  return s;
}
///////////////////////////////////////////////////////
// CToolTipCache class members
//
CToolTipCache::CToolTipCache() {
}
CToolTipCache::~CToolTipCache() {
}
void CToolTipCache::Clear() {
  m_map.RemoveAll();
}
void CToolTipCache::Add(LPCTSTR szParentName, LPCTSTR szControlName, CString& szContent) {
  CString sKey;
  sKey.Format(_T("%s_%s"), szParentName, szControlName);
  m_map.SetAt(sKey, szContent);
}

CString CToolTipCache::Lookup(LPCTSTR szParentName, LPCTSTR szControlName) {
  CString s, sKey;
  sKey.Format(_T("%s_%s"), szParentName, szControlName);
  m_map.Lookup(sKey, s);
  return s;
}

void CToolTipCache::FillForParent(TCHAR* pBuffer, CWnd* pParent, LPCTSTR szFormName, CPPToolTip* pTooltip) {
  CWnd* pWnd = pParent->GetWindow(GW_CHILD);
  while ( pWnd ) {
    CWnd* pChildWnd = pWnd->GetTopWindow();
    if ( pChildWnd ) {
      FillForParent(pBuffer, pWnd, szFormName, pTooltip);
    }
    UINT id = pWnd->GetDlgCtrlID();
    if ( FALSE==Is_IDC_STATIC(id) ) {
      SCONTROL* pControl = GetControl(szFormName, id);
      if ( pControl ) {
        CString sContext = GetControlContext(pBuffer, pControl->name);
        if ( !sContext.IsEmpty() ) {
          pTooltip->AddTool(pWnd, sContext);
          Add(szFormName, pControl->name, sContext);
        }
      }
    }
    pWnd = pWnd->GetWindow(GW_HWNDNEXT);
  }
}
void CToolTipCache::Fill(CWnd* pParent, LPCTSTR szFormName, CPPToolTip* pToolTip) {
  CString szHelpFile;
  szHelpFile.Format(_T("%s\\Help\\%s_Help_%s.htm"), GetModulePath(), szFormName, theApp.GetHelpPostfix());
  CFile f;

  if ( f.Open(szHelpFile, CFile::modeRead) ) {
    Clear();
    int nCount = (int)f.GetLength();
    TCHAR* pBuffer = new TCHAR[nCount+1];
    f.Read(pBuffer, nCount);
    f.Close();
    pBuffer[nCount] = 0;
    FillForParent(pBuffer, pParent, szFormName, pToolTip);

/************************************** : by VK at 21.04.2005 21:52:15 **\
  	CWnd* pItemWnd = pParent->GetWindow(GW_CHILD);
    while(pItemWnd) {
      CRuntimeClass* pRuntimeClass = pItemWnd->GetRuntimeClass();
      if ( pItemWnd->IsKindOf(RUNTIME_CLASS(CReBar)) ) {
        CWnd* pDlg = pItemWnd->GetWindow(GW_CHILD);
        if ( pDlg ) { // this window has controls
          Fill(pDlg, szFormName, pToolTip);
        }
      }
      else if ( pItemWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)) ) {
        CSplitterWnd* pSplitter = (CSplitterWnd*)pItemWnd;
        for( int row(0); row < pSplitter->GetRowCount(); row++ ) {
          for( int col(0); col < pSplitter->GetColumnCount(); col++ ) {
            CWnd* pPane = pSplitter->GetPane(row, col);
            if ( pPane )
              Fill(pPane, szFormName, pToolTip);
          }
        }
      }
      else if ( !pItemWnd->IsKindOf(RUNTIME_CLASS(CStatic)) ) {
        SCONTROL* pControl = GetControl(szFormName, pItemWnd->GetDlgCtrlID());
        if ( pControl ) {
          CString sContext = GetControlContext(pBuffer, pControl->name);
          if ( !sContext.IsEmpty() ) {
            pToolTip->AddTool(pItemWnd, sContext);
            Add(szFormName, pControl->name, sContext);
          }
        }
        // AddTool(pParent, pTooltip, szFormName, pItemWnd->GetDlgCtrlID() );
      }
      pItemWnd = pItemWnd->GetWindow(GW_HWNDNEXT);
    }
\************************************** : by VK at 21.04.2005 21:52:23 **/
    delete pBuffer;

  }
  pToolTip->SetCallbackHyperlink(pParent->GetSafeHwnd(), UNM_HYPERLINK_CLICKED);
}


void CToolTipCache::FillForToolBar(CToolBar* pParent, LPCTSTR szName, CPPToolTip* pToolTip) {
  CString szHelpFile;
  szHelpFile.Format(_T("%s\\Help\\%s_Help_%s.htm"), GetModulePath(), szName, theApp.GetHelpPostfix());
  CFile f;

  if ( f.Open(szHelpFile, CFile::modeRead) ) {
    int nCount = (int)f.GetLength();
    TCHAR* pBuffer = new TCHAR[nCount+1];
    f.Read(pBuffer, nCount);
    f.Close();
    pBuffer[nCount] = 0;

    int nButtons  = pParent->GetToolBarCtrl().GetButtonCount();

    for( int i(0); i < nButtons; i++ ) {
      int nItemID = pParent->GetItemID(i);
      SCONTROL* pControl = GetControl(szName, nItemID);
      if ( pControl ) {
        CString sContext = GetControlContext(pBuffer, pControl->name);
        if ( !sContext.IsEmpty() ) {
          pToolTip->AddTool(pParent, sContext);
          Add(szName, pControl->name, sContext);
        }
      }
    }

/************************************** : by VK at 24.05.2004 21:45:14 **\
  	CWnd* pItemWnd = pParent->GetWindow(GW_CHILD);
    while(pItemWnd) {
      CRuntimeClass* pRuntimeClass = pItemWnd->GetRuntimeClass();
      if ( !pItemWnd->IsKindOf(RUNTIME_CLASS(CStatic)) ) {
        SCONTROL* pControl = GetControl(pItemWnd->GetDlgCtrlID());
        if ( pControl ) {
          CString sContext = GetControlContext(pBuffer, pControl->name);
          if ( !sContext.IsEmpty() ) {
            pToolTip->AddTool(pItemWnd, sContext);
            Add(szFormName, pControl->name, sContext);
          }
        }
        // AddTool(pParent, pTooltip, szFormName, pItemWnd->GetDlgCtrlID() );
      }
      pItemWnd = pItemWnd->GetWindow(GW_HWNDNEXT);
    }
\************************************** : by VK at 24.05.2004 21:45:30 **/
    delete pBuffer;

  }
  pToolTip->SetCallbackHyperlink(pParent->GetSafeHwnd(), UNM_HYPERLINK_CLICKED);
}



void SetDefaults(CPPToolTip* pPPToolTip) {
	DWORD dwBehaviour = PPTOOLTIP_CLOSE_LEAVEWND |
	                    PPTOOLTIP_NOCLOSE_OVER   |
	                    PPTOOLTIP_DISABLE_AUTOPOP;
	                    //PPTOOLTIP_TRACKING_MOUSE;
	pPPToolTip->SetBehaviour(dwBehaviour);
  pPPToolTip->EnableEscapeSequences(FALSE);
  pPPToolTip->SetTooltipShadow(0, 0);
  pPPToolTip->SetSize(CPPToolTip::PPTTSZ_MARGIN_CX, 6);
  pPPToolTip->SetSize(CPPToolTip::PPTTSZ_MARGIN_CY, 6);
  pPPToolTip->SetSize(CPPToolTip::PPTTSZ_ROUNDED_CY,16);

  //pPPToolTip->SetDebugMode(TRUE);
//  pPPToolTip->SetBorder(

  // 	if (m_multiple_show) dwBehaviour |= PPTOOLTIP_MULTIPLE_SHOW;
}

void ShowHelpTooltip(CPPToolTip* pPPToolTip, CToolBar* pParent, LPCTSTR szParentName, UINT CtrlId) {
  SCONTROL* pControl = GetControl(szParentName, CtrlId);
  if ( NULL==pControl )
    return;
  LPCTSTR szControlName = pControl->name;

  CString szContent = theToolTipCache.Lookup( szParentName, szControlName);
  if ( szContent.IsEmpty() )
    return;

  int nIndex = pParent->CommandToIndex(CtrlId);

  CRect r;
  pParent->GetItemRect(nIndex, &r);
  pParent->ClientToScreen(&r);

/************************************** : by VK at 18.05.2004 7:20:21 **\
+-------------------------------+
|                     +-----+   |
| +--------+          |     |   |
| |        |          +-----+   |
| +--------+                    |
+-------------------------------+

\************************************** : by VK at 18.05.2004 7:20:23 **/
  CPoint pt = r.CenterPoint();
  pt.y = r.bottom;
  int xOffs = (r.right-r.left)/3;
  switch(pControl->direction) {
    case PPTOOLTIP_TOPEDGE_LEFT:
      pt.x = r.left+xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_TOPEDGE_CENTER:
      pt.y = r.bottom;
      break;
    case PPTOOLTIP_TOPEDGE_RIGHT:
      pt.x = r.right-xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_RIGHTEDGE_TOP:
      pt.x = r.left+xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_BOTTOMEDGE_LEFT:
      pt.x = r.left+xOffs;  pt.y = r.top;
      break;
    case PPTOOLTIP_BOTTOMEDGE_CENTER:
      pt.y = r.top;
      break;
    case PPTOOLTIP_BOTTOMEDGE_RIGHT:
      pt.x = r.right-xOffs; pt.y = r.top;
      break;
  }
  switch ( CtrlId ) {
    case IDC_REASON_PSEUDO:
      pt.x = r.left; pt.y = (r.top + r.bottom)/2;
      break;
    case ID_SEARCH_LIST:
    case ID_FOUND_LIST:
      pt.x = r.left; pt.y = (r.top + r.bottom)/2;
      break;
    case IDC_MARRIAGE_BY:
      pt.x = r.left+10; pt.y = r.bottom;
      break;
  }

  pPPToolTip->SetDirection(pControl->direction);
  pPPToolTip->ShowHelpTooltip(&pt, szContent);

}

void ShowHelpTooltipSetFocus(CPPToolTip* pPPToolTip, CWnd* pParent, LPCTSTR szParentName, CWnd* pControl, UINT CtrlId) {
  if ( pControl && FALSE==pControl->IsWindowVisible() ) {
    return;
  }
  CWnd* pWnd = NULL;
  if ( pParent->IsKindOf(RUNTIME_CLASS(CControlBar)) )
    pWnd = pControl;
  else
    pWnd = pParent->GetDlgItem(CtrlId);
/************************************** : by VK at 09.05.2005 4:58:35 **\
  if ( NULL==pWnd ) {
    if ( pControl && pControl->IsKindOf(RUNTIME_CLASS(CDateTimeEditCtrlEditCtrl)) ) {
      pWnd = pControl->GetParent();
      if ( pWnd )
        CtrlId = pWnd->GetDlgCtrlID();
    }
    if ( NULL==pWnd )
      return;
  }
\************************************** : by VK at 09.05.2005 4:58:38 **/
  SCONTROL* pSControl = GetControl(szParentName, CtrlId);
  if ( NULL==pSControl )
    return;

  LPCTSTR szControlName = pSControl->name;

  CString szContent = theToolTipCache.Lookup( szParentName, szControlName);
  if ( szContent.IsEmpty() )
    return;

  CRect rParent;
  pParent->GetWindowRect(&rParent);

  CRect r;
  pWnd->GetWindowRect(r);
/************************************** : by VK at 18.05.2004 7:20:21 **\
+-------------------------------+
|                     +-----+   |
| +--------+          |     |   |
| |        |          +-----+   |
| +--------+                    |
+-------------------------------+

\************************************** : by VK at 18.05.2004 7:20:23 **/
  CPoint pt = r.CenterPoint();
  pt.y = r.bottom;
  int xOffs = (r.right-r.left)/3;
  switch(pSControl->direction) {
    case PPTOOLTIP_TOPEDGE_LEFT:
      pt.x = r.left+xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_TOPEDGE_CENTER:
      pt.y = r.bottom;
      break;
    case PPTOOLTIP_TOPEDGE_RIGHT:
      pt.x = r.right-xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_RIGHTEDGE_TOP:
      pt.x = r.left+xOffs;  pt.y = r.bottom;
      break;
    case PPTOOLTIP_BOTTOMEDGE_LEFT:
      pt.x = r.left+xOffs;  pt.y = r.top;
      break;
    case PPTOOLTIP_BOTTOMEDGE_CENTER:
      pt.y = r.top;
      break;
    case PPTOOLTIP_BOTTOMEDGE_RIGHT:
      pt.x = r.right-xOffs; pt.y = r.top;
      break;
  }
  switch ( CtrlId ) {
    case IDC_REASON_PSEUDO:
      pt.x = r.left; pt.y = (r.top + r.bottom)/2;
      break;
    case ID_SEARCH_LIST:
    case ID_FOUND_LIST:
      pt.x = (r.left+r.right)/2; pt.y = (r.top + r.bottom)/2;
      break;
    case IDC_MARRIAGE_BY:
      pt.x = r.left+10; pt.y = r.bottom;
      break;
  }

  pPPToolTip->SetDirection(pSControl->direction);
  pPPToolTip->ShowHelpTooltip(&pt, szContent);

}

void ShowHelpTooltip(CPPToolTip* pPPToolTip, CWnd* pParent, LPCTSTR szParentName, UINT CtrlId) {
  CWnd* pWnd = pParent->GetDlgItem(CtrlId);
  if ( NULL==pWnd )
    return;

  SCONTROL* pControl = GetControl(szParentName, CtrlId);
  if ( NULL==pControl )
    return;

  LPCTSTR szControlName = pControl->name;
  if ( NULL==szControlName )
    return;

  CString szHelpFile;
  szHelpFile.Format(_T("%s\\Help\\%s_%s.htm"), GetModulePath(), szParentName, szControlName);
  CFile f;
  if ( f.Open(szHelpFile, CFile::modeRead) ) {
    CString s;
    int nCount = (int)f.GetLength();
    f.Read(s.GetBuffer(nCount+1), nCount);
    s.ReleaseBuffer();
    f.Close();

    theToolTipCache.Add(szParentName, szControlName, s);

  }

}
