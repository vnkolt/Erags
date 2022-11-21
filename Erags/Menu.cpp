//
// Menu.cpp
//
#include "stdafx.h"
#include "Erags.h"
#include "DateFunc.h"
#include "Defaults.h"
#include "DepDlg.h"
#include "MainFrm.h"
#include "Menu.h"
#include "MltDocDlg.h"
#include "NoteDlg.h"

#include "EraForm.h"
#include "FormBirth.h"
#include "FormDeath.h"

#include "..\Common\CyrString.h"
#include "..\Controls\NewMenu.h"

// 
// ContextMenu
//

CString g_sMenuItem;
extern LPCTSTR g_szBirthDate;
extern LPCTSTR g_szDeathDate;

struct CXFLags {
  UINT  cx_id;
  long  cx_flag;
};


CString ContextMenu(HWND hParent, UINT& nPos, BOOL fMale, DATE d, LPCTSTR szMemo, bool fHideWin,
                   COleDateTime* pD1/*=NULL*/, COleDateTime* pD2/*=NULL*/ ) {
  
  CNewMenu menu;
  CString sMemo = szMemo;

  if(FALSE==menu.LoadMenu(IDR_CONTEXT))
    return sMemo;

  UINT nSavePos = nPos;

  POINT p;
  if ( FALSE==GetCursorPos(&p) )
    return sMemo;

  CWnd* pParent = CWnd::FromHandle(hParent);//CWnd::WindowFromPoint(p);
  CNewMenu* pPopup = DYNAMIC_DOWNCAST(CNewMenu,menu.GetSubMenu(nPos));
  //CMenu* pPopup = menu.GetSubMenu(nPos);
  ASSERT(pPopup != NULL);

  if ( pParent ) {
    if ( CONTEXT_MARRIAGE==nPos ) {
      switch( pParent->GetDlgCtrlID() ) {
        case IDC_MNOTICE  :
          pPopup->RemoveMenu(ID_WSURNAME    , MF_BYCOMMAND);
          pPopup->RemoveMenu(ID_WNAME       , MF_BYCOMMAND);
          pPopup->RemoveMenu(ID_NOMEDICSW   , MF_BYCOMMAND);
          break;
        case IDC_WNOTICE  :
          pPopup->RemoveMenu(ID_MSURNAME    , MF_BYCOMMAND);
          pPopup->RemoveMenu(ID_MNAME       , MF_BYCOMMAND);
          pPopup->RemoveMenu(ID_NOMEDICSM   , MF_BYCOMMAND);
          break;
      }
    }
  }

  UINT nItemCount = pPopup->GetMenuItemCount();
  DWORD nItem(0);
  CString sBothGro(_T("Громадянство батьків документами не підтверджується."));

  CString sEOS=_T(".");

  for( UINT i(1); i < nItemCount; i++ ) {
    UINT nState = pPopup->GetMenuState(i, MF_BYPOSITION);
    if ( (MF_SEPARATOR & nState)==0 ) {
      MENUITEMINFO miInfo;
      miInfo.cbSize = sizeof(miInfo);
      UINT uID = pPopup->GetMenuItemID(i);
      CString sMenuString, sMenuPrompt, sNewItem, sFind;
      if ( sMenuPrompt.LoadString(uID) ) {
        sMenuPrompt.TrimRight('.'); sMenuPrompt.TrimRight(); 
      }
      pPopup->GetMenuString(i, sMenuString, MF_BYPOSITION); sMenuString.TrimRight('.');

      switch (uID) {
        case ID_CERTIFICATE:
          //pPopup->ModifyMenu(i, MF_BYPOSITION|MF_STRING, ID_CERTIFICATE, theIniCache.GetNoCert() );
          pPopup->ModifyODMenu(i, MF_BYPOSITION|MF_STRING, ID_CERTIFICATE, (LPCTSTR)theIniCache.GetNoCert() );
          break;
        case ID_NOBIRTH_DATE:
          if ( pD1 && COleDateTime::valid==pD1->GetStatus() ) {
            sNewItem.Format(_T("%s %s"), g_szBirthDate, GetDateDDMMMYYYYr(*pD1) );
            pPopup->ModifyODMenu(i, MF_BYPOSITION|MF_STRING, ID_NOBIRTH_DATE, sNewItem);
            sFind = g_szBirthDate;
          }
          break;
        case ID_NODEATH_DATE:
          if ( pD2 && COleDateTime::valid==pD2->GetStatus() ) {
            sNewItem.Format(_T("%s %s"), g_szDeathDate, GetDateDDMMMYYYYr(*pD2) );
            pPopup->ModifyODMenu(i, MF_BYPOSITION|MF_STRING, ID_NODEATH_DATE, sNewItem);
            sFind = g_szDeathDate;
          }
          break;
		    case ID_NOCERTIFICATE:
          { CString sNewItem;
            SYSTEMTIME st;
            GetLocalTime(&st);
            sNewItem.Format(_T("Замість гербового свідоцтва видана довідка № від %02d.%02d.%04d р."),
                            st.wDay, st.wMonth, st.wYear);
            pPopup->ModifyODMenu(i, MF_BYPOSITION|MF_STRING, ID_NOCERTIFICATE, sNewItem);
            sFind = _T("замість гербового свідоцтва.");
          }
		      break;
        case ID_FCITIZENSHIP:
        case ID_MCITIZENSHIP:
          if (sMemo.Find(sBothGro) >=0 )
            sFind = sBothGro;
          break;
        case ID_RENEW:
        case ID_LONGTERM:
        case ID_DECLDATA20:
        case IDC_STILL_BORN: {
            CFrameWnd* pFrame = ((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
            if ( pFrame ) {
              CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
              if ( pForm ) {
                if ( pForm->IsKindOf(RUNTIME_CLASS(CFormBirth)) ) {
                  BOOL bFlag = FALSE;
                  if ( ID_RENEW==uID )
                    bFlag = ((CFormBirth*)pForm)->IsRenew();
                  else if ( ID_LONGTERM==uID )
                    bFlag = ((CFormBirth*)pForm)->IsLongTerm();
                  else if ( ID_DECLDATA20==uID )
                    bFlag = ((CFormBirth*)pForm)->IsDeclarantIn20();
                  else if ( IDC_STILL_BORN==uID ) {
                    bFlag = !((CFormBirth*)pForm)->IsAlive();
                  }
                  if ( bFlag )
                    pPopup->CheckMenuItem(i, MF_BYPOSITION|MF_CHECKED); 
                  else
                    pPopup->CheckMenuItem(i, MF_BYPOSITION|MF_UNCHECKED); 
                  nItem++;
                  continue;
                }
              }
            }
          }
          break;
        case ID_NOMEDICSM:
        case ID_NOMEDICSW:
          sFind = _T("Від медичного обстеження");
          sEOS  = _T("_");
          break;
      }
      if ( sFind.IsEmpty() ) {
        if ( sMemo.Find(sMenuString) >= 0 )
          sFind = sMenuString;
        else
          sFind = sMenuPrompt;
      }

      UINT uCheck = (FALSE==sFind.IsEmpty() && sMemo.Find(sFind, 0) >= 0) ? MF_CHECKED : MF_UNCHECKED;
      pPopup->CheckMenuItem(i, MF_BYPOSITION|uCheck);
      nItem++;
    }
  }

  if ( fHideWin) {
	  pPopup->RemoveMenu(ID_WINDOW, MF_BYCOMMAND);
    pPopup->EnableMenuItem(ID_CHANGESTO, MF_DISABLED|MF_GRAYED|MF_BYCOMMAND);
  }

  pPopup->SetMenuTitle(_T("Для Відміток"), MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
  nPos = pPopup->TrackPopupMenu(TPM_NONOTIFY|TPM_RETURNCMD|TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, p.x, p.y, pParent);

  CString sMenuString, sMenuPrompt, sFind;
  CString sMenuS, sMenuP;
  if ( sMenuPrompt.LoadString(nPos) ) {
    sMenuP = sMenuPrompt;
    sMenuP.TrimRight('.');
    sMenuP.TrimRight();
  }
  pPopup->GetMenuString(nPos, sMenuString, MF_BYCOMMAND);
  sMenuS = sMenuString;
  sMenuS.TrimRight('.');
  sMenuS.TrimRight();

  if ( ID_CHANGESTO==nPos && false==fHideWin) {
    CDepDlg dlg(pParent);
    dlg.DoModal();
  }
  else if ( ID_WINDOW==nPos ) {
    CNoteDlg dlg(CWnd::FromHandle(hParent));
    dlg.m_sNote   = sMemo;
    dlg.m_nPos    = nSavePos;
    dlg.m_d       = d;
    dlg.m_fMale   = fMale;
    dlg.m_pD1 = pD1;
    dlg.m_pD2 = pD2;
    int dlgRes = dlg.DoModal();
    if(dlgRes==IDYES || dlgRes==IDOK){
      sMemo = dlg.m_sNote;
    }
  }
  else if ( ID_SETMILITARYDOC==nPos ) {
    CFormDeath* pForm = (CFormDeath*)theApp.GetGetActiveForm();
    CMltDocDlg dlg(pForm->m_pRSet, pForm);
    dlg.DoModal();
  }
  else if ( ID_RENEW==nPos || ID_LONGTERM==nPos || ID_DECLDATA20==nPos || IDC_STILL_BORN==nPos) {
    CFrameWnd* pFrame = ((CMainFrame*)AfxGetMainWnd())->GetActiveFrame();
    if ( pFrame ) {
      CEraForm* pForm = (CEraForm*)pFrame->GetActiveView();
      if ( pForm ) {
        if ( pForm->IsKindOf(RUNTIME_CLASS(CFormBirth)) ) {
          switch(nPos ) {
            case ID_RENEW:
              ((CFormBirth*)pForm)->OnRenew();
              break;
            case ID_LONGTERM:
              ((CFormBirth*)pForm)->OnLongTerm();
              break;
            case ID_DECLDATA20:
              ((CFormBirth*)pForm)->OnDecl20();
              break;
            case IDC_STILL_BORN:
              ((CFormBirth*)pForm)->OnAliveFlag();
              break;
          }
        }
      }
    }
  }
  else if ( nPos ) {
    MENUITEMINFO miInfo;
    miInfo.cbSize = sizeof(miInfo);
    miInfo.fMask = MIIM_STATE;
    pPopup->GetMenuItemInfo(nPos, &miInfo, FALSE);

    BOOL fChecked = (miInfo.fState & MFS_CHECKED) ? TRUE : FALSE;

    switch ( nPos ) {
      case ID_NOBIRTH_DATE:
        sFind = sMenuS = g_szBirthDate;
        break;
      case ID_NODEATH_DATE:
        sFind = sMenuS = g_szDeathDate;
        break;
      case ID_NOCERTIFICATE:
        sFind = _T("Замість гербового свідоцтва ");
        sEOS = _T("р.");
        break;
      case ID_PMMD1:
      case ID_PMMD2:
      case ID_NPM:
      case ID_MOTHERIS:
      case ID_FOUNDLING:
      case ID_OTHER_MARRIAGE:
        sFind = sMenuP;
        break;
      default:
        if ( FALSE==sMenuP.IsEmpty() && sMemo.Find(sMenuP) >= 0 )
          sFind = sMenuP;
        else if ( FALSE==sMenuS.IsEmpty() && sMemo.Find(sMenuS) >= 0 )
          sFind = sMenuS;
        else
          sFind = sMenuS;
        break;
    }

    if ( sMemo.Find(sFind) == -1 ) {  // to add
      sMemo = Trim(sMemo);
      sMemo += ' ';
      if ( sFind==sMenuP || sFind==sMenuPrompt )
        sMemo += sMenuPrompt;
      else if ( sFind==sMenuS || sMenuString.Find(sFind)>=0 )
        sMemo += sMenuString;
      sMemo = Trim(sMemo);
    }
    else {                            // to extract
      CString s = GetSentence(sMemo, sFind, sEOS);
      if ( !s.IsEmpty() ) {
        sMemo = FindAndReplace(sMemo, s, _T(""), true);
        sMemo = FindAndReplace(sMemo, _T("  "), _T(" "), true);
        if ( sEOS==_T("_") ) {
          sMemo = FindAndReplace(sMemo, sEOS, _T(""), true);
        }
      }
    }
  }

  menu.DestroyMenu();

  return Trim(sMemo);
}
