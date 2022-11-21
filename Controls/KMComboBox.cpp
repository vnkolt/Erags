// By Xiao Wu Guang

// KMComboBox.cpp : implementation file
//

#include "stdafx.h"
//#include "dataAlchemy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "KMComboBox.h"


/////////////////////////////////////////////////////////////////////////////
// CMultiColumnComboBox
CKMComboBox::CKMComboBox() {
  m_TotalColumn    = 0;
  m_BoundColumn    = 0;
  m_TextItemHeight  = 12;
  m_LightGrayPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DLIGHT));
  m_ColumnWidth    = NULL;
  m_ColumnAlignStyle  = NULL;
  m_ColumnItemList  = NULL;
  m_hListBox      = 0;
}

CKMComboBox::~CKMComboBox() {
  if (m_TotalColumn != 0) {
    delete[] m_ColumnWidth;
    delete[] m_ColumnAlignStyle;
    delete[] m_ColumnItemList;
  }
  m_LightGrayPen.DeleteObject();
}

BEGIN_MESSAGE_MAP(CKMComboBox, CEraComboBox)
  //{{AFX_MSG_MAP(CKMComboBox)
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
  ON_MESSAGE(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiColumnComboBox message handlers
void CKMComboBox::FormatComboBox(UINT TotalColumn, UINT BoundColumn) {
  ASSERT(TotalColumn > 1);  //You can use CEraComboBox class instead of this class

  m_TotalColumn = TotalColumn;
  m_BoundColumn = BoundColumn;

  m_ColumnWidth    = new UINT[m_TotalColumn];
  m_ColumnAlignStyle  = new UINT[m_TotalColumn];
  m_ColumnItemList  = new CStringList[m_TotalColumn];

  if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) != CBS_SIMPLE) {
    UINT ComboBoxWidth = GetDroppedWidth() - LEFTMARGIN_OF_DROPDOWNLIST - SPACE_BETWEEN_COLUMN - 1;
    UINT TotalColumnWidth = LEFTMARGIN_OF_DROPDOWNLIST + RIGHTMARGIN_OF_DROPDOWNLIST;
    for (UINT Index = 0; Index < m_TotalColumn; Index++) {
      //Assign default value 
      m_ColumnWidth[Index] = ComboBoxWidth;
      m_ColumnAlignStyle[Index] = DT_LEFT;
      TotalColumnWidth += (ComboBoxWidth + SPACE_BETWEEN_COLUMN);
    }

    SetDroppedWidth(TotalColumnWidth);
  }

  CDC * DeviceContextPointer = GetWindowDC();

  m_TextItemHeight = (DeviceContextPointer->GetTextExtent(" ", 1)).cy; // - 1;
  SetItemHeight(-1, m_TextItemHeight);
  ReleaseDC(DeviceContextPointer);
}

void CKMComboBox::SetColumnWidth(UINT ColumnWidth0, ...) {  
  va_list ColumnWidthPointer;
  UINT TotalColumnWidth;

  ASSERT(m_TotalColumn > 1);  //call FormatComboBox first

  m_ColumnWidth[0] = ColumnWidth0;
  TotalColumnWidth = ColumnWidth0 + SPACE_BETWEEN_COLUMN + LEFTMARGIN_OF_DROPDOWNLIST + RIGHTMARGIN_OF_DROPDOWNLIST;

  va_start(ColumnWidthPointer, ColumnWidth0);
  for (UINT Index = 1; Index < m_TotalColumn; Index++) {
    m_ColumnWidth[Index] = va_arg(ColumnWidthPointer, UINT);
    if (m_ColumnWidth[Index] > 0)
      TotalColumnWidth += (m_ColumnWidth[Index] + SPACE_BETWEEN_COLUMN);
  }
  va_end(ColumnWidthPointer);

  if ((GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) == CBS_SIMPLE) {
    CRect    WindowRectangle;
    GetWindowRect(WindowRectangle);
    SetWindowPos(NULL, 0, 0, TotalColumnWidth, WindowRectangle.bottom - WindowRectangle.top, SWP_NOMOVE | SWP_NOZORDER);
  }
  else
    SetDroppedWidth(TotalColumnWidth);
}

