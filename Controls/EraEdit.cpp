// EraEdit.cpp : implementation file
//
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "EraControls.h"
#include "EraMonthCalCtrl.h"
#include "NewMenu.h"
#include "VisualStylesXP.h"

// Common
#include "..\Common\CyrString.h"
#include "..\Common\EraMessages.h"

#include <winuser.h>

BOOL AFXAPI AfxFieldText(CDataExchange* pDX, int nIDC, void* pv, CDaoRecordset* pRecordset); // in DaoView.cpp


BOOL g_fOverwrite = false;
extern WORD ToolId[];

BOOL MyTrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack) {
  if ( g_Shell >= Win2000 ) {
    return _TrackMouseEvent(lpEventTrack);
  }
  else {
    HMODULE hUser32 = ::GetModuleHandle("User32.dll");
    if ( hUser32 ) {
      typedef WINUSERAPI BOOL (WINAPI pTrackMouseEvent(LPTRACKMOUSEEVENT lpEventTrack));
      pTrackMouseEvent* fTrackMouseEvent = (pTrackMouseEvent*)GetProcAddress(hUser32, _T("TrackMouseEvent"));
      if ( fTrackMouseEvent ) {
        return fTrackMouseEvent(lpEventTrack);
      }
    }
  }
  return false;
}


inline bool IsLeap(int y) {
  return y%4 == 0 && y%100 != 0 || y%400 == 0;
}
bool CanDateBack(CEdit* pEdit) {
  CString s;
  pEdit->GetWindowText(s);
  int nStartChar, nEndChar;
  pEdit->GetSel(nStartChar, nEndChar);
  if ( nEndChar==s.GetLength() )
    return true;
  return false;
}
/////////////////////////////////////////////////////////////////////////////
// COleDateTime read /write
COleDateTime ReadCOleDateTime(LPCSTR lpszData) {
  COleDateTime DateTime;
//  DateTime.ParseDateTime(lpszData);
  DateTime.ParseDateTime(lpszData, LOCALE_NOUSEROVERRIDE|VAR_DATEVALUEONLY, MAKELANGID(LANG_UKRAINIAN, SUBLANG_NEUTRAL));
  return DateTime;
}
void FormatCOleDateTime(CString& strData, COleDateTime DateTime, int len) {
  strData = "";
  if (DateTime.m_dt == 0) return;
  if (len == 8)
    strData = DateTime.Format("%d.%m.%y");
  else if(len == 5) // added these two
  	strData = DateTime.Format("%H:%M");
  else
    strData = DateTime.Format("%d.%m.%Y");
}

/////////////////////////////////////////////////////////////////////////////
// CEraEdit

CEraEdit::CEraEdit() {
  m_strFormat = _T("");
  m_bValid = true;  
  m_bFocus = false;
  m_bFirstUC = true;
  m_fReplaceQuote = true;
  m_fSelectAll = true;
  m_AltColor = 0;
}

CEraEdit::~CEraEdit() {
/************************************** : by VK at 20.01.2004 18:08:45 **\
  DestroyWindow();
\************************************** : by VK at 20.01.2004 18:08:49 **/
}

void CEraEdit::SetFormat(LPCTSTR szFormat) {
  if ( szFormat )
    m_strFormat = szFormat;
  else
    m_strFormat = _T("");
}
CString CEraEdit::GetText() {
  CString s;
  GetWindowText(s);
  return s;
}

bool CEraEdit::IsEmpty() {
  return IsEmptyText( GetText() );
}

void CEraEdit::ClearSelection() {
  int nStartChar, nEndChar, minPos;
  GetSel(nStartChar, nEndChar);
  minPos = min(nStartChar, nEndChar);
  SetSel(minPos, minPos);
}
void CEraEdit:: SetSelection() {
  if ( m_fSelectAll ) {
    if ( GetAsyncKeyState(VK_LBUTTON)<0 )
      return;
    if ( GetKeyState(VK_SHIFT) >=0 && GetKeyState(VK_CONTROL) >=0 ) {
      SetSel(0, -1);
    }
  }

}

UINT CEraEdit::MakeFirstUC(UINT nChar) {
  int x, y;
  GetCaretXY(x, y);
  if ( x==0 && m_bFirstUC) {
    nChar = (UINT)CyrUpper((TCHAR)nChar);
  }
  return nChar;
}
BOOL CEraEdit::OverwriteMode() {
  return g_fOverwrite;
}

POINT CEraEdit::GetCaretXY(int& x, int& y) {
  CPoint p = GetCaretPos();
  int iPos = CharFromPos(p);
  x = LOWORD(iPos);
  y = HIWORD(iPos);
  return p;
}

void CEraEdit::OnCharDriver(WPARAM& wParam, LPARAM& lParam) {
  char szMsgBuf[128];
  switch( (TCHAR)wParam ) {
    case '"': // Кавычки будем менять на нормальный апостроф, т.к. апостроф вводить неудобно.
      if ( m_fReplaceQuote )
        wParam = (WPARAM)'\'';
      break;
    case '`': // (ASCII 96 (0x60)) Хотят апостроф? На кой тогда вводить этот Grave Accent?
      wParam = (WPARAM)'\'';
      break;
    case 'Ё':   case 'ё':
    case 'Ы':   case 'ы':
    case 'Э':   case 'э':
    case 'Ъ':   case 'ъ':
      {
#ifdef _STRCPY_S
        sprintf_s(szMsgBuf, sizeof(szMsgBuf), "Російська мова, літера \"%c\".", (TCHAR)wParam);
#else
        sprintf(szMsgBuf, "Російська мова, літера \"%c\".", (TCHAR)wParam);
#endif
        AfxGetMainWnd()->SendMessage(WM_EM_MESSAGE, EM_RUSSIAN, (LPARAM)szMsgBuf);
      }
      break;
    default:
      if ( ('A' <= (TCHAR)wParam && (TCHAR)wParam <= 'Z') ||
           ('a' <= (TCHAR)wParam && (TCHAR)wParam <= 'z') ) {
#ifdef _STRCPY_S
         sprintf_s(szMsgBuf, sizeof(szMsgBuf), "Англійська мова, літера \"%c\".", (TCHAR)wParam);
#else
         sprintf(szMsgBuf, "Англійська мова, літера \"%c\".", (TCHAR)wParam);
#endif
        AfxGetMainWnd()->SendMessage(WM_EM_MESSAGE, EM_ENGLISH, (LPARAM)szMsgBuf);
      }
      break;
/*
    От этого отказались. Иногда нужно вводить фамилии, имена и т.п. на русском языке.

    case 'ё': wParam = (BYTE)'ґ'; break;
    case 'Ё': wParam = (BYTE)'Ґ'; break;
    case 'Ы': wParam = (BYTE)'І'; break;
    case 'ы': wParam = (BYTE)'і'; break;
    case 'Э': wParam = (BYTE)'Є'; break;
    case 'э': wParam = (BYTE)'є'; break;
*/
  }
  if ( !isdigit((TCHAR)wParam) ) {
    if ( GetStyle() & ES_NUMBER ) { // Можно вводить только цифры!
      AfxGetMainWnd()->SendMessage(WM_EM_MESSAGE, EM_WARNING, (LPARAM)"У цей елемент можна вводити тільки цифри.");
    }
  }
}

