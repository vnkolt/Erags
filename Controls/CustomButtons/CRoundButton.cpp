//---------------------------------------------------------------------------
//	THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. 
//	THE AUTHOR DISCLAIMS ALL WARRANTIES, EITHER EXPRESS OR IMPLIED, 
//	INCLUDING THE WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
//	PARTICULAR PURPOSE. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR 
//	ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL, 
//	CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, 
//
//	Written by Chris Maunder (chrismaunder@codeguru.com)
//	Copyright (c) 1998.
//	Adapted to work with CCustomButton as a base class.
//
//---------------------------------------------------------------------------

#include "stdafx.h"

#ifndef _CROUNDBUTTON_
#include "CRoundButton.h"
#endif

#include <MMSystem.h>

#ifdef _ERAGS
#include "..\..\Erags\resource.h"       // main symbols
#endif


#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoundButton
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CRoundButton,CCustomButton)

BEGIN_MESSAGE_MAP(CRoundButton,CCustomButton)
	//{{AFX_MSG_MAP(CRoundButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
//
bool CRoundButton::s_Hovering=false;


/////////////////////////////////////////////////////////////////////////////
// Calculate colour for a point at the given angle by performing a linear
// interpolation between the colours crBright and crDark based on the cosine
// of the angle between the light source and the point.
//
// Angles are measured from the +ve x-axis (i.e. (1,0) = 0 degrees, (0,1) = 90 degrees )
// But remember: +y points down!
/////////////////////////////////////////////////////////////////////////////

COLORREF CRoundButton::GetColour(double dAngle,COLORREF crBright,COLORREF crDark)
{
	const double Pi=3.1415;
	const double LIGHT_SOURCE_ANGLE=	-2.356;// -2.356 radians = -135 degrees, i.e. From top left

	ASSERT(dAngle > -3.1416 && dAngle < 3.1416);
	double dAngleDifference = LIGHT_SOURCE_ANGLE - dAngle;

	if (dAngleDifference <-Pi) 
		dAngleDifference = 6.293 + dAngleDifference;
	else if (dAngleDifference >Pi) 
		dAngleDifference = 6.293 - dAngleDifference;

	double Weight = 0.5*(cos(dAngleDifference)+1.0);

	BYTE Red   = (BYTE) (Weight*GetRValue(crBright) + (1.0-Weight)*GetRValue(crDark));
	BYTE Green = (BYTE) (Weight*GetGValue(crBright) + (1.0-Weight)*GetGValue(crDark));
	BYTE Blue  = (BYTE) (Weight*GetBValue(crBright) + (1.0-Weight)*GetBValue(crDark));

	return RGB(Red, Green, Blue);
}

