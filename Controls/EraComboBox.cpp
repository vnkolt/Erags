// EraComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "EraComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <afxdao.h>			// MFC DAO database classes


/////////////////////////////////////////////////////////////////////////////
// CComboEdit
IMPLEMENT_DYNAMIC(CComboEdit, CEraEdit)
CComboEdit::CComboEdit()
           :m_bHighlighted(false), m_nPos(0), m_nStartAfter(-1) {
}

CComboEdit::~CComboEdit() {
}


BEGIN_MESSAGE_MAP(CComboEdit, CEraEdit)
	//{{AFX_MSG_MAP(CComboEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboEdit message handlers

// This is called when a WM_KEYDOWN message is passed to CAS.
// OnKeyDown is needed because some special keys (like DELETE) 
// and the cursor keys are not trapped with a WM_CHAR message.
// After this function has been called, OnChar will be called
void CComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// Call base class implementation to ensure that key gets
	// handled as normal before I do anything dodgy with it
	CEraEdit::OnKeyDown(nChar, nRepCnt, nFlags);
	CTypeAheadCombo* pParent = (CTypeAheadCombo*) GetParent();

/************************************** : by VK at 09.01.2004 19:08:17 **\
  if ( GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_HOME) < 0) {
    int i= 0;
    i++;
  }
\************************************** : by VK at 09.01.2004 19:08:21 **/
	
	// If the DELETE or BACKSPACE keys were pressed, set a flag
	m_bDelete = false;
	m_bBackspace = false;
	switch (nChar) {
	case VK_DELETE:
		m_bDelete = true;
    m_bHighlighted = false;
		break;
	case VK_BACK:
		m_bBackspace = true;
    m_bHighlighted = false;
		break;
	}

	// Get current cursor position
	m_nPos = LOWORD(pParent->GetEditSel());
	if ((nChar == VK_LEFT) || (nChar == VK_RIGHT)) {
		// If the left or right cursor keys have been pressed, this
		// will unhighlight the item
		m_bHighlighted = false;
		m_SearchString.Empty();
	}
	
	// If the DELETE key was not pressed, a WM_CHAR message does not get
	// generated, manually call OnChar() 

/************************************** : by VK at 27.10.2003 22:24:46 **\
	if (m_bDelete)
		OnChar(nChar, nRepCnt, nFlags);
\************************************** : by VK at 27.10.2003 22:24:49 **/
}

// This is called when  WM_CHAR message is sent to CAS. The nChar
// parameter contains the code of the character pressed.
void CComboEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// Only call the base class if it was NOT the DELETE key that was
	// pressed because if it was then it means that this function
	// has been called manually and calling the base class again would
	// cause two characters to get deleted!
/************************************** : by VK at 09.01.2004 11:26:10 **\
	if (nChar != VK_DELETE)
		CEraMaskEdit::OnChar(nChar, nRepCnt, nFlags);
\************************************** : by VK at 09.01.2004 11:26:13 **/
  CEraEdit::OnChar(nChar, nRepCnt, nFlags);

	if (m_bHighlighted) {
		if ((m_bBackspace) || (m_bDelete)) {
			// A selection is highlighted and the backspace or delete
			// was pressed. Erase selection completely
			m_SearchString.Empty();
			m_bHighlighted = false;
      /************************************** : by VK at 27.10.2003 22:23:34 **\
			SetWindowText("");
      \************************************** : by VK at 27.10.2003 22:23:36 **/
			m_nStartAfter = -1;
		}
		else {
			// Alphanumeric key entered - go see if a match is found
			DoFind(nChar);
		}
	}
	else {
		// A selection is not highlighted, go see if a match is found
    if (false==m_bBackspace && false==m_bDelete)
		  DoFind(nChar);
	}
}

BOOL CComboEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CEraEdit::OnMouseWheel(nFlags, zDelta, pt);
}