IMPLEMENT_DYNAMIC(CEraEdit, CEdit)

BEGIN_MESSAGE_MAP(CEraEdit, CEdit)
	//{{AFX_MSG_MAP(CEraEdit)
  ON_WM_CHAR()
//  ON_WM_CTLCOLOR_REFLECT()
  ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraEdit message handlers
/////////////////
BOOL CEraEdit::OnEraseBkgnd(CDC * pDC) {
  if (FALSE==m_bFocus ) {
    CRect rParent, r;
    CWnd* pParent = GetParent();
    if ( !pParent->IsKindOf(RUNTIME_CLASS(CDialog)) ) {
      pParent = pParent->GetParent();
    }

    if ( pParent ) {
      GetClientRect(&r);
      GradientEraseBkgnd(this, pParent, pDC, r);
      //EraseBkgndForDlgControl(this, pDC, r);
      pDC->SetBkMode(TRANSPARENT);
      return TRUE;
    }
  }
  return CEdit::OnEraseBkgnd(pDC);
}

void CEraEdit::OnPaint() {
	CPaintDC dc(this); // device context for painting
  if(m_bFocus /*|| !IsWindowEnabled()*/) {
    CEraEdit::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
  }
  else {
    CString sText;
    CRect rc;
    GetWindowText(sText);
    GetClientRect(&rc);
    dc.SetBkMode(TRANSPARENT);
    OnEraseBkgnd(&dc);
    if ( m_strFormat.Left(12).Compare(_T("dd mmmm yyyy"))==0) {
      COleDateTime odt = ReadCOleDateTime(sText);
      if ( odt.m_status==COleDateTime::valid ) {
        sText.Format(_T("%02d %s %04d"),
                     odt.GetDay(),
                     ::GetMonth(odt.GetMonth()),
                     odt.GetYear());
        if ( IsWindowEnabled() ) {
          dc.SetTextColor(m_Properties.GetForeColor());
        }
        else {
          dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
        }
      }
      CFont* pFont = GetFont();
      CFont* pOldFont = dc.SelectObject(pFont);
      dc.DrawText(sText, &rc, DT_LEFT|DT_VCENTER/*|DT_NOCLIP*/);
      dc.SelectObject(pOldFont);
    }
    else {
      COLORREF clrText = IsWindowEnabled() ? m_Properties.GetForeColor() : GetSysColor(COLOR_GRAYTEXT);
      dc.SetTextColor(clrText);
      CFont* pFont = GetFont();
      CFont* pOldFont = dc.SelectObject(pFont);
      /************************************** : by VK at 23/07/2007 08:07:36 **\
      rc.DeflateRect(1, 1);
      \************************************** : by VK at 23/07/2007 08:07:38 **/
      if ( false==GetParent()->IsKindOf(RUNTIME_CLASS(CComboBox)) ) {
        rc.DeflateRect(1, 1);
      }
      UINT nFormat = DT_LEFT|DT_EDITCONTROL;
      DWORD lStyle = GetStyle();
      if ( lStyle & ES_CENTER     ) nFormat |= DT_CENTER;
      if ( lStyle & ES_RIGHT      ) nFormat |= DT_RIGHT;
      if ( lStyle & ES_MULTILINE  ) {
        int Line = GetFirstVisibleLine();
        if ( Line > 0 ) {
          int offs = LineIndex(Line);
          sText = sText.Mid(offs);
        }
        //dc.DrawText(sText, &rc, nFormat|DT_CALCRECT);
        nFormat |= DT_WORDBREAK;
      }
      else {
        nFormat |= DT_SINGLELINE;
      }
      //rc.left++;
      //rc.top++;
      //rc.DeflateRect(1,1,1,1);
      dc.DrawText(sText, &rc, nFormat);
      if ( false==m_szAltText.IsEmpty() ) {
        CRect rcWidth = rc;
        dc.DrawText(sText, &rcWidth, DT_CALCRECT|nFormat);
        if ( rcWidth.Width()+8 < rc.Width() ) {
          rc.left += rcWidth.Width()+8;
          if ( m_AltColor ) {
            dc.SetTextColor(m_AltColor);
          }
          dc.DrawText(m_szAltText, &rc, nFormat);
          //dc.TextOut(
        }
      }
      dc.SelectObject(pOldFont);
    }
  }
	// Do not call CEdit::OnPaint() for painting messages
}

void CEraEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	if ( OverwriteMode() ) {
    if ( isprint(nChar) ) {
      int startPos, endPos;
      GetSel(startPos, endPos);
      if ( startPos==endPos )
        SetSel(startPos, endPos+1);
    }
  }
  CEdit::OnChar(nChar, nRepCnt, nFlags);
}
void CEraEdit::OnContextMenu(CWnd* pWnd, CPoint point) {
	// TODO: Add your message handler code here
//  UNREFERENCED_PARAMETER(pWnd);
//  CEdit::OnContextMenu(pWnd, point);
//  return;
	if(point.x==-1 && point.y==-1)
	{
		CRect rect;
		GetWindowRect(rect);

		point = rect.TopLeft()+CPoint(10,10);
	}
	SetFocus();


	CNewMenu menu;
	menu.CreatePopupMenu();
	menu.InsertMenu(0, MF_BYPOSITION , ID_EDIT_UNDO,          _T("Відмінити"));
	menu.InsertMenu(1, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(2, MF_BYPOSITION , ID_EDIT_COPY,          _T("Копі&ювати"));
	menu.InsertMenu(2, MF_BYPOSITION , ID_EDIT_CUT,           _T("Вирі&зати"));
	menu.InsertMenu(4, MF_BYPOSITION , ID_EDIT_CLEAR,         _T("Ви&далити"));
	menu.InsertMenu(5, MF_BYPOSITION , ID_EDIT_PASTE,         _T("В&ставити"));
	menu.InsertMenu(6, MF_BYPOSITION|MF_SEPARATOR);
	menu.InsertMenu(7, MF_BYPOSITION , ID_EDIT_SELECT_ALL,    _T("Вид&ілити все"));

  menu.SetMenuTitle(_T("Редагування"),MFT_GRADIENT|MFT_SIDE_TITLE|MFT_LINE);
  menu.LoadToolBar(ToolId,RGB(192,192,192)); 

  int nPos = menu.TrackPopupMenu(TPM_NONOTIFY|TPM_RETURNCMD|TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, point.x, point.y, this);
  switch(nPos) {
    case ID_EDIT_UNDO:        Undo();       break;
    case ID_EDIT_COPY:        Copy();       break;
    case ID_EDIT_CUT:         Cut();        break;
    case ID_EDIT_CLEAR:       Clear();      break;
    case ID_EDIT_PASTE:       Paste();      break;
    case ID_EDIT_SELECT_ALL:  SetSel(0,-1); break;
  }
}

BOOL CEraEdit::DestroyWindow() {
	// TODO: Add your specialized code here and/or call the base class
  Detach();	
	return CEdit::DestroyWindow();
}

LRESULT CEraEdit::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	// TODO: Add your specialized code here and/or call the base class
  switch(message) {
    case WM_KILLFOCUS:
  	  m_bFocus = false;
      SetSel(-1, 0);
      Invalidate();           // invalidate client area
      break;
    case WM_SETFOCUS:
  	  m_bFocus = true;
      Invalidate();           // invalidate client area
      SetSelection();
      break;
  }
	return CEdit::DefWindowProc(message, wParam, lParam);
}

