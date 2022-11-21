// TextProgressCtrl.cpp : implementation file
//
// Written by Chris Maunder (cmaunder@mail.com)
// Copyright 1998.
//
// TextProgressCtrl is a drop-in replacement for the standard 
// CProgressCtrl that displays text in a progress control.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed by any means PROVIDING it is not sold for
// profit without the authors written consent, and providing that this
// notice and the authors name is included. If the source code in 
// this file is used in any commercial application then an email to
// the me would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer or anything else vaguely within it's vicinity.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#include "stdafx.h"
#include "TextProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifndef _MEMDC_H_
//////////////////////////////////////////////////
// CMemDC - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//
// This class implements a memory Device Context

class CMemDC : public CDC
{
public:

    // constructor sets up the memory DC
    CMemDC(CDC* pDC) : CDC()
    {
        ASSERT(pDC != NULL);

        m_pDC = pDC;
        m_pOldBitmap = NULL;
        m_bMemDC = !pDC->IsPrinting();
              
        if (m_bMemDC)    // Create a Memory DC
        {
            pDC->GetClipBox(&m_rect);
            CreateCompatibleDC(pDC);
            m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
            m_pOldBitmap = SelectObject(&m_bitmap);
            SetWindowOrg(m_rect.left, m_rect.top);
        }
        else        // Make a copy of the relevent parts of the current DC for printing
        {
            m_bPrinting = pDC->m_bPrinting;
            m_hDC       = pDC->m_hDC;
            m_hAttribDC = pDC->m_hAttribDC;
        }
    }
    
    // Destructor copies the contents of the mem DC to the original DC
    ~CMemDC()
    {
        if (m_bMemDC) 
        {    
            // Copy the offscreen bitmap onto the screen.
            m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                          this, m_rect.left, m_rect.top, SRCCOPY);

            //Swap back the original bitmap.
            SelectObject(m_pOldBitmap);
        } else {
            // All we need to do is replace the DC with an illegal value,
            // this keeps us from accidently deleting the handles associated with
            // the CDC that was passed to the constructor.
            m_hDC = m_hAttribDC = NULL;
        }
    }

    // Allow usage as a pointer
    CMemDC* operator->() {return this;}
        
    // Allow usage as a pointer
    operator CMemDC*() {return this;}

private:
    CBitmap  m_bitmap;      // Offscreen bitmap
    CBitmap* m_pOldBitmap;  // bitmap originally found in CMemDC
    CDC*     m_pDC;         // Saves CDC passed in constructor
    CRect    m_rect;        // Rectangle of drawing area.
    BOOL     m_bMemDC;      // TRUE if CDC really is a Memory DC.
};

#endif



/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl

CTextProgressCtrl::CTextProgressCtrl()
{
    m_nPos      = 0;
    m_nStepSize = 1;
    m_nMax      = 100;
    m_nMin      = 0;
    m_bShowText = TRUE;
    m_strText.Empty();
    m_crBarClr  = CLR_DEFAULT;
    m_crBgClr   = CLR_DEFAULT;

    m_nBarWidth = -1;
}

CTextProgressCtrl::~CTextProgressCtrl()
{
}

BEGIN_MESSAGE_MAP(CTextProgressCtrl, CProgressCtrl)
    //{{AFX_MSG_MAP(CTextProgressCtrl)
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_SIZE()
    //}}AFX_MSG_MAP
    ON_MESSAGE(WM_SETTEXT, OnSetText)
    ON_MESSAGE(WM_GETTEXT, OnGetText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl message handlers

LRESULT CTextProgressCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
    LRESULT result = Default();

    LPCTSTR szText = (LPCTSTR)lParam;

    if ( (!szText && m_strText.GetLength()) ||
         (szText && (m_strText != szText))   )
    {
        m_strText = szText;
        Invalidate();
    }

    return result;
}

LRESULT CTextProgressCtrl::OnGetText(WPARAM cchTextMax, LPARAM szText)
{
    if (!_tcsncpy((LPTSTR)szText, m_strText, cchTextMax))
        return 0;
    else 
        return min(cchTextMax, (UINT) m_strText.GetLength());
}

BOOL CTextProgressCtrl::OnEraseBkgnd(CDC* /*pDC*/) 
{    
     return TRUE;
}

void CTextProgressCtrl::OnSize(UINT nType, int cx, int cy) 
{
    CProgressCtrl::OnSize(nType, cx, cy);
    
    m_nBarWidth    = -1;   // Force update if SetPos called
}

