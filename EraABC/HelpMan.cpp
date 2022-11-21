//
// HelpMan.cpp
//
#include "stdafx.h"
#include "EraABC.h"

#include "HelpMan.h"

#include "..\Common\FHelpers.h"
#include "..\Controls\CPPTooltip\PPTooltip.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CToolTipCache theToolTipCache;

typedef struct tagSCONTROL {
  UINT    id;       // ID контрола в форме (диалоге, окне)
  LPCTSTR name;     // Имя контрола в .htm-файле
  DWORD   direction;// Положение и направление указателя PP-тултипа
} SCONTROL;
BOOL Is_IDC_STATIC(int id);

// Массив для формы ввода рождений
SCONTROL BirthFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_SURNAME,                _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NAME,                   _T("Name")            ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_PATRONYMIC,             _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {0,                          NULL                  ,0                            }
};

// Массив для формы ввода браков
SCONTROL MarriageFormControls[] = {
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_RIGHT      },

   {IDC_MOLD_SURNAME,           _T("MOldSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNEW_SURNAME,           _T("MNewSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNAME,                  _T("MName")           ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPATRONYMIC,            _T("MPatronymic")     ,PPTOOLTIP_TOPEDGE_LEFT       },

   {IDC_WOLD_SURNAME,           _T("WOldSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNEW_SURNAME,           _T("WNewSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNAME,                  _T("WName")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WPATRONYMIC,            _T("WPatronymic")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {0,                          NULL                  ,0                            }
};

// Массив для формы ввода расторжений браков
SCONTROL DivorceFormControls[] = {
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },

   {IDC_MOLD_SURNAME,           _T("MOldSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNEW_SURNAME,           _T("MNewSurname")     ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MNAME,                  _T("MName")           ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_MPATRONYMIC,            _T("MPatronymic")     ,PPTOOLTIP_TOPEDGE_LEFT       },

   {IDC_WOLD_SURNAME,           _T("WOldSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNEW_SURNAME,           _T("WNewSurname")     ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WNAME,                  _T("WName")           ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_WPATRONYMIC,            _T("WPatronymic")     ,PPTOOLTIP_TOPEDGE_CENTER     },

   {0,                          NULL                  ,0                            }
};

// Массив для формы ввода перемен
SCONTROL ChangeFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_OLD_SURNAME,            _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_SURNAME,            _T("NewSurname")      ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_OLD_NAME,               _T("Name")            ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_NAME,               _T("NewName")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_OLD_PATRONYMIC,         _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NEW_PATRONYMIC,         _T("NewPatronymic")   ,PPTOOLTIP_TOPEDGE_CENTER     },
   {0,                          NULL                  ,0                            }
};

// Массив для формы ввода смертей
SCONTROL DeathFormControls[] = {
   {IDC_SEX,                    _T("Sex")             ,PPTOOLTIP_TOPEDGE_RIGHT      },
   {IDC_DATEREG,                _T("DateReg")         ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_NUMBER,                 _T("Number")          ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_SURNAME,                _T("Surname")         ,PPTOOLTIP_TOPEDGE_LEFT       },
   {IDC_NAME,                   _T("Name")            ,PPTOOLTIP_TOPEDGE_CENTER     },
   {IDC_PATRONYMIC,             _T("Patronymic")      ,PPTOOLTIP_TOPEDGE_CENTER     },
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
  char* p1 = strstr(szBuffer, sBegin);
  char* p2 = strstr(szBuffer, sEnd);
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
    // Clear();
    int nCount = (int)f.GetLength();
    TCHAR* pBuffer = new TCHAR[nCount+1];
    f.Read(pBuffer, nCount);
    f.Close();
    pBuffer[nCount] = 0;
    FillForParent(pBuffer, pParent, szFormName, pToolTip);
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
    delete pBuffer;

  }
  pToolTip->SetCallbackHyperlink(pParent->GetSafeHwnd(), UNM_HYPERLINK_CLICKED);
}



void SetDefaults(CPPToolTip* pPPToolTip) {
	DWORD dwBehaviour = PPTOOLTIP_CLOSE_LEAVEWND |  //Close tooltip if mouse leave the control
	                    PPTOOLTIP_NOCLOSE_OVER   |  //No close tooltip if mouse over him
	                    PPTOOLTIP_DISABLE_AUTOPOP;  //Disables autopop tooltip from timer
	                    //PPTOOLTIP_TRACKING_MOUSE;
	pPPToolTip->SetBehaviour(dwBehaviour);      // Устанавливаем поведение PP-тултипа
  pPPToolTip->EnableEscapeSequences(FALSE);   // Запрещаем escape-последовательности
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