BOOL CEraEdit::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
  switch ( pMsg->message ) {
    case WM_KEYDOWN:
      if ( VK_RETURN==pMsg->wParam && GetKeyState(VK_CONTROL)>=0 ) {
        if ( IsKindOf(RUNTIME_CLASS(CComboEdit)) ) {
          CComboBox* pCombo = (CComboBox*)GetParent();
          CComboBox* pParentCombo;
          if ( pCombo && (pParentCombo=(CComboBox*)pCombo->GetParent())!=NULL ) {
            if ( pParentCombo->IsKindOf(RUNTIME_CLASS(CToolBar)) ) {
              int nItem = pCombo->GetCurSel();
              if ( CB_ERR != nItem ) {
                pParentCombo->PostMessage(WM_COMMAND, MAKEWPARAM(pCombo->GetDlgCtrlID(), CBN_SELENDOK), (LPARAM)pCombo->m_hWnd);
                return TRUE;
              }
            }
          }
        }
        pMsg->wParam = VK_TAB;
      }
      else if ( VK_BACK==pMsg->wParam ) {
        if ( IsKindOf(RUNTIME_CLASS(CEraDateEdit)) ) {
          if ( CanDateBack(this) )
            break;
          return TRUE;
        }
        if ( GetKeyState(VK_CONTROL) < 0 ) {
          CString szText;
          GetWindowText(szText);
          CPoint p = GetCaretPos();
          int nPos = CharFromPos(p);
          int nCharIndex = LOWORD(nPos) - 1;
          int nLineIndex = HIWORD(nPos);

          if ( szText.GetLength() == 1 ) {
            SetWindowText(_T(""));
            SetSel(0, 0);
            return true;
          }
          
          
          if ( nCharIndex > 0 && szText.GetLength() >= nCharIndex ) {
            TCHAR c = szText[nCharIndex];
            if ( IsDelim(c) ) {
              while ( nCharIndex > 0 && szText.GetLength() >= nCharIndex && IsDelim(c)  ) {
                szText.Delete(nCharIndex, 1);
                nCharIndex--;
                c = szText[nCharIndex];
              }
            }
            else {
              while ( nCharIndex > 0 && szText.GetLength() >= nCharIndex && false==IsDelim(c) ) {
                szText.Delete(nCharIndex, 1);
                nCharIndex--;
                c = szText[nCharIndex];
              }
            }
            nCharIndex++;
          }
          SetWindowText(szText);
          // p = PosFromChar( MAKEWPARAM(LOWORD(nCharIndex), HIWORD(nLineIndex)) );
          // SetCaretPos(p);
          SetSel(nCharIndex, nCharIndex);
          return true;
        }
      }
      break;
    case WM_CHAR:
      OnCharDriver(pMsg->wParam, pMsg->lParam);
      if ( IsKindOf(RUNTIME_CLASS(CEraNameEdit)) || GetParent()->IsKindOf(RUNTIME_CLASS(CEraNameComboBox)) ) {
        int nStartChar, nEndChar;
        GetSel(nStartChar, nEndChar);
        if ( 0==nStartChar && 0==nEndChar ) {
          if ( IsCyrLower(TCHAR(pMsg->wParam)) )
            pMsg->wParam = (WPARAM)CyrUpper( TCHAR(pMsg->wParam) );
        }
      }
      break;
  }
	return CEdit::PreTranslateMessage(pMsg);
}

/////////////////////////////////////////////////////////////////////////////
// DDX for mask control
void AFXAPI DDX_TextForEraDate(CDataExchange* pDX, int nIDC, COleDateTime& value) {
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate) {
		int nLen = ::GetWindowTextLength(hWndCtrl);
		CString strTemp;

		::GetWindowText(hWndCtrl, strTemp.GetBufferSetLength(nLen), nLen+1);
		strTemp.ReleaseBuffer();

    //if (!value.ParseDateTime(strTemp), /*LOCALE_NOUSEROVERRIDE|*/VAR_DATEVALUEONLY, MAKELANGID(LANG_UKRAINIAN, SUBLANG_NEUTRAL))  // throws exception
		if (!value.ParseDateTime(strTemp), /*LOCALE_NOUSEROVERRIDE|*/VAR_DATEVALUEONLY, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_UK))  // throws exception
		{
			// Can't convert string to datetime
			AfxMessageBox(AFX_IDP_PARSE_DATETIME);
			pDX->Fail();    // throws exception
		}
	}
	else
	{
		CString strTemp = value.Format();
		AfxSetWindowText(hWndCtrl, strTemp);
	}
}
void AFXAPI DDX_FieldTextEraDate(CDataExchange* pDX, int nIDC, COleDateTime& value, CDaoRecordset* pRecordset) {
	if (!AfxFieldText(pDX, nIDC, &value, pRecordset))
		DDX_TextForEraDate(pDX, nIDC, value);
}


void AFXAPI DDX_OleDate(CDataExchange* pDX, int nIDC, CEraDateEdit& rControl, COleDateTime& Date)
{
  DDX_Control(pDX, nIDC, (CWnd&)rControl);
  if (!pDX->m_bSaveAndValidate)
    rControl.SetDate(Date);
  else {
    if ( !((DATE)0==Date.m_dt && rControl.IsEmpty()) )
      Date = rControl.GetDate();
  }
}
/////////////////////////////////////////////////////////////////////////////
// CEraMaskEdit class
IMPLEMENT_DYNAMIC(CEraMaskEdit, CEraEdit)

BEGIN_MESSAGE_MAP(CEraMaskEdit, CEraEdit)
  //{{AFX_MSG_MAP(CEraMaskEdit)
  ON_WM_CHAR()
  ON_WM_KEYDOWN()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEraMaskEdit::CEraMaskEdit() {
  m_bUseMask = m_isdate = m_bMaskKeyInProgress = false;
  m_strMask = _T("");
  m_strLiteral = _T("");
  m_strValid = _T("");
}

