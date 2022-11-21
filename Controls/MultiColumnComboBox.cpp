/************************************
  REVISION LOG ENTRY
  Revision By: Mihai Filimon
  Revised on 9/16/98 2:20:27 PM
  Comments: MultiColumnComboBox.cpp : implementation file
 ************************************/

#include "stdafx.h"
#include "MultiColumnComboBox.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiColumnComboBox

CBrush CMultiColumnComboBox::m_brBkGnd(defaultRGBBkGnd);
CFont CMultiColumnComboBox::m_font;

static const LOGFONT logFontPages =
{
/*LONG lfHeight*/8,
/*LONG lfWidth*/0,
/*LONG lfEscapement*/0,
/*LONG lfOrientation*/0,
/*LONG lfWeight*/FW_NORMAL,
/*BYTE lfItalic*/FALSE,
/*BYTE lfUnderline*/FALSE,
/*BYTE lfStrikeOut*/FALSE,
/*BYTE lfCharSet*/ANSI_CHARSET,
/*BYTE lfOutPrecision*/0,
/*BYTE lfClipPrecision*/0,
/*BYTE lfQuality*/DEFAULT_QUALITY,
/*BYTE lfPitchAndFamily*/DEFAULT_PITCH,
/*CHAR lfFaceName[LF_FACESIZE]*/_T("MS Sans Serif")
};

// Function name	: CMultiColumnComboBox::CMultiColumnComboBox
// Description	    : default constuctor
// Return type		: 
CMultiColumnComboBox::CMultiColumnComboBox(int nColumnKey)
{
	RegClassMultiColumnComboBox();
	m_pListCtrl = NULL;
	m_pEdit = NULL;
	m_bCaptured = FALSE;
	m_nColumnKey = nColumnKey;
	SetRateWidth(0.0);
	SetMultipleHeight();
	m_bFirstShow = TRUE; 
  m_fEditOnChange = FALSE;
  m_bBackspace = m_bDelete = m_bKeyPressed = false;
  m_CompareFunc = NULL;
  m_EditID = IDEDIT;
  m_ListID = IDLISTCTRL;
}

// Function name	: CMultiColumnComboBox::~CMultiColumnComboBox
// Description	    : virtual destructor
// Return type		: 
CMultiColumnComboBox::~CMultiColumnComboBox()
{
}

BEGIN_MESSAGE_MAP(CMultiColumnComboBox, CWnd)
	//{{AFX_MSG_MAP(CMultiColumnComboBox)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiColumnComboBox message handlers
UINT CMultiColumnComboBox::m_nSelChange = NULL;

// Function name	: CMultiColumnComboBox::RegClassMultiColumnComboBox
// Description	    : Register this window class
// Return type		: BOOL 
BOOL CMultiColumnComboBox::RegClassMultiColumnComboBox()
{
	WNDCLASS wndClass;
		wndClass.style = CS_DBLCLKS;
		wndClass.lpfnWndProc = ::DefWindowProc;
		wndClass.cbClsExtra = NULL;
		wndClass.cbWndExtra = NULL;
		wndClass.hInstance = AfxGetInstanceHandle();
		wndClass.hIcon = NULL;
		wndClass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)m_brBkGnd;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = wndClassName;
	BOOL bResult = AfxRegisterClass(&wndClass);
	if (bResult)
	{
		if (!m_nSelChange)
			m_nSelChange = RegisterWindowMessage(defaultSelChange);
		if (!m_font.GetSafeHandle())
		{
			//At the first call set the new font
			m_font.CreateFontIndirect(&logFontPages);
		}
	}
	return bResult;
}

CMultiColumnComboBox* CMultiColumnComboBox::m_pActiveMCBox = NULL;
CMultiColumnComboBox::CWindowProcs CMultiColumnComboBox::m_wndProcs;
// Function name	: CMultiColumnComboBox::ListCtrlWindowProc
// Description	    : ListControl window procedure
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CMultiColumnComboBox::ListCtrlWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CMultiColumnComboBox* pOwner  = NULL;
	if (pOwner = CMultiColumnComboBox::m_pActiveMCBox)
		pOwner->ForwardMessage(nMsg, wParam, lParam);
	LRESULT lResult = CallWindowProc( CMultiColumnComboBox::m_wndProcs.GetOldListCtrlProcedure(hWnd), hWnd, nMsg, wParam, lParam );
	return lResult;
}

