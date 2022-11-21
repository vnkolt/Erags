#if !defined(MENU_H_INCLUDED)
#define MENU_H_INCLUDED

#define CONTEXT_UNKNWOWN      -1
#define ID_UNKNOWN            -1
#define CONTEXT_BIRTH         0
#define CONTEXT_MARRIAGE      1
#define CONTEXT_DIVORCE       2
#define CONTEXT_CHANGE        3
#define CONTEXT_DEATH         4
#define CONTEXT_RLIST         5

CString ContextMenu(HWND hParent, UINT& nPos, BOOL fMale, DATE d, LPCTSTR szMemo, bool fHideWin,
                    COleDateTime* pD1=NULL, /* BirthDate for DEATH */
                    COleDateTime* pD2=NULL  /* DeathDate for DEATH */
                   );


#endif // MENU_H_INCLUDED