bool CEraMaskEdit::InsertMode() {
  return false;
}

void CEraMaskEdit::SetMask(LPCSTR lpMask, LPCSTR lpLiteral, LPCSTR lpValid)
{
  m_bUseMask = FALSE;
  if (lpMask == NULL) return;
  m_strMask = lpMask;
  if (m_strMask.IsEmpty()) return;
  if (lpLiteral != NULL)
  {
    m_strLiteral = lpLiteral;
    if (m_strLiteral.GetLength() != m_strMask.GetLength())
      m_strLiteral.Empty();
  }
  else
    m_strLiteral.Empty();
  if (lpValid != NULL)
    m_strValid = lpValid;
  else
    m_strValid.Empty();
  m_bUseMask = TRUE;
}

void CEraMaskEdit::SendChar(UINT nChar) {
  m_bMaskKeyInProgress = TRUE;
/*
  #ifdef WIN32
    AfxCallWndProc(this, m_hWnd, WM_CHAR, nChar, 1);
  #else
    SendMessage(WM_CHAR, nChar, 1);
  #endif
*/
  AfxCallWndProc(this, m_hWnd, WM_CHAR, nChar, 1);
  m_bMaskKeyInProgress = FALSE;
}
int CEraMaskEdit::isprint(int c) {
  if ( IsCyrChar(c) )
    return c;
  return ::isprint(c);
}

void CEraMaskEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
  if (!m_bMaskKeyInProgress)
    if (!CheckChar(nChar)) return;

  if (m_bUseMask)  {
    if (isprint(nChar)) {
      // si un masque existe, on est en insert mode
      int startPos, endPos;
      GetSel(startPos, endPos);
      SetSel(startPos, endPos+1);
      Clear();
      /************************************** : by VK at 27.01.2003 23:19:53 **\
      if ( m_str.GetLength() < endPos )
	      m_str.SetAt(endPos, nChar); // added this
      else
        m_str += nChar;
      \************************************** : by VK at 27.01.2003 23:19:56 **/
      if ( m_str.GetLength() <= endPos )
        m_str += (TCHAR)nChar;
      else
	      m_str.SetAt(endPos, nChar); // added this
    }
  }
  CEraEdit::OnChar(nChar, nRepCnt, nFlags);

  if (!m_bMaskKeyInProgress && m_bUseMask && !m_strLiteral.IsEmpty())  {
    int startPos, endPos;
	  GetSel(startPos, endPos);
  	// make sure the string is not longer than the mask
	  if (endPos < m_strLiteral.GetLength()) {
	    UINT c = m_strLiteral.GetAt(endPos);
	    if (c != '_') { // Debuged by Sang-il, Lee T.T
		    SetSel(endPos+1,endPos+1);
	    }
	  }
  }

/**************************************** 15.05.2002 23:50:33 by VK
  switch ( nChar ) {
    case VK_BACK:
      CEraEdit::OnChar(nChar, nRepCnt, nFlags);
      return;
  }

  if (!m_bMaskKeyInProgress)
    if (!CheckChar(nChar)) return;

  if (m_bUseMask) {
    if (isprint(nChar))  {
      // si un masque existe, on est en insert mode
      int startPos, endPos;
      GetSel(startPos, endPos);
      SetSel(startPos, endPos+1);
      Clear();
      if ( m_str.GetLength() > endPos )
  	    m_str.SetAt(endPos, nChar); // added this
      else
        m_str += nChar;
    }
    else if (nChar == VK_BACK) return;
  }
  CEraEdit::OnChar(nChar, nRepCnt, nFlags);

  if (!m_bMaskKeyInProgress && m_bUseMask && !m_strLiteral.IsEmpty()) {
    int startPos, endPos;
    GetSel(startPos, endPos);
    // make sure the string is not longer than the mask
    if (endPos < m_strLiteral.GetLength()) {
      UINT c = m_strLiteral.GetAt(endPos);
      if (c != '_') SendChar(c);
    }
  }
***************************************** 15.05.2002 23:50:38 by VK */
}