// Function name	: CMultiColumnComboBox::ParentWindowProc
// Description	    : Parent window procedure.
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CMultiColumnComboBox::ParentWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	if (CMultiColumnComboBox* pOwner = CMultiColumnComboBox::m_pActiveMCBox)
	{
		switch (nMsg)
		{
			case WM_COMMAND:
			case WM_CAPTURECHANGED:
			case WM_SYSCOMMAND:
			case WM_LBUTTONDOWN:
			case WM_NCLBUTTONDOWN:
			{
				BOOL bDropped = pOwner->IsDropedDown();
        pOwner->m_bKeyPressed = false;
				pOwner->DropDown(FALSE);
				if (nMsg == WM_COMMAND)
					if (LOWORD(wParam) == IDOK)
					{
						pOwner->SelectCurrentItem(TRUE);
						return FALSE;
					}
					else
						if (LOWORD(wParam) == IDCANCEL)
							if (bDropped)
								return FALSE;
				break;
			}
		}
	};
	WNDPROC wndProc = CMultiColumnComboBox::m_wndProcs.GetOldParentProcedure(hWnd);
	ASSERT (wndProc);
	return CallWindowProc( wndProc, hWnd, nMsg, wParam, lParam );
}

// Function name	: CMultiColumnComboBox::EditWindowProc
// Description	    : Edit window procedure
// Return type		: LRESULT CALLBACK 
// Argument         : HWND hWnd
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CALLBACK CMultiColumnComboBox::EditWindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	CMultiColumnComboBox* pOwner = CMultiColumnComboBox::m_pActiveMCBox;
	switch (nMsg)
	{
		case WM_SETFOCUS:
			{
				CMultiColumnComboBox::m_pActiveMCBox = (CMultiColumnComboBox*)CWnd::FromHandle(::GetParent(hWnd));
				break;
			}
		case WM_KILLFOCUS:
			{
				if (pOwner)
				{
					pOwner->DropDown(FALSE);
					CMultiColumnComboBox::m_pActiveMCBox = NULL;
          if ( GetKeyState(VK_RETURN) < 0 ) {
            CString sText;
            sText = pOwner->GetEdit()->GetText();
            if ( !sText.IsEmpty() ) {
              pOwner->Search(pOwner->GetEdit()->GetText());
          		if (CWnd* pParent = pOwner->GetParent())
			          pParent->SendMessage(pOwner->m_nSelChange, (WPARAM)pOwner->GetDlgCtrlID(), (LPARAM)pOwner->m_hWnd);
            }
          }
				}
				break;
			}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				if (pOwner)
          pOwner->m_bKeyPressed = true;
          pOwner->m_bBackspace = pOwner->m_bDelete = false;
					switch ((int) wParam)
					{
						case VK_UP:
						case VK_DOWN:
							{
								if (GetAsyncKeyState(VK_MENU) >= 0)
								{
                  pOwner->m_bKeyPressed = false;
                  int nItem = pOwner->GetCurrentItem() + ((int) wParam == VK_UP ? -1 : +1);
									pOwner->SetCurrentItem(nItem);
                  pOwner->GetListCtrl()->EnsureVisible(nItem, FALSE);
									pOwner->SelectCurrentItem(FALSE);
									break;
								}
							}
						case defaultDropDownKey:
							{
								pOwner->DropDown(!pOwner->IsDropedDown());
								pOwner->CaptureListCtrl();
								break;
							}
            case VK_BACK:
              pOwner->m_bBackspace = true;
              break;
            case VK_DELETE:
              pOwner->m_bDelete = true;
              break;
					}
				break;
			}
	}
	return CallWindowProc( CMultiColumnComboBox::m_wndProcs.GetOldEditProcedure(hWnd), hWnd, nMsg, wParam, lParam );
}