// DoFind() is an internal helper function to do the work of checking 
// a searh string against the items in the combo box. The search string
// is gradually built up by adding each new keysytoke to it as the user
// types it. If a match is found, that item in the combo box is highlighted
void CComboEdit::DoFind(UINT nChar) {
	int length = 0, index = 0;
	CTypeAheadCombo* pParent = (CTypeAheadCombo*) GetParent();

	// Get the key that the user typed
	GetWindowText(m_SearchString);
	// Add it to the existing search string


	// Get the length of the new string
	length = m_SearchString.GetLength();
	if (length) {
		// Search string is at least one character
		index = pParent->FindString(m_nStartAfter, m_SearchString);
		if (index != -1) {
			// Search string was found, highlight the item
//    ************************************** : by VK at 24.01.2003 23:58:08
			pParent->SetCurSel(index);
//    ************************************** : by VK at 24.01.2003 23:58:11
      // by VK
      CString sFoundItem;
      pParent->GetLBText(index, sFoundItem);
      int lenFound = sFoundItem.GetLength();
      SetWindowText(sFoundItem);
      SetSel(length, lenFound);
      CWnd* pDlg = pParent->GetParent();
      if ( pDlg )
        pDlg->SendMessage(WM_COMMAND, MAKEWPARAM(pParent->GetDlgCtrlID(), CBN_SELCHANGE), (LPARAM)m_hWnd);
      // by VK

			m_nStartAfter = index;
			m_bHighlighted = true;
		}
		else {
			// Search string was not found in which case we want to put 
			// the user's text back into the edit box, reset
			// the search string and set the cursor appropriately
			if (m_bBackspace) {
				// BACKSPACE key pressed, the cursor position
				// needs to be one less than it was before
				pParent->SetEditSel(m_nPos - 1, m_nPos - 1);
			}
			else if (m_bDelete) {
				// DELETE key was pressed, leave the cursor as it was
				pParent->SetEditSel(m_nPos, m_nPos);
			}
			else if (m_bHighlighted) {
				// If the string was already highlighted then we put the
				// new search string in its place and set the cursor to the end
				SetWindowText(m_SearchString);
				pParent->SetEditSel(length, length);
			}
			else {
				// If a selection wasn't highlighted, we just move the cursor along
				pParent->SetEditSel(m_nPos + 1, m_nPos + 1);
			}
			// Clear out the search string 
			m_SearchString.Empty();
			m_bHighlighted = false;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo
IMPLEMENT_DYNAMIC(CTypeAheadCombo, CComboBox)
CTypeAheadCombo::CTypeAheadCombo() {
}
CTypeAheadCombo::~CTypeAheadCombo() {
}

BEGIN_MESSAGE_MAP(CTypeAheadCombo, CComboBox)
	//{{AFX_MSG_MAP(CTypeAheadCombo)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTypeAheadCombo message handlers
BOOL CTypeAheadCombo::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	// TODO: Add your message handler code here and/or call default
	if ( GetDroppedState() )
	  return CComboBox::OnMouseWheel(nFlags, zDelta, pt);
  return TRUE;
}

void CTypeAheadCombo::PreSubclassWindow() {
	m_xEdit.SubclassDlgItem(1001, this);	
	CComboBox::PreSubclassWindow();
  LONG lStyle = ::GetWindowLong(m_xEdit.m_hWnd, GWL_STYLE);
}

CString CTypeAheadCombo::GetCurText() {
  CString s;
  if ( ::IsWindow(m_xEdit.m_hWnd) ) {
    m_xEdit.GetWindowText(s);
  }
  else {
    int nIndex = GetCurSel();
    if ( CB_ERR != nIndex )
      GetLBText(nIndex, s);
  }
  return s;
/************************************** : by VK at 14.08.2004 0:24:44 **\
  CString s;
  int nIndex = GetCurSel();
  if ( CB_ERR != nIndex ) {
    GetLBText(nIndex, s);
  }
  else if ( ::IsWindow(m_xEdit.m_hWnd) ) {
    m_xEdit.GetWindowText(s);
  }
  return s;
\************************************** : by VK at 14.08.2004 0:24:48 **/
}

int CTypeAheadCombo::SetCurText(const CString& sText) {
  if ( sText.IsEmpty() )
    return CB_ERR;
  int nIndex = FindStringExact(-1, sText);
  if ( CB_ERR==nIndex )
    nIndex = AddString(sText);
  return SetCurSel(nIndex);
}

DWORD CTypeAheadCombo::GetCurData() {
  int nIndex = GetCurSel();
  if ( CB_ERR != nIndex )
    return GetItemData(nIndex);
  return NULL;
}

BOOL CTypeAheadCombo::IsEmpty() {
  CString s = Trim(GetCurText());
  return s.IsEmpty() ? TRUE : FALSE;
}

DWORD GetDataByIndex(HWND hWndCtrl, int index) {
  return (DWORD)::SendMessage(hWndCtrl, CB_GETITEMDATA, (WPARAM)index, 0);
}
int GetIndexByData(HWND hWndCtrl, DWORD dwData) {
  int nCount;
  DWORD dwItemData;
  nCount = ::SendMessage(hWndCtrl, CB_GETCOUNT, 0, 0);
  for ( int i(0); i < nCount; i++ ){
    dwItemData = GetDataByIndex(hWndCtrl, i);
    if( dwItemData==dwData)
      return i;
  }
  return -1;
}

void AFXAPI DDX_CBData(CDataExchange* pDX, int nIDC, long& ldata) {
	HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
	if (pDX->m_bSaveAndValidate) {
    int nIndex = (int)::SendMessage(hWndCtrl, CB_GETCURSEL, 0, 0L);
    if ( nIndex != CB_ERR )
  		ldata = GetDataByIndex(hWndCtrl, nIndex);
  }
	else {
    int nIndex = GetIndexByData(hWndCtrl, ldata);
    ::SendMessage(hWndCtrl, CB_SETCURSEL, (WPARAM)nIndex, 0L);
  }
}

void AFXAPI DDX_FieldCBData(CDataExchange* pDX, int nIDC, long& ldata, CDaoRecordset* pRecordset) {
	ASSERT_VALID(pRecordset);

	if (!pDX->m_bSaveAndValidate &&
		(!pRecordset->IsOpen() || pRecordset->IsFieldNull(&ldata)))
	{
		long lData = 0;
		DDX_CBData(pDX, nIDC, lData);
	}
	else
		DDX_CBData(pDX, nIDC, ldata);
}

/////////////////////////////////////////////////////////////////////////////
// CEraComboBox
IMPLEMENT_DYNAMIC(CEraComboBox, CTypeAheadCombo)
CEraComboBox::CEraComboBox() {
  m_bFocus = m_bFilled = false;
  m_pFatherCmb = m_pGrandFaCmd = NULL;
}

CEraComboBox::~CEraComboBox() {
}

LONG CEraComboBox::SetStyle(LONG lStyle) {
LONG lOldStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  SetWindowLong(m_hWnd, GWL_STYLE, lOldStyle | lStyle);
  return lOldStyle;
}

void CEraComboBox::SetDefault(LPCTSTR szDefValue) {
  m_sDefValue = szDefValue;
}

BOOL CEraComboBox::IsCurDefault() {
  CString s = GetCurText();
  if ( s.IsEmpty() )
    return FALSE;
  return (s==m_sDefValue);
}

void CEraComboBox::UpdateByDefault() {
  CString s = GetCurText();
  if ( !s.IsEmpty() )
    return;
  if ( FALSE==m_sDefValue.IsEmpty() ) {
    int nItem = GetCurSel();
    if ( CB_ERR==nItem ) { // empty
      nItem = FindString(-1, m_sDefValue);
      if ( nItem == CB_ERR )
        nItem = AddString(m_sDefValue);
    }
    SetCurSel(nItem);
  }
}

int CEraComboBox::FindData(long lData) {
  int nItems = GetCount();
  for( int i(0); i < nItems; i++ ) {
    if ( (DWORD)lData == GetItemData(i) )
      return i;
  }
  return CB_ERR;
}

BEGIN_MESSAGE_MAP(CEraComboBox, CComboBox)
	//{{AFX_MSG_MAP(CEraComboBox)
	ON_CONTROL_REFLECT(CBN_SETFOCUS, OnSetfocus)
	ON_WM_NCDESTROY()
	//}}AFX_MSG_MAP
//  ON_MESSAGE(WM_CTLCOLOREDIT, OnCtlColorEdit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEraComboBox message handlers
BOOL CEraComboBox::PreTranslateMessage(MSG* pMsg) {
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->message==WM_KEYDOWN && VK_RETURN==pMsg->wParam) {
    pMsg->wParam = VK_TAB;
  }
	return CComboBox::PreTranslateMessage(pMsg);
}

int CEraComboBox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct) {
	// TODO: Add your code to determine the sorting order of the specified items
	// return -1 = item 1 sorts before item 2
	// return 0 = item 1 and item 2 sort the same
	// return 1 = item 1 sorts after item 2
	return 0;
}
void CEraComboBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) {
	// TODO: Add your code to draw the specified item
  DefWindowProc(WM_DRAWITEM, (WPARAM)lpDIS->CtlID, (LPARAM)lpDIS);
}