BOOL CEraMaskEdit::CheckChar(UINT& nChar) {
  UINT c;

  // do not use mask
  if (!m_bUseMask) return TRUE;

  // control character, OK
  if (!isprint(nChar)) return TRUE;

  // unselect all selections, if any
  int startPos, endPos;
  GetSel(startPos, endPos);
  SetSel(-1, 0);
  SetSel(startPos, startPos);

  // check the key against the mask
  GetSel(startPos, endPos);

  // make sure the string is not longer than the mask
  if (endPos >= m_strMask.GetLength())  {
    MessageBeep((UINT)-1);
    CString s;
    s.Format(_T("Відмова введення: в цей елемент можна вводити лише %d символів."), m_strMask.GetLength());
    AfxGetMainWnd()->SendMessage(WM_EM_MESSAGE, EM_WARNING, (LPARAM)(LPCTSTR)s);
    return FALSE;
  }

  // check to see if a literal is in this position
  c = '_';
  if (!m_strLiteral.IsEmpty())
    c = m_strLiteral.GetAt(endPos);

  if (c != '_') {
    SendChar(c);
    GetSel(startPos, endPos);
  }

  // check the valid string character
  if (m_strValid.Find(nChar) != -1) return TRUE;

  // check the key against the mask
  c = m_strMask.GetAt(endPos);
  BOOL doit = TRUE;
  switch (c) {
    case '0':	{	// digit only //completely changed this
  		  BOOL doit = TRUE;
  	  	if (isdigit(nChar)) {
	  	  	if(m_isdate) {
		  	  	if(endPos == 0)	{
			  	  	if(nChar > '3')
				  	  	doit = FALSE;
				    }
    				else if(endPos == 1) {
	    				if(m_str.GetLength() && m_str.GetAt(0) == '3')	{
		    				if(nChar > '1')
			    				doit = FALSE;
				    	}
				    }
    				else if (endPos == 3)	{
	    				if(nChar > '1')
		    				doit = FALSE;
			    	}
  			  	else if (endPos == 4) {
	  			  	if (m_str.GetLength()>3 && m_str.GetAt(3) == '1') {
		  			  	if(nChar > '2')
			  			  	doit = FALSE;
				  	  }
				    }
            else if (6==startPos /*&& 6==endPos*/) {  // 01.01.2004 // first digit of year part
              CString sText = GetText();
              if ( '0'==nChar && sText.GetLength()==10 ) {  // full date?
                SetSel(8, 9);
                Clear();
                SetSel(6, 7);
              }
            }
			    }
  			  else {
	  			  if(endPos == 0) {
  	  				if(nChar > '2')
	  	  				doit = FALSE;
		  	  	}
			  	  if(endPos == 1)	{
  				  	if(m_str.GetLength() && m_str.GetAt(0) == '2') 	{
    						if(nChar > '3')
	    						doit = FALSE;
		    			}
			    	}
				    if(endPos == 3)	{
  					  if(nChar > '5')
	  					  doit = FALSE;
		  		  }
			    }
          return doit;
		    }
      }
      break;
    case '9':	// digit or space
      if (isdigit(nChar)) return TRUE;
      if (nChar != VK_SPACE) return TRUE;
      break;
    case '#':	// digit or space or '+' or '-'
      if (isdigit(nChar)) return TRUE;
      if (nChar == VK_SPACE || nChar == VK_ADD || nChar == VK_SUBTRACT) return TRUE;
      break;
    case 'L':	 // alpha only
      if (isalpha(nChar)) return TRUE;
      break;
    case '?':	// alpha or space
      if (isalpha(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    case 'A':	// alpha numeric only
      if (isalnum(nChar)) return TRUE;
      break;
    case 'a':	// alpha numeric or space
      if (isalnum(nChar)) return TRUE;
      if (nChar == VK_SPACE) return TRUE;
      break;
    case 'U': // Cyrillic (and ASCII) upper char
      if ( m_strFormat==_T("SERIA") ) {
        switch ( nChar ) {
          case UCHAR('i'): case UCHAR('і'): case UCHAR('І'):
            SendChar('I');
            return FALSE;
          case UCHAR('у'): case UCHAR('У'):
            SendChar('V');
            return FALSE;
          case UCHAR('п'): case UCHAR('П'):
            SendChar('I'); SendChar('I');
            return FALSE;
          case UCHAR('ш'): case UCHAR('Ш'):
            SendChar('I'); SendChar('I'); SendChar('I');
            return FALSE;
        }
      }
      if ( IsCyrChar(nChar) ) {
        if ( IsCyrLower(nChar) ) {
          SendChar(CyrUpper(nChar));
          return FALSE;
        }
        return TRUE;
      }
      else {
        if ( isalpha(nChar) ) {
          if ( islower(nChar) ) {
            SendChar( toupper(nChar) );
            return FALSE;
          }
        }
      }
      return TRUE;
    case 'u': // Cyrillic (and ASCII) char, ' ', '\-', or '\''
      switch ( nChar ) {
        case ' ': case '-': case '\'': return TRUE;
        case '"': SendChar('\'');      return FALSE;
        default:                       return IsCyrChar(nChar);
      }
      break;
    case '&':	// all print character only
      if (isprint(nChar)) return TRUE;
      break;
  }
  MessageBeep((UINT)-1);
  return FALSE;
}

void CEraMaskEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
  // si un masque existe, tester les touches spйciales
  if (m_bUseMask) {
    switch (nChar) {
      // case VK_DELETE:
      case VK_INSERT:
        return;
    }
  }
  CEraEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CEraNameEdit class

IMPLEMENT_DYNAMIC(CEraNameEdit, CEraEdit)
BEGIN_MESSAGE_MAP(CEraNameEdit, CEraEdit)
  //{{AFX_MSG_MAP(CEraNameEdit)
  ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_KILLFOCUS, OnKillfocus)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEraNameEdit::CEraNameEdit() {
  m_fReplaceQuote = true;
}
void CEraNameEdit::OnKillfocus() {
	CCyrString s, sCanonicalName;
  GetWindowText(s);
  sCanonicalName = s;
  sCanonicalName.MakeCanonical();
  if ( s != sCanonicalName )
    SetWindowText(sCanonicalName);
}

/////////////////////////////////////////////////////////////////////////////
// CEraDateEdit class

IMPLEMENT_DYNAMIC(CEraDateEdit, CEraMaskEdit)

BEGIN_MESSAGE_MAP(CEraDateEdit, CEraMaskEdit)
  //{{AFX_MSG_MAP(CEraDateEdit)
	ON_WM_PAINT()
  ON_WM_ERASEBKGND()
  ON_WM_SETFOCUS()
  ON_WM_KILLFOCUS()
  ON_WM_KEYDOWN()
  ON_WM_KEYUP()
  ON_WM_SYSKEYDOWN()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_WM_DESTROY()
  ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
  ON_MESSAGE(WM_CLEAR, OnClear)
  ON_MESSAGE(WM_CUT, OnCut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEraDateEdit::CEraDateEdit() {
  m_bUseMask = true;
  m_isdate   = true;
  m_strMask = _T("00.00.0000");
  m_strFormat = _T("dd mmmm yyyy");
  m_strLiteral = _T("__.__.____");

  m_dwBtnStyle = DFCS_SCROLLDOWN;
  m_fDropDown = false;
  m_fCalendarOn = false;
  m_fOffByBtn = false;
  m_pCalendarWnd = NULL;

/************************************** : by VK at 07.05.2005 5:49:23 **\
  RegisterWindowClass();
\************************************** : by VK at 07.05.2005 5:49:24 **/
}

BOOL CEraDateEdit::RegisterWindowClass() {
	WNDCLASS wndcls;
	HINSTANCE hInst;
	hInst = AfxGetInstanceHandle();

	ASSERT( hInst != 0 );

  if( !(::GetClassInfo(hInst, ERADATEEDIT_CLASSNAME, &wndcls)) ) {
    wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc      = ::DefWindowProc;
    wndcls.cbClsExtra       = 0;
		wndcls.cbWndExtra		    = 0;
    wndcls.hInstance        = hInst;
    wndcls.hIcon            = NULL;
    wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
    wndcls.hbrBackground    = (HBRUSH) (COLOR_WINDOW);
    wndcls.lpszMenuName     = NULL;
    wndcls.lpszClassName    = ERADATEEDIT_CLASSNAME;

    if( !AfxRegisterClass(&wndcls) ) {
      AfxThrowResourceException();
      return FALSE;
    }
  }
  return TRUE;
}

void CEraDateEdit::SetDate(COleDateTime& Date) {
  CString strText;
  FormatCOleDateTime(strText, Date, 10);
  SetWindowText(strText);
}
void CEraDateEdit::SetDate(SYSTEMTIME& st) {
  COleDateTime Date(st.wYear, st.wMonth, st.wDay, 0, 0, 0);
  if ( COleDateTime::valid == Date.GetStatus())
    SetDate( Date);
}

COleDateTime CEraDateEdit::GetDate() {
  CString strText;
  GetWindowText(strText);
  return ReadCOleDateTime(strText);
}

CString CEraDateEdit::GetDDMMYYYY() {
  CString s;
  COleDateTime odt = GetDate();
  if ( COleDateTime::valid==odt.GetStatus() && odt.m_dt != (DATE)0 )
    s.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear() );
  return s;
}
int CEraDateEdit::GetDatePart() {
  COleDateTime odt = GetDate();
  if ( odt.GetStatus() != COleDateTime::valid )
    return -1;
  int nStartChar, nEndChar;
  GetSel(nStartChar, nEndChar);
  if ( 0 <= nStartChar && nStartChar <= 2 )
    return 0;
  if ( 3 <= nStartChar && nStartChar <= 5 )
    return 1;
  return 2;
}
void CEraDateEdit::CorrectionDate(COleDateTime& odt, int y, int m, int d) {
  if ( m > 12 ) m = 1;
  if ( m < 1  ) m = 12;
  if ( d > 28 ) {
    switch(m) {
      case 2:
        d = IsLeap(y) ? 29 : 28;
        break;
      case 4: case 6: case 9: case 11:
        if ( d > 30 )
          d = 30;
        break;
    }
  }
  odt.SetDate(y, m, d);
}
void CEraDateEdit::OnDayUp() {
  COleDateTime odt = GetDate();
  odt += COleDateTimeSpan(1, 0, 0, 0);
  SetDate(odt);
  SetSel(0, 2, TRUE);
}
void CEraDateEdit::OnMonthUp() {
  COleDateTime odt = GetDate();
  int y = odt.GetYear();
  int m = odt.GetMonth() + 1;
  int d = odt.GetDay();
  CorrectionDate(odt, y, m, d);
  SetDate(odt);
  SetSel(3, 5, TRUE);
}
void CEraDateEdit::OnYearUp() {
  COleDateTime odt = GetDate();
  int y = odt.GetYear()  + 1;
  int m = odt.GetMonth();
  int d = odt.GetDay();
  CorrectionDate(odt, y, m, d);
  SetDate(odt);
  SetSel(6, -1, TRUE);
}
void CEraDateEdit::OnDateUp() {
  switch( GetDatePart() ) {
    case 0: OnDayUp();      break;
    case 1: OnMonthUp();    break;
    case 2: OnYearUp();     break;
  }
}
void CEraDateEdit::OnDayDown() {
  COleDateTime odt = GetDate();
  odt -= COleDateTimeSpan(1, 0, 0, 0);
  SetDate(odt);
  SetSel(0, 2, TRUE);
}
void CEraDateEdit::OnMonthDown() {
  COleDateTime odt = GetDate();
  int y = odt.GetYear();
  int m = odt.GetMonth() - 1;
  int d = odt.GetDay();
  CorrectionDate(odt, y, m, d);
  SetDate(odt);
  SetSel(3, 5, TRUE);
}
void CEraDateEdit::OnYearDown() {
  COleDateTime odt = GetDate();
  int y = odt.GetYear()  - 1;
  int m = odt.GetMonth();
  int d = odt.GetDay();
  CorrectionDate(odt, y, m, d);
  SetDate(odt);
  SetSel(6, -1, TRUE);
}
void CEraDateEdit::OnDateDown() {
  switch( GetDatePart() ) {
    case 0: OnDayDown();      break;
    case 1: OnMonthDown();    break;
    case 2: OnYearDown();     break;
  }
}
bool CEraDateEdit::OnLeft() {
  if ( GetKeyState(VK_SHIFT) < 0 )
    return false;
  int nStartChar, nEndChar;
  GetSel(nStartChar, nEndChar);
  if ( nStartChar==nEndChar )
    return false;
  switch( GetDatePart() ) {
    case 1: // go to day part
      SetSel(0, 2);
      break;
    case 2: // go to month part
      SetSel(3, 5);
      break;
    default:
      return false;
  }
  return true;
}
bool CEraDateEdit::OnRight() {
  if ( GetKeyState(VK_SHIFT) < 0 )
    return false;
  int nStartChar, nEndChar;
  GetSel(nStartChar, nEndChar);
  if ( nStartChar==nEndChar )
    return false;
  switch( GetDatePart() ) {
    case 0: // go to month part
      SetSel(3, 5);
      break;
    case 1: // go to year part
      SetSel(6, 10);
      break;
    default:
      return false;
  }
  return true;
}
void CEraDateEdit::SetDropBtnRect() {
	if ( GetSafeHwnd() ) {
    CRect r;
    GetClientRect(&r);
    r.left = r.right - ::GetSystemMetrics(SM_CXHSCROLL);
    m_rcDropButton = r;
    //m_rcDropButton.InflateRect(1, 1);
  }
}
void CEraDateEdit::SetSelection() {
  CString s = GetText();
  if ( s.GetLength()>=2 ) {
    SetSel(0, 2);
  }
}
void CEraDateEdit::ShowCalendar() {
  if ( NULL==m_pCalendarWnd ||  m_pCalendarWnd->GetSafeHwnd()==NULL ) {
    DWORD dwStyle = WS_POPUP|WS_VISIBLE|WS_CLIPSIBLINGS|WS_BORDER;
    DWORD dwExStyle = 0;///*WS_EX_TOOLWINDOW | */WS_EX_TOPMOST;
    m_pCalendarWnd = new CEraMonthCalCtrl();
    m_pCalendarWnd->CreateEx(dwExStyle, _T("SysMonthCal32"),  _T("Calendar"), dwStyle, 0,0,0,0, GetParent()->m_hWnd, 0);
    //return;
  }
  CRect r;
  GetWindowRect(&r);
  CRect clnRect;
  COleDateTime odt = GetDate();
  if ( COleDateTime::valid==odt.GetStatus() )
    m_pCalendarWnd->SetCurSel(odt);
  m_pCalendarWnd->SetOwner(this);
  m_pCalendarWnd->GetMinReqRect(&clnRect);
  m_pCalendarWnd->MoveWindow(r.left, r.bottom, clnRect.Width(), clnRect.Height());
  m_pCalendarWnd->ShowWindow(SW_SHOW);
  m_pCalendarWnd->SetFocus();
}
void CEraDateEdit::HideCalendar() {
  if ( NULL==m_pCalendarWnd ||  m_pCalendarWnd->GetSafeHwnd()==NULL )
    return;
  m_pCalendarWnd->ShowWindow(SW_HIDE);
  SetFocus();
  m_pCalendarWnd->DestroyWindow();
  delete m_pCalendarWnd;
  m_pCalendarWnd = NULL;
}
void CEraDateEdit::ShowHideCalendar() {
  m_fCalendarOn ^= 1;
  if ( m_fCalendarOn )
    ShowCalendar();
  else
    HideCalendar();
}
void CEraDateEdit::OnCalendarKillFocus() {
  if ( GetAsyncKeyState(VK_LBUTTON) ) { // Left mouse button was pressed
    CRect rWnd;
    CPoint p;
    GetWindowRect(&rWnd);
    GetCursorPos(&p);
    if ( rWnd.PtInRect(p) ) {
      m_fOffByBtn = true;
    }
    else {
      m_fCalendarOn = false;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////
// CEraDateEdit message handlers
void CEraDateEdit::PreSubclassWindow() {
	// TODO: Add your specialized code here and/or call the base class
  SetDropBtnRect();
  if ( IsWindow(m_hWnd) ) {
    ModifyStyle(0, WS_CLIPCHILDREN);
  }
	CEraMaskEdit::PreSubclassWindow();
}
void CEraDateEdit::DrawDropButton(CDC* pDC) {
  CRgn rgn;
  rgn.CreateRectRgn(m_rcDropButton.left,m_rcDropButton.top, m_rcDropButton.right, m_rcDropButton.bottom);
  pDC->SelectClipRgn(&rgn);
  HTHEME hTheme = NULL;
  BOOL bThemeActive = g_xpStyle.UseVisualStyles();
  if ( bThemeActive )
    hTheme = g_xpStyle.OpenThemeData( m_hWnd, L"COMBOBOX" );

  if ( hTheme ) {
    int nDropBtnThemeStyle = CBXS_NORMAL;
    if ( m_dwBtnStyle & DFCS_FLAT )
      nDropBtnThemeStyle = CBXS_HOT;
    if ( m_dwBtnStyle & DFCS_PUSHED )
      nDropBtnThemeStyle = CBXS_PRESSED;
    if ( GetStyle() & WS_DISABLED )
      nDropBtnThemeStyle = CBXS_DISABLED;
		  g_xpStyle.DrawThemeBackground( hTheme, pDC->m_hDC, CP_DROPDOWNBUTTON, nDropBtnThemeStyle, &m_rcDropButton, NULL);
  }
  else {
    pDC->DrawFrameControl(m_rcDropButton, DFC_SCROLL, m_dwBtnStyle);
  }
}
BOOL CEraDateEdit::OnEraseBkgnd(CDC * pDC) {
  CRect rParent, r;
  CWnd* pParent = GetParent();
  if ( !pParent->IsKindOf(RUNTIME_CLASS(CDialog)) ) {
    pParent = pParent->GetParent();
  }
  GetClientRect(&r);
  if ( pParent ) {
    r.right -= m_rcDropButton.Width();
    if (FALSE==m_bFocus ) {
      GradientEraseBkgnd(this, pParent, pDC, r);
      pDC->SetBkMode(TRANSPARENT);
    }
    else {
      COLORREF clr = GetSysColor(COLOR_WINDOW);
      pDC->FillSolidRect(&r, clr);
    }
    return TRUE;
  }
  return CEdit::OnEraseBkgnd(pDC);
}
void CEraDateEdit::OnPaint() {
	CPaintDC dc(this); // device context for painting
  SetDropBtnRect();
  dc.ExcludeClipRect(&m_rcDropButton);
	
	// TODO: Add your message handler code here
  CString sText;
  COleDateTime odt;
  GetWindowText(sText);
  //LANG_UKRAINIAN
  //(MAKELANGID(LANG_UKRAINIAN, SUBLANG_NEUTRAL))
  odt = ReadCOleDateTime(sText);

  BOOL bFocus = (GetFocus()==this);
  OnEraseBkgnd(&dc);
  if ( bFocus ) {
    sText.Format(_T("%02d.%02d.%04d"), odt.GetDay(), odt.GetMonth(), odt.GetYear());
    CEdit::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
  }
  else {
    if ( odt.GetStatus()==COleDateTime::valid ) {
      sText.Format(_T("%02d %s %04d"), odt.GetDay(), ::GetMonth(odt.GetMonth()), odt.GetYear());
      if ( false==IsWindowEnabled() ) {
        dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
      }
    }
    else {
      dc.SetTextColor(RGB(255,0,0));
    }
    

    CRect rcText;
    GetClientRect(&rcText);
    CFont* pFont = GetFont();
    CFont* pOldFont = dc.SelectObject(pFont);
    rcText.DeflateRect(1, 1);
#ifdef _ERA2XML
    dc.FillSolidRect(&rcText, GetSysColor(COLOR_WINDOW));
#endif
    dc.DrawText(sText, &rcText, DT_LEFT|DT_VCENTER);
    dc.SelectObject(pOldFont);
  }
  DrawDropButton(&dc);
	// Do not call CEdit::OnPaint() for painting messages
}
void CEraDateEdit::OnSetFocus(CWnd* pOldWnd) {
	CEraMaskEdit::OnSetFocus(pOldWnd);
	// TODO: Add your message handler code here
  InvalidateRect(NULL);
/************************************** : by VK at 14.05.2005 0:10:19 **\
  if ( m_pCalendarWnd && IsWindow(m_pCalendarWnd->m_hWnd) ) {
    if ( m_pCalendarWnd->GetOwner() != this ) {
      m_fCalendarOn = false;
      m_pCalendarWnd->SetOwner(this);
    }
  }
\************************************** : by VK at 14.05.2005 0:10:23 **/
}
void CEraDateEdit::OnKillFocus(CWnd* pNewWnd) {
  TRACKMOUSEEVENT tme;
  tme.cbSize = sizeof(tme);
  tme.dwFlags = TME_CANCEL|TME_LEAVE;
  tme.hwndTrack = m_hWnd;
  tme.dwHoverTime = HOVER_DEFAULT;
  MyTrackMouseEvent(&tme);

	CEdit::OnKillFocus(pNewWnd);
	// TODO: Add your message handler code here
  InvalidateRect(NULL);
}
void CEraDateEdit::OnDelete() {
  SetWindowText(_T(""));
  SetSel(0, 0);
}
void CEraDateEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	switch( nChar ) {
    case VK_DELETE:
      OnDelete();
      return;
    case VK_UP:
      OnDateUp();
      return;
    case VK_DOWN:
      OnDateDown();
      return;
    case VK_LEFT:
      if ( OnLeft() )
        return;
      break;
    case VK_RIGHT:
      if ( OnRight() )
        return;
      break;
    case VK_HOME :
    case VK_END  :
      break;
    case VK_F4:
      ShowCalendar();
      break;
    default:
      if ( !isdigit(nChar) ) {
        AfxGetMainWnd()->SendMessage(WM_EM_MESSAGE, EM_WARNING, (LPARAM)_T("Для визначення дати потрібно вводити лише цифри."));
      }
      break;
  }
	CEraMaskEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
void CEraDateEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
  CEraMaskEdit::OnKeyUp(nChar, nRepCnt, nFlags);
//  InvalidateRect(&m_rcDropButton);
  switch( nChar ) {
    case VK_BACK:
    case VK_DELETE:
      InvalidateRect(&m_rcDropButton);
      break;
  }
}
void CEraDateEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// TODO: Add your message handler code here and/or call default
	switch( nChar ) {
    case VK_DOWN:
      if ( GetKeyState(VK_MENU)<0 ) {
        ShowCalendar();
        return;
      }
      break;
  }
	CEraMaskEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CEraDateEdit::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  DWORD dwOldBtnStyle = m_dwBtnStyle;
  if ( m_rcDropButton.PtInRect(point) ) {
    SetCursor( ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)) );
    m_dwBtnStyle = DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT;
    m_fDropDown = true;
    SetFocus();
  }
  if ( dwOldBtnStyle != m_dwBtnStyle )
    InvalidateRect(&m_rcDropButton);
	CEdit::OnLButtonDown(nFlags, point);
}