// Function name	: CMultiColumnComboBox::OnInit
// Description	    : Init the control
// Return type		: BOOL 
BOOL CMultiColumnComboBox::OnInit()
{
	//Do not call twice
	ASSERT (m_pEdit == NULL && m_pListCtrl == NULL);
	ASSERT (m_font.GetSafeHandle());
	SetFont(&m_font);
	ModifyStyle(WS_OVERLAPPED , WS_TABSTOP);
  ModifyStyleEx(0, WS_EX_CLIENTEDGE); // instead of static edge
	m_pEdit		= new CEraEdit();
	m_pListCtrl = new CListCtrl();
	if (m_pEdit->Create(WS_CHILD | WS_VISIBLE | defaultEditStyle, CRect(0,0,0,0), this, m_EditID ))
	{
		ModifyStyleEx(0, WS_EX_STATICEDGE);
		m_pEdit->SetFont(&m_font);
		if (m_pListCtrl->Create(WS_BORDER | WS_CHILD | defaultListCtrlStyle , CRect(0,0,0,0), GetDesktopWindow(), m_ListID))
		{
			//Set the reference to this object in user data dword
			::SetWindowLong(m_pListCtrl->m_hWnd, GWL_USERDATA, (long)this);
			::SetWindowLong(m_pListCtrl->m_hWnd, GWL_STYLE, GetWindowLong(m_pListCtrl->m_hWnd, GWL_STYLE) | WS_CLIPSIBLINGS | WS_OVERLAPPED);
			m_pListCtrl->ModifyStyleEx(0, WS_EX_TOOLWINDOW);
			m_pListCtrl->SetWindowPos(&CWnd::wndTopMost,0,0,0,0, SWP_NOSIZE | SWP_NOMOVE);
			ListView_SetExtendedListViewStyle(m_pListCtrl->m_hWnd, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
			Resize();
			m_wndProcs.AddEdit(GetEdit(), EditWindowProc);
			m_wndProcs.AddListCtrl(GetListCtrl(), ListCtrlWindowProc);
			m_wndProcs.AddParent(GetParent(), ParentWindowProc);
			return TRUE;
		}
	}
	return FALSE;
}

// Function name	: CMultiColumnComboBox::PreSubclassWindow
// Description	    : Call to subclass window
// Return type		: void 
void CMultiColumnComboBox::PreSubclassWindow() 
{
	CWnd::PreSubclassWindow();

	// If this is dynamical created then do not call OnInit
	if (AfxGetThreadState()->m_pWndInit == 0)
		OnInit();
}

// Function name	: CMultiColumnComboBox::OnDestroy
// Description	    : Remove all dependent datas.
// Return type		: void 
void CMultiColumnComboBox::OnDestroy() 
{
	CWnd::OnDestroy();

	m_wndProcs.RemoveEdit(GetEdit());
	m_wndProcs.RemoveListCtrl(GetListCtrl());
	m_wndProcs.RemoveParent(GetParent());
	if (CListCtrl* pList = GetListCtrl())
		delete pList;

	if (CEraEdit* pEdit = GetEdit())
		delete pEdit;

	m_pListCtrl = NULL;
	m_pEdit = NULL;

}

// Function name	: CMultiColumnComboBox::GetListCtrl
// Description	    : return the list control for 
// Return type		: CListCtrl* 
CListCtrl* CMultiColumnComboBox::GetListCtrl()
{
	return m_pListCtrl;
}

// Function name	: CMultiColumnComboBox::GetEdit
// Description	    : retirn  pointer to edit control inside of thsi control
// Return type		: CEraEdit* 
CEraEdit* CMultiColumnComboBox::GetEdit() {
	return m_pEdit;
}

// Function name	: CMultiColumnComboBox::DrawButton
// Description	    : Draw down button
// Return type		: void 
// Argument         : CDC * pDC
// Argument         : CRect r
// Argument         : BOOL bDown
void CMultiColumnComboBox::DrawButton(CDC * pDC, CRect r, BOOL bDown) {
	COLORREF rgbShadow  = GetSysColor(COLOR_BTNSHADOW);
	COLORREF rgbFace = GetSysColor(COLOR_BTNFACE);
	
	pDC->FillRect(r,&CBrush(rgbFace));

	if (bDown)
	{
		pDC->FrameRect(r,&CBrush(rgbShadow));
	}
	else
	{
		pDC->DrawEdge( r, EDGE_RAISED,BF_RECT);
	}
	
	r.top += 2;
	r.bottom -= 2;

	CBitmap bitmapOEM;
	if (bitmapOEM.LoadOEMBitmap(OBM_COMBO))
	{
		CDC dcMem;
		if (dcMem.CreateCompatibleDC(pDC))
		{
			BITMAP b; bitmapOEM.GetBitmap(&b);
			int leftC = (r.Width() - b.bmWidth) / 2;
			int topC = (r.Height() - b.bmHeight) / 2;
			if (bDown)
			{
				leftC++;
				topC++;
			}
			CBitmap* pOldBitmap = dcMem.SelectObject(&bitmapOEM);
			pDC->BitBlt(r.left + leftC, r.top + topC, r.Width(), r.Height(), &dcMem, 0,0, SRCCOPY);
			pOldBitmap = dcMem.SelectObject(pOldBitmap);
		}
	}
}

// Function name	: CMultiColumnComboBox::OnPaint
// Description	    : On Draw function
// Return type		: void 
void CMultiColumnComboBox::OnPaint() {
	CPaintDC dc(this); // device context for painting
	
	CRect r; GetClientRect(r);
	
	r.left = r.right - defaultSizeDX;
	
	m_rectBtn = r;

	DrawButton(&dc, m_rectBtn);
}

// Function name	: CMultiColumnComboBox::Resize
// Description	    : Call to remove the edit and list controls
// Return type		: void 
void CMultiColumnComboBox::Resize()
{
	ASSERT (GetListCtrl());
	CRect r;
	GetWindowRect(r);
	SetWindowPos(0, 0, 0, r.Width(), defaultSizeDY, SWP_NOMOVE | SWP_NOZORDER);
	// Set the height and width of edit control
	GetClientRect(r);
	
	r.right -= defaultSizeDX;
	GetEdit()->MoveWindow(r.left, r.top, r.Width(), r.Height());
	// Set the height and width of list control
	GetWindowRect(r);
	int dy = r.Height();
	r.top = r.bottom;
	r.left++;r.right--;
	r.bottom += m_nMultipleHeight * dy;
	r.right += int(m_dWidthList * r.Width());

// by VK
  CWnd* pParent = GetParent();
  //CRect deskTopRect;
  //CWnd::GetDesktopWindow()->GetWindowRect(&deskTopRect);
  if ( pParent ) {
    CRect parentRect;
    pParent->GetWindowRect(&parentRect);
    while ( r.right > parentRect.right)
      r.OffsetRect(-1, 0);
  }
// by VK

	GetListCtrl()->MoveWindow(r.left, r.top, r.Width(), r.Height());
}

// Function name	: CMultiColumnComboBox::DropDown
// Description	    : DropDown
// Return type		: void 
// Argument         : BOOL bDown
void CMultiColumnComboBox::DropDown(BOOL bDown)
{
	if (IsWindowVisible())
	{
		if (IsDropedDown() != bDown)
		{
			Resize();
			GetListCtrl()->ShowWindow(bDown ? SW_SHOW : SW_HIDE);
			if (bDown)
				GetEdit()->SetFocus();
			else
				ReleaseCapture();
		}
	}
}

// Function name	: CMultiColumnComboBox::IsDropedDown
// Description	    : If the list control is dropped downd, return TRUE
// Return type		: BOOL 
BOOL CMultiColumnComboBox::IsDropedDown()
{
	return GetListCtrl()->IsWindowVisible();
}

// Function name	: CMultiColumnComboBox::OnWindowPosChanged
// Description	    : 
// Return type		: void 
// Argument         : WINDOWPOS FAR* lpwndpos
void CMultiColumnComboBox::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CWnd::OnWindowPosChanged(lpwndpos);
	Resize();
}