IMPLEMENT_DYNAMIC(CEraNameComboBox, CEraComboBox)
BEGIN_MESSAGE_MAP(CEraNameComboBox, CEraComboBox)
	//{{AFX_MSG_MAP(CEraNameComboBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEraNameComboBox::CEraNameComboBox() {
  m_xEdit.m_fReplaceQuote = true;
  m_xEdit.m_bFirstUC = true;
  m_MaleFemale = -1;
}

BOOL CEraNameComboBox::IsMale() {
  return (1==m_MaleFemale);
}
BOOL CEraNameComboBox::IsFemale() {
  return (0==m_MaleFemale);
}
void CEraNameComboBox::SetMale() {
  m_MaleFemale = 1;
}
void CEraNameComboBox::SetFemale() {
  m_MaleFemale = 0;
}
void CEraNameComboBox::SetAltText(LPCTSTR szText, COLORREF clrAltColor/*=0*/) {
  m_xEdit.SetAltText(szText, clrAltColor);
}
void CEraComboBox::OnSetfocus() {
/************************************** : by VK at 26.01.2004 22:35:58 **\
  CString s;
	m_bFocus = TRUE;
  if ( ::IsWindow(m_xEdit.m_hWnd) ) {
    m_xEdit.GetWindowText(s);
    if ( (m_pFatherCmb && m_pFatherCmb->IsCurDefault()) || (m_pGrandFaCmd &&  m_pGrandFaCmd->IsCurDefault()) ) {
      if ( s.IsEmpty() && !m_sDefValue.IsEmpty() ) {
        int nLength = m_sDefValue.GetLength();
        m_xEdit.SetWindowText(m_sDefValue);
        m_xEdit.SetSel(0, nLength, TRUE);
      }
    }
    m_xEdit.SetFocus();
  }
\************************************** : by VK at 26.01.2004 22:36:08 **/

/************************************** : by VK at 25.01.2004 18:50:49 **\
  s = GetCurText();
  int nIndex = GetCurSel();
  if ( CB_ERR==nIndex && false==IsEmptyText(s) ) {
    nIndex = AddString(s);
    SetCurSel(nIndex);
  }
\************************************** : by VK at 25.01.2004 18:50:52 **/
}