void CTextProgressCtrl::OnPaint() 
{
    if (m_nMin >= m_nMax) 
        return;

    COLORREF crBarColour, crBgColour;

    crBarColour = (m_crBarClr == CLR_DEFAULT)? ::GetSysColor(COLOR_HIGHLIGHT) : m_crBarClr;
    crBgColour = (m_crBgClr == CLR_DEFAULT)? ::GetSysColor(COLOR_WINDOW) : m_crBgClr;

    CRect LeftRect, RightRect, ClientRect;
    GetClientRect(ClientRect);

    double Fraction = (double)(m_nPos - m_nMin) / ((double)(m_nMax - m_nMin));

    CPaintDC PaintDC(this); // device context for painting
    CMemDC dc(&PaintDC);
    //CPaintDC dc(this);    // device context for painting (if not double buffering)

    // Draw Bar
    LeftRect = RightRect = ClientRect;

#ifdef PBS_VERTICAL
    DWORD dwStyle = GetStyle();
    if (dwStyle & PBS_VERTICAL)
    {
        LeftRect.top = LeftRect.bottom - (int)((LeftRect.bottom - LeftRect.top)*Fraction);
        RightRect.bottom = LeftRect.top;
    }
    else
#endif
    {
        LeftRect.right = LeftRect.left + (int)((LeftRect.right - LeftRect.left)*Fraction);
        RightRect.left = LeftRect.right;
    }
    dc.FillSolidRect(LeftRect, crBarColour);
    dc.FillSolidRect(RightRect, crBgColour);

    // Draw Text if not vertical
    if (m_bShowText
#ifdef PBS_VERTICAL
        && (dwStyle & PBS_VERTICAL) == 0
#endif
        )
    {
        CString str;
        if (m_strText.GetLength())
            str = m_strText;
        else
            str.Format(_T("%d%%"), (int)(Fraction*100.0));

        dc.SetBkMode(TRANSPARENT);

        DWORD dwTextStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE;

        // If we are drawing vertical, then create a new verticla font
        // based on the current font (only works with TrueType fonts)
        CFont font, *pOldFont = NULL;
#ifdef PBS_VERTICAL
        if (dwStyle & PBS_VERTICAL)
        {
            LOGFONT lf;
            GetFont()->GetLogFont(&lf);
            lf.lfEscapement = lf.lfOrientation = 900;
            font.CreateFontIndirect(&lf);
            pOldFont = (CFont*) dc.SelectObject(&font);

            dwTextStyle = DT_VCENTER|DT_CENTER|DT_SINGLELINE;
        }
#endif

        CRgn rgn;
        rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
        dc.SelectClipRgn(&rgn);
        dc.SetTextColor(crBgColour);
        dc.DrawText(str, ClientRect, dwTextStyle);

        rgn.DeleteObject();
        rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
        dc.SelectClipRgn(&rgn);
        dc.SetTextColor(crBarColour);
        dc.DrawText(str, ClientRect, dwTextStyle);

        if (pOldFont)
        {
            dc.SelectObject(pOldFont);
            font.DeleteObject();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl operations

void CTextProgressCtrl::SetShowText(BOOL bShow)
{ 
    if (::IsWindow(m_hWnd) && m_bShowText != bShow)
        Invalidate();

    m_bShowText = bShow;
}

void CTextProgressCtrl::SetRange(int nLower, int nUpper)
{
    m_nMax = nUpper;
    m_nMin = nLower;
}

void CTextProgressCtrl::GetRange(int& nLower, int& nUpper) const
{
    nUpper = m_nMax;
    nLower = m_nMin;
}

int CTextProgressCtrl::SetPos(int nPos) 
{    
    if (!::IsWindow(m_hWnd))
        return -1;
	//[TD]
	UpdateText();
	//[/TD]
    int nOldPos = m_nPos;
    m_nPos = nPos;

    CRect rect;
    GetClientRect(rect);

    double Fraction = (double)(m_nPos - m_nMin) / ((double)(m_nMax - m_nMin));
    int nBarWidth = (int) (Fraction * rect.Width());
	
    if (nBarWidth != m_nBarWidth)
    {
        m_nBarWidth = nBarWidth;
        RedrawWindow();
    }

    return nOldPos;
}

int CTextProgressCtrl::StepIt() 
{    
   return SetPos(m_nPos + m_nStepSize);
}

int CTextProgressCtrl::OffsetPos(int nPos)
{
    return SetPos(m_nPos + nPos);
}

int CTextProgressCtrl::SetStep(int nStep)
{
    int nOldStep = m_nStepSize;
    m_nStepSize = nStep;
    return nOldStep;
}

COLORREF CTextProgressCtrl::SetBarColour(COLORREF crBarClr /*= CLR_DEFAULT*/)
{
    if (::IsWindow(m_hWnd))
        Invalidate();

    COLORREF crOldBarClr = m_crBarClr;
    m_crBarClr = crBarClr;
    return crOldBarClr;
}

COLORREF CTextProgressCtrl::GetBarColour() const
{ 
    return m_crBarClr;
}

COLORREF CTextProgressCtrl::SetBgColour(COLORREF crBgClr /*= CLR_DEFAULT*/)
{
    if (::IsWindow(m_hWnd))
        Invalidate();

    COLORREF crOldBgClr = m_crBgClr;
    m_crBgClr = crBgClr;
    return crOldBgClr;
}

COLORREF CTextProgressCtrl::GetBgColour() const
{ 
    return m_crBgClr;
}

//TD modifications (just for TestDlg needs
//[TD]
void CTextProgressCtrl::Init(DWORD iRange)
{
	if (!iRange)
		return;
	ShowWindow(SW_SHOW);
	SetRange(0, iRange);
	SetPos(0);
}

void CTextProgressCtrl::Hide(bool bHide)
{
	ShowWindow(bHide ? SW_HIDE : SW_SHOW);
}

void CTextProgressCtrl::UpdateText()
{
	CString sz;
	sz.Format(_T("%.2f %%"), m_nMax > 0 ? ((float)m_nPos * 100 / m_nMax) : 0);
	SetWindowText(sz);

}
//[/TD]