// Function name	: CMultiColumnComboBox::OnLButtonDown
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CMultiColumnComboBox::OnLButtonDown(UINT nFlags, CPoint point) {
	if (m_rectBtn.PtInRect(point)) {
		SetButton();
		DropDown(!IsDropedDown());
	}
	else
	  CWnd::OnLButtonDown(nFlags, point);
}

// Function name	: CMultiColumnComboBox::OnLButtonUp
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CMultiColumnComboBox::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseButton();
	CaptureListCtrl();
	CWnd::OnLButtonUp(nFlags, point);
}

// Function name	: CMultiColumnComboBox::OnMouseMove
// Description	    : 
// Return type		: void 
// Argument         : UINT nFlags
// Argument         : CPoint point
void CMultiColumnComboBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured)
	{
		CPoint p; ::GetCursorPos(&p);
		ScreenToClient(&p);
		if (!m_rectBtn.PtInRect(p))
			ReleaseButton();
	}
	
	CWnd::OnMouseMove(nFlags, point);
}

// Function name	: CMultiColumnComboBox::ReleaseButton
// Description	    : Call to release the capture and image of button. After SetButton()
// Return type		: void 
void CMultiColumnComboBox::ReleaseButton()
{
	if (m_bCaptured)
	{
		ReleaseCapture();
		CDC* pDC = GetDC();
			DrawButton(pDC, m_rectBtn);
		ReleaseDC(pDC);
		m_bCaptured = FALSE;
		GetListCtrl()->SetCapture();
	}
}