void CKMComboBox::SetColumnAlignStyle(UINT ColumnAlignStyle0, ...) {  
  va_list ColumnAlignStylePointer;

  ASSERT(m_TotalColumn > 1);  //call FormatComboBox first

  m_ColumnAlignStyle[0] = ColumnAlignStyle0;

  va_start(ColumnAlignStylePointer, ColumnAlignStyle0);
  for (UINT Index = 1; Index < m_TotalColumn; Index++)
    m_ColumnAlignStyle[Index] = va_arg(ColumnAlignStylePointer, UINT);
  va_end(ColumnAlignStylePointer);
}

int CKMComboBox::AddRow(LPCTSTR lpszString0, ...) {  
  va_list StringPointerPointer;
  UINT  Index, ItemIndex;
  LPCTSTR  StringPointer;

  ASSERT(m_TotalColumn > 1);  //call FormatComboBox first

  if (m_BoundColumn == 0)
    ItemIndex = CEraComboBox::AddString(lpszString0);
  else {
    va_start(StringPointerPointer, lpszString0);
    for (Index = 1; Index < m_TotalColumn; Index++) {
      StringPointer = va_arg(StringPointerPointer, LPCTSTR);
      if (m_BoundColumn == Index)
        ItemIndex = CEraComboBox::AddString(StringPointer);
    }
  }

  if (ItemIndex == 0)
    m_ColumnItemList[0].AddHead(lpszString0);
  else
    if (ItemIndex == (UINT) CEraComboBox::GetCount() - 1)
      m_ColumnItemList[0].AddTail(lpszString0);
    else
      m_ColumnItemList[0].InsertBefore(m_ColumnItemList[0].FindIndex(ItemIndex), lpszString0);

  va_start(StringPointerPointer, lpszString0);
  for (Index = 1; Index < m_TotalColumn; Index++) {
    StringPointer = va_arg(StringPointerPointer, LPCTSTR);

    if (ItemIndex == 0)
      m_ColumnItemList[Index].AddHead(StringPointer);
    else
      if (ItemIndex == (UINT) CEraComboBox::GetCount() - 1)
        m_ColumnItemList[Index].AddTail(StringPointer);
      else
        m_ColumnItemList[Index].InsertBefore(m_ColumnItemList[Index].FindIndex(ItemIndex), StringPointer);
  }
  va_end(StringPointerPointer);

  return ItemIndex;
}

void CKMComboBox::ResetContent() {
  CEraComboBox::ResetContent();
  for (UINT ColumnIndex = 0; ColumnIndex < m_TotalColumn; ColumnIndex++)
    m_ColumnItemList[ColumnIndex].RemoveAll();
};

void CKMComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) {
  ASSERT(m_TotalColumn > 1);  //You can use CEraComboBox class instead of this class

  CPen*    OldPenPointer;  CDC*    DeviceContextPointer = CDC::FromHandle(lpDrawItemStruct->hDC);
//  CWnd*    DropDownWindowPointer = DeviceContextPointer->GetWindow();
  CWnd*    DropDownWindowPointer = FromHandle(m_hListBox); // This fixes a win2000 crash
  if (!DropDownWindowPointer)
    DropDownWindowPointer = DeviceContextPointer->GetWindow();
  BOOL    IsHighLightText = lpDrawItemStruct->itemAction & ODA_FOCUS || lpDrawItemStruct->itemState & ODS_SELECTED;
  CRect    TextRectangle = lpDrawItemStruct->rcItem;

  DeviceContextPointer->SetTextColor(GetSysColor(IsWindowEnabled() ? (IsHighLightText ? COLOR_HIGHLIGHTTEXT : COLOR_WINDOWTEXT) : COLOR_WINDOWTEXT));
  DeviceContextPointer->SetBkColor(GetSysColor(IsWindowEnabled() ? (IsHighLightText ? COLOR_HIGHLIGHT : COLOR_WINDOW) : COLOR_3DFACE));
  DeviceContextPointer->FillRect(TextRectangle, &CBrush(DeviceContextPointer->GetBkColor()));

  if (IsHighLightText)
    DeviceContextPointer->DrawFocusRect(TextRectangle);

  if (lpDrawItemStruct->itemID != (UINT)-1) {
    if (DropDownWindowPointer != this) { //Draw items in drop down list
      if (TextRectangle.top == 0 && (GetWindowLong(m_hWnd, GWL_STYLE) & 0x3) != CBS_SIMPLE) {
        //Only "dropdwon" & "drop list" combo box can move their drop down window
        CRect    WindowRectangle;
        DropDownWindowPointer->GetWindowRect(WindowRectangle);

        if (WindowRectangle.right > GetSystemMetrics(SM_CXSCREEN)) { //Move drop down window to left if its left side is out of screen
          WindowRectangle.OffsetRect(GetSystemMetrics(SM_CXSCREEN) - WindowRectangle.right, 0);
          DropDownWindowPointer->MoveWindow(WindowRectangle);
        }
      }
    }

    if (!IsHighLightText) {
      OldPenPointer = DeviceContextPointer->SelectObject(&m_LightGrayPen);
      DeviceContextPointer->MoveTo(TextRectangle.left, TextRectangle.bottom - 1);
      DeviceContextPointer->LineTo(TextRectangle.right, TextRectangle.bottom - 1);
    }
    
    TextRectangle.left += LEFTMARGIN_OF_DROPDOWNLIST;
    TextRectangle.right = TextRectangle.left;

    for (UINT ColumnIndex = 0; ColumnIndex < m_TotalColumn; ColumnIndex++) {
      TextRectangle.left = TextRectangle.right;
      if (m_ColumnWidth[ColumnIndex] != 0) {
        if (ColumnIndex > 1 || (ColumnIndex == 1 && m_ColumnWidth[0] != 0)) {  
          TextRectangle.left += SPACE_BETWEEN_COLUMN;
          if (!IsHighLightText) {  //draw vertical gray line
            DeviceContextPointer->MoveTo(TextRectangle.left - SPACE_BETWEEN_COLUMN / 2, TextRectangle.top);
            DeviceContextPointer->LineTo(TextRectangle.left - SPACE_BETWEEN_COLUMN / 2, TextRectangle.bottom);
          }
        }
        TextRectangle.right = TextRectangle.left + m_ColumnWidth[ColumnIndex];
        TextRectangle.left++;

               // if vertical scrool bar is visible
        if ((ColumnIndex == m_TotalColumn - 1 || (ColumnIndex == m_TotalColumn - 2 && m_ColumnWidth[m_TotalColumn - 1] == 0)) && (GetWindowLong(DropDownWindowPointer->m_hWnd, GWL_STYLE) & WS_VSCROLL))
          TextRectangle.right -= GetSystemMetrics(SM_CXVSCROLL);

        DeviceContextPointer->DrawText(m_ColumnItemList[ColumnIndex].GetAt(m_ColumnItemList[ColumnIndex].FindIndex(lpDrawItemStruct->itemID)), -1, TextRectangle,
        m_ColumnAlignStyle[ColumnIndex] | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
      }
    }

    if (!IsHighLightText)
      DeviceContextPointer->SelectObject(OldPenPointer);
  }

}

void CKMComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) {
  lpMeasureItemStruct->itemHeight = m_TextItemHeight;
}

CString CKMComboBox::GetColumnText(int nItem, int nCol) {
  return m_ColumnItemList[nCol].GetAt(m_ColumnItemList[nCol].FindIndex(nItem));
}

LRESULT CKMComboBox::OnCtlColorListBox(WPARAM wParam, LPARAM lParam) {
  if (m_hListBox == 0) {
    HWND hWnd = (HWND)lParam;

    if (hWnd != 0 && hWnd != m_hWnd) {
      // Save the listbox handle
      m_hListBox = hWnd;
    }
  }
  return DefWindowProc(WM_CTLCOLORLISTBOX, wParam, lParam);
}

void CKMComboBox::OnSize(UINT nType, int cx, int cy)  {
	CEraComboBox::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
}
BOOL CKMComboBox::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CEraComboBox::OnMouseWheel(nFlags, zDelta, pt);
}