/////////////////////////////////////////////////////////////////////////////
//
void CRoundButton::DrawCircle(CDC* pDC,CPoint p,LONG lRadius,COLORREF crColour,BOOL bDashed)
{
	const int nDashLength = 1;

	//Check to see that the coordinates are valid
	ASSERT((p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT((p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	BOOL bDashOn = TRUE;
	int  nDash = 0;
	//Set starting values
	LONG lXoffset = lRadius;
	LONG lYoffset = 0;
	LONG lError   = -lRadius;

	do 
		{
		if(bDashOn) 
			{
			pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);
			}
		//Advance the error term and the constant X axis step
		lError+=lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

		if (bDashed && (++nDash == nDashLength)) 
			{
			nDash = 0;
			bDashOn = !bDashOn;
			}
		}while (lYoffset <= lXoffset);//Continue until halfway point
} 

/////////////////////////////////////////////////////////////////////////////
//
void CRoundButton::DrawCircle(CDC* pDC,CPoint p,LONG lRadius,COLORREF crBright,COLORREF crDark)
{
	const double	Pi = 3.141592654; 
	const double	Pi_on_2 = Pi * 0.5;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	LONG lXoffset = lRadius;
	LONG lYoffset = 0;
	LONG lError   = -lRadius;

	do 
		{
		COLORREF crColour;
		double   dAngle = atan2(lYoffset,lXoffset);

		//Draw the current pixel, reflected across all eight arcs
		crColour = GetColour(dAngle,crBright,crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset,crColour);

		crColour = GetColour(Pi_on_2-dAngle,crBright,crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);

		crColour = GetColour(Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);

		crColour = GetColour(Pi - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);

		crColour = GetColour(-Pi + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);

		crColour = GetColour(-Pi_on_2 - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);

		crColour = GetColour(-Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);

		crColour = GetColour(-dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

		} while (lYoffset <= lXoffset);	//Continue until halfway point
} 


/////////////////////////////////////////////////////////////////////////////
//Override to define extra hover behaviour
//
void	CRoundButton::OnHover(bool bEnteringButton)
{
	if(bEnteringButton)
		::PlaySound((LPCTSTR)IDR_WAVE1,AfxGetResourceHandle(),SND_RESOURCE | SND_ASYNC);
}

/////////////////////////////////////////////////////////////////////////////
//Override to define own hit testing
//
bool CRoundButton::ModifyHitRegion(const CRect& rClient,CHitRgn& hitRgn)
{
	CRect r=rClient;
	// Resize the window to make it square
	r.bottom=r.right=min(r.bottom,r.right);

	// Create round hit region
	return hitRgn.CreateEllipticRgnIndirect(r)!=FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//Draw the button based on the current state as defined in state.

void	CRoundButton::OnDraw(CDC* pDC,const CCustomButtonState& state)
{	
	CRect r					=state.m_rClient;
	int nHoverRadius=GetRadius(r);
	int nRadius			=nHoverRadius-2;//Allow a hover rim
	CPoint centre		=r.CenterPoint();

	UINT nStyle			=GetStyle();
	int nSavedDC		=pDC->SaveDC();

	COLORREF c3DLight			=::GetSysColor(COLOR_3DLIGHT);
	COLORREF c3DHighlight	=::GetSysColor(COLOR_3DHIGHLIGHT);
	COLORREF c3DShadow		=::GetSysColor(COLOR_3DSHADOW);
	COLORREF c3DDkShadow	=::GetSysColor(COLOR_3DDKSHADOW);

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->FillSolidRect(r,::GetSysColor(COLOR_BTNFACE));

	// Draw the focus circle around the button
	if (state.m_bFocused)
		DrawCircle(pDC,centre,nRadius--,RGB(0,0,0));

	// Draw the raised/sunken edges of the button (unless flat)
	if (nStyle & BS_FLAT) 
		{
		DrawCircle(pDC,centre,nRadius--,RGB(0,0,0));
		DrawCircle(pDC,centre,nRadius--,c3DHighlight);
		} 
	else 
		{
		if(state.m_bSelected || state.m_bHilited)	
			{
			DrawCircle(pDC,centre,nRadius--,c3DDkShadow,c3DHighlight);
			DrawCircle(pDC,centre,nRadius--,c3DShadow,c3DLight);
			} 
		else 
			{
			DrawCircle(pDC,centre,nRadius--,c3DHighlight,c3DDkShadow);
			DrawCircle(pDC,centre,nRadius--,c3DLight,c3DShadow);
			}
		}
	
	// draw the text if there is any
	if(!state.m_sText.IsEmpty())
		{
		CRgn rgn;
		rgn.CreateEllipticRgn(centre.x-nRadius,centre.y-nRadius,
													centre.x+nRadius,centre.y+nRadius);
		pDC->SelectClipRgn(&rgn);

		CSize Extent=pDC->GetTextExtent(state.m_sText);
		CPoint pt		=CPoint(centre.x-Extent.cx/2,centre.x-Extent.cy/2);

		if (state.m_bSelected || state.m_bHilited) 
			pt.Offset(1,1);

		pDC->SetBkMode(TRANSPARENT);

		if (!state.m_bEnabled)
			pDC->DrawState(pt,Extent,state.m_sText,DSS_DISABLED,TRUE,0,(HBRUSH)NULL);
		else
			pDC->TextOut(pt.x,pt.y,state.m_sText);

		pDC->SelectClipRgn(NULL);
		rgn.DeleteObject();
		}

	// Draw the focus circle on the inside of the button
	if (state.m_bFocused)
		DrawCircle(pDC,centre,nRadius-1,RGB(0,0,0),TRUE);

	// Draw the hover hilite
	if (state.m_bHovering)
		{
		DrawCircle(pDC,centre,nHoverRadius,c3DHighlight,c3DShadow);
		DrawCircle(pDC,centre,nHoverRadius-1,c3DHighlight,c3DHighlight);
		}
	pDC->RestoreDC(nSavedDC);
}


/////////////////////////////////////////////////////////////////////////////