// Function name	: CMultiColumnComboBox::SetButton
// Description	    : 
// Return type		: void 
void CMultiColumnComboBox::SetButton()
{
	if (!m_bCaptured)
	{
		SetCapture();
		CDC* pDC = GetDC();
			DrawButton(pDC, m_rectBtn, TRUE);
		ReleaseDC(pDC);
		m_bCaptured = TRUE;
	}
}

// Function name	: CMultiColumnComboBox::ForwardMessage
// Description	    : This function is called by ListCtrlWindowProc
// Return type		: void 
// Argument         : UINT nMsg
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
void CMultiColumnComboBox::ForwardMessage(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	ASSERT (GetListCtrl());
	switch (nMsg)
	{
		case WM_MOUSEMOVE:
		case WM_NCMOUSEMOVE:
		{
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			GetListCtrl()->SetCapture();
		}
		case WM_LBUTTONDOWN:
		  {
        m_bKeyPressed = false;
  			CPoint point(LOWORD(lParam), HIWORD(lParam));
	  		CRect rectClient; GetListCtrl()->GetClientRect(rectClient);
		  	CRect rectWindow; GetListCtrl()->GetWindowRect(rectWindow);
  			CPoint pointScreen(point);
	  		GetListCtrl()->ClientToScreen(&pointScreen);
		  	LPARAM lPoint = MAKELPARAM(pointScreen.x, pointScreen.y);
			  UINT ht = GetListCtrl()->SendMessage(WM_NCHITTEST,0,lPoint);
  			if (HTCLIENT==ht) {
				  int nIndex = GetListCtrl()->HitTest(CPoint(LOWORD(lParam), HIWORD(lParam)));
  				if (GetCurrentItem() != nIndex)
	  				SetCurrentItem(nIndex);
		  	}
			  else {
				  if (rectWindow.PtInRect(pointScreen))
					  if (nMsg == WM_LBUTTONDOWN) {
						  ReleaseCapture();
						  GetListCtrl()->SendMessage(WM_NCLBUTTONDOWN, ht, lPoint);
						  break;
					  }
        }
			  if (WM_LBUTTONDOWN==nMsg) {
				  DropDown(FALSE);
          if ( HTCLIENT==ht )
				    SelectCurrentItem(TRUE);
			  }
      }
			break;
    case WM_KEYDOWN:
      {
        if ( (int) wParam==VK_RETURN ) {
          int i(0);
          i++;
        }
      }
      break;
	}
}

// Function name	: CMultiColumnComboBox::OnSetFocus
// Description	    : When control have focus then edit will take the focus
// Return type		: void 
// Argument         : CWnd* pOldWnd
void CMultiColumnComboBox::OnSetFocus(CWnd* pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	GetEdit()->SetFocus();
/************************************** : by VK at 21.01.2004 0:11:54 **\
  // by VK
  GetEdit()->SetSel(0, -1);
  // by VK
\************************************** : by VK at 21.01.2004 0:11:56 **/
}

// Function name	: CMultiColumnComboBox::OnCommand
// Description	    : When something is happen in edit control, notify the list control
// Return type		: BOOL 
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
BOOL CMultiColumnComboBox::OnCommand(WPARAM wParam, LPARAM lParam) {
	if (LOWORD(wParam) == m_EditID)
		if (HIWORD(wParam) == EN_CHANGE) {
      if ( m_fEditOnChange )
        return FALSE;
      m_fEditOnChange = TRUE;
			ASSERT( GetEdit() && GetEdit()->GetDlgCtrlID() == m_EditID);
			CString text,t ;
			GetEdit()->GetWindowText(t);
			Search(t);
      m_fEditOnChange = FALSE;
		}
	
	return CWnd::OnCommand(wParam, lParam);
}