void CEraDateEdit::OnLButtonUp(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  DWORD dwOldBtnStyle = m_dwBtnStyle;
	m_dwBtnStyle = DFCS_SCROLLDOWN;
  bool fShowCalendar = false;
  if ( m_fOffByBtn ) {
    m_fOffByBtn = false;
    HideCalendar();
    if ( dwOldBtnStyle != m_dwBtnStyle )
      InvalidateRect(&m_rcDropButton);
    m_fDropDown = false;
    m_fCalendarOn = false;
  }
  else {
    if ( m_fDropDown && m_rcDropButton.PtInRect(point) ) {
      //m_fCalendarOn = false;
      fShowCalendar = true;
    }
    m_fDropDown = false;
    if ( dwOldBtnStyle != m_dwBtnStyle )
      InvalidateRect(&m_rcDropButton);
    if ( fShowCalendar )
      ShowHideCalendar();
  }
	CEdit::OnLButtonUp(nFlags, point);
}

void CEraDateEdit::OnMouseMove(UINT nFlags, CPoint point) {
	// TODO: Add your message handler code here and/or call default
  CRect rc;
  GetClientRect(&rc);
  if ( rc.PtInRect(point) ) {
    TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(tme);
    tme.dwFlags = TME_LEAVE;
    tme.hwndTrack = m_hWnd;
    tme.dwHoverTime = HOVER_DEFAULT;
    MyTrackMouseEvent(&tme);
  }
  DWORD dwOldBtnStyle = m_dwBtnStyle;
  if ( m_rcDropButton.PtInRect(point) ) {
    SetCursor( ::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)) );
    if ( m_fDropDown && (MK_LBUTTON & nFlags) )
      m_dwBtnStyle = DFCS_SCROLLDOWN|DFCS_PUSHED|DFCS_FLAT;
    else
      m_dwBtnStyle = DFCS_SCROLLDOWN;
    m_dwBtnStyle |= DFCS_FLAT;
  }
  else {
      m_dwBtnStyle = DFCS_SCROLLDOWN;
  }
  if ( dwOldBtnStyle != m_dwBtnStyle )
    InvalidateRect(&m_rcDropButton);
	CEdit::OnMouseMove(nFlags, point);
}
void CEraDateEdit::OnDestroy() {
  HideCalendar();
  CEraMaskEdit::OnDestroy();
}

