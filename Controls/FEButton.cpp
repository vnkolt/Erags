// FEButton.cpp : implementation file
//

#include "stdafx.h"
#include "FEButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFEButton

CFEButton::CFEButton()
{
}

CFEButton::~CFEButton()
{
}


BEGIN_MESSAGE_MAP(CFEButton, CButton)
	//{{AFX_MSG_MAP(CFEButton)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFEButton message handlers

void CFEButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// Draws the button in its various states

	// create a CDC object for drawing
	CDC dc;
	dc.Attach(lpDIS->hDC);

	// create a CBrush for the background colour of the button
	CBrush theBrush(GetSysColor(COLOR_3DFACE));
	CBrush *poldBrush = dc.SelectObject(&theBrush);
	CPen *poldPen, thePen;
	if (lpDIS->itemState & ODS_SELECTED)	// Draw button as selected
	{
		// create the pen used to draw the border
		thePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		poldPen = dc.SelectObject(&thePen);

		// draw the sunken border
		dc.Rectangle(&lpDIS->rcItem);

		// draw the dots
		int x = lpDIS->rcItem.right / 2 - 2;
		int y = lpDIS->rcItem.bottom / 2;
		COLORREF dots = GetSysColor(COLOR_BTNTEXT);
		dc.SetPixel(x, y, dots);
		x += 3;
		dc.SetPixel(x, y, dots);
		x += 3;
		dc.SetPixel(x, y, dots);
	}
	else	// draw button as normal
	{
		// draw the outside border
		thePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DFACE));
		poldPen = dc.SelectObject(&thePen);
		dc.Rectangle(&lpDIS->rcItem);
		dc.SelectObject(poldPen);
		thePen.DeleteObject();

		// draw the top and left sides
		thePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));
		poldPen = dc.SelectObject(&thePen);
		dc.MoveTo(lpDIS->rcItem.left+1, lpDIS->rcItem.bottom-1);
		dc.LineTo(lpDIS->rcItem.left+1, lpDIS->rcItem.top+1);
		dc.LineTo(lpDIS->rcItem.right-2, lpDIS->rcItem.top+1);
		dc.SelectObject(poldPen);
		thePen.DeleteObject();

		// draw the bottom and right sides (top edge)
		thePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));
		poldPen = dc.SelectObject(&thePen);
		dc.LineTo(lpDIS->rcItem.right-2, lpDIS->rcItem.bottom-2);
		dc.LineTo(lpDIS->rcItem.left+1, lpDIS->rcItem.bottom-2);
		dc.SelectObject(poldPen);
		thePen.DeleteObject();

		// draw the bottom and right sides (bottom edge)
		thePen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));
		poldPen = dc.SelectObject(&thePen);
		dc.MoveTo(lpDIS->rcItem.right-1, lpDIS->rcItem.top);
		dc.LineTo(lpDIS->rcItem.right-1, lpDIS->rcItem.bottom-1);
		dc.LineTo(lpDIS->rcItem.left, lpDIS->rcItem.bottom-1);

		// draw the dots
		int x = lpDIS->rcItem.right / 2 - 3;
		int y = lpDIS->rcItem.bottom / 2 - 1;
		COLORREF dots;
		if (lpDIS->itemState & ODS_DISABLED)
			dots = GetSysColor(COLOR_GRAYTEXT);
		else
			dots = GetSysColor(COLOR_BTNTEXT);
		dc.SetPixel(x, y, dots);
		x += 3;
		dc.SetPixel(x, y, dots);
		x += 3;
		dc.SetPixel(x, y, dots);
		if (lpDIS->itemState & ODS_DISABLED)
		{
			x = lpDIS->rcItem.right / 2 - 2;
			y = lpDIS->rcItem.bottom / 2;
			dots = GetSysColor(COLOR_3DHILIGHT);
			dc.SetPixel(x, y, dots);
			x += 3;
			dc.SetPixel(x, y, dots);
			x += 3;
			dc.SetPixel(x, y, dots);
		}
	}
	dc.SelectObject(poldBrush);
	dc.SelectObject(poldPen);
	thePen.DeleteObject();
	theBrush.DeleteObject();
	dc.Detach();
}

void CFEButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// button should not keep the focus
	CButton::OnLButtonUp(nFlags, point);
	GetParent()->SetFocus();
}