// Function name	: CMultiColumnComboBox::Search
// Description	    : Look for the lpszFindItem
// Return type		: void 
// Argument         : LPCTSTR lpszFindItem
void CMultiColumnComboBox::Search(LPCTSTR lpszFindItem) {
  if (CListCtrl* pListCtrl = GetListCtrl()) {
    int nItem(-1);
    if ( false==m_bKeyPressed ) {
      POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
      if ( pos )
        nItem = pListCtrl->GetNextSelectedItem(pos);
    }
    if ( -1==nItem ) {
      LV_FINDINFO fInfo;
      fInfo.flags = LVFI_PARTIAL | LVFI_STRING;
      fInfo.psz = lpszFindItem;
      nItem = pListCtrl->FindItem(&fInfo);
      SetCurrentItem(nItem);
      pListCtrl->EnsureVisible(nItem, FALSE); 
    }
    if ( nItem != -1 ) {
      if ( false==m_bBackspace && false==m_bDelete ) {
        CString s = pListCtrl->GetItemText(nItem, 0);
        CEraEdit* pEdit = GetEdit();
        int nStart, nEnd;
        pEdit->GetSel(nStart, nEnd);
        pEdit->SetWindowText(s);
        pEdit->SetSel(nStart, s.GetLength() );
      }
    }
  }
  m_bKeyPressed = false;
}

// Function name	: CMultiColumnComboBox::SelectCurrentItem
// Description	    : Select the current item of list. Called if user click the mouse, oor press ENTER
// Return type		: void 
void CMultiColumnComboBox::SelectCurrentItem(BOOL fNotifyParent)
{
	int nIndex = GetCurrentItem();
  CString sText = GetListCtrl()->GetItemText(nIndex, m_nColumnKey);
	GetEdit()->SetWindowText( sText );
  GetEdit()->SetSel(0, -1);
	//Notify the parent that one item was changed
  if ( fNotifyParent ) {
  	if (nIndex >= 0)
	  	if (CWnd* pParent = GetParent())
		  	pParent->SendMessage(m_nSelChange, (WPARAM)GetDlgCtrlID(), (LPARAM)m_hWnd);
  }
}

// Function name	: CMultiColumnComboBox::GetCurrentItem
// Description	    : Get current item from list control
// Return type		: int 
int CMultiColumnComboBox::GetCurrentItem()
{
	return GetListCtrl()->GetNextItem(-1, LVNI_SELECTED);
}

// Function name	: CMultiColumnComboBox::SetCurrentItem
// Description	    : Set current item from list control to nIndex
// Return type		: void 
// Argument         : int nIndex
void CMultiColumnComboBox::SetCurrentItem(int nIndex)
{
	GetListCtrl()->SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

// Function name	: CMultiColumnComboBox::OnCreate
// Description	    : Call OnInit if control is created dynamically
// Return type		: int 
// Argument         : LPCREATESTRUCT lpCreateStruct
int CMultiColumnComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	OnInit();
	
	return 0;
}

// Function name	: CMultiColumnComboBox::SetRateWidth
// Description	    : This function will changes the width of inside listcontrol
// Return type		: double 
// Argument         : double dWidthList
double CMultiColumnComboBox::SetRateWidth(double dWidthList)
{
	double dResult = m_dWidthList;
	m_dWidthList = fabs(dWidthList);
	return dResult;
}

// Function name	: CMultiColumnComboBox::SetMultipleHeight
// Description	    : 
// Return type		: int 
// Argument         : int nMHeight
int CMultiColumnComboBox::SetMultipleHeight(int nMHeight)
{
	int nResult = m_nMultipleHeight;
	m_nMultipleHeight = abs(nMHeight);
	return nResult;
}

// Function name	: CMultiColumnComboBox::WindowProc
// Description	    : 
// Return type		: LRESULT 
// Argument         : UINT message
// Argument         : WPARAM wParam
// Argument         : LPARAM lParam
LRESULT CMultiColumnComboBox::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (GetEdit())
		switch ( message )
		{
			case WM_SETTEXT:
			case WM_GETTEXT:
			{
				GetEdit()->SendMessage( message, wParam, lParam );
				break;
			}
		}
	
	return CWnd::WindowProc(message, wParam, lParam);
}

// Function name	: CMultiColumnComboBox::OnSize
// Description	    : resize combo if needs
// Return type		: void 
// Argument         : UINT nType
// Argument         : int cx
// Argument         : int cy
void CMultiColumnComboBox::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	Resize();
	
}

// Function name	: CMultiColumnComboBox::CaptureListCtrl
// Description	    : Capture listcontrol to know when the drop will be up
// Return type		: void 
void CMultiColumnComboBox::CaptureListCtrl() {
	if (IsDropedDown())
		GetListCtrl()->SetCapture();
}