LRESULT CEraDateEdit::OnMouseLeave(WPARAM wParam, LPARAM lParam) {
  CPoint point;
  GetCursorPos(&point);
  ScreenToClient(&point);
  OnMouseMove(0, point);
  return 0L;
}
LRESULT CEraDateEdit::OnClear(WPARAM wParam, LPARAM lParam) {
  CEdit::DefWindowProc(WM_CLEAR, wParam, lParam);
  InvalidateRect(&m_rcDropButton);
  return 0L;
}
LRESULT CEraDateEdit::OnCut(WPARAM wParam, LPARAM lParam) {
  CEdit::DefWindowProc(WM_CUT, wParam, lParam);
  InvalidateRect(&m_rcDropButton);
  return 0L;
}

BOOL CEraDateEdit::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) {
	// TODO: Add your specialized code here and/or call the base class
  if ( m_pCalendarWnd && IsWindow(m_pCalendarWnd->m_hWnd) ) {
  	NMHDR* pnmhdr = (NMHDR*)lParam;
    if ( pnmhdr->hwndFrom == m_pCalendarWnd->m_hWnd ) {
      switch( pnmhdr->code ) {
        case NM_KILLFOCUS:
          OnCalendarKillFocus();
          break;
        case DTN_DATETIMECHANGE: {
            NMDATETIMECHANGE* pDateTimeChange =  (NMDATETIMECHANGE*)lParam;
            if ( pDateTimeChange->dwFlags == GDT_VALID ) {
              SetDate( pDateTimeChange->st );
            }
          }
          break;
      }
    }
  }
	return CEdit::OnNotify(wParam, lParam, pResult);
}

/////////////////////////////////////////////////////////////////////////////
// CEraSeriaEdit class
IMPLEMENT_DYNAMIC(CEraSeriaEdit, CEraMaskEdit)

BEGIN_MESSAGE_MAP(CEraSeriaEdit, CEraMaskEdit)
  //{{AFX_MSG_MAP(CEraSeriaEdit)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEraSeriaEdit::CEraSeriaEdit() {
  m_bUseMask = TRUE;
  m_strMask = CString(TCHAR('U'), 12);
  m_strFormat = _T("SERIA");
}
/////////////////////////////////////////////////////////////////////////////
// CEraNoticeEdit

CEraNoticeEdit::CEraNoticeEdit() {
}

CEraNoticeEdit::~CEraNoticeEdit() {
}

BEGIN_MESSAGE_MAP(CEraNoticeEdit, CEraEdit)
	//{{AFX_MSG_MAP(CEraNoticeEdit)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraNoticeEdit message handlers
void CEraNoticeEdit::OnContextMenu(CWnd* pWnd, CPoint point) {
	// TODO: Add your message handler code here
  CWnd* pParent = GetParent();
  if ( pParent )
    pParent->PostMessage(WM_CONTEXTMENU, (WPARAM)pWnd->m_hWnd, MAKELPARAM(point.x, point.y) );
}

/////////////////////////////////////////////////////////////////////////////
// CEraMoneyEdit
CEraMoneyEdit::CEraMoneyEdit() {
}

CEraMoneyEdit::~CEraMoneyEdit() {
}

BEGIN_MESSAGE_MAP(CEraMoneyEdit, CEraEdit)
	//{{AFX_MSG_MAP(CEraMoneyEdit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraMoneyEdit message handlers
void CEraMoneyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
  bool bDoProcess = false;
  switch( nChar ) {
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':  case '\b':
      bDoProcess = true; break;
    case ',': {
        CString sMoney;
        GetWindowText(sMoney);
        if ( sMoney.Find(TCHAR(','), 0) == -1 )
          bDoProcess = true;
      }
      break;
  }
  if ( bDoProcess )
	  CEraEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CEraEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
/************************************** : by VK at 17.02.2004 1:22:32 **\
	CFont* pFont = GetFont();
  if ( pFont ) {
    LOGFONT lf;
    pFont->GetLogFont(&lf);
    lf.lfWeight = FW_BOLD;

    CFont font;
    font.CreateFontIndirect(&lf);

    SetFont(&font);
  }
\************************************** : by VK at 17.02.2004 1:22:35 **/
	CEdit::PreSubclassWindow();
}
